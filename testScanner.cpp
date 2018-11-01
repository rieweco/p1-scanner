#include <iostream>
#include "testScanner.h"
#include "scanner.h"

using namespace std;

TestScanner::TestScanner() = default;
TestScanner::~TestScanner() = default;

const bool TestScanner::isCommentMode() const {
    return commentFlag;
}

void TestScanner::setCommentMode(const bool commentFlag) {
    TestScanner::commentFlag = commentFlag;
}

const std::string TestScanner::scan(const std::string &rawData) {
    Scanner *scanner = new Scanner();
    int index = 0;
    int lineNumber = 1 + linesBeforeToken(rawData, index);
    Token *token;
    string tokenLiteral;

    //scan next token and process until EOF is found. If it is an invalid token, error!
    do {
	try {
	    token = scanner->getNextToken(rawData, index, lineNumber);
	    tokenLiteral += token->toString();
	    tokenLiteral += "\n";
	    index += token->getValue().length();
	    lineNumber += linesBeforeToken(rawData, index);
	} catch(const string &e) {
	    cerr << e << endl;
	    throw 3;
	}
    } while((TOKEN_IDENTIFIER_TO_TOKEN_NAME_MAP.at(token->getTokenIdentifier()) != END_OF_FILE_TOKEN_NAME));
   
    return tokenLiteral;
}

const int TestScanner::linesBeforeToken(const string &rawData, int &index) {
    int newLines = 0;
    while(index < rawData.length() && tokenReadFlag(rawData[index])) {
	//check comment mode
	if(rawData[index] == '$') {
	    setCommentMode(!isCommentMode());
	}
	
	if(rawData[index] == '\n') {
	   newLines++;
	}
	
	index++;
    }
	
    return newLines;
}


const bool TestScanner::tokenReadFlag(const char next) const {
    if(isCommentMode()) {
	return true;
    }
    else {
	return next == '$' || next == ' ' || next == '\n';
    }
}	
