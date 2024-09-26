#include <Light.h>

void LowRenderer::PointLight::SendData(unsigned int shaderProgram, int lightIndex)
{
	std::stringstream ssPointLight;
	std::stringstream ssDiffuseColor;
	std::stringstream ssAmbientColor;
	std::stringstream ssSpecularColor;
	std::stringstream ssConstant;
	std::stringstream ssLinear;
	std::stringstream ssQuadratic;
	std::stringstream ssLightPos;

	ssPointLight << "Point Light " << lightIndex;
	ssDiffuseColor << "pointLights[" << lightIndex << "].diffuseColor";
	ssAmbientColor << "pointLights[" << lightIndex << "].ambientColor";
	ssSpecularColor << "pointLights[" << lightIndex << "].specularColor";
	ssConstant << "pointLights[" << lightIndex << "].constant";
	ssLinear << "pointLights[" << lightIndex << "].linear";
	ssQuadratic << "pointLights[" << lightIndex << "].quadratic";
	ssLightPos << "pointLights[" << lightIndex << "].position";



	glUniform3f(glGetUniformLocation(shaderProgram, ssDiffuseColor.str().c_str()), diffuseColor.x, diffuseColor.y, diffuseColor.z);
	glUniform3f(glGetUniformLocation(shaderProgram, ssAmbientColor.str().c_str()), ambientColor.x, ambientColor.y, ambientColor.z);
	glUniform3f(glGetUniformLocation(shaderProgram, ssSpecularColor.str().c_str()), specularColor.x, specularColor.y, specularColor.z);
	glUniform3f(glGetUniformLocation(shaderProgram, ssLightPos.str().c_str()), position.x, position.y, position.z);

	glUniform1f(glGetUniformLocation(shaderProgram, ssConstant.str().c_str()), constant);
	glUniform1f(glGetUniformLocation(shaderProgram, ssLinear.str().c_str()), linear);
	glUniform1f(glGetUniformLocation(shaderProgram, ssQuadratic.str().c_str()), quadratic);

	ssPointLight.str("");
	ssDiffuseColor.str("");
	ssAmbientColor.str("");
	ssSpecularColor.str("");
	ssLightPos.str("");
	ssConstant.str("");
	ssLinear.str("");
	ssQuadratic.str("");
	
}

void LowRenderer::DirectionnalLight::SendData(unsigned int shaderProgram, int lightIndex)
{

	std::stringstream ssDiffuseColor;
	std::stringstream ssAmbientColor;
	std::stringstream ssSpecularColor;
	std::stringstream ssLightDir;

	ssDiffuseColor << "directLights[" << lightIndex << "].diffuseColor";
	ssAmbientColor << "directLights[" << lightIndex << "].ambientColor";
	ssSpecularColor << "directLights[" << lightIndex << "].specularColor";
	ssLightDir << "directLights[" << lightIndex << "].direction";


	glUniform3f(glGetUniformLocation(shaderProgram, ssDiffuseColor.str().c_str()), diffuseColor.x, diffuseColor.y, diffuseColor.z);
	glUniform3f(glGetUniformLocation(shaderProgram, ssAmbientColor.str().c_str()), ambientColor.x, ambientColor.y, ambientColor.z);
	glUniform3f(glGetUniformLocation(shaderProgram, ssSpecularColor.str().c_str()), specularColor.x, specularColor.y, specularColor.z);
	glUniform3f(glGetUniformLocation(shaderProgram, ssLightDir.str().c_str()), direction.x, direction.y, direction.z);

	ssDiffuseColor.str("");
	ssAmbientColor.str("");
	ssSpecularColor.str("");
	ssLightDir.str("");


}

void LowRenderer::SpotLight::SendData(unsigned int shaderProgram, int lightIndex)
{
	std::stringstream ssDiffuseColor;
	std::stringstream ssAmbientColor;
	std::stringstream ssSpecularColor;
	std::stringstream ssConstant;
	std::stringstream ssLinear;
	std::stringstream ssQuadratic;
	std::stringstream ssLightPos;
	std::stringstream ssLightDir;
	std::stringstream ssLightAng;

	ssAmbientColor << "spotLights[" << lightIndex << "].ambientColor";
	ssDiffuseColor << "spotLights[" << lightIndex << "].diffuseColor";
	ssSpecularColor << "spotLights[" << lightIndex << "].specularColor";
	ssConstant << "spotLights[" << lightIndex << "].constant";
	ssLinear << "spotLights[" << lightIndex << "].linear";
	ssQuadratic << "spotLights[" << lightIndex << "].quadratic";
	ssLightPos << "spotLights[" << lightIndex << "].position";
	ssLightDir << "spotLights[" << lightIndex << "].direction";
	ssLightAng << "spotLights[" << lightIndex << "].angle";


	glUniform3f(glGetUniformLocation(shaderProgram, ssDiffuseColor.str().c_str()), diffuseColor.x, diffuseColor.y, diffuseColor.z);
	glUniform3f(glGetUniformLocation(shaderProgram, ssAmbientColor.str().c_str()), ambientColor.x, ambientColor.y, ambientColor.z);
	glUniform3f(glGetUniformLocation(shaderProgram, ssSpecularColor.str().c_str()), specularColor.x, specularColor.y, specularColor.z);
	glUniform3f(glGetUniformLocation(shaderProgram, ssLightPos.str().c_str()), position.x, position.y, position.z);
	glUniform3f(glGetUniformLocation(shaderProgram, ssLightDir.str().c_str()), direction.x, direction.y, direction.z);

	glUniform1f(glGetUniformLocation(shaderProgram, ssConstant.str().c_str()), constant);
	glUniform1f(glGetUniformLocation(shaderProgram, ssLinear.str().c_str()), linear);
	glUniform1f(glGetUniformLocation(shaderProgram, ssQuadratic.str().c_str()), quadratic);
	glUniform1f(glGetUniformLocation(shaderProgram, ssLightAng.str().c_str()), angle);

	ssDiffuseColor.str("");
	ssAmbientColor.str("");
	ssSpecularColor.str("");
	ssLightPos.str("");
	ssLightDir.str("");
	ssConstant.str("");
	ssLinear.str("");
	ssQuadratic.str("");
	ssLightAng.str("");
}
