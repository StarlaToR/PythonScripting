#pragma once
#include <Scene.h>
#include <ResourceManager.h>

namespace Platformer
{
	class SceneManager
	{
	private:

	public:
		bool drawOn = false;
		bool drawHitBoxOn = false;
		bool mouseOn = true;
		int forwardKey = GLFW_KEY_W;
		int backKey = GLFW_KEY_S;
		int leftKey = GLFW_KEY_A;
		int rightKey = GLFW_KEY_D;

		int camForwardKey = GLFW_KEY_UP;
		int camBackKey = GLFW_KEY_DOWN;
		int camLeftKey = GLFW_KEY_LEFT;
		int camRightKey = GLFW_KEY_RIGHT;

		int currentScene = 0;
		std::vector<Platformer::Scene*> scenes;
		GJK3D gjk;

		void InitScene1(Resources::ResourceManager* manager);
		void drawCube(Resources::ResourceManager* manager, Scene* scene);
		void Update(unsigned int shaderProgram, GLFWwindow* window, Resources::ResourceManager* manager);

		// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
		// ---------------------------------------------------------------------------------------------------------
		void processInput(GLFWwindow* window, LowRenderer::Camera* cam);

	};
}