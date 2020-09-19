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

// This method reads formatted data from a file and populates a vector of process_stats
// It ignores file headers and corrupt lines of data
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
	vector<process_stats> temp;
	process_stats tempProcess;

	if (mySortOrder == CPU_TIME) {
		for (int i = 0; i < holder.size() - 1; i++){
			for (int j = 1; j < holder.size(); j++){
				if (holder.at(i).cpu_time < holder.at(j).cpu_time){
					tempProcess.cpu_time       = holder.at(i).cpu_time;
					tempProcess.io_time		   = holder.at(i).io_time;
					tempProcess.process_number = holder.at(i).process_number;
					tempProcess.start_time	   = holder.at(i).start_time;
				} else {
					tempProcess.cpu_time       = holder.at(j).cpu_time;
					tempProcess.io_time		   = holder.at(j).io_time;
					tempProcess.process_number = holder.at(j).process_number;
					tempProcess.start_time	   = holder.at(j).start_time;
				}
			}
			temp.push_back(tempProcess);
			holder.erase(holder.begin() + i);
		}
	}
	else if (mySortOrder == PROCESS_NUMBER) {
		for (int i = 0; i < holder.size() - 1; i++){
			for (int j = 1; j < holder.size(); j++){
				if (holder.at(i).process_number < holder.at(j).process_number){
					tempProcess.cpu_time       = holder.at(i).cpu_time;
					tempProcess.io_time		   = holder.at(i).io_time;
					tempProcess.process_number = holder.at(i).process_number;
					tempProcess.start_time	   = holder.at(i).start_time;
				} else {
					tempProcess.cpu_time       = holder.at(j).cpu_time;
					tempProcess.io_time		   = holder.at(j).io_time;
					tempProcess.process_number = holder.at(j).process_number;
					tempProcess.start_time	   = holder.at(j).start_time;
				}
			}
			temp.push_back(tempProcess);
		}
	}
	else if (mySortOrder == START_TIME) {
		for (int i = 0; i < holder.size() - 1; i++){
			for (int j = 1; j < holder.size(); j++){
				if (holder.at(i).start_time < holder.at(j).start_time){
					tempProcess.cpu_time       = holder.at(i).cpu_time;
					tempProcess.io_time		   = holder.at(i).io_time;
					tempProcess.process_number = holder.at(i).process_number;
					tempProcess.start_time	   = holder.at(i).start_time;
				} else {
					tempProcess.cpu_time       = holder.at(j).cpu_time;
					tempProcess.io_time		   = holder.at(j).io_time;
					tempProcess.process_number = holder.at(j).process_number;
					tempProcess.start_time	   = holder.at(j).start_time;
				}
			}
			temp.push_back(tempProcess);
		}
	}
	else if (mySortOrder == IO_TIME) {
		for (int i = 0; i < holder.size() - 1; i++){
			for (int j = 1; j < holder.size(); j++){
				if (holder.at(i).io_time < holder.at(j).io_time){
					tempProcess.cpu_time       = holder.at(i).cpu_time;
					tempProcess.io_time		   = holder.at(i).io_time;
					tempProcess.process_number = holder.at(i).process_number;
					tempProcess.start_time	   = holder.at(i).start_time;
				} else {
					tempProcess.cpu_time       = holder.at(j).cpu_time;
					tempProcess.io_time		   = holder.at(j).io_time;
					tempProcess.process_number = holder.at(j).process_number;
					tempProcess.start_time	   = holder.at(j).start_time;
				}
			}
			temp.push_back(tempProcess);
		}
	}
	temp.push_back(holder.front());
	temp.swap(holder);
	return;
}

// Returns the next process_stats from the holder vector, and removes it from the vector
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




