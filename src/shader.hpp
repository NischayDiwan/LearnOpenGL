#ifndef SHADER_HPP
#define SHADER_HPP

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {

public:
    unsigned int id;

    Shader(const char *vertexPath, const char *fragmentPath) {
        unsigned int vertexShader, fragmentShader;
        vertexShader = readAndCompileShader(vertexPath, GL_VERTEX_SHADER);
        fragmentShader = readAndCompileShader(fragmentPath, GL_FRAGMENT_SHADER);
        id = glCreateProgram();
        glAttachShader(id, vertexShader);
        glAttachShader(id, fragmentShader);
        glLinkProgram(id);
        int success;
        char log[512];
        glGetProgramiv(id, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(id, 512, NULL, log);
            std::cout << "Error linking program:\n" << log << std::endl;
        }
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    void use() {
        glUseProgram(id);
    }

    void setBool(const std::string &name, bool value) const {
        glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value);
    }

    void setInt(const std::string &name, int value) const {
        glUniform1i(glGetUniformLocation(id, name.c_str()), value);
    }

    void setFloat(const std::string &name, float value) const {
        glUniform1f(glGetUniformLocation(id, name.c_str()), value);
    }

    unsigned int readAndCompileShader(const char *path, GLenum shaderType) {
        std::string code;
        std::ifstream file;
        file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try {
            file.open(path);
            std::stringstream stream;
            stream << file.rdbuf();
            file.close();
            code = stream.str();
        } catch (std::ifstream::failure e) {
            std::cout << "Error reading shader file " << path << std::endl;
            return 0;
        }
        const char *codePtr = code.c_str();
        int shader;
        int success;
        char log[512];
        shader = glCreateShader(shaderType);
        glShaderSource(shader, 1, &codePtr, NULL);
        glCompileShader(shader);
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 512, NULL, log);
            std::cout << "Error compiling shader " << path << ":\n" << log << std::endl;
        }
        return shader;
    }
};

#endif
