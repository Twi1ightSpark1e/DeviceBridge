#pragma once

#include <devicebridge/configuration.hpp>
#include <devicebridge/error.hpp>

#include <filesystem>
#include <map>
#include <string_view>
#include <vector>

namespace DeviceBridge {
    /*! \class application
     *  \brief Describes application work logic
     */
    class application
    {
    public:
        /*! \brief Basic constructor
         *
         *  Saves given execute arguments for further using
         *
         * \param argc Execute arguments amount
         * \param argv Execute arguments
         */
        application(const int argc, char *argv[]);
        virtual ~application();

        application(const application&) = delete;
        application& operator=(const application&) = delete;
        application(application&&) = delete;
        application& operator=(application&&) = delete;

        /*! \brief Entry point
         *
         *  Starts implementing work logic
         *
         * \return Exit code
         */
        error_code start();

    protected:
        /*! \brief Parse incoming arguments
         *
         *  Parses given arguments and fills corresponding class members
         *
         * \param argc Execute arguments amount
         * \param argv Execute arguments
         */
        void parse_args(const int argc, char *argv[]);

        /*! \brief Print help to stdout */
        void print_help() const;

        std::string_view m_execname; /*!< Executable file name, formerly known as argv[0] >*/
        std::vector<std::string_view> m_addargs; /*!< Additional arguments >*/
        std::map<std::string_view, bool> m_boolargs; /*!< Boolean arguments >*/
        std::map<std::string_view, std::string> m_strargs; /*!< String arguments >*/

        configuration m_config; /*!< Configuration file parser >*/
    };
} // namespace DeviceBridge

