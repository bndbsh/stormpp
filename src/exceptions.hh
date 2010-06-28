#ifndef _STORM_EXCEPTIONS_HH_
#define _STORM_EXCEPTIONS_HH_

#include <exception>
#include <string>

namespace storm {

/** 
 * @brief as the name implies, thrown when a file is not found
 * @author amro
 */
class FileNotFound : public std::exception {
	std::string data;
public:
	FileNotFound(const std::string& filename) : data("File not found: " + filename) { };
	virtual ~FileNotFound() throw() {};

	inline virtual const char* what() const throw() {return data.c_str();};
};

/** 
 * @brief thrown when an invalid operation is attempted
 * @author amro
 */
class InvalidOperation : public std::exception {
	std::string data;
public:
	InvalidOperation(const std::string& info) : data("Invalid operation. " + info) { };
	virtual ~InvalidOperation() throw() {};

	inline virtual const char* what() const throw() {return data.c_str();};
};

/**
 * @brief thrown when there are errors with MPQ operations
 * @author amro
 */
class MPQError : public std::exception {
	std::string data;
public:
	MPQError(const std::string& info) : data("MPQ error. " + info) { };
	virtual ~MPQError() throw() {};

	inline virtual const char* what() const throw() {return data.c_str();};
};

/** 
 * @brief bad things that should never happen, usually indicates a bug in storm++
 * @author amro
 */
class InternalError : public std::exception {
	std::string data;
public:
	InternalError(const std::string& details = "") : data("Zomg internal error! " + details) { };
	virtual ~InternalError() throw() {};

	inline virtual const char* what() const throw() {return data.c_str();};
};

}

#endif
