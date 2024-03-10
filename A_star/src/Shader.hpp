#pragma once

#include <glad/glad.h>
#include <string>
#include <stdlib.h>
#include <sstream>
#include <fstream>
#include <vector>
#include <debug.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
private:

    std::vector<std::string> shaders; 

    const char* readShader(const std::string& shaderPath);

    GLuint createShader(const std::string& shaderPath, GLenum shader_type);

    enum{LogLen = 512};

    char logInfo[LogLen] = {};
    
    int success = 0;

    GLuint createProgram(GLuint vertexShader, GLuint fragmentShader);

    GLuint getUniform(const char* uniformName);

public:

    GLuint ID;

    Shader(const char* vertexPath, const char* fragmentPath);

    void use();

    void setFloat(const char* uniformName, float val);

    void setInt(const char* uniformName, int val);

    void setMat4(const char* uniformName, const glm::mat4& mat);

    void setVec3(const char* uniformName, const glm::vec3& vec);
};
