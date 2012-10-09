#include "CommandLambda.h"
#include <exception>

bool CommandLambda::Execute()
{
	try
	{
		for(std::size_t i=0;i<m_RedoFunctions.size();i++)
		{
			m_RedoFunctions[i]();
		}

		return true;
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return false;
	}
}

bool CommandLambda::Unexecute()
{
	try
	{
		//unsigned int size = m_UndoFunctions.size();
		for(std::size_t i=0;i<m_UndoFunctions.size();i++)
		{
			m_UndoFunctions[i]();
		}

		return true;
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return false;
	}
}

void CommandLambda::AddRedoFunction( std::function<void(void)> func )
{
	m_RedoFunctions.push_back(func);
}

void CommandLambda::ClearRedoFunctions()
{
	m_RedoFunctions.clear();
}

void CommandLambda::AddUndoFunction( std::function<void(void)> func )
{
	m_UndoFunctions.push_back(func);
}

void CommandLambda::ClearUndoFunctions()
{
	m_UndoFunctions.clear();
}
