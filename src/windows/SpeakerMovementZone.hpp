#pragma once

#include <SFML/Graphics.hpp>

#include <vector>
#include <stdexcept>

#include "../settings.hpp"
#include "../objects/DynamicSpeaker.hpp"
#include "../utils/Logger.hpp"

namespace ads
{
	namespace window
	{
		class App;

		class SpeakerMovementZone
		{
		public:
			SpeakerMovementZone();

			void run();

			void addDynamicSpeaker(unsigned short id);
			ads::object::DynamicSpeaker getDynamicSpeaker(unsigned short id);
			void controll();

			void setZoom(float zoom) { zoom_ = zoom; }
			float getZoom() const { return zoom_; }

		private:
			float zoom_;

			std::shared_ptr<sf::RenderWindow> window_;
			std::vector<ads::object::DynamicSpeaker> dynamic_speakers_;

			friend App;
		};
	}
}