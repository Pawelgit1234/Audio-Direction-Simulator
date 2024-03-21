#include "Common.hpp"

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

        sf::Vector2f rayIntersectsWall(const sf::Vector2f& rayOrigin, const sf::Vector2f& rayDirection, const sf::RectangleShape& wall)
        {
            sf::FloatRect wallBounds = wall.getGlobalBounds();
            float wallLeft = wallBounds.left;
            float wallTop = wallBounds.top;
            float wallRight = wallLeft + wallBounds.width;
            float wallBottom = wallTop + wallBounds.height;

            float rayX = rayOrigin.x;
            float rayY = rayOrigin.y;
            float rayDirX = rayDirection.x;
            float rayDirY = rayDirection.y;

            float tEnterX = (wallLeft - rayX) / rayDirX;
            float tEnterY = (wallTop - rayY) / rayDirY;
            float tExitX = (wallRight - rayX) / rayDirX;
            float tExitY = (wallBottom - rayY) / rayDirY;

            float tEnter = std::max(std::min(tEnterX, tExitX), std::min(tEnterY, tExitY));
            float tExit = std::min(std::max(tEnterX, tExitX), std::max(tEnterY, tExitY));

            if (tEnter < tExit && tExit >= 0)
                return sf::Vector2f(rayX + rayDirX * tEnter, rayY + rayDirY * tEnter);

            return sf::Vector2f(0.f, 0.f);
        }

        sf::Vector2f rayIntersectsCircle(const sf::Vector2f& rayOrigin, const sf::Vector2f& rayDirection, const sf::CircleShape& circle)
        {
            sf::Vector2f circleCenter = circle.getPosition();
            float circleRadius = circle.getRadius();
            circleCenter.x += circleRadius;
            circleCenter.y += circleRadius;
            

            float rayX = rayOrigin.x;
            float rayY = rayOrigin.y;
            float rayDirX = rayDirection.x;
            float rayDirY = rayDirection.y;

            float circleX = circleCenter.x;
            float circleY = circleCenter.y;

            float deltaX = rayX - circleX;
            float deltaY = rayY - circleY;

            float a = rayDirX * rayDirX + rayDirY * rayDirY;
            float b = 2.f * (deltaX * rayDirX + deltaY * rayDirY);
            float c = deltaX * deltaX + deltaY * deltaY - circleRadius * circleRadius;

            float discriminant = b * b - 4.f * a * c;

            if (discriminant >= 0) {
                float t = (-b - std::sqrt(discriminant)) / (2.f * a);
                if (t >= 0) {
                    return sf::Vector2f(rayX + rayDirX * t, rayY + rayDirY * t);
                }
            }

            return sf::Vector2f(0.f, 0.f);
        }

        float distance(const sf::Vector2f& p1, const sf::Vector2f& p2)
        {
            float dx = p2.x - p1.x;
            float dy = p2.y - p1.y;
            return std::sqrt(dx * dx + dy * dy);
        }
	}
}