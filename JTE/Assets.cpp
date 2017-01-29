#define STB_IMAGE_IMPLEMENTATION
#define TINYOBJLOADER_IMPLEMENTATION 

#include <cassert>
#include <string>
#include "Assets.h"
#include "RenderDeclarations.h"
#include "RenderUtilities.h"
#include "stb_image.h"
#include "tiny_obj_loader.h"

namespace JTL
{
	namespace SIM
	{
		Assets::Assets()
		{
			REN::Vertex verts[4] = { { { -1,-1, 0, 1 },{ 1,1,1,0 },{ 0,0,1,0 },{ 0,0 } },
			{ { 1,-1, 0, 1 },{ 1,1,0,1 },{ 0,0,1,0 },{ 1,0 } },
			{ { 1, 1, 0, 1 },{ 1,0,1,1 },{ 0,0,1,0 },{ 1,1 } },
			{ { -1, 1, 0, 1 },{ 0,1,1,1 },{ 0,0,1,0 },{ 0,1 } } };;

			unsigned int tris[6] = { 0,1,2,0,2,3 };

			REN::Vertex vertsB[36] = { 
				{ {-1,1,-1,1}, {0,0,0,0}, {0,0,0,0}, { 0,0 } },
				{ {-1,-1,-1,1 },{ 0,0,0,0 },{ 0,0,0,0 },{ 0,0 } }, 
				{ {1,-1,-1,1}, {0,0,0,0}, {0,0,0,0}, { 0,0 } },
				{ {1,-1,-1,1 },{ 0,0,0,0 },{ 0,0,0,0 },{ 0,0 } } ,
				{ {1,1,-1,1 },{ 0,0,0,0 },{ 0,0,0,0 },{ 0,0 } } ,
				{ {-1,1,-1,1 },{ 0,0,0,0 },{ 0,0,0,0 },{ 0,0 } } ,
			
				{ { -1,-1,1,1 },{ 0,0,0,0 },{ 0,0,0,0 },{ 0,0 } },
				{ { -1,-1,-1,1 },{ 0,0,0,0 },{ 0,0,0,0 },{ 0,0 } },
				{ { -1,1,-1,1 },{ 0,0,0,0 },{ 0,0,0,0 },{ 0,0 } },
				{ { -1,1,-1,1 },{ 0,0,0,0 },{ 0,0,0,0 },{ 0,0 } } ,
				{ { -1,1,1,1 },{ 0,0,0,0 },{ 0,0,0,0 },{ 0,0 } } ,
				{ { -1,-1,1,1 },{ 0,0,0,0 },{ 0,0,0,0 },{ 0,0 } } , 
			
				{ { 1,-1,-1,1 },{ 0,0,0,0 },{ 0,0,0,0 },{ 0,0 } },
				{ { 1,-1,1,1 },{ 0,0,0,0 },{ 0,0,0,0 },{ 0,0 } },
				{ { 1,1,1,1 },{ 0,0,0,0 },{ 0,0,0,0 },{ 0,0 } },
				{ { 1,1,1,1 },{ 0,0,0,0 },{ 0,0,0,0 },{ 0,0 } } ,
				{ { 1,1,-1,1 },{ 0,0,0,0 },{ 0,0,0,0 },{ 0,0 } } ,
				{ { 1,-1,-1,1 },{ 0,0,0,0 },{ 0,0,0,0 },{ 0,0 } } , 
			
				{ { -1,-1,1,1 },{ 0,0,0,0 },{ 0,0,0,0 },{ 0,0 } },
				{ { -1,1,1,1 },{ 0,0,0,0 },{ 0,0,0,0 },{ 0,0 } },
				{ { 1,1,1,1 },{ 0,0,0,0 },{ 0,0,0,0 },{ 0,0 } },
				{ { 1,1,1,1 },{ 0,0,0,0 },{ 0,0,0,0 },{ 0,0 } } ,
				{ { 1,-1,1,1 },{ 0,0,0,0 },{ 0,0,0,0 },{ 0,0 } } ,
				{ { -1,-1,1,1 },{ 0,0,0,0 },{ 0,0,0,0 },{ 0,0 } } , 
			
				{ { -1,1,-1,1 },{ 0,0,0,0 },{ 0,0,0,0 },{ 0,0 } },
				{ { 1,1,-1,1 },{ 0,0,0,0 },{ 0,0,0,0 },{ 0,0 } },
				{ { 1,1,1,1 },{ 0,0,0,0 },{ 0,0,0,0 },{ 0,0 } },
				{ { 1,1,1,1 },{ 0,0,0,0 },{ 0,0,0,0 },{ 0,0 } } ,
				{ { -1,1,1,1 },{ 0,0,0,0 },{ 0,0,0,0 },{ 0,0 } } ,
				{ { -1,1,-1,1 },{ 0,0,0,0 },{ 0,0,0,0 },{ 0,0 } } , 
			
				{ { -1,-1,-1,1 },{ 0,0,0,0 },{ 0,0,0,0 },{ 0,0 } },
				{ { -1,-1,1,1 },{ 0,0,0,0 },{ 0,0,0,0 },{ 0,0 } },
				{ { 1,-1,-1,1 },{ 0,0,0,0 },{ 0,0,0,0 },{ 0,0 } },
				{ { 1,-1,-1,1 },{ 0,0,0,0 },{ 0,0,0,0 },{ 0,0 } } ,
				{ { -1,-1,1,1 },{ 0,0,0,0 },{ 0,0,0,0 },{ 0,0 } } ,
				{ { 1,-1,1,1 },{ 0,0,0,0 },{ 0,0,0,0 },{ 0,0 } } };

			unsigned int trisB[36] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35};

			makeGeometry("quad", verts, 4, tris, 6);
			makeGeometry("skybox", vertsB, 36, trisB, 36);
			loadTexture("default", "../res/textures/default.png", 1, 1);
			loadShader("geoPass", "../res/shaders/geoPass.vs", "../res/shaders/geoPass.fs");
			loadShader("litPass", "../res/shaders/litPass.vs", "../res/shaders/litPass.fs");
			loadShader("ltsPass", "../res/shaders/ltsPass.vs", "../res/shaders/ltsPass.fs");
			loadShader("sPass", "../res/shaders/sPass.vs", "../res/shaders/sPass.fs");
			loadShader("skybox", "../res/shaders/skybox.vs", "../res/shaders/skybox.fs");
			loadShader("SSAO", "../res/shaders/SSAO.vs", "../res/shaders/SSAO.fs");
			loadShader("sobel", "../res/shaders/sobel.vs", "../res/shaders/sobel.fs");
			loadShader("postProcess", "../res/shaders/postProcess.vs", "../res/shaders/postProcess.fs");

			shaders["geoPass"].flags.blend = false;
			shaders["geoPass"].flags.cull = true;
			shaders["postProcess"].flags.blend = false;
		}

		void Assets::loadGeometry(const std::string & name, const std::string & path)
		{
			if (!geometry.count(name))
			{
				geometry[name] = { REN::loadGeometryFromOBJ(path.c_str())};
			}
		}
		void Assets::makeGeometry(const std::string &name, const REN::Vertex * verts, const int & vsize, const unsigned int * tris, const int & tsize)
		{
			if (!geometry.count(name))
				geometry[name] = REN::makeGeometry(verts, vsize, tris, tsize);
		}
		void Assets::loadShader(const std::string & name, const std::string & vpath, const std::string & fpath)
		{
			if (!shaders.count(name))
			{
				shaders[name] = { REN::loadShader(vpath.c_str(), fpath.c_str()) };
			}
		}
		void Assets::loadTexture(const std::string & name, const std::string & path, const int & rows, const int & cols)
		{
			if (!textures.count(name))
			{
				textures[name] = REN::Texture{ REN::loadTexture(path.c_str()) };
				textures[name].rows = rows;
				textures[name].cols = cols;
			}
		}

		void Assets::loadCubeMap(const std::string &name, const std::string &pathPosX, const std::string &pathNegX, const std::string &pathPosY, const std::string &pathNegY, const std::string &pathPosZ, const std::string &pathNegZ)
		{
			if (!textures.count(name))
			{
				textures[name] = REN::Texture{ REN::loadCubeMap(pathPosX.c_str(), pathNegX.c_str(), pathPosY.c_str(), pathNegY.c_str(), pathPosZ.c_str(), pathNegZ.c_str()) };
				textures[name].rows = 1;
				textures[name].cols = 1;
			}
		}

		void Assets::makeFrameBuffer(const std::string & name, const int width, const int height, const int texCount, const bool *isFloat, const int *channels)
		{
			if (!frameBuffers.count(name))
			{
				frameBuffers[name] = REN::FrameBuffer(REN::makeFrameBuffer(width, height, texCount, isFloat, channels));
			}
		}
	}
}