/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** DrawObject
*/

#ifndef DRAWOBJECT_HPP
#define DRAWOBJECT_HPP

namespace arc {
    /**
     * @brief Enum for the type of the object to draw
     */
    enum ObjectType {
        TEXT,
        RECT,
        FILLRECT,
        TEXTURE
    };

    /**
     * @brief Class for the object to draw
     */
    class DrawObject {
    private:
        ObjectType type;

    public:
        /**
         * @brief Constructor for the object to draw
         * @param type Type of the object to draw
         */
        explicit DrawObject(ObjectType type) : type(type) {}

        /**
         * @brief Destructor for the object to draw
         */
        virtual ~DrawObject() = default;

        /**
         * @brief Get the type of the object to draw
         * @return ObjectType
         */
        [[nodiscard]] ObjectType getType() const { return type; }
    };
}

#endif //DRAWOBJECT_HPP
