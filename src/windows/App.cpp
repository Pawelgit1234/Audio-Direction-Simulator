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
                handleSpeakerMovementZone();
                handleSequenserZone();
                window_.display();
            }
        }

        void App::handleSpeakerMovementZone()
        {
            speaker_zone_.controll();

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

                    window_.draw(ray);
                }

                window_.draw(speaker.getCircle());
            }

            for (const auto& wall : speaker_zone_.walls_)
                window_.draw(wall.getRectangle());

            window_.draw(speaker_zone_.ear_.getCircle());
        }

        void App::handleSequenserZone()
        {
            sequenser_zone_.update(speaker_zone_.zoom_);
            window_.draw(sequenser_zone_.panel_);
        }
    }
}
