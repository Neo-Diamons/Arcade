/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Core
*/

#ifndef ARCADE_CORE_HPP
#define ARCADE_CORE_HPP

#include <vector>
#include "include/IGame.hpp"

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

        IGraphical *_graphical = nullptr;
        IKey *_key = nullptr;
        IGame *_game = nullptr;

        std::vector<std::string> _graphicalLibs{};
        std::vector<std::string> _gameLibs{};
        uint8_t _graphicalIndex = 0;
        uint8_t _gameIndex = 0;

        std::string _name;

        void *loadLib(const std::string &path);
        void loadGraphicalLib(const std::string &path);
        void loadGameLib(const std::string &path);

        void globalAction();
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
