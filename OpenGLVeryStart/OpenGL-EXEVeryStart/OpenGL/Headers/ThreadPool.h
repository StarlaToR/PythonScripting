#pragma once
#include <vector>
#include <thread>
#include <IResource.h>
#include <Task.h>
#include <Mutex.h>

namespace MultiThreading
{	
	class ThreadPool
	{
	public:

		std::atomic_bool done = false;
		MultiThreading::MyMutex m;
		std::vector<std::thread*> threads;
		std::vector<Task*> listTask;
		int NumbrThread = 10;
		int i = 0;

		void createThread()
		{
			for (int j = 0; j < NumbrThread; j++)
			{
				threads.push_back(new std::thread(&ThreadPool::LifeThread, this));
			}
		}

		ThreadPool()
		{
			createThread();
		}

		void LifeThread()
		{
			while (!done)
			{
				bool stop = false;
				Task* t = nullptr;

				m.Lock();
				if (listTask.size() != 0 && !listTask[0]->done)
				{
					t = listTask.back();
					listTask.pop_back();
					t->done = true;
					stop = true;
				}		
				m.Unlock();

				if (t != nullptr)
				{
					t->Fptr(t->resource);
					t = nullptr;
				}
			}
		}

		~ThreadPool()
		{
			done = true;
		}

	};
}
