#include "file.hh"
#include "archive.hh"
#include <iostream>
#include <StormLib.h>

namespace storm {

File::File() : mode(Invalid), open(false) {
	
}

File::File(const File& file) {
	mode = file.mode;
	archive = file.archive;
// 	diskFile = file.diskFile;
	filename = file.filename;
	fileHandle = file.fileHandle;
	open = file.open;
}

File::File(const std::string& filename, ArchiveHandle archive) : mode(MPQ), filename(filename), open(false) {
	
}

File::File(const std::string& filename) : mode(Disk), filename(filename), open(false) {
	
}

File::~File() {
	close();
}

unsigned int File::write(char* data, unsigned int count) throw(InvalidOperation, MPQError) {
	throw InvalidOperation("Writing to files is not yet implemented.");
	return 0;
}

unsigned int File::read(char* data, unsigned int count) throw(InvalidOperation, MPQError) {
	if (mode == Invalid) throw InvalidOperation("Cannot read from an invalid file.");
	if (mode == MPQ) {
		HANDLE mpqHandle = archive->getHandle();
		if (mpqHandle == 0) throw InvalidOperation("Invalid MPQ handle. Was the archive closed prematurely?");
		
	}
	return 0;
}

File& File::openRead() throw (InvalidOperation, MPQError, FileNotFound) {
	if (mode == Invalid) throw InvalidOperation("Cannot open an invalid file.");
	if (mode == MPQ) {
		HANDLE mpqHandle = archive->getHandle();
		if (mpqHandle == 0) throw InvalidOperation("Invalid MPQ handle. Was the archive closed prematurely?");
		if (!SFileOpenFileEx(mpqHandle, filename.c_str(), 0, &fileHandle)) throw MPQError("Error opening file " + filename);
		open = true;
	} else throw InvalidOperation("Opening Disk files is not yet implemented.");
	return *this;
}

void File::close() {
	if (open) {
		if (mode == MPQ) {
			HANDLE mpqHandle = archive->getHandle();
			if (mpqHandle == 0) throw InvalidOperation("Invalid MPQ handle. Was the archive closed prematurely?");
			SFileCloseFile(fileHandle);
		}
		else throw InvalidOperation("File operations not yet implemented for Disk");
	}
}

File& File::operator=(const File& file) {
	if (mode == MPQ) {
		
	}
	return *this;
}

bool File::isOpen() const {
	return open;
}

}
