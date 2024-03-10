#pragma once

#include <SFML/Graphics.hpp>

#include "../settings.hpp"

namespace ads
{
	namespace utils
	{
		void resizeView(const sf::RenderWindow& window, sf::View& view);
	}
}