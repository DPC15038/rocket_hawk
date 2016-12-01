#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
enum Location {TEMPERATURE, PRESSURE, ALTITUDE};

vector<string> getFileContents(ifstream& inputFile) {
  vector<string> returnVector;
  string line;
  if (inputFile.is_open()) {
    while (getline(inputFile, line)) {
      returnVector.push_back(line);
    }
  }
  return returnVector;
}


int main(){
  ifstream htmlInput("test.html");
  ifstream alt_temperature("../altimeter_temperature.txt");
  vector<string> temperature_readings;
  vector<string> htmlContents;
  vector<string> parsedHTML;
  temperature_readings = getFileContents(alt_temperature);
  htmlContents = getFileContents(htmlInput);
  
  return 0;
}
