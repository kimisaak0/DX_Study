#pragma once
#include "stdHeader_L.h"

namespace Lypi
{
#define KeyStateCount 256
#define DataBufferSize 16

	enum push
	{
		p_FREE = 0,
		p_DOWN = 1,
		p_HOLD = 2,
		p_UP = 3,
	};

	struct MouseInfo
	{
		POINT xy;

		push left;
		push right;
		push middle;
	};

	class DxInput
	{
	public:
		LPDIRECTINPUT8 m_pDxInput;
		LPDIRECTINPUTDEVICE8 m_pDxKeypad;
		LPDIRECTINPUTDEVICE8 m_pDxMouse;

		BYTE  m_KeyCurState[KeyStateCount];
		BYTE  m_KeyBefState[KeyStateCount];
		DIMOUSESTATE m_MouseCurState;
		DIMOUSESTATE m_MouseBefState;

		MouseInfo m_MouseState;

	public:
		bool Init();
		bool Frame();
		bool Render();
		bool Release();

		bool ResetDevice();
		bool ResetResource();

	public:
		bool InitDirectInput(bool keypad, bool mouse);
		bool KeyProcess();
		bool MouseProcess();

		void SetAcquire(bool bActive);
		void DeviceAcquire();
		void DeviceUnacquire();

		bool IsKeyDown(DWORD dwKey);
		bool IsKeyUP(DWORD dwKey);
		bool IsKeyDownOnce(DWORD dwKey);

		MouseInfo getMouseInfo();

	public:
		static DxInput& GetInstance();

	protected:
		DxInput();
		virtual ~DxInput();
	};

#define I_Input DxInput::GetInstance()
}