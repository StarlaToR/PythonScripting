#pragma once

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include<GameObject.h>
#include<Light.h>
#include <Player.h>
#include <Physics.h>
#include <Enemy.h>
#include <Camera.h>

namespace Platformer
{
	class Scene
	{
	private:

	public:
		string name;
		std::vector<LowRenderer::Mesh*> meshes;
		std::vector<Platformer::GameObject*> gameObjects;
		std::vector<LowRenderer::PointLight*> pointLights;
		std::vector<LowRenderer::DirectionnalLight*> directLights;
		std::vector<LowRenderer::SpotLight*> spotLights;
		std::vector<Platformer::Enemy*> enemies;
		Platformer::Player* player;
		LowRenderer::Camera cam;
		GLuint sampler = 0;
		GLint max = 0;
		int textId = 0;

		bool drawOn = false;
		bool drawHitBoxOn = false;
		bool resetScene = false;
		bool inGame = false;
		bool inOptions = false;

		Scene(string _sceneName) { name = _sceneName; }
		~Scene()
		{
			glDeleteSamplers(1, &sampler);
		}

		void Update(unsigned int shaderProgram, GJK3D* gjk, GLFWwindow* window);
		void Clear();
		void PointLightsToShaders(unsigned int shaderProgram);
		void DirectLightsToShaders(unsigned int shaderProgram);
		void SpotLightsToShaders(unsigned int shaderProgram);
		void DrawImGui(int shaderProgram, Mat4 projView);
		void DrawMainMenu(GLFWwindow* window);
		void DrawOptions();
	};
}