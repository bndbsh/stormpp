#include <gtest/gtest.h>
#include "file.hh"

using namespace storm;

namespace tests {

class FileTest : public ::testing::Test {
protected:
	FileTest() {}

	virtual ~FileTest() {
		
	}
	File invalid;
};

TEST_F(FileTest, SanityChecks) {
	ASSERT_THROW(invalid.read(0, 0), InvalidFile);
	ASSERT_THROW(invalid.write(0, 0), InvalidFile);
}

}
