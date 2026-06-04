#pragma once

namespace abstract {
    template <typename T>
    class Singleton {
    public:
        static auto get() -> T& {
            static T instance;
            return instance;
        }

        Singleton(const Singleton&)                     = delete;
        auto operator=(const Singleton&) -> Singleton&  = delete;
        Singleton(Singleton&&)                          = delete;
        auto operator=(Singleton&&) -> Singleton&       = delete;

    protected:
        Singleton()     = default;
        ~Singleton()    = default;
    };
}