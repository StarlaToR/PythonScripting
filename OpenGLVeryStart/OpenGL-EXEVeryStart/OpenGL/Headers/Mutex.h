#pragma once
#include <atomic>
#include <thread>


namespace MultiThreading
{
	class MyMutex
	{
	public:
		std::atomic_flag flg = ATOMIC_FLAG_INIT;

		void Lock()
		{
			while (flg.test_and_set(std::memory_order_acquire));
		}

		void Unlock()
		{
			flg.clear(std::memory_order_release);
		}

	};
}
