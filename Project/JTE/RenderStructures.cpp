#include "RenderStructures.h"
#include "RenderDeclarations.h"

JTL::SIM::REN::FrameBuffer JTL::SIM::REN::ActiveRenderInfo::currentFBO = JTL::SIM::REN::FrameBuffer{};
JTL::SIM::REN::Shader JTL::SIM::REN::ActiveRenderInfo::currentShader = JTL::SIM::REN::Shader{};
JTL::SIM::REN::Geometry JTL::SIM::REN::ActiveRenderInfo::currentGeometry = JTL::SIM::REN::Geometry{};
bool JTL::SIM::REN::ActiveRenderInfo::depthState = false;
bool JTL::SIM::REN::ActiveRenderInfo::cullState = false;
bool JTL::SIM::REN::ActiveRenderInfo::blendState = false;

namespace JTL
{
	namespace SIM
	{
		namespace REN
		{

#ifdef GL

			bool Geometry::Bind() const
			{
				if (this != &ActiveRenderInfo::currentGeometry) { glBindVertexArray(vao); return true; }
				else return false;
			}

			bool Shader::Bind() const
			{
				if (this != &ActiveRenderInfo::currentShader) { glUseProgram(handle); return true; }
				else return false;
			}

			void ShaderFlags::Enable() const
			{
				if (ActiveRenderInfo::depthState != depth)
				{
					ActiveRenderInfo::depthState = depth;

					if (depth == true) 
					{
						glEnable(GL_DEPTH_TEST);
						glDepthFunc(GL_LEQUAL);
					}
					else
						glDisable(GL_DEPTH_TEST);
				}

				if (ActiveRenderInfo::cullState != cull)
				{
					ActiveRenderInfo::cullState = cull;

					if (cull == true)
						glEnable(GL_CULL_FACE);
					else
						glDisable(GL_CULL_FACE);
				}

				if (ActiveRenderInfo::blendState != blend)
				{
					ActiveRenderInfo::blendState = blend;

					if (blend == true)
					{
						glEnable(GL_BLEND);
						glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
					}
					else
						glDisable(GL_BLEND);
				}
			}

			bool FrameBuffer::Bind() const
			{
				if (this != &ActiveRenderInfo::currentFBO) { glBindFramebuffer(GL_FRAMEBUFFER, handle); return true; }
				else return false;
			}

			void FrameBuffer::Resize(const int &w, const int &h)
			{ width = w; height = h; for each (Texture t in tex) { t.Resize(w,h); } depth.Resize(w,h); }

#endif // GL

			void Texture::Resize(const int &w, const int &h)
			{
				width = w;
				height = h;
				glBindTexture(GL_TEXTURE_2D, handle);    // Scoping

				glTexImage2D(GL_TEXTURE_2D, 0, iFormat, width, height, 0, eFormat, isFloat ? GL_FLOAT : GL_UNSIGNED_BYTE, nullptr);
			}

		}
	}
}