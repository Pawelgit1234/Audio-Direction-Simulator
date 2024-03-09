#pragma once

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
			App() = default;

			void run();

		private:
			SpeakerMovementZone speaker_zone_;
			SequencerZone sequenser_zone_;
		};
	}
}

