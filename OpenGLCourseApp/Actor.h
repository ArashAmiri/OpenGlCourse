#pragma once

#include "glm/glm.hpp"



class AActor
{

protected:

	class AMesh* Mesh;
	class AMaterial* Material;
	class ATexture* Texture;
	class FShaderProgram* ShaderProgram;

	glm::vec3 Position;

	float RotationFactor = 0.0f;

	glm::vec3 Rotation = glm::vec3(0.0f);

	float Speed = 0;

	bool bIsRotating = true;

	glm::vec3 RotationVector = glm::vec3(0.0f);

public:

	AActor();

	AActor(AMesh* Mesh, ATexture* Texture, AMaterial* Material, glm::vec3 Position, FShaderProgram* ShaderProgram);

	inline void SetMesh(AMesh* MeshToSet) { Mesh = MeshToSet; }
	inline AMesh* GetMesh() { return Mesh; }

	inline void UpdatePosition(glm::vec3 PositionToSet) { Position = PositionToSet; }

	inline glm::vec3 GetPosition() const { return Position; };

	void Update(float DeltaTime);

	void Rotate(glm::vec3 Rotation);

	inline void SetIsRotating(bool IsRotating) { bIsRotating = IsRotating; }
};

