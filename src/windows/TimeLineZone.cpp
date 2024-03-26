#include "TimeLineZone.hpp"

namespace ads
{
	namespace window
	{
		TimelineZone::TimelineZone(sf::RenderWindow& window)
			: panel_(sf::Vector2f(settings::WINDOW_WIDTH, settings::TIMELINE_ZONE_HEIGHT)), marker_(sf::Vector2f(settings::TIMELINE_MARKER_WIDTH, settings::TIMELINE_ZONE_HEIGHT)),
			window_(window), scale_(1.f), marker_pos_(0.f), timeline_pos_x_(0.f), timeline_pos_y_(0.f)
		{
			panel_.setFillColor(settings::TIMELINE_COLOR);
			marker_.setFillColor(settings::TIMELINE_MARKER_COLOR);
		}

		void TimelineZone::updatePositionAtWindow(float zoom)
		{
			sf::Vector2f newPos = window_.mapPixelToCoords(sf::Vector2i(0, settings::WINDOW_HEIGHT - settings::TIMELINE_ZONE_HEIGHT));

			panel_.setSize(sf::Vector2f(settings::WINDOW_WIDTH, settings::TIMELINE_ZONE_HEIGHT) * zoom);
			panel_.setPosition(newPos);

			float markerAbsolutePos = newPos.x + marker_pos_ * (settings::WINDOW_WIDTH * zoom - settings::TIMELINE_MARKER_WIDTH * zoom);
			marker_.setSize(sf::Vector2f(settings::TIMELINE_MARKER_WIDTH, settings::TIMELINE_ZONE_HEIGHT) * zoom);
			marker_.setPosition(markerAbsolutePos + timeline_pos_x_ * zoom, newPos.y);
		}
	}
}