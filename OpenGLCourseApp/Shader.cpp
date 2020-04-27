#include "Shader.h"

FShaderProgram::FShaderProgram()
{
	shaderProgramID, uniformProjection, uniformModel, uniformView, uniformAmbientIntensity, uniformAmbientColor = 0;
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

	uniformModel = glGetUniformLocation(shaderProgramID, "model");
	uniformProjection = glGetUniformLocation(shaderProgramID, "projection");
	uniformView = glGetUniformLocation(shaderProgramID, "view");
	uniformAmbientColor = glGetUniformLocation(shaderProgramID, "directionLight.color");
	uniformAmbientIntensity = glGetUniformLocation(shaderProgramID, "directionLight.ambientIntensity");
	uniformDirection = glGetUniformLocation(shaderProgramID, "directionLight.direction");
	uniformDiffuseIntensity = glGetUniformLocation(shaderProgramID, "directionLight.diffuseIntensity");
	uniformSpeculaIntensity = glGetUniformLocation(shaderProgramID, "material.specularIntensity");
	uniformShininess = glGetUniformLocation(shaderProgramID, "material.shininess");
	uniformEyePosition = glGetUniformLocation(shaderProgramID, "eyePosition");
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
