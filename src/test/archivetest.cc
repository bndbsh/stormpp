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

TEST_F(ArchiveTest, Constructor) {
	ASSERT_THROW(Archive("nonexistantpath"), FileNotFound);
	ASSERT_THROW(Archive("invalid.mpq"), InvalidArchive);
	ASSERT_NO_THROW(Archive("empty.mpq"));
	ASSERT_NO_THROW(Archive("simple.mpq"));
}

TEST_F(ArchiveTest, Reading) {
	Archive read("simple.mpq");
	EXPECT_EQ(true, read.hasFile("file1"));
	EXPECT_EQ(true, read.hasFile("dir\\file2"));
	EXPECT_EQ(true, read.hasFile("dir\\file3"));
	EXPECT_EQ(true, read.hasFile("dir/file3"));
}

}
