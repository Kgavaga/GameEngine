#include "Shader.h"

const std::string GameEngine::Shader::MODEL_MATRIX_ATTRIBUTE_NAME = "model";

GameEngine::Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath)
{
    _id = _createShaderProgram(_readFile(vertexPath), _readFile(fragmentPath));
}

void GameEngine::Shader::use()
{
    glUseProgram(_id);
}

void GameEngine::Shader::setBool(const std::string& name, bool value) const
{
    glUniform1i(glGetUniformLocation(_id, name.c_str()), (int)value);
}

void GameEngine::Shader::setInt(const std::string& name, int value) const
{
    glUniform1i(glGetUniformLocation(_id, name.c_str()), value);
}

void GameEngine::Shader::setFloat(const std::string& name, float value) const
{
    glUniform1f(glGetUniformLocation(_id, name.c_str()), value);
}

void GameEngine::Shader::setMatrix4fv(const std::string& name, float* values, bool transpose) const
{
    glUniformMatrix4fv(glGetUniformLocation(_id, name.c_str()), 1, (transpose) ? GL_TRUE : GL_FALSE, values);
}

unsigned int GameEngine::Shader::getId() const
{
    return _id;
}

std::string GameEngine::Shader::_readFile(const std::string& path) const
{
    std::ifstream shaderFile;
    // ensure ifstream objects can throw exceptions:
    shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        shaderFile.open(path);
        std::stringstream shaderStream;
        // read file's buffer contents into streams
        shaderStream << shaderFile.rdbuf();
        // close file handlers
        shaderFile.close();
        // convert stream into string
        return shaderStream.str();
    }
    catch (std::ifstream::failure& e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: " << e.what() << std::endl;
        exit(1);
    }
}

unsigned int GameEngine::Shader::_createShaderProgram(const std::string& vertexShaderSource, const std::string& fragmentShaderSource) const
{
    unsigned int vertexShader = _compileShader(GL_VERTEX_SHADER, vertexShaderSource);
    unsigned int fragmentShader = _compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
    // Create a shader program which links all shaders together
    unsigned int shaderProgram = glCreateProgram();

    // Attach the shaders to the program
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    // And linkt the shaders to the program
    glLinkProgram(shaderProgram);

    // Validate the program
    glValidateProgram(shaderProgram);
    // Error Handling
    int result;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &result);
    if (result == GL_FALSE)
    {
        char message[512];
        glGetProgramInfoLog(shaderProgram, 512, NULL, message);
        std::cout << "Failed to validate the shader program.\n";
        std::cout << message << "\n";
        exit(1);
    }

    // Delete shaders after use
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return shaderProgram;
}

unsigned int GameEngine::Shader::_compileShader(unsigned int shaderType, const std::string& shaderSource) const
{
    // Create a shader object
    unsigned int id = glCreateShader(shaderType);
    // Attach the source code of the shader
    const char* shaderCharString = shaderSource.c_str();
    glShaderSource(id, 1, &shaderCharString, NULL);
    // Compile the shader
    glCompileShader(id);

    // Error Handling
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        char message[512];
        glGetShaderInfoLog(id, 512, NULL, message);
        std::cout << "Failed to handle " << ((shaderType == GL_VERTEX_SHADER) ? "GL_VERTEX_SHADER" : "GL_FRAGMENT_SHADER") << "\n";
        std::cout << message << "\n";
        glDeleteShader(id);
        exit(1);
    }
    return id;
}
