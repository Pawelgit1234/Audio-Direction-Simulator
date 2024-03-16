#include "Common.hpp"



#include <iostream>



namespace ads
{
	namespace utils
	{
		bool isInsideCircle(const sf::Vector2f& point, const sf::CircleShape& circle)
		{
            float circleCenterX = circle.getPosition().x;
            float circleCenterY = circle.getPosition().y;
            float pointX = point.x;
            float pointY = point.y;
            float radius = circle.getRadius();

            float distanceSquared = std::pow((pointX - radius - circleCenterX), 2) + std::pow((pointY - radius - circleCenterY), 2);
            float radiusSquared = std::pow(radius, 2);

            bool inside = distanceSquared <= radiusSquared;

            return inside;
		}

        bool isInsideRectangle(const sf::Vector2f& point, const sf::RectangleShape& rect)
        {
            sf::FloatRect frect = rect.getGlobalBounds();
            return frect.contains(point);
        }
	}
}