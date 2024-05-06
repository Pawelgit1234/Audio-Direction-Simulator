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

			TimelineBarSlice slice(start, end, start, end, first_slice_id, is_wall);
			slices_.emplace_back(slice);
		}

		float TimelineBarSlice::calculateWidth()
		{
			float startSeconds = start_.convertPositionFromTime();
			float endSeconds = end_.convertPositionFromTime();

			float durationSeconds = endSeconds - startSeconds;

			return durationSeconds * settings::BAR_SCALE_FACTOR;
		}

		TimelineBarSlice::TimelineBarSlice(const utils::TimelineTimer& start, const utils::TimelineTimer& end, const utils::TimelineTimer& sound_start, const utils::TimelineTimer& sound_end, unsigned short id, bool is_wall)
			: start_(start), end_(end), id_(id), sound_start_(sound_start), sound_end_(sound_end)
		{
			rect_.setSize(sf::Vector2f(calculateWidth(), settings::TIMELINE_BAR_HEIGHT));
			rect_.setPosition(0.f, settings::TIMELINE_BAR_HEIGHT);
			rect_.setOutlineThickness(settings::TIMELINE_BAR_OUTLINE_THICKNESS);
			rect_.setOutlineColor(settings::TIMELINE_BAR_OUTLINE_COLOR);

			if (is_wall)
				rect_.setFillColor(settings::TIMELINE_WALL_BAR_COLOR);
			else
				rect_.setFillColor(settings::TIMELINE_SPEAKER_BAR_COLOR);
		}
	}
}