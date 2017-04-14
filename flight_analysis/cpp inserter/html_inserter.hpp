#ifndef HTML_INSERTER_HPP
#define HTML_INSERTER_HPP
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
class HTML_File{
public:
  HTML_File(const string& input);
  void printFile();
  int insertTextAtLocation(int startingPoint, vector<char> insertedText);
  int getStartingLocationForData(char TYPE);
  int commitChanges(const string& output);

private:
  ifstream inputFile;
  ofstream outputFile;
  vector<char> fileData;
};

#endif
