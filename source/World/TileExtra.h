#pragma once

#include "../Manager/ItemInfoManager.h"

class TileExtra
{
public:
    virtual ~TileExtra() {}
    eItemType m_extraType;
};

class SignExtra : public TileExtra
{
public:
    virtual ~SignExtra() override {}

    uint32_t GetEstimatedMem(bool bClientPacket = true)
    {
        uint32_t res = 0;
        res += sizeof(short) + m_label.size();
        res += sizeof(unsigned int);
        return res;
    }

    std::string m_label = "based server 3";
    unsigned int m_flags = 0;
};

class DoorExtra : public TileExtra
{
public:
    virtual ~DoorExtra() override {}

    uint32_t GetEstimatedMem(bool bClientPacket = true)
    {
        uint32_t res = 0;
        res += sizeof(short) + m_label.size();
        res += sizeof(uint8_t);
        return res;
    }

    std::string m_label = "based server 3 door";
    uint8_t m_bIsLocked = false;

    // sside
    std::string m_doorID = "";
    std::string m_target = "";
};

class LockExtra : public TileExtra
{
public:
    virtual ~LockExtra() override {}

    uint32_t GetEstimatedMem(bool bClientPacket = true)
    {
        uint32_t res = 0;
        res += sizeof(unsigned int);
        res += sizeof(int);
        res += sizeof(unsigned int);
        res += sizeof(unsigned int) * m_admins.size();
        return res;
    }

    unsigned int m_lockSettings{};
    int m_lockOwnerID = 1;
    unsigned int m_adminCount{};
    std::vector<unsigned int> m_admins;
};