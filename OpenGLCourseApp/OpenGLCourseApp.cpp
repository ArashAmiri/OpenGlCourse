#define STB_IMAGE_IMPLEMENTATION

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Mesh.h"
#include "Shader.h"
#include "Window.h"
#include "Camera.h"
#include "Texture.h"
#include "Light.h"
#include "Material.h"
#include "Transform.h"
#include "Pawn.h"
#include "PlayerController.h"

#include "OpenGLCourseApp.h"

#include "GraphicsLayer.h"	

std::vector<AMesh*> MeshList;
std::vector<FShaderProgram*> ShaderProgramList;


APlayerController* PlayerController;

Window MainWindow = Window(1366, 768);

APawn* Player;

ACamera Camera;

Light MainLight;

ATexture BrickTexture;
ATexture DirtTexture;

AMaterial ShinyMaterial;
AMaterial DullMaterial;

GLfloat DeltaTime = 0.f;
GLfloat LastTime = 0.f;

const float toRadians = 3.14159265f / 180.f;

// Vertex Shader
static const char* vShader = "Shaders/shader.vert";

// Fragment Shader
static const char* fShader = "Shaders/shader.frag";

void calcAverageNormals(
	unsigned int* indices,
	unsigned int indiceCount,
	GLfloat* vertices,
	unsigned int verticeCount,
	unsigned int vertexLength,
	unsigned int normalOffset)
{
	for (size_t i = 0; i < indiceCount; i += 3)
	{
		unsigned int in0 = indices[i] * vertexLength;
		unsigned int in1 = indices[i + 1] * vertexLength;
		unsigned int in2 = indices[i + 2] * vertexLength;
		glm::vec3 v1(vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0 + 1], vertices[in1 + 2] - vertices[in0 + 2]);
		glm::vec3 v2(vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0 + 1], vertices[in2 + 2] - vertices[in0 + 2]);
		glm::vec3 normal = glm::cross(v1, v2);
		normal = glm::normalize(normal);

		in0 += normalOffset;
		in1 += normalOffset;
		in2 += normalOffset;

		vertices[in0] += normal.x; vertices[in0 + 1] += normal.y; vertices[in0 + 2] += normal.z;
		vertices[in1] += normal.x; vertices[in1 + 1] += normal.y; vertices[in1 + 2] += normal.z;
		vertices[in2] += normal.x; vertices[in2 + 1] += normal.y; vertices[in2 + 2] += normal.z;
	}

	for (size_t i = 0; i < verticeCount / vertexLength; ++i)
	{
		unsigned int nOffsetForEachOne = i * vertexLength + normalOffset;
		glm::vec3 vec(vertices[nOffsetForEachOne], vertices[nOffsetForEachOne + 1], vertices[nOffsetForEachOne + 2]);
		vec = glm::normalize(vec);
		vertices[nOffsetForEachOne] = vec.x; vertices[nOffsetForEachOne + 1] = vec.y; vertices[nOffsetForEachOne + 2] = vec.z;
	}

}

APlayerController* GetGlobalPlayerController() { return PlayerController; }

void CreateObjects()
{
	unsigned int indices[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	GLfloat vertices[] = {
		//x    y    z      u     v      nx   ny   nz
		-1.f, -1.f, -0.6f, 0.0f, 2.0f,  0.f, 0.f, 0.f,
		 0.f, -1.f, 1.f,   0.0f, 1.0f,  0.f, 0.f, 0.f,
		 1.f, -1.f, -0.6f, 2.0f, 0.0f,	0.f, 0.f, 0.f,
		 0.f,  1.f, 0.f,   1.0f, 2.0f,	0.f, 0.f, 0.f
	};

	calcAverageNormals(indices, 12, vertices, 32, 8, 5);

	AMesh *Mesh1 = new AMesh();
	Mesh1->CreateMesh(vertices, indices, 32, 12);
	MeshList.push_back(Mesh1);

	AMesh* Mesh2 = new AMesh();
	Mesh2->CreateMesh(vertices, indices, 32, 12);
	MeshList.push_back(Mesh2);
}

void CreateShaders()
{
	FShaderProgram *ShaderProgram = new FShaderProgram();
	ShaderProgram->CreateFromFiles(vShader, fShader);
	ShaderProgramList.push_back(ShaderProgram);
}

int main()
{
	std::vector<AActor*> Actors;

	MainWindow.initialize();

	CreateObjects();
	CreateShaders();
	Camera = ACamera(glm::vec3(0.f), glm::vec3(0.f, 1.f, 0.f), -90.f, 0.f, 3.f, .1f);

	BrickTexture = ATexture((char *)"Textures/brick.png");
	BrickTexture.LoadTexture();

	DirtTexture = ATexture((char*)"Textures/dirt.png");
	DirtTexture.LoadTexture();

	ShinyMaterial = AMaterial(1.0f, 32.f);
	DullMaterial = AMaterial(0.3f, 4.f);

	AActor* Player = new AActor(MeshList[0], &DirtTexture, &DullMaterial, { 0.f, 3.f, 3.f }, ShaderProgramList[0]);
	Player->SetIsRotating(false);
	Actors.push_back(Player);


	float x, y, z;
	x = 0.f;
	y = 0.f;
	z = 0.f;

	for (int i = 0; i < 6000; i++)
	{
		x += 1.5f;
		AActor *Actor = new AActor(MeshList[1], &BrickTexture, &ShinyMaterial, { x, y, z }, ShaderProgramList[0]);
		Actors.push_back(Actor);
		if (i % 36 == 0)
		{
			x = 0.f;
			y += 1.5f;
		}
		if (i % 36 == 0)
		{
			z += 1.5f;
			x = 0.f;
			y = 0.f;			
		}
	}


	PlayerController = &APlayerController();
	PlayerController->SetControlledActor(*Player);

	Player->Update(DeltaTime);

	MainLight = Light(1.f, 1.0f, 1.0f, 0.2f, 
		2.0f, -1.f, -2.f, 0.3f);

	GLuint uniformModel, uniformProjection, uniformView, 
		uniformAmbientColor, uniformAmbientIntensity,
		uniformDirection, uniformDiffuseIntensity,
		uniformEyePosition,
		uniformSpecularIntensity,
		uniformShininess
		= 0;

	glm::mat4 projection = glm::perspective(45.f, GLfloat(MainWindow.getBufferWidth()) / GLfloat(MainWindow.getBufferHeight()), .1f, 100.f);

	FTransform Transform = FTransform();
	
	//Loop until window is closed
	while (!MainWindow.getShouldClose())
	{
		GLfloat Now = glfwGetTime();
		DeltaTime = Now - LastTime;
		LastTime = Now;

		// Get and handle user input event
		glfwPollEvents();

		Camera.KeyControl(MainWindow.GetKeys(), DeltaTime);
		Camera.MouseControl(MainWindow.GetXChange(), MainWindow.GetYChange());

		//Camera.SetPosition(Player->GetPosition() + glm::vec3(-4.0f, 0.f, 0.f));

		GraphicsLayer::ClearScreen(glm::vec4(0.2f, 0.2f, 0.2f, 1.f));

		ShaderProgramList[0]->UseShader();

		uniformModel = ShaderProgramList[0]->GetModelLocation();
		uniformProjection = ShaderProgramList[0]->GetProjectionLocation();
		uniformView = ShaderProgramList[0]->GetViewLocation();
		uniformAmbientColor = ShaderProgramList[0]->GetAmbientColorLocation();
		uniformAmbientIntensity = ShaderProgramList[0]->GetAmbientIntensityLocation();
		uniformDirection = ShaderProgramList[0]->GetDirectionLocation();
		uniformDiffuseIntensity = ShaderProgramList[0]->GetDiffuseIntensityLocation();
		uniformEyePosition = ShaderProgramList[0]->GetEyePositionLocation();
		uniformSpecularIntensity = ShaderProgramList[0]->GetSpecularIntensityLocation();
		uniformShininess = ShaderProgramList[0]->GetShininessLocation();
		
		MainLight.UseLight(uniformAmbientIntensity, uniformAmbientColor, uniformDiffuseIntensity, uniformDirection);

		GraphicsLayer::PassUniforms(uniformProjection, uniformView, uniformEyePosition, projection, Camera);

		//Transform.Location = Camera.GetFront() + Camera.GetPosition();
		
		

		for (auto Actor : Actors)
		{
			Actor->Update(DeltaTime);
		}

		PlayerController->HandleUserInput(MainWindow.GetKeys(), DeltaTime, Camera);

		//Camera.SetPosition(PlayerController->GetControlledActor()->GetPosition() - glm::vec3(6.0f, 0.0f, 0.0f));
		
		GraphicsLayer::UseShaderProgram(0);

		MainWindow.swapBuffers();
	}


	return 0;

}


