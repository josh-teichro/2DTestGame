#include "gepch.h"
#include "OpenGLVertexArray.h"
#include "OpenGLVertexBuffer.h"

#include <glad/glad.h>

namespace GameEngine
{

    OpenGLVertexArray::OpenGLVertexArray()
    {
        glGenVertexArrays(1, &m_id);
        glBindVertexArray(m_id);
    }

    OpenGLVertexArray::~OpenGLVertexArray()
    {
        glDeleteVertexArrays(1, &m_id);
    }

    void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
    {
        GE_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "VertexBufferLayout has no elements!");

        glBindVertexArray(m_id);
        vertexBuffer->Bind();

        const auto& elements = vertexBuffer->GetLayout().GetElements();

        for (int i = 0; i < elements.size(); i++)
        {
            const auto& el = elements[i];

            glEnableVertexAttribArray(i); 
            glVertexAttribPointer(
                i, 
                el.GetComponentCount(), 
                ShaderDataTypeToOpenGLBaseType(el.type), 
                el.normalized ? GL_TRUE : GL_FALSE,
                vertexBuffer->GetLayout().GetStride(),
                (const void*)(uintptr_t)el.offset
            );
        }

        m_vertexBuffers.push_back(vertexBuffer);
    }

    void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
    {
        indexBuffer->Bind();
        m_indexBuffer = indexBuffer;
    }


    void OpenGLVertexArray::Bind() const
    {
        glBindVertexArray(m_id);
    }

    void OpenGLVertexArray::Unbind() const
    {
        glBindVertexArray(0);
    }

}
