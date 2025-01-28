//
// Created by allos on 10/16/2024.
//

#include "shader.h"
#include "spdlog/spdlog.h"

catos::Shader::Shader() { }

void catos::Shader::init(const catos::ShaderCreateInfo &createInfo) {

    shaderProgram = glCreateProgram();

    if (createInfo.vertexSRC != nullptr) {
        addSubShader(createInfo.vertexSRC, ShaderType::VERTEX);
    } else {
        spdlog::info("W");
    }


    if (createInfo.fragmentSRC != nullptr) {
        addSubShader(createInfo.fragmentSRC, ShaderType::FRAGMENT);
    } else {
        spdlog::info("W");
    }

    if (createInfo.geometrySRC != nullptr) {
        addSubShader(createInfo.geometrySRC, ShaderType::GEOMETRY);
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
        spdlog::error("Compilation Failure");
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
    unsigned int loc = glGetUniformLocation(shaderProgram, name);

    glUniform1i(loc, val);
}

void catos::Shader::setTransform(const char* name, float* val) {
    unsigned int loc = glGetUniformLocation(shaderProgram, name);
    if (loc > 100)
        return;
    glUniformMatrix4fv(loc, 1, GL_FALSE, val);
}

void catos::Shader::setVector3(const char* name, math::Vector3& vec){
    unsigned int loc = glGetUniformLocation(shaderProgram, name);
    if (loc > 100)
        return;
    glUniform3fv(loc, 1, vec.value_ptr());
}

void catos::Shader::setFloat(const char *name, float val) {
    unsigned int loc = glGetUniformLocation(shaderProgram, name);
    if (loc > 100)
        return;
    glUniform1f(loc, val);
}

void catos::Shader::setVector3GLM(const char *name, float *ptr) {
    unsigned int loc = glGetUniformLocation(shaderProgram, name);
    if (loc > 100)
        return;
    glUniform3fv(loc, 1, ptr);
}
