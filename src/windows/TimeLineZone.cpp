#include "TimeLineZone.hpp"

namespace ads
{
	namespace window
	{
		TimeLineZone::TimeLineZone(sf::RenderWindow& window)
			: panel_(sf::Vector2f(settings::WINDOW_WIDTH, settings::TIME_LINE_ZONE_HEIGHT)),
			window_(window)
		{
			panel_.setFillColor(settings::TIME_LINE_COLOR);
		}

		void TimeLineZone::update(float zoom)
		{
			sf::Vector2f newPos = window_.mapPixelToCoords(sf::Vector2i(0, settings::WINDOW_HEIGHT - settings::TIME_LINE_ZONE_HEIGHT));
			panel_.setSize(sf::Vector2f(settings::WINDOW_WIDTH, settings::TIME_LINE_ZONE_HEIGHT) * zoom);
			panel_.setPosition(newPos);
		}
	}
}