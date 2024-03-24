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
	}
}