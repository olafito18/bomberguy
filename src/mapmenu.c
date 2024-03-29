/* map/tileset selection menu */

#include "bomberclone.h"
#include "menu.h"

/* launch the map options menu */
void
mapmenu ()
{
    int menuselect = 0;
    char *mapname = NULL,
        pathname[LEN_PATHFILENAME];
    _charlist maptypes[] = {
        {"selected file", NULL},
        {"random file", NULL},
        {"autogenerated", NULL},
        {"more random", NULL}
    }, tiletypes[] = {
        {
        "random"}, {
        "selected"}
    }, tunneltypes[] = {
        {
        "normal"}, {
        "tunnel"}, {
    "random"},}, *selmt = NULL, *selts = NULL, *seltt = NULL;
    char mname[100];
	_menu *menu;

    charlist_fillarraypointer (maptypes, 4);
    charlist_fillarraypointer (tiletypes, 2);
    charlist_fillarraypointer (tunneltypes, 3);

    while (menuselect != -1 && bman.state != GS_quit) {
        menu = menu_new ("Map Options", 420, 400);
        switch (map.map_selection) {
        case (MAPS_select):    // Selected Map
            selmt = charlist_findtext (maptypes, "selected file");
            if (map.map[0] == 0)
                sprintf (mname, "< undefined >");
            else
                sprintf (mname, "%s", getfilename (map.map));
            menu_create_label (menu, "Selected Map:", 20, 160, 0, COLOR_brown);
            menu_create_button (menu, mname, 10, 180, 170, 2);
            break;
        case (MAPS_randmap):   // Random Map
            selmt = charlist_findtext (maptypes, "random file");
            break;
        case (MAPS_randgen):   // Random Generated Map
            selmt = charlist_findtext (maptypes, "autogenerated");
            d_printf ("autogen\n");
            menu_create_entry (menu, "X Size:", 20, 160, 120, &map.size.x, MAX_FIELDSIZE_X, MENU_entryint16, 2);
            menu_create_entry (menu, "Y Size:", 20, 180, 120, &map.size.y, MAX_FIELDSIZE_Y, MENU_entryint16, 3);
            break;
        case (MAPS_morerand): // More Random
            selmt = charlist_findtext (maptypes, "more random");
            d_printf ("more random\n");
            menu_create_entry (menu, "X Size:", 20, 160, 120, &map.size.x, MAX_FIELDSIZE_X, MENU_entryint16, 2);
            menu_create_entry (menu, "Y Size:", 20, 180, 120, &map.size.y, MAX_FIELDSIZE_Y, MENU_entryint16, 3);
            break;
        }
        if (map.random_tileset)
			selts = &tiletypes[0];
		else
			selts = &tiletypes[1];
        if (map.tileset[0] == 0)
            sprintf (mname, "< undefined >");
        else
            sprintf (mname, "%s", map.tileset);
        menu_create_label (menu, "Selected Tileset:", 250, 140, 0, COLOR_brown);
        menu_create_button (menu, mname, 250, 160, 170, 5);

        switch (map.type) {
        case (MAPT_normal):
            seltt = charlist_findtext (tunneltypes, "normal");
            break;
        case (MAPT_tunnel):
            seltt = charlist_findtext (tunneltypes, "tunnel");
            break;
        default:
            seltt = charlist_findtext (tunneltypes, "random");
            break;
        }

        menu_create_label (menu, "Map Type:", 10, 50, 1, COLOR_brown);
        menu_create_label (menu, "Tileset:", 250, 50, 1, COLOR_brown);
        menu_create_label (menu, "Items:", 220, 200, 1, COLOR_brown);
        menu_create_list (menu, "mt", 10, 85, 170, 60, maptypes, &selmt, 1);
        menu_create_list (menu, "ts", 250, 85, 170, 40, tiletypes, &selts, 4);
        menu_create_list (menu, "tt", 10, 220, 100, 60, tunneltypes, &seltt, 6);

        menu_create_entry (menu, "Bombs:", 140, 240, 110, &map.bombs, 100, MENU_entryint32, 7);
        menu_create_entry (menu, "Fire: ", 140, 260, 110, &map.fire, 100, MENU_entryint32, 8);
        menu_create_entry (menu, "Shoes:", 140, 280, 110, &map.shoes, 100, MENU_entryint32, 9);
        menu_create_entry (menu, "Mixed:", 140, 300, 110, &map.mixed, 100, MENU_entryint32, 10);
        menu_create_entry (menu, "Death:", 140, 320, 110, &map.death, 100, MENU_entryint32, 11);

        menu_create_entry (menu, "Trigger:", 280, 240, 120, &map.sp_trigger, 30, MENU_entryint32, 12);
        menu_create_entry (menu, "Push:   ", 280, 260, 120, &map.sp_push, 30, MENU_entryint32, 13);
        menu_create_entry (menu, "Row:    ", 280, 280, 120, &map.sp_row, 30, MENU_entryint32, 14);
        menu_create_entry (menu, "Kick:   ", 280, 300, 120, &map.sp_kick, 30, MENU_entryint32, 15);

        menu_create_button (menu, "Game Options", -1, 350, 150, 16);

		menu_create_button (menu, "Ok", -1, 380, 150, 0);

        menuselect = menu_loop (menu);
        menu_delete (menu);
        switch (menuselect) {
        case (0):
            menuselect = -1;
            break;
        case (2):              // Select Map
            sprintf (pathname, "%s/maps", bman.datapath);
            mapname = menu_dir_select ("Select Map", pathname, DF_file);
            if (mapname == NULL) {
                map.map[0] = 0;
                map.map_selection = 2;
            }
            else
                sprintf (map.map, "%s/maps/%s", bman.datapath, mapname);
            break;

        case (5):              // Selected Tileset
            sprintf (pathname, "%s/tileset", bman.datapath);
            mapname = menu_dir_select ("Select Tileset", pathname, DF_dir);
            if (mapname == NULL) {
                map.tileset[0] = 0;
                map.random_tileset = 1;
            }
            else
                strcpy (map.tileset, mapname);
            break;
			
		case (16): /* Game Settings */
			mapgamesetting ();
			break;
        }

		/* map type */
        map.type = seltt - &tunneltypes[0];
        if (map.type == 2)
            map.type = -1;
        d_printf ("Tunnel:%d\n", map.type);

		/* tileset mode and map mode */
		map.random_tileset = 1-(selts - &tiletypes[0]);
        map.map_selection = selmt - &maptypes[0];
    }
    map.size.x = map.size.x | 1;
    if (map.size.x < MIN_FIELDSIZE_X)
        map.size.x = MIN_FIELDSIZE_X;
    if (map.size.x > MAX_FIELDSIZE_X)
        map.size.x = MAX_FIELDSIZE_X;
    map.size.y = map.size.y | 1;
    if (map.size.y < MIN_FIELDSIZE_Y)
        map.size.y = MIN_FIELDSIZE_Y;
    if (map.size.y > MAX_FIELDSIZE_Y)
        map.size.y = MAX_FIELDSIZE_Y;

	config_write ();
	if (GT_MP_PTPM)  net_send_servermode ();
}


/*
	Draw an info Screen about the mapsetting which are currently used
*/
#define WIN_X 500
#define WIN_Y 350
void
mapinfo ()
{
    _keybinput ki;
    SDL_Event event;
    int x,
      y,
      eventstate,
      done = 0;
    char text[255];

// draw_menubox (WIN_X, WIN_Y);

    x = gfx.res.x / 2;
    y = gfx.res.y / 2 - WIN_Y / 2;

    sprintf (text, "Map Settings");
// font_setcolor (128,128,0,1);
// font_draw (x - (font[1].size.x * strlen (text) / 2), y, text, 1);
// font_setcolor (255,255,0,1);
// font_draw (1 + x - (font[1].size.x * strlen (text) / 2),1 + y, text, 1);
    y = y + 2 + (font[1].size.y << 1);

    /* MapSize */
    sprintf (text, "Fieldsize: %d,%d", map.size.x, map.size.y);
// font_setcolor (128,128,128,0);
// font_draw (x - (font[0].size.x * strlen (text) / 2), y, text, 0);
// font_setcolor (255,255,255,0);
// font_draw (1 + x - (font[0].size.x * strlen (text) / 2),1 + y, text, 0);
    y = y + 2 + font[0].size.y;

    /* Tileset */
    if (map.random_tileset)
        sprintf (text, "Random Tileset");
    else
        sprintf (text, "Tileset: %s", map.tileset);
// font_setcolor (128,128,128,0);
// font_draw (2 + x - (WIN_X / 2), y, text, 0);
// font_setcolor (255,255,255,0);
// font_draw (3 + x - (WIN_X / 2) ,1 + y, text, 0);

    /* Mapselection */
    if (map.map_selection == 0)
        sprintf (text, "Selected Map: %s", map.map);
    else if (map.map_selection == 1)
        sprintf (text, "Random Map");
    else
        sprintf (text, "Random Generated Map");
// font_setcolor (128,128,128,0);
// font_draw (x , y, text, 0);
// font_setcolor (255,255,255,0);
// font_draw (1 + x, 1 + y, text, 0);
    y = y + 2 + (font[0].size.y << 1);

    /* Bomb Powerups */
    sprintf (text, "Bomb Powerup: %d", map.bombs);
// font_setcolor (128,128,128,0);
// font_draw (2 + x - (WIN_X / 2), y, text, 0);
// font_setcolor (255,255,255,0);
// font_draw (3 + x - (WIN_X / 2) ,1 + y, text, 0);

    /* Trigger */
    sprintf (text, "Trigger Specials: %d", map.sp_trigger);
// font_setcolor (128,128,128,0);
// font_draw (x , y, text, 0);
// font_setcolor (255,255,255,0);
// font_draw (1 + x, 1 + y, text, 0);
    y = y + 2 + font[0].size.y;

    /* Fire Powerups */
    sprintf (text, "Fire Powerup: %d", map.fire);
// font_setcolor (128,128,128,0);
// font_draw (2 + x - (WIN_X / 2), y, text, 0);
// font_setcolor (255,255,255,0);
// font_draw (3 + x - (WIN_X / 2) ,1 + y, text, 0);

    /* Push */
    sprintf (text, "Push Specials: %d", map.sp_push);
// font_setcolor (128,128,128,0);
// font_draw (x , y, text, 0);
// font_setcolor (255,255,255,0);
// font_draw (1 + x, 1 + y, text, 0);
    y = y + 2 + font[0].size.y;

    /* Shoe Powerups */
    sprintf (text, "Shoe Powerup: %d", map.shoes);
// font_setcolor (128,128,128,0);
// font_draw (2 + x - (WIN_X / 2), y, text, 0);
// font_setcolor (255,255,255,0);
// font_draw (3 + x - (WIN_X / 2) ,1 + y, text, 0);

    /* Row */
    sprintf (text, "Row Specials: %d", map.sp_row);
// font_setcolor (128,128,128,0);
// font_draw (x , y, text, 0);
// font_setcolor (255,255,255,0);
// font_draw (1 + x, 1 + y, text, 0);
    y = y + 2 + font[0].size.y;


    /* Mixed Powerups */
    sprintf (text, "Mixed Powerup: %d", map.mixed);
// font_setcolor (128,128,128,0);
// font_draw (2 + x - (WIN_X / 2), y, text, 0);
// font_setcolor (255,255,255,0);
// font_draw (3 + x - (WIN_X / 2) ,1 + y, text, 0);

    /* Special FREE 
       sprintf (text, "Push Specials: %d", map.sp_push);
       font_setcolor (128,128,128,0);
       font_draw (x , y, text, 0);
       font_setcolor (255,255,255,0);
       font_draw (1 + x, 1 + y, text, 0); */
    y = y + 2 + font[0].size.y;

    /* Death Powerups */
    sprintf (text, "Death Powerup: %d", map.death);
// font_setcolor (128,128,128,0);
// font_draw (2 + x - (WIN_X / 2), y, text, 0);
// font_setcolor (255,255,255,0);
// font_draw (3 + x - (WIN_X / 2) ,1 + y, text, 0);

    /* Special FREE
       sprintf (text, "Row Specials: %d", map.sp_row);
       font_setcolor (128,128,128,0);
       font_draw (x , y, text, 0);
       font_setcolor (255,255,255,0);
       font_draw (1 + x, 1 + y, text, 0); */
    y = y + 2 + font[0].size.y;

    SDL_Flip (gfx.screen);
    keybinput_new (&ki, KEYBI_text, 10);

    while (!done && bman.state == GS_wait) {
        if (GT_MP && bman.sock != -1) {
            network_loop ();
            eventstate = s_fetchevent (&event);
        }
        else
            eventstate = SDL_WaitEvent (&event);

        if (eventstate != 0)
            switch (event.type) {
            case (SDL_QUIT):
                bman.state = GS_quit;
                done = 1;
                break;
            }

        done = keybinput_loop (&ki, &event);
    }
}

#undef WIN_X
#undef WIN_Y


/* change start settings for the game */
void mapgamesetting () {
    int menuselect = 0;
	_charlist gametype [] = {
		{"Bomberman", NULL},
        {"Deathmatch", NULL},
		{"Teammode", NULL}
	};
	_charlist *gametype_sel = &gametype[bman.gametype];
	_menu *menu;
	
	charlist_fillarraypointer (gametype, 3);
	
    while (menuselect != -1 && bman.state != GS_quit) {
        menu = menu_new ("Game Options", 420, 400);
		
		menu_create_label (menu, "Start Values", 25, 50, 0, COLOR_brown);
		menu_create_entry (menu, "Bombs:", 25, 80, 150, &bman.start_bombs, MAX_BOMBS, MENU_entryint32, 1);
		menu_create_entry (menu, "Speed:", 25,110, 150, &bman.start_speed, MAX_SPEED, MENU_entryfloat, 2);
		menu_create_entry (menu, "Range:", 25,140, 150, &bman.start_range, MAX_RANGE, MENU_entryint32, 3);
		
		menu_create_label (menu, "Other Values", 200, 50, 0, COLOR_brown);
        menu_create_entry (menu, "Gametime:", 200, 80, 150, &bman.init_timeout, 1200, MENU_entryint32, 4);

		menu_create_label (menu, "Game Parameter", 25, 180, 1, COLOR_brown);
        menu_create_entry (menu, "Bomb Time:", 25, 220, 200, &bman.bomb_tickingtime, 1200, MENU_entryfloat, 5);
		menu_create_label (menu, "Gametype", 25, 250, 0, COLOR_brown);
		menu_create_list (menu, "GameType", 25, 280, 150, 60, gametype, &gametype_sel, 6);
		menu_create_bool (menu, "Drop Items", 200, 280, 150, &bman.dropitemsondeath, 7);	
		
        menu_create_button (menu, "Ok", -1, 380, 150, 0);
        menuselect = menu_loop (menu);
		menu_delete (menu);
		
		if (menuselect == 0) {
			bman.gametype = gametype_sel- &gametype[0];
			menuselect = -1;
		}
    }	
};
