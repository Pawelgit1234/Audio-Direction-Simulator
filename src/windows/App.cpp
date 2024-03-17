#include "App.hpp"

namespace ads
{
    namespace window
    {
        App::App()
            : window_(sf::VideoMode(settings::WINDOW_WIDTH, settings::WINDOW_HEIGHT), settings::WINDOW_NAME),
            speaker_zone_(window_)
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
                speakerPos.x += 50;
                speakerPos.y += 50;
                for (const auto& direction : speaker.getRayDirections())
                {
                    sf::VertexArray ray(sf::Lines, 2);
                    ray[0].position = speakerPos;
                    ray[1].position = speakerPos + direction * settings::RAY_LENGHT;
                    ray[0].color = settings::RAY_COLOR;
                    ray[1].color = settings::RAY_COLOR;
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
            
        }
    }
}
