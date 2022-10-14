#pragma once

#include <glad/glad.h> // include glad to get all the required OpenGL headers

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

namespace GameEngine {
	class Shader {
    public:
        static const std::string MODEL_MATRIX_ATTRIBUTE_NAME;

        Shader(const std::string& vertexPath, const std::string& fragmentPath);
        void use();
        void setBool(const std::string& name, bool value) const;
        void setInt(const std::string& name, int value) const;
        void setFloat(const std::string& name, float value) const;
        void setMatrix4fv(const std::string& name, float* values, bool transpose) const;
        unsigned int getId() const;

    private:
        unsigned int _id;

        std::string _readFile(const std::string& path) const;
        unsigned int _createShaderProgram(const std::string& vertexShaderSource, const std::string& fragmentShaderSource) const;
        unsigned int _compileShader(unsigned int shaderType, const std::string& shaderSource) const;

	};
}