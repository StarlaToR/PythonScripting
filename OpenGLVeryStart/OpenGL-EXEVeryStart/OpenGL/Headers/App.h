#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <ResourceManager.h>
#include <Maths.h>
#include <Mesh.h>
#include <Light.h>
#include <Log.h>
#include <sstream>
#include <SceneManager.h>


namespace Core
{
	struct AppInitializer
	{
		unsigned int width;
		unsigned int height;
		unsigned int major;
		unsigned int minor;
		const char* name;
		void (*framebuffer_size_callback)(GLFWwindow* window, int width, int height);
		void (*glDebugOutput)(GLenum source, GLenum type, GLuint id, GLenum severity,GLsizei length, const GLchar* message, const void* userParam);
	};

	class App
	{
	private:
		

	public:
		ResourceManager* manager;
		GLFWwindow* window;
		Platformer::SceneManager* sceneManager;
		std::vector<Platformer::Scene*> scenes;

		App()
		{
			sceneManager = new Platformer::SceneManager();
			manager = new ResourceManager();
		}

		~App();

		void Init(AppInitializer intializer);
		void Update(unsigned int shaderProgram);
		
		void SetManager(ResourceManager* _manager) { manager = _manager; };

	};
}