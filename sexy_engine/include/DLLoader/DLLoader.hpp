//
// Created by mymy on 04/01/18.
//

#ifndef RTYPE_DLLOADER_HPP
#define RTYPE_DLLOADER_HPP

#ifdef WIN32
#include <windows.h>
#endif

#include <utility>
#include <string>
#include <vector>
#include <memory>

namespace utils {
    class DLLoader {
#ifdef WIN32
            std::vector<std::pair<std::string, HINSTANCE>> _dlHandles;
#else
        std::vector<std::pair<std::string, void *>>     _dlHandles;
#endif
    public:
        DLLoader() : _dlHandles(0) {};
        ~DLLoader() = default;

        void    dlOpen(std::string const &);
        void    dlClose(std::string const &);
        void    dlCloseAll() noexcept;
        void    *dlSym(std::string const &, std::string const &) const;

        template<typename T>
        std::unique_ptr<T> loadDLL(std::string const &fileName, std::string const &sym)
        {
            void *func = this->dlSym(fileName, sym);
            return (std::unique_ptr<T>((reinterpret_cast<T *(*)()>(func))()));
        }

    };
}

#endif //RTYPE_DLLOADER_HPP
