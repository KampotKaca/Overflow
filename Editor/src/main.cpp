#include "pch.h"
#include "Editor.h"

using namespace overflow::edit;

int main()
{
	Editor::Init();
	Editor::Run();
	Editor::Terminate();

	return 0;
}
