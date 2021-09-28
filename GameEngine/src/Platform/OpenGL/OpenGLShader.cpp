#include "gepch.h"
#include "OpenGLShader.h"
#include "GameEngine/Core.h"

#include <fstream>
#include <sstream>
#include <iostream>

#include <glad/glad.h>

namespace GameEngine
{

    OpenGLShader::OpenGLShader(const std::string& filepath) :
        m_filepath(filepath)
    {
        std::string sourceRaw = ReadFile(filepath);
        std::unordered_map<GLenum, std::string> source = ParseShader(sourceRaw);

        m_id = CompileShader(source);
    }

    OpenGLShader::OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc)
    {
        std::unordered_map<GLenum, std::string> sources;
        sources[GL_VERTEX_SHADER] = vertexSrc;
        sources[GL_FRAGMENT_SHADER] = fragmentSrc;

        m_id = CompileShader(sources);
    }

    OpenGLShader::~OpenGLShader()
    {
        glDeleteProgram(m_id);
    }

    void OpenGLShader::Bind() const
    {
        glUseProgram(m_id);
    }

    void OpenGLShader::Unbind() const
    {
        glUseProgram(0);
    }

    void OpenGLShader::SetUniform1i(const std::string& name, int v)
    {
        glUniform1i(GetUniformLocation(name), v);
    }

    void OpenGLShader::SetUniform1f(const std::string& name, float v)
    {
        glUniform1f(GetUniformLocation(name), v);
    }

    void OpenGLShader::SetUniform2f(const std::string& name, const glm::vec2& value)
    {
        glUniform2f(GetUniformLocation(name), value[0], value[1]);
    }

    void OpenGLShader::SetUniform3f(const std::string& name, const glm::vec3& value)
    {
        glUniform3f(GetUniformLocation(name), value[0], value[1], value[2]);
    }

    void OpenGLShader::SetUniform4f(const std::string& name, const glm::vec4& value)
    {
        glUniform4f(GetUniformLocation(name), value[0], value[1], value[2], value[3]);
    }

    void OpenGLShader::SetUniformMat3f(const std::string& name, const glm::mat3& matrix)
    {
        glUniformMatrix3fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
    }

    void OpenGLShader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix)
    {
        glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
    }

    int OpenGLShader::GetUniformLocation(const std::string& name)
    {
        if (m_uniformLocationCache.find(name) != m_uniformLocationCache.end()) {
            return m_uniformLocationCache[name];
        }

        int location = glGetUniformLocation(m_id, name.c_str());
        if (location == -1)
        {
            std::cout << "Warning: uniform " << name << " doesn't exist!" << std::endl;
        }

        m_uniformLocationCache[name] = location;
        return location;
    }

    std::string OpenGLShader::ReadFile(const std::string& filepath)
    {
        std::string result;
        std::ifstream in(filepath, std::ios::in, std::ios::binary);	
        
        if (in)
        {
            in.seekg(0, std::ios::end);
            result.resize(in.tellg());
            in.seekg(0, std::ios::beg);
            in.read(&result[0], result.size());
            in.close();
            ;
        }
        else
        {
            GE_CORE_ERROR("Could not open file '{0}'", filepath);
        }

        return result;
    }

    std::unordered_map<GLenum, std::string> OpenGLShader::ParseShader(const std::string& shaderSource)
    {
        std::unordered_map<GLenum, std::string> shaderSources;

        const char* typeToken = "#type";
        size_t typeTokenLength = strlen(typeToken);
        size_t pos = shaderSource.find(typeToken, 0);

        while (pos != std::string::npos)
        {
            size_t eol = shaderSource.find_first_of("\r\n", pos);
            GE_CORE_ASSERT(eol != std::string::npos, "Syntax error");
            pos += typeTokenLength + 1;
            std::string type = shaderSource.substr(pos, eol - pos);
            pos = shaderSource.find_first_not_of("\r\n", eol);
            size_t nextPos = shaderSource.find(typeToken, pos);

            if (type == "vertex") 
            {
                shaderSources[GL_VERTEX_SHADER] = shaderSource.substr(pos, nextPos - pos);
            }
            else if (type == "fragment" || type == "pixel")
            {
                shaderSources[GL_FRAGMENT_SHADER] = shaderSource.substr(pos, nextPos - pos);
            }
            else
            {
                GE_CORE_ASSERT(false, "Invalid shader type specified");
            }

            pos = nextPos;
        }

        return shaderSources;
    }

    int OpenGLShader::CompileShader(std::unordered_map<GLenum, std::string> shaderSources)
    {
        uint32_t program = glCreateProgram();
        std::vector<GLenum> glShaderIDs(shaderSources.size());

        // compile
        for (auto& kv : shaderSources)
        {
            GLenum type = kv.first;
            const std::string& source = kv.second;

            GLuint shader = glCreateShader(type); 
            const GLchar* sourceCStr = source.c_str();
            glShaderSource(shader, 1, &sourceCStr, 0);
            glCompileShader(shader);

            GLint isCompiled = 0;
            glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
            if (isCompiled == GL_FALSE)
            {
                GLint maxLength = 0;
                glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

                std::vector<GLchar> infoLog(maxLength);
                glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

                glDeleteShader(shader);

                GE_CORE_ERROR("{0}", infoLog.data());
                GE_CORE_ASSERT(false, "Shader compilation failure!");
                break;
            }

            glAttachShader(program, shader);
            glShaderIDs.push_back(shader);
        }

        // link
        glLinkProgram(program);

        GLint isLinked = 0;
        glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
        if (isLinked == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<GLchar> infoLog(maxLength);
            glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

            glDeleteProgram(program);

            for (auto id : glShaderIDs)
            {
                glDetachShader(program, id);
                glDeleteShader(id);
            }

            GE_CORE_ERROR("{0}", infoLog.data());
            GE_CORE_ASSERT(false, "Shader link failure!");

            return -1;
        }

        // cleanup
        for (auto id : glShaderIDs)
        {
            glDetachShader(program, id);
            glDeleteShader(id);
        }

        return program;
    }

}
