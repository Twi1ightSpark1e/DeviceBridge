#pragma once

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
        application(const int argc, const char *argv[]);
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
        int start();

    protected:
        std::string_view m_execname; /*!< Executable file name, formerly known as argv[0] >*/
        std::vector<std::string_view> m_args; /*!< All passed arguments >*/
    };
} // namespace DeviceBridge

