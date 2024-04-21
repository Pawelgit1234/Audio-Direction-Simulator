#pragma once

#include <SFML/Graphics.hpp>

#include <vector>

#include "../settings.hpp"
#include "../utils/TimelineTimer.hpp"
#include "../utils/Logger.hpp"
#include "../objects/TimelineBar.hpp"
#include "../objects/DynamicSpeaker.hpp"
#include "../objects/Wall.hpp"

namespace ads
{
	namespace window
	{
		class App;

		class TimelineZone
		{
		public:
			TimelineZone(sf::RenderWindow& window);

			void addSpeakerBar(const utils::TimelineTimer& start, const utils::TimelineTimer& end, unsigned short object_id);
			void addWallBar(const utils::TimelineTimer& start, const utils::TimelineTimer& end, unsigned short object_id);

			void updatePositionAtWindow(float zoom);
			void updateTimeText();
			void updateMarkerPosition();
			std::vector<unsigned short> checkActive();

			void moveSlice(float x, unsigned short id);
			void cut(float pos, unsigned short id);

		private:
			sf::RectangleShape marker_;
			sf::RectangleShape panel_;
			sf::RectangleShape time_panel_;
			sf::Text time_text_;
			sf::RenderWindow& window_;

			sf::Font font;
			std::vector<object::TimelineBar> bars_;

			float marker_pos_;
			unsigned short latest_slice_id;
			float timeline_pos_x_;
			float timeline_pos_y_;
			utils::TimelineTimer time_;
			bool is_running_;

			friend App;
		};
	}
}

