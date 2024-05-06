#include "SoundManager.hpp"

namespace ads
{
	namespace sound
	{
		bool SoundManager::loadSound(unsigned short object_id, const std::string& file_path)
		{
			sf::SoundBuffer buffer;
			if (!buffer.loadFromFile(file_path))
				return false;

			sounds_[object_id] = Sound{ buffer, sf::Sound(buffer) };
			return true;
		}

		void SoundManager::playSound(unsigned short object_id, unsigned short sound_level, float ray_count_per, utils::TimelineTimer start)
		{
			auto it = sounds_.find(object_id);
			if (it != sounds_.end())
			{
				sf::Sound& sound = it->second.sound;
				sound.setVolume(sound_level * ray_count_per);
				sound.setBuffer(it->second.soundBuffer);
				float startTimeSeconds = start.getSecondsSum();
				sound.setPlayingOffset(sf::seconds(startTimeSeconds));
				sound.play();
			}
		}

		void SoundManager::stopSound(unsigned short object_id)
		{
			auto it = sounds_.find(object_id);
			if (it != sounds_.end())
			{
				sf::Sound& sound = it->second.sound;
				sound.setBuffer(it->second.soundBuffer);
				sound.stop();
			}
		}

		void SoundManager::stopAllSounds()
		{
			for (auto& pair : sounds_)
				pair.second.sound.stop();
		}

		void SoundManager::setVolume(unsigned short object_id, unsigned short sound_level, float ray_count_per)
		{
			auto it = sounds_.find(object_id);
			if (it != sounds_.end())
			{
				sf::Sound& sound = it->second.sound;
				sound.setVolume(sound_level * ray_count_per);
			}
		}

		utils::TimelineTimer SoundManager::getSoundLenght(unsigned short object_id) const
		{
			auto it = sounds_.find(object_id);
			if (it != sounds_.end())
			{
				sf::Time duration = it->second.soundBuffer.getDuration();
				float seconds = duration.asSeconds();

				int hours = static_cast<int>(seconds) / 3600;
				int remainingSeconds = static_cast<int>(seconds) % 3600;
				int minutes = remainingSeconds / 60;
				int secs = remainingSeconds % 60;

				return utils::TimelineTimer(hours, minutes, secs);
			}
			else
				return utils::TimelineTimer(0, 0, 0);
		}

		bool SoundManager::isSoundPlaying(unsigned short object_id) const
		{
			auto it = sounds_.find(object_id);

			if (it != sounds_.end() && it->second.sound.getStatus() == sf::Sound::Playing)
				return true;

			return false;
		}

	}
}