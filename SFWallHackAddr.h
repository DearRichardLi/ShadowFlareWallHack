/*
 * File Name: 			SFWallHackAddr.h
 * Author: 				Richard Li
 * Last Modified Date: 	Oct 24, 2023 (UTC +8:00)
 *
 * This file is part of the SF Wall Hack program. 
 * This file includes some address and offsets
 * which are used to read a particular value in SF
 */

#ifndef _SF_WALLHACK_ADDR
#define _SF_WALLHACK_ADDR
/*
 * define the known offsets and addresses of the SF game.
 * 
 * Notice: In different versions/languages, the "ShadowFlare.exe" 
 * loads resources and data into different mem addresses, 
 * like the [_Location_Addr_Offset1] below. 
 * But the second/third/... level addressing same. 
 */
/*
 * NOTICE: I don't have the ORIGINAL KOR ShadowFlare.exe
 * I only got a copy from the Chinese Community
 * Which the exe is packed (shelled?) by a member
 * I'm not sure whether this Korean version's addresses are 
 * same as the original copy.
 */

#ifndef _SF_LOCATION
#define _SF_LOCATION
const unsigned long long _Location_Addr_Offset1_Versions[SF_VERSION_COUNT + 1] = {
	  0 /* This line is to align the array index 0*/
	, 0x8C85C
	, 0x8C8F4
	, 0x8CE0C
	, 0x8CA0C
	, 0x8C85C	
};
const unsigned long long _Location_Addr_Offset2 = 0x4; 
const unsigned long long _Location_Addr_Offset3 = 0x0;
const unsigned long long _Location_Addr_Offset4_X = 0x2E0;
const unsigned long long _Location_Addr_Offset4_Y = 0x2E4;
/*
 * For example:
 * "ShadowFlare.exe + 8CE0C" -> 0X3440060
 * 0X3440060        + 0X4    -> 0XDEBCE00
 * 0XDEBCE00        + 0X0    -> 0XFB24218
 * 0XFB24218 		+ 0X2E0  == 0XFB244F8 //// So X is at 0XFB244F8
 */
#endif

// ----many of the addresses below are not currently used in this version---- //
#ifndef _SF_STATS
#define _SF_STATS
/*
 * the STATS, stands for STATUS_SERIES is a set of linear continuous address,
 * which stores a range of global variables (and pointers) (4 bytes per variable).
 *
 * It determined things like whether the Mini-Map is shown,
 * whether player use walk/run, whether player is using tele gates...
 * Since their memory is continuous, we just to need to store the base addr
 * and the offsets.
 *
 * the memory before STATS is LARGE field of 0x00, I've no idea what it is about.
 * the memory after STATS contains many unknown switches, timer and pointers.
 *
 * The full offset table is shown below.
 * I thought many methods to store these offsets..
 * because there are some addresses I don't know what they are for...
 * and I want to store the explains
 *
 * Anyway... STATS is currently covering 176 bytes (44 * 4 bytes)
 * (Maybe it will get longer if I understand any address after them)
 */
const unsigned long long _STATS_Addr_Offset1_Versions[SF_VERSION_COUNT + 1] ={
	  0
	, 0x8C844
	, 0x8C8DC
	, 0x8CDF4
	, 0x8C9F4
	, 0x8C844
};
/*
 * !IMPORTANT
 * I put some indicators to notice you which address is dangerous.
 * (Issues are welcomed to report any bug or data bound!)
 * Miswrite to the some address may cause CRASH
 * ========================================================================
 * [S]	-> SAFE, try for fun
 * [A]	-> value is controled and Kept (Locked?) by SF game. 
 * [B]	-> may cause BUGs or malfunction, but not always Crash
 * [@]	-> usually CRASH!
 * [!]	-> Most Important, DO NOT modify unless u know what u r doing!
 * ========================================================================
 *
 * I wrote the explains in the comment after each definations. 
 */
 
#define STATS_CAMERA_WIDTH_ORIGIN               0x00    //     [A]
#define STATS_CAMERA_HEIGHT_ORIGIN              0x04    //     [A]
#define STATS_CAMERA_HORIZONTAL_DISPLAY_OFFSET  0x08    //     [A]
#define STATS_CAMERA_VERTICAL_DISPLAY_OFFSET    0x0C    //     [A]
/*
 * indicates how the visuable area fit in the SF window.
 * if you open a tab, e.g., status page,
 * the STATS_CAMERA_HORIZONTAL_DISPLAY_OFFSET will 
 * change to 320
 */

#define STATS_POINTER_IMPORTANT_1               0x10    //     [A]     [@] [!]
#define STATS_POINTER_IMPORTANT_2               0x14    //     [A]     [@] [!]
#define STATS_POINTER_IMPORTANT_3               0x18    //     [A]     [@] [!]
#define STATS_POINTER_IMPORTANT_4               0x1C    //     [A]     [@] [!]
#define STATS_POINTER_IMPORTANT_5               0x20    //     [A]     [@] [!]
#define STATS_POINTER_IMPORTANT_6               0x24    //     [A]     [@] [!]
/*
 * Important pointers. points to address about personal
 * status or some other game status
 *
 * I have not understand them clearly
 */
 
#define STATS_HP_ANIMATION_SCALE                0x28    // [S] [A]
#define STATS_MP_ANIMATION_SCALE                0x2C    // [S] [A]
#define STATS_WEIGHT_BAR_SCALE                  0x30    // [S] [A]
#define STATS_WEIGHT_BAR_IS_ALTERING            0x34    // [S] [A]
#define STATS_LEVEL_NUM_FLASHING                0x38    // [S] [A]
#define STATS_TO_WAREHOUSE_ANIMATION_SCALE      0x3C    // [S] [A]
/*
 * status of some animation indicators
 * 
 * HP & MP scale will auto change with real HP/MP. 
 * the normal scale is : 0 - 206
 * the weight bar scale often stays in 0 - 34
 *
 * as long as you level up, the STATS_LEVEL_NUM_FLASHING
 * will change by your level, and you will see a flash
 * on the level number at the left bottom.
 *
 * STATS_TO_WAREHOUSE_ANIMATION_SCALE: 0 - 10
 */

#define STATS_POINTER_HOLDING_ITEM              0x40    //     [A]         [!] 
/*
 * Dangerous. Once you hold an item on cursor, this 
 * will point to that item.
 */
 
#define STATS_SHOW_STATUS                       0x44    // [S]
#define STATS_SHOW_ITEM                         0x48    // [S]
#define STATS_SHOW_MAGIC                        0x4C    // [S]
#define STATS_SHOW_SHOP                         0x50    //         [B] [@]
#define STATS_SHOW_WAREHOUSE                    0x54    // [S]
#define STATS_SHOW_GIANTWAREHOUSE               0x58    // [S]
#define STATS_SHOW_TELEPORT_GATES               0x5C    // [S] [A]
#define STATS_SHOW_QUEST                        0x60    // [S]
#define STATS_SHOW_HELP                         0x64    // [S]
#define STATS_SHOW_ESC_MENU                     0x68    // [S]
#define STATS_SHOW_OUTFIT_CUSTOMIZE             0x6C    // [S] [A]
#define STATS_SHOW_MINIMAP                      0x70    // [S]
#define STATS_SHOW_SPECIAL_ITEM                 0x74    // [S]
#define STATS_SHOW_BLACKJACK                    0x78    //         [B]
/*
 * decides if a tab in game show or not.
 * e.g., MiniMap/ Quests/ Warehouse
 *
 * the STATS_SHOW_SHOP is risky. It need to cooperate 
 * with another unknown pointer which points to a
 * merchant id?
 *
 * 0 means NOT shown, 1 means shown
 * 
 * the STATS_SHOW_TELEPORT_GATES is a special one.
 * if you are far away from a teleport Gate, this 
 * will auto turn to 0. However you can change this
 * value to bigger than 2. this will always let it 
 * shown on the screen.
 */

#define STATS_ESC_MENU_FLASHING                 0x7C    // [S] [A]
#define STATS_STATUS_FLASHING                   0x80    // [S] [A]
#define STATS_ITEM_FLASHING                     0x84    // [S] [A]
/*
 * if you turn these value to 1, you can the buttons
 * at the right bottom flash for one time.
 * then the value will go back to 0.
 */

#define STATS_PLAYER_IS_AT_DUNGEON              0x88    // [S] [A]
/*
 * interesting one. when you stays in a dungeon, cave,
 * remains or tower, this turns to 1
 * But this is not correlate with "Display Darkness",
 * Rain Weather or if you could use transport magic
 * in this map.
 */

#define STATS_WALK_RUN                          0x8C    // [S]
/*
 * 0: walk; 1: run 
 */

#define STATS_UNKNOWN1                          0x90    //         [B]     [!]
#define STATS_PAUSE_GAME                        0x94    //         [B]
#define STATS_UNKNOWN2                          0x98    //         [B]     [!]
#define STATS_TO_TITLE                          0x9C    //         [B]
#define STATS_UNKNOWN3                          0xA0    //         [B]     [!]
/*
 * Risky!
 * if turn STATS_UNKNOWN1 from 1 to 0, you will be
 * transport to the last SAFE map (like a town).
 * Sometimes the item durations or money will rollback...
 *
 * STATS_PAUSE_GAME literally Pause everything in the game.
 * including the background timers and animations
 * But this value doesn't change when you enter another map.
 *
 * the STATS_UNKNOWN2 is similar to Unknown1. if you change 
 * this to 1, the game, reload your Savefile? (Not sure)
 * 
 * ! If you tamper Unknown1 or Unknown2 too much, a bug may
 * appear in your Savefile. The performance is that you
 * need to cost much more time to Load/Save your savefile,
 * or enter another map (including by teleport Gates) 
 *
 * If you turn STATS_TO_TITLE to 1, you go back to the
 * Game Title (Main Menu) immediately, often without saving 
 * 
 * STATS_UNKNOWN3: just, unknown now...
 */

#define STATS_TIMER_ATTRIBUTE_GREEN_POINT       0xA4    // [S] [A]
/*
 * This green point is at the status page, at left bottom
 * Intereting that this timer always run, no matter you
 * open the status page or not.
 * Maybe it is a globle timer?
 */

#define STATS_SHOW_CLOSE_LABEL                  0xA8    // [S] [A]
#define STATS_TIMER_CLOSE_LABEL                 0xAC    // [S] [A]
/*
 * every time you open a tab, there will be a <CLOSE>
 * label appear at the bottom.
 *
 * STATS_SHOW_CLOSE_LABEL:
 * 0: Not shown
 * 1: display appear animation
 * 2: Shown
 * 3: Flash, then close all tabs (like you click it)
 * 4: display disappear animation (not used?)
 * 5: display disappear animation
 * 6: lock to Not shown (although a tab is open)
 */
#endif




#endif /* SFWallHackAddr.h */ 
