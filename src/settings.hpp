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
		const sf::Color WALL_COLOR = sf::Color::White;
		const sf::Color RAY_COLOR = sf::Color(211, 211, 211);

		const unsigned short NORMAL_SOUND_LEVEL = 50;
		const unsigned short NORMAL_SOUND_ANGLE = 50;
		const unsigned short RAY_COUNT = 1000;
		const float RAY_LENGTH = 2000.f;
		const unsigned short FRAMERATE_LIMIT = 60;

		const float DYNAMIC_SPEAKER_SIZE = 50.f;
		const float EAR_SIZE = 50.f;
		const float WALL_WIDTH = 15.f;
		const float WALL_HEIGHT = 150.f;

		extern const char* WINDOW_NAME;
		extern const char* ICON_PATH;
	}
}