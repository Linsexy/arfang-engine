//
// Created by benito on 1/4/18.
//

#ifndef RTYPE_INDEXTYPE_HPP
#define RTYPE_INDEXTYPE_HPP

#include <cstdio>
#include <utility>
#include <iostream>
#include <vector>

namespace utils {
    struct IndexType {
        static unsigned int _id;

        /* public for technical reasons, nobody should modify it */

        template<typename T>
        static auto get() noexcept {
            static const auto r_id = ++_id;

            return r_id;
        }

        template<typename... Args>
        static auto getMany() noexcept {
            using expander = std::vector<unsigned int>;

            static const auto ret = expander{0, (get<Args>())...};
            static const std::vector<unsigned int> rret(ret.begin() + 1, ret.end());

            /* need to change to fit well with c++17 */
            return rret;
        }
    };
}

#endif //RTYPE_INDEXTYPE_HPP
