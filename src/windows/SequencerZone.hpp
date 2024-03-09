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

			void run();

		private:
			std::shared_ptr<sf::RenderWindow> window_;

			friend App;
		};
	}
}

