#include "App.hpp"

namespace ads
{
    namespace window
    {
        App::App()
            : window_(sf::VideoMode(settings::WINDOW_WIDTH, settings::WINDOW_HEIGHT), settings::WINDOW_NAME),
            speaker_zone_(window_), sequenser_zone_(window_)
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

            speaker_zone_.addDynamicSpeaker(1);  // delete
            speaker_zone_.addDynamicSpeaker(2);  // delete
            speaker_zone_.addWall(1);  // delete

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
                        intersectionPointWall = utils::rayIntersectsWall(ray[0].position, direction, wall.getRectangle());
                        if (intersectionPointWall != sf::Vector2f(0.f, 0.f))
                            break;
                    }

                    if (intersectionPointEar == sf::Vector2f(0.f, 0.f) && intersectionPointWall != sf::Vector2f(0.f, 0.f))
                        ray[1].position = intersectionPointWall;
                    else if (intersectionPointEar != sf::Vector2f(0.f, 0.f) && intersectionPointWall == sf::Vector2f(0.f, 0.f))
                        ray[1].position = intersectionPointEar;
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

                window_.draw(speaker.getCircle());
            }

            for (const auto& wall : speaker_zone_.walls_)
                window_.draw(wall.getRectangle());

            window_.draw(speaker_zone_.ear_.getCircle());
        }

        void App::handleTimeLineZone()
        {
            sequenser_zone_.update(speaker_zone_.zoom_);
            window_.draw(sequenser_zone_.panel_);
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
                    break;
                case sf::Event::MouseButtonPressed:
                    sf::Vector2f mousePos = window_.mapPixelToCoords(sf::Mouse::getPosition(window_), speaker_zone_.view_);

                    if (utils::isInsideRectangle(mousePos, sequenser_zone_.panel_))
                    {
                        
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
            }
        }
    }
}
