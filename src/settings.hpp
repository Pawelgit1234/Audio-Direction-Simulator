#pragma once

#include <SFML/Graphics.hpp>

namespace ads
{
	namespace settings
	{
		const unsigned short WINDOW_WIDTH = 1280;
		const unsigned short WINDOW_HEIGHT = 720;
		const unsigned short SEQUENSER_ZONE_HEIGHT = 300;

		const sf::Color DYNAMIC_SPEAKER_COLOR = sf::Color::Red;
		const sf::Color EAR_COLOR = sf::Color::Green;

		const unsigned short NORMAL_SOUND_LEVEL = 50;

		const float DYNAMIC_SPEAKER_SIZE = 50.f;
		const float EAR_SIZE = 50.f;

		extern const char* WINDOW_NAME;
		extern const char* ICON_PATH;
	}
}