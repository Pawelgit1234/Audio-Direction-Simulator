#include "SpeakerMovementZone.hpp"

namespace ads
{
	namespace window
	{
		SpeakerMovementZone::SpeakerMovementZone(sf::RenderWindow& window)
			: window_(window)
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

		ads::object::DynamicSpeaker SpeakerMovementZone::getDynamicSpeaker(unsigned short id)
		{
			for (const auto& s : dynamic_speakers_)
				if (s.getId() == id)
					return s;

			ads::utils::log("Dynamic speaker with the given id not found.", ads::utils::LoggerType::WARNING);
			throw std::runtime_error("Dynamic speaker with the given id not found.");
		}

		void SpeakerMovementZone::controll()
		{
			bool isDragging = false;
			sf::Vector2f lastMousePosition;
			
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
						view_.zoom(1.1f);
					else if (event.mouseWheelScroll.delta < 0)
						view_.zoom(0.9f);

					window_.setView(view_);
					break;
				case sf::Event::MouseButtonPressed:
					if (event.mouseButton.button == sf::Mouse::Left)
					{
						isDragging = true;
						lastMousePosition = window_.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
					}
					break;
				case sf::Event::MouseMoved:
					if (isDragging)
					{
						sf::Vector2f newMousePosition = window_.mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
						sf::Vector2f delta = (lastMousePosition - newMousePosition);
						view_.move(delta);
						lastMousePosition = newMousePosition;
						window_.setView(view_);
					}
					break;
				case sf::Event::MouseButtonReleased:
					if (event.mouseButton.button == sf::Mouse::Left)
						isDragging = false;

					break;
				}
			}
		}
	}
}