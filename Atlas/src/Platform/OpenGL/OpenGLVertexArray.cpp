#include "atlaspch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Atlas
{

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case Atlas::ShaderDataType::Float:    return GL_FLOAT;
		case Atlas::ShaderDataType::Float2:   return GL_FLOAT;
		case Atlas::ShaderDataType::Float3:   return GL_FLOAT;
		case Atlas::ShaderDataType::Float4:   return GL_FLOAT;
		case Atlas::ShaderDataType::Mat3:     return GL_FLOAT;
		case Atlas::ShaderDataType::Mat4:     return GL_FLOAT;
		case Atlas::ShaderDataType::Int:      return GL_INT;
		case Atlas::ShaderDataType::Int2:     return GL_INT;
		case Atlas::ShaderDataType::Int3:     return GL_INT;
		case Atlas::ShaderDataType::Int4:     return GL_INT;
		case Atlas::ShaderDataType::Bool:     return GL_BOOL;
		}


		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &rendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &rendererID);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(rendererID);
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
	{

		glBindVertexArray(rendererID);
		vertexBuffer->Bind();

		uint32_t index = 0;
		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)element.Offset);
			index++;
		}

		vertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(rendererID);
		indexBuffer->Bind();

		this->indexBuffer = indexBuffer;
	}

}
