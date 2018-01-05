//
// Created by mymy on 04/01/18.
//

#ifndef RTYPE_DLLOADER_HPP
#define RTYPE_DLLOADER_HPP

#include <utility>
#include <string>
#include <vector>
#include <memory>

namespace Sex {
    class DLLoader {
        std::vector<std::pair<std::string, void *>>     _dlHandles;

    public:
        DLLoader() : _dlHandles(0) {};
        ~DLLoader() = default;

        void    dlOpen(std::string const &);
        void    dlClose(std::string const &);
        void    dlCloseAll() noexcept;
        void    *dlSym(std::string const &, std::string const &) const;

    };
}

#endif //RTYPE_DLLOADER_HPP
