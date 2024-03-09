#include "SpeakerMovementZone.hpp"

namespace ads
{
	namespace window
	{
		SpeakerMovementZone::SpeakerMovementZone()
			: zoom_(settings::NORMAL_ZOOM),
			window_(std::make_shared<sf::RenderWindow>(sf::VideoMode(settings::SPEAKER_MOVEMENT_ZONE_WIDTH, settings::SPEAKER_MOVEMENT_ZONE_HEIGHT), settings::WINDOW_NAME))
		{
			sf::Image icon;
			if (!icon.loadFromFile(settings::ICON_PATH))
			{
				icon.create(32, 32, sf::Color(255, 255, 255));
				ads::logger::log("Failed to load icon.", ads::logger::LoggerType::WARNING);
			}

			window_->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

			addDynamicSpeaker(1);  // delete
			addDynamicSpeaker(2);  // delete
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

			ads::logger::log("Dynamic speaker with the given id not found.", ads::logger::LoggerType::WARNING);
			throw std::runtime_error("Dynamic speaker with the given id not found.");
		}

		void SpeakerMovementZone::controll()
		{
			sf::Event event;
			while (window_->pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window_->close();
				else if (event.type == sf::Event::MouseWheelScrolled)
				{
					if (event.mouseWheelScroll.delta > 0 && zoom_ < 120.f)
						zoom_ += 10;
					else if (event.mouseWheelScroll.delta < 0 && zoom_ > 10.f)
						zoom_ -= 10;
				}
				/*else if ()
				{

				}*/
			}
		}

		void SpeakerMovementZone::run()
		{
			while (window_->isOpen())
			{
				window_->clear();
				controll();

				for (const auto& speaker : dynamic_speakers_)
				{
					sf::CircleShape circle(settings::OBJECT_SIZE / (zoom_ / 100.f));
					circle.setFillColor(sf::Color::Red);
					circle.setPosition(speaker.getX(), speaker.getY());
					window_->draw(circle);
				}

				window_->display();
			}
		}
	}
}