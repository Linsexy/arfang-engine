//
// Created by benito on 1/5/18.
//

#ifndef RTYPE_REGISTERTYPE_HPP
#define RTYPE_REGISTERTYPE_HPP

#include "IndexType.hpp"

namespace utils {
    template <typename... Args>
    struct RegisterType {
        auto getTypes() noexcept
        {
            return (getMany<Args>());
        }
    };
}
#endif //RTYPE_REGISTERTYPE_HPP
