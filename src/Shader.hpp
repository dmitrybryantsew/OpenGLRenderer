#pragma once
#include <cstring>
#include <fstream>
#include <sstream>
#include <iostream>
#include <GL/glew.h>

#include "Constants.hpp"

#include "DirectionalLight.hpp"
#include "PointLight.hpp"
#include "SpotLight.hpp"
class Shader
{
public:
	Shader();
	void CreateFromFiles(const char *vShader, const char *fShader);
	void UseShader() { glUseProgram(this->shader); }
	GLuint GetModelLocation() { return this->uniformModel; }
	GLuint GetProjectionLocation() { return this->uniformProjection; }
	GLuint GetViewLocation();
	void setDirectionalLight(DirectionalLight * dLight);
	void setPointLights(PointLight* pLight, unsigned  int lightCount);
	void setSpotLights(SpotLight* sLight, unsigned int lightCount);
	~Shader();
public:
    GLuint getUniformEyePosition() const;
    GLuint getUniformSpecularIntensity() const;
    GLuint getUniformShininess() const;

private:
	GLuint shader, uniformModel, uniformProjection, uniformView, uniformEyePosition,
	       uniformSpecularIntensity, uniformShininess;
	struct {
	    GLuint uniformColor;
	    GLuint uniformAmbientIntensity;
	    GLuint uniformDiffuseIntensity;

	    GLuint uniformDirection;
	} uniformDirectionalLight;

    struct {
        GLuint uniformColor;
        GLuint uniformAmbientIntensity;
        GLuint uniformDiffuseIntensity;

        GLuint uniformPosition;
        GLuint uniformConstant;
        GLuint uniformLinear;
        GLuint uniformExponent;
    } uniformPointLight[MAX_POINT_LIGHTS];

    struct {
        GLuint uniformColor;
        GLuint uniformAmbientIntensity;
        GLuint uniformDiffuseIntensity;

        GLuint uniformPosition;
        GLuint uniformConstant;
        GLuint uniformLinear;
        GLuint uniformExponent;

        GLuint uniformDirection;
        GLuint uniformEdge;
    } uniformSpotLight[MAX_SPOT_LIGHTS];
private:
    int pointLightCount;
    int spotLightCount;
    GLuint uniformPointLightCount;
    GLuint uniformSpotLightCount;
    std::string readShaderCodeFromFile(const char *shaderPath);
	void addShader(GLuint theProgram, const char *shaderCode, GLenum shaderType);
	void compileShaders(const char *vShaderCode, const char *fShaderCode);
};