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
	FTransform TransformToSet, 
	FShaderProgram* ShaderProgramToSet) 
	: 
	Mesh(MeshToSet), 
	Texture(TextureToSet), 
	Material(MaterialToSet), 
	Transform(TransformToSet), 
	ShaderProgram(ShaderProgramToSet) {}

void AActor::Update()
{
	GLuint uniformModel = ShaderProgram->GetModelLocation();

	GLuint uniformSpecularIntensity = ShaderProgram->GetSpecularIntensityLocation();
	GLuint uniformShininess = ShaderProgram->GetShininessLocation();

	glm::mat4 model(1);
	FVector Location = Transform.GetLocation();
	model = glm::translate(model, glm::vec3(Location.X, Location.Y, Location.Z));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

	Texture->UseTexture();
	Material->UseMaterial(uniformSpecularIntensity, uniformShininess);
	Mesh->RenderMesh();
}
