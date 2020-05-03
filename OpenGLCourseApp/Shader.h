#pragma once

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <unordered_map>

#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"

#include "CommonValues.h"

class FShaderProgram
{

public:
    FShaderProgram();

    void SetDirectionalLight(ADirectionalLight* DirectionalLightToSet);
    void SetPointLight(APointLight* PointLightToSet, unsigned int LightCount);
    void SetSpotLight(ASpotLight* SpotLightToSet, unsigned int LightCount);

    void CreateFromString(const char* vertexCode, const char* fragmentCode);

    inline GLuint GetProjectionLocation() { return uniformProjection; }
    inline GLuint GetModelLocation() { return uniformModel; }
    inline GLuint GetViewLocation() { return uniformView; }
    inline GLuint GetAmbientIntensityLocation() { return UniformDirectionalLight.UniformAmbientIntensity; }
    inline GLuint GetAmbientColorLocation() { return UniformDirectionalLight.UniformColor; }
    inline GLuint GetDiffuseIntensityLocation() { return UniformDirectionalLight.UniformDiffuseIntensity; }
    inline GLuint GetDirectionLocation() { return UniformDirectionalLight.UniformDirection;  }
    inline GLuint GetSpecularIntensityLocation() { return uniformSpeculaIntensity; }
    inline GLuint GetShininessLocation() { return uniformShininess; }
    inline GLuint GetEyePositionLocation() { return uniformEyePosition; }

    void UseShader();
    void ClearShader();
    void CreateFromFiles(const char* vertexLocation, const char* fragmentLocation);

    ~FShaderProgram();

    void UpadeModelUniform(glm::mat4 model);

private:

    int PointLightCount = 0;
    int SpotLightCount = 0;

    GLuint
        shaderProgramID = 0,
        uniformProjection = 0,
        uniformModel = 0,
        uniformView = 0,
        uniformEyePosition = 0,
        uniformSpeculaIntensity = 0,
        uniformShininess = 0,
        UniformPointLightCount = 0,
        UniformSpotLightCount = 0;

    struct LightUniformContainer {
        GLuint UniformColor;
        GLuint UniformAmbientIntensity;
        GLuint UniformDiffuseIntensity;
        GLuint UniformDirection;    
    } UniformDirectionalLight;
    
    struct PointLightUniformContainer : LightUniformContainer {    
        GLuint UniformPosition;
        GLuint UniformExponent;
        GLuint UniformLinear;
        GLuint UniformConstant;
    } UniformPointLight[MAX_POINT_LIGHTS];

    struct SpotLightUniformContainer : PointLightUniformContainer {
        GLuint UniformEdge;
    } UniformSpotLight[MAX_SPOT_LIGHTS];

    mutable std::unordered_map<std::string, GLuint> UniformCache;

    void CompileShader(const char* vertexCode, const char* fragmentCode);
    void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
    std::string ReadFile(const char* fileLocation);
    
    GLuint GetUniformByCache(std::string Name) const;

};

