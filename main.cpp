//main.cpp

#include <iostream>
#include <fstream>
#include "testScanner.h"

using namespace std;

//vars
static string NO_FILE_EXTENSION = "out";
static string FILE_IN_EXTENSION = ".fs182";


//functions
string getKBData();
string getFileData(string &fileName);
void runTestScanner(string &program, string &fileName);
string trim(string &toBeTrimmed);

int main(int argc, char *argv[]) {
	int numArgs = argc - 1;
	
	if (numArgs == 0) {	
    		string kbData = getKBData();
    		runTestScanner(kbData, NO_FILE_EXTENSION);
	}
	else if (numArgs == 1) {
		string fileName = argv[1];
		string extendedFileName = fileName + FILE_IN_EXTENSION;
		string fileData = getFileData(extendedFileName);
		runTestScanner(fileData,fileName);	
	}
	else {
		cout << "incorrect # of args! 0 args for kb input, 1 arg for file input." << endl;
		exit(1);
	}

	return 0;
}

string getKBData() {
    string data;
    string line;

    getline(cin, line);
    while (!cin.eof()) {
        if (data.empty()) {
            data = line;
        } else {
            data += "\n" + line;
        }
        getline(cin, line);
    }

    return data;
}

string getFileData(string &extendedFileName) {
    	ifstream inputFile(extendedFileName);

    	if (inputFile) {
        	string fileData;
        	string fileLine;

        	while (!inputFile.eof()) {
            		getline(inputFile, fileLine);
            		if (fileData.empty()) {
                		fileData = fileLine;
            		} else {
                		fileData += "\n" + fileLine;
            		}
        	}	

        	inputFile.close();

        	return fileData;
    	} else {
        	cout << "file: " << inputFile << " not found!" << endl;
        	exit(1);
   	}
}

void runTestScanner(string &program, string &fileName) {
    TestScanner *testScanner = new TestScanner();
    string token = testScanner->scan(program);
    cout << token << endl;
}
