#pragma once

namespace GameEngine
{

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual inline unsigned int GetCount() const = 0;

		static Ref<IndexBuffer> Create(const unsigned int* data, unsigned int count);
	};

}
