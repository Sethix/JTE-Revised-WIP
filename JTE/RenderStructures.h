#pragma once
#include "Settings.h"

namespace JTL
{
	namespace SIM
	{
		namespace REN
		{
#ifdef GL

			struct Vertex
			{
				union
				{
					float position[4];
					struct { float x, y, z, w; };
				};

				union
				{
					float normal[4];
					struct { float nx, ny, nz, nw; };
				};

				union
				{
					float color[4];
					struct { float r, g, b, a; };
				};

				union
				{
					float UV[2];
					struct { float u, v; };
				};

				enum
				{
					POSITION = 0,
					NORMAL = 16,
					COLOR = 32,
					TEXCOORD = 48,
				};
			};

			struct Geometry
			{
				unsigned vbo, ibo, vao, size;

				bool Bind() const;
			};

			struct ShaderFlags
			{
				bool depth, cull, blend;

				void Enable() const;
			};

			struct Shader
			{
				unsigned handle;
				ShaderFlags flags;

				bool Bind() const;
			};

			struct Texture
			{
				unsigned handle;
				unsigned width, height, rows, cols, iFormat, eFormat;
				bool isFloat;
				bool isCubemap;

				void Resize(const int &w, const int &h);
			};

			struct FrameBuffer
			{
				unsigned handle;
				unsigned width, height;
				unsigned texCount;

				Texture depth;
				Texture tex[16];

				bool Bind() const;
				void Resize(const int &w, const int &h);
			};

			struct ActiveRenderInfo
			{
				static Geometry currentGeometry;
				static Shader currentShader;
				static FrameBuffer currentFBO;

				static bool depthState, cullState, blendState;
			};

#endif // GL
		}
	}
}