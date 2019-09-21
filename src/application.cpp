#include <devicebridge/application.hpp>

#include <iostream>

#include <getopt.h>
#include <pwd.h>
#include <sys/types.h>
#include <unistd.h>

namespace fs = std::filesystem;

namespace DeviceBridge {

    application::application(const int argc, char *argv[]) {
        m_execname = argv[0];
        parse_args(argc, argv);

        if (m_strargs.find("config") == m_strargs.end()) {
            struct passwd *pw = getpwuid(getuid());
            fs::path home_dir(pw->pw_dir);
            fs::path default_config(home_dir / ".config" / "DeviceBridge" / "config.yaml");
            m_strargs.insert_or_assign("config", default_config.string());
        }
    }

    application::~application() {  }

    error_code application::start() {
        { // print help, if required
            auto res = m_boolargs.find("help");
            if ((res != m_boolargs.end()) && res->second) {
                print_help();
                return error_code();
            }
        }
        { // load configuration
            try {
                auto res = m_strargs.at("config");
                m_config.set_path(res).handle();
            } catch (const std::out_of_range &exc) {
                return error_code(
                        error_code::FILE_NOT_OPENED,
                        "Configuration file is not set");
            } catch (const std::exception &exc) {
                std::cerr << "Generic error\n";
                return error_code(
                        error_code::FILE_NOT_OPENED,
                        "Generic error");
            }
        }
        { // dump configuration, if required
            auto res = m_boolargs.find("dump");
            if (res != m_boolargs.end() && res->second) {
                m_config.dump(std::cout).handle();
                std::cout << '\n';
                return error_code();
            }
        }
        return error_code();
    }

    void application::parse_args(const int argc, char *argv[]) {
        int choice;
        while (1) {
            static struct option long_options[] = {
                /* Use flags like so:
                {"verbose",	no_argument,	&verbose_flag, 'V'}*/
                /* Argument styles: no_argument, required_argument, optional_argument */
                {"help",    no_argument,        0,  'h'},
                {"config",  required_argument,  0,  'c'},
                {"dump",    no_argument,        0,  'd'},
                {0,0,0,0}
            };

            /* Argument parameters:
                no_argument: " "
                required_argument: ":"
                optional_argument: "::" */
            static std::string short_options("hc:d");

            int option_index = 0;
            choice = getopt_long(argc, argv, short_options.c_str(),
                        long_options, &option_index);

            if (choice == -1) {
                break;
            }

            switch(choice) {
                case 'h':
                    m_boolargs["help"] = true;
                    break;

                case 'c':
                    m_strargs["config"] = optarg;
                    break;

                case 'd':
                    m_boolargs["dump"] = true;
                    break;

                case '?':
                    /* getopt_long will have already printed an error */
                    break;
            }
        }

        /* Deal with non-option arguments here */
        if (optind < argc) {
            while (optind < argc) {
                m_addargs.emplace_back(argv[optind++]);
            }
        }
    }

    void application::print_help() const {
        std::cout << "DeviceBridge application\n";
        std::cout << "Authored by Twi1ightSpark1e\n\n";

        std::cout << "Usage:\n";
        std::cout << "    " << m_execname << " [-h] [-c|--config=filename] [-d|--dump]\n\n";

        std::cout << "Where:\n";
        std::cout << "       -h        Show this message\n\n";

        std::cout << "       -c        Use selected configuration file, instead of default one\n";
        std::cout << " --config\n\n";

        std::cout << "       -d        Dump loaded configuration file into standard output\n";
        std::cout << "   --dump\n";
    }

} // namespace DeviceBridge
