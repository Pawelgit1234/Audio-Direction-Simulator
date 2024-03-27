#include "TimeLineZone.hpp"

namespace ads
{
	namespace window
	{
		TimelineZone::TimelineZone(sf::RenderWindow& window)
			: panel_(sf::Vector2f(settings::WINDOW_WIDTH, settings::TIMELINE_ZONE_HEIGHT)), marker_(sf::Vector2f(settings::TIMELINE_MARKER_WIDTH, settings::TIMELINE_ZONE_HEIGHT)),
			window_(window), scale_(1.f), marker_pos_(0.f), timeline_pos_x_(0.f), timeline_pos_y_(0.f), is_running_(false),
			time_panel_(sf::Vector2f(settings::TIME_PANEL_WIDTH, settings::TIME_PANEL_HEIGHT))
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
		}

		void TimelineZone::updateTimeText()
		{
			time_.convertTimeFromMarkerPosition(marker_pos_);
			time_text_.setString(time_.toString());
		}
	}
}