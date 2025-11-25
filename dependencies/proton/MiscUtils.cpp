#include "MiscUtils.h"
#include <cassert>

void MemorySerializeString( std::string &num, uint8_t *pMem, int &offsetInOut, bool bWriteToMem)
{
	uint16_t len;
	assert(num.length() < 1024*64);

	if (bWriteToMem)
	{
		len = (uint16_t) num.length();

		//copy how the len, up to 64k
		memcpy(&pMem[offsetInOut], &len, sizeof(len));
		offsetInOut += sizeof(len);

		//now copy the actual content
		memcpy(&pMem[offsetInOut], num.c_str(), len);
	
	} else
	{
		memcpy(&len, &pMem[offsetInOut], sizeof(len));
		offsetInOut += sizeof(len);

		num.resize(len);

		//trust me.
		memcpy((void*)num.c_str(), &pMem[offsetInOut], len);
	}
	offsetInOut += len;
}

bool MemorySerializeStringLarge(std::string& num, uint8_t* pMem, int& offsetInOut, bool bWriteToMem, uint32_t maxBytesInPacket) 
{
    uint32_t len;
    if (bWriteToMem) 
    {
        len = (uint32_t)num.length();
        if (maxBytesInPacket != 0 && len > (maxBytesInPacket - 4))
            return false;

        memcpy(&pMem[offsetInOut], &len, sizeof(len));
        offsetInOut += sizeof(len);

        memcpy(&pMem[offsetInOut], num.c_str(), len);
    } 
    else 
    {
        memcpy(&len, &pMem[offsetInOut], sizeof(len));
        offsetInOut += sizeof(len);

        num.resize(len);
        memcpy((void*)num.c_str(), &pMem[offsetInOut], len);
    }

    offsetInOut += len;
    return true;
}

void MemorySerializeRaw(uint8_t* pVar, uint8_t *pMem, int sizeBytes, int &offsetInOut, bool bWriteToMem )
{
	if (sizeBytes == 0) return;

	if (bWriteToMem)
	{
		::memcpy(&pMem[offsetInOut], pVar, sizeBytes);
	} else
	{
		::memcpy(pVar, &pMem[offsetInOut], sizeBytes);
	}

	offsetInOut += sizeBytes;
}

void MemorySerializeStringEncrypted( std::string &num, uint8_t *pMem, int &offsetInOut, bool bWriteToMem,int cryptID, const char *secretCode)
{
	uint16_t len;
	int codeLen=(int)strlen(secretCode);
	assert(codeLen>0 && codeLen<256);

	cryptID=cryptID%codeLen;	// cryptID is which position in secretCode you start at

	assert(num.length() < 1024*64);

	if (bWriteToMem)
	{
		len = (uint16_t) num.length();

		//copy how the len, up to 64k
		memcpy(&pMem[offsetInOut], &len, sizeof(len));
		offsetInOut += sizeof(len);

		//now copy the actual content, encrypted
		for(int i=0;i<len;i++)
		{
			uint8 b=(uint8_t)num.c_str()[i];
			b=b^secretCode[cryptID++];
			if(cryptID>=codeLen)
				cryptID=0;
			pMem[offsetInOut++]=b;
		}
	} 
	else
	{
		memcpy(&len, &pMem[offsetInOut], sizeof(len));
		offsetInOut += sizeof(len);

		num.resize(len);

		for(int i=0;i<len;i++)
		{
			uint8 b=pMem[offsetInOut++];
			num[i]=b^secretCode[cryptID++];
			if(cryptID>=codeLen)
				cryptID=0;
		}
	}
}

std::vector<std::string> StringTokenize (const  std::string  & theString,  const  std::string  & theDelimiter )
{
	std::vector<std::string> theStringVector;

	if (!theString.empty())
	{
		size_t  start = 0, end = 0;

		while ( end != std::string::npos )
		{
			end = theString.find( theDelimiter, start );

			// If at end, use length=maxLength.  Else use length=end-start.
			theStringVector.push_back( theString.substr( start,
														 (end == std::string::npos) ? std::string::npos : end - start ) );

			// If at end, use start=maxSize.  Else use start=end+delimiter.
			start = (   ( end > (std::string::npos - theDelimiter.size()) )
						?  std::string::npos  :  end + theDelimiter.size()    );
		}
	}

	return theStringVector;
}

void StringReplace(const std::string& what, const std::string& with, std::string& in)
{
	size_t pos = 0;
	size_t whatLen = what.length();
	size_t withLen = with.length();
	while ((pos = in.find(what, pos)) != std::string::npos)
	{
		in.replace(pos, whatLen, with);
		pos += withLen;
	}
}

inline std::string TrimRight (const std::string & s, const std::string & t)
{ 
	std::string d (s); 
	std::string::size_type i (d.find_last_not_of (t));
	if (i == std::string::npos)
		return "";
	else
		return d.erase (d.find_last_not_of (t) + 1) ; 
}  // end of trim_right

std::string TrimLeft (const std::string & s, const std::string & t) 
{ 
	std::string d (s); 
	return d.erase (0, s.find_first_not_of (t)) ; 
}  // end of trim_left

std::string StripWhiteSpace(const std::string & s)
{
	std::string d (s); 
	return TrimLeft (TrimRight (d, RT_UTIL_SPACES), RT_UTIL_SPACES) ; 
}

std::string SeparateStringSTL(std::string input, int index, char delimiter)
{
	//yes, this is pretty crap
	assert(input.size() < 4048 && "Fix this function..");
	char stInput[4048];
	if (SeparateString(input.c_str(), index, delimiter, stInput))
	{
		return stInput;
	} 

#ifdef _DEBUG
	::printf("Debug warning: SeparateStringSTL unable to find delimiter\n");
#endif
	return "";
}

bool SeparateString (const char str[], int num, char delimiter, char *return1) 
{
	size_t sLen = strlen(str);
	int l = 0;
	int c = 0;

	for (unsigned int k = 0; str[k] != 0; k++)
	{
		if (str[k] == delimiter)
		{
			l++;
			if (l == num+1)
				break;

			if (k < sLen) c = 0;
		}
		if (str[k] != delimiter)
			return1[c++] = str[k];
	}
	return1[c] = 0;

	if (l < num)
	{
		return1[0] = 0;
		return(false);
	}
	return true;
}

int StringToInt( const std::string &s )
{
	return atoi(s.c_str());
}

unsigned int StringToUInt32(const std::string& s)
{
	unsigned long lresult = std::stoul(s, 0, 10);
	unsigned int result = lresult;
	assert(result == lresult && "That's weird...");
	return result;
}

uint32_t StringToColor(const std::string& rgba)
{
    std::vector<std::string> pieces = StringTokenize(rgba, ",");

    uint32_t color = 0;

    if (pieces.size() == 4)
    {
        color = MAKE_RGBA(StringToInt(pieces[0]), StringToInt(pieces[1]), StringToInt(pieces[2]), StringToInt(pieces[3]));
    }
    else
    {
        ::printf("Badly formatted color: %s\n", rgba.c_str());
        color = 0;
    }

    return color;
}

std::string GetFileExtension(std::string fileName)
{
	size_t index = fileName.find_last_of('.');
	if (index == std::string::npos)
	{
		return "";
	}

	return fileName.substr(index+1, fileName.length());
}

uint8 * LoadFileIntoMemoryBasic(std::string fileName, unsigned int *length, bool bUseSavePath, bool bAddBasePath)
{
	*length = 0;

	if (bAddBasePath)
	{
		if (bUseSavePath)
		{
			//fileName = GetSavePath() + fileName;
		} else
		{
			//fileName = GetBaseAppPath() + fileName;
		}
	}
	
	FILE *fp = fopen(fileName.c_str(), "rb");
	if (!fp)
	{
		//file not found	
		return NULL;
	}

	fseek(fp, 0, SEEK_END);
	*length = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	uint8 *pData = new uint8[(*length) +1];
	
	if (!pData)
	{
		fclose(fp);
		*length = UINT_MAX; //signal a mem error
		return NULL;
	}
	pData[*length] = 0; 
	fread(pData, *length, 1, fp);
	fclose(fp);

	//we add an extra null at the end to be nice, when loading text files this can be useful

	return pData;
}

uint32 HashString(const char *str, int32 len)
{
	if (!str) return 0;

	unsigned char *n = (unsigned char *) str;
	uint32 acc = 0x55555555;

	if (len == 0)
	{
		while (*n)
			acc = (acc >> 27) + (acc << 5) + *n++;
	} else
	{
		for (int32 i=0; i < len; i++)
		{
			acc = (acc >> 27) + (acc << 5) + *n++;
		}
	}
	return acc;
}

unsigned int GetHashOfFile(std::string fName)
{
	unsigned int hash;
	int size;
	uint8 *pData;

	unsigned int lsize;
	//we use basic so it won't automatically decompress an .rttex for us
	pData = LoadFileIntoMemoryBasic(fName, &lsize, false, false);
	size = lsize;

	if (!pData) return 0; //no file, no hash
	hash = HashString((char*)pData, size);
	if (pData) { ::free(pData); }
	return hash;
}

void MemorySerialize( std::string &num, uint8 *pMem, int &offsetInOut, bool bWriteToMem)
{
    uint16 len;
    assert(num.length() < 1024*64);

    if (bWriteToMem)
    {
        len = (uint16) num.length();

        //copy how the len, up to 64k
        memcpy(&pMem[offsetInOut], &len, sizeof(len));
        offsetInOut += sizeof(len);

        //now copy the actual content
        memcpy(&pMem[offsetInOut], num.c_str(), len);
    
    } else
    {
        memcpy(&len, &pMem[offsetInOut], sizeof(len));
        offsetInOut += sizeof(len);

        num.resize(len);

        //trust me.
        memcpy((void*)num.c_str(), &pMem[offsetInOut], len);
    }
    offsetInOut += len;
}

static constexpr std::size_t utf8_sequence_length(unsigned char lead) noexcept
{
    // Determine length from the leading byte.
    if (lead < 0x80)                return 1; // ASCII
    if ((lead & 0xE0) == 0xC0)      return 2; // 110xxxxx
    if ((lead & 0xF0) == 0xE0)      return 3; // 1110xxxx
    if ((lead & 0xF8) == 0xF0)      return 4; // 11110xxx
    return 1; // invalid lead -> treat as single byte to avoid splitting buffer
}

static bool valid_utf8_continuation(unsigned char b) noexcept
{
    // Continuation bytes must have binary form 10xxxxxx (0x80..0xBF).
    return (b & 0xC0) == 0x80;
}

void TruncateString(std::string &input, std::size_t len)
{
    if (len == 0) { input.clear(); return; }
    std::size_t byteIndex = 0;
    std::size_t charCount = 0;
    const std::size_t n = input.size();

    while (byteIndex < n && charCount < len) {
        unsigned char lead = static_cast<unsigned char>(input[byteIndex]);
        std::size_t seqLen = utf8_sequence_length(lead);

        // If sequence would run past the end of the string, stop (avoid splitting).
        if (byteIndex + seqLen > n) {
            // treat remainder as invalid/truncated; stop before it
            break;
        }

        // Validate continuation bytes; if invalid, treat the lead as a single byte
        bool ok = true;
        for (std::size_t k = 1; k < seqLen; ++k) {
            if (!valid_utf8_continuation(static_cast<unsigned char>(input[byteIndex + k]))) {
                ok = false;
                break;
            }
        }
        if (!ok) {
            // treat this byte as a single (invalid) code point
            seqLen = 1;
        }

        byteIndex += seqLen;
        ++charCount;
    }

    // If we consumed fewer or equal bytes than original, truncate to byteIndex.
    // If charCount < len and byteIndex == n, the string is shorter than requested -> leave it.
    if (byteIndex < n) {
        input.erase(byteIndex); // keep [0, byteIndex)
    }
}