#pragma once

#include <iostream>
#include <string>
#include <chrono>
#include <ctime>

namespace ads
{
	namespace utils
	{
		enum class LoggerType
		{
			INFO,
			WARNING,
			CRITICAL,
		};

		void log(const std::string& msg, LoggerType msg_type);
	}
}