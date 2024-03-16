#include "Wall.hpp"


#include "../settings.hpp"

namespace ads
{
	namespace object
	{
		Wall::Wall(unsigned short id)
			: rotation_angle_(0), id_(id), rect_(sf::Vector2f(settings::WALL_WIDTH, settings::WALL_HEIGHT))

		{
			rect_.setFillColor(settings::WALL_COLOR);
			rect_.setPosition(0.f, 0.f);
		}
	}
}
