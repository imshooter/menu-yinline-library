#if defined _INC_MENU_YINLINE
	#endinput
#endif
#define _INC_MENU_YINLINE

#include <YSI_Coding\y_hooks>
#include <YSI_Coding\y_inline>

#define MENU_CB_NONE \
    (Func:0<iii>)

#define MENU:%0(%1) \
    forward %0(%1); public %0(%1)

static
    Menu:gMenu[MAX_PLAYERS] = { INVALID_MENU, ... },
    Func:gCallback[MAX_PLAYERS]<iii> = { MENU_CB_NONE, ... }
;

static Menu_ResponseInternal(playerid, bool:response, row) {
    new
        Func:callback<iii> = gCallback[playerid]
    ;

    gCallback[playerid] = MENU_CB_NONE;

    if (Indirect_GetMeta(callback) == _:tagof (F@_@iii:)) {
        Indirect_Call(_:callback, tagof (F@_@iii:), playerid, response, row);
    } else {
        Indirect_Call(_:callback, tagof (F@_@ii:), response, row);
    }
    
    Indirect_Release(callback);
}

stock bool:Menu_ShowCallback(playerid, Menu:menuid, {F@_@iii, F@_@ii}:callback, tag = tagof (callback)) {
    Indirect_Claim(callback);
    Indirect_SetMeta(callback, tag);

    gMenu[playerid] = menuid;
    gCallback[playerid] = callback;

    return ShowMenuForPlayer(menuid, playerid);
}

hook OnPlayerSelectedMenuRow(playerid, row) {
    if (GetPlayerMenu(playerid) == gMenu[playerid]) {
        Menu_ResponseInternal(playerid, true, row);
        
        return ~0;
    }
    
    return 0;
}

hook OnPlayerExitedMenu(playerid) {
    if (GetPlayerMenu(playerid) == gMenu[playerid]) {
        Menu_ResponseInternal(playerid, false, -1);

        return ~0;
    }
    
    return 0;
}

hook OnPlayerDisconnect(playerid, reason) {
    #pragma unused reason

    if (gMenu[playerid] != INVALID_MENU) {
        DestroyMenu(gMenu[playerid]);
        gMenu[playerid] = INVALID_MENU;

        if (gCallback[playerid]) {
            if (gCallback[playerid] != MENU_CB_NONE) {
                Indirect_Release(gCallback[playerid]);
            }

            gCallback[playerid] = MENU_CB_NONE;
        }
    }

    return 1;
}
