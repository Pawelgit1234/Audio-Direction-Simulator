#pragma once

#include "../settings.hpp"

namespace ads
{
	namespace object
	{
		class Wall
		{
		public:
			Wall(unsigned short id);

			void move(float offsetX, float offsetY) { rect_.setPosition(rect_.getPosition().x + offsetX, rect_.getPosition().y + offsetY); }
			void setX(float x) { rect_.setPosition(x, rect_.getPosition().y); }
			void setY(float y) { rect_.setPosition(rect_.getPosition().x, y); }
			void setRotationAngle(unsigned short angle) { rotation_angle_ = angle; }

			float getX() const { return rect_.getPosition().x; }
			float getY() const { return rect_.getPosition().y; }
			unsigned short getRotationAngle() const { return rotation_angle_; }
			unsigned short getId() const { return id_; }
			sf::RectangleShape getRectangle() const { return rect_; }

		private:
			sf::RectangleShape rect_;
			unsigned short rotation_angle_; // 1 - 360
			unsigned short id_;
			char title[25];
		};
	}
}

