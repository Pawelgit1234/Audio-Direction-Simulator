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

		private:
			sf::RectangleShape marker_;
			sf::RectangleShape panel_;
			sf::RenderWindow& window_;

			float scale_;
			float marker_pos_;
			float timeline_pos_width_x_;
			float timeline_pos_width_y_;

			friend App;
		};
	}
}

