#include <devicebridge/configuration.hpp>
#include <devicebridge/error.hpp>

#include <iostream>
#include <fstream>
#include <sstream>

#include <string.h>

#include <yaml-cpp/yaml.h>

namespace fs = std::filesystem;

namespace DeviceBridge {

    configuration::~configuration() {  }

    error_code configuration::set_path(const fs::path &path) {
        m_path = path;
        return parse_file();
    }

    error_code configuration::parse_file() {
        errno = 0;
        std::ifstream config_file(m_path);
        if (!config_file.is_open()) {
            return error_code(error_code::FILE_NOT_OPENED, strerror(errno));
        }
        const auto &config = YAML::Load(config_file);

        if (!config["capabilities"]) {
            return error_code(
                    error_code::MALFORMED_CONFIGURATION,
                    "There are no capabilities described");
        }

        const auto &capabilities = config["capabilities"];
        for (auto cap : capabilities) {
            m_capabilities.push_back(cap.as<std::string>());
        }

        if (!config["neighbors"]) {
            return error_code("Neighbors aren't in configuration file");
        }

        const auto &neighbors = config["neighbors"];
        for (auto nei_node: neighbors) {
            if (!nei_node["name"] || !nei_node["connectivity"]) {
                return error_code(
                        error_code::MALFORMED_CONFIGURATION,
                        "One of neighbors does not have name or connectivity methods");
            }

            auto &n = m_neighbors.emplace_back();
            n.name = nei_node["name"].as<std::string>();
            n.connectivities.reserve(nei_node["connectivity"].size());
            for (const auto &con : nei_node["connectivity"]) {
                if (con["lan"]) {
                    const auto &lan = con["lan"];
                    for (const auto &l : lan) {
                        auto &con_info = n.connectivities.emplace_back();
                        con_info.interface = "lan";
                        if (l["mac"]) {
                            con_info.type = "mac";
                            con_info.value = l["mac"].as<std::string>();
                        } else if (l["ip"]) {
                            con_info.type = "ip";
                            con_info.value = l["ip"].as<std::string>();
                        } else if (l["ipv6"]) {
                            con_info.type = "ipv6";
                            con_info.value = l["ipv6"].as<std::string>();
                        } else {
                            return error_code(
                                    error_code::MALFORMED_CONFIGURATION,
                                    "Wrong connectivity option described");
                        }
                    }
                } else if (con["bluetooth"]) {
                    const auto &bluetooth = con["bluetooth"];
                    for (const auto &bt : bluetooth) {
                        auto &con_info = n.connectivities.emplace_back();
                        con_info.interface = "bluetooth";
                        if (bt["mac"]) {
                            con_info.type = "mac";
                            con_info.value = bt["mac"].as<std::string>();
                        } else {
                            return error_code(
                                    error_code::MALFORMED_CONFIGURATION,
                                    "Wrong connectivity option described");
                        }
                    }
                } else {
                    return error_code(
                            error_code::MALFORMED_CONFIGURATION,
                            "Wrong connectivity type");
                }
            }
        }

        return error_code();
    }

    error_code configuration::dump(std::ostream &out) {
        std::ostream::sentry s(out);
        if (s) {
            YAML::Emitter yaml(out);
            yaml << YAML::BeginMap;

            yaml << YAML::Key << "capabilities";
            yaml << YAML::Value << m_capabilities;

            yaml << YAML::Key << "neighbors";
            yaml << YAML::Value << m_neighbors;

            yaml << YAML::EndMap;
            return error_code();
        }
        return error_code(
                error_code::FILE_NOT_OPENED,
                "Dump destination is not ready");
    }

} /* namespace DeviceBridge */
