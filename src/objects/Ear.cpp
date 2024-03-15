#include "Ear.hpp"

namespace ads
{
	namespace object
	{
		Ear::Ear()
			: circle_(settings::EAR_SIZE)
		{
			circle_.setFillColor(settings::EAR_COLOR);
			circle_.setPosition(0.f, 0.f);
		}
	}
}
