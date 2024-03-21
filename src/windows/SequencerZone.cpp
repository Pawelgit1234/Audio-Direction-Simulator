#include "SequencerZone.hpp"

namespace ads
{
	namespace window
	{
		SequencerZone::SequencerZone(sf::RenderWindow& window)
			: panel_(sf::Vector2f(settings::WINDOW_WIDTH, settings::SEQUENSER_ZONE_HEIGHT)),
			window_(window)
		{
			panel_.setFillColor(settings::SEQUENSER_COLOR);
		}

		void SequencerZone::update(float zoom)
		{
			sf::Vector2f topLeftOfWindow = window_.mapPixelToCoords(sf::Vector2i(0, settings::WINDOW_HEIGHT - settings::SEQUENSER_ZONE_HEIGHT));
			panel_.setSize(sf::Vector2f(settings::WINDOW_WIDTH, settings::SEQUENSER_ZONE_HEIGHT) * zoom);
			panel_.setPosition(topLeftOfWindow);
		}
	}
}