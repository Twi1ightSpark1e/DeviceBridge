#include <devicebridge/neighbour.hpp>

#include <yaml-cpp/yaml.h>

namespace DeviceBridge {

YAML::Emitter& operator<<(YAML::Emitter &out, const DeviceBridge::neighbour::connectivity &c) {
    out << YAML::BeginMap;
    out << YAML::Key << c.type << YAML::Value << c.value;
    out << YAML::EndMap;
    return out;
}

YAML::Emitter& operator<<(YAML::Emitter &out, const std::vector<DeviceBridge::neighbour::connectivity> &v) {
    if (v.size() == 0) {
        return out;
    }

    out << YAML::BeginSeq;
    for (auto con = v.cbegin(); con != v.cend(); con++) {
        out << YAML::BeginMap;
        auto interface = con->interface;
        out << YAML::Key << interface;
        out << YAML::Value << YAML::BeginSeq;
        while (con->interface == interface) {
            out << *con;
            con++;
        }
        con--; // cause `con` will be incremented before next iteration
        out << YAML::EndSeq;
        out << YAML::EndMap;
    }
    out << YAML::EndSeq;
    return out;
}

YAML::Emitter& operator<<(YAML::Emitter &out, const DeviceBridge::neighbour &n) {
    out << YAML::BeginMap;

    out << YAML::Key << "name";
    out << YAML::Value << n.name;

    out << YAML::Key << "connectivity";
    out << YAML::Value << n.connectivities;

    out << YAML::EndMap;
    return out;
}

} /* namespace DeviceBridge */

