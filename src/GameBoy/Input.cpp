#include "Input.h"
#include <Windows.h>
#include <WinUser.h>

void InputHandler::GetInputState(EmulatorInputs::InputState& state)
{
	if (GetKeyState('W') & 0x8000)
	{
		state.SetButtonDown(EmulatorInputs::DPad::Up);
	}
	if (GetKeyState('A') & 0x8000)
	{
		state.SetButtonDown(EmulatorInputs::DPad::Left);
	}
	if (GetKeyState('S') & 0x8000)
	{
		state.SetButtonDown(EmulatorInputs::DPad::Down);
	}
	if (GetKeyState('D') & 0x8000)
	{
		state.SetButtonDown(EmulatorInputs::DPad::Right);
	}

	if (GetKeyState('N') & 0x8000)
	{
		state.SetButtonDown(EmulatorInputs::Buttons::A);
	}
	if (GetKeyState('M') & 0x8000)
	{
		state.SetButtonDown(EmulatorInputs::Buttons::B);
	}
	if (GetKeyState('K') & 0x8000)
	{
		state.SetButtonDown(EmulatorInputs::Buttons::Start);
	}
	if (GetKeyState('L') & 0x8000)
	{
		state.SetButtonDown(EmulatorInputs::Buttons::Select);
	}
}
