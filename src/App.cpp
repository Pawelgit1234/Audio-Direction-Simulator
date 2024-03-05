#include "App.hpp"

namespace ads
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
	}

	void App::run()
	{
        ads::logger::log("Program started.", ads::logger::LoggerType::INFO);
        while(window_.isOpen())
        {
            sf::Event event;
            while (window_.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window_.close();
            }

            window_.display();
        }
	}
}
