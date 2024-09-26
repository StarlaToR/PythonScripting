#include <Mesh.h>

using namespace LowRenderer;

Mesh::Mesh(Model* mod, Texture* text)
{
	model = mod;
	texture = text;
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void Mesh::Init(GLuint& sampler, int& textId)
{
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glGenVertexArrays(1, &VAO);

	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	//glNamedBufferData(VBO, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * model->getVertexBuffer().size(), model->getVertexBuffer().data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * model->getIndexBuffer().size(), model->getIndexBuffer().data(), GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	texture->BindResource(sampler, textId);
	textId++;

	isInit = true;
}

void Mesh::Update(const Mat4& projviewMatrix, unsigned int shaderProgram, GLuint& sampler, int& textId)
{
	if (isInit)
	{
		Mat4 transformMatrix = projviewMatrix * modelMatrix;

		glUseProgram(shaderProgram);

		unsigned int modelLoc = glGetUniformLocation(shaderProgram, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, *modelMatrix.tab);
		unsigned int transformLoc = glGetUniformLocation(shaderProgram, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, *transformMatrix.tab);

		// draw our first triangle

		if (texture->isBinded)// ! texture peut ne pas etre loader si multithreading !
		{
			glBindTextureUnit(0, texture->texture);
			glUniform1i(glGetUniformLocation(shaderProgram, "texture1"), 0); // set it manually
		}

		glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

		glDrawElements(GL_TRIANGLES, model->getVertexBuffer().size(), GL_UNSIGNED_INT, 0);
	}
	else if (model->isLoaded && texture->isLoaded)
	{
		Init(sampler, textId);
	}
}

void Mesh::SetModelMatrix(const Mat4& modelMat)
{
	modelMatrix = modelMat;
}

std::vector<Vec3> Mesh::GetVertices()
{
	std::vector<Vertex> v =  model->getVertexBuffer();
	std::vector<Vec3> final;
	for (Vertex vertex : v)
	{
		final.push_back(vertex.Position);
	}
	return final;
}
