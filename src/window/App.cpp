#include "App.hpp"

namespace ads
{
    namespace window
    {
        App::App() : window_(sf::VideoMode(settings::WINDOW_WIDTH, settings::WINDOW_HEIGHT), settings::WINDOW_NAME)
        {
            sf::Image icon;
            if (!icon.loadFromFile(settings::IMG_PATH))
            {
                icon.create(32, 32, sf::Color(255, 255, 255));
                ads::logger::log("Failed to load icon.", ads::logger::LoggerType::WARNING);
            }

            window_.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

            speaker_zone_.addDynamicSpeaker(1);
        }

        void App::run()
        {
            ads::logger::log("Program started.", ads::logger::LoggerType::INFO);
            while (window_.isOpen())
            {
                sf::Event event;
                while (window_.pollEvent(event))
                {
                    if (event.type == sf::Event::Closed)
                        window_.close();
                }

                window_.clear();

                for (const auto& speaker : speaker_zone_.getDynamicSpeakers())
                {
                    sf::CircleShape circle(settings::OBJECT_SIZE / (speaker_zone_.getZoom() / 100.f));
                    circle.setFillColor(sf::Color::Red);
                    circle.setPosition(speaker.getX(), speaker.getY());
                    window_.draw(circle);
                }

                window_.display();
            }
        }
    }
}
