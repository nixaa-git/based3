#include "ItemInfoManager.h"
#include <proton/MiscUtils.h>
#include <cassert>

#include "../CoreApp.h"

//#include "util/CRandom.h"
//#include "util/ResourceUtils.h"

int g_checksumBase = 0;

ItemInfoManager::ItemInfoManager()
{
	//g_checksumBase = Random(2834);
}

eBodyParts StringToBodyPart(const std::string& bodyPart)
{
	eBodyParts part = BODY_PARTS_HAT;
	if (bodyPart == "HAT")
	{
		part = BODY_PARTS_HAT;
	}
	else if (bodyPart == "HAIR")
	{
		part = BODY_PARTS_HAIR;
	}
	else if (bodyPart == "SHIRT")
	{
		part = BODY_PARTS_SHIRT;
	}
	else if (bodyPart == "PANTS")
	{
		part = BODY_PARTS_PANTS;
	}
	else if (bodyPart == "SHOES")
	{
		part = BODY_PARTS_SHOES;
	}
	else if (bodyPart == "FACEITEM")
	{
		part = BODY_PARTS_FACE_ITEM;
	}
	else if (bodyPart == "HAND")
	{
		part = BODY_PARTS_HAND;
	}
	else if (bodyPart == "CHESTITEM")
	{
		part = BODY_PARTS_CHEST_ITEM;
	}
	else if (bodyPart == "BACK")
	{
		part = BODY_PARTS_BACK;
	}
	else
	{
		::printf("Warning: StringToTileStorage doesn't know what a %s is\n", bodyPart.c_str());
		part = BODY_PARTS_HAT;
	}

	return part;
}



eItemMaterial StringToItemMaterial(const std::string& materialType)
{
	eItemMaterial mat = ITEM_MATERIAL_WOOD;

	if (materialType == "MATERIAL_WOOD")
	{
		mat = ITEM_MATERIAL_WOOD;
	}
	else if (materialType == "MATERIAL_GLASS")
	{
		mat = ITEM_MATERIAL_GLASS;
	}
	else if (materialType == "MATERIAL_ROCK")
	{
		mat = ITEM_MATERIAL_ROCK;
	}
	else if (materialType == "MATERIAL_METAL")
	{
		mat = ITEM_MATERIAL_METAL;
	}

	return mat;
}


eItemElement StringToItemElement(const std::string& elementType)
{
	if (elementType == "FIRE")
	{
		return ITEM_ELEMENT_FIRE;
	}
	else if (elementType == "WATER")
	{
		return ITEM_ELEMENT_WATER;
	}
	else if (elementType == "AIR")
	{
		return ITEM_ELEMENT_AIR;
	}
	else if (elementType == "WIND")
	{
		return ITEM_ELEMENT_WIND;
	}
	else if (elementType == "EARTH")
	{
		return ITEM_ELEMENT_EARTH;
	}

	return ITEM_ELEMENT_NONE;
}


eItemType StringToItemType(const std::string& itemType)
{
	if (itemType == "TYPE_DOOR")
	{
		return ITEM_TYPE_DOOR;
	}
	else if (itemType == "TYPE_BEDROCK")
	{
		return ITEM_TYPE_BEDROCK;
	}
	else if (itemType == "TYPE_LAVA")
	{
		return ITEM_TYPE_LAVA;
	}
	else if (itemType == "TYPE_USER_DOOR")
	{
		return ITEM_TYPE_USER_DOOR;
	}
	else if (itemType == "TYPE_NORMAL")
	{
		return ITEM_TYPE_NORMAL;
	}
	else if (itemType == "TYPE_SIGN")
	{
		return ITEM_TYPE_SIGN;
	}
	else if (itemType == "TYPE_BACKGROUND")
	{
		return ITEM_TYPE_BACKGROUND;
	}
	else if (itemType == "TYPE_FIST")
	{
		return ITEM_TYPE_FIST;
	}
	else if (itemType == "TYPE_CLOTHES")
	{
		return ITEM_TYPE_CLOTHES;
	}
	else if (itemType == "TYPE_BOOMBOX")
	{
		return ITEM_TYPE_BOOMBOX;
	}
	else if (itemType == "TYPE_SEED")
	{
		return ITEM_TYPE_SEED;
	}
	else if (itemType == "TYPE_LOCK")
	{
		return ITEM_TYPE_LOCK;
	}
	else if (itemType == "TYPE_WRENCH")
	{
		return ITEM_TYPE_WRENCH;
	}
	else if (itemType == "TYPE_PLATFORM")
	{
		return ITEM_TYPE_PLATFORM;
	}
	else if (itemType == "TYPE_TREASURE")
	{
		return ITEM_TYPE_TREASURE;
	}
	else if (itemType == "TYPE_SFX_WITH_EXTRA_FRAME")
	{
		return ITEM_TYPE_SFX_WITH_EXTRA_FRAME;
	}
	else if (itemType == "TYPE_BACKGD_SFX_EXTRA_FRAME")
	{
		return ITEM_TYPE_BACKGD_SFX_EXTRA_FRAME;
	}
	else if (itemType == "TYPE_GEMS")
	{
		return ITEM_TYPE_GEMS;
	}
	else if (itemType == "TYPE_DEADLY")
	{
		return ITEM_TYPE_DEADLY;
	}
	else if (itemType == "TYPE_TRAMPOLINE")
	{
		return ITEM_TYPE_TRAMPOLINE;
	}
	else if (itemType == "TYPE_CONSUMABLE")
	{
		return ITEM_TYPE_CONSUMABLE;
	}
	else if (itemType == "TYPE_GATEWAY")
	{
		return ITEM_TYPE_GATEWAY;
	}
	else if (itemType == "TYPE_NORMAL_WITH_EXTRA_FRAME")
	{
		return ITEM_TYPE_NORMAL_WITH_EXTRA_FRAME;
	}
	else if (itemType == "TYPE_BACK_BOOMBOX")
	{
		return ITEM_TYPE_BACK_BOOMBOX;
	}
	else if (itemType == "TYPE_BOUNCY")
	{
		return ITEM_TYPE_BOUNCY;
	}
	else if (itemType == "TYPE_POINTY")
	{
		return ITEM_TYPE_POINTY;
	}
	else if (itemType == "TYPE_PORTAL")
	{
		return ITEM_TYPE_PORTAL;
	}
	else if (itemType == "TYPE_CHECKPOINT")
	{
		return ITEM_TYPE_CHECKPOINT;
	}
	else if (itemType == "TYPE_MUSICNOTE")
	{
		return ITEM_TYPE_MUSIC_NOTE;
	}
	else if (itemType == "TYPE_ICE")
	{
		return ITEM_TYPE_ICE;
	}
	else if (itemType == "TYPE_SWITCHEROO")
	{
		return ITEM_TYPE_SWITCHEROO;
	}
	else if (itemType == "TYPE_CHEST")
	{
		return ITEM_TYPE_CHEST;
	}
	else if (itemType == "TYPE_MAILBOX")
	{
		return ITEM_TYPE_MAILBOX;
	}
	else if (itemType == "TYPE_BULLETIN")
	{
		return ITEM_TYPE_BULLETIN;
	}
	else if (itemType == "TYPE_PINATA")
	{
		return ITEM_TYPE_PINATA;
	}
	else if (itemType == "TYPE_DICE")
	{
		return ITEM_TYPE_DICE;
	}
	else if (itemType == "TYPE_PROVIDER")
	{
		return ITEM_TYPE_PROVIDER;
	}
	else if (itemType == "TYPE_COMPONENT")
	{
		return ITEM_TYPE_COMPONENT;
	}
	else if (itemType == "TYPE_LAB")
	{
		return ITEM_TYPE_LAB;
	}
	else if (itemType == "TYPE_ACHIEVEMENT")
	{
		return ITEM_TYPE_ACHIEVEMENT;
	}
	else if (itemType == "TYPE_WEATHER_MACHINE")
	{
		return ITEM_TYPE_WEATHER_MACHINE;
	}
	else if (itemType == "TYPE_SCOREBOARD")
	{
		return ITEM_TYPE_SCOREBOARD;
	}
	else if (itemType == "TYPE_SUNGATE")
	{
		return ITEM_TYPE_SUNGATE;
	}
	else if (itemType == "TYPE_PROFILE")
	{
		return ITEM_TYPE_PROFILE;
	}
	else if (itemType == "TYPE_DEADLY_IF_ON")
	{
		return ITEM_TYPE_DEADLY_IF_ON;
	}
	else if (itemType == "TYPE_HEARTMONITOR")
	{
		return ITEM_TYPE_HEART_MONITOR;
	}
	else if (itemType == "TYPE_DONATION_BOX")
	{
		return ITEM_TYPE_DONATION_BOX;
	}
	else if (itemType == "TYPE_TOYBOX")
	{
		return ITEM_TYPE_TOYBOX;
	}
	else if (itemType == "TYPE_MANNEQUIN")
	{
		return ITEM_TYPE_MANNEQUIN;
	}
	else if (itemType == "TYPE_CAMERA")
	{
		return ITEM_TYPE_CAMERA;
	}
	else if (itemType == "TYPE_MAGICEGG")
	{
		return ITEM_TYPE_MAGIC_EGG;
	}
	else if (itemType == "TYPE_TEAM")
	{
		return ITEM_TYPE_TEAM;
	}
	else if (itemType == "TYPE_GAME_GEN")
	{
		return ITEM_TYPE_GAME_GEN;
	}
	else if (itemType == "TYPE_XENONITE")
	{
		return ITEM_TYPE_XENONITE;
	}
	else if (itemType == "TYPE_DRESSUP")
	{
		return ITEM_TYPE_DRESSUP;
	}
	else if (itemType == "TYPE_CRYSTAL")
	{
		return ITEM_TYPE_CRYSTAL;
	}
	else if (itemType == "TYPE_BURGLAR")
	{
		return ITEM_TYPE_BURGLAR;
	}
	else if (itemType == "TYPE_COMPACTOR")
	{
		return ITEM_TYPE_COMPACTOR;
	}
	else if (itemType == "TYPE_SPOTLIGHT")
	{
		return ITEM_TYPE_SPOTLIGHT;
	}
	else if (itemType == "TYPE_WIND")
	{
		return ITEM_TYPE_WIND;
	}
	else if (itemType == "TYPE_DISPLAY_BLOCK")
	{
		return ITEM_TYPE_DISPLAY_BLOCK;
	}
	else if (itemType == "TYPE_VENDING")
	{
		return ITEM_TYPE_VENDING;
	}
	else if (itemType == "TYPE_FISHTANK")
	{
		return ITEM_TYPE_FISH_TANK;
	}
	else if (itemType == "TYPE_PETFISH")
	{
		return ITEM_TYPE_PET_FISH;
	}
	else if (itemType == "TYPE_SOLAR")
	{
		return ITEM_TYPE_SOLAR;
	}
	else if (itemType == "TYPE_FORGE")
	{
		return ITEM_TYPE_FORGE;
	}
	else if (itemType == "TYPE_GIVING_TREE")
	{
		return ITEM_TYPE_GIVING_TREE;
	}
	else if (itemType == "TYPE_GIVING_TREE_STUMP")
	{
		return ITEM_TYPE_GIVING_TREE_STUMP;
	}
	else if (itemType == "TYPE_STEAMPUNK")
	{
		return ITEM_TYPE_STEAMPUNK;
	}
	else if (itemType == "TYPE_STEAM_LAVA_IF_ON")
	{
		return ITEM_TYPE_STEAM_LAVA_IF_ON;
	}
	else if (itemType == "TYPE_STEAM_ORGAN")
	{
		return ITEM_TYPE_STEAM_ORGAN;
	}
	else if (itemType == "TYPE_TAMAGOTCHI")
	{
		return ITEM_TYPE_TAMAGOTCHI;
	}
	else if (itemType == "TYPE_SEWING")
	{
		return ITEM_TYPE_SEWING;
	}
	else if (itemType == "TYPE_FLAG")
	{
		return ITEM_TYPE_FLAG;
	}
	else if (itemType == "TYPE_LOBSTER_TRAP")
	{
		return ITEM_TYPE_LOBSTER_TRAP;
	}
	else if (itemType == "TYPE_ARTCANVAS")
	{
		return ITEM_TYPE_ART_CANVAS;
	}
	else if (itemType == "TYPE_BATTLE_CAGE")
	{
		return ITEM_TYPE_BATTLE_CAGE;
	}
	else if (itemType == "TYPE_PET_TRAINER")
	{
		return ITEM_TYPE_PET_TRAINER;
	}
	else if (itemType == "TYPE_STEAM_ENGINE")
	{
		return ITEM_TYPE_STEAM_ENGINE;
	}
	else if (itemType == "TYPE_LOCK_BOT")
	{
		return ITEM_TYPE_LOCK_BOT;
	}
	else if (itemType == "TYPE_WEATHER_SPECIAL")
	{
		return ITEM_TYPE_WEATHER_SPECIAL;
	}
	else if (itemType == "TYPE_SPIRIT_STORAGE")
	{
		return ITEM_TYPE_SPIRIT_STORAGE;
	}
	else if (itemType == "TYPE_DISPLAY_SHELF")
	{
		return ITEM_TYPE_DISPLAY_SHELF;
	}
	else if (itemType == "TYPE_VIP_DOOR")
	{
		return ITEM_TYPE_VIP_DOOR;
	}
	else if (itemType == "TYPE_CHAL_TIMER")
	{
		return ITEM_TYPE_CHALLENGE_TIMER;
	}
	else if (itemType == "TYPE_CHAL_FLAG")
	{
		return ITEM_TYPE_CHALLENGE_FLAG;
	}
	else if (itemType == "TYPE_FISH_MOUNT")
	{
		return ITEM_TYPE_FISH_MOUNT;
	}
	else if (itemType == "TYPE_PORTRAIT")
	{
		return ITEM_TYPE_PORTRAIT;
	}
	else if (itemType == "TYPE_WEATHER_SPECIAL2")
	{
		return ITEM_TYPE_WEATHER_SPECIAL2;
	}
	else if (itemType == "TYPE_FOSSIL")
	{
		return ITEM_TYPE_FOSSIL;
	}
	else if (itemType == "TYPE_FOSSIL_PREP")
	{
		return ITEM_TYPE_FOSSIL_PREP;
	}
	else if (itemType == "TYPE_DNA_MACHINE")
	{
		return ITEM_TYPE_DNA_MACHINE;
	}
	else if (itemType == "TYPE_BLASTER")
	{
		return ITEM_TYPE_BLASTER;
	}
	else if (itemType == "TYPE_VALHOWLA")
	{
		return ITEM_TYPE_VALHOWLA;
	}
	else if (itemType == "TYPE_CHEMSYNTH")
	{
		return ITEM_TYPE_CHEMSYNTH;
	}
	else if (itemType == "TYPE_CHEMTANK")
	{
		return ITEM_TYPE_CHEMTANK;
	}
	else if (itemType == "TYPE_STORAGE")
	{
		return ITEM_TYPE_STORAGE;
	}
	else if (itemType == "TYPE_OVEN")
	{
		return ITEM_TYPE_OVEN;
	}
	else if (itemType == "TYPE_SUPER_MUSIC")
	{
		return ITEM_TYPE_SUPER_MUSIC;
	}
	else if (itemType == "TYPE_GEIGERCHARGE")
	{
		return ITEM_TYPE_GEIGER_CHARGE;
	}
	else if (itemType == "TYPE_ADVENTURE_RESET")
	{
		return ITEM_TYPE_ADVENTURE_RESET;
	}
	else if (itemType == "TYPE_TOMB_ROBBER")
	{
		return ITEM_TYPE_TOMB_ROBBER;
	}
	else if (itemType == "TYPE_FACTION")
	{
		return ITEM_TYPE_FACTION;
	}
	else if (itemType == "TYPE_RED_FACTION")
	{
		return ITEM_TYPE_RED_FACTION;
	}
	else if (itemType == "TYPE_GREEN_FACTION")
	{
		return ITEM_TYPE_GREEN_FACTION;
	}
	else if (itemType == "TYPE_BLUE_FACTION")
	{
		return ITEM_TYPE_BLUE_FACTION;
	}
	else if (itemType == "TYPE_ARTIFACT")
	{
		return ITEM_TYPE_ARTIFACT;
	}

	return ITEM_TYPE_FIST;
}


eTileVisualEffect StringToTileVisualEffect(const std::string& visualType)
{
	if (visualType == "VISUAL_EFFECT_FLAME_LICK")
	{
		return CHOOSE_VISUAL_EFFECT_FLAME_LICK;
	}
	else if (visualType == "VISUAL_EFFECT_SMOKING")
	{
		return CHOOSE_VISUAL_EFFECT_SMOKING;
	}
	else if (visualType == "VISUAL_EFFECT_GLOW_TINT1")
	{
		return CHOOSE_VISUAL_EFFECT_GLOW_TINT1;
	}
	else if (visualType == "VISUAL_EFFECT_ANIM")
	{
		return CHOOSE_VISUAL_EFFECT_ANIM;
	}
	else if (visualType == "VISUAL_EFFECT_BUBBLES")
	{
		return CHOOSE_VISUAL_EFFECT_BUBBLES;
	}
	else if (visualType == "VISUAL_EFFECT_PET")
	{
		return CHOOSE_VISUAL_EFFECT_PET;
	}
	else if (visualType == "VISUAL_EFFECT_PET_ANIM")
	{
		return CHOOSE_VISUAL_EFFECT_PET_ANIM;
	}
	else if (visualType == "VISUAL_EFFECT_NO_ARMS")
	{
		return CHOOSE_VISUAL_EFFECT_NO_ARMS;
	}
	else if (visualType == "VISUAL_EFFECT_WAVEY")
	{
		return CHOOSE_VISUAL_EFFECT_WAVEY;
	}
	else if (visualType == "VISUAL_EFFECT_WAVEY_ANIM")
	{
		return CHOOSE_VISUAL_EFFECT_WAVEY_ANIM;
	}
	else if (visualType == "VISUAL_EFFECT_BOTHARMS")
	{
		return CHOOSE_VISUAL_EFFECT_BOTH_ARMS;
	}
	else if (visualType == "VISUAL_EFFECT_LOWHAIR")
	{
		return CHOOSE_VISUAL_EFFECT_LOW_HAIR;
	}
	else if (visualType == "VISUAL_EFFECT_UNDERFACE")
	{
		return CHOOSE_VISUAL_EFFECT_UNDER_FACE;
	}
	else if (visualType == "VISUAL_EFFECT_SKINTINT")
	{
		return CHOOSE_VISUAL_EFFECT_SKIN_TINT;
	}
	else if (visualType == "VISUAL_EFFECT_MASK")
	{
		return CHOOSE_VISUAL_EFFECT_MASK;
	}
	else if (visualType == "VISUAL_EFFECT_ANIM_MASK")
	{
		return CHOOSE_VISUAL_EFFECT_ANIM_MASK;
	}
	else if (visualType == "VISUAL_EFFECT_LOWHAIR_MASK")
	{
		return CHOOSE_VISUAL_EFFECT_LOW_HAIR_MASK;
	}
	else if (visualType == "VISUAL_EFFECT_GHOST")
	{
		return CHOOSE_VISUAL_EFFECT_GHOST;
	}
	else if (visualType == "VISUAL_EFFECT_PULSE")
	{
		return CHOOSE_VISUAL_EFFECT_PULSE;
	}
	else if (visualType == "VISUAL_EFFECT_COLORIZE")
	{
		return CHOOSE_VISUAL_EFFECT_COLORIZE;
	}
	else if (visualType == "VISUAL_EFFECT_COLORIZE_TO_SHIRT")
	{
		return CHOOSE_VISUAL_EFFECT_COLORIZE_TO_SHIRT;
	}
	else if (visualType == "VISUAL_EFFECT_COLORIZE_ANIM")
	{
		return CHOOSE_VISUAL_EFFECT_COLORIZE_ANIM;
	}
	else if (visualType == "VISUAL_EFFECT_HIGHFACE")
	{
		return CHOOSE_VISUAL_EFFECT_HIGH_FACE;
	}
	else if (visualType == "VISUAL_EFFECT_HIGHFACE_ANIM")
	{
		return CHOOSE_VISUAL_EFFECT_HIGH_FACE_ANIM;
	}
	else if (visualType == "VISUAL_EFFECT_RAINBOW_SHIFT")
	{
		return CHOOSE_VISUAL_EFFECT_RAINBOW_SHIFT;
	}
	else if (visualType == "VISUAL_EFFECT_BACKFORE")
	{
		return CHOOSE_VISUAL_EFFECT_BACKFORE;
	}
	else if (visualType == "VISUAL_EFFECT_COLORIZE_WITH_SKIN")
	{
		return CHOOSE_VISUAL_EFFECT_COLORIZE_WITH_SKIN;
	}
	else if (visualType == "VISUAL_EFFECT_NO_RENDER")
	{
		return CHOOSE_VISUAL_EFFECT_NO_RENDER;
	}
	else if (visualType == "VISUAL_EFFECT_SPIN")
	{
		return CHOOSE_VISUAL_EFFECT_SPIN;
	}
	else if (visualType == "VISUAL_EFFECT_OFFHAND")
	{
		return CHOOSE_VISUAL_EFFECT_OFF_HAND;
	}
	else if (visualType == "VISUAL_EFFECT_WINGED")
	{
		return CHOOSE_VISUAL_EFFECT_WINGED;
	}
	else if (visualType == "VISUAL_EFFECT_SINK")
	{
		return CHOOSE_VISUAL_EFFECT_SINK;
	}
	else if (visualType == "VISUAL_EFFECT_DARKNESS")
	{
		return CHOOSE_VISUAL_EFFECT_DARKNESS;
	}
	else if (visualType == "VISUAL_EFFECT_LIGHTSOURCE")
	{
		return CHOOSE_VISUAL_EFFECT_LIGHT_SOURCE;
	}
	else if (visualType == "VISUAL_EFFECT_LIGHT_IF_ON")
	{
		return CHOOSE_VISUAL_EFFECT_LIGHT_IF_ON;
	}
	else if (visualType == "VISUAL_EFFECT_DISCOLOR")
	{
		return CHOOSE_VISUAL_EFFECT_DISCOLOR;
	}
	else if (visualType == "VISUAL_EFFECT_STEP_SPIN")
	{
		return CHOOSE_VISUAL_EFFECT_STEP_SPIN;
	}
	else if (visualType == "VISUAL_EFFECT_PETCOLORED")
	{
		return CHOOSE_VISUAL_EFFECT_PET_COLORED;
	}
	else if (visualType == "VISUAL_EFFECT_SILKFOOT")
	{
		return CHOOSE_VISUAL_EFFECT_SILK_FOOT;
	}
	else if (visualType == "VISUAL_EFFECT_TILTY")
	{
		return CHOOSE_VISUAL_EFFECT_TILTY;
	}
	else if (visualType == "VISUAL_EFFECT_TILTY_DARK")
	{
		return CHOOSE_VISUAL_EFFECT_TILTY_DARK;
	}
	else if (visualType == "VISUAL_EFFECT_NEXT_FRAME_IF_ON")
	{
		return CHOOSE_VISUAL_EFFECT_NEXT_FRAME_IF_ON;
	}
	else if (visualType == "VISUAL_EFFECT_WOBBLE")
	{
		return CHOOSE_VISUAL_EFFECT_WOBBLE;
	}
	else if (visualType == "VISUAL_EFFECT_SCROLL")
	{
		return CHOOSE_VISUAL_EFFECT_SCROLL;
	}
	else if (visualType == "VISUAL_EFFECT_LIGHTSOURCE_PULSE")
	{
		return CHOOSE_VISUAL_EFFECT_LIGHT_SOURCE_PULSE;
	}

	return CHOOSE_VISUAL_EFFECT_NONE;
}


eItemImageStorage StringToTileStorage(const std::string& storageType)
{
	if (storageType == "STORAGE_SINGLE_FRAME_ALONE")
	{
		return ITEM_IMAGE_STORAGE_SINGLE_FRAME_ALONE;
	}
	else if (storageType == "STORAGE_SINGLE_FRAME")
	{
		return ITEM_IMAGE_STORAGE_SINGLE_FRAME;
	}
	else if (storageType == "STORAGE_SMART_EDGE")
	{
		return ITEM_IMAGE_STORAGE_SMART_EDGE;
	}
	else if (storageType == "STORAGE_SMART_EDGE_HORIZ")
	{
		return ITEM_IMAGE_STORAGE_SMART_EDGE_HORIZ;
	}
	else if (storageType == "STORAGE_SMART_CLING")
	{
		return ITEM_IMAGE_STORAGE_SMART_CLING;
	}
	else if (storageType == "STORAGE_SMART_CLING2")
	{
		return ITEM_IMAGE_STORAGE_SMART_CLING2;
	}
	else if (storageType == "STORAGE_SMART_OUTER")
	{
		return ITEM_IMAGE_STORAGE_SMART_OUTER;
	}
	else if (storageType == "STORAGE_RANDOM")
	{
		return ITEM_IMAGE_STORAGE_RANDOM;
	}
	else if (storageType == "STORAGE_SMART_EDGE_VERT")
	{
		return ITEM_IMAGE_STORAGE_SMART_EDGE_VERT;
	}
	else if (storageType == "STORAGE_SMART_EDGE_HORIZ_CAVE")
	{
		return ITEM_IMAGE_STORAGE_SMART_EDGE_HORIZ_CAVE;
	}
	else
	{
		::printf("Warning: StringToTileStorage doesn't know what a %s is\n", storageType.c_str());
	}

	return ITEM_IMAGE_STORAGE_SMART_EDGE;
}


eTileCollisionType StringToTileCollisionType(const std::string& collisionType)
{
	if (collisionType == "TILE_COLLISION_NONE")
	{
		return TILE_COLLISION_NONE;
	}
	else if (collisionType == "TILE_COLLISION_JUMP_THROUGH")
	{
		return TILE_COLLISION_JUMP_THROUGH;
	}
	else if (collisionType == "TILE_COLLISION_JUMP_DOWN")
	{
		return TILE_COLLISION_JUMP_DOWN;
	}
	else if (collisionType == "TILE_COLLISION_GATEWAY")
	{
		return TILE_COLLISION_GATEWAY;
	}
	else if (collisionType == "TILE_COLLISION_IF_OFF")
	{
		return TILE_COLLISION_IF_OFF;
	}
	else if (collisionType == "TILE_COLLISION_IF_ON")
	{
		return TILE_COLLISION_IF_ON;
	}
	else if (collisionType == "TILE_COLLISION_ONE_WAY")
	{
		return TILE_COLLISION_ONE_WAY;
	}
	else if (collisionType == "TILE_COLLISION_VIP")
	{
		return TILE_COLLISION_VIP;
	}
	else if (collisionType == "TILE_COLLISION_ADVENTURE")
	{
		return TILE_COLLISION_ADVENTURE;
	}
	else if (collisionType == "TILE_COLLISION_ADVENTURE")
	{
		return TILE_COLLISION_ADVENTURE;
	}

	return TILE_COLLISION_SOLID;
}

bool IsAdventureItem(int itemID)
{
	// if the item is a seed/not in range for the adventure items, we only allow crystal goblet and pineapple to be considered aventure items.
	if ((itemID < ITEM_ID_ADVENTURE_ITEM_ID_ROPE || itemID > ITEM_ID_ADVENTURE_ITEM_ID_TORCH)
		|| (itemID & 1))
	{
		return itemID == ITEM_ID_ADVENTURE_ITEM_ID_CRYSTAL_GOBLET || itemID == ITEM_ID_ADVENTURE_ITEM_ID_PINEAPPLE;
	}

	return true;
}

#ifdef RT_SERVER
bool ItemInfoManager::Load(TextScanner scanner, const std::string& fileName)
#else
bool ItemInfoManager::Load(TextScanner scanner)
#endif
{
	::printf("Please wait, loading tile definitions...\n");

	if (!scanner.IsLoaded())
	{
		::printf("Error getting tile definitions\n");
		return false;
	}

    ::printf("items file has %d lines\n", scanner.GetLineCount());
	
	int itemID = -1;

	for (int line = 0; line < scanner.GetLineCount(); line++)
	{
		std::string lineContents = scanner.GetLine(line);

		// For the line to work, it has to be at the very least two letters long to allow commenting.
		// Not sure in where real server does this, but it's good here because we don't waste time with other instructions before.
		if (lineContents.empty() || lineContents.length() < 3)
		{
			continue;
		}

		// Line is commented, it would look something like "//comment example"
		if (lineContents[0] == '/' && lineContents[1] == '/')
		{
			continue;
		}

		// #comment
		if (lineContents[0] == '#')
		{
			continue;
		}

        static std::string delim = "|";
		std::vector<std::string> pieces = StringTokenize(lineContents, delim);

		if (pieces[0] == "add_item")
		{
			ItemInfo* pCurInfo = NULL;
			// ! Has to have at least 18 params, just stop loading if one line doesn't.
			if (pieces.size() < 18)
			{
				::printf("Malformed item info on line %d\n", line);
				return false;
			}

			itemID = StringToInt(pieces[1]);

			// We probably don't intend this, but it's a possibility we want to modify an already existing item. Allow it like real server.
			if (itemID < m_itemInfo.size())
			{
				pCurInfo = &m_itemInfo[itemID];
			}
			else
			{
				m_itemInfo.resize(itemID + 1);

				pCurInfo = &m_itemInfo[itemID];

				if (m_itemInfo.size() >= 3)
				{
					// (m_itemInfo.back().m_itemID + 1) should equal itemID if the last item was added right.
					ItemInfo& oldItem = m_itemInfo[m_itemInfo.size() - 3];

					if ((oldItem.m_itemID + 2) != itemID)
					{
						::printf("ItemID's must be in order!\n");
						return false;
					}
				}
			}

			pCurInfo->m_description = "No info.";
			pCurInfo->m_itemID = itemID;
			pCurInfo->m_name = pieces[2];
			pCurInfo->m_type = StringToItemType(pieces[3]);
			pCurInfo->m_materialType = StringToItemMaterial(pieces[4]);
			pCurInfo->m_visualType = StringToTileVisualEffect(pieces[5]);
			pCurInfo->m_storageType = StringToTileStorage(pieces[6]);
			pCurInfo->m_frameX = StringToInt(pieces[7]);
			pCurInfo->m_frameY = StringToInt(pieces[8]);
			pCurInfo->m_fileName = pieces[9];
			pCurInfo->m_fileHash = StringToUInt32(pieces[10]);
			pCurInfo->m_layer = StringToInt(pieces[11]);
			pCurInfo->m_collisionType = StringToTileCollisionType(pieces[12]);
			pCurInfo->m_hp = StringToInt(pieces[13]) * 7;
			pCurInfo->m_secondsToHeal = StringToUInt32(pieces[14]);
			pCurInfo->m_recycleGemCount = StringToUInt32(pieces[15]);
			pCurInfo->m_elementType = StringToItemElement(pieces[16]);

			switch (pCurInfo->m_type)
			{
			case ITEM_TYPE_USER_DOOR:
			case ITEM_TYPE_LOCK:
			case ITEM_TYPE_GATEWAY:
			case ITEM_TYPE_SIGN:
			case ITEM_TYPE_BOOMBOX:
			case ITEM_TYPE_PORTAL:
			case ITEM_TYPE_SWITCHEROO:
			case ITEM_TYPE_DICE:
			case ITEM_TYPE_SUNGATE:
			case ITEM_TYPE_TEAM:
			case ITEM_TYPE_ADVENTURE_RESET:
			{
				if (!IsAdventureItem(itemID))
				{
					pCurInfo->m_itemInfoFlags |= ITEM_INFO_FLAG_EDITABLE;
				}
			}
			}

			if (pCurInfo->m_type == ITEM_TYPE_LOCK)
			{
				pCurInfo->m_itemInfoFlags |= 0x20c;
			}

			// create seed
			CreateSeedVersionOfLastItemAdded(itemID);
		}
		else if (pieces[0] == "setup_seed")
		{
			int itemID = StringToInt(pieces[1]);
			ItemInfo* pSeedInfo = &m_itemInfo[itemID];

			pSeedInfo->m_seedMix1 = StringToInt(pieces[3]);
			pSeedInfo->m_seedMix2 = StringToInt(pieces[5]);
			pSeedInfo->m_secondsToBloom = StringToUInt32(pieces[7]);
			pSeedInfo->m_maxFruit = StringToUInt32(pieces[9]);

			// Now apply flags from the parent to the seed if necessary.
			// Realistically this can't fail, but we could work on making this safer.
			ItemInfo* pSeedParent = &m_itemInfo[(itemID - 1)];

			if (pSeedParent->m_itemInfoFlags & ITEM_INFO_FLAG_SEEDLESS)
			{
				pSeedInfo->m_itemInfoFlags |= ITEM_INFO_FLAG_SEEDLESS;
			}

			if (pSeedParent->m_itemInfoFlags & ITEM_INFO_FLAG_MOD)
			{
				pSeedInfo->m_itemInfoFlags |= ITEM_INFO_FLAG_MOD;
			}

			if (pSeedParent->m_itemInfoFlags & ITEM_INFO_FLAG_HOLIDAY)
			{
				pSeedInfo->m_itemInfoFlags |= ITEM_INFO_FLAG_HOLIDAY;
			}

			uint32_t bgColor = StringToColor(pieces[11]);

			if (bgColor != 0)
			{
				pSeedInfo->m_treeBgColor = bgColor;
			}

			uint32_t fgColor = StringToColor(pieces[13]);

			if (fgColor != 0)
			{
				pSeedInfo->m_treeFgColor = fgColor;
			}
		}
		else if (pieces[0] == "set_cook")
		{
			m_itemInfo[itemID].m_cookTime = StringToInt(pieces[1]);
		}
		else if (pieces[0] == "set_lock_power")
		{
			m_itemInfo[itemID].m_lockPower = StringToInt(pieces[1]);
		}
		else if (pieces[0] == "desc")
		{
			m_itemInfo[itemID].m_description = pieces[1];
		}
		else if (pieces[0] == "set_minimum_protocol")
		{
			m_itemInfo[itemID].m_minimumProtocol = StringToInt(pieces[1]);
		}
		else if (pieces[0] == "set_flags")
		{
			ItemInfo& itemInfo = m_itemInfo[itemID];
			for (int i = 1; i < pieces.size(); i++)
			{
				if (i >= pieces.size())
				{
					continue;
				}

				if (pieces[i] == "FLIPPABLE")
				{
					itemInfo.m_itemInfoFlags |= ITEM_INFO_FLAG_FLIPPABLE;
				}
				else if (pieces[i] == "EDITABLE")
				{
					itemInfo.m_itemInfoFlags |= ITEM_INFO_FLAG_EDITABLE;
				}
				else if (pieces[i] == "SEEDLESS")
				{
					itemInfo.m_itemInfoFlags |= ITEM_INFO_FLAG_SEEDLESS;
				}
				else if (pieces[i] == "PERMANENT")
				{
					itemInfo.m_itemInfoFlags |= ITEM_INFO_FLAG_PERMANENT;
				}
				else if (pieces[i] == "AUTOPICKUP")
				{
					itemInfo.m_itemInfoFlags |= ITEM_INFO_FLAG_AUTOPICKUP;
				}
				else if (pieces[i] == "DROPLESS")
				{
					itemInfo.m_itemInfoFlags |= ITEM_INFO_FLAG_DROPLESS;
				}
				else if (pieces[i] == "NOSELF")
				{
					itemInfo.m_itemInfoFlags |= ITEM_INFO_FLAG_NO_SELF;
				}
				else if (pieces[i] == "NOSHADOW")
				{
					itemInfo.m_itemInfoFlags |= ITEM_INFO_FLAG_NO_SHADOW;
				}
				else if (pieces[i] == "WORLDLOCKED")
				{
					itemInfo.m_itemInfoFlags |= ITEM_INFO_FLAG_WORLDLOCKED;
				}
				else if (pieces[i] == "FOREGROUND")
				{
					itemInfo.m_itemInfoFlags |= ITEM_INFO_FLAG_FOREGROUND;
				}
				else if (pieces[i] == "RANDGROW")
				{
					itemInfo.m_itemInfoFlags |= ITEM_INFO_FLAG_RANDOM_GROW;
				}
				else if (pieces[i] == "MOD")
				{
					itemInfo.m_itemInfoFlags |= ITEM_INFO_FLAG_MOD;
				}
				else if (pieces[i] == "PUBLIC")
				{
					itemInfo.m_itemInfoFlags |= ITEM_INFO_FLAG_PUBLIC;
				}
				else if (pieces[i] == "HOLIDAY")
				{
					itemInfo.m_itemInfoFlags |= ITEM_INFO_FLAG_HOLIDAY;
				}
				else if (pieces[i] == "UNTRADEABLE")
				{
					itemInfo.m_itemInfoFlags |= ITEM_INFO_FLAG_UNTRADEABLE;
				}
				else if (pieces[i] == "BETA")
				{
					itemInfo.m_itemInfoFlags |= ITEM_INFO_FLAG_BETA;
				}
				else if (pieces[i] == "SERVER_ALTMODE")
				{
					itemInfo.m_serverFlags |= 1;
				}
			}
		}
		else if (pieces[0] == "force_rarity")
		{
			m_itemInfo[itemID].m_rarity = StringToInt(pieces[1]);
			m_itemInfo[itemID + 1].m_rarity = StringToInt(pieces[1]);
		}
		else if (pieces[0] == "set_max_can_hold")
		{
			m_itemInfo[StringToInt(pieces[1])].m_maxCanHold = StringToInt(pieces[2]);
		}
		else if (pieces[0] == "set_extra_string")
		{
			m_itemInfo[StringToInt(pieces[1])].m_extraFileName = pieces[2];
			m_itemInfo[StringToInt(pieces[1])].m_animMS = StringToInt(pieces[4]);
		}
		else if (pieces[0] == "pet_name")
		{
			m_itemInfo[itemID].m_petName = pieces[1];
			m_itemInfo[itemID].m_petPrefix = pieces[2];
			m_itemInfo[itemID].m_petSuffix = pieces[3];
			m_itemInfo[itemID].m_petAbility = pieces[4];
		}
		else if (pieces[0] == "null_items")
		{
			int startID = StringToInt(pieces[1]);
			int endID = StringToInt(pieces[2]);

			for (int i = startID; i < endID; i++)
			{
				// Create seeds with the util
				if (i & 1)
				{
					continue;
				}

				m_itemInfo.emplace_back(ItemInfo());
				assert(i < m_itemInfo.size() && "Null item base wasn't created?");

				ItemInfo* pItemInfo = &m_itemInfo[i];

				pItemInfo->m_itemID = i;
				pItemInfo->m_name += "null_item" + toString(i);
				pItemInfo->m_hp = 1;
				pItemInfo->m_itemInfoFlags = 1300;
				pItemInfo->m_recycleGemCount = 0;
				pItemInfo->m_secondsToHeal = 2;
				pItemInfo->m_fileName = "tiles_page1.rttex";
				CreateSeedVersionOfLastItemAdded(i);
			}
		}
		else if (pieces[0] == "add_clothes")
		{
			ItemInfo* pCurInfo = NULL;
			// ! Has to have at least 18 params, just stop loading if one line doesn't.
			if (pieces.size() < 13)
			{
				::printf("Malformed item info on line %d\n", line);
				return false;
			}

			itemID = StringToInt(pieces[1]);

			// We probably don't intend this, but it's a possibility we want to modify an already existing item. Allow it like real server.
			if (itemID < m_itemInfo.size())
			{
				pCurInfo = &m_itemInfo[itemID];
			}
			else
			{
				m_itemInfo.resize(itemID + 1);

				pCurInfo = &m_itemInfo[itemID];

				if (m_itemInfo.size() >= 3)
				{
					// (m_itemInfo.back().m_itemID + 1) should equal itemID if the last item was added right.
					ItemInfo& oldItem = m_itemInfo[m_itemInfo.size() - 3];

					if ((oldItem.m_itemID + 2) != itemID)
					{
						::printf("ItemID's must be in order!\n");
						return false;
					}
				}
			}

			pCurInfo->m_elementType = ITEM_ELEMENT_WIND;
			pCurInfo->m_description = "No info.";
			pCurInfo->m_itemID = itemID;
			pCurInfo->m_name = pieces[2];
			pCurInfo->m_type = StringToItemType(pieces[3]);
			pCurInfo->m_visualType = StringToTileVisualEffect(pieces[4]);
			pCurInfo->m_storageType = StringToTileStorage(pieces[5]);
			pCurInfo->m_frameX = StringToInt(pieces[6]);
			pCurInfo->m_frameY = StringToInt(pieces[7]);
			pCurInfo->m_fileName = pieces[8];
			pCurInfo->m_fileHash = StringToInt(pieces[9]);
			pCurInfo->m_growMultiplier = 1;
			pCurInfo->m_bodyPart = StringToBodyPart(pieces[10]);
			pCurInfo->m_materialType = (eItemMaterial)StringToInt(pieces[11]);
			pCurInfo->m_recycleGemCount = StringToInt(pieces[12]);
			CreateSeedVersionOfLastItemAdded(itemID);
		}
		else if (pieces[0] == "quit_processing_items_now")
		{
			::printf("Found quit_processing_items_now, quiting item processing earlier, Seth probably wanted to test without local.txt\n");
			break;
			}
		else if (pieces[0] == "setup_provider")
		{
			if (pieces.size() < 8)
			{
				::printf("Malformed setup_provider on line %d\n", line);
				return false;
			}

			m_itemInfo[itemID].m_extraFileName = pieces[1];
			m_itemInfo[itemID].m_animMS = StringToInt(pieces[2]);
			m_itemInfo[itemID].m_minDropCount = StringToInt(pieces[3]);
			m_itemInfo[itemID].m_maxCanHold = StringToInt(pieces[4]);
			m_itemInfo[itemID].m_goodieFlags = 3;
			m_itemInfo[itemID].m_goodieID = StringToInt(pieces[5]);
			m_itemInfo[itemID].m_secondsToBloom = StringToInt(pieces[6]);
			m_itemInfo[itemID].m_bloomSecondsToGiveOrTake = StringToInt(pieces[7]);
		}
		else if (pieces[0] == "set_fx_flags")
		{
			for (int i = 0; i < pieces.size(); i++)
			{
				std::string flag = pieces[i];
				if (flag == "MULTI_ANIM_START")
				{
					m_itemInfo[itemID].m_animationFlags |= 1; // TODO: make an enum for these

					std::string finalFlags = "";
					for (int frames = (i + 1); frames < pieces.size(); frames++)
					{
						if (pieces[frames] == "MULTI_ANIM_END")
						{
							break;
						}

						finalFlags += pieces[frames] + "|";
					}

					m_itemInfo[itemID].m_animationFrames = finalFlags;
				}

				if (flag == "MULTI_ANIM2_START")
				{
					//0x20 = 32 - flag

					m_itemInfo[itemID].m_animationFlags |= 32;

					std::string finalFlags = "";
					for (int frames = (i + 1); frames < pieces.size(); frames++)
					{
						if (pieces[frames] == "MULTI_ANIM2_END")
						{
							break;
						}

						finalFlags += pieces[frames] + "|";
					}

					m_itemInfo[itemID].m_animationFramesV2 = finalFlags;
				}
				if (flag == "PING_PONG_ANIM")
				{
					m_itemInfo[itemID].m_animationFlags |= 2; // TODO: flags enum
				}
				else if (flag == "OVERLAY_OBJECT")
				{
					m_itemInfo[itemID].m_animationFlags |= 4;

					int nextPiece = i + 1;
					if (nextPiece >= pieces.size())
					{
						::printf("Umm, OVERLAY_OBJECT failed because the supposed animation file wasn't present?\n");
						continue;
					}

					m_itemInfo[itemID].m_animationFile = pieces[nextPiece];
				}
				else if (flag == "OFFSET_UP")
				{
					m_itemInfo[itemID].m_animationFlags |= 8;
				}
				else if (flag == "DUAL_LAYER")
				{
					m_itemInfo[itemID].m_animationFlags |= 16;

					int nextPiece = i + 1;
					if (nextPiece >= pieces.size())
					{
						::printf("Umm, DUAL_LAYER failed because the supposed dual layer position wasn't present?\n");
						continue;
					}

					std::vector<std::string> layers = StringTokenize(pieces[nextPiece], ",");

					m_itemInfo[itemID].m_dualLayerX = StringToInt(layers[0]);
					m_itemInfo[itemID].m_dualLayerY = StringToInt(layers[1]);
				}
				else if (flag == "USE_SKIN_TINT")
				{
					m_itemInfo[itemID].m_animationFlags |= 128;
				}
				else if (flag == "SEED_TINT_LAYER1")
				{
					m_itemInfo[itemID].m_animationFlags |= 256;
				}
				else if (flag == "SEED_TINT_LAYER2")
				{
					m_itemInfo[itemID].m_animationFlags |= 512;
				}
				else if (flag == "RAINBOW_TINT_LAYER1")
				{
					m_itemInfo[itemID].m_animationFlags |= 1024;
				}
				else if (flag == "RAINBOW_TINT_LAYER2")
				{
					m_itemInfo[itemID].m_animationFlags |= 2048;
				}
				else if (flag == "GLOW")
				{
					m_itemInfo[itemID].m_animationFlags |= 4096;
				}
			}
		}
	}

	// TODO: add goodie

	::printf("Items loaded, calculating rarities...\n");
	
	CalculateRarityForAllItems();
	HackInSpecialProperties();
	
	::printf("Checking for duplicate item recipes...\n");
	::printf("Loaded %zda tile definitions.  Taking up around %d bytes of memory.\n", m_itemInfo.size(), sizeof(ItemInfo) * m_itemInfo.size());

	return true;
}

void ItemInfoManager::HackInSpecialProperties()
{

}

void ItemInfoManager::CreateSeedVersionOfLastItemAdded(int itemIDOfLastItemAdded)
{
	int itemID = itemIDOfLastItemAdded + 1;

	if (m_itemInfo.size() <= itemID)
	{
		m_itemInfo.emplace_back(ItemInfo());
	}

	ItemInfo* pSeedInfo = &m_itemInfo[itemID];
	ItemInfo* pItemInfo = &m_itemInfo[itemIDOfLastItemAdded];

	if (pSeedInfo == NULL || pItemInfo == NULL)
	{
		return;
	}

	pSeedInfo->m_itemID = pItemInfo->m_itemID;
	pSeedInfo->m_type = pItemInfo->m_type;
	pSeedInfo->m_materialType = pItemInfo->m_materialType;
	pSeedInfo->m_elementType = pItemInfo->m_elementType;
	pSeedInfo->m_name = pItemInfo->m_name;
	pSeedInfo->m_fileHash = pItemInfo->m_fileHash;
	pSeedInfo->m_fileName = pItemInfo->m_fileName;
	pSeedInfo->m_visualType = pItemInfo->m_visualType;
	pSeedInfo->m_cookTime = pItemInfo->m_cookTime;
	pSeedInfo->m_frameX = pItemInfo->m_frameX;
	pSeedInfo->m_frameY = pItemInfo->m_frameY;
	pSeedInfo->m_storageType = pItemInfo->m_storageType;
	pSeedInfo->m_layer = pItemInfo->m_layer;
	pSeedInfo->m_collisionType = pItemInfo->m_collisionType;
	pSeedInfo->m_hp = pItemInfo->m_hp;
	pSeedInfo->m_itemInfoFlags = pItemInfo->m_itemInfoFlags;
	pSeedInfo->m_serverFlags = pItemInfo->m_serverFlags;
	pSeedInfo->m_secondsToHeal = pItemInfo->m_secondsToHeal;
	pSeedInfo->m_bodyPart = pItemInfo->m_bodyPart;

	pSeedInfo->m_seedOverlayType = pItemInfo->m_seedOverlayType;
	pSeedInfo->m_seedBaseType = pItemInfo->m_seedBaseType;
	pSeedInfo->m_treeBaseType = pItemInfo->m_treeBaseType;
	pSeedInfo->m_treeOverlayType = pItemInfo->m_treeOverlayType;

	pSeedInfo->m_treeFgColor = pItemInfo->m_treeFgColor;
	pSeedInfo->m_treeBgColor = pItemInfo->m_treeBgColor;

	pSeedInfo->m_seedMix1 = pItemInfo->m_seedMix1;
	pSeedInfo->m_seedMix2 = pItemInfo->m_seedMix2;

	pSeedInfo->m_maxFruit = pItemInfo->m_maxFruit;
	pSeedInfo->m_secondsToBloom = pItemInfo->m_secondsToBloom;
	pSeedInfo->m_growMultiplier = pItemInfo->m_growMultiplier;
	pSeedInfo->m_rarity = pItemInfo->m_rarity;
	pSeedInfo->m_maxCanHold = pItemInfo->m_maxCanHold;
	pSeedInfo->m_extraFileName = pItemInfo->m_extraFileName;
	pSeedInfo->m_animMS = pItemInfo->m_animMS;
	pSeedInfo->m_description = pItemInfo->m_description;
	pSeedInfo->m_playModID = pItemInfo->m_playModID;
	pSeedInfo->m_minimumProtocol = pItemInfo->m_recycleGemCount;
	pSeedInfo->m_petName = pItemInfo->m_petName;
	pSeedInfo->m_petAbility = pItemInfo->m_petAbility;
	pSeedInfo->m_petPrefix = pItemInfo->m_petPrefix;
	pSeedInfo->m_petSuffix = pItemInfo->m_petSuffix;
	pSeedInfo->m_recycleGemCount = pItemInfo->m_recycleGemCount;
	pSeedInfo->m_animationFlags = pItemInfo->m_animationFlags;
	pSeedInfo->m_animationFrames = pItemInfo->m_animationFrames;

	if (itemID == 611)
	{
		pSeedInfo->m_name = "Magic Egg";
	}
	else if (itemID == 2035)
	{
		pSeedInfo->m_name = "Starseed";
	}
	else if (itemID == 2037)
	{
		pSeedInfo->m_name = "Galactic Starseed";
	}
	else if (itemID == 4455)
	{
		pSeedInfo->m_name = "Mutated Seed";
	}
	else
	{
		pSeedInfo->m_name += " Seed";
	}

	pSeedInfo->m_itemID = itemID;
	pSeedInfo->m_type = ITEM_TYPE_SEED;
	pSeedInfo->m_collisionType = TILE_COLLISION_NONE;
	pSeedInfo->CalculateGrowImagesAndColors(itemIDOfLastItemAdded / 2);
	pSeedInfo->m_hp = 120;
	pSeedInfo->m_itemInfoFlags = 0;
	pSeedInfo->m_secondsToHeal = 2;
	pSeedInfo->m_visualType = CHOOSE_VISUAL_EFFECT_NONE;

	if (pItemInfo->m_itemInfoFlags & ITEM_INFO_FLAG_RANDOM_GROW)
	{
		pSeedInfo->m_itemInfoFlags |= ITEM_INFO_FLAG_RANDOM_GROW;
	}

	if (pItemInfo->m_itemInfoFlags & ITEM_INFO_FLAG_MOD)
	{
		pSeedInfo->m_itemInfoFlags |= ITEM_INFO_FLAG_MOD;
	}

	if (pItemInfo->m_itemInfoFlags & ITEM_INFO_FLAG_SEEDLESS)
	{
		pSeedInfo->m_itemInfoFlags |= ITEM_INFO_FLAG_SEEDLESS;
	}

	if (pItemInfo->m_itemInfoFlags & ITEM_INFO_FLAG_BETA)
	{
		pSeedInfo->m_itemInfoFlags |= ITEM_INFO_FLAG_BETA;
	}

	if (pItemInfo->m_itemInfoFlags & ITEM_INFO_FLAG_HOLIDAY)
	{
		pSeedInfo->m_itemInfoFlags |= ITEM_INFO_FLAG_HOLIDAY;
	}
}

/*
uint32_t GetBrightColorWithSeededRandom(CRandom& random)
{
	int random1 = random.Random(2);
	int random2 = random.Random(3);

	int rgba[4] = { 0 };

	int colorPaletIndicator = 0;

	if (random2 == 0)
	{
		random2 = random.Random(150);
		random2 += 105; // makes the color brighter
		colorPaletIndicator = random1 % 3;
		rgba[colorPaletIndicator] = random2;
	}
	else
	{
		random2 = random.Random(80);
		random2 += 175;
		colorPaletIndicator = random1 % 3;
		rgba[colorPaletIndicator] = random2;
	}

	uint32 random3 = random.Random(355U - random2);
	int result = 255;
	if (random3 < 256)
	{
		result = random.Random(355U - random2);
	}

	rgba[(random1 + 1) % 3] = result;

	int populator = 455 - (result + rgba[colorPaletIndicator]);
	random3 = random.Random(populator);
	random2 = 255;
	if (random3 < 256)
	{
		random2 = random.Random(populator);
	}

	rgba[(random1 + 2) % 3] = random2;

	// So here we do this... then we do a little bit of that, and it all makes sense!
	return (uint32)(rgba[2] * 0x1000000 + rgba[0] * 0x100 + 0xff + rgba[1] * 0x10000); // this is probably just MAKE_RGB but wna be sure
}
    */

void ItemInfo::CalculateGrowImagesAndColors(int seed)
{
    /*
	CRandom random = {};
	random.SetRandomSeed(seed);
	m_treeFgColor = GetBrightColorWithSeededRandom(random);
	m_treeBgColor = GetBrightColorWithSeededRandom(random);

	uint8_t imageSeed = seed >> 31;

	m_seedBaseType = (seed + (imageSeed >> 4) & 15) - (imageSeed >> 4);
	m_treeBaseType = (seed + (imageSeed >> 5) & 7) - (imageSeed >> 4);

	imageSeed = seed * 2;
	uint8_t slotSeed = seed * 2 >> 31;

	m_treeOverlayType = (imageSeed + (slotSeed >> 5) & 7) - (slotSeed >> 5);
	m_seedOverlayType = (imageSeed + (slotSeed >> 4) & 15) - (slotSeed >> 4);
    */
}


int ItemInfoManager::GetBaseItem(int itemID)
{
	if (!(m_itemInfo[itemID].m_itemInfoFlags & ITEM_INFO_FLAG_RANDOM_GROW))
	{
		return itemID;
	}

	int baseID = itemID % 2;

	if (itemID - 582 < 10)
	{
		baseID = baseID + 582;
	}
	else if (itemID - 616 < 4)
	{
		baseID = baseID + 616;
	}
	else if (itemID - 626 < 24)
	{
		baseID = baseID + 626;
	}
	else if (itemID - 742 < 8)
	{
		baseID = baseID + 742;
	}
	else if (itemID - 802 < 12)
	{
		baseID = baseID + 802;
	}
	else if ((itemID - 4308 < 12) || (itemID - 1258 < 14))
	{
		baseID = baseID + 1258;
	}
	else if (itemID - 2074 < 120)
	{
		baseID = baseID + 2074;
	}
	else if (itemID - 2194 < 10)
	{
		baseID = baseID + 2194;
	}
	else if (itemID - 2292 < 10)
	{
		baseID = baseID + 2292;
	}
	else if (itemID - 2308 < 10)
	{
		baseID = baseID + 2308;
	}
	else if (itemID - 2320 < 10)
	{
		baseID = baseID + 2320;
	}
	else if (itemID - 2332 < 10)
	{
		baseID = baseID + 2332;
	}
	else if (itemID - 2648 < 12)
	{
		baseID = baseID + 2648;
	}
	else if (itemID - 2660 < 12)
	{
		baseID = baseID + 2660;
	}
	else if (itemID - 2684 < 12)
	{
		baseID = baseID + 2684;
	}
	else if (itemID - 2672 < 12)
	{
		baseID = baseID + 2672;
	}
	else if (itemID - 2814 < 20)
	{
		baseID = baseID + 2814;
	}
	else if (itemID - 2834 < 20)
	{
		baseID = baseID + 2834;
	}
	else if (itemID - 3500 < 12)
	{
		baseID = baseID + 3500;
	}
	else if (itemID - 3478 < 16)
	{
		baseID = baseID + 3478;
	}
	else if (itemID - 4784 < 8)
	{
		baseID = baseID + 4784;
	}
	else
	{
		baseID = itemID;
	}

	return baseID;
}

int TimeToGrow(ItemInfo* pItemInfo)
{
	int time = 3600;
	int rarity = pItemInfo->m_rarity;

	if (rarity != 999)
	{
		time = (rarity * rarity + 30) * rarity;
	}

	return time;
}

void ItemInfoManager::CalculateRarityForAllItems()
{
	if (m_itemInfo.size() > 1)
	{
		for (int i = 1; i < m_itemInfo.size(); i += 2)
		{
			ItemInfo * pItemInfo = &m_itemInfo[i];
			ItemInfo * pBaseItem = NULL;

			if (pItemInfo->m_itemID < 0 || pItemInfo->m_itemID >= m_itemInfo.size())
			{
				//???? This is NOT allowed...
				pBaseItem = &m_itemInfo[i];
			}
			else
			{
				pBaseItem = &m_itemInfo[pItemInfo->m_itemID];

				if (pBaseItem == NULL)
				{
					pBaseItem = NULL;
				}
				else if (pBaseItem->m_itemInfoFlags & ITEM_INFO_FLAG_RANDOM_GROW)
				{
					int baseID = pItemInfo->m_itemID % 2;

					if ((pItemInfo->m_itemID - 582) < 10)
					{
						pBaseItem = &m_itemInfo[(baseID + 582)];
					}
					else if ((pItemInfo->m_itemID - 616) < 4)
					{
						pBaseItem = &m_itemInfo[(baseID + 616)];
					}
					else if ((pItemInfo->m_itemID - 626) < 24)
					{
						pBaseItem = &m_itemInfo[(baseID + 626)];
					}
					else if ((pItemInfo->m_itemID - 742) < 8)
					{
						pBaseItem = &m_itemInfo[(baseID + 742)];
					}
					else if ((pItemInfo->m_itemID - 802) < 12)
					{
						pBaseItem = &m_itemInfo[(baseID + 802)];
					}
					else if ((pItemInfo->m_itemID - 4308) < 12 || (pBaseItem->m_itemID - 1258 < 14))
					{
						pBaseItem = &m_itemInfo[(baseID + 1258)];
					}
					else if (pItemInfo->m_itemID - 2074 < 120)
					{
						pBaseItem = &m_itemInfo[(baseID + 2074)];
					}
					else if (pItemInfo->m_itemID - 2194 < 10)
					{
						pBaseItem = &m_itemInfo[(baseID + 2194)];
					}
					else if (pItemInfo->m_itemID - 2292 < 10)
					{
						pBaseItem = &m_itemInfo[(baseID + 2292)];
					}
					else if (pItemInfo->m_itemID - 2308 < 10)
					{
						pBaseItem = &m_itemInfo[(baseID + 2308)];
					}
					else if (pItemInfo->m_itemID - 2320 < 10)
					{
						pBaseItem = &m_itemInfo[(baseID + 2320)];
					}
					else if (pItemInfo->m_itemID - 2332 < 10)
					{
						pBaseItem = &m_itemInfo[(baseID + 2332)];
					}
					else if (pItemInfo->m_itemID - 2648 < 10)
					{
						pBaseItem = &m_itemInfo[(baseID + 2648)];
					}
					else if (pItemInfo->m_itemID - 2660 < 10)
					{
						pBaseItem = &m_itemInfo[(baseID + 2660)];
					}
					else if (pItemInfo->m_itemID - 2684 < 12)
					{
						pBaseItem = &m_itemInfo[(baseID + 2684)];
					}
					else if (pItemInfo->m_itemID - 2672 < 12)
					{
						pBaseItem = &m_itemInfo[(baseID + 2672)];
					}
					else if (pItemInfo->m_itemID - 2814 < 20)
					{
						pBaseItem = &m_itemInfo[(baseID + 2814)];
					}
					else if (pItemInfo->m_itemID - 2834 < 20)
					{
						pBaseItem = &m_itemInfo[(baseID + 2834)];
					}
					else if (pItemInfo->m_itemID - 3500 < 12)
					{
						pBaseItem = &m_itemInfo[(baseID + 3500)];
					}
					else if (pItemInfo->m_itemID - 3478 < 16)
					{
						pBaseItem = &m_itemInfo[(baseID + 3478)];
					}
					else if (pItemInfo->m_itemID - 4784 < 8)
					{
						pBaseItem = &m_itemInfo[(baseID + 4784)];
					}
				}
			}

			int rarity = pBaseItem->m_rarity;
			
			if (rarity == 0)
			{
				rarity = 1;
				if (pBaseItem->m_seedMix1 != 0)
				{
					int r1 = GetRarityForItem(&m_itemInfo[pBaseItem->m_seedMix1], 0);
					int r2 = GetRarityForItem(&m_itemInfo[pBaseItem->m_seedMix2], 0);
					
					rarity = 999;

					if (r1 + r2 < 1000)
					{
						rarity = r1 + r2;
					}
				}
			}

			pItemInfo->m_rarity = rarity;
			m_itemInfo[i - 1].m_rarity = rarity; // also set block's id

			if (pItemInfo->m_secondsToBloom == 0)
			{
				pItemInfo->m_secondsToBloom = TimeToGrow(pItemInfo);
			}

			if (pItemInfo->m_maxFruit == 0)
			{
				m_itemInfo[i].m_maxFruit = 5;
			}
		}
	}

	// TODO: build graphviz dot
}


uint32_t ItemInfoManager::GetRarityForItem(ItemInfo* pItemInfo, uint32_t unused)
{
	//* TODO: make this function safer with accessing the m_itemInfo vector

	if (pItemInfo == NULL)
	{
		return 1;
	}

	int baseID = pItemInfo->m_itemID;
	
	ItemInfo * pRarityItem = NULL;

	if (baseID < 0)
	{
		pRarityItem = &m_itemInfo[0];
	}

	if (baseID < m_itemInfo.size())
	{
		// use baseID at first, if necessary we also use the RANDOM_GROW definitions.
		pRarityItem = &m_itemInfo[baseID];

		if (pRarityItem == NULL)
		{
			// TODO: rgt sets the id to 0 and proceeds as if nothing happened, but it should result in 1 always anyway.
			assert(pRarityItem == NULL && "Wtf?");
			return 1;
		}

		if (pRarityItem->m_itemInfoFlags & ITEM_INFO_FLAG_RANDOM_GROW)
		{
			int evenID = baseID % 2;
			evenID = baseID % 2;
			if (baseID - 582 < 10)
			{
				pRarityItem = &m_itemInfo[(evenID + 582)];
			}
			else if (baseID - 616 < 4)
			{
				pRarityItem = &m_itemInfo[(evenID + 616)];
			}
			else if (baseID - 626 < 24)
			{
				pRarityItem = &m_itemInfo[(evenID + 626)];
			}
			else if (baseID - 742 < 8)
			{
				pRarityItem = &m_itemInfo[(evenID + 742)];
			}
			else if (baseID - 0x322U < 12)
			{
				pRarityItem = &m_itemInfo[(evenID + 802)];
			}
			else if ((baseID - 4308 < 12) || (baseID - 1258 < 14))
			{
				pRarityItem = &m_itemInfo[(evenID + 1258)];
			}
			else if (baseID - 2074 < 120)
			{
				pRarityItem = &m_itemInfo[(evenID + 2074)];
			}
			else if (baseID - 2194 < 10)
			{
				pRarityItem = &m_itemInfo[(evenID + 2194)];
			}
			else if (baseID - 2292 < 10)
			{
				pRarityItem = &m_itemInfo[(evenID + 2292)];
			}
			else if (baseID - 2308 < 10)
			{
				pRarityItem = &m_itemInfo[(evenID + 2308)];
			}
			else if (baseID - 2320 < 10)
			{
				pRarityItem = &m_itemInfo[(evenID + 2320)];
			}
			else if (baseID - 2332 < 10)
			{
				pRarityItem = &m_itemInfo[(evenID + 2332)];
			}
			else if (baseID - 2648 < 12)
			{
				pRarityItem = &m_itemInfo[(evenID + 2648)];
			}
			else if (baseID - 2660 < 12)
			{
				pRarityItem = &m_itemInfo[(evenID + 2660)];
			}
			else if (baseID - 2684 < 12)
			{
				pRarityItem = &m_itemInfo[(evenID + 2684)];
			}
			else if (baseID - 2672 < 12)
			{
				pRarityItem = &m_itemInfo[(evenID + 2672)];
			}
			else if (baseID - 2814 < 20)
			{
				pRarityItem = &m_itemInfo[(evenID + 2814)];
			}
			else if (baseID - 2834 < 20)
			{
				pRarityItem = &m_itemInfo[(evenID + 2834)];
			}
			else if (baseID - 3500 < 12)
			{
				pRarityItem = &m_itemInfo[(evenID + 3500)];
			}
			else if (baseID - 3478 < 16)
			{
				pRarityItem = &m_itemInfo[(evenID + 3478)];
			}
			else
			{
				if (baseID - 4784 < 8)
				{
					baseID = evenID + 4784;
				}
				pRarityItem = &m_itemInfo[baseID];
			}
		}
	}

	if (pRarityItem == NULL)
	{
		return 1;
	}

	int resultRarity = pRarityItem->m_rarity;
	if (pRarityItem->m_rarity == 0)
	{
		resultRarity = 1;

		if (pRarityItem->m_seedMix1 != 0)
		{
			ItemInfo * pMixItem1 = &m_itemInfo[GetBaseItem(pRarityItem->m_seedMix1)];
			
			resultRarity = pMixItem1->m_rarity;
			if (pMixItem1->m_rarity == 0)
			{
				resultRarity = 1;
				if (pMixItem1->m_seedMix1 != 0)
				{
					int r1 = GetRarityForItem(&m_itemInfo[pMixItem1->m_seedMix1], unused);
					int r2 = GetRarityForItem(&m_itemInfo[pMixItem1->m_seedMix2], unused);

					resultRarity = r1 + r2;
					if (resultRarity > 999)
					{
						resultRarity = 999;
					}

					pMixItem1->m_rarity = resultRarity;
				}
			}

			ItemInfo * pMixItem2 = &m_itemInfo[GetBaseItem(pRarityItem->m_seedMix2)];

			// we add this to the result that we just made (if we did)
			int secondaryResult = pMixItem2->m_rarity;

			if (pMixItem2->m_rarity == 0)
			{
				secondaryResult = 1;


				// dont increment to this?
				if (pMixItem2->m_seedMix1 != 0)
				{
					int r1 = GetRarityForItem(&m_itemInfo[pMixItem2->m_seedMix1], unused);
					int r2 = GetRarityForItem(&m_itemInfo[pMixItem2->m_seedMix2], unused);

					secondaryResult = r1 + r2;
					if (secondaryResult > 999)
					{
						secondaryResult = 999;
					}

					pMixItem2->m_rarity = secondaryResult;
				}
			}

			secondaryResult = secondaryResult + resultRarity;
			if (secondaryResult > 999)
			{
				secondaryResult = 999;
			}

			return secondaryResult;
		}
	}

	// fallback
	return resultRarity;
}


void ItemInfoManager::SetupFileHashes(bool bSetupOgg, bool bUseBetaHashes)
{
	int amount = 0;

	TextScanner setup("file_hashes.txt");
	setup.LoadFile("file_hashes.txt");
	if (!setup.IsLoaded())
	{
		::printf("Can't find file_hashes.txt to load!\n");
		return;
	}

	std::map<std::string, uint32_t> foundHashes = {};

	for (int lineNum = 0; lineNum < setup.m_lines.size(); lineNum++)
	{
		if (setup.GetLine(lineNum).empty())
		{
			continue;
		}

		std::string fileName = setup.GetParmStringFromLine(lineNum, 0);
		foundHashes[fileName] = StringToUInt32(setup.GetParmStringFromLine(lineNum, 1));
	}

	for (auto& item : m_itemInfo)
	{
		uint32_t finalHash = 0;

		if (bUseBetaHashes)
		{
			std::string nameToFind = "game/" + item.m_fileName;
			
			if (GetFileExtension(nameToFind) == "rttex")
			{
				StringReplace(".rttex", "_beta.rttex", nameToFind);
			}

			auto foundBetaHash = foundHashes.find(nameToFind);
			if (foundBetaHash != foundHashes.end())
			{
				finalHash = foundBetaHash->second;
				StringReplace(".rttex", "_beta.rttex", item.m_fileName);
			}
		}

		std::string fileName = "game/" + item.m_fileName;

		if (finalHash == 0)
		{
			auto foundHash = foundHashes.find(fileName);
			if (foundHash != foundHashes.end())
			{
				finalHash = foundHash->second;
			}
		}
		
		if (item.m_fileHash == 0)
		{
			item.m_fileHash = finalHash;
		}
		
		if (item.m_fileHash == 0)
		{
			::printf("Warning: No hash found for item %d\n", item.m_itemID);
		}

		if (!item.m_extraFileName.empty())
		{
			if (bSetupOgg)
			{
				StringReplace("mp3", "ogg", item.m_extraFileName);
			}

			uint32_t finalExtraHash = 0;

			if (bUseBetaHashes)
			{
				std::string nameToFind2 = "game/" + item.m_extraFileName;

				if (GetFileExtension(nameToFind2) == "rttex")
				{
					StringReplace(".rttex", "_beta.rttex", nameToFind2);
				}

				auto foundBetaHash2 = foundHashes.find(nameToFind2);
				if (foundBetaHash2 != foundHashes.end())
				{
					finalExtraHash = foundBetaHash2->second;
					StringReplace(".rttex", "_beta.rttex", item.m_extraFileName);
				}
			}

			std::string extraFileName = item.m_extraFileName;

			if (finalExtraHash == 0)
			{
				auto foundHash2 = foundHashes.find(extraFileName);
				if (foundHash2 != foundHashes.end())
				{
					finalExtraHash = foundHash2->second;
				}
			}

			if (item.m_extraFileHash == 0)
			{
				item.m_extraFileHash = finalExtraHash;
			}

			if (item.m_extraFileHash == 0)
			{
				::printf("Warning: No hash found for %s on item %d.  can probably ignore if it's just the ogg versions for Android...\n", item.m_extraFileName.c_str(), item.m_itemID);
			}
		}
	}
}


void ItemInfo::Serialize(uint8_t* pBuffer, int& offset, bool bWrite, uint16_t version, bool bClientData)
{
	// Actually, these two should be in separate ifs() but no point as we call MemorySerialize rather than write manually to a buffer offset.
	MemorySerialize(m_itemID, pBuffer, offset, bWrite);
	MemorySerialize(m_itemInfoFlags, pBuffer, offset, bWrite);
	
	uint8_t type = 0;
	
	if (bWrite)
	{
		// Copy it to an uint8, so it represents a singular byte
		type = (uint8_t)m_type;

		MemorySerialize(type, pBuffer, offset, bWrite);
	}
	else
	{	
		MemorySerialize(type, pBuffer, offset, bWrite);
	}

	// apply the (possibly) read type to the type. It's also safe if we were writing it, just gonna apply the old one.
	m_type = type;
	uint8 materialType = 0;

	if (bWrite)
	{
		materialType = m_materialType;
	}

	MemorySerialize(materialType, pBuffer, offset, bWrite);

	m_materialType = (eItemMaterial)materialType;

	if (version < 3)
	{
		MemorySerialize(m_name, pBuffer, offset, bWrite);
	}
	else
	{
		MemorySerializeStringEncrypted(m_name, pBuffer, offset, bWrite, m_itemID, "PBG892FXX982ABC*");
	}

	MemorySerialize(m_fileName, pBuffer, offset, bWrite);
	MemorySerialize(m_fileHash, pBuffer, offset, bWrite);
	
	uint8_t visualType = 0;
	uint8_t storageType = 0;
	uint8_t collisionType = 0;
	uint8_t bodyPart = 0;

	if (bWrite)
	{
		visualType = m_visualType;
		MemorySerialize(visualType, pBuffer, offset, bWrite);
		
		MemorySerialize(m_cookTime, pBuffer, offset, bWrite);
		MemorySerialize(m_frameX, pBuffer, offset, bWrite);
		MemorySerialize(m_frameY, pBuffer, offset, bWrite);
		
		storageType = m_storageType;
		MemorySerialize(storageType, pBuffer, offset, bWrite);

		MemorySerialize(m_layer, pBuffer, offset, bWrite);
		
		collisionType = m_collisionType;
		MemorySerialize(collisionType, pBuffer, offset, bWrite);
		MemorySerialize(m_hp, pBuffer, offset, bWrite);
		MemorySerialize(m_secondsToHeal, pBuffer, offset, bWrite);

		bodyPart = m_bodyPart;
		MemorySerialize(bodyPart, pBuffer, offset, bWrite);
		
		MemorySerialize(m_rarity, pBuffer, offset, bWrite);
		MemorySerialize(m_maxCanHold, pBuffer, offset, bWrite);
		MemorySerialize(m_extraFileName, pBuffer, offset, bWrite);
		MemorySerialize(m_extraFileHash, pBuffer, offset, bWrite);

		MemorySerialize(m_animMS, pBuffer, offset, bWrite);
	}
	else
	{
		MemorySerialize(visualType, pBuffer, offset, bWrite);
		MemorySerialize(m_cookTime, pBuffer, offset, bWrite);
		MemorySerialize(m_frameX, pBuffer, offset, bWrite);
		MemorySerialize(m_frameY, pBuffer, offset, bWrite);

		MemorySerialize(storageType, pBuffer, offset, bWrite);
		MemorySerialize(m_layer, pBuffer, offset, bWrite);
		MemorySerialize(collisionType, pBuffer, offset, bWrite);
		MemorySerialize(m_hp, pBuffer, offset, bWrite);
		MemorySerialize(m_secondsToHeal, pBuffer, offset, bWrite);
		MemorySerialize(bodyPart, pBuffer, offset, bWrite);

		MemorySerialize(m_rarity, pBuffer, offset, bWrite);
		MemorySerialize(m_maxCanHold, pBuffer, offset, bWrite);
		MemorySerialize(m_extraFileName, pBuffer, offset, bWrite);
		MemorySerialize(m_extraFileHash, pBuffer, offset, bWrite);

		MemorySerialize(m_animMS, pBuffer, offset, bWrite);
	}

	m_visualType = (eTileVisualEffect)visualType;
	m_storageType = (eItemImageStorage)storageType;
	m_collisionType = (eTileCollisionType)collisionType;
	m_bodyPart = (eBodyParts)bodyPart;

	if (version > 3)
	{
		MemorySerialize(m_petName, pBuffer, offset, bWrite);
		MemorySerialize(m_petPrefix, pBuffer, offset, bWrite);
		MemorySerialize(m_petSuffix, pBuffer, offset, bWrite);
		
		if (version != 4)
		{
			MemorySerialize(m_petAbility, pBuffer, offset, bWrite);
		}
	}

	MemorySerialize(m_seedBaseType, pBuffer, offset, bWrite);
	MemorySerialize(m_seedOverlayType, pBuffer, offset, bWrite);
	MemorySerialize(m_treeBaseType, pBuffer, offset, bWrite);
	MemorySerialize(m_treeOverlayType, pBuffer, offset, bWrite);

	MemorySerialize(m_treeBgColor, pBuffer, offset, bWrite);
	MemorySerialize(m_treeFgColor, pBuffer, offset, bWrite);

	// TODO: add server side information properly.
	// I won't focus on this right now since i'm not even on ServerClient as of 8/18/2025
	if (!bClientData)
	{
		MemorySerialize(m_seedMix1, pBuffer, offset, bWrite);
		MemorySerialize(m_seedMix2, pBuffer, offset, bWrite);
		MemorySerialize(m_growMultiplier, pBuffer, offset, bWrite); // TODO: find if its uint8
		MemorySerialize(m_maxFruit, pBuffer, offset, bWrite);
		MemorySerialize(m_serverFlags, pBuffer, offset, bWrite);
	
		MemorySerialize(m_playModID, pBuffer, offset, bWrite);
		MemorySerialize(m_description, pBuffer, offset, bWrite);
		MemorySerialize(m_bloomSecondsToGiveOrTake, pBuffer, offset, bWrite);

		// writes goodie data here but idk what it looks like yet since haven't reversed. Not even important now, though.
	}
	else
	{	
		// I have no idea why the server does this, I guess this was meant to represent something at first but seth just said no.
		// (Also, yes, this is done by the official program too, not a skill issue from my end)
		uint16 padding = 0;
		MemorySerialize(padding, pBuffer, offset, bWrite);
		MemorySerialize(padding, pBuffer, offset, bWrite);
	}

	MemorySerialize(m_secondsToBloom, pBuffer, offset, bWrite);

	if (version > 6)
	{
		MemorySerialize(m_animationFlags, pBuffer, offset, bWrite);
		MemorySerialize(m_animationFrames, pBuffer, offset, bWrite);
		
		if (version != 7)
		{
			MemorySerialize(m_animationFile, pBuffer, offset, bWrite);
			MemorySerialize(m_animationFramesV2, pBuffer, offset, bWrite);
			
			MemorySerialize(m_dualLayerX, pBuffer, offset, bWrite);
			MemorySerialize(m_dualLayerY, pBuffer, offset, bWrite);
		}
	}

	m_checkSum = (uint32)m_itemInfoFlags + m_materialType + g_checksumBase + m_collisionType + m_itemID + (int)m_layer + m_type * 2;
}


uint8* ItemInfoManager::SaveToMem(int& offset, uint16 version, bool bUseClientData)
{
	uint8 * pBuffer = (uint8*)std::malloc(m_itemInfo.size() * sizeof(ItemInfo));

	uint32 itemCount = (uint32)m_itemInfo.size();

	MemorySerialize(version, pBuffer, offset, true);
	MemorySerialize(itemCount, pBuffer, offset, true);

	for (auto& item : m_itemInfo)
	{
		item.Serialize(pBuffer, offset, true, version, bUseClientData);
	}

	return pBuffer;
}

ItemInfo* ItemInfoManager::GetItemByIDSafe(int itemID)
{
	if (itemID >= m_itemInfo.size() || m_itemInfo.empty())
	{
		return NULL;
	}

	return &m_itemInfo[itemID];
}

ItemInfo* ItemInfoManager::GetItemByNameSafe(const std::string& name)
{
	for (auto& item : m_itemInfo)
	{
		if (ToLowercase(item.m_name) == ToLowercase(name))
		{
			return &item;
		}
	}

	return nullptr;
}

bool ItemInfoManager::LoadFromMem(uint8* pBuffer, bool bUseClientData)
{
	uint32 itemCount = 0;
	uint16 itemVersion = 0;

	int offset = 0;

	MemorySerialize(itemVersion, pBuffer, offset, false);
	MemorySerialize(itemCount, pBuffer, offset, false);

	m_itemInfo.resize(itemCount);

	for (int i = 0; i < itemCount; i++)
	{
		m_itemInfo[i].Serialize(pBuffer, offset, false, itemVersion, bUseClientData);
	}

	return true;
}

bool IfTargetExistsInUpdateList(const std::string& fileName, const std::vector<FileUpdate>& fileUpdates)
{
	for (auto& fileUpdate : fileUpdates)
	{
		if (fileUpdate.fileName == fileName)
		{
			return true;
		}
	}

	return false;
}

void ItemInfo::CheckItemForUpdates(std::vector<FileUpdate>& fileUpdates) const
{
	//std::string fileName = 
#ifdef RT_CLIENT
	if (!m_fileName.empty())
	{
		std::string fileName = GetApp()->GetSmartFileName("game/" + m_fileName);
		
		if (!IfTargetExistsInUpdateList(fileName, fileUpdates))
		{
			FileUpdate fileUpdate{};
			fileUpdate.bNeedsUpdating = m_fileHash != GetHashOfFile(fileName, false);
			fileUpdate.fileName = fileName;
			fileUpdate.rawName = "game/"+m_fileName;

			fileUpdates.push_back(fileUpdate);
		}
	}

	if (!m_extraFileName.empty())
	{
		std::string extraFileName = GetApp()->GetSmartFileName(m_extraFileName);

		if (IfTargetExistsInUpdateList(extraFileName, fileUpdates))
		{
			FileUpdate fileUpdate{};
			fileUpdate.bNeedsUpdating = m_fileHash != GetHashOfFile(extraFileName, false);
			fileUpdate.fileName = extraFileName;
			fileUpdate.rawName = m_extraFileName;

			fileUpdates.push_back(fileUpdate);
		}
	}
#endif // RT_CLIENT
}
