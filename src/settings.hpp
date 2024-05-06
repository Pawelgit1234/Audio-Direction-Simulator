#pragma once

#include <SFML/Graphics.hpp>

namespace ads
{
	namespace utils
	{
		struct TimelineTimer;
	}

	namespace settings
	{
		const unsigned short WINDOW_WIDTH = 1920;
		const unsigned short WINDOW_HEIGHT = 1080;
		const unsigned short TIMELINE_ZONE_HEIGHT = 400;
		const unsigned short TIME_PANEL_WIDTH = 100;
		const unsigned short TIME_PANEL_HEIGHT = 40;
		const float DYNAMIC_SPEAKER_SIZE = 50.f;
		const float EAR_SIZE = 50.f;
		const float WALL_WIDTH = 15.f;
		const float WALL_HEIGHT = 150.f;
		const float TIMELINE_MARKER_WIDTH = 10.f;
		const unsigned short FONT_SIZE = 25;
		const unsigned short TIMELINE_BAR_HEIGHT = 50;
		const unsigned short TIMELINE_BAR_OUTLINE_THICKNESS = 3.f;

		const sf::Color DYNAMIC_SPEAKER_COLOR = sf::Color::Red;
		const sf::Color EAR_COLOR = sf::Color::Green;
		const sf::Color WALL_COLOR = sf::Color::White;
		const sf::Color RAY_COLOR(211, 211, 211, 50);
		const sf::Color TIMELINE_COLOR(50, 50, 50);
		const sf::Color TIMELINE_MARKER_COLOR(255, 127, 80);
		const sf::Color TIME_PANEL_COLOR(80, 80, 80);
		const sf::Color FONT_COLOR = sf::Color::White;
		const sf::Color TIMELINE_SPEAKER_BAR_COLOR(179, 0, 0);
		const sf::Color TIMELINE_WALL_BAR_COLOR(191, 191, 191);
		const sf::Color TIMELINE_BAR_OUTLINE_COLOR(70, 70, 70);

		const float TIMELINE_START = 0.f;
		const float TIMELINE_END = 863.99f;

		const unsigned short NORMAL_SOUND_LEVEL = 50;
		const unsigned short NORMAL_SOUND_ANGLE = 50;
		const unsigned short RAY_COUNT = 1000;
		const float RAY_LENGTH = 2000.f;
		const unsigned short FRAMERATE_LIMIT = 60;
		const float TIMELINE_DRAGGING_EQUALIZER = 1876.f;
		const float TOTAL_DURATION_SECONDS = 100.f;
		const float BAR_SCALE_FACTOR = 2000.f;
		
		extern const char* WINDOW_NAME;
		extern const char* ICON_PATH;
		extern const std::string FONT_PATH;
		extern const std::string SPEAKERS_PATH;
	}
}