/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Exception
*/

#ifndef ARCADE_EXCEPTION_HPP
#define ARCADE_EXCEPTION_HPP

#include <exception>
#include <string>

namespace arc {
    /**
     * @brief Exception class for the arcade project
     */
    class Exception : public std::exception {
    public:
        Exception(const std::string &name, const std::string &message) : _message(name + ": " + message) {}
        [[nodiscard]] const char *what() const noexcept override { return _message.c_str(); }

    private:
        std::string _message;
    };
}

#endif //ARCADE_EXCEPTION_HPP
