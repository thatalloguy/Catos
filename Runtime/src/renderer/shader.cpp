//
// Created by allos on 10/16/2024.
//

#include "shader.h"
#include "glad/glad.h"
#include "spdlog/spdlog.h"

catos::Shader::Shader() { }

void catos::Shader::init(const catos::ShaderCreateInfo &createInfo) {

    shaderProgram = glCreateProgram();

    if (createInfo.vertexSRC != nullptr) {
        addSubShader(createInfo.vertexSRC, ShaderType::VERTEX);
    }


    if (createInfo.fragmentSRC != nullptr) {
        addSubShader(createInfo.fragmentSRC, ShaderType::FRAGMENT);
    }


    glLinkProgram(shaderProgram);
}


catos::Shader::~Shader() {
    glDeleteProgram(shaderProgram);
}

catos::ShaderStatus catos::Shader::addSubShader(const char *src, catos::ShaderType type) {

    ShaderProgram shader;

    try {
        shader = loadShader(src, type);
    } catch (ShaderStatus error) {
        return error;
    }

    glAttachShader(shaderProgram, shader);

    glDeleteShader(shader);

    return catos::ShaderStatus::SUCCESSFUL;
}

const char *catos::Shader::getCompilationErrorMessage() {
    return "What ?";
}

catos::ShaderProgram catos::Shader::loadShader(const char *src, catos::ShaderType type) {

    unsigned int shader;

    shader = glCreateShader(type);
    glShaderSource(shader, 1, &src, NULL);
    glCompileShader(shader);


    //Check for errors
    int  success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        spdlog::error("Shader Compilation Error: {}", infoLog);
        throw ShaderStatus::COMPILATION_FAILED;
    }

    return shader;
}

void catos::Shader::bind() {
    glUseProgram(shaderProgram);
}

void catos::Shader::setInt(const char *name, int val) {
    glUniform1i(glGetUniformLocation(shaderProgram, name), val);
}
