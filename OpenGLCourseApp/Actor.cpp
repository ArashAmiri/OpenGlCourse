#include "Actor.h"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Texture.h"
#include "Material.h"
#include "Mesh.h"

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

void AActor::Update()
{
	GLuint uniformModel = ShaderProgram->GetModelLocation();

	GLuint uniformSpecularIntensity = ShaderProgram->GetSpecularIntensityLocation();
	GLuint uniformShininess = ShaderProgram->GetShininessLocation();

	glm::mat4 model(1);
	model = glm::translate(model, Position);
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

	Texture->UseTexture();
	Material->UseMaterial(uniformSpecularIntensity, uniformShininess);
	Mesh->RenderMesh();
}
