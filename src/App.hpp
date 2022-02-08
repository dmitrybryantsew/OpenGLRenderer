#ifndef TEMPLATEPROJECT_APP_HPP
#define TEMPLATEPROJECT_APP_HPP
#include "stdafx.hpp"
#include <iostream>
#include <vector>
#include <unordered_map>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> // translate, rotate, scale, identity
#include <glm/gtc/type_ptr.hpp>

#include "Constants.hpp"
#include "Window.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"
#include "Debug.hpp"
#include "Camera.hpp"
#include "Texture.hpp"
#include "DirectionalLight.hpp"
#include "PointLight.hpp"
#include "SpotLight.hpp"
#include <limits.h>
#include <unistd.h>
#include "Material.hpp"
//#include "assimp/Importer.hpp"
#include "Model.hpp"

namespace simple3DEngine{
    class App {
    public:
        //constructor
        App();
        ~App();
        //structs
        struct cubeChunk{
            int startIndex;
            int endIndex;
        };
        struct cubePlane{
            int startIndex;
            int endIndex;
        };
        struct cubeLine{
            int startIndex;
            int endIndex;
        };
        //functions
        void render();
        void update();
        void processInput();
        void run();
        void initialize();
        void addTexture();
        void addModel();
        void addMaterial();
        static std::string getExePath();
        void calcAverageNormals(unsigned int *indices, unsigned int indiceCount,
                                GLfloat * vertices, unsigned int verticeCount,
                                unsigned int vLength, unsigned int normalOffset);
        void CreatePlane();
//TODO rewrite all cube gen code to more effective its rly bad for now
//TODO fix cube texture map its broken
        void CreateCube(int x, int y, int z);
        cubeLine createCubeLine();
//TODO fix rotation probably camera
        cubePlane createCubePlane();
        cubeChunk createNewCubeChunk();
        void CreateShaders();
        //data
        /*std::unordered_map<std::string, Model> models;
        std::unordered_map<std::string, Texture> textures;
        std::unordered_map<std::string, Material> materials;
        std::unordered_map<std::string, PointLight> pointLights;
        std::unordered_map<std::string, SpotLight> spotLights;
        std::unordered_map<std::string, DirectionalLight> directionalLights;*/
        Window window;
        Camera camera;
        GLuint shader;
        std::vector<Mesh *> meshList;
        std::vector<Shader> shaderList;

        const GLint WIDTH = 800, HEIGHT = 600; //todo move cosntants into config
        GLfloat deltaTime = 0.0f;
        GLfloat lastTime = 0.0f;
        cubeLine myLine;
        cubePlane myPlane;
        cubeChunk myChunk;
        float currAngle = 0.0f; //todo model should contain angle
        GLuint uniformModel = 0, uniformProjection = 0, uniformView = 0,
                uniformSpecularIntensity = 0, uniformShininess = 0, uniformEyePosition = 0;
        glm::mat4 projection;
        unsigned int pointLightCount = 0;
        unsigned int spotLightCount = 0;
        // Vertex Shader
         const char *vShader = "../Shaders/shader.vert";

// Fragment Shader
         const char *fShader = "../Shaders/shader.frag";
        static const int MAX_POINT_LIGHTS = 3;
        static const int MAX_SPOT_LIGHTS = 3;
        Texture brickTexture;
        Texture groundTexture;
        Texture grassSideTexture;
        DirectionalLight dLight;
        PointLight pointLights[MAX_POINT_LIGHTS];
        SpotLight spotLights[MAX_SPOT_LIGHTS];

        Material shinyMaterial;
        Material dullMaterial;


        Model building;
        Model stanfordBunny;
        Model horse;
        Model suzanne;
        Model teapot;

        static void GLAPIENTRY  MessageCallback(GLenum source,
                             GLenum type,
                             GLuint id,
                             GLenum severity,
                             GLsizei length,
                             const GLchar *message,
                             const void *userParam);

        const float toRadians = 3.14159265f / 180.0f;







    };
}


#endif //TEMPLATEPROJECT_APP_HPP
