//  ***************************************************************
//  TextScanner - Creation date: 06/09/2009
//  -------------------------------------------------------------
//  Robinson Technologies Copyright (C) 2009 - All Rights Reserved
//
//  ***************************************************************
//  Programmer(s):  Seth A. Robinson (seth@rtsoft.com)
//  ***************************************************************


/* Simple way to read parms from a text file

Here is an example of use:

Assume a simple text file, settings.txt holds the following:

name|Jeff
lives|3

You could parse it like this:

TextScanner t("settings.txt");

//Or, if you've downloaded the file, you can just pass in the memory location:
//TextScanner t(pPointerToMem);

if (!t.IsLoaded())
{
LogError("Oh damn");
}

//Note: returns a blank string if the parm is missing
string name = t.GetParmString("name", 1, "|");

//Note: the number says which section to return, you can have multiple delimiters in the same line
int lives = atoi( t.GetParmString("lives",1,"|") );


*/

#ifndef TextScanner_h__
#define TextScanner_h__

#include <iostream>
#include <vector>

class TextScanner
{
public:

	TextScanner();
	TextScanner(const char *pCharArray);
	TextScanner(const std::string &fName);
	TextScanner(const std::string &fName, bool bAddBasePath );
	~TextScanner();

	void Kill();

	bool LoadFile(const std::string &fName, bool bAddBasePath = true);
	bool SaveFile(const std::string &fName, bool bAddBasePath = true);
	std::string GetParmString(std::string label, int index, std::string token = "|");
	std::string GetParmStringFromLine(int lineNum, int index, std::string token = "|");
	int GetParmIntFromLine( int lineNum, int index, std::string token = "|" );
	float GetParmFloatFromLine( int lineNum, int index, std::string token = "|");
	std::string GetMultipleLineStrings(std::string label, std::string token = "|");
	std::string GetLine(int lineNum); //0 based, returns "" if out of range
	void Replace( const std::string &thisStr, const std::string &thatStr );
	bool IsLoaded() {return !m_lines.empty();}
	bool SetupFromMemoryAddress(const char *pCharArray);
	bool SetupFromMemoryAddressRaw( const char *pCharArray, int size );
	void DeleteLine(int lineNum);
	void StripLeadingSpaces();
	std::string GetAll(); //it does trim whitespace
	std::string GetAllRaw(); //no trimming whitespace with this one
	int GetLineCount() {return (int)m_lines.size();}
	void DumpToLog(); //sends the entire contents to the log via LogMsg(), helpful when debugging
	std::vector<std::string> TokenizeLine(int lineNum, const std::string &theDelimiter = "|");
	void AppendToFile(std::string fileName, bool bAddBasePath = true);
	bool AppendFromMemoryAddress(const char *pCharArray);
	bool AppendFromMemoryAddressRaw( const char *pCharArray, int size );
	bool AppendFromString(const std::string lines);

	void AddParmString(std::string key, std::string value, std::string token = "|");

	std::vector<std::string> m_lines;

private:

	int m_lastLine; //used during searches to remember the state
};


#endif // TextScanner_h__