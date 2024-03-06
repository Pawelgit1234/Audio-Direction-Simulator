#include "DynamicSpeaker.hpp"

namespace ads
{
	namespace sound
	{
		DynamicSpeaker::DynamicSpeaker()
			: x_(0), y_(0), sound_level_(settings::NORMAL_SOUND_LEVEL),
			rotation_angle_(0), sound_angle_(0) {}
	}
}