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
	virtual ~FileNotFound() throw() { };

	inline virtual const char* what() const throw() {return data.c_str();};
};

}

#endif
