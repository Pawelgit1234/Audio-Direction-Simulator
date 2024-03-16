#pragma once

#include <SFML/Graphics.hpp>

#include <vector>
#include <stdexcept>
#include <cmath>

#include "../settings.hpp"
#include "../objects/DynamicSpeaker.hpp"
#include "../objects/Ear.hpp"
#include "../objects/Wall.hpp"
#include "../utils/Logger.hpp"
#include "../utils/Common.hpp"

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
			void addWall(unsigned short id);
			void controll();

			ads::object::DynamicSpeaker getDynamicSpeaker(unsigned short id);
			ads::object::Wall getWall(unsigned short id);

		private:
			sf::RenderWindow& window_;
			sf::View view_;
			std::vector<ads::object::DynamicSpeaker> dynamic_speakers_;
			std::vector<ads::object::Wall> walls_;
			ads::object::Ear ear_;

			friend App;
		};
	}
}