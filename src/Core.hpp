/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Core
*/

#ifndef ARCADE_CORE_HPP
#define ARCADE_CORE_HPP

#include "include/Exception.hpp"
#include "include/Graphical.hpp"

/**
 * @brief Namespace for the arcade project
 */
namespace arc {
    /**
     * @brief Core class for the arcade project
     */
    class Core {
    private:
        void *_graphicalLib{};
        void *_gameLib{};

        Graphical *_graphical{};

        void loadGraphicalLib(const std::string &path);
        void loadGameLib(const std::string &path);

        void selectionLoop();
    public:
        /**
         * @brief Exception implementation for the Core
         */
        class CoreException : public Exception {
        public:
            explicit CoreException(const std::string &message) : Exception("Core", message) {}
        };

        /**
         * @brief Constructor for the core
         * @param path Path to the graphical library
         */
        explicit Core(const std::string &path);

        /**
         * @brief Run the core
         */
        void run();
    };
}

#endif //ARCADE_CORE_HPP
