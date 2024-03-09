#include "App.hpp"

namespace ads
{
    namespace window
    {
        void App::run()
        {
            ads::logger::log("Program started.", ads::logger::LoggerType::INFO);

            while (speaker_zone_.window_->isOpen() || sequenser_zone_.window_->isOpen())
            {
                /*Speaker Movement Zone*/
                speaker_zone_.window_->clear();
                speaker_zone_.controll();

                for (const auto& speaker : speaker_zone_.dynamic_speakers_)
                {
                    sf::CircleShape circle(settings::OBJECT_SIZE / (speaker_zone_.zoom_ / 100.f));
                    circle.setFillColor(sf::Color::Red);
                    circle.setPosition(speaker.getX(), speaker.getY());
                    speaker_zone_.window_->draw(circle);
                }

                speaker_zone_.window_->display();

                /*Sequenser Zone*/
                sequenser_zone_.window_->clear();
                sequenser_zone_.window_->display();
            }
        }
    }
}
