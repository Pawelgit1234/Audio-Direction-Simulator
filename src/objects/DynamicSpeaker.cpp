#include "DynamicSpeaker.hpp"

namespace ads
{
	namespace object
	{
		DynamicSpeaker::DynamicSpeaker(unsigned short id)
			: x_(0.f), y_(0.f), sound_level_(settings::NORMAL_SOUND_LEVEL),
			rotation_angle_(0), sound_angle_(0), id_(id) {}
	}
}