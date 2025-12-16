#include "CommandHandler.h"
#include "Commands.h"
#include <format>

void CommandHandler::Init()
{
    this->RegisterCommand("give", cmd::give);
}

void CommandHandler::RegisterCommand(const std::string& cmd, std::function<void(CMD_ARGS)> handler)
{
    auto it = m_handlers.find(cmd);

    if (it != m_handlers.end())
    {
        return;
    }

    m_handlers.insert_or_assign(cmd, handler);
}

void CommandHandler::CallHandler(const std::string& cmd, EventContext& ctx)
{
    if (!ctx.m_pClient)
    {
        return;
    }

    ctx.m_pClient->SendPacket(3, std::format("action|log\nmsg|`6{}``", ctx.m_packetText));

    auto it = m_handlers.find(cmd);

    if (it == m_handlers.end())
    {
        ctx.m_pClient->SendPacket(3, "action|log\nmsg|`4Unknown command.``  Enter `$/?`` for a list of valid commands.");
        return;
    }
    
    it->second(ctx);
}

std::vector<std::string> CommandHandler::FetchArguments(const std::string& cmd)
{
    if (cmd.empty())
    {
        return {};
    }

    return StringTokenize(cmd, " ");
}