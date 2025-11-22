#pragma once

#include <iostream>
#include <enet/include/enet.h>

class ENetServer
{
public:
    ENetServer() = default;
    ~ENetServer() = default;

    void Start(int port = 16999);
    void HostService();

private:
    ENetHost* m_pENetHost = NULL;
    bool m_bServiceRunning = false;
};