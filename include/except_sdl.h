#pragma once
#include <stdexcept>
#include <SDL3/SDL_error.h>

namespace rgp {
    class SDLException final : public std::runtime_error {
    public:
        explicit SDLException(const std::string& message) : runtime_error(message + " | " + std::string(SDL_GetError())) {}
    };
}
