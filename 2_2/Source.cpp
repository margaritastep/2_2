#include <iostream>
#include <array>
#include <vector>
#include <deque>
#include <list>
#include <forward_list>
#include <algorithm>
#include <chrono>

class Timer
{
public:
	using clock_t = std::chrono::steady_clock;
	using time_point_t = clock_t::time_point;
	void pause()
	{
		dur = std::chrono::duration_cast <std::chrono::microseconds>(clock_t::now() - m_begin);
		paused = true;
	}
	void cont()
	{
		m_begin = clock_t::now() - dur;
		paused = false;
	}
	Timer() : m_begin(clock_t::now()), dur(std::chrono::duration_cast <std::chrono::microseconds>(clock_t::now() - clock_t::now())), paused(false) {}
	~Timer()
	{
		if (!paused) {
			dur = std::chrono::duration_cast <std::chrono::microseconds>(clock_t::now() - m_begin);
		}
		m_begin = clock_t::now() - dur;
		auto end = clock_t::now();
		std::cout << "microseconds: " << std::chrono::duration_cast <std::chrono::microseconds> (end - m_begin).count() << std::endl;
	}
private:
	time_point_t m_begin;
	std::chrono::microseconds dur;
	bool paused;
};

int main()
{
	std::array <int, 1000> my_array;
	std::vector <int> my_vector(1000);
	std::deque <int> my_deque(1000);
	std::list <int> my_list;
	std::forward_list <int> my_flist(1000);

	for (auto i = 0; i < std::size(my_array); ++i)
	{
		my_array[i] = i;
	}
	for (auto i = 0; i < std::size(my_vector); ++i)
	{
		my_vector[i] = i;
	}
	for (auto i = 0; i < std::size(my_deque); ++i)
	{
		my_deque[i] = i;
	}
	for (auto i = 0; i < 1000; ++i)
	{
		my_list.push_back(i);
	}
	for (auto i = 0; i < 1000; ++i)
	{
		my_flist.push_front(1000 - i);
	}

	std::cout << "std::array(std::sort):   ";
	{
		Timer t1;
		std::sort(std::begin(my_array), std::end(my_array), std::greater <int>());
	}
	std::cout << "std::vector(std::sort):   ";
	{
		Timer t2;
		std::sort(std::begin(my_vector), std::end(my_vector), std::greater <int>());
	}
	std::cout << "std::deque(std::sort):   ";
	{
		Timer t3;
		std::sort(std::begin(my_deque), std::end(my_deque), std::greater <int>());
	}
	std::cout << "std::list:   ";
	{
		Timer t4;
		my_list.sort(std::greater <int>());
	}
	std::cout << "std::forward_list:   ";
	{
		Timer t5;
		my_flist.sort(std::greater <int>());
	}
	std::cout << "leader is std::list";



	return 0;
}