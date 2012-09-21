#pragma once

#include "CommandBase.h"

class CommandManagerBase
{
public:
	virtual bool CallCommand( CommandBase* command ) = 0;
	virtual void ClearCommands() = 0;
	virtual void Redo() = 0;
	virtual void Undo() = 0;
	virtual bool CanUndo() = 0;
	virtual bool CanRedo() = 0;
};