#include "App.hpp"

namespace ads
{
    namespace window
    {
        void App::run()
        {
            ads::utils::log("Program started.", ads::utils::LoggerType::INFO);

            while (speaker_zone_.window_.isOpen() || sequenser_zone_.window_.isOpen())
            {
                handleSpeakerMovementZone();
                handleSequenserZone();
            }
        }

        void App::handleSpeakerMovementZone()
        {
            speaker_zone_.window_.clear();
            speaker_zone_.controll();

            for (const auto& speaker : speaker_zone_.dynamic_speakers_)
            {
                sf::CircleShape circle(settings::OBJECT_SIZE);
                circle.setFillColor(sf::Color::Red);
                circle.setOrigin(circle.getRadius(), circle.getRadius());
                circle.setPosition(speaker.getX(), speaker.getY());
                speaker_zone_.window_.draw(circle);
            }

            speaker_zone_.window_.display();
        }

        void App::handleSequenserZone()
        {
            sequenser_zone_.window_.clear();
            sequenser_zone_.window_.display();
        }
    }
}
