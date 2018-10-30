#ifndef TESTSCANNER_H
#define TESTSCANNER_H

#include <string>

class TestScanner {
    private: 
	bool commentFlag = false;
	const bool tokenReadFlag(const char nextChar) const;
	const int linesBeforeToken(const std::string &rawData, int &currentIndex);
	
    public:
	TestScanner();
	~TestScanner();
	const bool isCommentMode() const;
	void setCommentMode(const bool commentFlag);
	const std::string scan(const std::string &rawData);
};

#endif
