/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** DLLoader
*/

#ifndef ARCADE_DLLOADER_HPP
#define ARCADE_DLLOADER_HPP

#include <dlfcn.h>
#include <string>

#include "include/Exception.hpp"

namespace arc {
    /**
     * @brief Class to load a dynamic library
     * @tparam T
     */
    template<typename T>
    class DLLoader {
    private:
        void *_lib = nullptr;

    public:
        /**
         * @brief Exception for the DLLoader
         */
        class DLLoaderException : public Exception {
        public:
            explicit DLLoaderException(const std::string &message) : Exception("DLLoader", message) {}
        };

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
