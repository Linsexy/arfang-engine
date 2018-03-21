//
// Created by benito on 1/16/18.
//

#ifndef RTYPE_NAMMED_HPP
#define RTYPE_NAMMED_HPP

#include <string>

namespace utils {
    template<typename T>
    struct Named {
        Named(const std::string &n)
        {
            name = n;
        }

        static std::string name;
    };
}

template <typename T>
std::string utils::Named<T>::name = "";

namespace utils {
    template<typename T>
    struct is_named {
        static const bool value = std::is_base_of<Named<T>, T>::value;
    };
}

#endif //RTYPE_NAMMED_HPP
