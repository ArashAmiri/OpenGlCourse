#include "Actor.h"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Shader.h"
#include "Texture.h"
#include "Material.h"
#include "Mesh.h"

#include "Material.h"

AActor::AActor(
	AMaterial *MaterialToSet,
	glm::vec3 PositionToSet, 
	FShaderProgram* ShaderProgramToSet) 
	: Material(MaterialToSet)
	, Position(PositionToSet)
	, ShaderProgram(ShaderProgramToSet) {}

void AActor::LoadModel(const std::string& Filename)
{
	Assimp::Importer Importer;
	const aiScene* Scene = Importer.ReadFile(
		Filename, 
		aiProcess_Triangulate 
		| aiProcess_FlipUVs 
		| aiProcess_GenSmoothNormals 
		| aiProcess_JoinIdenticalVertices);

	if (!Scene)
	{
		printf("%s Model failed to Load %s", Filename, Importer.GetErrorString());
		return;
	}

	LoadNode(Scene->mRootNode, Scene);
	LoadMaterials(Scene);
}

void AActor::Update(float DeltaTime)
{
	GLuint uniformSpecularIntensity = ShaderProgram->GetSpecularIntensityLocation();
	GLuint uniformShininess = ShaderProgram->GetShininessLocation();

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::mat4(1.0f);
	model = glm::translate(model, Position);

	for (size_t i = 0; i < MeshList.size(); ++i)
	{
		unsigned int MaterialIndex = MeshToText[i];

		if (MaterialIndex < TextureList.size() && TextureList[MaterialIndex])
		{
			TextureList[MaterialIndex]->UseTexture();
		}

		MeshList[i]->RenderMesh();
	}

	ShaderProgram->UpadeModelUniform(model);
	Material->UseMaterial(uniformSpecularIntensity, uniformShininess);
}

void AActor::ClearModel()
{
	for (size_t i = 0; i < MeshList.size(); ++i)
	{
		if (MeshList[i])
		{
			delete MeshList[i];
			MeshList[i] = nullptr;
		}
	}

	for (size_t i = 0; i < TextureList.size(); ++i)
	{
		if (TextureList[i])
		{
			delete TextureList[i];
			TextureList[i] = nullptr;
		}
	}

}

void AActor::Rotate(glm::vec3 RotationVectorToSet)
{
	RotationVector = RotationVectorToSet;
}

void AActor::LoadNode(aiNode* Node, const aiScene* Scene)
{
	for (size_t i = 0; i < Node->mNumMeshes; ++i)
	{
		LoadMesh(Scene->mMeshes[Node->mMeshes[i]], Scene);
	}

	for (size_t i = 0; i < Node->mNumChildren; ++i)
	{
		LoadNode(Node->mChildren[i], Scene);
	}
}

void AActor::LoadMesh(aiMesh* Mesh, const aiScene* Scene)
{
	std::vector<GLfloat> Vertices;
	std::vector<unsigned int> Indices;

	for (size_t i = 0; i < Mesh->mNumVertices; ++i)
	{
		Vertices.insert(Vertices.end(), { Mesh->mVertices[i].x, Mesh->mVertices[i].y, Mesh->mVertices[i].z });
		if (Mesh->mTextureCoords[0])
		{
			Vertices.insert(Vertices.end(), { Mesh->mTextureCoords[0][i].x, Mesh->mTextureCoords[0][i].y });
		}
		else
		{
			Vertices.insert(Vertices.end(), { 0.0f, 0.0f });
		}

		Vertices.insert(Vertices.end(), { -Mesh->mNormals[i].x, -Mesh->mNormals[i].y, -Mesh->mNormals[i].z });
	}

	for (size_t i = 0; i < Mesh->mNumFaces; ++i)
	{
		aiFace Face = Mesh->mFaces[i];
		for (size_t j = 0; j < Face.mNumIndices; j++)
		{
			Indices.push_back(Face.mIndices[j]);
		}
	}

	AMesh* NewMesh = new AMesh();
	NewMesh->CreateMesh(&Vertices[0], &Indices[0], Vertices.size(), Indices.size());
	MeshList.push_back(NewMesh);
	MeshToText.push_back(Mesh->mMaterialIndex);
}

void AActor::LoadMaterials(const aiScene* Scene)
{
	TextureList.resize(Scene->mNumMaterials);
	
	for (size_t i = 0; i < Scene->mNumMaterials; ++i)
	{
		aiMaterial* Material = Scene->mMaterials[i];
		TextureList[i] = nullptr;
		if (Material->GetTextureCount(aiTextureType_DIFFUSE))
		{
			aiString Path;
			if (Material->GetTexture(aiTextureType_DIFFUSE, 0, &Path) == AI_SUCCESS)
			{
				int Idx = std::string(Path.data).rfind("\\");
				std::string Filename = std::string(Path.data).substr(Idx + 1);

				std::string TexturePath = std::string("Textures/") + Filename;

				TextureList[i] = new ATexture(TexturePath.c_str());

				if (!TextureList[i]->LoadTexture())
				{
					printf("Failed to load texture %s. ", TexturePath);
					delete TextureList[i];
					TextureList[i] = nullptr;
				}
			}
		}

		if (!TextureList[i])
		{
			TextureList[i] = new ATexture("Textures/plain.png");
			TextureList[i]->LoadTextureWithAlpha();
		}
	}
}
