#include "SpeakerMovementZone.hpp"

namespace ads
{
	namespace window
	{
		SpeakerMovementZone::SpeakerMovementZone()
			: zoom_(1.f),
			window_(sf::VideoMode(settings::SPEAKER_MOVEMENT_ZONE_WIDTH, settings::SPEAKER_MOVEMENT_ZONE_HEIGHT), settings::WINDOW_NAME),
			view_()
		{
			window_.setView(view_);

			sf::Image icon;
			if (!icon.loadFromFile(settings::ICON_PATH))
			{
				icon.create(32, 32, sf::Color(255, 255, 255));
				ads::utils::log("Failed to load icon.", ads::utils::LoggerType::WARNING);
			}

			window_.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

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

			ads::utils::log("Dynamic speaker with the given id not found.", ads::utils::LoggerType::WARNING);
			throw std::runtime_error("Dynamic speaker with the given id not found.");
		}

		void SpeakerMovementZone::controll()
		{
			
			sf::Event event;
			while (window_.pollEvent(event))
			{
				switch (event.type)
				{
				case sf::Event::Closed:
					window_.close();
					break;
				case sf::Event::Resized:
					utils::resizeView(window_, view_);
					break;
				}
			}
		}
	}
}