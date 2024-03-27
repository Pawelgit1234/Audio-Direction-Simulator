#include "TimelineTimer.hpp"

namespace ads
{
	namespace utils
	{
		TimelineTimer::TimelineTimer(int h, int m, int s)
			: hours(h), minutes(m), seconds(s) {}

        TimelineTimer::TimelineTimer() : hours(0), minutes(0), seconds(0) {}

		std::string TimelineTimer::toString() const
        {
            std::string timeStr = "";
            if (hours < 10) timeStr += "0";
                timeStr += std::to_string(hours) + ":";

            if (minutes < 10) timeStr += "0";
                timeStr += std::to_string(minutes) + ":";

            if (seconds < 10) timeStr += "0";
                timeStr += std::to_string(seconds);

            return timeStr;
        }

        void TimelineTimer::convertTimeFromMarkerPosition(float marker_pos) const
        {
            float totalDurationSeconds = settings::TOTAL_DURATION_SECONDS;
            float markerTimeSeconds = marker_pos * totalDurationSeconds;

            hours = static_cast<int>(markerTimeSeconds) / 3600;
            minutes = (static_cast<int>(markerTimeSeconds) % 3600) / 60;
            seconds = static_cast<int>(markerTimeSeconds) % 60;
        }

	}
}