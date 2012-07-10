/*! @brief 處理raw input的類別
可以得到鍵盤的 down up hold press 四個事件
可以得到mouse 三個鍵的 down up hold press
可以得到滑鼠位置與滾輪滾動量
*/

#ifndef INPUTSTATE_H
#define INPUTSTATE_H

#include "GetDirectXInput.h"
#include <queue>
#include <boost/thread/detail/singleton.hpp>

class InputState
{
public:
	enum {
		MOUSE_LEFT,	///< 滑鼠左鍵
		MOUSE_RIGHT,	///< 滑鼠右鍵
		MOUSE_MIDDLE	///< 滑鼠中鍵
	};
	InputState();
	/// 更新輸入訊號
	void GetInput();
	/// 設定輸入端
	void SetDirectXInput(GetDirectXInput *DxInput );
	/// 確認 代碼為index的鍵 是否為按下鍵的瞬間
	bool isKeyDown(int index);
	/// 確認 代碼為index的鍵 是否為放開鍵的瞬間
	bool isKeyUp(int index);
	/// 確認 代碼為index的鍵 是否為按住鍵不放
	bool isKeyHold(int index);
	/// 確認 代碼為index的鍵 是否為按下鍵
	bool isKeyPress(int index);
	/// 確認 滑鼠左鍵 是否為按下鍵的瞬間
	bool isMouseLDown();
	/// 確認 滑鼠右鍵 是否為按下鍵的瞬間
	bool isMouseRDown();
	/// 確認 滑鼠中鍵 是否為按下鍵的瞬間
	bool isMouseMDown();
	/// 確認 滑鼠左鍵 是否為放開鍵的瞬間
	bool isMouseLUp();
	/// 確認 滑鼠右鍵 是否為放開鍵的瞬間
	bool isMouseRUp();
	/// 確認 滑鼠中鍵 是否為放開鍵的瞬間
	bool isMouseMUp();
	/// 確認 滑鼠左鍵 是否為按住鍵不放
	bool isMouseLHold();
	/// 確認 滑鼠右鍵 是否為按住鍵不放
	bool isMouseRHold();
	/// 確認 滑鼠中鍵 是否為按住鍵不放
	bool isMouseMHold();
	/// 確認 滑鼠左鍵 是否為按下鍵
	bool isMouseLPress();
	/// 確認 滑鼠右鍵 是否為按下鍵
	bool isMouseRPress();
	/// 確認 滑鼠中鍵 是否為按下鍵
	bool isMouseMPress();
	/// 得到滑鼠位置
	POINT GetMousePos();
	/// 得到滾輪動量
	int  GetMouseWheel();
	/// 取得所有按下的鍵值
	std::queue<int> GetKeyDownQue();
private:
	char m_NowKeyState[256],m_LastKeyState[256];
	GetDirectXInput *m_lpDxInput;
	MouseInfo m_MouseInfo;
	MouseInfo m_LastMouseInfo;
};
typedef boost::detail::thread::singleton<InputState> InputStateS; // InputStateS
#endif //INPUTSTATE_H
