#include "archive.hh"

#include <iostream>

namespace storm {

Archive::Archive(const std::string& filename, bool create) throw(FileNotFound, InvalidArchive) : mpqHandle(0), open(false) {
	file.exceptions(std::ios::eofbit | std::ios::failbit | std::ios::badbit);
	try {
		file.open(filename.c_str());
	} catch (std::exception e) {
		throw FileNotFound(filename);
	}
	int nError = ERROR_SUCCESS;

	if(!SFileOpenArchive(filename.c_str(), 0, 0, &mpqHandle)) nError = GetLastError();
	if (nError != ERROR_SUCCESS) throw InvalidArchive(filename);
	
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

File& Archive::operator[](const std::string& filename) {
	if (!hasFile(filename)) throw FileNotFound(filename);
	if (files.find(filename) != files.end()) return files[filename];
	else {
		files[filename] = File(filename, ArchiveHandle(this));
	}
}

const File& Archive::operator[](const std::string& filename) const {
	if (!hasFile(filename)) throw FileNotFound(filename);
	if (files.find(filename) != files.end()) return files.at(filename);
	else {
		throw InvalidOperation("Not yet implemented.");
	}
}

HANDLE Archive::getHandle() const {
	if (!open) return 0;
	return mpqHandle;
}
}
