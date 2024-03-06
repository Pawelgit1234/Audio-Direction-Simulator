#pragma once

#include "../settings.hpp"

namespace ads
{
	namespace object
	{
		class DynamicSpeaker
		{
		public:
			DynamicSpeaker(unsigned short id);

			void setX(short x) { x_ = x; }
			void setY(short y) { y_ = y; }
			void setSoundlevel(unsigned short soundlevel) { sound_level_ = soundlevel; }
			void setRotationAngle(unsigned short angle) { rotation_angle_ = angle; }
			void setSoundAngle(unsigned short angle) { sound_angle_ = angle; }

			short getX() const { return x_; }
			short getY() const { return y_; }
			unsigned short getSoundlevel() const { return sound_level_; }
			unsigned short getRotationAngle() const { return rotation_angle_; }
			unsigned short getSoundAngle() const { return sound_angle_; }
			unsigned short getId() const { return id_; }

		private:
			short x_;
			short y_;
			unsigned short sound_level_; // 1 - 100
			unsigned short rotation_angle_; // 1 - 360
			unsigned short sound_angle_; // 1 - 360
			unsigned short id_;
			char title[25];
		};
	}
}



