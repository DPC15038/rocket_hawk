#include "html_inserter.hpp"

vector<char> getFileContents(ifstream& inputFile) {
  vector<char> returnVector;
  char tmp;
  while (inputFile >> noskipws >> tmp) {
      returnVector.push_back(tmp);
  }
  return returnVector;
}

int main() {
  ifstream alt_temperature("altimeter_data/altimeter_temperature.txt");
  ifstream alt_pressure("altimeter_data/altimeter_pressure.txt");
  ifstream alt_altitude("altimeter_data/altimeter_altitude.txt");
  vector<char> temperatureTextToInsert = getFileContents(alt_temperature);
  vector<char> pressureTextToInsert = getFileContents(alt_pressure);
  vector<char> altitudeTextToInsert = getFileContents(alt_altitude);
  HTML_File htmlTemperature("temp_chart.html");
  if (htmlTemperature.insertTextAtLocation(htmlTemperature.getStartingLocationForData('T'), temperatureTextToInsert) == 1) {
    if (htmlTemperature.commitChanges("temp_chart.html") != 1){
      return -1;
    };

  }
  HTML_File htmlPressure("temp_chart.html");
  if (htmlPressure.insertTextAtLocation(htmlPressure.getStartingLocationForData('P'), pressureTextToInsert) == 1) {
    if (htmlPressure.commitChanges("temp_chart.html") != 1){
      return -1;
    };

  }
  HTML_File htmlAltitude("temp_chart.html");
  if (htmlAltitude.insertTextAtLocation(htmlAltitude.getStartingLocationForData('A'), altitudeTextToInsert) == 1) {
    if (htmlAltitude.commitChanges("temp_chart.html") != 1){
      return -1;
    };
  }
  return 0;
}

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
HTML_File::HTML_File(const string& input) {
  inputFile.open(input);
  char tmp;
  while (inputFile >> noskipws >> tmp) {
    fileData.push_back(tmp);
  }
  inputFile.close();
}

void HTML_File::printFile() {
  for (auto i = fileData.begin(); i != fileData.end(); ++i) {
    cout << *i;
  }
}

int HTML_File::insertTextAtLocation(int startingPoint, vector<char> insertedText) {
  if (startingPoint < 0) return 0;
  vector<char> newFileData;
  int i;
  for (i = 0; i < startingPoint;i++) {
    newFileData.push_back(fileData[i]);
  }
  for (int j = 0; j < insertedText.size(); j++) {
    newFileData.push_back(insertedText[j]);
  }
  for (i+=3; i < fileData.size(); i++) {
    newFileData.push_back(fileData[i]);
  }
  fileData = newFileData;
  return 1;
}

int HTML_File::getStartingLocationForData(char TYPE) {
  int endVal = fileData.size()-2; // So we dont have to calculate it every time
    for (int i = 0; i < endVal; i ++) {
      if (fileData[i] == '*' && fileData[i+1] == TYPE && fileData[i+2] == '*') {
        return i;
      }
    }
  return -1;
}
int HTML_File::commitChanges(const string& output) {
  outputFile.open(output);
  for (auto i = fileData.begin(); i != fileData.end();++i) {
    outputFile << *i;
  }
  outputFile.close();
  return 1;
}
