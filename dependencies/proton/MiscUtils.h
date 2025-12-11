#pragma once

#include <iostream>
#include <vector>
#include <sstream>
#include <string>

#ifdef __unix__
    #include <stdint.h>
    #include <string.h>
#endif

typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;

typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;

#define RT_UTIL_SPACES " \t\r\n"
#define MAKE_RGB(r, g, b)      ( ((uint32_t)(r) << 8) + ((uint32_t)(g) << 16) + ((uint32_t)(b) << 24) )
#define MAKE_RGBA(r, g, b, a) ( ((uint32_t)(r) << 8) + ((uint32_t)(g) << 16) + ((uint32_t)(b) << 24) + ((uint32_t)(a)))

std::vector<std::string> StringTokenize (const  std::string  & theString,  const  std::string  & theDelimiter );
void StringReplace(const std::string& what, const std::string& with, std::string& in);
bool SeparateString (const char str[], int num, char delimiter, char *return1);
std::string SeparateStringSTL(std::string input, int index, char delimiter);
uint32 HashString(const char *str, int32 len);
unsigned int GetHashOfFile(std::string fName);

inline std::string TrimRight (const std::string & s, const std::string & t);
std::string TrimLeft (const std::string & s, const std::string & t);
std::string StripWhiteSpace(const std::string & s);

template<typename T>
inline std::string toString(T value)
{
	std::ostringstream o;
	o << value;
	return o.str();
}

int StringToInt( const std::string &s );
unsigned int StringToUInt32(const std::string& s);
uint32_t StringToColor(const std::string& rgba);
std::string GetFileExtension(std::string fileName);

void MemorySerializeString( std::string &num, uint8_t *pMem, int &offsetInOut, bool bWriteToMem);
bool MemorySerializeStringLarge(std::string& num, uint8_t* pMem, int& offsetInOut, bool bWriteToMem, uint32_t maxBytesInPacket);
void MemorySerializeRaw(uint8_t* pVar, uint8_t *pMem, int sizeBytes, int &offsetInOut, bool bWriteToMem );
void MemorySerializeStringEncrypted( std::string &num, uint8_t *pMem, int &offsetInOut, bool bWriteToMem,int cryptID,const char *secretCode);

template <typename T>
inline void MemorySerialize(T& out, uint8_t* in, int& offsetInOut, bool bWriteToMem)
{
    uint8_t* addr = in + offsetInOut;

    if (bWriteToMem)
    {
        memcpy(addr, &out, sizeof(T));
    }
    else
    {
        memcpy(&out, addr, sizeof(T));
    }

    offsetInOut += static_cast<int>(sizeof(T));
}

void MemorySerialize( std::string &num, uint8 *pMem, int &offsetInOut, bool bWriteToMem);

inline uint32_t ReliableHash(const void* data, size_t dataLen)
{
	if (!data) return 0;

	uint32_t hash = 0x55555555;

	for (size_t i = 0; i < dataLen; i++)
		hash = (hash >> 27) + (hash << 5) + static_cast<const uint8_t*>(data)[i];

	return hash;
}

void TruncateString(std::string &input, std::size_t len);
