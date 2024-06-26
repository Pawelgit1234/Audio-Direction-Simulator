﻿#include "App.hpp"

namespace ads
{
    namespace window
    {
        App::App()
            : window_(sf::VideoMode(settings::WINDOW_WIDTH, settings::WINDOW_HEIGHT), settings::WINDOW_NAME),
            speaker_zone_(window_), timeline_zone_(window_)
        {
            window_.setFramerateLimit(settings::FRAMERATE_LIMIT);

            sf::Image icon;
            if (!icon.loadFromFile(settings::ICON_PATH))
            {
                icon.create(32, 32, sf::Color(255, 255, 255));
                ads::utils::log("Failed to load icon.", ads::utils::LoggerType::WARNING);
            }

            window_.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
        }

        void App::run()
        {
            ads::utils::log("Program started.", ads::utils::LoggerType::INFO);

            addSpeakers();
            while (window_.isOpen())
            {
                window_.clear();
                controll();
                handleSpeakerMovementZone();
                handleTimeLineZone();
                window_.display();
            }
        }

        void App::handleSpeakerMovementZone()
        {
            for (const auto& speaker : speaker_zone_.dynamic_speakers_)
            {
                unsigned short ray_count = 0;

                if (!speaker.getActive())
                {
                    sound_manager_.stopSound(speaker.getId());
                    continue;
                }

                sf::Vector2f speakerPos = speaker.getCircle().getPosition();
                speakerPos.x += speaker.getCircle().getRadius();
                speakerPos.y += speaker.getCircle().getRadius();

                for (const auto& direction : speaker.getRayDirections())
                {
                    sf::VertexArray ray(sf::Lines, 2);
                    ray[0].position = speakerPos;
                    ray[1].position = speakerPos + direction * settings::RAY_LENGTH;
                    ray[0].color = settings::RAY_COLOR;
                    ray[1].color = settings::RAY_COLOR;

                    sf::Vector2f intersectionPointEar;
                    sf::Vector2f intersectionPointWall;

                    intersectionPointEar = utils::rayIntersectsCircle(ray[0].position, direction, speaker_zone_.ear_.getCircle());

                    for (const auto& wall : speaker_zone_.walls_)
                    {
                        if (!wall.getActive())
                            continue;

                        intersectionPointWall = utils::rayIntersectsWall(ray[0].position, direction, wall.getRectangle());
                        if (intersectionPointWall != sf::Vector2f(0.f, 0.f))
                            break;
                    }

                    if (intersectionPointEar == sf::Vector2f(0.f, 0.f) && intersectionPointWall != sf::Vector2f(0.f, 0.f))
                        ray[1].position = intersectionPointWall;
                    else if (intersectionPointEar != sf::Vector2f(0.f, 0.f) && intersectionPointWall == sf::Vector2f(0.f, 0.f))
                    {
                        ray[1].position = intersectionPointEar;
                        ray_count++;
                    }
                    else if (intersectionPointEar != sf::Vector2f(0.f, 0.f) && intersectionPointWall != sf::Vector2f(0.f, 0.f))
                    {
                        float earDistance = utils::distance(speaker.getCircle().getPosition(), intersectionPointEar);
                        float wallDistance = utils::distance(speaker.getCircle().getPosition(), intersectionPointWall);

                        if (earDistance < wallDistance)
                            ray[1].position = intersectionPointEar;
                        else
                            ray[1].position = intersectionPointWall;
                    }

                    if (direction.x > 0)
                    {
                        if (ray[1].position.x > speakerPos.x + direction.x * settings::RAY_LENGTH)
                            ray[1].position = speakerPos + direction * settings::RAY_LENGTH;
                    }
                    else
                    {
                        if (ray[1].position.x < speakerPos.x + direction.x * settings::RAY_LENGTH)
                            ray[1].position = speakerPos + direction * settings::RAY_LENGTH;
                    }

                    window_.draw(ray);
                }

                bool wasSoundPlayed = sound_manager_.isSoundPlaying(speaker.getId());
                
                if (speaker.getActive() && ray_count > 0 && timeline_zone_.is_running_)
                {
                    utils::TimelineTimer play_timer;

                    for (const auto& bar : timeline_zone_.bars_)
                    {
                        if (bar.isWall())
                            continue;

                        if (bar.getObjectId() == speaker.getId())
                        {
                            for (const auto& slice : bar.getSlices())
                            {
                                if (slice.start_.convertPositionFromTime() < timeline_zone_.marker_pos_ && timeline_zone_.marker_pos_ < slice.end_.convertPositionFromTime())
                                {
                                    play_timer = slice.sound_start_;
                                    break;
                                }
                            }
                            break;
                        }
                    }

                    if (!wasSoundPlayed)
                        sound_manager_.playSound(speaker.getId(), speaker.getSoundLevel(), (float)ray_count / (settings::RAY_COUNT / 2), play_timer);
                    else
                        sound_manager_.setVolume(speaker.getId(), speaker.getSoundLevel(), (float)ray_count / (settings::RAY_COUNT / 2));
                }
                else
                {
                    if (wasSoundPlayed)
                        sound_manager_.stopSound(speaker.getId());
                }

                window_.draw(speaker.getCircle());
            }

            for (const auto& wall : speaker_zone_.walls_)
            {
                if (!wall.getActive())
                    continue;

                window_.draw(wall.getRectangle());
            }

            window_.draw(speaker_zone_.ear_.getCircle());
        }

        void App::handleTimeLineZone()
        {
            timeline_zone_.updateTimeText();
            timeline_zone_.updatePositionAtWindow(speaker_zone_.zoom_);
            std::vector<unsigned short> lines = timeline_zone_.checkActive();

            for (object::TimelineBar& bar : timeline_zone_.bars_)
            {
                bool isActive = false;
                if (std::find(lines.begin(), lines.end(), bar.getLine()) == lines.end())
                    isActive = true;

                if (bar.isWall())
                {
                    auto wall = std::find_if(speaker_zone_.walls_.begin(), speaker_zone_.walls_.end(), [bar](const object::Wall& wall) {
                        return wall.getId() == bar.getObjectId();
                        });

                    wall->setActive(isActive);
                }
                else
                {
                    auto speaker = std::find_if(speaker_zone_.dynamic_speakers_.begin(), speaker_zone_.dynamic_speakers_.end(), [bar](const object::DynamicSpeaker& speaker) {
                        return speaker.getId() == bar.getObjectId();
                        });

                    speaker->setActive(isActive);
                }
            }

            if (timeline_zone_.is_running_)
                timeline_zone_.updateMarkerPosition();

            window_.draw(timeline_zone_.panel_);

            for (object::TimelineBar& bar : timeline_zone_.bars_)
                for (const object::TimelineBarSlice& slice : bar.getSlices())
                    window_.draw(const_cast<sf::RectangleShape&>(slice.rect_));

            window_.draw(timeline_zone_.marker_);
            window_.draw(timeline_zone_.time_panel_);
            window_.draw(timeline_zone_.time_text_);
        }


        void App::controll()
        {
            sf::Vector2i lastMousePos = sf::Mouse::getPosition(window_);

            sf::Event event;
            while (window_.pollEvent(event))
            {
                switch (event.type)
                {
                case sf::Event::Closed:
                    window_.close();
                    break;
                case sf::Event::Resized:
                    speaker_zone_.view_.setSize(sf::Vector2f(event.size.width, event.size.height));
                    window_.setView(speaker_zone_.view_);
                    break;
                case sf::Event::MouseWheelScrolled:
                {
                    sf::Vector2f mousePos = window_.mapPixelToCoords(sf::Mouse::getPosition(window_), speaker_zone_.view_);

                    if (utils::isInsideRectangle(mousePos, timeline_zone_.panel_))
                    {
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))
                        {
                            if (event.mouseWheelScroll.delta > 0)
                                timeline_zone_.timeline_pos_y_ -= 15;
                            else if (event.mouseWheelScroll.delta < 0)
                                timeline_zone_.timeline_pos_y_ += 15;
                        }
                        else
                        {
                            if (event.mouseWheelScroll.delta > 0)
                                timeline_zone_.timeline_pos_x_ -= 20.f;
                            else if (event.mouseWheelScroll.delta < 0)
                                timeline_zone_.timeline_pos_x_ += 20.f;
                        } 
                    }
                    else
                    {
                        if (event.mouseWheelScroll.delta > 0)
                        {
                            speaker_zone_.view_.zoom(1.1f);
                            speaker_zone_.zoom_ *= 1.1f;
                        }
                        else if (event.mouseWheelScroll.delta < 0)
                        {
                            speaker_zone_.view_.zoom(0.9f);
                            speaker_zone_.zoom_ *= 0.9f;
                        }
                        window_.setView(speaker_zone_.view_);
                    }
                    break;
                }
                case sf::Event::MouseButtonPressed:
                {
                    sf::Vector2f mousePos = window_.mapPixelToCoords(sf::Mouse::getPosition(window_), speaker_zone_.view_);

                    if (utils::isInsideRectangle(mousePos, timeline_zone_.panel_))
                    {
                        if (utils::isInsideRectangle(mousePos, timeline_zone_.marker_))
                        {
                            while (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                            {
                                sf::Vector2i mousePos = sf::Mouse::getPosition(window_);
                                sf::Vector2i delta = mousePos - lastMousePos;

                                timeline_zone_.marker_pos_ += static_cast<float>(delta.x) / settings::TIMELINE_DRAGGING_EQUALIZER;
                                lastMousePos = mousePos;
                            }

                            break;
                        }
                        else
                        {
                            for (object::TimelineBar& bar : timeline_zone_.bars_)
                            {
                                for (const object::TimelineBarSlice& slice : bar.getSlices())
                                {
                                    if (utils::isInsideRectangle(mousePos, slice.rect_))
                                    {
                                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
                                        {
                                            sf::Vector2i mousePos = sf::Mouse::getPosition(window_);
                                            timeline_zone_.cut(static_cast<float>(mousePos.x), slice.id_);
                                            return;
                                        }
                                        else
                                        {
                                            sf::Vector2i mousePos;
                                            while (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                                                mousePos = sf::Mouse::getPosition(window_);

                                            sf::Vector2i delta = mousePos - lastMousePos;
                                            timeline_zone_.moveSlice(static_cast<float>(delta.x) / settings::TIMELINE_DRAGGING_EQUALIZER, slice.id_);
                                            lastMousePos = mousePos;
                                            return;
                                        }
                                    }
                                }
                            }

                            break;
                        }
                        
                        break;
                    }

                    if (utils::isInsideCircle(sf::Vector2f(mousePos), speaker_zone_.ear_.getCircle()))
                    {
                        for (auto& speaker : speaker_zone_.dynamic_speakers_)
                            speaker.updateRays();

                        while (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                        {
                            sf::Vector2i mousePos = sf::Mouse::getPosition(window_);
                            sf::Vector2i delta = mousePos - lastMousePos;

                            speaker_zone_.ear_.move(static_cast<float>(delta.x), static_cast<float>(delta.y));
                            window_.setView(speaker_zone_.view_);

                            lastMousePos = mousePos;
                        }
                        break;
                    }

                    for (auto& speaker : speaker_zone_.dynamic_speakers_)
                    {
                        speaker.updateRays();
                        if (utils::isInsideCircle(sf::Vector2f(mousePos), speaker.getCircle()))
                        {
                            while (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                            {
                                sf::Vector2i mousePos = sf::Mouse::getPosition(window_);
                                sf::Vector2i delta = mousePos - lastMousePos;

                                speaker.move(static_cast<float>(delta.x), static_cast<float>(delta.y));
                                window_.setView(speaker_zone_.view_);

                                lastMousePos = mousePos;
                            }

                            break;
                        }
                    }

                    for (auto& wall : speaker_zone_.walls_)
                    {
                        for (auto& speaker : speaker_zone_.dynamic_speakers_)
                            speaker.updateRays();

                        if (utils::isInsideRectangle(sf::Vector2f(mousePos), wall.getRectangle()))
                        {
                            while (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                            {
                                sf::Vector2i mousePos = sf::Mouse::getPosition(window_);
                                sf::Vector2i delta = mousePos - lastMousePos;

                                wall.move(static_cast<float>(delta.x), static_cast<float>(delta.y));
                                window_.setView(speaker_zone_.view_);

                                lastMousePos = mousePos;
                            }

                            break;
                        }
                    }

                    while (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                    {
                        sf::Vector2i mousePos = sf::Mouse::getPosition(window_);
                        sf::Vector2i delta = mousePos - lastMousePos;

                        speaker_zone_.view_.move(-static_cast<float>(delta.x), -static_cast<float>(delta.y));
                        window_.setView(speaker_zone_.view_);

                        lastMousePos = mousePos;
                    }
                    break;
                }
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Space)
                        timeline_zone_.is_running_ = !timeline_zone_.is_running_;
                    break;
                }
            }
        }

        void App::addSpeakers()
        {
            for (const auto& entry : std::filesystem::directory_iterator(settings::SPEAKERS_PATH))
            {
                if (entry.is_regular_file() && utils::endsWith(entry.path().filename().string(), ".wav"))
                {
                    unsigned short id = speaker_zone_.dynamic_speakers_.size() + 1;
                    speaker_zone_.addDynamicSpeaker(id);
                    sound_manager_.loadSound(id, entry.path().string());
                    timeline_zone_.addSpeakerBar(utils::TimelineTimer(0, 0, 0), sound_manager_.getSoundLenght(id), id);
                }
            }
        }
    } 
}
