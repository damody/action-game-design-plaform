/*! @brief �B�zraw input�����O
�i�H�o����L�� down up hold press �|�Өƥ�
�i�H�o��mouse �T���䪺 down up hold press
�i�H�o��ƹ���m�P�u���u�ʶq
*/

#pragma once

#include "GetDirectXInput.h"
#include <queue>
#include <boost/thread/detail/singleton.hpp>

class InputState
{
public:
	enum
	{
	        MOUSE_LEFT,	///< �ƹ�����
	        MOUSE_RIGHT,	///< �ƹ��k��
	        MOUSE_MIDDLE	///< �ƹ�����
	};
	InputState();
	~InputState();
	/// ��s��J�T��
	void GetInput();
	/// �]�w��J��
	int InputInit( HWND hWnd, HINSTANCE Instance );
	/// �T�{ �N�X��index���� �O�_�����U�䪺����
	bool isKeyDown( int index );
	/// �T�{ �N�X��index���� �O�_����}�䪺����
	bool isKeyUp( int index );
	/// �T�{ �N�X��index���� �O�_�������䤣��
	bool isKeyHold( int index );
	/// �T�{ �N�X��index���� �O�_�����U��
	bool isKeyPress( int index );
	/// �T�{ �ƹ����� �O�_�����U�䪺����
	bool isMouseLDown();
	/// �T�{ �ƹ��k�� �O�_�����U�䪺����
	bool isMouseRDown();
	/// �T�{ �ƹ����� �O�_�����U�䪺����
	bool isMouseMDown();
	/// �T�{ �ƹ����� �O�_����}�䪺����
	bool isMouseLUp();
	/// �T�{ �ƹ��k�� �O�_����}�䪺����
	bool isMouseRUp();
	/// �T�{ �ƹ����� �O�_����}�䪺����
	bool isMouseMUp();
	/// �T�{ �ƹ����� �O�_�������䤣��
	bool isMouseLHold();
	/// �T�{ �ƹ��k�� �O�_�������䤣��
	bool isMouseRHold();
	/// �T�{ �ƹ����� �O�_�������䤣��
	bool isMouseMHold();
	/// �T�{ �ƹ����� �O�_�����U��
	bool isMouseLPress();
	/// �T�{ �ƹ��k�� �O�_�����U��
	bool isMouseRPress();
	/// �T�{ �ƹ����� �O�_�����U��
	bool isMouseMPress();
	/// �o��ƹ���m
	POINT GetMousePos();
	/// �o��u���ʶq
	int  GetMouseWheel();
	/// ���o�Ҧ����U�����
	std::queue<int> GetKeyDownQue();
private:
	char m_NowKeyState[256], m_LastKeyState[256];
	GetDirectXInput* m_lpDxInput;
	MouseInfo m_MouseInfo;
	MouseInfo m_LastMouseInfo;
};
typedef boost::detail::thread::singleton<InputState> InputStateS; // InputStateS
