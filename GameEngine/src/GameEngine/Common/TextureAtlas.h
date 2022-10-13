#pragma once

#include "GameEngine/Renderer/Texture.h"
#include "GameEngine/Common/Common.h"

namespace GameEngine
{

	class TextureAtlas
	{
	public:
		TextureAtlas() {};
		TextureAtlas(int cols, int rows, Ref<Texture2D> texture) : m_cols(cols), m_rows(rows), m_texture(texture) {}

		Rect Get(int col, int row) {
			return {
				(float) col / m_cols,
				(float) row / m_rows,
				(float) 1 / m_cols,
				(float) 1 / m_rows,
			};
		}

		int GetCols() { return m_cols; }
		int GetRows() { return m_rows; }
		int GetPixlesPerCol() { return m_texture->GetWidth() / m_cols; }
		int GetPixlesPerRow() { return m_texture->GetHeight() / m_rows; }

		Ref<Texture2D> GetBaseTexture() { return m_texture; }

	private:
		int m_cols, m_rows;

		Ref<Texture2D> m_texture;
	};

}
