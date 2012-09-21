#include "CommandManager.h"

bool CommandManager::CallCommand( CommandBase* command )
{
	if( command )
	{
		if( command->Execute() )
		{
			PushUndoCommand( command );
			ClearRedoCommands();
			return true;
		}
		else
		{
			delete command;
		}
	}

	return false;
}

void CommandManager::ClearCommands()
{
	ClearRedoCommands();
	ClearUndoCommands();
}

void CommandManager::Redo()
{
	CommandBase* command = PopRedoCommand();

	if( command )
	{
		if( command->Execute() )
		{
			PushUndoCommand( command );
		}
		else
		{
			delete command;
		}
	}
}

void CommandManager::Undo()
{
	CommandBase* command = PopUndoCommand();

	if( command )
	{
		if( command->Unexecute() )
		{
			PushRedoCommand( command );
		}
		else
		{
			delete command;
		}
	}
}

bool CommandManager::CanRedo()
{
	return !m_RedoCommands.empty();
}

bool CommandManager::CanUndo()
{
	return !m_UndoCommands.empty();
}

void CommandManager::PushRedoCommand( CommandBase* command )
{
	if( command )
		m_RedoCommands.push( command );
}

void CommandManager::PushUndoCommand( CommandBase* command )
{
	if( command )
		m_UndoCommands.push( command );
}

CommandBase* CommandManager::PopRedoCommand()
{
	CommandBase* command = NULL;
	if( !m_RedoCommands.empty() )
	{
		command = m_RedoCommands.top();
		m_RedoCommands.pop();
	}
	return command;
}

CommandBase* CommandManager::PopUndoCommand()
{
	CommandBase* command = NULL;
	if( !m_UndoCommands.empty() )
	{
		command = m_UndoCommands.top();
		m_UndoCommands.pop();
	}
	return command;
}

void CommandManager::ClearRedoCommands()
{
	while( !m_RedoCommands.empty() )
	{
		delete m_RedoCommands.top();
		m_RedoCommands.pop();
	}
}

void CommandManager::ClearUndoCommands()
{
	while( !m_UndoCommands.empty() )
	{
		delete m_UndoCommands.top();
		m_UndoCommands.pop();
	}
}

