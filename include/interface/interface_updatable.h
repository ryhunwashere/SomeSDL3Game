#pragma once

namespace rgp {
	class IUpdatable {
	public:
		virtual ~IUpdatable() = default;
		virtual void update(float dt) = 0;
	};
}