#pragma once
#include <SDL3/SDL.h>

namespace rgp {
	class IEventHandlable {
	public:
		virtual ~IEventHandlable() = default;
		virtual void handleEvent(SDL_Event* event) = 0;
	};
}