/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Color
*/

#ifndef ARCADE_COLOR_HPP
#define ARCADE_COLOR_HPP

#define WHITE Color(255, 255, 255)
#define BLACK Color(0, 0, 0)
#define RED Color(255, 0, 0)
#define GREEN Color(0, 255, 0)
#define BLUE Color(0, 0, 255)
#define YELLOW Color(255, 255, 0)
#define MAGENTA Color(255, 0, 255)
#define CYAN Color(0, 255, 255)

namespace arc {
    /**
     * @brief Class for the color
     */
    class Color {
    public:
        short r;
        short g;
        short b;

        Color(const short r, const short g, const short b)
            : r(r), g(g), b(b) {}

        bool operator==(const Color &other) const {
            return r == other.r &&
                   g == other.g &&
                   b == other.b;
        }
    };
}

#endif //ARCADE_COLOR_HPP
