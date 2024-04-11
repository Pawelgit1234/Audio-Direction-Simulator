#include "TimelineBar.hpp"

namespace ads
{
	namespace object
	{
		

		TimelineBar::TimelineBar(const utils::TimelineTimer& start, const utils::TimelineTimer& end, unsigned short object_id, unsigned short line, unsigned short first_slice_id, bool is_wall, sf::Font& font)
			: start_(start), end_(end), object_id_(object_id), is_wall_(is_wall), font_(font), line_(line)
		{
			time_text_.setFont(font);
			time_text_.setCharacterSize(settings::FONT_SIZE);
			time_text_.setFillColor(settings::FONT_COLOR);

			TimelineBarSlice slice(start, end, first_slice_id);
			slices_.emplace_back(slice);

			if (is_wall)
				slices_[0].rect_.setFillColor(settings::TIMELINE_WALL_BAR_COLOR);
			else	   
				slices_[0].rect_.setFillColor(settings::TIMELINE_SPEAKER_BAR_COLOR);
		}

		float TimelineBarSlice::calculateWidth()
		{
			float startSeconds = start_.convertPositionFromTime();
			float endSeconds = end_.convertPositionFromTime();

			float durationSeconds = endSeconds - startSeconds;

			return durationSeconds * settings::BAR_SCALE_FACTOR;
		}

		TimelineBarSlice::TimelineBarSlice(const utils::TimelineTimer& start, const utils::TimelineTimer& end, unsigned short id)
			: start_(start), end_(end), id_(id)
		{
			rect_.setSize(sf::Vector2f(calculateWidth(), settings::TIMELINE_BAR_HEIGHT));
			rect_.setPosition(0.f, settings::TIMELINE_BAR_HEIGHT);
			rect_.setOutlineThickness(settings::TIMELINE_BAR_OUTLINE_THICKNESS);
			rect_.setOutlineColor(settings::TIMELINE_BAR_OUTLINE_COLOR);
		}
	}
}