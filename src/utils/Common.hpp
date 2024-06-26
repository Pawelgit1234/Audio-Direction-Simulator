#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>

#include "../settings.hpp"

namespace ads
{
	namespace utils
	{
		bool isInsideCircle(const sf::Vector2f& point, const sf::CircleShape& circle);
		bool isInsideRectangle(const sf::Vector2f& point, const sf::RectangleShape& rect);
		sf::Vector2f rayIntersectsWall(const sf::Vector2f& rayOrigin, const sf::Vector2f& rayDirection, const sf::RectangleShape& wall);
		sf::Vector2f rayIntersectsCircle(const sf::Vector2f& rayOrigin, const sf::Vector2f& rayDirection, const sf::CircleShape& circle);
		float distance(const sf::Vector2f& p1, const sf::Vector2f& p2);
		bool endsWith(const std::string& fullString, const std::string& ending);
	}
}