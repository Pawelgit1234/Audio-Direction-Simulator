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

        void TimelineTimer::convertTimeFromPosition(float pos)
        {
            float timeSeconds = pos * settings::TOTAL_DURATION_SECONDS;

            hours = static_cast<int>(timeSeconds) / 3600;
            minutes = (static_cast<int>(timeSeconds) % 3600) / 60;
            seconds = static_cast<int>(timeSeconds) % 60;
        }

        float TimelineTimer::convertPositionFromTime() const
        {
            float currentTimeInSeconds = hours * 3600 + minutes * 60 + seconds;
            float pos = currentTimeInSeconds / settings::TOTAL_DURATION_SECONDS;

            return pos;
        }

        unsigned short TimelineTimer::getSecondsSum() const
        {
            return seconds + minutes * 60 + hours * 3600;
        }

        TimelineTimer TimelineTimer::operator+(const TimelineTimer& other) const
        {
            TimelineTimer result;
            result.hours = this->hours + other.hours;
            result.minutes = this->minutes + other.minutes;
            result.seconds = this->seconds + other.seconds;

            if (result.seconds >= 60)
            {
                result.minutes += result.seconds / 60;
                result.seconds %= 60;
            }
            if (result.minutes >= 60)
            {
                result.hours += result.minutes / 60;
                result.minutes %= 60;
            }

            return result;
        }

        TimelineTimer TimelineTimer::operator-(const TimelineTimer& other) const
        {
            TimelineTimer result;
            result.hours = this->hours - other.hours;
            result.minutes = this->minutes - other.minutes;
            result.seconds = this->seconds - other.seconds;

            if (result.seconds < 0)
            {
                result.minutes -= 1;
                result.seconds += 60;
            }
            if (result.minutes < 0)
            {
                result.hours -= 1;
                result.minutes += 60;
            }

            return result;
        }
	}
}