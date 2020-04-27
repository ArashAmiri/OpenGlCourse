#pragma once

#include "Transform.h"

class AActor
{

protected:

	class AMesh* Mesh;
	class AMaterial* Material;
	class ATexture* Texture;
	class FShaderProgram* ShaderProgram;

	struct FTransform Transform = FTransform();
	float Speed = 0;

public:

	AActor(AMesh* Mesh, ATexture* Texture, AMaterial* Material, FTransform Transform, FShaderProgram* ShaderProgram);

	inline void SetMesh(AMesh* MeshToSet) { Mesh = MeshToSet; }
	inline AMesh* GetMesh() { return Mesh; }
	inline FTransform GetTransform() { return this->Transform; }
	inline void SetTransform(FTransform TransformToSet) { this->Transform = Transform; }

	void Update();

};

