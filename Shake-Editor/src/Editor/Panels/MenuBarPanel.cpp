#include "MenuBarPanel.h"

#include "imgui/imgui.h"
#include "Shake/Core/Application.h"

namespace Shake
{
    MenuBarPanel::MenuBarPanel(SharedPtr<SceneX> scene)
        : BasePanel(scene)
    {
        
    }

    void MenuBarPanel::OnImGuiRender()
    {
        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("Docking"))
            {
                // Disabling fullscreen would allow the window to be moved to the front of other windows,
                // which we can't undo at the moment without finer window depth/z control.
                //ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen_persistant);

                if (ImGui::MenuItem("Exit", "", (ImGuiDockNodeFlags_None & ImGuiDockNodeFlags_NoSplit) != 0))
                {
                    Shake::Application::Get().Close();
                }

                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        } 
    }
}
