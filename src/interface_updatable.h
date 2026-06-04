#pragma once

namespace interface 
{
	class IUpdatable 
	{
	public:
		virtual ~IUpdatable() = default;
		virtual void update() = 0;
	};
}