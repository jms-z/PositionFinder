// James Stanko
// CS 33101
// Structure of Programming Languages
// 5/3/2017

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include "ReadDATFile.h"

int main(){

	DATData tmp;
	unsigned char hold;
	int shold = 0;
	std::string READ_RESULT;
	std::ifstream inputfile("GrTMt.dat", std::ios::binary); //open file as binary
	std::stringstream StrStream;

	inputfile >> std::noskipws; //Dont skip whitespaces when reading!
	
	while ((!inputfile.eof())) {//put hex values into stringstream	
		inputfile >> hold;
		StrStream << std::hex << std::setfill('0') << std::setw(2) << (int)hold;
	}
	std::cout << "File read completed.\n";

	READ_RESULT = StrStream.str();

	tmp.SEARCHFILE(READ_RESULT);

	tmp.PRINTRESULTS();

	std::cin.get();
	inputfile.close();

}

//=====================================Definitions=====================================

DATData::DATData(){
}

DATData::~DATData(){
}

void DATData::SEARCHFILE(const std::string &read){

	int i = 0;
	int j = 0;
	int tmp_offset; //this will keep track of the offset; when position data found, 
				//set the incremented offset to the current value held in this;
	int tmp_loc = 0;
	std::string tmp_hex;
	std::string PositionStart("3f8000003f8000003f800000"); //used to find position data;
	std::size_t loc = 0;

	while (i < read.capacity()){
		
		if (i != loc){ //first search
			loc = read.find(PositionStart);
		}
		if (i == loc){ //subsequent searches
			loc = read.find(PositionStart, loc + 1);
		}

		if (loc != std::string::npos){//when position data found
			tmp_offset = loc;
			tmp_loc = loc;
			tmp_offset = ((tmp_offset)/2); //***convert to hex
			this->offset.push_back("0x" + std::to_string(tmp_offset));

			for (int k = 0; k < 48; ++k){
				tmp_hex.push_back(read[tmp_loc]);
				tmp_loc++;
			}

			this->hex.push_back(tmp_hex);
			tmp_hex = "";
		}
		else{
			std::cout << "Position data search completed.\n";
			std::cout << std::endl;
		}

		i = loc;
	}

	return;
}

void DATData::PRINTRESULTS(){
	for (int i = 0; i < this->hex.size(); ++i){
		std::cout << "Offset: " << offset[i] << std::endl;
		std::cout << "X Pos: " << hex[i].substr(24, 8) << std::endl;
		std::cout << "Y Pos: " << hex[i].substr(32, 8) << std::endl;
		std::cout << "Z Pos: " << hex[i].substr(40, 8) << std::endl;
		std::cout << std::endl;
	}
}