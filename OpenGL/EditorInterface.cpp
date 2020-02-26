#include "EditorInterface.h"
#include "TheDebug.h"
#include "imgui/imgui.h"


//-------------------------------------------------------------------------------
//Constructor
//-------------------------------------------------------------------------------
EditorInterface::EditorInterface()
{
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
    //DrawConsole();
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
    ImGui::SetNextWindowSize(ImVec2(500, 400), ImGuiCond_FirstUseEver);
    ImGui::Begin("Example: Log", &m_isConsoleOpen);
    if (ImGui::SmallButton("[Debug] Add 5 entries"))
    {
        static int counter = 0;
        for (int n = 0; n < 5; n++)
        {
            const char* categories[3] = { "info", "warn", "error" };
            const char* words[] = { "Bumfuzzled", "Cattywampus", "Snickersnee", "Abibliophobia", "Absquatulate", "Nincompoop", "Pauciloquent" };
            //log.AddLog("[%05d] [%s] Hello, current time is %.1f, here's a word: '%s'\n",
            //    ImGui::GetFrameCount(), categories[counter % IM_ARRAYSIZE(categories)], ImGui::GetTime(), words[counter % IM_ARRAYSIZE(words)]);
            counter++;
        }
    }
    ImGui::End();

    // Actually call in the regular Log helper (which will Begin() into the same window as we just did)
    /*log.Draw("Example: Log", &m_isConsoleOpen);*/
}

//-------------------------------------------------------------------------------
//Draw Hierarchy 
//-------------------------------------------------------------------------------
void EditorInterface::DrawHierarchy()
{
}

//-------------------------------------------------------------------------------
//Draw Inspector
//-------------------------------------------------------------------------------
void EditorInterface::DrawInspector()
{
}

void EditorInterface::DrawTopMenu()
{
}
