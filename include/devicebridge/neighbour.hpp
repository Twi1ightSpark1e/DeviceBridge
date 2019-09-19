#ifndef DEVICEBRIDGE_NEIGHBOUR_HPP
#define DEVICEBRIDGE_NEIGHBOUR_HPP

#include <string>
#include <vector>

#include <yaml-cpp/yaml.h>

namespace DeviceBridge {

    struct neighbour {

        struct connectivity {
            std::string interface; /*!< What will be used to connect: LAN, BlueTooth, etc. >*/
            std::string type; /*!< Information type about neighbour: MAC or IP address or etc. >*/
            std::string value; /*!< MAC or IP address or etc. itseft >*/
        };

        std::string name; /*!< Neighbour visible name >*/
        std::vector<connectivity> connectivities; /*!< Available connections to neighbour >*/
    };

YAML::Emitter& operator<<(YAML::Emitter &out, const DeviceBridge::neighbour &n);
YAML::Emitter& operator<<(YAML::Emitter &out, const std::vector<DeviceBridge::neighbour::connectivity> &v);
YAML::Emitter& operator<<(YAML::Emitter &out, const DeviceBridge::neighbour::connectivity &c);

} /* namespace DeviceBridge */

#endif // include guard
