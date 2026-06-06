#pragma once

namespace rgp {
	class IDrawable {
	public:
		virtual ~IDrawable() = default;
		virtual void draw() = 0;
	};
}