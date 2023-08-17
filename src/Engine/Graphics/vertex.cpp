// Engine : vertex.cpp

#include "vertex.hpp"

#include <iostream>

VertexArray::VertexArray() {
    VertexBufferIndex = 0;
    glad_glCreateVertexArrays(1, &vtxAObj);
}
VertexArray::~VertexArray() {
    glad_glDeleteVertexArrays(1, &vtxAObj);
}

void VertexArray::bind() const {
    glad_glBindVertexArray(vtxAObj);
}
void VertexArray::unbind() const {
    glad_glBindVertexArray(0);
}

void VertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vtxBuffer) {

    if (vtxBuffer->GetLayout().GetElements().size() == 0) {
        std::cerr << "vertex buffer has no layout!";
        return;
    }

    glad_glBindVertexArray(vtxAObj);
    vtxBuffer->Bind();

    const auto& layout = vtxBuffer->GetLayout();

    for (const auto& element : layout) {

        glad_glEnableVertexAttribArray(VertexBufferIndex);
        glad_glVertexAttribPointer(VertexBufferIndex, element.GetComponentCount(), ShaderTypeToGLBaseType(element.type),
            element.normalized ? GL_TRUE : GL_FALSE, layout.GetStride(), reinterpret_cast<const void*>(element.offset));
        VertexBufferIndex++;
    }

    VertexBuffers.push_back(vtxBuffer);
}

void VertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& idxBuffer) {

    glad_glBindVertexArray(vtxAObj);
    idxBuffer->Bind();

    ptrIndexBuffer = idxBuffer;
}

const std::vector<std::shared_ptr<VertexBuffer>>& VertexArray::GetVertexBuffers() const {
    return VertexBuffers;
}
const std::shared_ptr<IndexBuffer>& VertexArray::GetIndexBuffer() const {
    return ptrIndexBuffer;
}
