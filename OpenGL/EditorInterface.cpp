#include "EditorInterface.h"
#include "TheDebug.h"
#include "imgui/imgui.h"
#include "Game.h"


//-------------------------------------------------------------------------------
//Constructor
//-------------------------------------------------------------------------------
EditorInterface::EditorInterface()
{
    #define HI(v)   ImVec4(0.502f, 0.075f, 0.256f, v)
    #define MED(v)  ImVec4(0.455f, 0.198f, 0.301f, v)
    #define LOW(v)  ImVec4(0.232f, 0.201f, 0.271f, v)
        // backgrounds (@todo: complete with BG_MED, BG_LOW)
    #define BG(v)   ImVec4(0.200f, 0.220f, 0.270f, v)
    // text
    #define TEXT(v) ImVec4(0.860f, 0.930f, 0.890f, v)

    auto& style = ImGui::GetStyle();
    style.Colors[ImGuiCol_Text] = TEXT(0.78f);
    style.Colors[ImGuiCol_TextDisabled] = TEXT(0.28f);
    style.Colors[ImGuiCol_WindowBg] = ImVec4(0.13f, 0.14f, 0.17f, 1.00f);
    style.Colors[ImGuiCol_ChildBg] = BG(0.58f);
    style.Colors[ImGuiCol_PopupBg] = BG(0.9f);
    style.Colors[ImGuiCol_Border] = ImVec4(0.31f, 0.31f, 1.00f, 0.00f);
    style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    style.Colors[ImGuiCol_FrameBg] = BG(1.00f);
    style.Colors[ImGuiCol_FrameBgHovered] = MED(0.78f);
    style.Colors[ImGuiCol_FrameBgActive] = MED(1.00f);
    style.Colors[ImGuiCol_TitleBg] = LOW(1.00f);
    style.Colors[ImGuiCol_TitleBgActive] = HI(1.00f);
    style.Colors[ImGuiCol_TitleBgCollapsed] = BG(0.75f);
    style.Colors[ImGuiCol_MenuBarBg] = BG(0.47f);
    style.Colors[ImGuiCol_ScrollbarBg] = BG(1.00f);
    style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.09f, 0.15f, 0.16f, 1.00f);
    style.Colors[ImGuiCol_ScrollbarGrabHovered] = MED(0.78f);
    style.Colors[ImGuiCol_ScrollbarGrabActive] = MED(1.00f);
    style.Colors[ImGuiCol_CheckMark] = ImVec4(0.71f, 0.22f, 0.27f, 1.00f);
    style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.47f, 0.77f, 0.83f, 0.14f);
    style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.71f, 0.22f, 0.27f, 1.00f);
    style.Colors[ImGuiCol_Button] = ImVec4(0.47f, 0.77f, 0.83f, 0.14f);
    style.Colors[ImGuiCol_ButtonHovered] = MED(0.86f);
    style.Colors[ImGuiCol_ButtonActive] = MED(1.00f);
    style.Colors[ImGuiCol_Header] = MED(0.76f);
    style.Colors[ImGuiCol_HeaderHovered] = MED(0.86f);
    style.Colors[ImGuiCol_HeaderActive] = HI(1.00f);
    //style.Colors[ImGuiCol_Column] = ImVec4(0.14f, 0.16f, 0.19f, 1.00f);
    //style.Colors[ImGuiCol_Column] = ImVec4(0.14f, 0.16f, 0.19f, 1.00f);
    //style.Colors[ImGuiCol_ColumnHovered] = MED(0.78f);
    //style.Colors[ImGuiCol_ColumnActive] = MED(1.00f);
    style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.47f, 0.77f, 0.83f, 0.04f);
    style.Colors[ImGuiCol_ResizeGripHovered] = MED(0.78f);
    style.Colors[ImGuiCol_ResizeGripActive] = MED(1.00f);
    style.Colors[ImGuiCol_PlotLines] = TEXT(0.63f);
    style.Colors[ImGuiCol_PlotLinesHovered] = MED(1.00f);
    style.Colors[ImGuiCol_PlotHistogram] = TEXT(0.63f);
    style.Colors[ImGuiCol_PlotHistogramHovered] = MED(1.00f);
    style.Colors[ImGuiCol_TextSelectedBg] = MED(0.43f);
    // [...]
    style.Colors[ImGuiCol_ModalWindowDarkening] = BG(0.73f);

    style.WindowPadding = ImVec2(6, 4);
    style.WindowRounding = 0.0f;
    style.FramePadding = ImVec2(5, 2);
    style.FrameRounding = 3.0f;
    style.ItemSpacing = ImVec2(7, 1);
    style.ItemInnerSpacing = ImVec2(1, 1);
    style.TouchExtraPadding = ImVec2(0, 0);
    style.IndentSpacing = 6.0f;
    style.ScrollbarSize = 12.0f;
    style.ScrollbarRounding = 16.0f;
    style.GrabMinSize = 20.0f;
    style.GrabRounding = 2.0f;

    style.WindowTitleAlign.x = 0.50f;

    style.Colors[ImGuiCol_Border] = ImVec4(0.539f, 0.479f, 0.255f, 0.162f);
    style.FrameBorderSize = 0.0f;
    style.WindowBorderSize = 1.0f;
}

//-------------------------------------------------------------------------------
//Destructor
//-------------------------------------------------------------------------------
EditorInterface::~EditorInterface()
{
}

//-------------------------------------------------------------------------------
//Draw Editor
//-------------------------------------------------------------------------------
void EditorInterface::DrawEditor()
{
    DrawConsole();
    DrawHierarchy();
    DrawInspector();
	//Draw Demo Window
	ImGui::ShowDemoWindow();
}

//-------------------------------------------------------------------------------
//Draw Console
//-------------------------------------------------------------------------------
void EditorInterface::DrawConsole()
{
    //static ExampleAppLog log;

    // For the demo: add a debug button _BEFORE_ the normal log window contents
    // We take advantage of a rarely used feature: multiple calls to Begin()/End() are appending to the _same_ window.
    // Most of the contents of the window will be added by the log.Draw() call.
    
    ImGui::SetWindowPos(ImVec2(300, 150), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(500, 200), ImGuiCond_FirstUseEver);
    ImGui::Begin("Console", &m_isConsoleOpen);

    if (ImGui::Button("Clear")) { TheDebug::Instance()->Clear(); } ImGui::SameLine();
    if (ImGui::Button("Stack")) { TheDebug::Instance()->Stack(); } ImGui::SameLine();
    if (ImGui::Button("Warning")) { TheDebug::Instance()->ShowWarning(); } ImGui::SameLine();
    if (ImGui::Button("Error")) { TheDebug::Instance()->ShowError(); } ImGui::SameLine();

    ImGui::Separator();

    //Loop Alerts
    if (TheDebug::Instance()->GetShowingAlerts())
    {
        for (size_t i = 0; i < TheDebug::Instance()->GetAlerts().size(); i++)
        {
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.4f, 0.4f, 1.0f));

            ImGui::TextUnformatted(TheDebug::GetAlerts()[i].c_str());

            ImGui::PopStyleColor();
        }
    }

    //Loop Warnings
    if (TheDebug::Instance()->GetShowingWarnings())
    {
        for (size_t i = 0; i < TheDebug::Instance()->GetWarnings().size(); i++)
        {
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.8f, 0.6f, 1.0f));

            ImGui::TextUnformatted(TheDebug::GetWarnings()[i].c_str());

            ImGui::PopStyleColor();
        }
    }

    //Loop Logs
    for (size_t i = 0; i < TheDebug::Instance()->GetLogs().size(); i++)
    {
        ImGui::TextUnformatted(TheDebug::GetLogs()[i].c_str());
    }

    //AutoScroll
    if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
        ImGui::SetScrollHereY(1.0f);

    ImGui::End();


    // Actually call in the regular Log helper (which will Begin() into the same window as we just did)
    /*log.Draw("Example: Log", &m_isConsoleOpen);*/
}

//-------------------------------------------------------------------------------
//Draw Hierarchy 
//-------------------------------------------------------------------------------
void EditorInterface::DrawHierarchy()
{
    ImGui::SetWindowPos(ImVec2(1000, 150), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(300, 400), ImGuiCond_Appearing);
    ImGui::Begin("Hierarchy", &m_isHierarchyOpen);


    struct funcs
    {
        static void ShowDummyObject(const char* prefix, int uid)
        {
            ImGui::PushID(uid);                      // Use object uid as identifier. Most commonly you could also use the object pointer as a base ID.
            ImGui::AlignTextToFramePadding();  // Text and Tree nodes are less high than regular widgets, here we add vertical spacing to make the tree lines equal high.
            bool node_open = ImGui::TreeNode("Object", "%s_%u", prefix, uid);
            ImGui::AlignTextToFramePadding();
 /*           ImGui::Text("my sailor is rich");*/
            if (node_open)
            {

                //if (children)
                //{
                //    //for all the children
                //    ShowDummyObject("Child", 424242);
                //}

                ImGui::TreePop();
            }
            ImGui::PopID();
        }
    };

    int i = 0;

    for (auto& str : Game::Instance()->GetCurrentScene()->GetHierarchy())
    {
        i++;
        funcs::ShowDummyObject(str->Getname().c_str(), i);
    }

    ImGui::Separator();

    ImGui::End();
}

//-------------------------------------------------------------------------------
//Draw Inspector
//-------------------------------------------------------------------------------
void EditorInterface::DrawInspector()
{
    ImGui::SetNextWindowSize(ImVec2(300, 500), ImGuiCond_Appearing);
    ImGui::Begin("Inspector", &m_isInspectorOpen);

    if (Game::Instance()->GetCurrentScene()->GetSelectedObject() != NULL)
    {
        GameObject* selectedObj = Game::Instance()->GetCurrentScene()->GetSelectedObject();

        glm::vec3 tempPos = selectedObj->GetTransform()->GetLocalPos();
        glm::vec3 tempRot = selectedObj->GetTransform()->GetLocalRot();
        glm::vec3 tempScale = selectedObj->GetTransform()->GetLocalScale();
        glm::vec3 tempAmbient = selectedObj->GetMaterial()->GetAmbient();
        glm::vec3 tempDiffuse = selectedObj->GetMaterial()->GetDiffuse();
        glm::vec3 tempSpecular = selectedObj->GetMaterial()->GetSpecular();

        float position[3] = { tempPos.x, tempPos.y, tempPos.z };
        float rotation[3] = { tempRot.x, tempRot.y, tempRot.z };
        float scale[3] = { tempScale.x, tempScale.y, tempScale.z };
        float Ambient[3] = { tempScale.x, tempScale.y, tempScale.z };
        float Diffuse[3] = { tempScale.x, tempScale.y, tempScale.z };
        float specular[3] = { tempScale.x, tempScale.y, tempScale.z };

        ImGui::Text("Transform");

        if (ImGui::InputFloat3("Position", position, "%.3f", ImGuiInputTextFlags_AlwaysInsertMode))
        {
            if (position[0] != selectedObj->GetTransform()->GetLocalPos().x)
            {
                float xOffset = position[0] - tempPos.x;
                selectedObj->Translate(glm::vec3(xOffset, 0.0f, 0.0f));

            }
            if (position[0] != selectedObj->GetTransform()->GetLocalPos().x)
            {

                float xOffset = position[0] - tempPos.y;
                selectedObj->Translate(glm::vec3(0.0f, xOffset, 0.0f));

            }
            if (position[0] != selectedObj->GetTransform()->GetLocalPos().x)
            {

                float xOffset = position[0] - tempPos.z;
                selectedObj->Translate(glm::vec3(0.0f, 0.0f, xOffset));
            }
        }

        if (ImGui::InputFloat3("Rotation", rotation, "%.3f", ImGuiInputTextFlags_AlwaysInsertMode))
        {
            selectedObj->Rotate(rotation[0], glm::vec3(1.0f, 0.0f, 0.0f));
            selectedObj->Rotate(rotation[1], glm::vec3(0.0f, 1.0f, 0.0f));
            selectedObj->Rotate(rotation[2], glm::vec3(0.0f, 0.0f, 1.0f));
        }

        if (ImGui::InputFloat3("Scale", scale, "%.3f", ImGuiInputTextFlags_AlwaysInsertMode))
        {
            TheDebug::Log("test", LOG);

            if (scale[0] != tempScale.x)
            {
                selectedObj->Scale(glm::vec3(scale[0], 1.0f, 1.0f));
            }

            if (scale[1] != tempScale.y)
            {
                selectedObj->Scale(glm::vec3(1.0f, scale[1], 1.0f));
            }

            if (scale[2] != tempScale.z)
            {
                selectedObj->Scale(glm::vec3(1.0f, 1.0f, scale[2]));
            }
        }

        if (selectedObj->GetMaterial() != nullptr)
        {
      /*      ImGui::ColorEdit3("Ambient");*/
            
            
        }
        if (selectedObj->GetHasPhong())
        {
            //Maybe make class render and make it a component
        }
    }

    ImGui::End();
}

//-------------------------------------------------------------------------------
//Draw Top Menu
//-------------------------------------------------------------------------------
void EditorInterface::DrawTopMenu()
{
}
