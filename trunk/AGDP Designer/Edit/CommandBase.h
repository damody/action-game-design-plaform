#pragma once

class CommandBase
{
public:
	virtual bool Execute() = 0;
	virtual bool Unexecute() = 0;
};