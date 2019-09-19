#ifndef DEVICEBRIDGE_ERROR_HPP
#define DEVICEBRIDGE_ERROR_HPP

#include <cstdint>
#include <optional>
#include <string>
#include <typeinfo>

namespace DeviceBridge {

    /*! \class error_codes
     *  \brief Centralized place to work with internal errors
     *
     *  Class to work with internal errors
     */
    class error_code {
    protected:
        uint8_t m_value; /*!< Error code itseft >*/

    public:
        static const uint8_t
            NO_ERROR = 0,
            FILE_NOT_OPENED = 1,
            MALFORMED_CONFIGURATION = 2,
            GENERIC = 255;

        constexpr error_code(void) noexcept : m_value(NO_ERROR) {  }
        constexpr error_code(uint8_t value) noexcept : m_value(value) {  }
        error_code(const error_code&) = delete;
        error_code& operator=(const error_code&) = delete;
        error_code(error_code&&) = delete;
        error_code& operator=(error_code&&) = delete;

        constexpr std::string_view to_string() const noexcept {
            switch (m_value) {
                case NO_ERROR:
                    return "No error";
                case FILE_NOT_OPENED:
                    return "File cannot be opened";
                case MALFORMED_CONFIGURATION:
                    return "Malformed configuration";
                default:
                    return "No such error code";
            }
        }

        constexpr auto raw() const noexcept { return m_value; };
        constexpr operator uint8_t() const noexcept { return m_value; };
        constexpr operator bool() const noexcept { return m_value != NO_ERROR; };
    };

} /* namespace DeviceBridge */

#endif /* end of include guard */
