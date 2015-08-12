#pragma once

#include "types.h"

#include <functional>
#include <map>
#include <vector>

namespace sam
{
    class func_group
    {
    public:
        typedef int32 id;

        static const id invalid_id = (id) 0;

        typedef std::function<void()> func;

        func_group();

        virtual ~func_group();

        func_group::id add(func &value);

        void remove(id value);

        bool contain(id value);

        void run();

    protected:
        void add_to_group();

        void remove_from_group();

    private:
        id current;
        std::map<id, func> group;
        std::map<id, func> add_cache;
        std::vector<id> remove_cache;
    };
}