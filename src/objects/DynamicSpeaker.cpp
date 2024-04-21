#include "DynamicSpeaker.hpp"

namespace ads
{
	namespace object
	{
		DynamicSpeaker::DynamicSpeaker(unsigned short id)
			: sound_level_(settings::NORMAL_SOUND_LEVEL),
			rotation_angle_(0), sound_angle_(settings::NORMAL_SOUND_ANGLE), id_(id), circle_(settings::DYNAMIC_SPEAKER_SIZE), is_active_(false)
		
		{
			circle_.setFillColor(settings::DYNAMIC_SPEAKER_COLOR);
			circle_.setPosition(0.f, 0.f);
			updateRays();
		}

		void DynamicSpeaker::updateRays()
		{
			rayDirections_.clear();
			float rotation_rad = static_cast<float>(rotation_angle_ * M_PI / 180.0);
			float sound_angle_rad = static_cast<float>(sound_angle_ * M_PI / 180.0);
			float angle_interval = sound_angle_rad / (settings::RAY_COUNT - 1);

			for (int i = 0; i < settings::RAY_COUNT; ++i)
			{
				float current_angle = rotation_rad - (sound_angle_rad / 2.0) + (i * angle_interval);
				sf::Vector2f direction(std::cos(current_angle), std::sin(current_angle));
				rayDirections_.push_back(direction);
			}
		}
	}
}