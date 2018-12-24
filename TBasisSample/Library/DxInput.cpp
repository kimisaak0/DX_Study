#include "DxInput.h"

namespace Lypi
{

	DxInput& DxInput::GetInstance()
	{
		static DxInput inst;
		return inst;
	}

	DxInput::DxInput()
	{
		m_pDxInput = nullptr;
		m_pDxKeypad = nullptr;
		m_pDxMouse = nullptr;
	}

	bool DxInput::Init()
	{
		//프로그램 시작시 한번만 초기화 되면 되는 거면 생성자에서,
		//필요할 때 한번씩 초기화 시켜줘야하는 거면 Init에서.
		ZeroMemory(&m_KeyBefState, sizeof(BYTE)*KeyStateCount);
		ZeroMemory(&m_KeyCurState, sizeof(BYTE)*KeyStateCount);

		ZeroMemory(&m_MouseBefState, sizeof(DIMOUSESTATE));
		ZeroMemory(&m_MouseCurState, sizeof(DIMOUSESTATE));

		return true;
	}

	bool DxInput::Frame()
	{
		if (!KeyProcess() || !MouseProcess()) {
			return false;
		}

		return true;
	}

	bool DxInput::Render()
	{

		I_Font.SetAlignment(DWRITE_TEXT_ALIGNMENT_LEADING, DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
		I_Font.SetTextColor(ColorF(1, 0, 0, 1));

		TCHAR pBuffer[256];
		memset(pBuffer, 0, sizeof(TCHAR) * 256);

		int iCount = 0;

		static LONG MousePosX = I_Input.m_MouseCurState.lX;
		static LONG MousePosY = I_Input.m_MouseCurState.lY;
		static LONG MousePosZ = I_Input.m_MouseCurState.lZ;

		MousePosX += I_Input.m_MouseCurState.lX;
		MousePosY += I_Input.m_MouseCurState.lY;
		MousePosZ += I_Input.m_MouseCurState.lZ;

		_stprintf_s(pBuffer, _T("Mouse X:%ld, Y:%ld, Z:%ld"), MousePosX, MousePosY, MousePosZ);

		FLOAT iStartX = 0;
		FLOAT iStartY = (FLOAT)(50 + (20 * iCount));
		I_Font.SetlayoutRt(iStartX, iStartY, (FLOAT)g_rtClient.right, (FLOAT)g_rtClient.bottom);
		I_Font.Drawtxt(pBuffer);
		iCount++;

		for (int iKey = 0; iKey < KeyStateCount; iKey++) {
			if (I_Input.m_KeyCurState[iKey] & 0x80) {
				_stprintf_s(pBuffer, _T("Key State : 0x%02x : %d"), iKey, I_Input.m_KeyCurState[iKey]);
				UINT iStartX = 0;
				UINT iStartY = 50 + (20 * iCount);
				I_Font.SetlayoutRt((FLOAT)iStartX, (FLOAT)iStartY, (FLOAT)g_rtClient.right, (FLOAT)g_rtClient.bottom);
				I_Font.Drawtxt(pBuffer);

				iCount++;
			}
		}

		for (int iKey = 0; iKey < 4; iKey++) {
			if (I_Input.m_MouseCurState.rgbButtons[iKey] & 0x80) {
				_stprintf_s(pBuffer, _T("Mouse Button State : %02d"), iKey);
				UINT iStartX = 0;
				UINT iStartY = 50 + (20 * iCount);
				I_Font.SetlayoutRt((FLOAT)iStartX, (FLOAT)iStartY, (FLOAT)g_rtClient.right, (FLOAT)g_rtClient.bottom);
				I_Font.Drawtxt(pBuffer);

				iCount++;
			}
		}
		return true;
	}

	bool DxInput::Release()
	{
		if (m_pDxInput) {
			if (m_pDxKeypad) {
				m_pDxKeypad->Unacquire();
				m_pDxKeypad->Release();
				m_pDxKeypad = nullptr;
			}

			if (m_pDxMouse) {
				m_pDxMouse->Unacquire();
				m_pDxMouse->Release();
				m_pDxMouse = nullptr;
			}

			m_pDxInput->Release();
			m_pDxInput = nullptr;
		}

		return true;
	}


	bool DxInput::InitDirectInput(bool keypad, bool mouse)
	{
		HRESULT hr;

		if (m_pDxKeypad || m_pDxMouse) {
			return true;
		}

		V_FRETURN(DirectInput8Create(g_hInst, DIRECTINPUT_VERSION, IID_IDirectInput8, (LPVOID*)&m_pDxInput, NULL));

		if (keypad) {
			V_FRETURN(m_pDxInput->CreateDevice(GUID_SysKeyboard, &m_pDxKeypad, NULL));
			V_FRETURN(m_pDxKeypad->SetDataFormat(&c_dfDIKeyboard));

			if (FAILED(hr = m_pDxKeypad->SetCooperativeLevel(g_hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND | DISCL_NOWINKEY))) {
				while (m_pDxKeypad->Acquire() == DIERR_INPUTLOST);

				if (FAILED(m_pDxKeypad->SetCooperativeLevel(g_hWnd, DISCL_EXCLUSIVE | DISCL_BACKGROUND | DISCL_NOWINKEY))) {
					return false;
				}
			}

			while (m_pDxKeypad->Acquire() == DIERR_INPUTLOST);
		}

		if (mouse) {
			V_FRETURN(m_pDxInput->CreateDevice(GUID_SysMouse, &m_pDxMouse, NULL));
			V_FRETURN(m_pDxMouse->SetDataFormat(&c_dfDIMouse));

			if (FAILED(m_pDxMouse->SetCooperativeLevel(g_hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND))) {
				while (m_pDxMouse->Acquire() == DIERR_INPUTLOST);

				if (FAILED(m_pDxMouse->SetCooperativeLevel(g_hWnd, DISCL_EXCLUSIVE | DISCL_FOREGROUND))) {
					return false;
				}
			}

			while (m_pDxMouse->Acquire() == DIERR_INPUTLOST);
		}

		return true;
	}

	void DxInput::DeviceAcquire()
	{
		if (m_pDxKeypad) {
			m_pDxKeypad->Acquire();
		}

		if (m_pDxMouse) {
			m_pDxMouse->Acquire();
		}
	}

	void DxInput::DeviceUnacquire()
	{
		if (m_pDxKeypad) {
			m_pDxKeypad->Unacquire();
		}

		if (m_pDxMouse) {
			m_pDxMouse->Unacquire();
		}
	}

	void DxInput::SetAcquire(bool bActive)
	{
		if (bActive) {
			DeviceAcquire();
		}
		else {
			DeviceUnacquire();
		}
	}

	bool DxInput::KeyProcess()
	{
		memcpy(&m_KeyBefState, &m_KeyCurState, sizeof(BYTE) * KeyStateCount);


		ZeroMemory(m_KeyCurState, sizeof(BYTE)*KeyStateCount);
		if (!m_pDxKeypad) {
			return false;
		}

		if (FAILED(m_pDxKeypad->GetDeviceState(KeyStateCount, m_KeyCurState))) {
			while (m_pDxKeypad->Acquire() == DIERR_INPUTLOST) {
				m_pDxKeypad->Acquire();
			}
			return true;
		}

		return true;
	}

	bool DxInput::MouseProcess()
	{
		memcpy(&m_MouseBefState, &m_MouseCurState, sizeof(DIMOUSESTATE));

		ZeroMemory(&m_MouseCurState, sizeof(DIMOUSESTATE));

		if (!m_pDxMouse) {
			return false;
		}

		if (FAILED(m_pDxMouse->GetDeviceState(sizeof(DIMOUSESTATE), &m_MouseCurState))) {
			while (m_pDxMouse->Acquire() == DIERR_INPUTLOST) {
				m_pDxMouse->Acquire();
			}

			return true;
		}

		return true;
	}

	bool DxInput::ResetDevice()
	{
		Release();
		Init();
		return true;
	}

	bool DxInput::ResetResource()
	{
		return true;
	}

#define KEYDOWN(key)	(((m_KeyCurState[key]) & 0x80) ? true : false)
#define KEYUP(key)		(((m_KeyCurState[key]) & 0x80) ? false : true)

	bool DxInput::IsKeyDown(DWORD dwKey)
	{
		if (KEYDOWN(dwKey)) {
			return true;
		}
		return false;
	}

	bool DxInput::IsKeyUP(DWORD dwKey)
	{
		if (m_KeyBefState[dwKey] & 0x80) {
			if (KEYUP(dwKey)) {
				return true;
			}
		}
		return false;
	}

	bool DxInput::IsKeyDownOnce(DWORD dwKey)
	{
		if (!(m_KeyBefState[dwKey] & 0x80)) {
			if (KEYDOWN(dwKey)) {
				return true;
			}
		}
		return false;
	}

	MouseInfo DxInput::getMouseInfo()
	{
		MouseInfo ret;
		POINT MousePos;

		GetCursorPos(&MousePos);
		ScreenToClient(g_hWnd, &MousePos);

		ret.xy = MousePos;

		ret.xy.x = MousePos.x * g_rtClient.right / (g_rtClient.right + g_rtWindow.left);
		ret.xy.y = MousePos.y * g_rtClient.bottom / (g_rtClient.bottom + g_rtWindow.top);

		for (int iB = 0; iB < 3; iB++)
			if (m_MouseBefState.rgbButtons[iB] & 0x80) {
				if (m_MouseCurState.rgbButtons[iB] & 0x80) {
					switch (iB) {
						case 0: ret.left = p_HOLD;
						case 1: ret.right = p_HOLD;
						case 2: ret.middle = p_HOLD;
					}
				}
				else {
					switch (iB) {
						case 0: ret.left = p_UP;
						case 1: ret.right = p_UP;
						case 2: ret.middle = p_UP;
					}
				}
			}
			else {
				if (m_MouseCurState.rgbButtons[iB] & 0x80) {
					switch (iB) {
						case 0: ret.left = p_DOWN;
						case 1: ret.right = p_DOWN;
						case 2: ret.middle = p_DOWN;
					}
				}
				else {
					switch (iB) {
						case 0: ret.left = p_FREE;
						case 1: ret.right = p_FREE;
						case 2: ret.middle = p_FREE;
					}
				}
			}

			for (int iB = 0; iB < 3; iB++) {
				m_MouseBefState.rgbButtons[iB] = m_MouseCurState.rgbButtons[iB];
			}

			return ret;
	}

	DxInput::~DxInput()
	{
		Release();
	}
}