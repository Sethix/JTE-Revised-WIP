#pragma once

#include "RenderStructures.h"
#include "Assets.h"

namespace JTL
{

	struct Vector2;
	struct Vector3;
	struct Vector4;
	struct Matrix3;
	struct Matrix4;

	namespace SIM
	{

		namespace REN
		{

#ifdef GL

			Geometry makeGeometry(const struct Vertex *verts, const int &vsize, const unsigned int *tris, const int &tsize);
			Geometry loadGeometryFromOBJ(const char *path);
			void freeGeometry(Geometry&);

			Shader makeShader(const char *v, const char *f, const bool depth = true, const bool additiveBlend = true, const bool faceCull = true);
			Shader loadShader(const char *v, const char *f, const bool depth = true, const bool additiveBlend = true, const bool faceCull = true);
			void freeShader(Shader&);

			Texture makeTexture(const unsigned &w, const unsigned &h, const unsigned &f, const unsigned char *pixels, const bool &isFloat = false);
			Texture makeCubeTexture(unsigned width, unsigned height, unsigned channels, const void **pixels, bool isFloat);
			Texture loadTexture(const char *path);
			Texture loadCubeMap(const char * path_Xpos, const char * path_Xneg, const char * path_Ypos, const char * path_Yneg, const char * path_Zpos, const char * path_Zneg);
			void freeTexture(Texture&);

			FrameBuffer makeFrameBuffer(const unsigned width, const unsigned height, const unsigned nTex, const bool *isFloat = nullptr, const int *channels = nullptr);
			void clearFrameBuffer(FrameBuffer&);
			void clearFrameBuffer(const unsigned&);
			void freeFrameBuffer(FrameBuffer&);

			void drawStart(const Shader &s, const Geometry &g, const FrameBuffer &f);

			void drawFinal(const Shader &s, const Geometry &g, const FrameBuffer &f);

			size_t drawStyle(const size_t idx, const size_t tex, int &val);

			size_t drawStyle(const size_t idx, const size_t tex, float &val);

			size_t drawStyle(const size_t idx, const size_t tex, Texture &val);

			size_t drawStyle(const size_t idx, const size_t tex, JTL::Vector2 &val);

			size_t drawStyle(const size_t idx, const size_t tex, JTL::Vector3 &val);

			size_t drawStyle(const size_t idx, const size_t tex, JTL::Vector4 &val);

			size_t drawStyle(const size_t idx, const size_t tex, JTL::Matrix3 &val);

			size_t drawStyle(const size_t idx, const size_t tex, JTL::Matrix4 &val);

			size_t drawStyle(const size_t idx, const size_t tex, const int &val);

			size_t drawStyle(const size_t idx, const size_t tex, const float &val);

			size_t drawStyle(const size_t idx, const size_t tex, const Texture &val);

			size_t drawStyle(const size_t idx, const size_t tex, const JTL::Vector2 &val);

			size_t drawStyle(const size_t idx, const size_t tex, const JTL::Vector3 &val);

			size_t drawStyle(const size_t idx, const size_t tex, const JTL::Vector4 &val);

			size_t drawStyle(const size_t idx, const size_t tex, const JTL::Matrix3 &val);

			size_t drawStyle(const size_t idx, const size_t tex, const JTL::Matrix4 &val);

			template<typename T, typename ...U>
			void drawSteal(const size_t idx, size_t tex, const T &val, U &&... uniforms)
			{
				tex += drawStyle(idx, tex, val);
				drawSteal(idx + 1, tex, uniforms...);
			}

			template<typename T>
			void drawSteal(const size_t idx, size_t tex, const T &val)
			{
				drawStyle(idx, tex, val);
			}

			template<typename ... U>
			void draw(const Geometry &g, const Shader &s, const FrameBuffer &f, const U &... uniforms)
			{
				drawStart(s, g, f);
				drawSteal(0, 0, uniforms...);
				drawFinal(s, g, f);
			}

#endif // GL

		}
	}
}