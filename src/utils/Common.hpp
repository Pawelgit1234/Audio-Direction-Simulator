#pragma once

#include <SFML/Graphics.hpp>

#include "../settings.hpp"

namespace ads
{
	namespace utils
	{
		bool isInsideCircle(const sf::Vector2f& point, const sf::CircleShape& circle);
		bool isInsideRectangle(const sf::Vector2f& point, const sf::RectangleShape& rect);
		bool rayIntersectsWall(const sf::Vector2f& rayOrigin, const sf::Vector2f& rayDirection, const sf::RectangleShape& wall);
		bool rayIntersectsEar(const sf::Vector2f& rayOrigin, const sf::Vector2f& rayDirection, const sf::CircleShape& ear);
	}
}