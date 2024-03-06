#pragma once

#include <SFML/Graphics.hpp>

#include "../settings.hpp"
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
			sf::RenderWindow window_;
			SpeakerMovementZone speaker_zone_;
			SequencerZone sequenser_zone_;
		};
	}
}

