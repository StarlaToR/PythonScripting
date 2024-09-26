#pragma once
#include <IResource.h>
#include <functional>

namespace MultiThreading
{
	typedef std::function<void(Resources::IResource*)> FuntionPointer;

	class Task
	{
	public:
		FuntionPointer Fptr;
		Resources::IResource *resource;
		std::atomic_bool done;

	public:

		Task(FuntionPointer Fptr2, Resources::IResource *b) : Fptr ( Fptr2), resource ( b), done ( false)
		{
			
		}

	};
}


