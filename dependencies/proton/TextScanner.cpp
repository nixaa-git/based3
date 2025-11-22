#include "TextScanner.h"
//#include "ResourceUtils.h"
#include "MiscUtils.h"
#include <fstream>
//#include "FileSystem/FileManager.h"
#include <cassert>

// file funcs needed rn cba to make a custom implementation
char* OpenFileAndGetChars(const std::string& name)
{
    std::ifstream f(name, std::ios::binary);
    if (!f.good())
    {
        ::printf("OpenFileAndGetChars() Fatal error, failed to open file %s\n", name.c_str());
        return nullptr;
    }

    f.seekg(0, std::ios::end);
    std::streamsize size = f.tellg();
    f.seekg(0, std::ios::beg);

    if (size <= 0)
        return nullptr;

    char* pFileData = new char[size + 1];  // +1 for null terminator
    f.read(pFileData, size);

    pFileData[size] = '\0'; // null-terminate for safety

    return pFileData;
}


//////

TextScanner::TextScanner()
{
	m_lastLine = 0;
}

TextScanner::TextScanner(const std::string &fName )
{
	m_lastLine = 0;
	LoadFile(fName);
}

TextScanner::TextScanner(const std::string &fName, bool bAddBasePath )
{
	m_lastLine = 0;
	LoadFile(fName, bAddBasePath);
}

TextScanner::TextScanner( const char *pCharArray )
{
	m_lastLine = 0;
	SetupFromMemoryAddress(pCharArray);
}


bool TextScanner::LoadFile( const std::string &fName, bool bAddBasePath )
{
	Kill();

	return SetupFromMemoryAddress(OpenFileAndGetChars(fName));
}

bool TextScanner::SetupFromMemoryAddress(const char *pCharArray)
{
    if (!pCharArray)
    {
        ::printf("TextScanner::SetupFromMemoryAddress() : Fatal error, pCharArray passed was nullptr\n");
        return false;
    }

	m_lines = StringTokenize(pCharArray, "\n");

	for (unsigned int i=0; i < m_lines.size(); i++)
	{
		StringReplace("\r", "", m_lines[i]);

	}
	return true;
}

bool TextScanner::SetupFromMemoryAddressRaw( const char *pCharArray, int size )
{
	m_lines = StringTokenize(pCharArray, "\n");
	return true;
}

std::string TextScanner::GetParmString( std::string label, int index,  std::string token)
{
	if (m_lines.empty())
	{
		::printf("Load a file first\n");
		return "";
	}

	for (unsigned int i=0; i < m_lines.size(); i++)
	{
		if (m_lines[i].empty()) continue;
		std::vector<std::string> line = StringTokenize(m_lines[i], token);
		if (line[0] == label)
		{
			//found it
			return line[index];
		}
	}

	return "";
}

TextScanner::~TextScanner()
{
	Kill();
}

void TextScanner::Kill()
{
	m_lines.clear();
	m_lastLine = 0;
}

std::string TextScanner::GetMultipleLineStrings( std::string label, std::string token )
{
	for (unsigned int i=m_lastLine; i < m_lines.size(); i++)
	{
		if (m_lines[i].empty()) continue;
		std::vector<std::string> line = StringTokenize(m_lines[i], token);
		if (line[0] == label)
		{
			//found it
			m_lastLine = i+1;
			return m_lines[i];
		}
	}
	m_lastLine = 0; //reset it
	return "";
}

void TextScanner::StripLeadingSpaces()
{
	for (unsigned int i=0; i < m_lines.size(); i++)
	{
		m_lines[i] = StripWhiteSpace(m_lines[i]);

	}

}

std::string TextScanner::GetLine( int lineNum )
{
	if ((int)m_lines.size() > lineNum && lineNum >= 0)
	{
		return m_lines[lineNum];
	}

	//invalid line
	return "";
}

std::string TextScanner::GetAll()
{
	std::string s;

	for (unsigned int i=0; i < m_lines.size(); i++)
	{
		s += StripWhiteSpace(m_lines[i])+"\n";
	}

	return s;
}

std::string TextScanner::GetAllRaw()
{
	std::string s;

	for (unsigned int i=0; i < m_lines.size(); i++)
	{
		s +=m_lines[i]+"\n";
	}

	return s;
}

std::string TextScanner::GetParmStringFromLine( int lineNum, int index, std::string token /*= "|"*/ )
{
	assert(lineNum >= 0 && (uint32_t)lineNum < m_lines.size());
	assert(token.size() == 1 && "We don't actually support a non char delim yet");
	return SeparateStringSTL(m_lines[lineNum], index, token[0]);
}

int TextScanner::GetParmIntFromLine( int lineNum, int index, std::string token /*= "|"*/ )
{
	assert(lineNum >= 0 && (uint32_t)lineNum < m_lines.size());
	assert(token.size() == 1 && "We don't actually support a non char delim yet");
	return std::atoi(SeparateStringSTL(m_lines[lineNum], index, token[0]).c_str());
}

float TextScanner::GetParmFloatFromLine( int lineNum, int index, std::string token /*= "|"*/ )
{
	assert(lineNum >= 0 && (uint32_t)lineNum < m_lines.size());
	assert(token.size() == 1 && "We don't actually support a non char delim yet");
	return (float)atof(SeparateStringSTL(m_lines[lineNum], index, token[0]).c_str());
}


void TextScanner::Replace( const std::string &thisStr, const std::string &thatStr )
{
	for (unsigned int i=0; i < m_lines.size(); i++)
	{
		StringReplace(thisStr, thatStr, m_lines[i]);
	}

}

void TextScanner::DumpToLog()
{
	for (int i=0; i < GetLineCount(); i++)
	{
		std::string tmp = m_lines[i].c_str();
	    StringReplace("%", "%%", tmp);
		::printf("%s\n", tmp.c_str());
	}
}

bool TextScanner::SaveFile( const std::string &fName, bool bAddBasePath /*= true*/ )
{
	std::string f;

	std::string lineFeed = "\r\n";
	if (bAddBasePath)
	{
		//f = GetSavePath()+fName;
	} else
	{
		f = fName;
	}
	FILE *fp = fopen( f.c_str(), "wb");

	if (!fp)
	{
		::printf("Unable to save data\n");
		return false;
	}

	for (uint32_t i=0; i < m_lines.size(); i++)
	{
		fwrite(m_lines[i].c_str(), m_lines[i].size(), 1, fp);
		fwrite(lineFeed.c_str(), lineFeed.size(), 1, fp);
	}
	
	fclose(fp);
	return true;
}

void TextScanner::DeleteLine( int lineNum )
{
	if (m_lastLine && m_lastLine >= lineNum) m_lastLine--;
	m_lines.erase(m_lines.begin()+lineNum);
}

std::vector<std::string> TextScanner::TokenizeLine( int lineNum, const std::string &theDelimiter /*= "|"*/ )
{
	return StringTokenize(m_lines[lineNum], theDelimiter);
}

void TextScanner::AppendToFile( std::string fileName, bool bAddBasePath /*= true*/ )
{
	if (m_lines.empty()) return;

	if (bAddBasePath)
	{
		//fileName = GetBaseAppPath()+fileName;
	}

	FILE *fp = NULL;

	if (NULL != 1 /*GetPlatformID() == PLATFORM_ID_LINUX*/)
	{
		fp = fopen(fileName.c_str(), "a+");

	} else
	{
		fp = fopen(fileName.c_str(), "ab");

		if (!fp)
		{
			fp = fopen(fileName.c_str(), "wb");
		}
	}

	if (!fp)
	{
		//Uhh.... bad idea, could create infinite loop
		//LogError("Unable to create/append to %s", text);
		return;
	}

	std::string temp;
	for (uint32_t i=0; i < m_lines.size(); i++)
	{
		temp = m_lines[i]+"\r\n";
		fwrite(temp.c_str(), temp.size(), 1, fp);
	}

	fclose(fp);
//	
}

bool TextScanner::AppendFromMemoryAddress(const char *pCharArray)
{
	std::vector<std::string> tempVec= StringTokenize(pCharArray, "\n");

	for (unsigned int i=0; i < tempVec.size(); i++)
	{
		StringReplace("\r", "", tempVec[i]);
		m_lines.push_back(tempVec[i]);

	}
	return true;
}

bool TextScanner::AppendFromString( const std::string lines )
{
	std::vector<std::string> tempVec= StringTokenize(lines, "\n");

	for (unsigned int i=0; i < tempVec.size(); i++)
	{
		StringReplace("\r", "", tempVec[i]);
		m_lines.push_back(tempVec[i]);
	}

	return true;
}

bool TextScanner::AppendFromMemoryAddressRaw( const char *pCharArray, int size )
{
	std::vector<std::string> tempVec= StringTokenize(pCharArray, "\n");

	for (unsigned int i=0; i < tempVec.size(); i++)
	{
		m_lines.push_back(tempVec[i]);
	}

	return true;
}