#pragma once

#include <SFML/Graphics.hpp>

#include <vector>
#include <algorithm>

#include "../utils/TimelineTimer.hpp"
#include "../settings.hpp"

namespace ads
{
	namespace object
	{
		struct TimelineBarSlice
		{
			utils::TimelineTimer start_;
			utils::TimelineTimer end_;
			utils::TimelineTimer sound_start_;
			utils::TimelineTimer sound_end_;
			unsigned short id_;
			sf::RectangleShape rect_;

			float calculateWidth();

			TimelineBarSlice(const utils::TimelineTimer& start, const utils::TimelineTimer& end, const utils::TimelineTimer& sound_start, const utils::TimelineTimer& sound_end, unsigned short id, bool is_wall);
		};

		class TimelineBar
		{
		public:
			TimelineBar(const utils::TimelineTimer& start, const utils::TimelineTimer& end, unsigned short object_id, unsigned short line, unsigned short first_slice_id, bool is_wall, sf::Font& font);

			void addSlice(const TimelineBarSlice& slice) { slices_.emplace_back(slice); }

			unsigned short getLine() const { return line_; }
			const std::vector<TimelineBarSlice>& getSlices() const { return slices_; }
			bool isWall() const { return is_wall_; }
			unsigned short getObjectId() const { return object_id_; }

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


