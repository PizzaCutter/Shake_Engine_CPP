#pragma once

#include "Shake/Window.h"
#include "include/GLFW/glfw3.h"

namespace Shake
{
    class WindowsWindow : public Shake::Window
    {
    public:
        WindowsWindow(const WindowProps& props);
        virtual ~WindowsWindow();

        void OnUpdate() override;

        unsigned GetWidth() const override { return m_Data.Width; };
        unsigned GetHeight() const override { return m_Data.Height; };

        void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; };
        void SetVSync(bool enabled) override;
        bool IsVSync() const override;

        void* GetNativeWindow() const override;
    private:
        virtual void Init(const Shake::WindowProps& props);
        void SetupGLFWWindowCallbacks() const;
        virtual void Shutdown();

    private:
        GLFWwindow* m_Window;

        struct WindowData
        {
            std::string Title;
            unsigned int Width, Height;
            bool VSync;

            EventCallbackFn EventCallback;
        };

        WindowData m_Data;
    };
}
