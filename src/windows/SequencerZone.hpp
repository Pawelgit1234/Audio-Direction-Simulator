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
			SequencerZone();

		private:
			sf::RenderWindow window_;

			friend App;
		};
	}
}

