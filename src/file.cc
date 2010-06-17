#include "file.hh"

namespace storm {

File::File() : mode(Invalid) {
	
}

File::File(const std::string& fileName) : mode(Disk) {
	
}

unsigned int File::write(char* data, unsigned int count) throw(InvalidFile) {
	if (mode == Invalid) throw InvalidFile("write");
	return 0;
}

unsigned int File::read(char* data, unsigned int count) throw(InvalidFile) {
	if (mode == Invalid) throw InvalidFile("read");
	return 0;
}

}
