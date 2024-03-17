#pragma once

#define _USE_MATH_DEFINES
#include <cmath>

#include "../settings.hpp"

namespace ads
{
	namespace object
	{
		class DynamicSpeaker
		{
		public:
			DynamicSpeaker(unsigned short id);

			void move(float offsetX, float offsetY) { circle_.setPosition(circle_.getPosition().x + offsetX, circle_.getPosition().y + offsetY); }
			void setX(float x) { circle_.setPosition(x, circle_.getPosition().y); }
			void setY(float y) { circle_.setPosition(circle_.getPosition().x, y); }
			void setSoundlevel(unsigned short soundlevel) { sound_level_ = soundlevel; }
			void setRotationAngle(unsigned short angle) { rotation_angle_ = angle; }
			void setSoundAngle(unsigned short angle) { sound_angle_ = angle; }
			void updateRays();

			float getX() const { return circle_.getPosition().x; }
			float getY() const { return circle_.getPosition().y; }
			unsigned short getSoundlevel() const { return sound_level_; }
			unsigned short getRotationAngle() const { return rotation_angle_; }
			unsigned short getSoundAngle() const { return sound_angle_; }
			unsigned short getId() const { return id_; }
			sf::CircleShape getCircle() const { return circle_; }
			const std::vector<sf::Vector2f>& getRayDirections() const { return rayDirections_; }

		private:
			unsigned short sound_level_; // 1 - 100
			unsigned short rotation_angle_; // 1 - 360
			unsigned short sound_angle_; // 1 - 360
			unsigned short id_;
			char title[25];
			sf::CircleShape circle_;
			std::vector<sf::Vector2f> rayDirections_;
		};
	}
}
