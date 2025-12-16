#include "Terraformer.h"
#include "World.h"
#include "../Manager/ItemDB.h"
#include <algorithm>
#include <random>

void Terraformer::MakeDefault()
{
    if (!m_pWorld)
    {
        ::printf("Terraformer::MakeDefault() Failed since m_pWorld is nullptr!!!\n");
        return;
    }

    WorldTileMap& tilemap = m_pWorld->GetWorldTileMap();
    auto& tiles = tilemap.GetTiles();

    tiles.reserve(tilemap.GetSize().x * tilemap.GetSize().y);

    for (int i = 0; i < (tilemap.GetSize().x * tilemap.GetSize().y); i++)
    {
        int x = i % tilemap.GetSize().x;
        int y = i / tilemap.GetSize().x;

        Tile tile{};
        tile.m_index = i;
        tile.m_fg = 0;

        tiles.push_back(tile);
    }

    m_pWorld->SetWeatherID(static_cast<uint32_t>(eWeatherID::SUNNY)) ;
    
    // dirt layer
    tilemap.FillRect({0, 24}, {100, 53}, ITEM_ID_DIRT, ITEM_ID_CAVE_BACKGROUND);

    // bedrock layer
    tilemap.FillRect({0, 53}, {100, 60}, ITEM_ID_BEDROCK, ITEM_ID_CAVE_BACKGROUND);

    // rock
    tilemap.FillRectRandom({1, 25}, {100, 53}, 100, ITEM_ID_ROCK, ITEM_ID_CAVE_BACKGROUND);

    // lava
    tilemap.FillRectRandom({1, 49}, {100, 53}, 160, ITEM_ID_LAVA, ITEM_ID_CAVE_BACKGROUND);

    // pick tile for the main door
    CL_Vec2i mainDoorPos = {RandomRange(1, 99), 23};
    Tile* pMainDoorTile = tilemap.GetTileAtPos(mainDoorPos.x, mainDoorPos.y);
    if (pMainDoorTile)
    {
        tilemap.SetMainDoorPos(mainDoorPos);
        pMainDoorTile->SetFG(ITEM_ID_MAIN_DOOR, true);
        Tile* pTileBelow = tilemap.GetTileAtPos(mainDoorPos.x, mainDoorPos.y + 1);
        if (pTileBelow)
        {
            pTileBelow->m_fg = ITEM_ID_BEDROCK;
        }
    }
}

void Terraformer::MakeBeach()
{
    if (!m_pWorld)
        return;

    WorldTileMap& map = m_pWorld->GetWorldTileMap();
    auto& tiles = map.GetTiles();
    const int mapWidth  = 100;
    const int mapHeight = 60;

    tiles.clear();
    tiles.resize(mapWidth * mapHeight);

    for (int y = 0; y < mapHeight; ++y)
    {
        for (int x = 0; x < mapWidth; ++x)
        {
            int idx = y * mapWidth + x;
            tiles[idx].m_index = idx;
            tiles[idx].m_fg = 0;
            tiles[idx].m_bg = 0;
            tiles[idx].m_flags = 0;
        }
    }

    // determine when we start the slope and then do the range thing from that value 
    int startDescent = RandomRange(16, 26);

    CL_Vec2i mainDoorPos = {RandomRange(0, 9), 29};
    map.SetMainDoorPos(mainDoorPos);

    m_pWorld->SetWeatherID(static_cast<uint32_t>(eWeatherID::SUNSET));

    map.FillRect({0, 30}, {100, 55}, ITEM_ID_SAND, ITEM_ID_OCEAN_ROCK);
    map.FillRect({0, 30}, {startDescent - 1, 30}, ITEM_ID_SAND, ITEM_ID_OCEAN_ROCK); // individual layer for the very top
    map.FillRect({0, 56}, {100, 60}, ITEM_ID_BEDROCK, ITEM_ID_OCEAN_ROCK);

    map.FillRectRandom({1, 31}, {100, 55}, 18, ITEM_ID_ROCK, ITEM_ID_OCEAN_ROCK);

    // now set main door tile values after finished filling rects.
    Tile* pMainDoor = map.GetTileAtPos(mainDoorPos.x, mainDoorPos.y);
    if (pMainDoor)
    {
        pMainDoor->SetFG(ITEM_ID_MAIN_DOOR, true);
        pMainDoor->m_bg = ITEM_ID_OCEAN_ROCK;
        Tile* pTileBelow = map.GetTileAtPos(mainDoorPos.x, mainDoorPos.y + 1);
        if (pTileBelow)
        {
            pTileBelow->m_fg = ITEM_ID_BEDROCK;
            pTileBelow->m_bg = ITEM_ID_OCEAN_ROCK;
        }
    }
    
    int goingDown = 0;
    const int maxWeBeGoingDown = RandomRange(15, 20);

    int moveX = 1;
    while (goingDown < maxWeBeGoingDown)
    {
        int roll1 = RandomRange(1, 11);
        if (roll1 >= 3)
        {
            Tile* pTile = map.GetTileAtPos(startDescent + moveX, 30 + goingDown);
            if (pTile)
            {
                pTile->m_fg = ITEM_ID_SAND;
                pTile->m_bg = ITEM_ID_OCEAN_ROCK;
            }
        }
        else
        {
            map.FillRect({ startDescent + moveX, 30 + goingDown }, { 100, 30 + goingDown }, ITEM_ID_BLANK, ITEM_ID_OCEAN_ROCK, 0x400u);   
            ++goingDown;
        }

        moveX++;
    }

    // place random coral and seaweed
    const int maxAttempts2 = 1000;
    const int maxNeededToPass = RandomRange(34, 52);
    int successfulAttempts2 = 0;
    int amountSeaweed = 0;
    for (int attempts = 0; attempts < maxAttempts2; attempts++)
    {
        if (successfulAttempts2 >= maxNeededToPass)
            break; // enough!

        CL_Vec2i randomSpot = { RandomRange(1, 99), RandomRange(34, 53) };
        Tile* pTilePicked = map.GetTileAtPos(randomSpot.x, randomSpot.y);
        if (pTilePicked)
        {
            Tile* pTileBelow = map.GetTileAtPos(randomSpot.x, randomSpot.y + 1);
            if (pTileBelow && 
                (pTilePicked->m_fg == ITEM_ID_BLANK || pTilePicked->m_fg == ITEM_ID_CORAL) && 
                pTilePicked->m_flags == 0x400u)
            {
                if (pTileBelow->m_fg != ITEM_ID_BLANK)
                {
                    int roll2 = RandomRange(1, 16);
                    if (roll2 > 6)
                    {
                        if (amountSeaweed > 14)
                            continue;
                        pTilePicked->m_fg = ITEM_ID_SEAWEED;
                        amountSeaweed++;
                    }
                    else
                    {
                        pTilePicked->m_fg = ITEM_ID_CORAL;
                        int direction = RandomRange(0, 2);
                        CL_Vec2i adjacentPos = randomSpot;

                        switch (direction)
                        {
                            case 0: adjacentPos.x -= 1; break; // left
                            case 1: adjacentPos.x += 1; break; // right
                            case 2: adjacentPos.y -= 1; break; // above
                        }

                        Tile* pAdjacentTile = map.GetTileAtPos(adjacentPos.x, adjacentPos.y);
                        if (pAdjacentTile && pAdjacentTile->m_fg == ITEM_ID_BLANK)
                        {
                            pAdjacentTile->m_fg = ITEM_ID_CORAL;
                        }
                    }

                    successfulAttempts2++;
                }
            }
        }
    }


    //now thats finished move onto placing treasure chests

    const int maxAttempts = 100;
    int successfulAttempts = 0;
    for (int attempts = 0; attempts < maxAttempts; attempts++)
    {
        if (successfulAttempts >= 3)
            break; // enough !

        CL_Vec2i randomSpot = { RandomRange(1, 99), RandomRange(34, 53) };
        Tile* pTilePicked = map.GetTileAtPos(randomSpot.x, randomSpot.y);
        if (pTilePicked)
        {
            if (pTilePicked->m_fg == ITEM_ID_SAND && pTilePicked->m_flags != 0x400u)
            {
                pTilePicked->m_fg = ITEM_ID_TREASURE_CHEST;
                // todo roll Summer Item and put object there !
                // make sure obj is centered, ie pos.x + 16, pos.y + 16
                successfulAttempts++;
            }
        }
    }
}

void Terraformer::MakeMars()
{
    if (!m_pWorld)
        return;

    WorldTileMap& map = m_pWorld->GetWorldTileMap();
    auto& tiles = map.GetTiles();
    const int mapWidth  = 100;
    const int mapHeight = 60;

    tiles.clear();
    tiles.resize(mapWidth * mapHeight);
    for (int y = 0; y < mapHeight; ++y)
    {
        for (int x = 0; x < mapWidth; ++x)
        {
            int idx = y * mapWidth + x;
            tiles[idx].m_index = idx;
            tiles[idx].m_fg = 0;
            tiles[idx].m_bg = 0;
            tiles[idx].m_flags = 0;
        }
    }

    // todo set main door randomly on the perlin noise hill
    map.SetMainDoorPos({50, 1});

    m_pWorld->SetWeatherID(static_cast<uint32_t>(eWeatherID::MARS));

    // soil
    map.FillRect({0, 24}, {100, 53}, ITEM_ID_MARTIAN_SOIL, ITEM_ID_CAVE_BACKGROUND);

    // bedrock layer
    map.FillRect({0, 53}, {100, 60}, ITEM_ID_BEDROCK, ITEM_ID_CAVE_BACKGROUND);

    // rock
    map.FillRectRandom({1, 22}, {100, 53}, 100, ITEM_ID_MARS_ROCK, ITEM_ID_CAVE_BACKGROUND);

    // ice
    map.FillRectRandom({1, 49}, {100, 53}, 30, ITEM_ID_ICE, ITEM_ID_CAVE_BACKGROUND);

    // perlin noise hills shit
    int baseY = 23;
    const int maxOffset = 4;

    std::mt19937 rng(12345);
    std::uniform_real_distribution<float> dist(0.f, 1.f);

    int prevTopY = baseY;

    for (int x = 0; x < mapWidth; ++x)
    {
        float n = dist(rng) * maxOffset;
        int topY = baseY - static_cast<int>(roundf(n));

        // prevent gaps bigger than 1 block
        if (topY < prevTopY - 1)
            topY = prevTopY - 1;
        if (topY > prevTopY + 1)
            topY = prevTopY + 1;

        prevTopY = topY;

        for (int y = topY; y <= baseY; ++y)
        {
            if (Tile* t = map.GetTileAtPos(x, y))
                t->m_fg = ITEM_ID_MARTIAN_SOIL;
        }

        // 15% chance to place a tree above top soil
        if (dist(rng) < 0.15f)
        {
            if (Tile* tAbove = map.GetTileAtPos(x, topY - 1))
                tAbove->m_fg = ITEM_ID_MARTIAN_TREE;
        }
    }
}
