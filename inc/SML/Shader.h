#pragma once

#include <glad/glad.h>

#include <glm/glm.hpp>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

namespace SML
{

class Shader
{
public:
    unsigned int shaderProgramID;

    Shader()
    {
        loaded = false;
        shaderProgramID = 0;
    }

    // constructor to load the shaders from strings
    // ------------------------------------------------------------------------
    Shader(std::string vertexCode, std::string fragmentCode)
    {
        const char* vShaderCode = vertexCode.c_str();
        const char* fShaderCode = fragmentCode.c_str();
        // 2. compile shaders
        unsigned int vertex, fragment;
        // vertex shader
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);
        checkCompileErrors(vertex, "VERTEX");
        // fragment Shader
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);
        checkCompileErrors(fragment, "FRAGMENT");
        // shader Program
        shaderProgramID = glCreateProgram();
        glAttachShader(shaderProgramID, vertex);
        glAttachShader(shaderProgramID, fragment);
        glLinkProgram(shaderProgramID);
        checkCompileErrors(shaderProgramID, "PROGRAM", "Program Linking Stage");
        // delete the shaders as they're linked into our program now and no longer necessary
        glDeleteShader(vertex);
        glDeleteShader(fragment);

        loaded = true;
    }

    // constructor generates the shader on the fly
    // ------------------------------------------------------------------------
    Shader(const char* vertexPath, const char* fragmentPath)
    {
        // 1. retrieve the vertex/fragment source code from filePath
        std::string vertexCode;
        std::string fragmentCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;
        // ensure ifstream objects can throw exceptions:
        vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try
        {
            // open files
            vShaderFile.open(vertexPath);
            fShaderFile.open(fragmentPath);
            std::stringstream vShaderStream, fShaderStream;
            // read file's buffer contents into streams
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();
            // close file handlers
            vShaderFile.close();
            fShaderFile.close();
            // convert stream into string
            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();
        }
        catch (std::ifstream::failure& e)
        {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
        }
        const char* vShaderCode = vertexCode.c_str();
        const char* fShaderCode = fragmentCode.c_str();
        // 2. compile shaders
        unsigned int vertex, fragment;
        // vertex shader
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);
        checkCompileErrors(vertex, "VERTEX", vertexPath);
        // fragment Shader
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);
        checkCompileErrors(fragment, "FRAGMENT", fragmentPath);
        // shader Program
        shaderProgramID = glCreateProgram();
        glAttachShader(shaderProgramID, vertex);
        glAttachShader(shaderProgramID, fragment);
        glLinkProgram(shaderProgramID);
        checkCompileErrors(shaderProgramID, "PROGRAM", "Program Linking Stage");
        // delete the shaders as they're linked into our program now and no longer necessary
        glDeleteShader(vertex);
        glDeleteShader(fragment);

        loaded = true;
    }

    // activate the shader
    // ------------------------------------------------------------------------
    void use() const
    {
        if (!loaded)
        {
            std::cout << "ERROR::SHADER::USE::SHADER_NOT_LOADED" << std::endl;
            return;
        }

        glUseProgram(shaderProgramID);
    }

    // utility uniform functions
    // ------------------------------------------------------------------------
    void setBool(const std::string& name, bool value) const
    {
        if (!loaded)
        {
            std::cout << "ERROR::SHADER::SETBOOL::SHADER_NOT_LOADED" << std::endl;
            return;
        }

        glUniform1i(glGetUniformLocation(shaderProgramID, name.c_str()), (int)value);
    }

    // ------------------------------------------------------------------------
    void setInt(const std::string& name, int value) const
    {
        if (!loaded)
        {
            std::cout << "ERROR::SHADER::SETINT::SHADER_NOT_LOADED" << std::endl;
            return;
        }

        glUniform1i(glGetUniformLocation(shaderProgramID, name.c_str()), value);
    }

    // ------------------------------------------------------------------------
    void setFloat(const std::string& name, float value) const
    {
        if (!loaded)
        {
            std::cout << "ERROR::SHADER::SETFLOAT::SHADER_NOT_LOADED" << std::endl;
            return;
        }

        glUniform1f(glGetUniformLocation(shaderProgramID, name.c_str()), value);
    }

    // ------------------------------------------------------------------------
    void setVec2(const std::string& name, const glm::vec2& value) const
    {
        if (!loaded)
        {
            std::cout << "ERROR::SHADER::SETVEC2::SHADER_NOT_LOADED" << std::endl;
            return;
        }

        glUniform2fv(glGetUniformLocation(shaderProgramID, name.c_str()), 1, &value[0]);
    }

    void setVec2(const std::string& name, float x, float y) const
    {
        if (!loaded)
        {
            std::cout << "ERROR::SHADER::SETVEC2::SHADER_NOT_LOADED" << std::endl;
            return;
        }

        glUniform2f(glGetUniformLocation(shaderProgramID, name.c_str()), x, y);
    }

    // ------------------------------------------------------------------------
    void setVec3(const std::string& name, const glm::vec3& value) const
    {
        if (!loaded)
        {
            std::cout << "ERROR::SHADER::SETVEC3::SHADER_NOT_LOADED" << std::endl;
            return;
        }

        glUniform3fv(glGetUniformLocation(shaderProgramID, name.c_str()), 1, &value[0]);
    }

    void setVec3(const std::string& name, float x, float y, float z) const
    {
        if (!loaded)
        {
            std::cout << "ERROR::SHADER::SETVEC3::SHADER_NOT_LOADED" << std::endl;
            return;
        }

        glUniform3f(glGetUniformLocation(shaderProgramID, name.c_str()), x, y, z);
    }

    // ------------------------------------------------------------------------
    void setVec4(const std::string& name, const glm::vec4& value) const
    {
        if (!loaded)
        {
            std::cout << "ERROR::SHADER::SETVEC4::SHADER_NOT_LOADED" << std::endl;
            return;
        }

        glUniform4fv(glGetUniformLocation(shaderProgramID, name.c_str()), 1, &value[0]);
    }

    void setVec4(const std::string& name, float x, float y, float z, float w) const
    {
        if (!loaded)
        {
            std::cout << "ERROR::SHADER::SETVEC4::SHADER_NOT_LOADED" << std::endl;
            return;
        }

        glUniform4f(glGetUniformLocation(shaderProgramID, name.c_str()), x, y, z, w);
    }

    // ------------------------------------------------------------------------
    void setMat2(const std::string& name, const glm::mat2& mat) const
    {
        if (!loaded)
        {
            std::cout << "ERROR::SHADER::SETMAT2::SHADER_NOT_LOADED" << std::endl;
            return;
        }

        glUniformMatrix2fv(glGetUniformLocation(shaderProgramID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    // ------------------------------------------------------------------------
    void setMat3(const std::string& name, const glm::mat3& mat) const
    {
        if (!loaded)
        {
            std::cout << "ERROR::SHADER::SETMAT3::SHADER_NOT_LOADED" << std::endl;
            return;
        }

        glUniformMatrix3fv(glGetUniformLocation(shaderProgramID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    // ------------------------------------------------------------------------
    void setMat4(const std::string& name, const glm::mat4& mat) const
    {
        if (!loaded)
        {
            std::cout << "ERROR::SHADER::SETMAT4::SHADER_NOT_LOADED" << std::endl;
            return;
        }

        glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

private:
    bool loaded = false;

    // utility function for checking shader compilation/linking errors.
    // ------------------------------------------------------------------------
    void checkCompileErrors(GLuint shader, std::string type)
    {
        GLint success;
        GLchar infoLog[1024];
        if (type != "PROGRAM")
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n"
                          << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
        else
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n"
                          << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
    }

    void checkCompileErrors(GLuint shader, std::string type, std::string fileName)
    {
        GLint success;
        GLchar infoLog[1024];
        if (type != "PROGRAM")
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                std::cout << "ERROR from: " << fileName << std::endl << std::endl;
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n"
                          << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
        else
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success)
            {
                std::cout << "ERROR from: " << fileName << std::endl << std::endl;
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n"
                          << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
    }
};

} // namespace SML
