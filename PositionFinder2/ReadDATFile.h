//James Stanko
//CS 33101
//Structure of Programming Languages

//class definition for dat file information holder
//***Position data has 13 groups of 4 pairs of bytes (99009900)

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

class DATData{

public:
	DATData();
	~DATData();
	void SEARCHFILE(const std::string &read); //file, after opened, finds and dumps hex data into relevant indexes	
	void PRINTRESULTS();				      //Prints results

protected:
	std::vector<std::string> offset;          //offset (i.e. 0x9834)
	std::vector<std::string> hex;             //hex data for offset (i.e. 021F)

};