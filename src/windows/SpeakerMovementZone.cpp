#include "SpeakerMovementZone.hpp"

namespace ads
{
	namespace window
	{
		SpeakerMovementZone::SpeakerMovementZone(sf::RenderWindow& window)
			: window_(window), zoom_(1.f)
		{
			view_.setSize(sf::Vector2f(settings::WINDOW_WIDTH, settings::WINDOW_HEIGHT));
			view_.setCenter(sf::Vector2f(settings::WINDOW_WIDTH / 2.f, settings::WINDOW_HEIGHT / 2.f));
			window_.setView(view_);
		}

		void SpeakerMovementZone::addDynamicSpeaker(unsigned short id)
		{
			object::DynamicSpeaker dynamic_speaker(id);
			dynamic_speakers_.push_back(dynamic_speaker);
		}

        void SpeakerMovementZone::addWall(unsigned short id)
        {
            object::Wall wall(id);
            walls_.push_back(wall);
        }

		ads::object::DynamicSpeaker SpeakerMovementZone::getDynamicSpeaker(unsigned short id)
		{
			for (const auto& s : dynamic_speakers_)
				if (s.getId() == id)
					return s;

			ads::utils::log("Dynamic speaker with the given id not found.", ads::utils::LoggerType::WARNING);
			throw std::runtime_error("Dynamic speaker with the given id not found.");
		}

        ads::object::Wall SpeakerMovementZone::getWall(unsigned short id)
        {
            for (const auto& w : walls_)
                if (w.getId() == id)
                    return w;

            ads::utils::log("Wall with the given id not found.", ads::utils::LoggerType::WARNING);
            throw std::runtime_error("Wall with the given id not found.");
        }

        void SpeakerMovementZone::controll()
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
                    view_.setSize(sf::Vector2f(event.size.width, event.size.height));
                    window_.setView(view_);
                    break;
                case sf::Event::MouseWheelScrolled:
                    if (event.mouseWheelScroll.delta > 0)
                    {
                        view_.zoom(1.1f);
                        zoom_ *= 1.1f;
                    }
                    else if (event.mouseWheelScroll.delta < 0)
                    {
                        view_.zoom(0.9f);
                        zoom_ *= 0.9f;
                    }

                    window_.setView(view_);
                    break;
                case sf::Event::MouseButtonPressed:
                    sf::Vector2f mousePos = window_.mapPixelToCoords(sf::Mouse::getPosition(window_), view_);

                    if (utils::isInsideCircle(sf::Vector2f(mousePos), ear_.getCircle()))
                    {
                        for (auto& speaker : dynamic_speakers_)
                            speaker.updateRays();

                        while (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                        {
                            sf::Vector2i mousePos = sf::Mouse::getPosition(window_);
                            sf::Vector2i delta = mousePos - lastMousePos;

                            ear_.move(static_cast<float>(delta.x), static_cast<float>(delta.y));
                            window_.setView(view_);

                            lastMousePos = mousePos;
                        }

                        break;
                    }

                    for (auto& speaker : dynamic_speakers_)
                    {
                        speaker.updateRays();
                        if (utils::isInsideCircle(sf::Vector2f(mousePos), speaker.getCircle()))
                        {
                            while (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                            {
                                sf::Vector2i mousePos = sf::Mouse::getPosition(window_);
                                sf::Vector2i delta = mousePos - lastMousePos;

                                speaker.move(static_cast<float>(delta.x), static_cast<float>(delta.y));
                                window_.setView(view_);

                                lastMousePos = mousePos;
                            }
                            
                            break;
                        }
                    }

                    for (auto& wall : walls_)
                    {
                        for (auto& speaker : dynamic_speakers_)
                            speaker.updateRays();

                        if (utils::isInsideRectangle(sf::Vector2f(mousePos), wall.getRectangle()))
                        {
                            while (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                            {
                                sf::Vector2i mousePos = sf::Mouse::getPosition(window_);
                                sf::Vector2i delta = mousePos - lastMousePos;

                                wall.move(static_cast<float>(delta.x), static_cast<float>(delta.y));
                                window_.setView(view_);

                                lastMousePos = mousePos;
                            }

                            break;
                        }
                    }

                    while (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                    {
                        sf::Vector2i mousePos = sf::Mouse::getPosition(window_);
                        sf::Vector2i delta = mousePos - lastMousePos;

                        view_.move(-static_cast<float>(delta.x), -static_cast<float>(delta.y));
                        window_.setView(view_);

                        lastMousePos = mousePos;
                    }
                    break;
                }
            }
        }
	}
}