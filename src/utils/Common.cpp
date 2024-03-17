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

        bool rayIntersectsWall(const sf::Vector2f& rayOrigin, const sf::Vector2f& rayDirection, const sf::RectangleShape& wall)
        {
            sf::FloatRect wallBounds = wall.getGlobalBounds();

            if (rayOrigin.x < wallBounds.left || rayOrigin.x > wallBounds.left + wallBounds.width ||
                rayOrigin.y < wallBounds.top || rayOrigin.y > wallBounds.top + wallBounds.height)
                return false;

            float tmin = (wallBounds.left - rayOrigin.x) / rayDirection.x;
            float tmax = (wallBounds.left + wallBounds.width - rayOrigin.x) / rayDirection.x;

            if (tmin > tmax) std::swap(tmin, tmax);

            float tymin = (wallBounds.top - rayOrigin.y) / rayDirection.y;
            float tymax = (wallBounds.top + wallBounds.height - rayOrigin.y) / rayDirection.y;

            if (tymin > tymax) std::swap(tymin, tymax);

            if ((tmin > tymax) || (tymin > tmax))
                return false;

            return true;
        }

        bool rayIntersectsEar(const sf::Vector2f& rayOrigin, const sf::Vector2f& rayDirection, const sf::CircleShape& ear)
        {
            sf::Vector2f earCenter = ear.getPosition();
            float earRadius = ear.getRadius();

            sf::Vector2f rayToEar = earCenter - rayOrigin;

            float projectionLength = rayToEar.x * rayDirection.x + rayToEar.y * rayDirection.y;
            if (projectionLength < 0)
                return false;
     
            sf::Vector2f intersectionPoint = rayOrigin + projectionLength * rayDirection;

            float distanceToEarCenterSquared = std::pow(intersectionPoint.x - earCenter.x, 2) + std::pow(intersectionPoint.y - earCenter.y, 2);
            float earRadiusSquared = std::pow(earRadius, 2);

            return distanceToEarCenterSquared <= earRadiusSquared;
        }
	}
}