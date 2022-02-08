//
// Created by Taily on 9/4/2021.
//

#include "App.hpp"
namespace simple3DEngine{
    void App::render() {
        GLfloat now = glfwGetTime();
        deltaTime = now - lastTime;
        lastTime = now;
        glfwPollEvents();
        camera.keyControl(window.getKeys(), deltaTime);
        camera.mouseControl(window.getXChange(), window.getYChange());

        GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
        GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

        shaderList[0].UseShader();
        uniformModel = shaderList[0].GetModelLocation();
        uniformProjection = shaderList[0].GetProjectionLocation();
        uniformView = shaderList[0].GetViewLocation();

        uniformEyePosition = shaderList[0].getUniformEyePosition();
        uniformSpecularIntensity = shaderList[0].getUniformSpecularIntensity();
        uniformShininess = shaderList[0].getUniformShininess();

        glm::vec3 lowerLight = camera.getPosition();
        lowerLight.y -=0.3f;

        spotLights[0].setFlashlightPosition(lowerLight, camera.getCameraDirection());
        shaderList[0].setDirectionalLight(&dLight);
        shaderList[0].setPointLights(pointLights, pointLightCount);
        shaderList[0].setSpotLights(spotLights, spotLightCount);

        pointLights[1].changePosition(0.1f, 0.f, 0.f);

        //plane
        glm::mat4 model = glm::mat4(1.0f);
        GLCall(glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection)));
        GLCall(glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix())));
        glUniform3f(uniformEyePosition, camera.getPosition().x, camera.getPosition().y, camera.getPosition().z);
        GLCall(glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model)));
        groundTexture.useTexture();
        shinyMaterial.useMaterial(uniformSpecularIntensity, uniformShininess);
        meshList[0]->RenderMesh();

        //cubes
        for(int i =myLine.startIndex; i < myLine.endIndex; ++i) {
            model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(30.5f, 20.5f, 20.0f));
            GLCall(glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model)));
            GLCall(glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection)));

            grassSideTexture.useTexture();
            shinyMaterial.useMaterial(uniformSpecularIntensity, uniformShininess);
            meshList[i]->RenderMesh();
        }

        for(int i =myPlane.startIndex; i < myPlane.endIndex; ++i) {
            model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(30.5f, 20.5f, 30.0f));
            GLCall(glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model)));
            GLCall(glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection)));

            grassSideTexture.useTexture();
            shinyMaterial.useMaterial(uniformSpecularIntensity, uniformShininess);
            meshList[i]->RenderMesh();
        }

        for(int i = myChunk.startIndex; i < myChunk.endIndex; ++i) {
            model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(40.5f, 40.5f, 40.0f));
            GLCall(glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model)));
            GLCall(glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection)));

            grassSideTexture.useTexture();
            shinyMaterial.useMaterial(uniformSpecularIntensity, uniformShininess);
            meshList[i]->RenderMesh();
        }

        //building
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.5f , 10.5f, -2.0f));
        GLCall(glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model)));
        GLCall(glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection)));

        dullMaterial.useMaterial(uniformSpecularIntensity, uniformShininess);
        building.renderModel();


        //bunny
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(20.5f , 20.5f, -2.0f));
        model = glm::scale(model, glm::vec3(10.f, 10.f, 10.f));
        GLCall(glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model)));
        GLCall(glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection)));

        dullMaterial.useMaterial(uniformSpecularIntensity, uniformShininess);
        stanfordBunny.renderModel();

        //horse
        if (currAngle>180){
            currAngle = -180.;

        }
        currAngle++;
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(50.5f , 20.5f, -2.0f));
        model = glm::rotate(model, currAngle, glm::vec3(1, 0, 0));
        model = glm::scale(model, glm::vec3(50.f, 50.f, 50.f));
        GLCall(glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model)));
        GLCall(glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection)));

        dullMaterial.useMaterial(uniformSpecularIntensity, uniformShininess);
        horse.renderModel();

        //teapot
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(20.5f , 50.5f, -2.0f));
        model = glm::scale(model, glm::vec3(2.f, 2.f, 2.f));
        GLCall(glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model)));
        GLCall(glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection)));

        dullMaterial.useMaterial(uniformSpecularIntensity, uniformShininess);
        teapot.renderModel();

        //suzanne
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(20.5f , 20.5f, -50.0f));
        model = glm::scale(model, glm::vec3(5.f, 5.f, 5.f));
        GLCall(glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model)));
        GLCall(glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection)));

        dullMaterial.useMaterial(uniformSpecularIntensity, uniformShininess);
        suzanne.renderModel();
        glUseProgram(0);

        window.swapBuffers();;
    }

    void App::update() {

    }

    void App::processInput() {

    }

    void App::run() {

        initialize();

        while(window.isOpen()){
            render();
            update();
        }
    }

    std::string App::getExePath() {
        char result[PATH_MAX];
        ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
        return std::string(result, (count > 0) ? count : 0);
    }

    void App::initialize() {

        this->camera = Camera(glm::vec3(2.0f, 1.0f,2.0f),
                              glm::vec3(0.0f,1.0f,0.0f),
                              0.0f, 90.0f, 5.0f, 1.0f);
        std::cout << getExePath() << std::endl;
        window.initialize();
        CreatePlane();
        CreateShaders();
        myLine = createCubeLine();
        myPlane = createCubePlane();
        myChunk = createNewCubeChunk();
        grassSideTexture = Texture("../Textures/grass_block_side1.png");
        grassSideTexture.loadTextureA();
        brickTexture = Texture("../Textures/bricks.png");
        brickTexture.loadTextureA();
        groundTexture = Texture("../Textures/ground2.png");
        groundTexture.loadTextureA();

        shinyMaterial = Material(1.0, 32);
        dullMaterial = Material(0.3, 4);

        building = Model();
        building.loadModel("../Models/Build.obj");

        stanfordBunny = Model();
        stanfordBunny.loadModel("../Models/stanford-bunny.obj");

        horse = Model();
        horse.loadModel("../Models/horse.obj");

        teapot = Model();
        teapot.loadModel("../Models/teapot.obj");

        suzanne = Model();
        suzanne.loadModel("../Models/suzanne.obj");

        dLight = DirectionalLight(1.0f, 1.0f, 1.0f, 0.3f,
                                  0.8f, 0.0f, 0.0f, -1.0f);

        pointLights[0] = PointLight(0.0f, 0.0f, 1.0f,
                                    0.1f, 1.0f,
                                    -4.0f, 4.0f, 10.0f,
                                    0.3f, 0.2f, 0.001f);
        pointLightCount++;
        pointLights[1] = PointLight(1.0f, 0.0f, 0.0f,
                                    0.1f, 1.0f,
                                    -40.0f, 6.0f, 10.0f,
                                    0.3f, 0.2f, 0.1f);
        pointLightCount++;

        ;
        spotLights[0] = SpotLight(1.0f, 1.0f, 1.0f,
                                  0.1f, 1.0f,
                                  -0.0f, 6.0f, 10.0f,
                                  0.0f, -1.0f, 0.0f,
                                  0.9f, 0.0f, 0.0f,
                                  20.0f);
        spotLightCount++;
        spotLights[1] = SpotLight(1.0f, 1.0f, 1.0f,
                                  0.1f, 1.0f,
                                  -0.0f, 6.0f, 10.0f,
                                  -100.0f, -1.0f, 0.0f,
                                  1.0f, 0.0f, 0.0f,
                                  20.0f);
        spotLightCount++;
        // During init, enable debug output
        GLCall(glEnable(GL_DEBUG_OUTPUT));
        GLCall(glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS));
        glDebugMessageCallback(MessageCallback, 0);
        projection = glm::perspective(45.0f, (GLfloat)window.getBufferWidth() / (GLfloat)window.getBufferHeight(), 0.1f, 100.0f);
        currAngle = -75.;

    }



    App::App() {


    }

    void App::calcAverageNormals(unsigned int *indices, unsigned int indiceCount, GLfloat *vertices,
                                 unsigned int verticeCount, unsigned int vLength, unsigned int normalOffset) {
        for(size_t i = 0; i < indiceCount; i+=3)
        {
            unsigned int in0 = indices[i] * vLength;
            unsigned int in1 = indices[i + 1] * vLength;
            unsigned int in2 = indices[i + 2] * vLength;

            glm::vec3 v1(vertices[in1] - vertices[in0],
                         vertices[in1 + 1] - vertices[in0 + 1],
                         vertices[in1 + 2] - vertices[in0 + 2]);

            glm::vec3 v2(vertices[in2] - vertices[in0],
                         vertices[in2 + 1] - vertices[in0 + 1],
                         vertices[in2 + 2] - vertices[in0 + 2]);

            glm::vec3 normal = glm::cross(v1, v2);
            normal = glm::normalize(normal);

            in0 += normalOffset; in1 +=normalOffset; in2 += normalOffset;
            vertices[in0] += normal.x; vertices[in0 + 1] += normal.y; vertices [in0 + 2] += normal.z;
            vertices[in1] += normal.x; vertices[in1 + 1] += normal.y; vertices [in1 + 2] += normal.z;
            vertices[in2] += normal.x; vertices[in2 + 1] += normal.y; vertices [in2 + 2] += normal.z;
        }

        for (size_t i = 0; i < verticeCount / vLength; ++i)
        {
            unsigned int nOffset = i * vLength + normalOffset;
            glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
            vec = glm::normalize(vec);
            std::cout << "\n norm vec is " << vec.x << " " << vec.y << " " << vec.z  << "length is " << nOffset<< std::endl;
            vertices[nOffset] = vec.x; vertices[nOffset + 1] = vec.y; vertices[nOffset + 2] = vec.z;
        }
    }

    void App::CreatePlane() {
        unsigned int indices[] = {
                0, 1, 2,
                2, 3, 0,
        };

        GLfloat vertices[] = {
                -50.0f, 5.0f, -100.0f, 0.0f, 0.0f,0.0f, -1.0f, 0.0f,
                -50.0f, 5.0f, 100.0f, 50.0f, 0.0f, 0.0f, -1.0f, 0.0f,
                50.0f, 5.0f, 100.0f, 0.0f, 50.0f, 0.0f, -1.0f, 0.0f,
                50.0f, 5.0f, -100.0f, 50.0f, 50.0f, 0.0f, -1.0f, 0.0f, };

        //calcAverageNormals(indices, 6, vertices, 32, 8, 5);

        Mesh *obj3 = new Mesh();
        obj3->CreateMesh(vertices, indices, 32, 6);
        meshList.push_back(obj3);

    }

    void App::CreateCube(int x, int y, int z) {
        unsigned int indices[] = {
                0, 1, 2,
                2, 3, 0,
                12, 8, 11,
                11, 15, 12,
                4, 5, 6,
                6, 7, 4,
                13, 14, 10,
                10, 9, 13,
                12, 5, 1,
                1, 8, 4,
                6, 2, 3,
                3, 7, 6,
        };

        GLfloat vertices[] = {
                -1.0f + x, 1.0f + y, 1.0f + z, 0.0f, 0.0f,0.0f, -1.0f, 0.0f, //0
                1.0f + x, 1.0f + y, 1.0f + z, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f, //1
                1.0f + x, -1.0f + y, 1.0f + z, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f, //2
                -1.0f + x, -1.0f + y, 1.0f + z, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, //3
                -1.0f + x, 1.0f + y, -1.0f + z, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, //4
                1.0f + x, 1.0f + y, -1.0f + z, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f, //5
                1.0f + x, -1.0f + y, -1.0f + z, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f, //6
                -1.0f + x, -1.0f + y, -1.0f + z, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, //7
                -1.0f + x, 1.0f + y, 1.0f + z, 1.0f, 0.0f,0.0f, -1.0f, 0.0f, //8
                1.0f + x, 1.0f + y, 1.0f + z, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f, //9
                1.0f + x, -1.0f + y, 1.0f + z, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f, //10
                -1.0f + x, -1.0f + y, 1.0f + z, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f, //11
                -1.0f + x, 1.0f + y, -1.0f + z, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, //12
                1.0f + x, 1.0f + y, -1.0f + z, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, //13
                1.0f + x, -1.0f + y, -1.0f + z, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, //14
                -1.0f + x, -1.0f + y, -1.0f + z, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, //15
        };

        //calcAverageNormals(indices, 6, vertices, 32, 8, 5);

        Mesh *obj4 = new Mesh();
        obj4->CreateMesh(vertices, indices, 128, 36); //todo redo - inefficient memory usage
        meshList.push_back(obj4);


    }

    App::cubeLine App::createCubeLine() {
        cubeLine newLine;
        newLine.startIndex = meshList.size();
        for(int i = 0; i < 10; ++i)
        {
            CreateCube(i*2, 0, 0);
        }
        newLine.endIndex = newLine.startIndex + 10;
        return newLine;;
    }

    App::cubePlane App::createCubePlane() {
        cubePlane newPlane;
        newPlane.startIndex = meshList.size();
        for(int i = 0; i < 10; ++i)
        {
            for(int j =0; j < 10; ++j)
            {
                CreateCube(i*2, j*2, 0);
            }
        }
        newPlane.endIndex = newPlane.startIndex + 100;
        return newPlane;
    }

    App::cubeChunk App::createNewCubeChunk() {
        cubeChunk newChunk;
        newChunk.startIndex = meshList.size();
        for(int i = 0; i < 6; ++i)
        {
            for(int j =0; j < 6; ++j)
            {
                for (int k = 0; k < 6; ++k)
                {
                    CreateCube(i*2, j*2, k*2);
                }
            }
        }
        newChunk.endIndex = newChunk.startIndex + 6*6*6;

        return newChunk;
    }

    void App::CreateShaders() {
        Shader *shader1 = new Shader();
        shader1->CreateFromFiles(vShader, fShader);
        shaderList.push_back(*shader1);
    }

    void
    App::MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message,
                         const void *userParam) {
        fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
                (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
                type, severity, message);

    }

    App::~App() {

        window.closeWindow();
    }


}
