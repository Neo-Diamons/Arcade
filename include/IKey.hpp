/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Key
*/

#ifndef ARCADE_IKEY_HPP
#define ARCADE_IKEY_HPP

namespace arc {
    /**
     * @interface IKey
     * @brief Interface for the keyboard management
     */
    class IKey {
    public:
        /**
         * @brief Enum for the key
         */
        enum KeyEnum {
            UNKNOWN = -1,
            A = 0,
            B = 1,
            C = 2,
            D = 3,
            E = 4,
            F = 5,
            G = 6,
            H = 7,
            I = 8,
            J = 9,
            K = 10,
            L = 11,
            M = 12,
            N = 13,
            O = 14,
            P = 15,
            Q = 16,
            R = 17,
            S = 18,
            T = 19,
            U = 20,
            V = 21,
            W = 22,
            X = 23,
            Y = 24,
            Z = 25,
            NUM0 = 26,
            NUM1 = 27,
            NUM2 = 28,
            NUM3 = 29,
            NUM4 = 30,
            NUM5 = 31,
            NUM6 = 32,
            NUM7 = 33,
            NUM8 = 34,
            NUM9 = 35,
            ESCAPE = 36,
            SPACE = 57,
            RETURN = 58,
            BACKSPACE = 59,
            UP = 60,
            DOWN = 61,
            LEFT = 62,
            RIGHT = 63,
        };

        /**
         * @brief Check if a key is pressed
         * @param key The key to check
         * @return true if the key is pressed, false otherwise
         */
        virtual bool isKeyPressed(KeyEnum key) = 0;
    };
}

#endif //ARCADE_IKEY_HPP
