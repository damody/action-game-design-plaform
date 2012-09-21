#pragma once

#include <stack>
#include "CommandManagerBase.h"

class CommandManager : public CommandManagerBase
{
public:
	bool CallCommand( CommandBase* command );
	void ClearCommands();
	void Redo();
	void Undo();
	bool CanRedo();
	bool CanUndo();

protected:
	void PushRedoCommand( CommandBase* command );
	void PushUndoCommand( CommandBase* command );
	CommandBase* PopRedoCommand();
	CommandBase* PopUndoCommand();
	void ClearRedoCommands();
	void ClearUndoCommands();

private:
	std::stack<CommandBase*> m_RedoCommands;
	std::stack<CommandBase*> m_UndoCommands;
};