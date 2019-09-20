#include <devicebridge/application.hpp>
#include <devicebridge/configuration.hpp>

#include <iostream>

int main(int argc, char *argv[]) {
    DeviceBridge::application app(argc, argv);
    return app.start().normal_exit();
}
