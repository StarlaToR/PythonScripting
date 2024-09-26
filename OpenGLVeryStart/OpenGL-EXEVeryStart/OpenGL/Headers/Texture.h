#pragma once
#include <IResource.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>



namespace Resources
{
	class Texture : public IResource
	{
	private:
		int width, height, nrChannels;
		unsigned char* data;
	public:
		bool isBinded = false;
		GLuint texture;

		Texture() {};
		Texture(const std::string& filename)
		{
			setResourcePath(filename);
			//loadResource();
		}

		void loadResource();
		void unloadResource();
		void BindResource(GLuint& sampler, int textId);
	};
}