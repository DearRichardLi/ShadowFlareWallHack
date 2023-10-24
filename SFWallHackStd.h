/*
 * File Name: 			SFWallHackStd.h
 * Author: 				Richard Li
 * Last Modified Date: 	Oct 24, 2023 (UTC +8:00)
 *
 * This file is part of the SF Wall Hack program. 
 * This file includes some basic constants and
 * data structures used in the program.
 */

#ifndef _SF_WALLHACK_STD
#define _SF_WALLHACK_STD


/*
 * Frequently output HELPs
 * Not used in this version
 */
#define NOTICE_COUNT 15 


/*
 * define the supported versons.
 * 
 * This program only support the "original" game versions.
 * And is not currently compatible with 
 * "resulution hack" "open game with multiple copies" "Black Jack hack (From CN community)"
 */
#define SF_VERSION_COUNT 5
typedef struct _Version{
	char* Language;
	char* VersionNumber;
	char* Info;
	char* WindowTitle;
} Version;
const Version GameVersions[SF_VERSION_COUNT + 1] = {
	  {"Lan", "Version", "Info", "Window Title"} /* This line is to align the array index 0*/
	, {"CHT", "2.004.000", "繁體中文 CHT 2.004.000", "ShadowFlare for Window98/Me/2000/XP"}
	, {"CHS", "2.004.000", "简体中文 CHN 2.004.000", "ShadowFlare for Window98/Me/2000/XP"}
	, {"ENG", "2.004.000", "ENGLISH  ENG 2.004.000", "ShadowFlare for Window98/Me/2000"}
	, {"JPN", "2.004.000", "日本語   JPN 1.004.003", "SHADOW FLARE for Window98/Me/2000"}
	, {"KOR", "2.004.001", "Korean   KOR 2.004.001", "ShadowFlare for Windows98/Me/2000/XP"}
		/*
		 * NOTICE: I don't have the ORIGINAL KOR ShadowFlare.exe
		 * I only got a copy from the Chinese Community
		 * Which the exe is packed (shelled?) by a member
		 * I'm not sure whether this Korean version's addresses are 
		 * same as the original copy.
		 */
};


/*
 * define the default moving distance 
 * and the delay between two movements (in millisecond)
 * 
 * in SF, the coordinate is presented as X and Y (signed int32) 
 */
#define DEFAULT_MOVING_DISTANCE 100
#define DEFAULT_MOVING_DELAY_MILLISECONDS 10


/*
 * define the sleep duration when an error occur, then exit.
 * and the waiting time to check whether the game is closed.
 */
#define DEFAULT_SLEEP_MILLISECONDS 3000
#define DEFAULT_CHECKIFSFCLOSED_WATING_MILLISECONDS 10 


/*
 * used for multi threads and Keyboard Hook.
 * Avoid High CPU Usage
 */
#define DEFAULT_CPU_SLEEP_MILLISECONDS 10


/*
 * This is to store Info of the SF Game Window
 */
typedef struct _SF_Window_Info{
	HWND 	hWnd;
	DWORD 	PID;
	DWORD 	TID;
	HANDLE 	SF_Handle;
	HMODULE Base_hModule;
	int 	SF_Version;
} SF_Window_Info;



/*
 * data structure used in this program
 */
typedef struct _Posi_Addr{
	void* Position_X_Addr;
	void* Position_Y_Addr;
} Posi_Addr;
typedef struct _Posi_Val{
	DWORD Position_X_Val;
	DWORD Position_Y_Val;
} Posi_Val;


/*
 * define some error codes
 */
#define NORMAL_EXIT                         0
#define ERR_SF_WINDOW_NOT_FOUND 			10001
#define ERR_SF_GET_TID_FAILED				10002
#define ERR_SF_GET_PID_FAILED				10003
#define ERR_SF_GET_HANDLE_FAILED 			10004
#define ERR_SF_GET_PROCESS_MODULES_FAILED 	10005
#define ERR_SF_READ_MEMORY_FAILED 			10010
#define ERR_SF_KEYBOARD_HOOK_FAILED 		10020
#define ERR_SF_CLOSED						10999



#endif /* SFWallHackStd.h */

