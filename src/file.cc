#include "file.hh"
#include "archive.hh"
#include <iostream>
#include <StormLib.h>

namespace storm {

File::File() : mode(Invalid), ioMode(Closed), open(false) {
	
}

File::File(const File& file) {
	mode = file.mode;
	ioMode = file.ioMode;
	archive = file.archive;
	filename = file.filename;
	fileHandle = file.fileHandle;
	open = file.open;
}

File::File(const std::string& filename, ArchiveHandle archive) : mode(MPQ), ioMode(Closed), archive(archive), filename(filename), open(false) {
	
}

File::File(const std::string& filename) : mode(Disk), ioMode(Closed), filename(filename), open(false) {
	
}

File::~File() {
	close();
}

File& File::operator=(const File& file) {
	if (mode == MPQ) {
		
	} else if (mode == Invalid) {
		mode = file.mode;
		ioMode = file.ioMode;
		archive = file.archive;
		filename = file.filename;
		fileHandle = file.fileHandle;
		open = file.open;
	}
	return *this;
}

// bool WINAPI SFileWriteFile(
//   HANDLE hFile,                     // Handle to the file
//   const void * pvData,              // Pointer to data to be written
//   DWORD dwSize,                     // Size of the data pointed by pvData
//   DWORD dwCompression               // Specifies compression of the data block
// );

unsigned int File::write(const char* data, unsigned int count) throw(InvalidOperation, MPQError) {
	if (mode == Invalid) throw InvalidOperation("Cannot write to an invalid file.");
	if (ioMode == Read) throw InvalidOperation("Cannot write to a read-mode file.");
	if (!SFileWriteFile(fileHandle, data, count, MPQ_COMPRESSION_ZLIB)) throw MPQError("Error while writing to file.");
	return 0;
}

unsigned int File::read(char* data, unsigned int count) throw(InvalidOperation, MPQError) {
	if (mode == Invalid) throw InvalidOperation("Cannot read from an invalid file.");
	if (ioMode == Write) throw InvalidOperation("Cannot read from a write-mode file.");
	if (mode == MPQ) {
		HANDLE mpqHandle = archive->getHandle();
		if (mpqHandle == 0) throw InvalidOperation("Invalid MPQ handle. Was the archive closed prematurely?");
		unsigned int actualCount = 0;
		if (!SFileReadFile(fileHandle, data, count, &actualCount, 0)) {
			throw MPQError("Error while reading from file " + filename);
		}
		return actualCount;
	}
	return 0;
}

File& File::openRead() throw (InvalidOperation, MPQError, FileNotFound) {
	if (mode == Invalid) throw InvalidOperation("Cannot open an invalid file.");
	if (mode == MPQ) {
		if (ioMode != Closed) throw InvalidOperation("Cannot open a file that is already open.");
		HANDLE mpqHandle = archive->getHandle();
		if (mpqHandle == 0) throw InvalidOperation("Invalid MPQ handle. Was the archive closed prematurely?");
		if (!SFileOpenFileEx(mpqHandle, filename.c_str(), 0, &fileHandle)) throw MPQError("Error opening file for reading: " + filename);
		open = true;
		ioMode = Read;
	} else throw InvalidOperation("Opening Disk files is not yet implemented.");
	return *this;
}

// bool WINAPI SFileCreateFile(
//   HANDLE hMpq,                      // Handle to the MPQ
//   const char * szArchivedName,      // The name under which the file will be stored
//   TMPQFileTime * pFT                // Specifies the date and file time
//   DWORD dwFileSize                  // Specifies the size of the file
//   LCID lcLocale                     // Specifies the file locale
//   DWORD dwFlags                     // Specifies archive flags for the file
//   HANDLE * phFile                   // Returned file handle
// );

File& File::openWrite(unsigned int fileSize) throw (InvalidOperation, MPQError) {
	if (mode == Invalid) throw InvalidOperation("Cannot open an invalid file.");
	if (mode == Disk) throw InvalidOperation("Not yet implemented.");
	if (mode == MPQ) {
		if (ioMode != Closed) throw InvalidOperation("Cannot open a file that is already open.");
		HANDLE mpqHandle = archive->getHandle();
		if (mpqHandle == 0) throw InvalidOperation("Invalid MPQ handle. Was the archive closed prematurely?");
		if (!SFileCreateFile(mpqHandle, filename.c_str(), 0, fileSize, 0, 0, &fileHandle)) throw MPQError("Error opening file for writing: " + filename);
		open = true;
		ioMode = Write;
	}
	return *this;
}

void File::close() {
	if (open) {
		if (mode == MPQ) {
			if (ioMode == Read) {
				HANDLE mpqHandle = archive->getHandle();
				if (mpqHandle == 0) throw InvalidOperation("Invalid MPQ handle. Was the archive closed prematurely?");
				SFileCloseFile(fileHandle);
			} else if (ioMode == Write) {
				if (!SFileFinishFile(fileHandle)) {
					if (GetLastError() == ERROR_CAN_NOT_COMPLETE) throw MPQError("Amount of bytes written to file exceeds size declared in call to openWrite.");
					else throw MPQError("Error finalizing file.");
				}
			}
		}
		else throw InvalidOperation("File operations not yet implemented for Disk");
	}
}

bool File::isOpen() const {
	return open;
}

}
