#include <gtest/gtest.h>
#include "archive.hh"

using namespace storm;

namespace tests {

class ArchiveTest : public ::testing::Test {
protected:
	ArchiveTest() {}

	virtual ~ArchiveTest() {
		
	}
};

TEST_F(ArchiveTest, SanityChecks) {
	ASSERT_THROW(Archive("nonexistantpath"), FileNotFound);
	ASSERT_THROW(Archive("invalid.mpq"), InvalidArchive);
	Archive("empty.mpq");
	ASSERT_NO_THROW(Archive("empty.mpq"));
}

}
