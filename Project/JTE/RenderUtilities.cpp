#pragma once
#include <cassert>
#include <fstream>
#include <istream>
#include <string>
#include <algorithm>
#include "RenderDeclarations.h"
#include "RenderStructures.h"
#include "RenderUtilities.h"
#include "Vector4.h"
#include "Matrix3.h"
#include "Matrix4.h"
#include "stb_image.h"
#include "tiny_obj_loader.h"

std::string stdStyleFileToString(const char *path)
{
	std::ifstream infile{ path };
	std::string file_contents{ std::istreambuf_iterator<char>(infile),
		std::istreambuf_iterator<char>() };
	return file_contents;
}

namespace JTL
{
	namespace SIM
	{
		namespace REN
		{
#pragma region Geo

			Geometry makeGeometry(const Vertex * verts, const int & vsize, const unsigned int * tris, const int & tsize)
			{
				Geometry retval;

				// Define the variables
				glGenBuffers(1, &retval.vbo);	   // Store vertices
				glGenBuffers(1, &retval.ibo);	   // Store indices
				glGenVertexArrays(1, &retval.vao); // Store attribute information

												   // Scope the variables
				glBindVertexArray(retval.vao);
				glBindBuffer(GL_ARRAY_BUFFER, retval.vbo); // scope our vertices
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, retval.ibo); // triangle is scoped

																   // Initialize the variables
				glBufferData(GL_ARRAY_BUFFER, vsize * sizeof(Vertex), verts, GL_STATIC_DRAW);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, tsize * sizeof(unsigned), tris, GL_STATIC_DRAW);

				// Attributes let us tell openGL how the memory is laid out
				glEnableVertexAttribArray(0); // Position
				glEnableVertexAttribArray(1); // Normal
				glEnableVertexAttribArray(2); // Color
				glEnableVertexAttribArray(3); // TexCoord

											  // index of the attribute, number of elements, type, normalized?, size of vertex, offset
				glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)Vertex::POSITION);
				glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)Vertex::NORMAL);
				glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)Vertex::COLOR);
				glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)Vertex::TEXCOORD);

				// unscope the variables
				glBindVertexArray(0);
				glBindBuffer(GL_ARRAY_BUFFER, 0);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
				retval.size = tsize;
				return retval;
			}

			Geometry loadGeometryFromOBJ(const char * path)
			{
				tinyobj::attrib_t attrib;
				std::vector<tinyobj::shape_t> shapes;
				std::vector<tinyobj::material_t> materials;
				std::string err;
				bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, path);
				int vsize = shapes[0].mesh.indices.size();
				Vertex   *verts = new Vertex[vsize];
				unsigned * tris = new unsigned[vsize];

				for (int i = 0; i < vsize; ++i)
				{
					auto ind = shapes[0].mesh.indices[i];

					const float *n = &attrib.normals[ind.normal_index * 3]; // +1, +2, 0
					const float *p = &attrib.vertices[ind.vertex_index * 3]; // +1, +2, 1

					memcpy(verts[i].position, Vector4{ p[0], p[1], p[2], 1.f }.v, sizeof(Vector4));
					memcpy(verts[i].normal, Vector4{ n[0], n[1], n[2], 0.f }.v, sizeof(Vector4));

					if (ind.texcoord_index >= 0)
					{
						const float *t = &attrib.texcoords[ind.texcoord_index * 2]; // +1
						memcpy(verts[i].UV, Vector2{ t[0], t[1] }.v, sizeof(float) * 2);
					}

					tris[i] = i;
				}

				Geometry retval = makeGeometry(verts, vsize, tris, vsize);

				delete[] verts;
				delete[] tris;
				// then we can call makeGeometry as per normal.
				return retval;
			}

			void freeGeometry(Geometry& g)
			{
				glDeleteBuffers(1, &g.vbo);
				glDeleteBuffers(1, &g.ibo);
				glDeleteVertexArrays(1, &g.vao);
				g = { 0,0,0,0 };
			}

#pragma endregion

#pragma region Shader

			Shader makeShader(const char * v, const char * f, const bool depth, const bool additiveBlend, const bool faceCull)
			{
				Shader retval;
				// create our variables
				retval.handle = glCreateProgram();
				unsigned vs = glCreateShader(GL_VERTEX_SHADER);
				unsigned fs = glCreateShader(GL_FRAGMENT_SHADER);
				// initialize our variables
				glShaderSource(vs, 1, &v, 0);
				glShaderSource(fs, 1, &f, 0);
				// compile the shaders
				glCompileShader(vs);
				glCompileShader(fs);

				GLint success = GL_FALSE;
				glGetShaderiv(fs, GL_COMPILE_STATUS, &success);
				if (success == GL_FALSE)
				{
					int length = 0;
					glGetShaderiv(fs, GL_INFO_LOG_LENGTH, &length);
					char *log = (char*)malloc(length);
					glGetShaderInfoLog(fs, length, 0, log);
					//std::cout << log << std::endl; 
					printf("%s\n", log);
					free(log);
				}



				// link the shaders into a single program
				glAttachShader(retval.handle, vs);
				glAttachShader(retval.handle, fs);
				glLinkProgram(retval.handle);

				success = GL_FALSE;
				glGetProgramiv(retval.handle, GL_LINK_STATUS, &success);
				if (success == GL_FALSE)
				{
					int length = 0;
					glGetProgramiv(retval.handle, GL_INFO_LOG_LENGTH, &length);
					char *log = (char*)malloc(length);
					glGetProgramInfoLog(retval.handle, length, 0, log);
					//std::cout << log << std::endl; 
					printf("%s\n", log);
					free(log);
				}

				// no longer need these! Their functionality has been eaten by the program.
				glDeleteShader(vs);
				glDeleteShader(fs);




				retval.flags.blend = additiveBlend;
				retval.flags.depth = depth;
				retval.flags.cull = faceCull;

				return retval;
			}

			Shader loadShader(const char * v, const char * f, const bool depth, const bool additiveBlend, const bool faceCull)
			{
				std::string vs = stdStyleFileToString(v);
				std::string fs = stdStyleFileToString(f);

				return makeShader(vs.c_str(), fs.c_str(), depth, additiveBlend, faceCull);
			}

			void freeShader(Shader& s)
			{
				glDeleteProgram(s.handle);
				s.handle = 0;
			}

#pragma endregion

#pragma region Tex

			Texture makeTexture(const unsigned &w, const unsigned &h, const unsigned &f, const unsigned char *pixels, const bool &isFloat)
			{
				Texture retval = { 0, w, h, 1, 1, f };

				GLenum e = GL_RGBA;
				GLenum i;

				switch (f)
				{
				case 0: e = GL_DEPTH_COMPONENT; i = GL_DEPTH24_STENCIL8; break;
				case 1: e = GL_RED; i = isFloat ? GL_R32F : e;	break;
				case 2: e = GL_RG; i = isFloat ? GL_RG32F : e; break;
				case 3: e = GL_RGB; i = isFloat ? GL_RGB32F : e; break;
				case 4: e = GL_RGBA; i = isFloat ? GL_RGBA32F : e; break;
				default: assert(false && "File not found or incorrect format.");
				}

				retval.iFormat = i;
				retval.eFormat = e;
				retval.isFloat = isFloat;

				glGenTextures(1, &retval.handle);				// Declaration
				glBindTexture(GL_TEXTURE_2D, retval.handle);    // Scoping

				glTexImage2D(GL_TEXTURE_2D, 0, i, w, h, 0, e, isFloat ? GL_FLOAT : GL_UNSIGNED_BYTE, pixels);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

				glBindTexture(GL_TEXTURE_2D, 0);

				retval.isCubemap = false;

				return retval;
			}

			Texture makeCubeTexture(unsigned width, unsigned height, unsigned channels, const void **pixels, bool isFloat)
			{
				Texture retval = { 0, width, height, channels };

				GLenum eformat = GL_RGBA; // Number of channels goes.
				GLenum iformat = isFloat ? GL_RGBA32F : eformat; // number of channels and the type.
				switch (channels)
				{
				case 0: eformat = GL_DEPTH_COMPONENT; iformat = GL_DEPTH24_STENCIL8; break;

				case 1: eformat = GL_RED;  iformat = isFloat ? GL_R32F : eformat; break;
				case 2: eformat = GL_RG;   iformat = isFloat ? GL_RG32F : eformat; break;
				case 3: eformat = GL_RGB;  iformat = isFloat ? GL_RGB32F : eformat; break;
				case 4: eformat = GL_RGBA; iformat = isFloat ? GL_RGBA32F : eformat; break;
				}

				glGenTextures(1, &retval.handle);
				glBindTexture(GL_TEXTURE_CUBE_MAP, retval.handle);

				for (unsigned i = 0; i < 6; ++i)
					glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, iformat, width, height, 0, eformat, isFloat ? GL_FLOAT : GL_UNSIGNED_BYTE, pixels[i]);

				GL_TEXTURE_CUBE_MAP_NEGATIVE_X;

				glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

				glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

				retval.isCubemap = true;

				return retval;
			}

			Texture loadTexture(const char *path)
			{
				int w, h, f;
				//unsigned d = 0;
				stbi_set_flip_vertically_on_load(true);

				auto p = stbi_load(path, &w, &h, &f, STBI_default);

				Texture tex = makeTexture(w, h, f, p, false);

				stbi_image_free(p);

				return tex;
			}

			Texture loadCubeMap(const char * path_Xpos, const char * path_Xneg, const char * path_Ypos, const char * path_Yneg, const char * path_Zpos, const char * path_Zneg)
			{
				stbi_set_flip_vertically_on_load(false);
				int w[6], h[6], f[6];

				unsigned char *pixels[6];
				pixels[1] = stbi_load(path_Xpos, w + 0, h + 0, f + 0, STBI_default);
				pixels[2] = stbi_load(path_Ypos, w + 1, h + 1, f + 1, STBI_default);
				pixels[4] = stbi_load(path_Zpos, w + 2, h + 2, f + 2, STBI_default);
				pixels[0] = stbi_load(path_Xneg, w + 3, h + 3, f + 3, STBI_default);
				pixels[3] = stbi_load(path_Yneg, w + 4, h + 4, f + 4, STBI_default);
				pixels[5] = stbi_load(path_Zneg, w + 5, h + 5, f + 5, STBI_default);

				bool valid =
					std::min(w + 0, w + 6) == std::max(w + 0, w + 6) &&
					std::min(h + 0, h + 6) == std::max(h + 0, h + 6) &&
					std::min(f + 0, f + 6) == std::max(f + 0, f + 6);

				Texture retval = makeCubeTexture(w[0], h[0], f[0], (const void**)pixels, false);

				for (int i = 0; i < 6; ++i) stbi_image_free(pixels[i]);

				return retval;
			}

			void freeTexture(Texture& t)
			{
				glDeleteTextures(1, &t.handle);
				t = { 0,0,0,0,0,0 };
			}

#pragma endregion

#pragma region FBO

			FrameBuffer makeFrameBuffer(const unsigned width, const unsigned height, const unsigned nTex, const bool *isFloat, const int *channels)
			{
				FrameBuffer fbo{ 0, width, height, nTex };

				glGenFramebuffers(1, &fbo.handle);
				glBindFramebuffer(GL_FRAMEBUFFER, fbo.handle);

				fbo.depth = makeTexture(width, height, 0, 0);
				glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, fbo.depth.handle, 0);

				const GLenum attachments[16] =
				{ GL_COLOR_ATTACHMENT0 , GL_COLOR_ATTACHMENT1 , GL_COLOR_ATTACHMENT2 , GL_COLOR_ATTACHMENT3 ,
					GL_COLOR_ATTACHMENT4 , GL_COLOR_ATTACHMENT5 , GL_COLOR_ATTACHMENT6 , GL_COLOR_ATTACHMENT7 ,
					GL_COLOR_ATTACHMENT8 , GL_COLOR_ATTACHMENT9 , GL_COLOR_ATTACHMENT10, GL_COLOR_ATTACHMENT11,
					GL_COLOR_ATTACHMENT12, GL_COLOR_ATTACHMENT13, GL_COLOR_ATTACHMENT14, GL_COLOR_ATTACHMENT15 };

				for (int i = 0; i < nTex; ++i)
				{
					fbo.tex[i] = makeTexture(width, height, channels ? channels[i] : 4, 0, isFloat ? isFloat[i] : false);
					glFramebufferTexture(GL_FRAMEBUFFER, attachments[i], fbo.tex[i].handle, 0);
				}

				glDrawBuffers(nTex, attachments);
				glBindFramebuffer(GL_FRAMEBUFFER, 0);

				return fbo;
			}

			void clearFrameBuffer(FrameBuffer &fbo)
			{
				glBindFramebuffer(GL_FRAMEBUFFER, fbo.handle);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			}

			void clearFrameBuffer(const unsigned &fbo)
			{
				glBindFramebuffer(GL_FRAMEBUFFER, fbo);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			}

			void freeFrameBuffer(FrameBuffer &fbo)
			{
				for (int i = 0; i < fbo.texCount; ++i)
					freeTexture(fbo.tex[i]);

				glDeleteFramebuffers(1, &fbo.handle);
				fbo = { 0,0,0,0 };
			}

#pragma endregion

#pragma region DrawFunctions

			void drawStart(const Shader &s, const Geometry &g, const FrameBuffer &f)
			{
				if (f.Bind()) ActiveRenderInfo::currentFBO = f;
				if (s.Bind()) ActiveRenderInfo::currentShader = s;
				if (g.Bind()) ActiveRenderInfo::currentGeometry = g;

				s.flags.Enable();

				glViewport(0, 0, f.width, f.height);
			}

			void drawFinal(const Shader &s, const Geometry &g, const FrameBuffer &f)
			{
				glDrawElements(GL_TRIANGLES, g.size, GL_UNSIGNED_INT, 0);
			}

			size_t drawStyle(const size_t idx, const size_t tex, int &val)
			{
				glUniform1i(idx, val);
				return 0;
			}

			size_t drawStyle(const size_t idx, const size_t tex, float &val)
			{
				glUniform1f(idx, val);
				return 0;
			}

			size_t drawStyle(const size_t idx, const size_t tex, Texture &val)
			{
				glActiveTexture(GL_TEXTURE0 + tex);
				glBindTexture(GL_TEXTURE_2D, val.handle);
				glUniform1i(idx, tex);
				return 1;
			}

			size_t drawStyle(const size_t idx, const size_t tex, JTL::Vector2 &val)
			{
				glUniform2fv(idx, 1, val.v);
				return 0;
			}

			size_t drawStyle(const size_t idx, const size_t tex, JTL::Vector3 &val)
			{
				glUniform3fv(idx, 1, val.v);
				return 0;
			}

			size_t drawStyle(const size_t idx, const size_t tex, JTL::Vector4 &val)
			{
				glUniform4fv(idx, 1, val.v);
				return 0;
			}

			size_t drawStyle(const size_t idx, const size_t tex, JTL::Matrix3 &val)
			{
				glUniformMatrix3fv(idx, 1, true, val.m);
				return 0;
			}

			size_t drawStyle(const size_t idx, const size_t tex, JTL::Matrix4 &val)
			{
				glUniformMatrix4fv(idx, 1, true, val.m);
				return 0;
			}

			size_t drawStyle(const size_t idx, const size_t tex, const int &val)
			{
				glUniform1i(idx, val);
				return 0;
			}

			size_t drawStyle(const size_t idx, const size_t tex, const float &val)
			{
				glUniform1f(idx, val);
				return 0;
			}

			size_t drawStyle(const size_t idx, const size_t tex, const Texture &val)
			{
				glActiveTexture(GL_TEXTURE0 + tex);
				if (val.isCubemap) glBindTexture(GL_TEXTURE_CUBE_MAP, val.handle);
				else glBindTexture(GL_TEXTURE_2D, val.handle);
				glUniform1i(idx, tex);
				return 1;
			}

			size_t drawStyle(const size_t idx, const size_t tex, const JTL::Vector2 &val)
			{
				glUniform2fv(idx, 1, val.v);
				return 0;
			}

			size_t drawStyle(const size_t idx, const size_t tex, const JTL::Vector3 &val)
			{
				glUniform3fv(idx, 1, val.v);
				return 0;
			}

			size_t drawStyle(const size_t idx, const size_t tex, const JTL::Vector4 &val)
			{
				glUniform4fv(idx, 1, val.v);
				return 0;
			}

			size_t drawStyle(const size_t idx, const size_t tex, const JTL::Matrix3 &val)
			{
				glUniformMatrix3fv(idx, 1, true, val.m);
				return 0;
			}

			size_t drawStyle(const size_t idx, const size_t tex, const JTL::Matrix4 &val)
			{
				glUniformMatrix4fv(idx, 1, true, val.m);
				return 0;
			}

#pragma endregion

		}
	}
}