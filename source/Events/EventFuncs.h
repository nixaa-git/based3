#pragma once

#include "EventContext.h"

// holds all decls for our cpp file events

namespace event
{
    /****Generic Text****/
    void requestedName(EVENT_HANDLER_ARGS);
    void refresh_item_data(EVENT_HANDLER_ARGS);
    void enter_game(EVENT_HANDLER_ARGS);
    void input(EVENT_HANDLER_ARGS);
    
    /****Game Message****/
    void join_request(EVENT_HANDLER_ARGS);
    void quit_to_exit(EVENT_HANDLER_ARGS);
    
    /****Game Update****/
    void gp_state(EVENT_HANDLER_ARGS);
    void gp_tilechangerequest(EVENT_HANDLER_ARGS);
}