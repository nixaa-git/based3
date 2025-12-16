#include "CoreApp.h"
#include <filesystem>
#include <system_error>

void CoreApp::Init()
{
    // todo.
    m_pENetServer = new ENetServer();
    m_pEventManager = new EventManager();
    m_pCommandHandler = new CommandHandler();
    m_pItemInfoManager = new ItemInfoManager();
    m_pWorldManager = new WorldManager();
    m_pAccountManager = new AccountManager();
    m_pWorldDBManager = new WorldDBManager();

    m_pSQLManager = GetSQLManager();
}

bool DoesDirExist(const std::string& dir)
{
    namespace fs = std::filesystem;

    if (fs::exists(dir) && fs::is_directory(dir))
    {
        return true;
    }

    return false;
}

void CoreApp::CreateDirsIfNeeded()
{
    namespace fs = std::filesystem;

    static std::vector<std::string> dirsToCreate = {
        "maps",
    };

    for (const auto& dir : dirsToCreate)
    {
        if (!DoesDirExist(dir))
        {
            std::error_code ec;
            if (std::filesystem::create_directories(dir, ec))
            {
                ::printf("Created directory: %s\n", dir.c_str());
            }
            else
            {
                ::printf("Failed to create directory: %s, error: %s\n", dir.c_str(), ec.message().c_str());
            }
        }
    }
}

void CoreApp::Main()
{
    if (!m_pENetServer)
    {
        return;
    }

    this->CreateDirsIfNeeded();

    m_pAccountManager->Init();
    m_pWorldDBManager->Init(); 
    m_pEventManager->Init();
    m_pCommandHandler->Init();
    this->InitItemData();


    // begin service loop
    m_pENetServer->Start();
}

void CoreApp::InitItemData()
{
    TextScanner scan(std::string("item_definitions.txt"));

    ::printf("Items.dat is %zu bytes (as text), converted to %zu lines.\n", scan.GetAllRaw().size(), scan.m_lines.size());

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

    m_itemInfoBufferSize = offset;

    m_itemInfoHash = HashString((const char*)m_pItemInfoBuffer, m_itemInfoBufferSize);

    ::printf("m_itemInfoBufferSize offset is %d\n", m_itemInfoBufferSize);
}

ENetServer* CoreApp::GetENetServer()
{
    return m_pENetServer;
}

EventManager* CoreApp::GetEventManager()
{
    return m_pEventManager;
}

CommandHandler* CoreApp::GetCommandHandler()
{
    return m_pCommandHandler;
}

MySQLManager* CoreApp::GetSQLManager()
{
    return m_pSQLManager;
}

AccountManager* CoreApp::GetAccountManager()
{
    return m_pAccountManager;
}

WorldDBManager* CoreApp::GetWorldDBManager()
{
    return m_pWorldDBManager;
}

ItemInfoManager* CoreApp::GetItemInfoManager()
{
    return m_pItemInfoManager;
}

WorldManager* CoreApp::GetWorldManager()
{
    return m_pWorldManager;
}

uint8_t* CoreApp::GetItemInfoBuffer()
{
    return m_pItemInfoBuffer;
}

uint32_t CoreApp::GetItemInfoBufferSize()
{
    return m_itemInfoBufferSize;
}

uint32_t CoreApp::GetItemInfoHash()
{
    return m_itemInfoHash;
}