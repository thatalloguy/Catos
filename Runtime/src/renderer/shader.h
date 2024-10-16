//
// Created by allos on 10/16/2024.
//

#ifndef CATOS_SHADER_H
#define CATOS_SHADER_H


namespace catos {

    typedef unsigned int ShaderProgram;

    /// Statuses for shader operations
    enum class ShaderStatus: unsigned int {
        SUCCESSFUL = 0,

        UNKNOWN_SOURCE = 1,
        COMPILATION_FAILED = 2,
    };

    /// Shader Type (more to be added in the future such as geometry).
    enum ShaderType: unsigned int {
        VERTEX = 0x8B31,
        FRAGMENT = 0x8B30,
    };

    struct ShaderCreateInfo {
        const char* vertexSRC = nullptr;
        const char* fragmentSRC = nullptr;
    };

    /*
     * A Shader is a object that holds a program that runs on the GPU.
     */
    class Shader {

    public:
        Shader();
        ~Shader();

        /// Creates 2 shaders for the Vertex and Fragment Shader
        void init(const ShaderCreateInfo& createInfo);

        /// Adds a new subShader to the ShaderProgram
        ShaderStatus addSubShader(const char* src, ShaderType type);

        /// Returns the last compilation error.
        const char* getCompilationErrorMessage();

        /// Returns the raw ShaderProgram object for GL uses
        ShaderProgram getShaderProgram() { return shaderProgram; };

        /// Binds the shader
        void bind();

        /// Sets a int uniform
        void setInt(const char* name, int val);

    private:

        ShaderProgram loadShader(const char* src, ShaderType type);

        ShaderProgram shaderProgram;

    };

}



#endif //CATOS_SHADER_H
