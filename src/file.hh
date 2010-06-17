#ifndef _STORM_FILE_HH_
#define _STORM_FILE_HH_

#include <StormLib.h>
#include <string>
#include <fstream>
#include <exception>

namespace storm {

/** 
 * @brief as the name implies, thrown when a file is not found
 * @author amro
 */
class FileNotFound : public std::exception {
	std::string data;
public:
	FileNotFound(const std::string& filename) : data("File not found: " + filename) { };
	virtual ~FileNotFound() throw() { };

	inline virtual const char* what() const throw() {return data.c_str();};
};

/** 
 * @brief thrown when an operation is attempted on an invalid File object
 * @author amro
 */
class InvalidFile : public std::exception {
	std::string data;
public:
	InvalidFile(const std::string& context) : data("Invalid File. " + context + " requires a valid file.") { };
	virtual ~InvalidFile() throw() { };

	inline virtual const char* what() const throw() {return data.c_str();};
};

/**
 * @brief Represents a file, either on disk or in an archive
 * @author amro
 */
class File {
public:
	/**
	 * Operating mode for this file. This affects the behavior
	 * of read and write operations.
	 */
	enum FileMode {
		Disk,
		MPQ,
		Invalid
	};
	
	/**
	 * Construct a File object attached to fileName on disk
	 * @arg fileName full path to the file on disk.
	 */
	File(const std::string& fileName);
	
	/**
	 * Constructs a default, inoperative File object
	 */
	File();
	
	///Opens the file for reading and writing, if necessary.
	void open();
	
	/**
	 * Attempts to write count bytes from buffer into the file.
	 */
	unsigned int write(char* buffer, unsigned int count) throw (InvalidFile);
	
	/**
	 * Attempts to read count bytes from file into the buffer.
	 */
	unsigned int read(char* buffer, unsigned int count) throw (InvalidFile);
private:
	///Operating mode
	FileMode mode;
	
	///File's StormLib handle, if in MPQ mode
	HANDLE mpqHandle;
	
	///File on disk, if in Disk mode
	std::fstream fileHandle;
};

}

#endif
