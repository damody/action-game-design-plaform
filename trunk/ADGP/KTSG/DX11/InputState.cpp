#include "stdafx.h"
#include "InputState.h"

InputState::InputState()
{
	memset(m_NowKeyState,0,sizeof(m_NowKeyState));
	memset(m_LastKeyState,0,sizeof(m_LastKeyState));
	memset(&m_MouseInfo,0,sizeof(m_MouseInfo));
	memset(&m_LastMouseInfo,0,sizeof(m_LastMouseInfo));
}

bool InputState::isKeyDown( int index )
{
	if ( m_NowKeyState[index] && !m_LastKeyState[index] ) // key down
		return true;
	return false;
}

bool InputState::isKeyUp( int index )
{
	if ( !m_NowKeyState[index] && m_LastKeyState[index] ) // key up
		return true;
	return false;
}

bool InputState::isKeyHold( int index )
{
	if ( m_NowKeyState[index] && m_LastKeyState[index] ) // key hold
		return true;
	return false;
}

bool InputState::isKeyPress( int index )
{
	if ( m_NowKeyState[index] ) // key pressed
		return true;
	return false;
}

void InputState::GetInput()
{
	memcpy(m_LastKeyState, m_NowKeyState, sizeof(m_LastKeyState));
	m_lpDxInput->ReadKeyboard(m_NowKeyState);
	memcpy(&m_LastMouseInfo, &m_MouseInfo, sizeof(m_MouseInfo));
	m_lpDxInput->ReadMouse(&m_MouseInfo);
}

void InputState::SetDirectXInput( GetDirectXInput *DxInput )
{
	m_lpDxInput = DxInput;
}

bool InputState::isMouseLDown()
{
	if ( m_MouseInfo.button[MOUSE_LEFT] && !m_LastMouseInfo.button[MOUSE_LEFT] ) 
		return true;
	return false;
}

bool InputState::isMouseRDown()
{
	if ( m_MouseInfo.button[MOUSE_RIGHT] && !m_LastMouseInfo.button[MOUSE_RIGHT] ) 
		return true;
	return false;
}

bool InputState::isMouseMDown()
{
	if ( m_MouseInfo.button[MOUSE_MIDDLE] && !m_LastMouseInfo.button[MOUSE_MIDDLE] ) 
		return true;
	return false;
}

bool InputState::isMouseLUp()
{
	if ( !m_MouseInfo.button[MOUSE_LEFT] && m_LastMouseInfo.button[MOUSE_LEFT] ) 
		return true;
	return false;
}

bool InputState::isMouseRUp()
{
	if ( !m_MouseInfo.button[MOUSE_RIGHT] && m_LastMouseInfo.button[MOUSE_RIGHT] ) 
		return true;
	return false;
}

bool InputState::isMouseMUp()
{
	if ( !m_MouseInfo.button[MOUSE_MIDDLE] && m_LastMouseInfo.button[MOUSE_MIDDLE] ) 
		return true;
	return false;
}

bool InputState::isMouseLHold()
{
	if ( m_MouseInfo.button[MOUSE_LEFT] && m_LastMouseInfo.button[MOUSE_LEFT] ) 
		return true;
	return false;
}

bool InputState::isMouseRHold()
{
	if ( m_MouseInfo.button[MOUSE_RIGHT] && m_LastMouseInfo.button[MOUSE_RIGHT] ) 
		return true;
	return false;
}

bool InputState::isMouseMHold()
{
	if ( m_MouseInfo.button[MOUSE_MIDDLE] && m_LastMouseInfo.button[MOUSE_MIDDLE] ) 
		return true;
	return false;
}

bool InputState::isMouseLPress()
{
	if ( m_MouseInfo.button[MOUSE_LEFT] )
		return true;
	return false;
}

bool InputState::isMouseRPress()
{
	if ( m_MouseInfo.button[MOUSE_RIGHT] )
		return true;
	return false;
}

bool InputState::isMouseMPress()
{
	if ( m_MouseInfo.button[MOUSE_MIDDLE] )
		return true;
	return false;
}

POINT InputState::GetMousePos()
{
	POINT pos, leftup;
	RECT rcClient;
	GetCursorPos(&pos);
	GetClientRect(m_lpDxInput->m_hWnd, &rcClient); 
	leftup.x=rcClient.left;
	leftup.y=rcClient.top;
	ClientToScreen(m_lpDxInput->m_hWnd, &leftup);
	pos.x = pos.x - leftup.x;
	pos.y = pos.y - leftup.y;
	return pos;
}

int InputState::GetMouseWheel()
{
	return m_MouseInfo.z;
}
