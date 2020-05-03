#include "Actor.h"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Shader.h"
#include "Texture.h"
#include "Material.h"
#include "Mesh.h"

AActor::AActor()
{
}

AActor::AActor(
	AMesh* MeshToSet, 
	ATexture* TextureToSet, 
	AMaterial* MaterialToSet, 
	glm::vec3 PositionToSet, 
	FShaderProgram* ShaderProgramToSet) 
	: 
	Mesh(MeshToSet), 
	Texture(TextureToSet), 
	Material(MaterialToSet), 
	Position(PositionToSet), 
	ShaderProgram(ShaderProgramToSet) {}

void AActor::Update(float DeltaTime)
{
	GLuint uniformSpecularIntensity = ShaderProgram->GetSpecularIntensityLocation();
	GLuint uniformShininess = ShaderProgram->GetShininessLocation();

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::mat4(1.0f);
	model = glm::translate(model, Position);

	if (bIsRotating)
	{
		//RotationFactor += (DeltaTime * 2);
		//model = glm::rotate(model, RotationFactor, glm::vec3(1.f));
	}
	else
	{
		model = glm::rotate(model, 1.f, RotationVector);
	}

	ShaderProgram->UpadeModelUniform(model);

	Texture->UseTexture();
	Material->UseMaterial(uniformSpecularIntensity, uniformShininess);
	Mesh->RenderMesh();
}

void AActor::Rotate(glm::vec3 RotationVectorToSet)
{
	RotationVector = RotationVectorToSet;
}
