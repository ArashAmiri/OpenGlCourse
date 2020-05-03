#include "Shader.h"

#include <glm/gtc/type_ptr.hpp>


FShaderProgram::FShaderProgram()
{
	shaderProgramID 
		= uniformProjection 
		= uniformModel 
		= uniformView 
		= UniformDirectionalLight.UniformAmbientIntensity 
		= UniformDirectionalLight.UniformColor
		= 0;
}

void FShaderProgram::SetDirectionalLight(ADirectionalLight* DirectionalLightToSet)
{
	DirectionalLightToSet->UseLight(
		UniformDirectionalLight.UniformAmbientIntensity,
		UniformDirectionalLight.UniformColor,
		UniformDirectionalLight.UniformDiffuseIntensity,
		UniformDirectionalLight.UniformDirection);
}

void FShaderProgram::SetPointLight(APointLight* PointLightToSet, unsigned int LightCount)
{
	if (LightCount > MAX_POINT_LIGHTS)
	{
		LightCount = MAX_POINT_LIGHTS;
	}

	glUniform1i(UniformPointLightCount, LightCount);

	for (size_t i = 0; i < LightCount; i++)
	{
		PointLightToSet[i].UseLight(
			UniformPointLight[i].UniformAmbientIntensity,
			UniformPointLight[i].UniformColor,
			UniformPointLight[i].UniformDiffuseIntensity,
			UniformPointLight[i].UniformPosition,
			UniformPointLight[i].UniformConstant,
			UniformPointLight[i].UniformLinear,
			UniformPointLight[i].UniformExponent
		);

	}
}

void FShaderProgram::SetSpotLight(ASpotLight* SpotLightToSet, unsigned int LightCount)
{
	if (LightCount > MAX_SPOT_LIGHTS)
	{
		LightCount = MAX_SPOT_LIGHTS;
	}

	glUniform1i(UniformSpotLightCount, LightCount);

	for (size_t i = 0; i < LightCount; i++)
	{
		SpotLightToSet[i].UseLight(
			UniformSpotLight[i].UniformAmbientIntensity, 
			UniformSpotLight[i].UniformColor, 
			UniformSpotLight[i].UniformDiffuseIntensity, 
			UniformSpotLight[i].UniformPosition, 
			UniformSpotLight[i].UniformDirection, 
			UniformSpotLight[i].UniformConstant, 
			UniformSpotLight[i].UniformLinear, 
			UniformSpotLight[i].UniformExponent, 
			UniformSpotLight[i].UniformEdge
		);
	}
}

void FShaderProgram::CreateFromString(const char* vertexCode, const char* fragmentCode)
{
	CompileShader(vertexCode, fragmentCode);
}


void FShaderProgram::UseShader()
{
	glUseProgram(shaderProgramID);
}

void FShaderProgram::ClearShader()
{
	if (shaderProgramID != 0)
	{
		glDeleteProgram(shaderProgramID);
		shaderProgramID = 0;
	}
	uniformModel = 0;
	uniformProjection = 0;
}

FShaderProgram::~FShaderProgram()
{
	ClearShader();
}

void FShaderProgram::UpadeModelUniform(glm::mat4 model)
{
	glUniformMatrix4fv(GetModelLocation(), 1, GL_FALSE, glm::value_ptr(model));
}

void FShaderProgram::CompileShader(const char* vertexCode, const char* fragmentCode)
{
	shaderProgramID = glCreateProgram();

	if (!shaderProgramID) {
		printf("Error creating shader program!\n");
		return;
	}

	AddShader(shaderProgramID, vertexCode, GL_VERTEX_SHADER);
	AddShader(shaderProgramID, fragmentCode, GL_FRAGMENT_SHADER);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glLinkProgram(shaderProgramID);
	glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shaderProgramID, sizeof(eLog), NULL, eLog);
		printf("Error linking program: '%s'\n", eLog);
		return;
	}

	glValidateProgram(shaderProgramID);
	glGetProgramiv(shaderProgramID, GL_VALIDATE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shaderProgramID, sizeof(eLog), NULL, eLog);
		printf("Error validating program: '%s'\n", eLog);
		return;
	}

	uniformModel = GetUniformByCache("model");
	uniformProjection = GetUniformByCache("projection");
	uniformView = GetUniformByCache("view");

	UniformDirectionalLight.UniformColor = GetUniformByCache("directionLight.base.color");
	UniformDirectionalLight.UniformAmbientIntensity = GetUniformByCache("directionLight.base.ambientIntensity");
	UniformDirectionalLight.UniformDiffuseIntensity = GetUniformByCache("directionLight.base.diffuseIntensity");	
	UniformDirectionalLight.UniformDirection = GetUniformByCache("directionLight.direction");

	UniformPointLightCount = GetUniformByCache("pointLightCount");

	
	for (size_t i = 0; i < MAX_POINT_LIGHTS; ++i)
	{
		char locBuff[100] = { '\0' };
		snprintf(locBuff, sizeof(locBuff), "pointLights[%d].base.color", i);
		UniformPointLight[i].UniformColor = GetUniformByCache(locBuff);

		snprintf(locBuff, sizeof(locBuff), "pointLights[%d].base.ambientIntensity", i);
		UniformPointLight[i].UniformAmbientIntensity = GetUniformByCache(locBuff);

		snprintf(locBuff, sizeof(locBuff), "pointLights[%d].base.diffuseIntensity", i);
		UniformPointLight[i].UniformDiffuseIntensity = GetUniformByCache(locBuff);

		snprintf(locBuff, sizeof(locBuff), "pointLights[%d].position", i);
		UniformPointLight[i].UniformPosition = GetUniformByCache(locBuff);

		snprintf(locBuff, sizeof(locBuff), "pointLights[%d].constant", i);
		UniformPointLight[i].UniformConstant = GetUniformByCache(locBuff);

		snprintf(locBuff, sizeof(locBuff), "pointLights[%d].linear", i);
		UniformPointLight[i].UniformLinear = GetUniformByCache(locBuff);

		snprintf(locBuff, sizeof(locBuff), "pointLights[%d].exponent", i);
		UniformPointLight[i].UniformExponent = GetUniformByCache(locBuff);
	}	

	
	for (size_t i = 0; i < MAX_SPOT_LIGHTS; ++i)
	{
		char locBuff[100] = { '\0' };
		snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.base.color", i);
		UniformSpotLight[i].UniformColor = GetUniformByCache(locBuff);

		snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.base.ambientIntensity", i);
		UniformSpotLight[i].UniformAmbientIntensity = GetUniformByCache(locBuff);

		snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.base.diffuseIntensity", i);
		UniformSpotLight[i].UniformDiffuseIntensity = GetUniformByCache(locBuff);

		snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.position", i);
		UniformSpotLight[i].UniformPosition = GetUniformByCache(locBuff);

		snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.constant", i);
		UniformSpotLight[i].UniformConstant = GetUniformByCache(locBuff);

		snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.linear", i);
		UniformSpotLight[i].UniformLinear = GetUniformByCache(locBuff);

		snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.exponent", i);
		UniformSpotLight[i].UniformExponent = GetUniformByCache(locBuff);

		snprintf(locBuff, sizeof(locBuff), "spotLights[%d].direction", i);
		UniformSpotLight[i].UniformDirection = GetUniformByCache(locBuff);

		snprintf(locBuff, sizeof(locBuff), "spotLights[%d].edge", i);
		UniformSpotLight[i].UniformEdge = GetUniformByCache(locBuff);

	}
	 
	uniformSpeculaIntensity = GetUniformByCache("material.specularIntensity");
	uniformShininess = GetUniformByCache("material.shininess");
	uniformEyePosition = GetUniformByCache("eyePosition");
}

void FShaderProgram::AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType)
{
	GLuint theShader = glCreateShader(shaderType);

	const GLchar* theCode[1];
	theCode[0] = shaderCode;

	GLint codeLength[1];
	codeLength[0] = strlen(shaderCode);

	glShaderSource(theShader, 1, theCode, codeLength);
	glCompileShader(theShader);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(theShader, sizeof(eLog), NULL, eLog);
		printf("Error compiling the %d shader: '%s'\n", shaderType, eLog);
		return;
	}

	glAttachShader(theProgram, theShader);
}

void FShaderProgram::CreateFromFiles(const char* vertexLocation, const char* fragmentLocation)
{
	std::string vertexString = ReadFile(vertexLocation);
	std::string fragmentString = ReadFile(fragmentLocation);
	const char* vertextCode = vertexString.c_str();
	const char* fragmentCode = fragmentString.c_str();
	CompileShader(vertextCode, fragmentCode);
}

std::string FShaderProgram::ReadFile(const char* fileLocation)
{
	std::string content;
	std::ifstream fileStream(fileLocation, std::ios::in);

	if (!fileStream.is_open())
	{
		printf("Failed to read %s. File does not exists! ", fileLocation);
		return "";
	}

	std::string line = "";
	while (!fileStream.eof())
	{
		std::getline(fileStream, line);
		content.append(line + "\n");
	}

	fileStream.close();

	return content;
}

GLuint FShaderProgram::GetUniformByCache(std::string UniformName) const
{
	auto CachedUniform = UniformCache.find(UniformName);
	if (CachedUniform != UniformCache.end())
	{
		return UniformCache[UniformName];
	}
	else
	{
		GLuint UniformFromGPU = glGetUniformLocation(shaderProgramID, UniformName.c_str());
		UniformCache[UniformName] = UniformFromGPU;
		return UniformFromGPU;
	}
	return GLuint();
}
