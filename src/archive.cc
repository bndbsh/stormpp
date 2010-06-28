#include "archive.hh"

#include <sys/stat.h>
#include <iostream>

namespace storm {

Archive::Archive(const std::string& filename, unsigned int hashtableSize) throw(FileNotFound, InvalidOperation, InvalidArchive) : mpqHandle(0), open(false) {
	struct stat fileInfo; 
	if(stat(filename.c_str(), &fileInfo) == 0) { 
		if (hashtableSize > 0) throw InvalidOperation("File already exists: " + filename);
		if (!SFileOpenArchive(filename.c_str(), 0, 0, &mpqHandle)) throw InvalidArchive(filename);
	} else {
		if (hashtableSize == 0) throw FileNotFound(filename);
		if (errno == ENOTDIR) throw InvalidOperation("path does not exist"); ///TODO: improve
		if (!SFileCreateArchive(filename.c_str(), 0, hashtableSize, &mpqHandle)) throw InternalError();
	}
	open = true;
}

Archive::~Archive() {
	if (open) SFileCloseArchive(mpqHandle);
}

void Archive::flush() {
	SFileFlushArchive(mpqHandle);
}

bool Archive::hasFile(const std::string& filename) const {
	std::string name = filename;
	int index = name.find('/');
	while (index != -1) {
		name.replace(index, 1, "\\");
		index = name.find('/');
	}
	return SFileHasFile(mpqHandle, name.c_str());
}

bool Archive::isOpen() const {
	return open;
}

File Archive::operator[](const std::string& filename) {
	return File(filename, ArchiveHandle(this));
}

HANDLE Archive::getHandle() const {
	if (!open) return 0;
	return mpqHandle;
}
}
