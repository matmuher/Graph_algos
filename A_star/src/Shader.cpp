#include <Shader.hpp>

GLuint Shader::getUniform(const char* uniformName)
{
    return glGetUniformLocation(ID, uniformName);
}

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
    GLuint vertexShader = createShader(vertexPath, GL_VERTEX_SHADER);
    GLuint fragmentShader = createShader(fragmentPath, GL_FRAGMENT_SHADER);
    glCheckError();

    ID = createProgram(vertexShader, fragmentShader);
    glCheckError();
}

GLuint Shader::createProgram(GLuint vertexShader, GLuint fragmentShader)
{
    GLuint shaderProgram = glCreateProgram();
    glCheckError();

    glAttachShader(shaderProgram, vertexShader);

    glCheckError();

    glAttachShader(shaderProgram, fragmentShader);

    glCheckError();

    glLinkProgram(shaderProgram);
    glCheckError();

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, LogLen, NULL, logInfo);
        printf("[link shader program error] %s\n", logInfo);
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    shaders.clear();

    return shaderProgram;
}

GLuint Shader::createShader(const std::string& shaderPath, GLenum shader_type)
{
    const char* shaderSrc = readShader(shaderPath);
    GLuint shaderObj = glCreateShader(shader_type);
    glShaderSource(shaderObj, 1, &shaderSrc, NULL);
    glCompileShader(shaderObj);
    
    glGetShaderiv(shaderObj, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(shaderObj, LogLen, NULL, logInfo);
        printf("[compile error: %s] %s\n", shaderPath.c_str(), logInfo);
    }

    return shaderObj;
}

void Shader::use()
{
    glUseProgram(ID);
}

void Shader::setFloat(const char* uniformName, float val)
{
    GLuint uniformLoc = glGetUniformLocation(ID, uniformName);
    glUniform1f(uniformLoc, val);
}

void Shader::setInt(const char* uniformName, int val)
{
    glCheckError();

    // std::cerr << "uniform name: " << uniformName << '\n';

    GLuint uniformLoc = glGetUniformLocation(ID, uniformName);
    
    // std::cerr << "uniformLoc: " << uniformLoc << '\n';

    glCheckError();
    glUniform1i(uniformLoc, val);

    glCheckError();
}

void Shader::setMat4(const char* uniformName, const glm::mat4& mat)
{
    GLuint uniformLoc = getUniform(uniformName);
    glUniformMatrix4fv(uniformLoc, 1, GL_FALSE, glm::value_ptr(mat));
}

void Shader::setVec3(const char* uniformName, const glm::vec3& vec)
{
    GLuint uniformLoc = getUniform(uniformName);
    glUniform3f(uniformLoc, vec.x, vec.y, vec.z);
}

const char* Shader::readShader(const std::string& filename)
{
    std::ifstream ifile(filename);

    if (!ifile.is_open())
    {
        printf("[error: read shader] %s\n", filename.c_str());
    }

    std::stringstream buffer;

    buffer << ifile.rdbuf();
    
    shaders.push_back(buffer.str());

    return shaders.back().c_str();
}
