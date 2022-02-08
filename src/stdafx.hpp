//
// Created by dmitr on 11/27/2021.
//
#include <iostream>
#include <vector>
#include <memory>
#include <unordered_map>
#include <array>
#include <string>
#include <cstring>
#include <fstream>
#include <sstream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> // translate, rotate, scale, identity
#include <glm/gtc/type_ptr.hpp>

#include <limits.h>
#include <stdint.h>
#include <assert.h>

//#include <unistd.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <boost/algorithm/string.hpp>