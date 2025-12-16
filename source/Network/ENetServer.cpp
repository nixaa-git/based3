#include "ENetServer.h"
#include "../Data/GameClient.h"
#include "../Data/PacketUtils.h"
#include "../CoreApp.h"

void ENetServer::Start(int port)
{
    enet_initialize();

    ENetAddress address{};
    address.host = ENET_HOST_ANY;
    address.port = port;
    m_pENetHost = enet_host_create(&address, 250, 1, 0, 0);
    m_pENetHost->checksum = enet_crc32;
    enet_host_compress_with_range_coder(m_pENetHost);

    if (!m_pENetHost)
    {
        ::printf("ENetServer::Start() : Fatal error. m_pENetHost is nullptr\n");
        return;
    }

    m_bServiceRunning = true;
    this->HostService();
}

void ENetServer::HostService()
{
    ::printf("enet listening on port %d\n", m_pENetHost->address.port);
    while (m_bServiceRunning)
    {
        ENetEvent event{};
        while (enet_host_service(m_pENetHost, &event, 5) > 0)
        {
            switch (event.type)
            {
                case ENET_EVENT_TYPE_CONNECT:
                {
                    ::printf("ENetServer got connection!\n");
                    GameClient* pClient = new GameClient(event.peer);
                    event.peer->data = (GameClient*)pClient;
                    pClient->SendHelloPacket();
                } break;
                case ENET_EVENT_TYPE_DISCONNECT:
                {
                    ::printf("ENetServer got disconnection!\n");

                    GameClient* pClient = ((GameClient*)event.peer->data);
                    if (!pClient) continue;

                    g_pApp->GetAccountManager()->SaveProfile(pClient);
                } break;
                case ENET_EVENT_TYPE_RECEIVE:
                {
                    GameClient* pClient = ((GameClient*)event.peer->data);
                    if (!pClient) continue;

                    const char* textPtr = GetTextPointerFromPacket(event.packet);
                    int msgType = GetMessageTypeFromPacket(event.packet);
                    GameUpdatePacket* gamePkt = GetStructPointerFromPacket(event.packet);

                    EventContext ctx = EventContext(pClient, msgType, msgType != 4 ? std::string(textPtr) : "", msgType == 4 ? gamePkt : nullptr);
                    g_pApp->GetEventManager()->HandlePacket(ctx);

                    if (msgType == 2 || msgType == 3)
                    {
                        ::printf("\ngeneric packet data:\n%s\n\n", GetTextPointerFromPacket(event.packet));
                    }
                } break;
                default: break;
            }
        }
    }

    enet_deinitialize();
}