#include "TimeLineZone.hpp"

namespace ads
{
	namespace window
	{
		TimelineZone::TimelineZone(sf::RenderWindow& window)
			: panel_(sf::Vector2f(settings::WINDOW_WIDTH, settings::TIMELINE_ZONE_HEIGHT)), marker_(sf::Vector2f(settings::TIMELINE_MARKER_WIDTH, settings::TIMELINE_ZONE_HEIGHT)),
			window_(window), marker_pos_(0.f), timeline_pos_x_(0.f), timeline_pos_y_(0.f), is_running_(false),
			time_panel_(sf::Vector2f(settings::TIME_PANEL_WIDTH, settings::TIME_PANEL_HEIGHT)), latest_slice_id(1)
		{
			panel_.setFillColor(settings::TIMELINE_COLOR);
			marker_.setFillColor(settings::TIMELINE_MARKER_COLOR);
			time_panel_.setFillColor(settings::TIME_PANEL_COLOR);

			if (!font.loadFromFile(settings::FONT_PATH))
				ads::utils::log("Failed to load font.", ads::utils::LoggerType::WARNING);

			time_text_.setFont(font);
			time_text_.setCharacterSize(settings::FONT_SIZE);
			time_text_.setFillColor(settings::FONT_COLOR);
			updateTimeText();
		}

		void TimelineZone::addSpeakerBar(const utils::TimelineTimer& start, const utils::TimelineTimer& end, unsigned short object_id)
		{
			object::TimelineBar bar(start, end, object_id, bars_.size() + 1, latest_slice_id, false, font);
			bars_.push_back(bar);
			latest_slice_id++;
		}

		void TimelineZone::addWallBar(const utils::TimelineTimer& start, const utils::TimelineTimer& end, unsigned short object_id)
		{
			object::TimelineBar bar(start, end, object_id, bars_.size() + 1, latest_slice_id, true, font);
			bars_.push_back(bar);
			latest_slice_id++;
		}

		void TimelineZone::updatePositionAtWindow(float zoom)
		{
			sf::Vector2f newPos = window_.mapPixelToCoords(sf::Vector2i(0, settings::WINDOW_HEIGHT - settings::TIMELINE_ZONE_HEIGHT));

			panel_.setSize(sf::Vector2f(settings::WINDOW_WIDTH, settings::TIMELINE_ZONE_HEIGHT) * zoom);
			panel_.setPosition(newPos);

			float markerAbsolutePos = newPos.x + marker_pos_ * (settings::WINDOW_WIDTH * zoom - settings::TIMELINE_MARKER_WIDTH * zoom);
			marker_.setSize(sf::Vector2f(settings::TIMELINE_MARKER_WIDTH, settings::TIMELINE_ZONE_HEIGHT) * zoom);
			marker_.setPosition(markerAbsolutePos + timeline_pos_x_ * zoom, newPos.y);

			time_panel_.setSize(sf::Vector2f(settings::TIME_PANEL_WIDTH, settings::TIME_PANEL_HEIGHT) * zoom);
			time_panel_.setPosition(newPos);

			time_text_.setCharacterSize(settings::FONT_SIZE * zoom);
			time_text_.setPosition(newPos);

			for (object::TimelineBar& bar : bars_)
			{
				for (const object::TimelineBarSlice& slice : bar.getSlices())
				{
					float xPos = newPos.x + slice.start_.convertPositionFromTime() * settings::BAR_SCALE_FACTOR * zoom + timeline_pos_x_ * zoom;
					float yPos = newPos.y + (bar.getLine() - 1) * settings::TIMELINE_BAR_HEIGHT * zoom + settings::TIMELINE_BAR_OUTLINE_THICKNESS * zoom + timeline_pos_y_ * zoom;

					const_cast<sf::RectangleShape&>(slice.rect_).setOutlineThickness(settings::TIMELINE_BAR_OUTLINE_THICKNESS * zoom);
					const_cast<sf::RectangleShape&>(slice.rect_).setSize(sf::Vector2f(const_cast<object::TimelineBarSlice&>(slice).calculateWidth(), settings::TIMELINE_BAR_HEIGHT) * zoom);
					const_cast<sf::RectangleShape&>(slice.rect_).setPosition(xPos, yPos);

					if (slice.rect_.getPosition().y < panel_.getPosition().y)
					{
						float yOffset = panel_.getPosition().y - slice.rect_.getPosition().y;
						const_cast<sf::RectangleShape&>(slice.rect_).move(0.f, yOffset);

						float ySize = slice.rect_.getSize().y - yOffset;
						if (ySize < 0)
							ySize = 0;

						const_cast<sf::RectangleShape&>(slice.rect_).setSize(sf::Vector2f(slice.rect_.getSize().x, ySize));
						continue;
					}
				}
			}
		}

		void TimelineZone::updateTimeText()
		{
			time_.convertTimeFromPosition(marker_pos_);
			time_text_.setString(time_.toString());
		}

		void TimelineZone::updateMarkerPosition()
		{
			static sf::Clock clock;
			static float previousTime = 0.f;

			float currentTime = clock.getElapsedTime().asSeconds();
			if (currentTime - previousTime >= 1.f)
			{
				utils::TimelineTimer timer(0, 0, 1);
				marker_pos_ += timer.convertPositionFromTime();
				updateTimeText();
				previousTime = currentTime;
			}
		}

		std::vector<unsigned short> TimelineZone::checkActive()
		{
			std::vector<unsigned short> result;

			for (object::TimelineBar& bar : bars_)
			{
				bool in_slice = false;
				for (const object::TimelineBarSlice& slice : bar.getSlices())
				{
					if (slice.start_.convertPositionFromTime() < marker_pos_ && marker_pos_ < slice.end_.convertPositionFromTime())
					{
						in_slice = true;
						break;
					}
				}

				if (!in_slice)
					result.push_back(bar.getLine());
			}

			return result;
		}

		void TimelineZone::moveSlice(float x, unsigned short id)
		{
			for (object::TimelineBar& bar : bars_)
			{
				for (const object::TimelineBarSlice& slice : bar.getSlices())
				{
					if (slice.id_ == id)
					{
						utils::TimelineTimer timer;
						timer.convertTimeFromPosition(x);
						slice.start_.hours += timer.hours;
						slice.start_.minutes += timer.minutes;
						slice.start_.seconds += timer.seconds;
						slice.end_.hours += timer.hours;
						slice.end_.minutes += timer.minutes;
						slice.end_.seconds += timer.seconds;
						return;
					}
				}
			}
		}

		void TimelineZone::cut(float pos, unsigned short id)
		{
			utils::TimelineTimer cut_timer;
			cut_timer.convertTimeFromPosition((pos - timeline_pos_x_) / settings::TIMELINE_DRAGGING_EQUALIZER);

			for (object::TimelineBar& bar : bars_)
			{
				for (const object::TimelineBarSlice& slice : bar.getSlices())
				{
					if (slice.id_ == id)
					{
						latest_slice_id++;

						utils::TimelineTimer new_sound_start = slice.sound_end_ - (slice.end_ - cut_timer);
						object::TimelineBarSlice newSlice(cut_timer, slice.end_, new_sound_start, slice.sound_end_ , latest_slice_id, bar.isWall());


						const_cast<object::TimelineBarSlice&>(slice).end_ = cut_timer;
						const_cast<object::TimelineBarSlice&>(slice).sound_end_ = const_cast<object::TimelineBarSlice&>(slice).sound_start_ + (slice.start_ - cut_timer);
						bar.addSlice(newSlice);
						return;
					}
				}
			}
		}
	}
}