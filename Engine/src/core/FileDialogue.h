#ifndef FILE_DIALOGUE_H
#define FILE_DIALOGUE_H

#include "utils.h"

namespace overflow
{
	class FileDialogue
	{
	public:
		virtual ~FileDialogue() = default;

		virtual std::string OpenFile(const char* filter) = 0;
		virtual std::string OpenFolder(const char* duty) = 0;
		virtual std::string SaveFile(const char* filter) = 0;

		static ref<FileDialogue> CreateFileDialogue();
	};
}

#endif //FILE_DIALOGUE_H
