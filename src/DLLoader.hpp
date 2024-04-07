/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** DLLoader
*/

#ifndef ARCADE_DLLOADER_HPP
#define ARCADE_DLLOADER_HPP

#include <iostream>
#include <dlfcn.h>
#include <string>

#include "include/Exception.hpp"
#include "include/LibraryType.hpp"

namespace arc {
    /**
     * @brief Class to load a dynamic library
     * @tparam T
     */
    template <typename T>
    class DLLoader {
    private:
        void *_lib = nullptr;
        LibraryType _type;

    public:
        /**
         * @brief Exception for the DLLoader
         */
        class DLLoaderException final : public Exception {
        public:
            explicit DLLoaderException(const std::string &message) : Exception("DLLoader", message) {}
        };

        /**
         * @brief Constructor
         * @param type The type of the library
         */
        explicit DLLoader(const LibraryType type) : _type(type) {}

        /**
         * @brief Get the type of the library
         * @return The type of the library
         */
        LibraryType getType(const std::string &path)
        {
            _lib = dlopen(path.c_str(), RTLD_LAZY);
            if (!_lib)
                throw DLLoaderException(dlerror());
            void *getType = dlsym(_lib, "getType");
            if (!getType)
                throw DLLoaderException(dlerror());
            const LibraryType type = reinterpret_cast<LibraryType (*)()>(getType)();
            dlclose(_lib);
            return type;
        }

        /**
         * @brief Get an instance of a Object from a dynamic library
         * @param path The path to the dynamic library
         * @return An new instance of the Object
         */
        T *getInstance(const std::string &path)
        {
            _lib = dlopen(path.c_str(), RTLD_LAZY);
            if (!_lib)
                throw DLLoaderException(dlerror());
            void *getType = dlsym(_lib, "getType");
            if (reinterpret_cast<LibraryType (*)()>(getType)() != _type)
                throw DLLoaderException("Invalid library type");
            void *constructor = dlsym(_lib, "create");
            if (!constructor)
                throw DLLoaderException(dlerror());
            return reinterpret_cast<T *(*)()>(constructor)();
        }

        /**
         * @brief Destroy an instance of a Object from a dynamic library
         * @param instance The instance to destroy
         */
        void destroyInstance(T *instance)
        {
            void *destructor = dlsym(_lib, "destroy");
            if (!destructor)
                throw DLLoaderException(dlerror());
            reinterpret_cast<void (*)(T *)>(destructor)(instance);
            dlclose(_lib);
        }
    };
}


#endif //ARCADE_DLLOADER_HPP
