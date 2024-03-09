#include "App.hpp"

namespace ads
{
    namespace window
    {
        void App::run()
        {
            ads::logger::log("Program started.", ads::logger::LoggerType::INFO);

            speaker_zone_.run();
            sequenser_zone_.run();

        }
    }
}
