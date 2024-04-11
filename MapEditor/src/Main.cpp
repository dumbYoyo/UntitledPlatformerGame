#include "Engine/Scene.h"
#include "Editor.h"

int main()
{
	Scene* editor = new Editor();
	editor->Run();
	delete editor;

	return 0;
}