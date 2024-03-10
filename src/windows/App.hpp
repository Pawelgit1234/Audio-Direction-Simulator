#pragma once

#include <SFML/Graphics.hpp>

#include "../utils/Logger.hpp"
#include "SpeakerMovementZone.hpp"
#include "SequencerZone.hpp"

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
			void handleSequenserZone();

			sf::RenderWindow window_;
			SpeakerMovementZone speaker_zone_;
			SequencerZone sequenser_zone_;
		};
	}
}

