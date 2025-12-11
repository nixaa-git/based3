#ifndef ItemInfoManager_h__
#define ItemInfoManager_h__
#include <iostream>
#include <vector>
#include <map>
#include "ItemDB.h"

#include <proton/TextScanner.h>

#ifdef __unix__
    #include <stdint.h>
#endif

//enum ePlayModType; // make a forward declaration for the client ig

enum ePlayModType
{
    NONE = 0,
    TEST
};

#define RT_ITEM_INFO_VERSION 8

enum eItemInfoFlags
{
	ITEM_INFO_FLAG_FLIPPABLE = 1,
	ITEM_INFO_FLAG_EDITABLE = 2,
	ITEM_INFO_FLAG_SEEDLESS = 4,
	ITEM_INFO_FLAG_PERMANENT = 8,
	ITEM_INFO_FLAG_DROPLESS = 16,
	ITEM_INFO_FLAG_NO_SELF = 32,
	ITEM_INFO_FLAG_NO_SHADOW = 64,
	ITEM_INFO_FLAG_WORLDLOCKED = 128,
	ITEM_INFO_FLAG_BETA = 256,
	ITEM_INFO_FLAG_AUTOPICKUP = 512,
	ITEM_INFO_FLAG_MOD = 1024,
	ITEM_INFO_FLAG_RANDOM_GROW = 2048, // RANDOM_GROW?
	ITEM_INFO_FLAG_PUBLIC = 4096,
	ITEM_INFO_FLAG_FOREGROUND = 8192,
	ITEM_INFO_FLAG_HOLIDAY = 16384,
	ITEM_INFO_FLAG_UNTRADEABLE = 32768
};

enum eItemType
{
	ITEM_TYPE_FIST = 0,
	ITEM_TYPE_WRENCH,
	ITEM_TYPE_USER_DOOR,
	ITEM_TYPE_LOCK,
	ITEM_TYPE_GEMS,
	ITEM_TYPE_TREASURE,
	ITEM_TYPE_DEADLY,
	ITEM_TYPE_TRAMPOLINE,
	ITEM_TYPE_CONSUMABLE,
	ITEM_TYPE_GATEWAY,
	ITEM_TYPE_SIGN,
	ITEM_TYPE_SFX_WITH_EXTRA_FRAME,
	ITEM_TYPE_BOOMBOX,
	ITEM_TYPE_DOOR,
	ITEM_TYPE_PLATFORM,
	ITEM_TYPE_BEDROCK,
	ITEM_TYPE_LAVA,
	ITEM_TYPE_NORMAL,
	ITEM_TYPE_BACKGROUND,
	ITEM_TYPE_SEED,
	ITEM_TYPE_CLOTHES,
	ITEM_TYPE_NORMAL_WITH_EXTRA_FRAME,
	ITEM_TYPE_BACKGD_SFX_EXTRA_FRAME,
	ITEM_TYPE_BACK_BOOMBOX,
	ITEM_TYPE_BOUNCY,
	ITEM_TYPE_POINTY,
	ITEM_TYPE_PORTAL,
	ITEM_TYPE_CHECKPOINT,
	ITEM_TYPE_MUSIC_NOTE,
	ITEM_TYPE_ICE,
	ITEM_TYPE_30,
	ITEM_TYPE_SWITCHEROO,
	ITEM_TYPE_CHEST,
	ITEM_TYPE_MAILBOX,
	ITEM_TYPE_BULLETIN,
	ITEM_TYPE_PINATA,
	ITEM_TYPE_DICE,
	ITEM_TYPE_COMPONENT,
	ITEM_TYPE_PROVIDER,
	ITEM_TYPE_LAB,
	ITEM_TYPE_ACHIEVEMENT,
	ITEM_TYPE_WEATHER_MACHINE,
	ITEM_TYPE_SCOREBOARD,
	ITEM_TYPE_SUNGATE,
	ITEM_TYPE_PROFILE,
	ITEM_TYPE_DEADLY_IF_ON,
	ITEM_TYPE_HEART_MONITOR,
	ITEM_TYPE_DONATION_BOX,
	ITEM_TYPE_TOYBOX,
	ITEM_TYPE_MANNEQUIN,
	ITEM_TYPE_CAMERA,
	ITEM_TYPE_MAGIC_EGG,
	ITEM_TYPE_TEAM,
	ITEM_TYPE_GAME_GEN,
	ITEM_TYPE_XENONITE,
	ITEM_TYPE_DRESSUP,
	ITEM_TYPE_CRYSTAL,
	ITEM_TYPE_BURGLAR,
	ITEM_TYPE_COMPACTOR,
	ITEM_TYPE_SPOTLIGHT,
	ITEM_TYPE_WIND,
	ITEM_TYPE_DISPLAY_BLOCK,
	ITEM_TYPE_VENDING,
	ITEM_TYPE_FISH_TANK,
	ITEM_TYPE_PET_FISH,
	ITEM_TYPE_SOLAR,
	ITEM_TYPE_FORGE,
	ITEM_TYPE_GIVING_TREE,
	ITEM_TYPE_GIVING_TREE_STUMP,
	ITEM_TYPE_STEAMPUNK,
	ITEM_TYPE_STEAM_LAVA_IF_ON,
	ITEM_TYPE_STEAM_ORGAN,
	ITEM_TYPE_TAMAGOTCHI,
	ITEM_TYPE_SEWING,
	ITEM_TYPE_FLAG,
	ITEM_TYPE_LOBSTER_TRAP,
	ITEM_TYPE_ART_CANVAS,
	ITEM_TYPE_BATTLE_CAGE,
	ITEM_TYPE_PET_TRAINER,
	ITEM_TYPE_STEAM_ENGINE,
	ITEM_TYPE_LOCK_BOT,
	ITEM_TYPE_WEATHER_SPECIAL,
	ITEM_TYPE_SPIRIT_STORAGE,
	ITEM_TYPE_DISPLAY_SHELF,
	ITEM_TYPE_VIP_DOOR,
	ITEM_TYPE_CHALLENGE_TIMER,
	ITEM_TYPE_CHALLENGE_FLAG,
	ITEM_TYPE_FISH_MOUNT,
	ITEM_TYPE_PORTRAIT,
	ITEM_TYPE_WEATHER_SPECIAL2,
	ITEM_TYPE_FOSSIL,
	ITEM_TYPE_FOSSIL_PREP,
	ITEM_TYPE_DNA_MACHINE,
	ITEM_TYPE_BLASTER,
	ITEM_TYPE_VALHOWLA,
	ITEM_TYPE_CHEMSYNTH,
	ITEM_TYPE_CHEMTANK,
	ITEM_TYPE_STORAGE,
	ITEM_TYPE_OVEN,
	ITEM_TYPE_SUPER_MUSIC,
	ITEM_TYPE_GEIGER_CHARGE,
	ITEM_TYPE_ADVENTURE_RESET,
	ITEM_TYPE_TOMB_ROBBER,
	ITEM_TYPE_FACTION,
	ITEM_TYPE_RED_FACTION,
	ITEM_TYPE_GREEN_FACTION,
	ITEM_TYPE_BLUE_FACTION,
	ITEM_TYPE_ARTIFACT
};

enum eItemMaterial
{
	ITEM_MATERIAL_WOOD = 0,
	ITEM_MATERIAL_GLASS,
	ITEM_MATERIAL_ROCK,
	ITEM_MATERIAL_METAL
};

enum eTileVisualEffect
{
	CHOOSE_VISUAL_EFFECT_NONE = 0,
	CHOOSE_VISUAL_EFFECT_FLAME_LICK,
	CHOOSE_VISUAL_EFFECT_SMOKING,
	CHOOSE_VISUAL_EFFECT_GLOW_TINT1,
	CHOOSE_VISUAL_EFFECT_ANIM,
	CHOOSE_VISUAL_EFFECT_BUBBLES,
	CHOOSE_VISUAL_EFFECT_PET,
	CHOOSE_VISUAL_EFFECT_PET_ANIM,
	CHOOSE_VISUAL_EFFECT_NO_ARMS,
	CHOOSE_VISUAL_EFFECT_WAVEY,
	CHOOSE_VISUAL_EFFECT_WAVEY_ANIM,
	CHOOSE_VISUAL_EFFECT_BOTH_ARMS,
	CHOOSE_VISUAL_EFFECT_LOW_HAIR,
	CHOOSE_VISUAL_EFFECT_UNDER_FACE,
	CHOOSE_VISUAL_EFFECT_SKIN_TINT,
	CHOOSE_VISUAL_EFFECT_MASK,
	CHOOSE_VISUAL_EFFECT_ANIM_MASK,
	CHOOSE_VISUAL_EFFECT_LOW_HAIR_MASK,
	CHOOSE_VISUAL_EFFECT_GHOST,
	CHOOSE_VISUAL_EFFECT_PULSE,
	CHOOSE_VISUAL_EFFECT_COLORIZE,
	CHOOSE_VISUAL_EFFECT_COLORIZE_TO_SHIRT,
	CHOOSE_VISUAL_EFFECT_COLORIZE_ANIM,
	CHOOSE_VISUAL_EFFECT_HIGH_FACE,
	CHOOSE_VISUAL_EFFECT_HIGH_FACE_ANIM,
	CHOOSE_VISUAL_EFFECT_RAINBOW_SHIFT,
	CHOOSE_VISUAL_EFFECT_BACKFORE,
	CHOOSE_VISUAL_EFFECT_COLORIZE_WITH_SKIN,
	CHOOSE_VISUAL_EFFECT_NO_RENDER,
	CHOOSE_VISUAL_EFFECT_SPIN,
	CHOOSE_VISUAL_EFFECT_OFF_HAND,
	CHOOSE_VISUAL_EFFECT_WINGED,
	CHOOSE_VISUAL_EFFECT_SINK,
	CHOOSE_VISUAL_EFFECT_DARKNESS,
	CHOOSE_VISUAL_EFFECT_LIGHT_SOURCE,
	CHOOSE_VISUAL_EFFECT_LIGHT_IF_ON,
	CHOOSE_VISUAL_EFFECT_DISCOLOR,
	CHOOSE_VISUAL_EFFECT_STEP_SPIN,
	CHOOSE_VISUAL_EFFECT_PET_COLORED,
	CHOOSE_VISUAL_EFFECT_SILK_FOOT,
	CHOOSE_VISUAL_EFFECT_TILTY,
	CHOOSE_VISUAL_EFFECT_TILTY_DARK,
	CHOOSE_VISUAL_EFFECT_NEXT_FRAME_IF_ON,
	CHOOSE_VISUAL_EFFECT_WOBBLE,
	CHOOSE_VISUAL_EFFECT_SCROLL,
	CHOOSE_VISUAL_EFFECT_LIGHT_SOURCE_PULSE
};

enum eTileCollisionType
{
	TILE_COLLISION_NONE = 0,
	TILE_COLLISION_SOLID,
	TILE_COLLISION_JUMP_THROUGH,
	TILE_COLLISION_GATEWAY,
	TILE_COLLISION_IF_OFF,
	TILE_COLLISION_ONE_WAY,
	TILE_COLLISION_VIP,
	TILE_COLLISION_JUMP_DOWN,
	TILE_COLLISION_ADVENTURE,
	TILE_COLLISION_IF_ON,
	TILE_COLLISION_FACTION
};

enum eItemImageStorage
{
	ITEM_IMAGE_STORAGE_SINGLE_FRAME_ALONE = 0,
	ITEM_IMAGE_STORAGE_SINGLE_FRAME,
	ITEM_IMAGE_STORAGE_SMART_EDGE,
	ITEM_IMAGE_STORAGE_SMART_EDGE_HORIZ,
	ITEM_IMAGE_STORAGE_SMART_CLING,
	ITEM_IMAGE_STORAGE_SMART_OUTER,
	ITEM_IMAGE_STORAGE_RANDOM,
	ITEM_IMAGE_STORAGE_SMART_EDGE_VERT,
	ITEM_IMAGE_STORAGE_SMART_EDGE_HORIZ_CAVE,
	ITEM_IMAGE_STORAGE_SMART_CLING2
};

enum eItemElement
{
	ITEM_ELEMENT_NONE = 0,
	ITEM_ELEMENT_FIRE,
	ITEM_ELEMENT_WATER,
	ITEM_ELEMENT_AIR,
	ITEM_ELEMENT_WIND,
	ITEM_ELEMENT_EARTH
};

enum eBodyParts
{
	BODY_PARTS_HAT = 0,
	BODY_PARTS_SHIRT,
	BODY_PARTS_PANTS,
	BODY_PARTS_SHOES,
	BODY_PARTS_FACE_ITEM,
	BODY_PARTS_HAND,
	BODY_PARTS_BACK,
	BODY_PARTS_HAIR,
	BODY_PARTS_CHEST_ITEM,
	NUM_BODY_PARTS
};


eItemMaterial StringToItemMaterial(const std::string& materialType);
eItemElement StringToItemElement(const std::string& elementType);
eItemType StringToItemType(const std::string& itemType);
eTileVisualEffect StringToTileVisualEffect(const std::string& visualType);
eItemImageStorage StringToTileStorage(const std::string& storageType);
eTileCollisionType StringToTileCollisionType(const std::string& collisionType);
eBodyParts StringToBodyPart(const std::string& bodyPart);

bool IsAdventureItem(int itemID);

struct FileUpdate
{
	std::string rawName		= "";
	std::string fileName	= "";
	bool bNeedsUpdating		= false;
};

class ItemInfo
{
public:
	ItemInfo() = default;
	~ItemInfo() = default;

	void CalculateGrowImagesAndColors(int seed);
	void Serialize(uint8_t* pBuffer, int& offset, bool bWrite, uint16_t version, bool bClientData);
	void CheckItemForUpdates(std::vector<FileUpdate>& fileUpdates) const;

public:
	int m_itemID = -1;

	// TODO: actually change these to the enum objects. Thats probably why they all are 4 bytes long in the class.
	int m_type = 0; // gets translated to uint8_tin serialization. 
	eItemMaterial m_materialType = ITEM_MATERIAL_WOOD;
	eTileVisualEffect m_visualType = CHOOSE_VISUAL_EFFECT_NONE;
	eItemImageStorage m_storageType = ITEM_IMAGE_STORAGE_SMART_EDGE;
	eTileCollisionType m_collisionType = TILE_COLLISION_NONE;
	eItemElement m_elementType = ITEM_ELEMENT_NONE;

	std::string m_fileName = "";
	uint32_t m_fileHash = 0;
	uint8_t m_frameX = 0;
	uint8_t m_frameY = 0;

	std::string m_name = "";

	uint16_t m_rarity = 0;

	uint8_t m_layer = 0;
	uint8_t m_hp = 0;
	uint8_t m_maxCanHold = 0;

	uint8_t m_growMultiplier = 0;

	uint32_t m_secondsToHeal = 0;
	uint32_t m_recycleGemCount = 0;

	int m_cookTime = 0;
	eBodyParts m_bodyPart = BODY_PARTS_HAT;

	uint16_t m_itemInfoFlags = 0;
	uint16_t m_serverFlags = 0;

	uint8_t m_seedBaseType = 0;
	uint8_t m_seedOverlayType = 0;
	uint8_t m_treeBaseType = 0;
	uint8_t m_treeOverlayType = 0;

	uint32_t m_treeFgColor = 0;
	uint32_t m_treeBgColor = 0;

	uint16_t m_seedMix1 = 0;
	uint16_t m_seedMix2 = 0;

	uint32_t m_secondsToBloom = 0;

	union
	{
		uint32_t m_maxFruit = 0;
		int m_lockPower;
	};

	std::string m_extraFileName = "";
	uint32_t m_extraFileHash = 0;
	uint32_t m_animMS = 400;
	ePlayModType m_playModID;

	uint8_t m_minDropCount = 0;
	uint8_t m_maxDropCount = 0;
	uint8_t m_goodieFlags = 0;
	uint16_t m_goodieID = 0;
	uint32_t m_bloomSecondsToGiveOrTake = 0;

	int m_minimumProtocol = 0;

	uint32_t m_checkSum = 0;

	uint32_t m_animationFlags = 0;
	std::string m_animationFrames = "";
	std::string m_animationFramesV2 = "";
	std::string m_animationFile = "";
	int m_dualLayerX = 0;
	int m_dualLayerY = 0;


	std::string m_petName = "";
	std::string m_petPrefix = "";
	std::string m_petSuffix = "";
	std::string m_petAbility = "";

	std::string m_description = "";
};

class ItemInfoManager
{
public:
	ItemInfoManager();
	~ItemInfoManager() = default;

#ifdef RT_SERVER
	bool Load(TextScanner scanner, const std::string& fileName);
#else
	bool Load(TextScanner scanner);
#endif
	void CreateSeedVersionOfLastItemAdded(int itemIDOfLastItemAdded);

	int GetBaseItem(int itemID);

	void CalculateRarityForAllItems();
	uint32_t GetRarityForItem(ItemInfo* pItemInfo, uint32_t unused);
	void HackInSpecialProperties();

	void SetupFileHashes(bool bSetupOgg, bool bUseBetaHashes);

	uint8_t* SaveToMem(int & offset, uint16_t version, bool bUseClientData);

	ItemInfo* GetItemByIDSafe(int itemID);
	bool LoadFromMem(uint8_t* pBuffer, bool bUseClientData);

public:
	std::vector<ItemInfo> m_itemInfo = {};
};

#endif // ItemInfoManager_h__
