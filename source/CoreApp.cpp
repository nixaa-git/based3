#include "CoreApp.h"

void CoreApp::Init()
{
    // todo.
    m_pENetServer = new ENetServer();
    m_pEventManager = new EventManager();
    m_pItemInfoManager = new ItemInfoManager();
}

void CoreApp::Main()
{
    if (!m_pENetServer)
    {
        return;
    }

    m_pEventManager->Init();
    this->InitItemData();

    // begin service loop
    m_pENetServer->Start();
}

void CoreApp::InitItemData()
{
    TextScanner scan(std::string("item_definitions.txt"));
    //scan.SetupFromMemoryAddress(scan.GetAllRaw().c_str());

    ::printf("Items.dat is %d bytes (as text), converted to %d lines.\n", scan.GetAllRaw().size(), scan.m_lines.size());

    m_pItemInfoManager->Load(scan);

    if (m_pItemInfoManager->m_itemInfo.size() <= 4999)
    {
        ::printf("Item count too low, aborting before tons of data is removed from maps!\n");
        return;
    }

    ::printf("Initing file hashes...\n");
    m_pItemInfoManager->SetupFileHashes(true, false);

    int offset = 0;
    m_pItemInfoBuffer = m_pItemInfoManager->SaveToMem(offset, RT_ITEM_INFO_VERSION, true);

    m_itemInfoBufferSize = 6 + sizeof(ItemInfo) * m_pItemInfoManager->m_itemInfo.size();
}

ENetServer* CoreApp::GetENetServer()
{
    return m_pENetServer;
}

EventManager* CoreApp::GetEventManager()
{
    return m_pEventManager;
}

ItemInfoManager* CoreApp::GetItemInfoManager()
{
    return m_pItemInfoManager;
}

uint8_t* CoreApp::GetItemInfoBuffer()
{
    return m_pItemInfoBuffer;
}

uint32_t CoreApp::GetItemInfoBufferSize()
{
    return m_itemInfoBufferSize;
}