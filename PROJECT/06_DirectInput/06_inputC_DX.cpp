#include "06_inputC_DX.h"


input_DX& input_DX::GetInstance()
{
	static input_DX inst;
	return inst;
}

input_DX* input_DX::GetInstancePtr()
{
	static input_DX inst;
	return &inst;
}


input_DX::input_DX()
{
	m_pDxInput = nullptr;
	m_pDxKeypad = nullptr;
	m_pDxMouse = nullptr;

	m_dwElemts = 0;
	m_bImmediate = true;
}

bool input_DX::Init()
{

	//프로그램 시작시 한번만 초기화 되면 되는 거면 생성자에서,
	//필요할 때 한번씩 초기화 시켜줘야하는 거면 Init에서.
	ZeroMemory(&m_KeyBefState, sizeof(BYTE)*KeyStateCount);
	ZeroMemory(&m_KeyCurState, sizeof(BYTE)*KeyStateCount);

	ZeroMemory(&m_MouseBefState, sizeof(DIMOUSESTATE));
	ZeroMemory(&m_MouseCurState, sizeof(DIMOUSESTATE));

	return true;
}

bool input_DX::Frame()
{
	if (!KeyProcess() || !MouseProcess()) {
		return false;
	}

	return true;
}

bool input_DX::Render()
{
	return true;
}

bool input_DX::Release()
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


bool input_DX::InitDirectInput(bool keypad, bool mouse)
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

		if (!m_bImmediate) {
			DIPROPDWORD dipdw;
			dipdw.diph.dwSize = sizeof(DIPROPDWORD);
			dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
			dipdw.diph.dwObj = 0;
			dipdw.diph.dwHow = DIPH_DEVICE;
			dipdw.dwData = DataBufferSize;

			if (FAILED(hr = m_pDxKeypad->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph))) {
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

void input_DX::DeviceAcquire()
{
	if (m_pDxKeypad) {
		m_pDxKeypad->Acquire();
	}

	if (m_pDxMouse) {
		m_pDxMouse->Acquire();
	}
}

void input_DX::DeviceUnacquire()
{
	if (m_pDxKeypad) {
		m_pDxKeypad->Unacquire();
	}

	if (m_pDxMouse) {
		m_pDxMouse->Unacquire();
	}
}

void input_DX::SetAcquire(bool bActive)
{
	if (bActive) {
		DeviceAcquire();
	}
	else {
		DeviceUnacquire();
	}
}

void input_DX::PostProcess()
{
	memcpy(&m_KeyBefState, &m_KeyCurState, sizeof(BYTE) * KeyStateCount);
	memcpy(&m_MouseBefState, &m_MouseCurState, sizeof(DIMOUSESTATE));
}

bool input_DX::KeyProcess()
{
	HRESULT hr;
	
	if (m_bImmediate) {
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
	}
	else {
		if (m_pDxKeypad == nullptr) {
			return false;
		}
		
		ZeroMemory(&m_sDidod, sizeof(DIDEVICEOBJECTDATA)*DataBufferSize);

		m_dwElemts = DataBufferSize;
		
		hr = m_pDxKeypad->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), m_sDidod, &m_dwElemts, 0);

		if (hr != DI_OK) {
			m_dwElemts = 0;
			hr = m_pDxKeypad->Acquire();
			while (hr == DIERR_INPUTLOST) {
				hr = m_pDxKeypad->Acquire();
			}

			return true;
		}
	}

	return true;
}

bool input_DX::MouseProcess()
{
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

bool input_DX::ResetDevice()
{
	Release();
	Init();
	return true;
}

bool input_DX::ResetResource()
{
	return true;
}


//TODO : 필요할 때 다시 제대로 만들 것.
#define KEYDOWN(key)	(((m_KeyCurState[key]) & 0x80) ? true : false)
#define KEYUP(key)		(((m_KeyCurState[key]) & 0x80) ? false : true)

bool input_DX::IsKeyDown(DWORD dwKey)
{
	if (m_bImmediate) {
		if (KEYDOWN(dwKey)) {
			return true;
		}
	}
	else {
		for (DWORD i = 0; i < m_dwElemts; i++) {
			if (m_sDidod[i].dwOfs == dwKey && (m_sDidod[i].dwData & 0x80)) {
				return true;
			}
		}
	}

	return false;
}

bool input_DX::IsKeyUP(DWORD dwKey)
{
	if (m_bImmediate) {
		if (m_KeyBefState[dwKey] & 0x80) {
			if (KEYUP(dwKey)) {
				return true;
			}
		}
	}
	else {
		for (DWORD i = 0; i < m_dwElemts; i++) {
			if (m_sDidod[i].dwOfs == dwKey && !(m_sDidod[i].dwData & 0x80)) {
				return true;
			}
		}
	}

	return false;
}

input_DX::~input_DX()
{
	Release();
}