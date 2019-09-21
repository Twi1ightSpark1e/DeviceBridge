#ifndef DEVICEBRIDGE_ERROR_HPP
#define DEVICEBRIDGE_ERROR_HPP

#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <memory>
#include <sstream>

namespace DeviceBridge {

    /*! \class error_codes
     *  \brief Centralized place to work with internal errors
     *
     *  Class to work with internal errors
     */
    class error_code {
    protected:
        uint8_t m_value; /*!< Error code itseft >*/
        std::ostringstream m_message; /*!< Error message >*/

    public:
        static constexpr uint8_t
            NO_ERROR = 0, /*!< Everything-is-okay code >*/
            FILE_NOT_OPENED = 1, /*!< Cannot-open-file code >*/
            MALFORMED_CONFIGURATION = 2, /*!< Shitty-config code >*/
            GENERIC = 255; /*!< Fallback code >*/

        /*! \brief Everything-is-okay constructor
         *
         *  Uses NO_ERROR as error code, and zero-initializes message
         *
         * \param argc Execute arguments amount
         * \param argv Execute arguments
         */
        error_code(void) noexcept : m_value(NO_ERROR) {  }

        /*! \brief Warning constructor
         *
         *  Uses NO_ERROR as error code, but stores given message
         *
         * \param message Message that will be stored
         */
        template<typename... Args>
        error_code(Args&&... args) noexcept : m_value(NO_ERROR) {
            (m_message << ... << args);
        }

        /*! \brief Quiet error constructor
         *
         *  Uses given error code, and zero-initializes message
         *
         * \param value Error code
         */
        error_code(uint8_t value) noexcept : m_value(value) {  }

        /*! \brief Verbose error constructor
         *
         *  Uses given error code, and stores given message
         *
         * \param value Error code
         * \param message Message that will be stored
         */
        template<typename... Args>
        error_code(uint8_t value, Args&&... args) noexcept : m_value(value) {
            (m_message << ... << args);
        }

        auto raw() const noexcept { return m_value; };
        operator uint8_t() const noexcept { return m_value; };
        operator bool() const noexcept { return m_value != NO_ERROR; };

        /*! \brief Get error code's string representation
         *
         * \return Error code's string representation
         */
        std::string to_string() const noexcept {
            static const std::map<uint8_t, std::string_view> messages {{
                { error_code::NO_ERROR, "No error" },
                { error_code::FILE_NOT_OPENED, "File cannot be opened" },
                { error_code::MALFORMED_CONFIGURATION, "Malformed configuration" },
                { error_code::GENERIC, "Generic error" }
            }};

            std::ostringstream oss;

            if (!*this && has_message()) { // Warning constructor were used
                oss << "Warning: " << m_message.str();
                return oss.str();
            }

            if (!*this) { return ""; } // Everything-is-okay constructor were used

            auto res = messages.find(m_value);
            if (res != messages.end()) {
                oss << "Error '" << res->second << "'";
                if (has_message()) {
                    oss << ": " << m_message.str();
                }
                return oss.str();
            }
            return "No such error code";
        }

        /*! \brief Is everything-is-okay constructor were used */
        bool is_empty() const noexcept {
            return !(*this || has_message());
        }

        bool has_message() const noexcept {
            return m_message.str().size() != 0;
        }

        /*! \brief Handles current error state
         *
         *  If there is a warning or error inside - print it.
         *  If there is an error inside -- exit after that.
         */
        void handle() const noexcept {
            if (!is_empty()) {
                std::cerr << to_string() << '\n';
            }
            if (*this) {
                ::exit(m_value);
            }
        }
    };

} /* namespace DeviceBridge */

#endif /* end of include guard */
