#include "SequencerZone.hpp"

namespace ads
{
	namespace window
	{
		SequencerZone::SequencerZone() :
			window_(std::make_shared<sf::RenderWindow>(sf::VideoMode(settings::SEQUENSER_ZONE_WIDTH , settings::SEQUENSER_ZONE_HEIGHT), settings::WINDOW_NAME))
		{
		}
	}
}