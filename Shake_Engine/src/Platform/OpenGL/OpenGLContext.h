#pragma once

#include "Shake/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Shake
{
   class OpenGLContext : public GraphicsContext
   {
   public:
      OpenGLContext(GLFWwindow* windowHandle);
      
      void Init() override;
      void SwapBuffers() override;
   private:
      GLFWwindow* m_WindowHandle;
   };
}
