#include "pch.h"
#include "FileDialogue.h"

#if PLATFORM_WINDOWS
#include "platform/windows/Win_FileDialogue.h"
#endif

namespace overflow
{
	ref<FileDialogue> FileDialogue::CreateFileDialogue()
	{
#if PLATFORM_WINDOWS
		return make_ref(Win_FileDialogue);
#else
		return nullptr;
#endif
	}
}