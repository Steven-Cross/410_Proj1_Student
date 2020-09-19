/***
 * KP Utils
 */
#include <numeric>
#include <math.h>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "utilities.h"
#include "stdlib.h"

using namespace std;

//********************** private to this compilation unit **********************

vector<process_stats> holder;

//if myString does not contain a string rep of number returns o
//if int not large enough has undefined behaviour, very fragile
int stringToInt(const char *myString) {
	return atoi(myString);
}

// This method reads in a line to check if the data is corrupt by checking
// if the line begins or ends with a comma
// if the line contains a space OR two commas in a row, indicating a missing element
bool isCorrupt(string line) {

	if (line.front() == ',' || line.back() == ',') {
		return true;
	}
	if (line.find(" ") != string::npos) {
		return true;
	}

	for (int i = 0; i < line.length()-1; i++) {
		if (line.at(i) == ',' && line.at(i + 1) == ',') {
			return true;
		}
	}

	return false;
}

int loadData(const char* filename, bool ignoreFirstRow) {

	ifstream myFile;
	myFile.open(filename);
	string line = "";
	holder.clear();

	if (!myFile.is_open()){
		return COULD_NOT_OPEN_FILE;
	}

	if (ignoreFirstRow){
		getline(myFile, line);
		line = "ignored";
	}

	while (!myFile.eof()){
		getline(myFile, line);
		if (isCorrupt(line)){
			continue;
		}
		stringstream ss(line);
		process_stats data;

		getline(ss, line, CHAR_TO_SEARCH_FOR);

		data.process_number = stringToInt(line.c_str());


		getline(ss, line, CHAR_TO_SEARCH_FOR);
		data.start_time = stringToInt(line.c_str());

		getline(ss, line, CHAR_TO_SEARCH_FOR);
		data.cpu_time = stringToInt(line.c_str());

		getline(ss, line, CHAR_TO_SEARCH_FOR);
		data.io_time = stringToInt(line.c_str());

		holder.push_back(data);
	}
	myFile.close();
	return SUCCESS;
}


//will sort according to user preference
void sortData(SORT_ORDER mySortOrder) {

}

process_stats getNext() {
	process_stats myFirst;
	myFirst.process_number = holder.front().process_number;
	myFirst.start_time 	   = holder.front().start_time;
	myFirst.cpu_time 	   = holder.front().cpu_time;
	myFirst.io_time 	   = holder.front().io_time;
	holder.erase(holder.begin());

	return myFirst;
}

//returns number of process_stats structs in the vector holding them
int getNumbRows(){
	return holder.size();
}




