#pragma once

#include "../settings.hpp"

namespace ads
{
	namespace object
	{
		class Ear
		{
		public:
			Ear();

			void move(float offsetX, float offsetY) { circle_.setPosition(circle_.getPosition().x + offsetX, circle_.getPosition().y + offsetY); }
			void setX(float x) { circle_.setPosition(x, circle_.getPosition().y); }
			void setY(float y) { circle_.setPosition(circle_.getPosition().x, y); }

			float getX() const { return circle_.getPosition().x; }
			float getY() const { return circle_.getPosition().y; }
			sf::CircleShape getCircle() const { return circle_; }

		private:
			sf::CircleShape circle_;
		};
	}
}
