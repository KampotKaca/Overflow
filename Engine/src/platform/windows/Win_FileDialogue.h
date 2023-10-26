#ifndef WIN_FILE_DIALOGUE_H
#define WIN_FILE_DIALOGUE_H

#include "core/FileDialogue.h"

namespace overflow
{
	class Win_FileDialogue : public FileDialogue
	{
	public:
		Win_FileDialogue() = default;
		~Win_FileDialogue() override = default;

		std::string OpenFile(const char *filter) override;
		std::string SaveFile(const char *filter) override;
	};
}

#endif //WIN_FILE_DIALOGUE_H
