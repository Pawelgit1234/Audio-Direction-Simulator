#pragma once

#include <SFML/Graphics.hpp>

#include <vector>
#include <stdexcept>
#include <cmath>

#include "../settings.hpp"
#include "../objects/DynamicSpeaker.hpp"
#include "../utils/Logger.hpp"
#include "../utils/Common.hpp"

namespace ads
{
	namespace window
	{
		class App;

		class SpeakerMovementZone
		{
		public:
			SpeakerMovementZone();

			void addDynamicSpeaker(unsigned short id);
			ads::object::DynamicSpeaker getDynamicSpeaker(unsigned short id);
			void controll();

			void setZoom(float zoom) { zoom_ = zoom; }
			float getZoom() const { return zoom_; }

		private:
			float zoom_;

			sf::RenderWindow window_;
			sf::View view_;
			std::vector<ads::object::DynamicSpeaker> dynamic_speakers_;

			friend App;
		};
	}
}