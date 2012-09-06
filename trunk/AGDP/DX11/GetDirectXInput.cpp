#include "StdGame.h"
#include "GetDirectXInput.h"

#define SAFE_RELEASE(x) if (x) { x->Release(); x=NULL; }
#define RELEASE_ARRAY(x) if (x) { delete [] x; x=NULL; }

LPDIRECTINPUT8 GetDirectXInput::m_pDI;
LPDIRECTINPUTDEVICE8 GetDirectXInput::m_pMouse;
LPDIRECTINPUTDEVICE8 GetDirectXInput::m_pKeyboard;
LPDIRECTINPUTDEVICE8 GetDirectXInput::m_pJoystick;
POINT GetDirectXInput::m_op;
POINT GetDirectXInput::m_mouse;
KeyHandlerProc GetDirectXInput::m_pKeyDownFuncs[256];
KeyHandlerProc GetDirectXInput::m_pKeyUpFuncs[256];
KeyHandlerProc GetDirectXInput::m_pKeyPressedFuncs[256];
char GetDirectXInput::m_keyboard_state[256];


int GetDirectXInput::InputRestore( void )
{
	if ( m_pMouse ) { m_pMouse->Acquire(); }

	if ( m_pJoystick ) { m_pJoystick->Acquire(); }

	if ( m_pKeyboard ) { m_pKeyboard->Acquire(); }

	return 1;
}

int GetDirectXInput::InputInit( HWND hWnd, HINSTANCE Instance )
{
	m_hWnd = hWnd;
	m_Instance = Instance;
	memset( m_pKeyDownFuncs, 0, sizeof( m_pKeyDownFuncs ) );
	memset( m_pKeyUpFuncs, 0, sizeof( m_pKeyUpFuncs ) );
	memset( m_pKeyPressedFuncs, 0, sizeof( m_pKeyPressedFuncs ) );
	int hr;
	hr = DirectInput8Create( m_Instance, DIRECTINPUT_VERSION, IID_IDirectInput8, ( void** )&m_pDI, NULL );

	if ( FAILED( hr ) )
	{
		return false;
	}

	// create keyboard device
	hr = m_pDI->CreateDevice( GUID_SysKeyboard, &m_pKeyboard, NULL );

	if ( FAILED( hr ) )
	{
		return false;
	}

	if ( m_pKeyboard )
	{
		m_pKeyboard->SetCooperativeLevel( hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE );
		m_pKeyboard->SetDataFormat( &c_dfDIKeyboard );
		m_pKeyboard->Acquire();
	}

	// create mouse device
	hr = m_pDI->CreateDevice( GUID_SysMouse, &m_pMouse, NULL );

	if ( FAILED( hr ) )
	{
		return false;
	}

	if ( m_pMouse )
	{
		m_pMouse->SetCooperativeLevel( hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE );
		m_pMouse->SetDataFormat( &c_dfDIMouse2 );
		m_pMouse->Acquire();
	}

	GetCursorPos( &m_op );
	ScreenToClient( hWnd, &m_op );
	m_mouse = m_op;
	// create joystick device
	hr = m_pDI->EnumDevices( DI8DEVCLASS_GAMECTRL, &GetDirectXInput::EnumJoysticksCallback, NULL, DIEDFL_ATTACHEDONLY );

	if ( FAILED( hr ) )
	{
		return false;
	}

	if ( m_pJoystick )
	{
		m_pJoystick->SetCooperativeLevel( hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE );
		m_pJoystick->SetDataFormat( &c_dfDIJoystick );
		m_pJoystick->Acquire();
	}

	return 1;
}

int GetDirectXInput::InputClose( void )
{
	if ( m_pMouse )	{ m_pMouse->Unacquire(); }

	if ( m_pKeyboard ) { m_pKeyboard->Unacquire(); }

	if ( m_pJoystick ) { m_pJoystick->Unacquire(); }

	SAFE_RELEASE( m_pMouse );
	SAFE_RELEASE( m_pKeyboard );
	SAFE_RELEASE( m_pJoystick );
	return 1;
}

int GetDirectXInput::ReadMouse( MouseInfo* info )
{
	if ( NULL == m_pMouse )
	{
		return false;
	}

	// DirectInput mouse state structure
	DIMOUSESTATE2 dims2;
	// Get the input's device state, and put the state in dims
	ZeroMemory( &dims2, sizeof( dims2 ) );
	int hr = m_pMouse->GetDeviceState( sizeof( DIMOUSESTATE2 ), &dims2 );

	if ( FAILED( hr ) )
	{
		m_pMouse->Acquire();
		m_pMouse->GetDeviceState( sizeof( DIMOUSESTATE2 ), &dims2 );
	}

	info->x = dims2.lX;
	info->y = dims2.lY;
	info->z = dims2.lZ;
	m_mouse.x += info->x;
	m_mouse.y += info->y;
	info->button[0] = dims2.rgbButtons[0] & 0x80 ? 1 : 0;
	info->button[1] = dims2.rgbButtons[1] & 0x80 ? 1 : 0;
	info->button[2] = dims2.rgbButtons[2] & 0x80 ? 1 : 0;
	return 1;
}

int GetDirectXInput::ReadKeyboard( char buffer[256] )
{
	if ( NULL == m_pKeyboard )
	{
		return false;
	}

	int hr = m_pKeyboard->GetDeviceState( 256, buffer );

	if ( FAILED( hr ) )
	{
		hr = m_pKeyboard->Acquire();

		for ( int i = 0; hr == DIERR_INPUTLOST && i < 10; i++ )
		{
			hr = m_pKeyboard->Acquire();

			if ( !FAILED( hr ) ) { break; }
		}

		memset( buffer, 0, 256 );
		return false;
	}

	return 1;
}

void GetDirectXInput::ReadKeyboard( void )
{
	char keyboard[256];
	ReadKeyboard( keyboard );

	for ( int i = 0; i < 256; i++ )
	{
		// key down
		if ( keyboard[i] && !m_keyboard_state[i] )
		{
			if ( m_pKeyDownFuncs[i] ) { m_pKeyDownFuncs[i](); }
		}
		else if ( !keyboard[i] && m_keyboard_state[i] ) // key up
		{
			if ( m_pKeyUpFuncs[i] ) { m_pKeyUpFuncs[i](); }
		}
		else if ( keyboard[i] ) // key pressed
		{
			if ( m_pKeyPressedFuncs[i] ) { m_pKeyPressedFuncs[i](); }
		}
	}

	memcpy( m_keyboard_state, keyboard, sizeof( keyboard ) );
}

int GetDirectXInput::ReadJoystick( JoystickInfo* joystick )
{
	DIJOYSTATE js;

	if ( m_pJoystick == NULL || joystick == NULL )
	{
		return false;
	}

	// Poll the device to read the current state
	int hr = m_pJoystick->Poll();

	if ( FAILED( hr ) )
	{
		m_pJoystick->Acquire();
		m_pJoystick->Poll();
	}

	// Get the input's device state
	hr = m_pJoystick->GetDeviceState( sizeof( DIJOYSTATE ), &js );

	if ( hr == DIERR_INPUTLOST )
	{
		// DInput is telling us that the input stream has been
		// interrupted. We aren't tracking any state between polls, so
		// we don't have any special reset that needs to be done. We
		// just re-acquire and try again.
		hr = m_pJoystick->Acquire();

		if ( FAILED( hr ) )
		{
			return false;
		}
	}

	joystick->x = js.lX;
	joystick->y = js.lY;
	joystick->z = js.lZ;
	joystick->rx = js.lRx;
	joystick->ry = js.lRy;
	joystick->rz = js.lRz;
	joystick->pov[0] = js.rgdwPOV[0];
	joystick->pov[1] = js.rgdwPOV[1];
	joystick->pov[2] = js.rgdwPOV[2];
	joystick->pov[3] = js.rgdwPOV[3];
	memcpy( joystick->button, js.rgbButtons, 32 );
	return 1;
}

void GetDirectXInput::RegisterKeyDown( int key, void ( *pKeyDownFunc )( void ) )
{
	m_pKeyDownFuncs[key] = pKeyDownFunc;
}

void GetDirectXInput::RegisterKeyUp  ( int key, void ( *pKeyDownUp )( void ) )
{
	m_pKeyUpFuncs[key] = pKeyDownUp;
}

void GetDirectXInput::RegisterKeyPressed( int key, void ( *pKeyPressed )( void ) )
{
	m_pKeyPressedFuncs[key] = pKeyPressed;
}


