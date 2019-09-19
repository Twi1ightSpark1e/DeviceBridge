#include <devicebridge/application.hpp>
#include <devicebridge/configuration.hpp>

#include <iostream>

int main(int argc, char *argv[]) {
    DeviceBridge::application app(argc, argv);
    auto result = app.start();
    if (result.raw() != DeviceBridge::error_code::NO_ERROR) {
        std::cout << result.to_string() << std::endl;
    }
    return result.raw();
}
