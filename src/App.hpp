#pragma once

#include <SFML/Graphics.hpp>

#include "settings.hpp"
#include "utils/Logger.hpp"

namespace ads
{
	class App
	{
	public:
		App();

		void run();

	private:
		sf::RenderWindow window_;
	};
}

