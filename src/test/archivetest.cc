#include <gtest/gtest.h>
#include <stdio.h>
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
	ASSERT_THROW(Archive("invalid.mpq", 24), InvalidOperation);
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
	ASSERT_NO_THROW(read["file1"]);
	ASSERT_NO_THROW(read["dir/file3"]);
	char buffer[3];
	memset(buffer, 0, 3);
	File f = read["file1"];
	ASSERT_NO_THROW(f.openRead().read(buffer, 2));
	EXPECT_EQ(std::string("FI"), buffer);
	ASSERT_NO_THROW(f.read(buffer, 2));
	EXPECT_EQ(std::string("LE"), buffer);
	
	File f3 = read["dir\\file3"];
	ASSERT_NO_THROW(f3.openRead().read(buffer, 2));
	EXPECT_EQ(std::string("FI"), buffer);
	ASSERT_NO_THROW(f3.read(buffer, 2));
	EXPECT_EQ(std::string("LE"), buffer);
}

TEST_F(ArchiveTest, Writing) {
	remove("local/write1.mpq");
	ArchiveHandle readh;
	ASSERT_NO_THROW(readh = ArchiveHandle(new Archive("local/write1.mpq", 32)));
	Archive& read = *readh;
	File f;
	ASSERT_NO_THROW(f = read["test"]);
	ASSERT_NO_THROW(f.openWrite(4));
	ASSERT_NO_THROW(f.write("TEST", 4));
	ASSERT_NO_THROW(f.close());
// 	remove("local/write1.mpq");
}

}
