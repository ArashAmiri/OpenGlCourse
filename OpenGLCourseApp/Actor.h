#pragma once

#include "Transform.h"
#include "glm/glm.hpp"

class AActor
{

protected:

	class AMesh* Mesh;
	class AMaterial* Material;
	class ATexture* Texture;
	class FShaderProgram* ShaderProgram;

	glm::vec3 Position;
	float Speed = 0;

public:

	AActor(AMesh* Mesh, ATexture* Texture, AMaterial* Material, glm::vec3 Position, FShaderProgram* ShaderProgram);

	inline void SetMesh(AMesh* MeshToSet) { Mesh = MeshToSet; }
	inline AMesh* GetMesh() { return Mesh; }

	inline void UpdatePosition(glm::vec3 PositionToSet) { Position = PositionToSet; }

	inline glm::vec3 GetPosition() const { return Position; };

	void Update();

};

