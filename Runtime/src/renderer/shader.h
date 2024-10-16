//
// Created by allos on 10/16/2024.
//

#ifndef CATOS_SHADER_H
#define CATOS_SHADER_H


namespace catos {

    typedef unsigned int ShaderProgram;

    enum class ShaderStatus: unsigned int {
        SUCCESSFUL = 0,

        UNKNOWN_SOURCE = 1,
        COMPILATION_FAILED = 2,
    };

    enum ShaderType: unsigned int {
        VERTEX = 0x8B31,
        FRAGMENT = 0x8B30,
    };

    struct ShaderCreateInfo {
        const char* vertexSRC = nullptr;
        const char* fragmentSRC = nullptr;
    };

    class Shader {

    public:
        Shader();
        ~Shader();

        void init(const ShaderCreateInfo& createInfo);

        ShaderStatus addSubShader(const char* src, ShaderType type);

        const char* getCompilationErrorMessage();

        ShaderProgram getShaderProgram() { return shaderProgram; };

        void bind();

        void setInt(const char* name, int val);

    private:

        ShaderProgram loadShader(const char* src, ShaderType type);

        ShaderProgram shaderProgram;

    };

}



#endif //CATOS_SHADER_H
