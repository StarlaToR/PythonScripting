#pragma once
#include <iostream>
#include <IResource.h>
#include <unordered_map>
#include <thread>
#include <Model.h>
#include <Texture.h>
#include <ThreadPool.h>

using namespace std;

namespace Resources
{
	class ResourceManager
	{
	private:
		unordered_map<string, IResource*> mResources = {};

		enum LoadingMode
		{
			MonoThread,
			MultiThread,
			ThreadPool,
		};

		LoadingMode mode;

	public:
		MultiThreading::ThreadPool pool;

		ResourceManager(){}

		template <typename T>

		void Create(const string& path, const string& name)
		{
			T* resource = new T();
			resource->setResourcePath(path);
			resource->setResourceId(mResources.size());

			if (mode == MultiThread)
			{
				std::thread t(&IResource::loadResource, resource);
				t.detach();
			}
			else if (mode == ThreadPool)
			{				
				pool.listTask.push_back(new MultiThreading::Task(bind(&IResource::loadResource, resource), resource));
			}
			else
			{
				resource->loadResource();
			}

			mResources.insert(pair<string, IResource*>(name, (IResource*)resource));
		}

		void Add(IResource* resource, const string& name)
		{
			resource->setResourceId(mResources.size());
			//resource->loadResource();
			mResources.insert(pair<string, IResource*>(name, resource));
		}
		
		template <typename T>
		T* Get(const string& name)
		{
			auto itr = mResources.find(name);
			if (itr != mResources.end())
				return dynamic_cast<T*>(itr->second);
			else
			{
				cout << "can't get the texture" << endl;
				return nullptr;
			}
		}

		void Delete(const string& path)
		{
			mResources.erase(path);
		}

		void Clear()
		{
			mResources.clear();
			//mResources.empty();
			pool.done = true;
		}

		void MenuConsole()
		{
			std::cout << "choose your Loading Mode \n";
			std::cout << "0. MonoThread \n1. MultiThread \n2. ThreadPool \n";
			int choise;
			std::cin >> choise;

			switch (choise)
			{
				case 0:
					mode = MonoThread;
					break;
				case 1:
					mode = MultiThread;
					break;
				case 2:
					mode = ThreadPool;
					break;
			}
		}

		void Init()
		{	
			pool.done = false;
			if (mode == MultiThread)
				std::cout << "Simple MultiThread" << std::endl;
			else if (mode == ThreadPool)
				std::cout << "MultiThread with ThreadPool" << std::endl;
			else
				std::cout << "MonoThread" << std::endl;

			Create<Model>("Resources/Obj/cube.obj", "cube");
			Create<Model>("Resources/Obj/khazix.obj", "khazix");
			Create<Model>("Resources/Obj/Azir.obj", "azir");
			Create<Model>("Resources/Obj/GanondorfPast.obj", "GanondorfPast");
			Create<Model>("Resources/Obj/AMF.obj", "MF");
			Create<Model>("Resources/Obj/Garen.obj", "garen");
			Create<Model>("Resources/Obj/Darius.obj", "darius");
			Create<Texture>("Resources/Textures/khaz.png", "khazText");
			Create<Texture>("Resources/Textures/Azir.png", "azirText");
			Create<Texture>("Resources/Textures/sample.png", "catText");
			Create<Texture>("Resources/Textures/sample2.png", "dogText");
			Create<Texture>("Resources/Textures/ganondorf.png", "ganondorfText");
			Create<Texture>("Resources/Textures/missF.png", "missText");
			Create<Texture>("Resources/Textures/garen.png", "garenText");
			Create<Texture>("Resources/Textures/DR.png", "dariusText");
		}
		
	};
}