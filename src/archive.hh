#ifndef _STORM_ARCHIVE_HH_
#define _STORM_ARCHIVE_HH_

#include "exceptions.hh"
#include "file.hh"

#include <StormLib.h>

#include <fstream>
#include <map>

#include "object.hh"

namespace storm {
/** 
 * @brief thrown when trying to open an invalid archive
 * @author amro
 */
class InvalidArchive : public std::exception {
	std::string data;
public:
	InvalidArchive(const std::string& filename) : data("Invalid archive. " + filename) { };
	virtual ~InvalidArchive() throw() { };

	inline virtual const char* what() const throw() {return data.c_str();};
};

/**
 * @brief Represents an MPQ archive
 * @author amro
 */
class Archive : public Object {
public:
	/**
	 * Constructs an archive from the given path. If hashtableSize is not 0,
	 * it will create the archive. Else, it will attempt to open it.
	 * @arg fileName full path to the archive
	 * @arg hashtableSize the size of the hashtable (i.e. max file capacity)
	 * @throws FileNotFound if hashtableSize is 0 and the file does not exist
	 * @throws InvalidArchive if hashtableSize is 0 and the file is not recognized
	 * @throws InvalidOperation if hashtableSize is nonzero and the file exists
	 */
	Archive(const std::string& filename, unsigned int hashtableSize = 0) throw(FileNotFound, InvalidOperation, InvalidArchive);
	
	///Cleanup
	~Archive();
	
	/**
	 * Checks for the existence of a file in the hashtable
	 * @arg filename to check for
	 * @returns true if the file exists in the hashtable
	 */
	bool hasFile(const std::string& filename) const;
	
	///Accessor for files. Attempts to read file filename from Archive
	File operator[](const std::string& filename);
	
	///@returns true if the archive is open
	bool isOpen() const;
	
	///@returns the handle if the archive is open, 0 otherwise
	HANDLE getHandle() const;
private:
	///The file on disk
	std::fstream file;
	
	///MPQ handle
	HANDLE mpqHandle;
	
	///True if the archive is currently open via StormLib
	bool open;
	
	typedef std::map<std::string, File> FileMap;
	
	///Cache for files
	FileMap files;
	
	///Flushes any unwritten data
	void flush();
};
typedef boost::intrusive_ptr<Archive> ArchiveHandle;
}

#endif
