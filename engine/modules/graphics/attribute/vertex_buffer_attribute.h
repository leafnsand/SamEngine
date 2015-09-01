#pragma once

#include "graphics/core/define.h"
#include "graphics/core/vertex_layout.h"

namespace sam
{
    class vertex_buffer_attribute
    {
    public:
        int32 count{ 0 };

        vertex_layout layout;

        resource_usage usage{ resource_usage::invalid };

        int32 size() const;
    };

    inline int32 vertex_buffer_attribute::size() const
    {
        return count * layout.size();
    }
}