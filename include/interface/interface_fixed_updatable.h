#pragma once

namespace rgp {
    class IFixedUpdatable {
    public:
        virtual ~IFixedUpdatable() = default;
        virtual void fixedUpdate(float fixedDt) = 0;
    };
}