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
            speaker_zone_.addWall(1);  // delete

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
                window_.draw(speaker.getCircle());

            for (const auto& wall : speaker_zone_.walls_)
                window_.draw(wall.getRectangle());

            window_.draw(speaker_zone_.ear_.getCircle());

            window_.display();
        }

        void App::handleSequenserZone()
        {
            
        }
    }
}
