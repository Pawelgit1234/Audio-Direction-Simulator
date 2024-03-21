#pragma once

#include <SFML/Graphics.hpp>

#include "../settings.hpp"

namespace ads
{
	namespace window
	{
		class App;

		class SequencerZone
		{
		public:
			SequencerZone(sf::RenderWindow& window);

			void update(float zoom);

		private:
			sf::RectangleShape panel_;
			sf::RenderWindow& window_;

			friend App;
		};
	}
}

