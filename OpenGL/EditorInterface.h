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

private:
};

#endif