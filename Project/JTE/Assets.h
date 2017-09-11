#pragma once
#include <unordered_map>
#include <string>
#include "Settings.h"
#include "RenderStructures.h"
#include "RenderDeclarations.h"

namespace JTL
{
	namespace SIM
	{

		class Transform;

		class Assets
		{
			Assets();

		public:

			std::unordered_map<std::string, REN::Geometry   > geometry;
			std::unordered_map<std::string, REN::Shader	   > shaders;
			std::unordered_map<std::string, REN::Texture	   > textures;
			std::unordered_map<std::string, REN::FrameBuffer> frameBuffers;

			void loadGeometry	(const std::string &name, const std::string &path);
			void makeGeometry	(const std::string &name, const REN::Vertex *verts, const int &vsize, const unsigned int *tris, const int &tsize);
			void loadShader		(const std::string &name, const std::string & vpath, const std::string & fpath);
			void loadTexture	(const std::string &name, const std::string &path, const int &rows, const int &cols);
			void loadCubeMap	(const std::string &name, const std::string &pathPosX, const std::string &pathNegX, const std::string &pathPosY, const std::string &pathNegY, const std::string &pathPosZ, const std::string &pathNegZ);
			void makeFrameBuffer(const std::string &name, const int width, const int height, const int texCount, const bool *isFloat = nullptr, const int *channels = nullptr);

			template<typename ...U>
			inline void draw(const REN::Geometry &g, const REN::Shader &s, const REN::FrameBuffer &f, const U &... uniforms)
			{ REN::draw(g, s, f, uniforms...); }

			static Assets &instance() { static Assets i; return i; }
		};
	}
}