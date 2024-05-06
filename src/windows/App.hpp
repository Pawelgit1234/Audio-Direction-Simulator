#pragma once

#include <SFML/Graphics.hpp>

#include <filesystem>

#include "../utils/Logger.hpp"
#include "SpeakerMovementZone.hpp"
#include "TimelineZone.hpp"
#include "../sounds/SoundManager.hpp"

namespace ads
{
	namespace window
	{
		class App
		{
		public:
			App();

			void run();

		private:
			void handleSpeakerMovementZone();
			void handleTimeLineZone();
			void controll();
			void addSpeakers();

			sf::RenderWindow window_;
			SpeakerMovementZone speaker_zone_;
			TimelineZone timeline_zone_;
			sound::SoundManager sound_manager_;
		};
	}
}

