#include<Scene.h>

using namespace Platformer;

void Scene::Update(unsigned int shaderProgram, GJK3D* gjk, GLFWwindow* window)
{
	if (player != nullptr)
		cam.Update(player->transform->GetPosition());
	
	Mat4 projView = cam.GetProjectionMatrix() * cam.GetViewMatrix();

	if (inGame)
		DrawImGui(shaderProgram, projView);
	else if (inOptions)
		DrawOptions();
	else
		DrawMainMenu(window);

	if (glfwWindowShouldClose(window) == true)
		return;

	ASSERT(directLights.size() + pointLights.size() + spotLights.size() > 8, "There are too many lights in the scene");

	PointLightsToShaders(shaderProgram);
	DirectLightsToShaders(shaderProgram);
	SpotLightsToShaders(shaderProgram);

	player->collideWith = nullptr;
	player->heightLimit = 0;

	if (drawOn)
	{
		for (int i = 0; i < gameObjects.size(); i++)
		{
			gameObjects[i]->Update(projView, shaderProgram, sampler, textId);

			if (gameObjects[i] != player && gjk->intersect(*player->collider, *gameObjects[i]->collider))
				player->collideWith = gameObjects[i];
		}

		player->Update();
	}

	if (drawHitBoxOn)
	{
		for (int i = 0; i < gameObjects.size(); i++)
		{
			gameObjects[i]->DrawHitbox(projView, shaderProgram, sampler, textId);
		}
	}
}

void Scene::Clear()
{
	meshes.clear();
	gameObjects.clear();
	pointLights.clear();
	directLights.clear();
	spotLights.clear();
	enemies.clear();
	player = nullptr;
}

void Scene::PointLightsToShaders(unsigned int shaderProgram)
{
	stringstream pointLight;
	stringstream diffuseColor;
	stringstream ambientColor;
	stringstream specularColor;
	stringstream constant;
	stringstream linear;
	stringstream quadratic;
	stringstream lightPos;

	for (int i = 0; i < pointLights.size(); i++)
	{
		pointLight << "Point Light " << i;
		diffuseColor << "pointLights[" << i << "].diffuseColor";
		ambientColor << "pointLights[" << i << "].ambientColor";
		specularColor << "pointLights[" << i << "].specularColor";
		constant << "pointLights[" << i << "].constant";
		linear << "pointLights[" << i << "].linear";
		quadratic << "pointLights[" << i << "].quadratic";
		lightPos << "pointLights[" << i << "].position";

		glUniform3f(glGetUniformLocation(shaderProgram, diffuseColor.str().c_str()), pointLights[i]->diffuseColor.x, pointLights[i]->diffuseColor.y, pointLights[i]->diffuseColor.z);
		glUniform3f(glGetUniformLocation(shaderProgram, ambientColor.str().c_str()), pointLights[i]->ambientColor.x, pointLights[i]->ambientColor.y, pointLights[i]->ambientColor.z);
		glUniform3f(glGetUniformLocation(shaderProgram, specularColor.str().c_str()), pointLights[i]->specularColor.x, pointLights[i]->specularColor.y, pointLights[i]->specularColor.z);
		glUniform3f(glGetUniformLocation(shaderProgram, lightPos.str().c_str()), pointLights[i]->position.x, pointLights[i]->position.y, pointLights[i]->position.z);

		glUniform1f(glGetUniformLocation(shaderProgram, constant.str().c_str()), pointLights[i]->constant);
		glUniform1f(glGetUniformLocation(shaderProgram, linear.str().c_str()), pointLights[i]->linear);
		glUniform1f(glGetUniformLocation(shaderProgram, quadratic.str().c_str()), pointLights[i]->quadratic);

		pointLight.str("");
		diffuseColor.str("");
		ambientColor.str("");
		specularColor.str("");
		lightPos.str("");
		constant.str("");
		linear.str("");
		quadratic.str("");
	}

	glUniform1i(glGetUniformLocation(shaderProgram, "pointLightCount"), pointLights.size());
}

void Scene::DirectLightsToShaders(unsigned int shaderProgram)
{
	stringstream directLight;
	stringstream diffuseColor;
	stringstream ambientColor;
	stringstream specularColor;
	stringstream lightDir;

	for (int i = 0; i < directLights.size(); i++)
	{

		directLights[i]->SendData(shaderProgram, i);

		directLight << "Direct Light " << i;
		diffuseColor << "directLights[" << i << "].diffuseColor";
		ambientColor << "directLights[" << i << "].ambientColor";
		specularColor << "directLights[" << i << "].specularColor";
		lightDir << "directLights[" << i << "].direction";

		glUniform3f(glGetUniformLocation(shaderProgram, diffuseColor.str().c_str()), directLights[i]->diffuseColor.x, directLights[i]->diffuseColor.y, directLights[i]->diffuseColor.z);
		glUniform3f(glGetUniformLocation(shaderProgram, ambientColor.str().c_str()), directLights[i]->ambientColor.x, directLights[i]->ambientColor.y, directLights[i]->ambientColor.z);
		glUniform3f(glGetUniformLocation(shaderProgram, specularColor.str().c_str()), directLights[i]->specularColor.x, directLights[i]->specularColor.y, directLights[i]->specularColor.z);
		glUniform3f(glGetUniformLocation(shaderProgram, lightDir.str().c_str()), directLights[i]->direction.x, directLights[i]->direction.y, directLights[i]->direction.z);

		directLight.str("");
		diffuseColor.str("");
		ambientColor.str("");
		specularColor.str("");
		lightDir.str("");
	}

	glUniform1i(glGetUniformLocation(shaderProgram, "directLightCount"), directLights.size());
}

void Scene::SpotLightsToShaders(unsigned int shaderProgram)
{
	stringstream spotLight;
	stringstream diffuseColor;
	stringstream ambientColor;
	stringstream specularColor;
	stringstream constant;
	stringstream linear;
	stringstream quadratic;
	stringstream lightPos;
	stringstream lightDir;
	stringstream lightAng;

	for (int i = 0; i < spotLights.size(); i++)
	{
		spotLight << "Spot Light " << i;
		ambientColor << "spotLights[" << i << "].ambientColor";
		diffuseColor << "spotLights[" << i << "].diffuseColor";
		specularColor << "spotLights[" << i << "].specularColor";
		constant << "spotLights[" << i << "].constant";
		linear << "spotLights[" << i << "].linear";
		quadratic << "spotLights[" << i << "].quadratic";
		lightPos << "spotLights[" << i << "].position";
		lightDir << "spotLights[" << i << "].direction";
		lightAng << "spotLights[" << i << "].angle";

		glUniform3f(glGetUniformLocation(shaderProgram, diffuseColor.str().c_str()), spotLights[i]->diffuseColor.x, spotLights[i]->diffuseColor.y, spotLights[i]->diffuseColor.z);
		glUniform3f(glGetUniformLocation(shaderProgram, ambientColor.str().c_str()), spotLights[i]->ambientColor.x, spotLights[i]->ambientColor.y, spotLights[i]->ambientColor.z);
		glUniform3f(glGetUniformLocation(shaderProgram, specularColor.str().c_str()), spotLights[i]->specularColor.x, spotLights[i]->specularColor.y, spotLights[i]->specularColor.z);
		glUniform3f(glGetUniformLocation(shaderProgram, lightPos.str().c_str()), spotLights[i]->position.x, spotLights[i]->position.y, spotLights[i]->position.z);
		glUniform3f(glGetUniformLocation(shaderProgram, lightDir.str().c_str()), spotLights[i]->direction.x, spotLights[i]->direction.y, spotLights[i]->direction.z);

		glUniform1f(glGetUniformLocation(shaderProgram, constant.str().c_str()), spotLights[i]->constant);
		glUniform1f(glGetUniformLocation(shaderProgram, linear.str().c_str()), spotLights[i]->linear);
		glUniform1f(glGetUniformLocation(shaderProgram, quadratic.str().c_str()), spotLights[i]->quadratic);
		glUniform1f(glGetUniformLocation(shaderProgram, lightAng.str().c_str()), spotLights[i]->angle);

		diffuseColor.str("");
		ambientColor.str("");
		specularColor.str("");
		lightPos.str("");
		lightDir.str("");
		constant.str("");
		linear.str("");
		quadratic.str("");
		lightAng.str("");
		spotLight.str("");
	}

	glUniform1i(glGetUniformLocation(shaderProgram, "spotLightCount"), spotLights.size());
}

void Scene::DrawImGui(int shaderProgram, Mat4 projView)
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	{
		ImGui::Begin("Control Panel");
		ImGui::Checkbox("Draw models", &drawOn);
		ImGui::Checkbox("Draw hitboxes", &drawHitBoxOn);
		ImGui::Checkbox("Reset Scene", &resetScene);


		if (ImGui::Button("Add Cube"))
			gameObjects.push_back(new Platformer::GameObject(meshes[2], Vec3(), Vec3(1, 1, 1), Vec3()));


		if (ImGui::Button("Add Point Light"))
			pointLights.push_back(new LowRenderer::PointLight(Vec3(0, 0, 0), Vec3(1, 1, 1), 1, 0.022f, 0.0019f));

		if (ImGui::Button("Add Spot Light"))
			spotLights.push_back(new LowRenderer::SpotLight(Vec3(0, -10, 0), Vec3(0, 0, 0), Vec3(1, 1, 1), 1, 0.022f, 0.0019f, M_PI / 4));

		stringstream gameObject;
		stringstream rotationString;
		stringstream positionString;
		stringstream scaleString;

		for (int i = 0; i < gameObjects.size(); i++)
		{
			gameObject << "GameObject " << i + 1;
			rotationString << "rotation" << i;
			positionString << "position " << i;
			scaleString << "scale " << i;

			if (ImGui::TreeNode(gameObject.str().c_str()))
			{
				ImGui::SliderFloat3(rotationString.str().c_str(), gameObjects[i]->rotation, -2 * M_PI, 2 * M_PI);
				gameObjects[i]->transform->SetRotation(Vec3(gameObjects[i]->rotation[0], gameObjects[i]->rotation[1], gameObjects[i]->rotation[2]));
				ImGui::SliderFloat3(positionString.str().c_str(), gameObjects[i]->position, -100, 100);
				gameObjects[i]->transform->SetPosition(Vec3(gameObjects[i]->position[0], gameObjects[i]->position[1], gameObjects[i]->position[2]));
				ImGui::SliderFloat3(scaleString.str().c_str(), gameObjects[i]->scale, 0.0, 3);
				gameObjects[i]->transform->SetScale(Vec3(gameObjects[i]->scale[0], gameObjects[i]->scale[1], gameObjects[i]->scale[2]));

				ImGui::TreePop();
				ImGui::Separator();
			}

			rotationString.str("");
			positionString.str("");
			scaleString.str("");
			gameObject.str("");
		}

		ImGui::Text("light");
		static float color[4] = { 1.0f,1.0f,1.0f,1.0f };
		ImGui::ColorEdit3("color", color);
		ImGui::End();
	}

	ImGui::EndFrame();
}

void Scene::DrawOptions()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();

	ImGui::NewFrame();
	{
		ImGui::Begin("Options");

		if (ImGui::Button("Avancer")) {}
		if (ImGui::Button("Reculer")) {}
		if (ImGui::Button("Droite")) {}
		if (ImGui::Button("Gauche")) {}
		if (ImGui::Button("Saut")) {}

		ImGui::End();
	}
	ImGui::EndFrame();
}

void Scene::DrawMainMenu(GLFWwindow* window)
{

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();

	ImGui::NewFrame();
	{
		ImGui::Begin("Menu principal");

		if (ImGui::Button("Nouvelle partie"))
		{
			inGame = true;
			drawOn = true;
		}

		if (ImGui::Button("Options"))
		{
			inOptions = true;
		}

		if (ImGui::Button("Quitter"))
		{ 
			glfwSetWindowShouldClose(window, true);
			Clear();
		}

		ImGui::End();
	}
	ImGui::EndFrame();
}