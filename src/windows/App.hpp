#pragma once

#include <SFML/Graphics.hpp>

#include "../utils/Logger.hpp"
#include "SpeakerMovementZone.hpp"
#include "TimelineZone.hpp"

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

			sf::RenderWindow window_;
			SpeakerMovementZone speaker_zone_;
			TimelineZone timeline_zone_;
		};
	}
}

