#pragma once

#include <SFML/Graphics.hpp>

#include <vector>

#include "../utils/TimelineTimer.hpp"

namespace ads
{
	namespace object
	{
		struct TimelineBarSlice
		{
			utils::TimelineTimer start_;
			utils::TimelineTimer end_;
			unsigned short id_;
			sf::RectangleShape rect_;

			float calculateWidth();

			TimelineBarSlice(const utils::TimelineTimer& start, const utils::TimelineTimer& end, unsigned short id);
		};

		class TimelineBar
		{
		public:
			TimelineBar(const utils::TimelineTimer& start, const utils::TimelineTimer& end, unsigned short object_id, unsigned short line, bool is_wall, sf::Font& font);

			void cut(utils::TimelineTimer& pos);

			unsigned short getLine() const { return line_; }
			const std::vector<TimelineBarSlice>& getSlices() const { return slices_; }

		private:
			unsigned short object_id_;
			unsigned short line_;
			utils::TimelineTimer start_;
			utils::TimelineTimer end_;
			mutable std::vector<TimelineBarSlice> slices_;
			sf::Text time_text_;
			sf::Font& font_;

			bool is_wall_;
		};
	}
}


