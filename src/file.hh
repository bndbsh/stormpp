#ifndef _STORM_FILE_HH_
#define _STORM_FILE_HH_

#include <StormLib.h>
#include <string>
#include <fstream>
#include "exceptions.hh"

#include "object.hh"

namespace storm {
class Archive;
typedef boost::intrusive_ptr<Archive> ArchiveHandle;
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
class File : public Object {
public:
	/**
	 * Operating mode for this file. This affects the behavior
	 * of read and write operations.
	 */
	enum FileMode {
		Disk = 0,
		MPQ = 1,
		Invalid = 2
	};
	
	/**
	 * IO mode for this file. This affects which operations
	 * are permitted.
	 */
	enum IOMode {
		Read = 0,
		Write = 1,
		Closed = 2
	};
	
	/**
	 * Construct a File object attached to filename on disk
	 * @arg filename full path to the file on disk.
	 */
	File(const std::string& filename);
	
	/**
	 * Constructs a File object attached to an archive
	 * @arg filename filename in the archive
	 * @arg archive handle to the archive
	 */
	File(const std::string& filename, ArchiveHandle archive);
	
	///Constructs a default, inoperative File object
	File();
	
	///Copy constructor
	File(const File& file);
	
	///Cleanup
	~File();
	
	///Closes the file
	void close();
	
	/**
	 * Attempts to write count bytes from buffer into the file.
	 * @returns number of bytes actually written
	 */
	unsigned int write(const char* buffer, unsigned int count) throw (InvalidOperation, MPQError);
	
	/**
	 * Attempts to read count bytes from file into the buffer.
	 * @returns number of bytes actually reads
	 */
	unsigned int read(char* buffer, unsigned int count) throw (InvalidOperation, MPQError);
	
	///Opens the file for reading.
	///@returns reference to self for chain calling
	File& openRead() throw(InvalidOperation, MPQError, FileNotFound);
	
	///Opens the file for writing.
	///@arg fileSize the size of the file. This is exactly how many bytes must be subsequently written to the file.
	///@returns reference to self for chain calling
	File& openWrite(unsigned int fileSize) throw(InvalidOperation, MPQError);
	
	///@returns true if the file is open
	bool isOpen() const;
	
	/**
	 * Assignment operator.
	 * Copies the data from file into this file.
	 * @arg file file to copy from
	 */
	File& operator=(const File& file);
private:
	///Operating mode
	FileMode mode;
	
	///IO mode
	IOMode ioMode;
	
	///File's StormLib handle, if in MPQ mode
	HANDLE fileHandle;
	
	///File on disk, if in Disk mode
	std::fstream diskFile;
	
	///The archive this file belongs to, if in MPQ mode
	ArchiveHandle archive;
	
	///The file's filename (full path)
	std::string filename;
	
	///True if the file is open
	bool open;
};
typedef boost::intrusive_ptr<File> FileHandle;
}

#endif
