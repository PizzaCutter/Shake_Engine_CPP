#include "sepch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRenderAPI.h"

namespace Shake
{
   RenderAPI* RenderCommand::s_renderAPI = new OpenGLRenderAPI();     
}