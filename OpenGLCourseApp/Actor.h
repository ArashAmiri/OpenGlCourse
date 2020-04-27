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

	inline virtual void HandleUserInput(bool* keys, float DeltaTime) {};
	inline void SetMesh(AMesh* MeshToSet) { Mesh = MeshToSet; }
	inline AMesh* GetMesh() { return Mesh; }
	
	void Update();

};

