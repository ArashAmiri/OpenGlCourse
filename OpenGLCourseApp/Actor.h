#pragma once

#include "glm/glm.hpp"

#include <vector>
#include <string>

#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>
#include <assimp/Importer.hpp>

class AActor
{

private:

	std::vector<class AMesh*> MeshList;
	std::vector<class ATexture*> TextureList;
	std::vector<unsigned int> MeshToText;

	std::string Name = "DefaultName";

protected:

	class AMaterial* Material;
	class FShaderProgram* ShaderProgram;

	float RotationFactor = 0.0f;
	glm::vec3 Rotation = glm::vec3(0.0f);
	float Speed = 0;
	bool bIsRotating = true;

public:
	mutable glm::vec3 Position;
	mutable glm::vec3 RotationVector = glm::vec3(0.0f);

	AActor(std::string Name, class AMaterial *MaterialToSet, glm::vec3 Position, FShaderProgram* ShaderProgram);

	//inline void UpdatePosition(glm::vec3 PositionToSet) { Position = PositionToSet; }

	inline glm::vec3 GetPosition() const { return Position; };

	void LoadModel(const std::string& Filename);
	void Update(float DeltaTime); //RenderModel
	void ClearModel();
	void Rotate(glm::vec3 Rotation);

private:

	void LoadNode(aiNode *Node, const aiScene *Scene);
	void LoadMesh(aiMesh* Mesh, const aiScene* Scene);
	void LoadMaterials(const aiScene *Scene);
};

