#pragma once


#include "Shake/Window.h"

struct GLFWwindow;

namespace Shake
{
    class GraphicsContext;

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

        inline void* GetNativeWindow() const override { return m_Window; };
    private:
        virtual void Init(const Shake::WindowProps& props);
        void SetupGLFWWindowCallbacks() const;
        virtual void Shutdown();

    private:
        GLFWwindow* m_Window;
        GraphicsContext* m_Context;
        
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
