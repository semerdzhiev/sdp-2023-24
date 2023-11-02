#pragma once

#include <chrono>
#include <iostream>

class Stopwatch {

	using clock = std::chrono::steady_clock;

	clock::time_point m_start;
	clock::time_point m_end;

public:
	void start()
	{
		m_end = clock::time_point(); // set to the clock's epoch (ensures end < start)
		m_start = clock::now();
	}

	void stop()
	{
		m_end = clock::now();
	}

	void printInfo(std::ostream& out) const
	{
		if(m_end < m_start)
			out << "[No results to report yet]";
		else
			out
				<< std::chrono::duration_cast<std::chrono::milliseconds>(m_end - m_start).count()
				<< "ms (~ "
				<< std::chrono::duration_cast<std::chrono::seconds>(m_end - m_start).count()
				<< "s)";
	}

	friend std::ostream& operator<<(std::ostream& out, const Stopwatch& timer)
	{
		timer.printInfo(out);
		return out;
	}
};