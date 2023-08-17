// Engine : shader.cpp

#include "shader.hpp"

#include <iostream>

#include <array>
#include <fstream>
#include <unordered_map>

#include <GLM/gtc/type_ptr.hpp>

int ShaderDataTypeSize(ShaderDataType type) {

    switch (type) {
    case ShaderDataType::Float:         return 4;
    case ShaderDataType::Float2:        return 4 * 2;
    case ShaderDataType::Float3:        return 4 * 3;
    case ShaderDataType::Float4:        return 4 * 4;
    case ShaderDataType::Mat3:          return 4 * 3 * 3;
    case ShaderDataType::Mat4:          return 4 * 4 * 4;
    case ShaderDataType::Int:           return 4;
    case ShaderDataType::Int2:          return 4 * 2;
    case ShaderDataType::Int3:          return 4 * 3;
    case ShaderDataType::Int4:          return 4 * 4;
    case ShaderDataType::Bool:          return 1;
    default:                            return 0;
    }
}

GLenum ShaderTypeToGLBaseType(ShaderDataType type) {

    switch (type) {

    case ShaderDataType::Float:         return GL_FLOAT;
    case ShaderDataType::Float2:        return GL_FLOAT;
    case ShaderDataType::Float3:        return GL_FLOAT;
    case ShaderDataType::Float4:        return GL_FLOAT;
    case ShaderDataType::Mat3:          return GL_FLOAT;
    case ShaderDataType::Mat4:          return GL_FLOAT;
    case ShaderDataType::Int:           return GL_INT;
    case ShaderDataType::Int2:          return GL_INT;
    case ShaderDataType::Int3:          return GL_INT;
    case ShaderDataType::Int4:          return GL_INT;
    case ShaderDataType::Bool:          return GL_INT;
    default:                            return 0;
    }
}

const std::string& Shader::GetName() const {
    return name;
}
const unsigned int Shader::GetRendererID() const {
    return RendererID;
}

Shader::Shader(const std::string& _name, const std::string& vtxPath, const std::string& frgPath) {
    name = _name;
    init(vtxPath, frgPath);
}

void Shader::init(const std::string& vtxPath, const std::string& frgPath) {

    std::string vtxShader = "";

    std::ifstream vtxIn(vtxPath, std::ios::binary);
    if (vtxIn) {

        vtxIn.seekg(0, std::ios::end);
        vtxShader.resize(vtxIn.tellg());

        vtxIn.seekg(0, std::ios::beg);
        vtxIn.read(&vtxShader[0], vtxShader.size());
        vtxIn.close();
    }

    std::string frgShader = "";

    std::ifstream frgIn(frgPath, std::ios::binary);
    if (frgIn) {

        frgIn.seekg(0, std::ios::end);
        frgShader.resize(frgIn.tellg());
        
        frgIn.seekg(0, std::ios::beg);
        frgIn.read(&frgShader[0], frgShader.size());
        frgIn.close();
    }

    // Shader Processing
    std::unordered_map<GLenum, std::string> sources;
    sources[GL_VERTEX_SHADER] = vtxShader;
    sources[GL_FRAGMENT_SHADER] = frgShader;

    unsigned int program = glad_glCreateProgram();

    std::array<unsigned int, 2> ids = {};
    int idIndex = 0;

    for (auto& source : sources) {

        GLenum type = source.first;
        const std::string& src = source.second;

        GLuint shader = glad_glCreateShader(type);

        const GLchar* srccstr = src.c_str();
        glad_glShaderSource(shader, 1, &srccstr, 0);
        glad_glCompileShader(shader);

        GLint isCompiled = (GLint)false;
        glad_glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);

        if (isCompiled == GL_FALSE) {

            GLint logLength = 0;
            glad_glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);

            std::vector<GLchar> log(logLength);
            glad_glGetShaderInfoLog(shader, logLength, &logLength, &log[0]);

            glad_glDeleteShader(shader);

            std::cerr << log.data();

            return;
        }

        glad_glAttachShader(program, shader);
        ids[idIndex++] = shader;
    }

    RendererID = program;
    GLint isLinked = (GLint)false;

    glad_glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
    if (isLinked == GL_FALSE) {

        GLint logLength = 0;
        glad_glGetShaderiv(program, GL_INFO_LOG_LENGTH, &logLength);

        std::vector<GLchar> log(logLength);
        glad_glGetShaderInfoLog(program, logLength, &logLength, &log[0]);

        glad_glDeleteProgram(program);

        for (auto id : ids)
            glad_glDeleteShader(id);

        std::cerr << log.data();

        return;
    }

    for (auto id : ids) {
        glad_glDetachShader(program, id);
        glad_glDeleteShader(id);
    }
}


void Shader::bind() const {
    glad_glUseProgram(RendererID);
}

void Shader::unbind() const {
    glad_glUseProgram(0);
}

void Shader::SetInt(const std::string& _name, int _value) {
    UploadUniformInt(_name, _value);
}
void Shader::SetFloat(const std::string& _name, const float _value) {
    UploadUniformFloat(_name, _value);
}
void Shader::SetFloat2(const std::string& _name, const glm::vec2& _value) {
    UploadUniformFloat2(_name, _value);
}
void Shader::SetFloat3(const std::string& _name, const glm::vec3& _value) {
    UploadUniformFloat3(_name, _value);
}
void Shader::SetFloat4(const std::string& _name, const glm::vec4& _value) {
    UploadUniformFloat4(_name, _value);
}
void Shader::SetMat3(const std::string& _name, const glm::mat3& _value) {
    UploadUniformMat3(_name, _value);
}
void Shader::SetMat4(const std::string& _name, const glm::mat4& _value) {
    UploadUniformMat4(_name, _value);
}
void Shader::SetBool(const std::string& _name, const bool _value) {
    UploadUniformBool(_name, _value);
}

void Shader::SetInt1v(const std::string& _name, const int _count, const int* _values) {
    UploadUniformInt1v(_name, _count, _values);
}

void Shader::UploadUniformInt(const std::string& _name, int _value) {
    GLuint location = glad_glGetUniformLocation(RendererID, _name.c_str());
    glad_glUniform1i(location, _value);
}

void Shader::UploadUniformFloat(const std::string& _name, float _value) {
    GLuint location = glad_glGetUniformLocation(RendererID, _name.c_str());
    glad_glUniform1f(location, _value);
}
void Shader::UploadUniformFloat2(const std::string& _name, const glm::vec2& _value) {
    GLuint location = glad_glGetUniformLocation(RendererID, _name.c_str());
    glad_glUniform2f(location, _value.x, _value.y);
}
void Shader::UploadUniformFloat3(const std::string& _name, const glm::vec3& _value) {
    GLuint location = glad_glGetUniformLocation(RendererID, _name.c_str());
    glad_glUniform3f(location, _value.x, _value.y, _value.z);
}
void Shader::UploadUniformFloat4(const std::string& _name, const glm::vec4& _value) {
    GLuint location = glad_glGetUniformLocation(RendererID, _name.c_str());
    glad_glUniform4f(location, _value.x, _value.y, _value.z, _value.w);
}

void Shader::UploadUniformMat3(const std::string& _name, const glm::mat3& _matrix) {
    GLuint location = glad_glGetUniformLocation(RendererID, _name.c_str());
    glad_glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(_matrix));
}
void Shader::UploadUniformMat4(const std::string& _name, const glm::mat4& _matrix) {
    GLuint location = glad_glGetUniformLocation(RendererID, _name.c_str());
    glad_glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(_matrix));
}
void Shader::UploadUniformBool(const std::string& _name, const bool _value) {
    GLuint location = glad_glGetUniformLocation(RendererID, _name.c_str());
    glad_glUniform1i(location, _value);
}

void Shader::UploadUniformInt1v(const std::string& _name, const int _count, const int* _values) {
    GLuint location = glad_glGetUniformLocation(RendererID, _name.c_str());
    glad_glUniform1iv(location, _count, _values);
}
