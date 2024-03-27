#pragma once

#include <string>

#include "../settings.hpp"

namespace ads
{
	namespace utils
	{
		struct TimelineTimer
		{
            mutable int hours;
            mutable int minutes;
            mutable int seconds;

            TimelineTimer(int h, int m, int s);
			TimelineTimer();

			std::string toString() const;
			void convertTimeFromMarkerPosition(float marker_pos) const;
		};
	}
}


