#pragma once

#include <SFML/Graphics.hpp>

#include "../settings.hpp"

namespace ads
{
	namespace window
	{
		class App;

		class TimelineZone
		{
		public:
			TimelineZone(sf::RenderWindow& window);

			void updatePositionAtWindow(float zoom);
			void moveMarker(float x) { marker_pos_ += x; }
			void moveTimelinePositionX(float x) { timeline_pos_x_ += x; }
			void moveTimelinePositionY(float y) { timeline_pos_y_ += y; }
			void moveTimelineScale(float scale) { scale_ += scale; }

		private:
			sf::RectangleShape marker_;
			sf::RectangleShape panel_;
			sf::RenderWindow& window_;

			float scale_;
			float marker_pos_;
			float timeline_pos_x_;
			float timeline_pos_y_;

			friend App;
		};
	}
}

