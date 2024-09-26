#include <SceneManager.h>

using namespace Platformer;

void SceneManager::InitScene1(Resources::ResourceManager* manager)
{
	Scene* scene = new Scene("Scene 1");


	glGenSamplers(1, &scene->sampler);
	glSamplerParameteri(scene->sampler, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glSamplerParameteri(scene->sampler, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glSamplerParameteri(scene->sampler, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glSamplerParameteri(scene->sampler, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glSamplerParameterf(scene->sampler, GL_TEXTURE_MAX_ANISOTROPY_EXT, 4.f);

	glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &scene->max);
	
	scene->cam = LowRenderer::Camera();
	scene->cam.position = Vec3(0, 10, -30);

	scene->directLights.push_back(new LowRenderer::DirectionnalLight(Vec3(5, -10, 0), Vec3(1, 1, 1)));
	scene->pointLights.push_back(new LowRenderer::PointLight(Vec3(0, 10, 0), Vec3(1, 1, 1), 1, 0.022f, 0.0019f));
	scene->spotLights.push_back(new LowRenderer::SpotLight(Vec3(0, -10, 0), Vec3(0, 0, 0), Vec3(1, 1, 1), 1, 0.022f, 0.0019f, M_PI / 3.15));


	//Player
	LowRenderer::Mesh* khaMeshPtr = new LowRenderer::Mesh(manager->Get<Model>("khazix"), manager->Get<Texture>("khazText"));
	scene->meshes.push_back(khaMeshPtr);
	Player* player = new Player(khaMeshPtr, Vec3(), Vec3(0, -M_PI / 2, 0), Vec3(0.02f, 0.02f, 0.02f), Vec3(0, 0, 1), new float[3]{ 0.02f,0.02f,0.02f });

	scene->player = player;
	scene->gameObjects.push_back(player);
	scene->spotLights.push_back(player->GetShadow());

	//Enem
	LowRenderer::Mesh* azirMeshPtr = new LowRenderer::Mesh(manager->Get<Model>("azir"), manager->Get<Texture>("azirText"));
	scene->meshes.push_back(azirMeshPtr);
	Enemy* azir = new Enemy(azirMeshPtr, Vec3(-20, 0, -1), Vec3(0.03f, 0.03f, 0.03f), Vec3());
	scene->gameObjects.push_back(azir);
	scene->enemies.push_back(azir);

	//Level
	Vec3 levelCoord[9] = { Vec3(0, -5, 0), Vec3(0, 8, 13), Vec3(0, 16, 23), Vec3(7, 27, 28), Vec3(-17, 32, 18), Vec3(7, 32, 9), Vec3(-30, 45, 9), Vec3(-50, 45, 9), Vec3(-50, 10, 9) };
	LowRenderer::Mesh* cubeMeshPtr = new LowRenderer::Mesh(manager->Get<Model>("cube"), manager->Get<Texture>("catText"));
	scene->meshes.push_back(cubeMeshPtr);
	for (int i = 0; i < 9; i++)
	{
		scene->gameObjects.push_back(new GameObject(cubeMeshPtr, levelCoord[i], Vec3(3.f, 3.f, 3.f), Vec3()));
	}
	scene->gameObjects.push_back(new GameObject(khaMeshPtr, Vec3(20, 0, -1), Vec3(0.05f, 0.05f, 0.05f), Vec3()));

	//Obejct
	LowRenderer::Mesh* GD = new LowRenderer::Mesh(manager->Get<Model>("GanondorfPast"), manager->Get<Texture>("ganondorfText"));
	scene->meshes.push_back(GD);
	Enemy* Ganon = new Enemy(GD, Vec3(10, -10, 10), Vec3(0.1f, 0.1f, 0.1f), Vec3(0, 3, 0));
	scene->gameObjects.push_back(Ganon);
	scene->enemies.push_back(Ganon);

	LowRenderer::Mesh* MF = new LowRenderer::Mesh(manager->Get<Model>("MF"), manager->Get<Texture>("missText"));
	scene->meshes.push_back(MF);
	Enemy* Miss = new Enemy(MF, Vec3(10, -10, 20), Vec3(0.3f, 0.3f, 0.3f), Vec3());
	scene->gameObjects.push_back(Miss);
	scene->enemies.push_back(Miss);

	LowRenderer::Mesh* garen = new LowRenderer::Mesh(manager->Get<Model>("garen"), manager->Get<Texture>("garenText"));
	scene->meshes.push_back(garen);
	Enemy* Grn = new Enemy(garen, Vec3(10, 0, -30), Vec3(0.3f, 0.3f, 0.3f), Vec3(0, 4, 0));
	scene->gameObjects.push_back(Grn);
	scene->enemies.push_back(Grn);

	LowRenderer::Mesh* darius = new LowRenderer::Mesh(manager->Get<Model>("darius"), manager->Get<Texture>("dariusText"));
	scene->meshes.push_back(darius);
	Enemy* Drs = new Enemy(darius, Vec3(-18, 0, -30), Vec3(0.3f, 0.3f, 0.3f), Vec3(0, 1.5f, 0));
	scene->gameObjects.push_back(Drs);
	scene->enemies.push_back(Drs);

	LowRenderer::Mesh* hitbox = new LowRenderer::Mesh(manager->Get<Model>("cube"), manager->Get<Texture>("dogText"));

	for (int i = 0; i < scene->gameObjects.size(); i++)
	{
		scene->gameObjects[i]->hitbox = hitbox;
	}

	scenes.push_back(scene);	
}

void SceneManager::Update(unsigned int shaderProgram, GLFWwindow* window, Resources::ResourceManager* manager)
{
	processInput(window, &scenes[currentScene]->cam);

	if (mouseOn)
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	else
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	if (scenes[currentScene]->resetScene)
	{
		scenes[currentScene]->Clear();
		scenes.pop_back();
		
		manager->Clear();
		manager->Init();
		
		InitScene1(manager);
		scenes[currentScene]->resetScene = false;
	}

	scenes[currentScene]->Update(shaderProgram, &gjk, window);

}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void SceneManager::processInput(GLFWwindow* window, LowRenderer::Camera* cam)
{
	
	if (scenes[currentScene]->inGame)
	{

		//Camera
		if (glfwGetKey(window, camLeftKey) == GLFW_PRESS)
			cam->AddOffset(cam->camRight * cam->speed);
		if (glfwGetKey(window, camRightKey) == GLFW_PRESS)
			cam->AddOffset(-1 * cam->camRight * cam->speed);
		if (glfwGetKey(window, camForwardKey) == GLFW_PRESS)
			cam->AddOffset(cam->camUp * cam->speed);
		if (glfwGetKey(window, camBackKey) == GLFW_PRESS)
			cam->AddOffset(-1 * cam->camUp * cam->speed);

		if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
			scenes[currentScene]->resetScene = true;

		if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
		{
			try {
				auto player_pyt = pybind11::module::import("Script.Controle");
				auto player_Jump = player_pyt.attr("Reload");
				player_Jump();
			}
			catch (pybind11::error_already_set error) {
				printf("%s\n", error.what());
			}
		}

		//Player movement
		if (glfwGetKey(window, leftKey) == GLFW_PRESS)
			scenes[currentScene]->player->MovePlayer(Vec3(-1, 0, 0), cam->camForward);
		if (glfwGetKey(window, rightKey) == GLFW_PRESS)
			scenes[currentScene]->player->MovePlayer(Vec3(1, 0, 0), cam->camForward);
		if (glfwGetKey(window, forwardKey) == GLFW_PRESS)
			scenes[currentScene]->player->MovePlayer(Vec3(0, 0, 1), cam->camForward);
		if (glfwGetKey(window, backKey) == GLFW_PRESS)
			scenes[currentScene]->player->MovePlayer(Vec3(0, 0, -1), cam->camForward);


		//PlayerJump
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS
			&& scenes[currentScene]->player->canJump
			&& scenes[currentScene]->player->collideWith == nullptr)
			scenes[currentScene]->player->Jump();

		if ((cam->position - scenes[currentScene]->player->transform->GetPosition()).GetMagnitude() >= 50)
			cam->SetOffset(Vec3(cam->position - scenes[currentScene]->player->transform->GetPosition()) * 0.9f);
	}

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		scenes[currentScene]->inGame = false;
		scenes[currentScene]->inOptions = false;
	}

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT))
	{
		mouseOn = true;
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		cam->MouseDirection(xpos, ypos);
	}
	else
	{
		mouseOn = false;
		cam->camForward = cam->oldDirection;
		cam->firstMouse = true;
	}
}