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
        using meta = unsigned int;

        static meta _id;

        /* public for technical reasons, nobody should modify it */

        template<typename T>
        static auto get() noexcept {
            static const auto r_id = ++_id;

            return r_id;
        }

        template<typename... Args>
        static auto getMany() noexcept {
            using expander = std::vector<meta>;
            static const auto ret = expander{(get<Args>())...};

            return ret;
        }
    };
}

#endif //RTYPE_INDEXTYPE_HPP
