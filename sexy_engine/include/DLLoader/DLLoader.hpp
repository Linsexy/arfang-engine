//
// Created by mymy on 04/01/18.
//

#ifndef RTYPE_DLLOADER_HPP
#define RTYPE_DLLOADER_HPP

#include <utility>
#include <string>

namespace Sex {
    class DLLoader {
        std::pair<std::string, void *>     dlHandles;

    public:
        DLLoader() = default;
        ~DLLoader() = default;

        void    dlOpen(std::string const &);

    };
}

#endif //RTYPE_DLLOADER_HPP
