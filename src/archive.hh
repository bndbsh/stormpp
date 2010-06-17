#ifndef _STORM_ARCHIVE_HH_
#define _STORM_ARCHIVE_HH_

#include "exceptions.hh"

#include <StormLib.h>

#include <fstream>

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
class Archive {
public:
	/**
	 * Constructs an archive from the given path. If create is true, it will
	 * create it if it does not already exist. If create is false, it will
	 * throw FileNotFound.
	 * @arg fileName full path to the archive
	 * @arg create if true, create archive if it doesn't exist
	 * @throws FileNotFound
	 */
	Archive(const std::string& filename, bool create = false) throw(FileNotFound, InvalidArchive);
	
	///Cleanup
	~Archive();
	
	/**
	 * Checks for the existence of a file in the hashtable
	 * @arg filename to check for
	 * @returns true if the file exists in the hashtable
	 */
	bool hasFile(const std::string& filename) const;
private:
	///The file on disk
	std::fstream file;
	
	///MPQ handle
	HANDLE mpqHandle;
	
	///True if the archive is currently open via StormLib
	bool open;
	
	///Flushes any unwritten data
	void flush();
};

}

#endif
