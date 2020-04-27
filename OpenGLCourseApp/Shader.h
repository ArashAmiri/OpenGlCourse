#pragma once

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>

#include <GL/glew.h>

class FShaderProgram
{

public:
    FShaderProgram();

    void CreateFromString(const char* vertexCode, const char* fragmentCode);

    inline GLuint GetProjectionLocation() { return uniformProjection; }
    inline GLuint GetModelLocation() { return uniformModel; }
    inline GLuint GetViewLocation() { return uniformView; }
    inline GLuint GetAmbientIntensityLocation() { return uniformAmbientIntensity; }
    inline GLuint GetAmbientColorLocation() { return uniformAmbientColor; }
    inline GLuint GetDiffuseIntensityLocation() { return uniformDiffuseIntensity; }
    inline GLuint GetDirectionLocation() { return uniformDirection;  }
    inline GLuint GetSpecularIntensityLocation() { return uniformSpeculaIntensity; }
    inline GLuint GetShininessLocation() { return uniformShininess; }
    inline GLuint GetEyePositionLocation() { return uniformEyePosition; }

    void UseShader();
    void ClearShader();
    void CreateFromFiles(const char* vertexLocation, const char* fragmentLocation);

    ~FShaderProgram();

private:
    GLuint 
        shaderProgramID, 
        uniformProjection, 
        uniformModel, 
        uniformView,
        uniformEyePosition,
        uniformSpeculaIntensity,
        uniformShininess,
        uniformAmbientIntensity, 
        uniformAmbientColor, 
        uniformDiffuseIntensity, 
        uniformDirection 
        = 0;

    void CompileShader(const char* vertexCode, const char* fragmentCode);
    void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
    std::string ReadFile(const char* fileLocation);
};

