#ifndef DEVICEBRIDGE_ERROR_HPP
#define DEVICEBRIDGE_ERROR_HPP

#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <string>

namespace DeviceBridge {

    /*! \class error_codes
     *  \brief Centralized place to work with internal errors
     *
     *  Class to work with internal errors
     */
    class error_code {
    protected:
        uint8_t m_value; /*!< Error code itseft >*/
        char* m_message; /*!< Error message >*/

    public:
        static constexpr uint8_t
            NO_ERROR = 0,
            FILE_NOT_OPENED = 1,
            MALFORMED_CONFIGURATION = 2,
            GENERIC = 255;

        constexpr error_code(void) noexcept : m_value(NO_ERROR), m_message(0) {  }
        constexpr error_code(uint8_t value) noexcept : m_value(value), m_message(0) {  }
        constexpr error_code(uint8_t value, const std::string_view& message) noexcept
                : m_value(value), m_message(0) {
            m_value = value;
            m_message = new char[strlen(message.data())];
            strcpy(m_message, message.data());
        }

        constexpr auto raw() const noexcept { return m_value; };
        constexpr operator uint8_t() const noexcept { return m_value; };
        constexpr operator bool() const noexcept { return m_value != NO_ERROR; };

        std::string_view to_string() const noexcept {
            static const std::map<uint8_t, std::string_view> messages {{
                { error_code::NO_ERROR, "No error" },
                { error_code::FILE_NOT_OPENED, "File cannot be opened" },
                { error_code::MALFORMED_CONFIGURATION, "Malformed configuration" },
                { error_code::GENERIC, "Generic error" }
            }};

            auto res = messages.find(m_value);
            if (res != messages.end()) {
                return res->second;
            }
            return "No such error code";
        }

        int normal_exit() const {
            if (*this) { // see `operator bool()`
                std::cerr << "An error '" << to_string() << "' has occured";
                if (m_message) {
                    std::cerr << ": " << m_message;
                }
                std::cerr << '\n';
            }
            return m_value;
        }

        void abort() const {
            ::exit(normal_exit());
        }
    };

} /* namespace DeviceBridge */

#endif /* end of include guard */
