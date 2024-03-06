#include "SpeakerMovementZone.hpp"

namespace ads
{
	namespace window
	{
		SpeakerMovementZone::SpeakerMovementZone()
			: zoom_(settings::NORMAL_ZOOM), line_(settings::NORMAL_LINE_POS)
		{
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
	}
}