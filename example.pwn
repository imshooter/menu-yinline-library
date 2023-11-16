/**
 * NOTE: The menu is not destroyed anywhere.
 */

#include <open.mp>
#include <YSI_Visual\y_commands>

#include "menu-yinline"

main(){}

YCMD:test1(playerid, params[], help) {
    new
        Menu:m = CreateMenu("YSI Inline Menu", 1, 29.0, 145.0, 186.0, 186.0)
    ;

    AddMenuItem(m, 0, "Item-0");
    AddMenuItem(m, 0, "Item-1");
    AddMenuItem(m, 0, "Item-2");

    inline const Response(response, row) {
        if (!response) {
            @return SendClientMessage(playerid, -1, "* You closed the menu.");
        }

        SendClientMessage(playerid, -1, "* Row %i selected.", row);
    }

    Menu_ShowCallback(playerid, m, using inline Response);
    
    return 1;
}

YCMD:test2(playerid, params[], help) {
    new
        Menu:m = CreateMenu("YSI Inline Menu", 1, 29.0, 145.0, 186.0, 186.0)
    ;

    AddMenuItem(m, 0, "Item-0");
    AddMenuItem(m, 0, "Item-1");
    AddMenuItem(m, 0, "Item-2");

    Menu_ShowCallback(playerid, m, using public SelectMenuRow<iii>);
    
    return 1;
}

MENU:SelectMenuRow(playerid, response, row) {
    if (!response) {
        return SendClientMessage(playerid, -1, "* You closed the menu.");
    }

    SendClientMessage(playerid, -1, "* Row %i selected.", row);
    
    return 1;
}
