#pragma once

#include <SFML/Graphics.hpp>

#include "../settings.hpp"

namespace ads
{
	namespace utils
	{
		bool isInsideCircle(const sf::Vector2f& point, const sf::CircleShape& circle);
	}
}