//
// Created by benito on 1/4/18.
//

#ifndef RTYPE_INDEXTYPE_HPP
#define RTYPE_INDEXTYPE_HPP

#include <cstdio>
#include <utility>
#include <iostream>
#include <vector>

struct IndexType
{
    static unsigned int _id;
    /* public for technical reasons, nobody should modify it */

    template <typename T>
    static auto get()
    {
        static auto r_id = ++_id;

        return r_id;
    }

    template <typename T, typename U, typename... Args>
    static auto get()
    {
        //get<Args>(...);
        using expander = std::vector<unsigned int>;
        //(void) expander{ 0, (get(Args))... };

        std::vector<unsigned int> ret = expander{ 0, (get<Args>())... };
        return ret;
    }
};

#endif //RTYPE_INDEXTYPE_HPP
