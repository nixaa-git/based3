#pragma once

#include <unordered_map>
#include <functional>
#include "../Events/EventContext.h"

#define CMD_ARGS EventContext& ctx

using CommandHandler_t = std::unordered_map<std::string, std::function<void(CMD_ARGS)>>;

class CommandHandler
{
public:
    void Init();
    void RegisterCommand(const std::string& cmd, std::function<void(CMD_ARGS)> handler);
    void CallHandler(const std::string& cmd, EventContext& ctx);

    //util
    static std::vector<std::string> FetchArguments(const std::string& txt);

private:
    CommandHandler_t m_handlers;
};