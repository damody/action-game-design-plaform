#pragma once
#include<vector>
#include<string>

struct Creation
{
	//�гy���󤧦W��
	std::wstring	name;
	//�гy���󤧼ƶq
	int				amount;
	//�гy���󤧦�m
	float			x, y;
	//��ͪ��󤧭��V
	int				facing;
	//�����l frame
	std::wstring	frame;
	//�����l frame �Ǹ�
	int				frameID;
	//�����q
	int				HP;
	//�����t��
	Vector3			v0;
	//ai
};

typedef std::vector<Creation> Creations;