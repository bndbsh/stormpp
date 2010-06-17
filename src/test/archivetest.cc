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
	ArchiveHandle readh = ArchiveHandle(new Archive("simple.mpq"));
	Archive& read = *readh;
	EXPECT_EQ(true, read.hasFile("file1"));
	EXPECT_EQ(true, read.hasFile("dir\\file2"));
	EXPECT_EQ(true, read.hasFile("dir\\file3"));
	EXPECT_EQ(true, read.hasFile("dir/file3"));
	EXPECT_THROW(read["nonexistant"], FileNotFound);
// 	read["file1"];
	ASSERT_NO_THROW(read["file1"]);
	char buffer[5];
	File& f = read["file1"];
	f.openRead().read(buffer, 5);
	ASSERT_NO_THROW(read["file1"].openRead().read(buffer, 5));
}

}
