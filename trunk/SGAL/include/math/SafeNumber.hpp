#pragma once

template <class T>
class SafeNumberImpl
{
private:
	T	m_SafeValue;
	T	m_NowValue;
	T	m_LastValue;
	T	m_LastOperatorValue;
	char	m_LastOperator;
	SafeNumberImpl(T value)
	{
		m_SafeValue = ~value;
		m_NowValue = value;
		m_LastValue = value;
		m_LastOperatorValue = T(0);
		m_LastOperator = '+';
	}

	bool	CheckSafe()
	{
		switch (m_LastOperator)
		{
		case '+':
			if ((m_LastValue + m_LastOperatorValue) == m_NowValue)
			{
				return true;
			}
			break;
		case '-':
			if ((m_LastValue - m_LastOperatorValue) == m_NowValue)
			{
				return true;
			}
			break;
		case '*':
			if ((m_LastValue * m_LastOperatorValue) == m_NowValue)
			{
				return true;
			}
			break;
		case '/':
			if ((m_LastValue / m_LastOperatorValue) == m_NowValue)
			{
				return true;
			}
			break;
		}
		return false;
	}
	T GetSafeValue()
	{
		return ~m_SafeValue;
	}
	SafeNumberImpl<T> operator +(const SafeNumberImpl<T> rhs)
	{
		
	}
};
