#include "DynamicSpeaker.hpp"

namespace ads
{
	namespace object
	{
		DynamicSpeaker::DynamicSpeaker(unsigned short id)
			: sound_level_(settings::NORMAL_SOUND_LEVEL),
			rotation_angle_(0), sound_angle_(0), id_(id), circle_(settings::DYNAMIC_SPEAKER_SIZE)
		
		{
			circle_.setFillColor(settings::DYNAMIC_SPEAKER_COLOR);
			circle_.setPosition(0.f, 0.f);
		}
	}
}