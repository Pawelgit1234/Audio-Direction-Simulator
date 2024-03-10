#pragma once

#include <SFML/Graphics.hpp>

#include <vector>
#include <stdexcept>
#include <cmath>

#include "../settings.hpp"
#include "../objects/DynamicSpeaker.hpp"
#include "../utils/Logger.hpp"

namespace ads
{
	namespace window
	{
		class App;

		class SpeakerMovementZone
		{
		public:
			SpeakerMovementZone(sf::RenderWindow& window);

			void addDynamicSpeaker(unsigned short id);
			ads::object::DynamicSpeaker getDynamicSpeaker(unsigned short id);
			void controll();

		private:
			sf::RenderWindow& window_;
			sf::View view_;
			std::vector<ads::object::DynamicSpeaker> dynamic_speakers_;

			friend App;
		};
	}
}