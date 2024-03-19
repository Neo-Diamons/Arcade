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
#include "DLLoader.hpp"

/**
 * @brief Namespace for the arcade project
 */
namespace arc {
    /**
     * @brief Core class for the arcade project
     */
    class Core {
    private:
        const std::vector<std::string> _graphicalLibFiles = {
            "arcade_ncurses.so",
            "arcade_sdl2.so",
            "arcade_ndk++.so",
            "arcade_aalib.so",
            "arcade_libcaca.so",
            "arcade_allegro5.so",
            "arcade_xlib.so",
            "arcade_gtk+.so",
            "arcade_sfml.so",
            "arcade_irrlicht.so",
            "arcade_opengl.so",
            "arcade_vulkan.so",
            "arcade_qt5.so"
        };
        const std::vector<std::string> _gameLibFiles = {
            "arcade_snake.so",
            "arcade_nibbler.so",
            "arcade_pacman.so",
            "arcade_qix.so",
            "arcade_centipede.so",
            "arcade_solarfox.so"
        };

        DLLoader<IGraphical> _graphicalLoader;
        DLLoader<IGame> _gameLoader;

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

        void loadGraphicalLib(const std::string &path);
        void loadGameLib(const std::string &path);

        void getLib();

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
         * @brief Destructor for the core
         */
        ~Core();

        /**
         * @brief Run the core
         */
        void run();
    };
}

#endif //ARCADE_CORE_HPP
