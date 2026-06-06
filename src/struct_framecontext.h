#pragma once
#include <vector>
#include <memory>

namespace rgp {
    class IUpdatable;
    class IDrawable;

	struct FrameContext {
        std::vector<std::shared_ptr<IUpdatable>>& updatables;
        std::vector<std::shared_ptr<IDrawable>>& drawables;
	};
}