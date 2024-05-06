#pragma once

#include <SFML/Audio.hpp>

#include <unordered_map>
#include <string>

#include "../utils/TimelineTimer.hpp"

namespace ads
{
	namespace sound
	{
		struct Sound
		{
			sf::SoundBuffer soundBuffer;
			sf::Sound sound;
		};

		class SoundManager
		{
		public:
			SoundManager() = default;

			bool loadSound(unsigned short object_id, const std::string& file_path);
			void playSound(unsigned short object_id, unsigned short sound_level, float ray_count_per, utils::TimelineTimer start);
			void stopSound(unsigned short object_id);
			void stopAllSounds();
			void setVolume(unsigned short object_id, unsigned short sound_level, float ray_count_per);

			utils::TimelineTimer getSoundLenght(unsigned short object_id) const;
			bool isSoundPlaying(unsigned short object_id) const;

		private:
			std::unordered_map<unsigned short, Sound> sounds_;
		};
	}
}

