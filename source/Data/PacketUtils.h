#pragma once

#include <iostream>
#include <enet/include/enet.h>

extern int GetMessageTypeFromPacket(ENetPacket* pNetPacket);
extern const char* GetTextPointerFromPacket(ENetPacket* pNetPacket);

#pragma pack(push, 1)
struct GameUpdatePacket
{
    GameUpdatePacket() {}

    uint8_t type = 0;
 
    union
    {
        uint8_t field0 = 0;
        uint8_t characterPunchEffect;
    };
 
    union
    {
        uint8_t field1 = 0;
        uint8_t itemRemoveCount;
        uint8_t characterBuildLength;
    };
    union
    {
        uint8_t field2 = 0;
        uint8_t adventureType;
        uint8_t itemGiveCount;
        uint8_t characterPunchLength;
    };
 
    union
    {
        int32_t field3 = 0;
        int32_t netID;
        int32_t adventureItemID;
        int32_t objectChangeType;
        int32_t userID;
        int32_t particleID;
    };
 
    union
    {
        int32_t field4 = 0;
        int32_t characterPupilColor;
        int32_t itemNetID;
        int32_t tilesLength;
        int32_t itemPunched;
    };
 
    int32_t flags = 0;
 
    union
    {
        float field5 = 0;
        float characterWaterSpeed;
        float objectCount; // Why the fuck is the object count a float??
    };
 
    union
    {
        int32_t field6 = 0;
        int32_t functionDelay;
        int32_t itemID;
        int32_t characterFlags;
        int32_t damage;
        int32_t objectID;
    };
 
    union
    {
        float field7 = 0;
        float walkPosX;
        float posX;
        float characterVelocity;
    };
 
    union
    {
        float field8 = 0;
        float walkPosY;
        float posY;
        float characterStrength;
    };
 
    union
    {
        float field9 = 0;
        float characterSpeed;
        float particleSize;
    };
 
    union
    {
        float field10 = 0;
        float characterGravity;
        float secondaryParticleID;
    };
 
    union
    {
 
        float field11 = 0;
 
    };
    union
    {
        uint32_t field12 = 0;
        uint32_t adventureTileX;
        uint32_t tileX;
        uint32_t characterHairColor;
    };
 
    union
    {
        uint32_t field13 = 0;
        uint32_t adventureTileY;
        uint32_t tileY;
        uint32_t characterEyeColor;
        uint32_t secondaryParticleSize;
    };
 
    uint32_t extraDataSize = 0; //must be initialized if packet flags contain extra data
};
 
#pragma pack(pop)

extern GameUpdatePacket* GetStructPointerFromPacket(ENetPacket* pNetPacket);
 
//todo: other packet flags too
#define NET_GAME_PACKET_FLAG_EXTENDED (1 << 3)
 
enum {
    PACKET_STATE = 0,
    PACKET_CALL_FUNCTION,
    PACKET_UPDATE_STATUS,
    PACKET_TILE_CHANGE_REQUEST,
    PACKET_SEND_MAP_DATA,
    PACKET_SEND_TILE_UPDATE_DATA,
    PACKET_SEND_TILE_UPDATE_DATA_MULTIPLE,
    PACKET_TILE_ACTIVATE_REQUEST,
    PACKET_TILE_APPLY_DAMAGE,
    PACKET_SEND_INVENTORY_STATE,
    PACKET_ITEM_ACTIVATE_REQUEST,
    PACKET_ITEM_ACTIVATE_OBJECT_REQUEST,
    PACKET_SEND_TILE_TREE_STATE,
    PACKET_MODIFY_ITEM_INVENTORY,
    PACKET_ITEM_CHANGE_OBJECT,
    PACKET_SEND_LOCK,
    PACKET_SEND_ITEM_DATABASE_DATA,
    PACKET_SEND_PARTICLE_EFFECT,
    PACKET_SET_ICON_STATE,
    PACKET_ITEM_EFFECT,
    PACKET_SET_CHARACTER_STATE,
    PACKET_PING_REPLY,
    PACKET_PING_REQUEST,
    PACKET_GOT_PUNCHED,
    PACKET_APP_CHECK_RESPONSE,
    PACKET_APP_INTEGRITY_FAIL,
    PACKET_DISCONNECT,
    PACKET_BATTLE_JOIN,
    PACKET_BATTLE_EVENT,
    PACKET_USE_DOOR,
    PACKET_SEND_PARENTAL,
    PACKET_GONE_FISHIN,
    PACKET_STEAM,
    PACKET_PET_BATTLE,
    PACKET_NPC,
    PACKET_SPECIAL,
    PACKET_SEND_PARTICLE_EFFECT_V2,
    PACKET_ACTIVE_ARROW_TO_ITEM,
    PACKET_SELECT_TILE_INDEX,
    PACKET_SEND_PLAYER_TRIBUTE_DATA, //39
    PACKET_PVE_UNK1, //no names for these 5, so i named them unk.
    PACKET_PVE_UNK2,
    PACKET_PVE_UNK3,
    PACKET_PVE_UNK4,
    PACKET_PVE_UNK5,
    PACKET_SET_EXTRA_MODS,
    PACKET_ON_STEP_ON_TILE_MOD,
    PACKET_MAXVAL                    //not real, just for string overflow
};