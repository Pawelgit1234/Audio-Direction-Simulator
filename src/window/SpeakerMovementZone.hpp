#pragma once

#include "../settings.hpp"

namespace ads
{
	namespace window
	{
		class SpeakerMovementZone
		{
		public:
			SpeakerMovementZone();

		private:
			unsigned short zoom_;
			unsigned short line_;
		};
	}
}