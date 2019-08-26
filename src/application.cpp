#include <devicebridge/application.hpp>

#include <iostream>

namespace DeviceBridge {

    application::application(const int argc, const char *argv[]) {
        m_execname = argv[0];
        for (int i = 1; i < argc; i++) {
            m_args.emplace_back(argv[i]);
        }
    }

    application::~application() {  }

    int application::start() {
        std::cout << "Here is all what you passed as arguments:\n";
        for (auto arg : m_args) {
            std::cout << arg << "\n";
        }
        return 0;
    }

} // namespace DeviceBridge
