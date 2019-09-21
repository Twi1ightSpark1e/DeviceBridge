#ifndef DEVICEBRIDGE_CONFIGURATION_HPP
#define DEVICEBRIDGE_CONFIGURATION_HPP

#include <devicebridge/error.hpp>
#include <devicebridge/neighbour.hpp>

#include <filesystem>
#include <vector>
#include <string_view>

namespace DeviceBridge {

    /*! \class configuration
     *  \brief Parses and holds configuration file
     *
     *  Loads YAML configuration file, parses it, holds information
     */
    class configuration {
    public:
        virtual ~configuration();

        /*! \brief Change configuration file path
         *
         *  Changes internal configuration file path, and parses it
         *
         * \param path Configuration file path
         * \return Is file parsed successfully
         */
        [[nodiscard]] error_code set_path(const std::filesystem::path &path);

        /*! \brief Dump current configuration
         *
         *  Pretty prints current configuration into selected `ostream`
         *
         * \param out Output stream
         * \return Error code
         */
        [[nodiscard]] error_code dump(std::ostream &out);

    protected:
        [[nodiscard]] error_code parse_file();

        std::filesystem::path m_path; /*!< Configuration file path >*/
        std::vector<std::string> m_capabilities; /*!< Capabilities list >*/
        std::vector<neighbour> m_neighbors; /*!< Neighbors list >*/
    };

} // namespace DeviceBridge

#endif /* end of include guard */
