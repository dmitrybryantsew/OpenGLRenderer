#include "Shader.hpp"
#include <iostream>
Shader::Shader()
{
	shader = 0, uniformModel = 0, uniformProjection = 0, pointLightCount = 0, spotLightCount = 0;
}

void Shader::CreateFromFiles(const char *vShader, const char *fShader)
{
	std::string vShaderCode = readShaderCodeFromFile(vShader);
	std::string fShaderCode = readShaderCodeFromFile(fShader);
	std::cout << "shader code!  \n";
    std::cout << vShaderCode << std::endl;
    std::cout << fShaderCode << std::endl;
	compileShaders(vShaderCode.c_str(), fShaderCode.c_str());
}

Shader::~Shader()
{
}

std::string Shader::readShaderCodeFromFile(const char *shaderPath)
{
	std::string code;
	std::ifstream shaderFile;
	shaderFile.exceptions(std::ifstream::badbit);
	try
	{
		// Открываем файлы
		shaderFile.open(shaderPath);
		if (shaderFile.fail())
		{
			std::cerr << "Error!" << std::endl;
		}
		std::stringstream shaderStream;
		// Считываем данные в потоки
		shaderStream << shaderFile.rdbuf();
		// Закрываем файлы
		shaderFile.close();
		// Преобразовываем потоки в массив GLchar
		code = shaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "Shader file " << shaderPath << " cannot be read" << std::endl;
	}

	return code;
}

void Shader::addShader(GLuint theProgram, const char *shaderCode, GLenum shaderType)
{
	GLuint theShader = glCreateShader(shaderType);

	const GLchar *theCode[1];
	theCode[0] = shaderCode;

	GLint codeLength[1];
	codeLength[0] = strlen(shaderCode);

	glShaderSource(theShader, 1, theCode, codeLength);
	glCompileShader(theShader);

	GLint result = 0;
	GLchar errLog[1024] = {0};

	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);

	if (!result)
	{
		glGetShaderInfoLog(theShader, sizeof(errLog), NULL, errLog);
		std::cerr << "Error compiling the " << shaderType << " shader: '" << errLog << "'\n";
		return;
	}

	glAttachShader(theProgram, theShader);
}

void Shader::compileShaders(const char *vShaderCode, const char *fShaderCode)
{
	shader = glCreateProgram();

	if (!shader)
	{
		std::cerr << "Error creating shader program\n";
		return;
	}

	addShader(shader, vShaderCode, GL_VERTEX_SHADER);
	addShader(shader, fShaderCode, GL_FRAGMENT_SHADER);

	GLint result = 0;
	GLchar errLog[1024] = {0};

	glLinkProgram(shader);
	glGetProgramiv(shader, GL_LINK_STATUS, &result);

	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(errLog), NULL, errLog);
		std::cerr << "Error linking program: '" << errLog << "'\n";
		return;
	}

	glValidateProgram(shader);
	glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);

	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(errLog), NULL, errLog);
		std::cerr << "Error validating program: '" << errLog << "'\n";
		return;
	}

	uniformModel = glGetUniformLocation(shader, "model");
	uniformProjection = glGetUniformLocation(shader, "projection");
	uniformView = glGetUniformLocation(shader, "view");
	uniformDirectionalLight.uniformColor = glGetUniformLocation(shader, "directionalLight.base.color");
	uniformDirectionalLight.uniformAmbientIntensity = glGetUniformLocation(shader, "directionalLight.base.ambientIntensity");
	uniformDirectionalLight.uniformDiffuseIntensity = glGetUniformLocation(shader, "directionalLight.base.diffuseIntensity");
	uniformDirectionalLight.uniformDirection = glGetUniformLocation(shader, "directionalLight.direction");
	uniformSpecularIntensity = glGetUniformLocation(shader, "material.specularIntensity");
	uniformShininess = glGetUniformLocation(shader, "material.shininess");
	uniformEyePosition = glGetUniformLocation(shader, "eyePosition");

	uniformPointLightCount = glGetUniformLocation(shader, "pointLightCount");

	for (size_t i = 0; i < MAX_POINT_LIGHTS; ++i)
    {
	    char locBuff[100] = {'\0'};

        snprintf(locBuff, sizeof (locBuff), "pointLights[%d].base.color", i);
        uniformPointLight[i].uniformColor = glGetUniformLocation(shader, locBuff);

        snprintf(locBuff, sizeof (locBuff), "pointLights[%d].base.ambientIntensity", i);
        uniformPointLight[i].uniformAmbientIntensity = glGetUniformLocation(shader, locBuff);

        snprintf(locBuff, sizeof (locBuff), "pointLights[%d].base.diffuseIntensity", i);
        uniformPointLight[i].uniformDiffuseIntensity = glGetUniformLocation(shader, locBuff);

        snprintf(locBuff, sizeof (locBuff), "pointLights[%d].position", i);
        uniformPointLight[i].uniformPosition = glGetUniformLocation(shader, locBuff);

        snprintf(locBuff, sizeof (locBuff), "pointLights[%d].constant", i);
        uniformPointLight[i].uniformConstant = glGetUniformLocation(shader, locBuff);

        snprintf(locBuff, sizeof (locBuff), "pointLights[%d].linear", i);
        uniformPointLight[i].uniformLinear = glGetUniformLocation(shader, locBuff);

        snprintf(locBuff, sizeof (locBuff), "pointLights[%d].exponent", i);
        uniformPointLight[i].uniformExponent = glGetUniformLocation(shader, locBuff);
    }
    uniformSpotLightCount = glGetUniformLocation(shader, "spotLightCount");

    for (size_t i = 0; i < MAX_SPOT_LIGHTS; ++i)
    {
        char locBuff[100] = {'\0'};

        snprintf(locBuff, sizeof (locBuff), "spotLights[%d].base.base.color", i);
        uniformSpotLight[i].uniformColor = glGetUniformLocation(shader, locBuff);

        snprintf(locBuff, sizeof (locBuff), "spotLights[%d].base.base.ambientIntensity", i);
        uniformSpotLight[i].uniformAmbientIntensity = glGetUniformLocation(shader, locBuff);

        snprintf(locBuff, sizeof (locBuff), "spotLights[%d].base.base.diffuseIntensity", i);
        uniformSpotLight[i].uniformDiffuseIntensity = glGetUniformLocation(shader, locBuff);

        snprintf(locBuff, sizeof (locBuff), "spotLights[%d].base.position", i);
        uniformSpotLight[i].uniformPosition = glGetUniformLocation(shader, locBuff);

        snprintf(locBuff, sizeof (locBuff), "spotLights[%d].base.constant", i);
        uniformSpotLight[i].uniformConstant = glGetUniformLocation(shader, locBuff);

        snprintf(locBuff, sizeof (locBuff), "spotLights[%d].base.linear", i);
        uniformSpotLight[i].uniformLinear = glGetUniformLocation(shader, locBuff);

        snprintf(locBuff, sizeof (locBuff), "spotLights[%d].base.exponent", i);
        uniformSpotLight[i].uniformExponent = glGetUniformLocation(shader, locBuff);

        snprintf(locBuff, sizeof (locBuff), "spotLights[%d].direction", i);
        uniformSpotLight[i].uniformDirection = glGetUniformLocation(shader, locBuff);

        snprintf(locBuff, sizeof (locBuff), "spotLights[%d].edge", i);
        uniformSpotLight[i].uniformEdge = glGetUniformLocation(shader, locBuff);
    }
}

GLuint Shader::GetViewLocation() {
    return uniformView;
}

GLuint Shader::getUniformEyePosition() const {
    return uniformEyePosition;
}

GLuint Shader::getUniformSpecularIntensity() const {
    return uniformSpecularIntensity;
}

GLuint Shader::getUniformShininess() const {
    return uniformShininess;
}

void Shader::setDirectionalLight(DirectionalLight *dLight) {
    dLight->useLight(uniformDirectionalLight.uniformAmbientIntensity,
                     uniformDirectionalLight.uniformColor,
                     uniformDirectionalLight.uniformDiffuseIntensity,
                     uniformDirectionalLight.uniformDirection);
}

void Shader::setPointLights(PointLight *pLight, unsigned int lightCount) {
    if (lightCount > MAX_POINT_LIGHTS) lightCount = MAX_POINT_LIGHTS;

    glUniform1i(uniformPointLightCount, lightCount);

    for(size_t i = 0; i < lightCount; i++){
        pLight[i].useLight(uniformPointLight[i].uniformAmbientIntensity, uniformPointLight[i].uniformColor,
                           uniformPointLight[i].uniformDiffuseIntensity, uniformPointLight[i].uniformPosition,
                           uniformPointLight[i].uniformConstant, uniformPointLight[i].uniformLinear,
                           uniformPointLight[i].uniformExponent);
    }
}

void Shader::setSpotLights(SpotLight *sLight, unsigned int lightCount) {
    if (lightCount > MAX_POINT_LIGHTS) lightCount = MAX_POINT_LIGHTS;

    glUniform1i(uniformSpotLightCount, lightCount);

    for(size_t i = 0; i < lightCount; i++){
        sLight[i].useLight(uniformSpotLight[i].uniformAmbientIntensity, uniformSpotLight[i].uniformColor,
                           uniformSpotLight[i].uniformDiffuseIntensity, uniformSpotLight[i].uniformPosition,
                           uniformSpotLight[i].uniformConstant, uniformSpotLight[i].uniformLinear,
                           uniformSpotLight[i].uniformExponent,
                           uniformSpotLight[i].uniformDirection, uniformSpotLight[i].uniformEdge);
    }
}
