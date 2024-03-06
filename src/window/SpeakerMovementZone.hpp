#pragma once

#include <vector>
#include <stdexcept>

#include "../settings.hpp"
#include "../objects/DynamicSpeaker.hpp"
#include "../utils/Logger.hpp"

namespace ads
{
	namespace window
	{
		class SpeakerMovementZone
		{
		public:
			SpeakerMovementZone();

			void addDynamicSpeaker(unsigned short id);

			std::vector<ads::object::DynamicSpeaker> getDynamicSpeakers() { return dynamic_speakers_; }
			ads::object::DynamicSpeaker getDynamicSpeaker(unsigned short id);

			void setZoom(float zoom) { zoom_ = zoom; }
			void setLine(unsigned short line) { line_ = line; }

			float getZoom() const { return zoom_; }
			unsigned short getLine() const { return line_; }

		private:
			float zoom_;
			unsigned short line_;

			std::vector<ads::object::DynamicSpeaker> dynamic_speakers_;
		};
	}
}