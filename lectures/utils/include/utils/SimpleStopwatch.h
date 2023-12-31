#pragma once

#include <ctime>
#include <iostream>

class SimpleStopwatch {
	time_t m_start = 0;
	time_t m_end = 0;

public:
	void start()
	{
		m_end = 0;
		m_start = std::time(NULL);
	}

	void stop()
	{
		m_end = std::time(NULL);
	}

	void printInfo(std::ostream& out) const
	{
		if(m_end == 0)
			out << "[No results to report yet]";
		else
			out << m_end - m_start << " second(s)";
	}

	friend std::ostream& operator<<(std::ostream& out, const SimpleStopwatch& timer)
	{
		timer.printInfo(out);
		return out;
	}
};
