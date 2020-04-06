#ifndef EDITORINTERFACE_H
#define EDITORINTERFACE_H

class EditorInterface
{
public:

	EditorInterface();
	~EditorInterface();

public:

	void DrawEditor();

public:

	void DrawConsole();
	void DrawHierarchy();
	void DrawInspector();
	void DrawTopMenu();
	void DrawStateSlider();

public:

	void SetIsConsoleActive(const bool& value);
	void SetIsHierarchyActive(const bool& value);
	void SetIsInspectorActive(const bool& value);

public:

	bool GetIsConsoleActive() const;
	bool GetIsHierarchyActive() const;
	bool GetIsInspectorActive() const;

private:

	bool m_isConsoleOpen;
	bool m_isHierarchyOpen;
	bool m_isInspectorOpen;
	bool m_isSliderOpen;

	int currentScene = 1;
};

#endif