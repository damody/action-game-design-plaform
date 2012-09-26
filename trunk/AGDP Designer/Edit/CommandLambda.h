#pragma once

#include "CommandBase.h"
#include <functional>
#include <vector>
#include <iostream>

class CommandLambda : public CommandBase
{
public:
	bool Execute();
	bool Unexecute();
	void AddRedoFunction(std::function<void(void)> func);
	void ClearRedoFunctions();
	void AddUndoFunction(std::function<void(void)> func);
	void ClearUndoFunctions();
private:
	std::vector<std::function<void(void)>> m_RedoFunctions;
	std::vector<std::function<void(void)>> m_UndoFunctions;
};