#include "App.hpp"

namespace ads
{
    namespace window
    {
        App::App()
            : window_(sf::VideoMode(settings::WINDOW_WIDTH, settings::WINDOW_HEIGHT), settings::WINDOW_NAME),
            speaker_zone_(window_)
        {
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

            while (window_.isOpen())
            {
                handleSpeakerMovementZone();
                handleSequenserZone();
            }
        }

        void App::handleSpeakerMovementZone()
        {
            window_.clear();
            speaker_zone_.controll();

            for (const auto& speaker : speaker_zone_.dynamic_speakers_)
            {
                sf::CircleShape circle(settings::OBJECT_SIZE);
                circle.setFillColor(sf::Color::Red);
                circle.setPosition(speaker.getX(), speaker.getY());
                window_.draw(circle);
            }

            window_.display();
        }

        void App::handleSequenserZone()
        {
            
        }
    }
}
