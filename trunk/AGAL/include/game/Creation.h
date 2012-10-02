#pragma once
#include<vector>
#include<string>

struct Creation
{
	//創造物件之名稱
	std::wstring	name;
	//創造物件之數量
	int				amount;
	//創造物件之位置
	float			x, y;
	//初生物件之面向
	int				facing;
	//物件初始 frame
	std::wstring	frame;
	//物件初始 frame 序號
	int				frameID;
	//物件血量
	int				HP;
	//物件初速度
	Vector3			v0;
	//ai
};

typedef std::vector<Creation> Creations;