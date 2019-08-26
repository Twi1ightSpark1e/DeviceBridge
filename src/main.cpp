#include <devicebridge/application.hpp>

int main(int argc, const char *argv[]) {
    DeviceBridge::application app(argc, argv);
    return app.start();
}
