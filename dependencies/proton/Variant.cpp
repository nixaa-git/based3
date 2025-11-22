#include "Variant.h"
#include <cstring>

Variant::Variant() 
{
    m_type = TYPE_UNUSED;
}

Variant::~Variant() 
{
    //
}

void Variant::Set(float var) 
{
    m_type = TYPE_FLOAT; 
    *((float*)m_var) = var;
}

float& Variant::GetFloat() 
{
    if (m_type == TYPE_UNUSED) 
        Set(0.f);

    return *((float*)m_var);
}

const float& Variant::GetFloat() const 
{ 
    return *((float*)m_var); 
}

void Variant::Set(uint32_t var) 
{
    m_type = TYPE_UINT32; 
    *((uint32_t*)m_var) = var;
}

uint32_t& Variant::GetUInt32() 
{
    if (m_type == TYPE_UNUSED) 
        Set(uint32_t(0));

    return *((uint32_t*)m_var);
}
const uint32_t& Variant::GetUInt32() const 
{ 
    return *((uint32_t*)m_var); 
}

void Variant::Set(int32_t var) 
{
    m_type = TYPE_INT32; 
    *((int32_t*)m_var) = var;
}

int32_t& Variant::GetInt32() 
{
    if (m_type == TYPE_UNUSED) 
        Set(int32_t(0));
        
    return *((int32_t*)m_var);
}

const int32_t& Variant::GetInt32() const 
{ 
    return *((int32_t*)m_var); 
}

void Variant::Set(std::string const &var) 
{
	m_type = TYPE_STRING;
	m_string = var;
}

std::string& Variant::GetString() 
{
    return m_string;
}

const std::string& Variant::GetString() const 
{ 
    return m_string; 
}

void Variant::Set(const CL_Vec2f& var) 
{
    m_type = TYPE_VECTOR2; 
    *((CL_Vec2f*)m_var) = var;
}

CL_Vec2f& Variant::GetVector2() 
{
    if (m_type == TYPE_UNUSED)
        Set(CL_Vec2f(0,0));

    return *((CL_Vec2f*)m_var);
}

const CL_Vec2f& Variant::GetVector2() const 
{
    return *((CL_Vec2f*)m_var);
}

void Variant::Set(const CL_Vec3f& var) 
{
    m_type = TYPE_VECTOR3; 
    *((CL_Vec3f*)m_var) = var;
}

CL_Vec3f& Variant::GetVector3() 
{
    if (m_type == TYPE_UNUSED)
        Set(CL_Vec3f(0,0,0));

    return *((CL_Vec3f*)m_var);
}

const CL_Vec3f& Variant::GetVector3() const 
{
    return  *((CL_Vec3f*)m_var);
}

int GetSizeOfData(uint8_t type) 
{
	switch (type)
	{
	    case TYPE_UINT32:
	    case TYPE_INT32:
	    case TYPE_FLOAT:
		    return sizeof(int);

	    case TYPE_VECTOR2:
		    return sizeof(CL_Vec2f);

	    case TYPE_VECTOR3:
		    return sizeof(CL_Vec3f);

	    default:
            return 0;
	}

    return 0;
}

uint8_t* VariantList::SerializeToMem(uint32_t& sizeOut)
{
	uint8_t variants = 0;
	size_t dataLen = 0;
	size_t varSize = 0;

    for (uint8_t i = 0; i < C_MAX_VARIANT_LIST_PARMS; i++)
	{
		if (m_variant[i].GetType() == TYPE_STRING) 
            varSize = m_variant[i].GetString().size() + sizeof(uint32_t);
        else 
            varSize = GetSizeOfData(m_variant[i].GetType());

		if (varSize < 1)
            continue;

        variants++;
        dataLen += varSize + 2;
	}

    int offsetInOut = 0;
    size_t memSize = 1 + dataLen;
	uint8_t* pMem = (uint8_t*)std::malloc(memSize);
    if (!pMem)
        return NULL;

    MemorySerialize(variants, pMem, offsetInOut, true);

	for (uint8_t i = 0; i < C_MAX_VARIANT_LIST_PARMS; i++)
	{
        uint8_t varType = m_variant[i].GetType();
		size_t varSize = GetSizeOfData(m_variant[i].GetType());
        if (varSize < 1 && varType != TYPE_STRING)
            continue;

        MemorySerialize(i, pMem, offsetInOut, true);
		MemorySerialize(varType, pMem, offsetInOut, true);
		
        if (m_variant[i].GetType() == TYPE_STRING) 
            MemorySerializeStringLarge(m_variant[i].GetString(), pMem, offsetInOut, true, 0);
        else 
        {
            ::memcpy(pMem + offsetInOut, m_variant[i].m_var, varSize); 
            offsetInOut += varSize;
		}
	}

	sizeOut = memSize;
	return pMem;
}
