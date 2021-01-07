#pragma once

namespace Ass02_pong
{
	class State
	{
	public:
		virtual void Init() = 0;
		virtual void HandleInput() = 0;
		virtual void Update(float dT) = 0;
		virtual void Render(float dT) = 0;
	
		virtual void Pause() {}
		virtual void Resume() {}
	};
}