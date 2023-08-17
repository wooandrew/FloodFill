// Engine : shader.hpp

#pragma once

#ifndef ENGINE_GRAPHICS_SHADER_CHPP
#define ENGINE_GRAPHICS_SHADER_CHPP

#include <string>

#include <GLAD/glad.h>
#include <GLM/glm.hpp>

enum class ShaderDataType {

    None = 0,
    Float, Float2, Float3, Float4,
    Mat3, Mat4,
    Int, Int2, Int3, Int4,
    Bool
};

int ShaderDataTypeSize(ShaderDataType type);
GLenum ShaderTypeToGLBaseType(ShaderDataType type);

class Shader {

public:

    Shader() = default;
    Shader(const std::string& _name, const std::string& vtxPath, const std::string& frgPath);

    void init(const std::string& vtxPath, const std::string& frgPath);
    void bind() const;
    void unbind() const;

    void SetInt(const std::string& _name, const int _value);
    void SetFloat(const std::string& _name, const float _value);
    void SetFloat2(const std::string& _name, const glm::vec2& _value);
    void SetFloat3(const std::string& _name, const glm::vec3& _value);
    void SetFloat4(const std::string& _name, const glm::vec4& _value);
    void SetMat3(const std::string& _name, const glm::mat3& _value);
    void SetMat4(const std::string& _name, const glm::mat4& _value);
    void SetBool(const std::string& _name, const bool _value);
    void SetInt1v(const std::string& _name, const int _count, const int* _values);

    const std::string& GetName() const;
    const unsigned int GetRendererID() const;

private:

    void UploadUniformInt(const std::string& _name, int _value);
    void UploadUniformFloat(const std::string& _name, float _value);
    void UploadUniformFloat2(const std::string& _name, const glm::vec2& _value);
    void UploadUniformFloat3(const std::string& _name, const glm::vec3& _value);
    void UploadUniformFloat4(const std::string& _name, const glm::vec4& _value);
    void UploadUniformMat3(const std::string& _name, const glm::mat3& _matrix);
    void UploadUniformMat4(const std::string& _name, const glm::mat4& _matrix);
    void UploadUniformBool(const std::string& _name, const bool _value);

    void UploadUniformInt1v(const std::string& _name, const int _count, const int* _values);

    unsigned int RendererID;
    std::string name;
};

#endif // !ENGINE_GRAPHICS_SHADER_CHPP
