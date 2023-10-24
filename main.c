/*
 * File Name: 			main.c
 * Author: 				Richard Li
 * Last Modified Date: 	Oct 24, 2023 (UTC +8:00)
 *
 * This file is part of the SF Wall Hack program. 
 * This file contains the core codes.
 */


#include <stdio.h>
#include <stdlib.h> 
#include <windows.h> 
#include <conio.h> 
#include <memoryapi.h>
#include <psapi.h> 
#include <pthread.h>

//#include <wchar.h>  // ----This version doesn't contain wide characters---- //
#include <locale.h>   // ----But use selocale() to compatible with GBK coding---- //
/* 
 * The compatible of GBK and UTF-8 is annoying,
 * The running result varies from PCs in different countries...
 * So I give it up !!!!!!! LMAO 
 */

#include "SFWallHackStd.h"
#include "SFWallHackLanguage.h"
#include "SFWallHackAddr.h"
#include "SFWallHackTheme.h"

#pragma comment(lib,"psapi.lib") // ----Don't know why some envs cannot include <psapi.h>---- //

/*
 * 
 */
DWORD 			MOVING_DISTANCE = DEFAULT_MOVING_DISTANCE;
DWORD 			MOVING_DELAY	= DEFAULT_MOVING_DELAY_MILLISECONDS; 
int 			APP_Language	= 0;
SF_Window_Info 	SF_Window 		= {NULL, 0, 0, 0, NULL, 0};
Posi_Addr 		Position_Addr 	= {NULL, NULL};
Posi_Val 		Position_Val 	= {0, 0};
/*
 * init of golbal variables
 */


void SleepAndExit(unsigned int SleepMilliseconds, int ExitCode){
	Sleep(SleepMilliseconds);
	exit(ExitCode);
}

void SelectSFVersion(void){
		// ----print the version table---- //
	printf("----%s----\n", APP_STRINGS[2][1]);
	printf("----%s----\n", APP_STRINGS[3][1]);
	
	for(int i = 1; i <= SF_VERSION_COUNT; i++){
		printf(" [%d]. %s\n", i, GameVersions[i].Info);
	} 

	printf("----%s----\n", APP_STRINGS[2][2]);
	printf("----%s----\n", APP_STRINGS[3][2]);
	
		// ----Let user select---- //
	int ver = 0;
	while(1){
		if(_kbhit()){ 
			ver = getch() - '0'; //'0' == 48
			if(0 < ver && ver <= SF_VERSION_COUNT)
				break;
			else{
				printf("----%s----\n", APP_STRINGS[2][3]);
				printf("----%s----\n", APP_STRINGS[3][3]);
			}
		} 
	}
	
	SF_Window.SF_Version = ver; 
}

void SetAPPLanguage(void){
	switch (SF_Window.SF_Version){
		case 1: // ----CHT----//
			APP_Language = 1; break;
		case 2: // ----CHS----//
			APP_Language = 2; break;
		case 3: // ----ENG----//
			APP_Language = 3; break;
		default:
			APP_Language = 3;
	}
}

void OpenSF(){
	char *name = GameVersions[SF_Window.SF_Version].WindowTitle;
	SF_Window.hWnd = FindWindow(NULL, name);
	if(SF_Window.hWnd == NULL){ // Failed to find ShadowFlare.exe Window 
		printf("%s\n", APP_STRINGS[APP_Language][27]);
		SleepAndExit(DEFAULT_SLEEP_MILLISECONDS, ERR_SF_WINDOW_NOT_FOUND);
	}
	printf("%s\n0x%p\n", APP_STRINGS[APP_Language][4], (void*)SF_Window.hWnd);
	
		// ----Try to get TID & PID---- //
	SF_Window.TID = GetWindowThreadProcessId(SF_Window.hWnd, &SF_Window.PID);
	if(SF_Window.TID == 0){ // ----Failed to get TID---- //
		printf("%s\n", APP_STRINGS[APP_Language][28]);
		SleepAndExit(DEFAULT_SLEEP_MILLISECONDS, ERR_SF_GET_TID_FAILED);
	}
	printf("%s%d\n", APP_STRINGS[APP_Language][5], (int)SF_Window.TID);
	if(SF_Window.PID == 0){ // ----Failed to get PID---- //
		printf("%s\n", APP_STRINGS[APP_Language][29]);
		SleepAndExit(DEFAULT_SLEEP_MILLISECONDS, ERR_SF_GET_PID_FAILED);
	}
	printf("%s%d\n", APP_STRINGS[APP_Language][6], (int)SF_Window.PID);
	
		// ----Try to get HANDLE---- //
	SF_Window.SF_Handle = OpenProcess(PROCESS_ALL_ACCESS, TRUE, SF_Window.PID);
	if(SF_Window.SF_Handle == 0){ // ----Failed to get HANDLE---- // 
		printf("%s\n", APP_STRINGS[APP_Language][30]);
		SleepAndExit(DEFAULT_SLEEP_MILLISECONDS, ERR_SF_GET_HANDLE_FAILED);
	}
	printf("%s%u\n", APP_STRINGS[APP_Language][7], SF_Window.SF_Handle);

}

void GetSFBaseAddress(void){
		// ----Try to get the entry of Shadowflare.exe, not the DLLs---- //
	DWORD dwRet = 0;
	HMODULE hModule[128] = {0}; // ----The List of Modules---- //
	int bRet = EnumProcessModulesEx(SF_Window.SF_Handle, (HMODULE*)hModule, sizeof(hModule), &dwRet, 0x03);
	long unsigned Module_Num = dwRet / sizeof(HMODULE);
	if(Module_Num == 0){ // ----Failed to get Process Modules---- //
		printf("%s\n", APP_STRINGS[APP_Language][31]);
		SleepAndExit(DEFAULT_SLEEP_MILLISECONDS, ERR_SF_GET_PROCESS_MODULES_FAILED);
	}
	printf("%s\n", APP_STRINGS[APP_Language][8]);
	

	/*
		// ----Print every module with address---- //
	system(mode con cols=100 lines=30)
	char lpBaseName[129];
	for(int i = 0; i < Module_Num; i++){
		GetModuleBaseNameA(SF_Handle, hModule[i], lpBaseName, sizeof(lpBaseName));
		printf("%-3d %-50s: %#x\n", i, lpBaseName, hModule[i]);
	}
	*/
	
	// ----Base Addr is the Addr of 1st Module---- //
	SF_Window.Base_hModule = hModule[0]; 
	printf("%s\n0x%p\n", APP_STRINGS[APP_Language][9], (void *)SF_Window.Base_hModule);
}

void CheckIsKeyboardHookSuccess(HHOOK keyboardHook){
	if (keyboardHook == 0){
		printf("%s\n", APP_STRINGS[APP_Language][33]);
		SleepAndExit(DEFAULT_SLEEP_MILLISECONDS, ERR_SF_KEYBOARD_HOOK_FAILED);
	}
}

void CheckIsSFClosed(void){
	DWORD flag = WaitForSingleObject(SF_Window.SF_Handle, DEFAULT_CHECKIFSFCLOSED_WATING_MILLISECONDS);
	if(flag == 0){
		printf("%s\n", APP_STRINGS[APP_Language][34]);
		SleepAndExit(DEFAULT_SLEEP_MILLISECONDS, ERR_SF_CLOSED);
	}
}

DWORD ReadVal(const void* addr){
	DWORD val;
	int ret = ReadProcessMemory(SF_Window.SF_Handle, (LPVOID)addr, &val, sizeof(DWORD), NULL);
	if(ret == 0){
		printf("%s\n", APP_STRINGS[APP_Language][32]);
		SleepAndExit(DEFAULT_SLEEP_MILLISECONDS, ERR_SF_READ_MEMORY_FAILED);
	}
	return val;
}

void ReadPositionValue(void){
	Position_Val.Position_X_Val = ReadVal(Position_Addr.Position_X_Addr);
	Position_Val.Position_Y_Val = ReadVal(Position_Addr.Position_Y_Addr);
}

void WritePositionValue(void){
	WriteProcessMemory(SF_Window.SF_Handle, (LPVOID)Position_Addr.Position_X_Addr, (LPCVOID)&(Position_Val.Position_X_Val), sizeof(DWORD), NULL);
	WriteProcessMemory(SF_Window.SF_Handle, (LPVOID)Position_Addr.Position_Y_Addr, (LPCVOID)&(Position_Val.Position_Y_Val), sizeof(DWORD), NULL);
} 

void PrintPosition(void){
	ReadPositionValue();
	printf("X:%lu Y:%lu\n", Position_Val.Position_X_Val, Position_Val.Position_Y_Val);
}

void GetPositionAddress(){
	/*
	 * Address Offsets are defined in SFWallHackAddr.h
	 */
	
		// ----First-level addressing---- //
	DWORD Addr1_Val = ReadVal( (void*)( (unsigned long long)SF_Window.Base_hModule + _Location_Addr_Offset1_Versions[SF_Window.SF_Version] ) );
	void *Addr1_P = (void*)((unsigned long long)Addr1_Val);
//	printf("第1次寻址: *(%#X + %#X) -> %#X\n", SF_Window.Base_hModule, _Location_Addr_Offset1_Versions[SF_Window.SF_Version], Addr1_P);
	
		// ----Second-level addressing---- //
	DWORD Addr2_Val = ReadVal( (void*)( (unsigned long long)Addr1_P + _Location_Addr_Offset2 ) );
	void *Addr2_P = (void*)((unsigned long long)Addr2_Val);
//	printf("第2次寻址: *(%#X + %#X) -> %#X\n", Addr1_P, _Location_Addr_Offset2, Addr2_P);
	
		// ----Third-level addressing---- //
	DWORD Addr3_Val = ReadVal( (void*)(( unsigned long long)Addr2_P + _Location_Addr_Offset3 ) );
	void *Addr3_P = (void*)((unsigned long long)Addr3_Val);
//	printf("第3次寻址: *(%#X + %#X) -> %#X\n", Addr2_P, _Location_Addr_Offset3, Addr3_P);
	
		// ----Fourth-level addressing---- //
	Position_Addr.Position_X_Addr = (void*)( (unsigned long long)Addr3_P + _Location_Addr_Offset4_X );
	printf("%s 0x%p\n", APP_STRINGS[APP_Language][10], Position_Addr.Position_X_Addr);
//	printf("X地址: %#X + %#X = %#X\n", Addr3_P, _Location_Addr_Offset4_X, Position_Addr.Position_X_Addr);
	Position_Addr.Position_Y_Addr = (void*)( (unsigned long long)Addr3_P + _Location_Addr_Offset4_Y );
	printf("%s 0x%p\n", APP_STRINGS[APP_Language][11], Position_Addr.Position_Y_Addr);
//	printf("Y地址: %#X + %#X = %#X\n", Addr3_P, _Location_Addr_Offset4_Y, Position_Addr.Position_Y_Addr);
}

DWORD GetSTATSValue(unsigned long long Offset){
	DWORD Val = ReadVal( (void*)( (unsigned long long)SF_Window.Base_hModule + _STATS_Addr_Offset1_Versions[SF_Window.SF_Version] + Offset) );
	return Val; 
}

int Check_Is_Moveable(void){
	if( GetSTATSValue(STATS_SHOW_SHOP)
	 || GetSTATSValue(STATS_SHOW_QUEST)
	 || GetSTATSValue(STATS_SHOW_HELP)
	 || GetSTATSValue(STATS_SHOW_ESC_MENU)
	 || GetSTATSValue(STATS_SHOW_OUTFIT_CUSTOMIZE)
	 || GetSTATSValue(STATS_SHOW_BLACKJACK)
	)
		return 0;
	
	return 1;
}

int Check_Minimap(void){
	if(GetSTATSValue(STATS_SHOW_MINIMAP) == 0)
		return 0;

	return 1;
}

	// ----Move player to eight directions---- //
/*
 * "North" in game stand for the upper right of the screen.
 *
 *                    西北 NorthWest
 *           西 West        ||        北 North 
 *                \\        ||        //
 *                  \\      ||      //
 *                    \\    ||    //
 *                      \\  ||  //
 *                        \\||//
 * 西南 SouthWest ==========##========== 东南 NorthEast 
 *                        //||\\
 *                      //  ||  \\
 *                    //    ||    \\
 *                  //      ||      \\
 *                //        ||        \\
 *           南 South       ||        东 East 
 *                    东南 SouthEast 
 *
 *
 * The "X" axis points from [West] to [East], and value increases at the same time
 * The "Y" axis points from [North] to [South], and value increases at the same time
 * The values are 4-bytes integers. Overflow doesn't have a impact in game.
 */
void Move_Player_North(void){
    Position_Val.Position_Y_Val -= MOVING_DISTANCE;
}
void Move_Player_South(void){
    Position_Val.Position_Y_Val += MOVING_DISTANCE;
}
void Move_Player_West(void){
    Position_Val.Position_X_Val -= MOVING_DISTANCE;
}
void Move_Player_East(void){
    Position_Val.Position_X_Val += MOVING_DISTANCE;
}
void Move_Player_NorthWest(void){
    Position_Val.Position_Y_Val -= MOVING_DISTANCE;
    Position_Val.Position_X_Val -= MOVING_DISTANCE;
}
void Move_Player_NorthEast(void){
    Position_Val.Position_Y_Val -= MOVING_DISTANCE;
    Position_Val.Position_X_Val += MOVING_DISTANCE;
}
void Move_Player_SouthWest(void){
    Position_Val.Position_Y_Val += MOVING_DISTANCE;
    Position_Val.Position_X_Val -= MOVING_DISTANCE;
}
void Move_Player_SouthEast(void){
    Position_Val.Position_Y_Val += MOVING_DISTANCE;
    Position_Val.Position_X_Val += MOVING_DISTANCE;
}


void PrintHELP(void){
	printf("%s", LINE_SEPARATER); 
	printf("%s\n", APP_STRINGS[APP_Language][12]);
	printf("%s\n", APP_STRINGS[APP_Language][13]);
	printf("%s\n", APP_STRINGS[APP_Language][14]);
	printf("%s\n", APP_STRINGS[APP_Language][15]);
	printf("%s\n", APP_STRINGS[APP_Language][16]);
	printf("%s", LINE_SEPARATER); 
} 

void ChangeMOVING_DISTANCE(DWORD *MOVING_DISTANCE){
		// ----Set a new moving MOVING_DISTANCE---- //
	printf("%s", LINE_SEPARATER); 
	printf("%s%lu\n", APP_STRINGS[APP_Language][20], *MOVING_DISTANCE);
	printf("%s", APP_STRINGS[APP_Language][17]);
	int temp 		= 0;
	int isChanged 	= 0;
	scanf("%d", &temp);
	if (temp < 0) 
		printf("%s\n", APP_STRINGS[APP_Language][18]);
//	else if(temp < 10) printf("距离太小了吧..\n"); 
	else if(temp > 1001) 
		printf("%s\n", APP_STRINGS[APP_Language][19]);
	else isChanged = 1;
	
	if (isChanged == 0){
		*MOVING_DISTANCE = DEFAULT_MOVING_DISTANCE;
		printf("%s%lu\n", APP_STRINGS[APP_Language][25], *MOVING_DISTANCE);
	}else{
		*MOVING_DISTANCE = (DWORD)temp;
		printf("%s", APP_STRINGS[APP_Language][26]);
	}
	printf("%s%lu\n", APP_STRINGS[APP_Language][20], *MOVING_DISTANCE);
//	printf("%s", LINE_SEPARATER); 
}

void ChangeMOVING_DELAY(DWORD *MOVING_DELAY){
		// ----Set a new moving delay---- //
	printf("%s", LINE_SEPARATER); 
	printf("%s%lu\n", APP_STRINGS[APP_Language][24], *MOVING_DELAY);
	printf("%s", APP_STRINGS[APP_Language][21]);
	int temp 		= 0;
	int isChanged 	= 0;
	scanf("%d", &temp);
	if (temp < 0) 
		printf("%s\n", APP_STRINGS[APP_Language][22]);
	else if(temp > 201) 
		printf("%s\n", APP_STRINGS[APP_Language][23]);
	else isChanged = 1;
	
	if (isChanged == 0){
		*MOVING_DELAY = DEFAULT_MOVING_DELAY_MILLISECONDS;
		printf("%s%lu\n", APP_STRINGS[APP_Language][25], *MOVING_DELAY);
	}else{
		*MOVING_DELAY = (DWORD)temp;
		printf("%s", APP_STRINGS[APP_Language][26]);
	}
	printf("%s%lu\n", APP_STRINGS[APP_Language][24], *MOVING_DELAY);
//	printf("%s", LINE_SEPARATER); 
} 

LRESULT CALLBACK LowLevelKeyboardProc(
	int nCode,		// 规定钩子如何处理消息，小于 0 则直接 CallNextHookEx
	WPARAM wParam,	// 消息类型
	LPARAM lParam	// 指向某个结构体的指针，这里是 KBDLLHOOKSTRUCT（低级键盘输入事件）
	){
		/*
		 * This function is to define a Global Keyboard Hook listener
		 * and define the reactions
		 * 
		 */
    KBDLLHOOKSTRUCT *ks = (KBDLLHOOKSTRUCT*)lParam;	// Include Low Level Keyboard event info
    
    if(ks->flags == 0 || ks->flags == 1){
    	/*
    	 * Here's a trap. For most of the keys, ks->flags==0 means press down
    	 * and 128 stand for release
    	 * But for ARROW keys, ks->flags==1 means press down
    	 * and 129 stand for release
    	 */
    	CheckIsSFClosed();
		int moveable = Check_Is_Moveable();	// ----Check before read and modify, prevent miswrite---- //
		if( moveable ) {
			ReadPositionValue();
			int Minimap = Check_Minimap();
			
				// Monitoring keyboard
			switch(ks->vkCode){				
	//		case 0x31: number 1 on main keyboard
			case VK_NUMPAD1: case 0x46: 		// numpad 1 & F, SOUTH
				Move_Player_South(); break;
	//		case 0x33: 
			case VK_NUMPAD3: case 0x47: 		// numpad 3 & G, EAST
				Move_Player_East(); break;
	//		case 0x37: 
			case VK_NUMPAD7: case 0x54: 		// numpad 7 & T, WEST
				Move_Player_West(); break;
	//		case 0x39: 
			case VK_NUMPAD9: case 0x59: 		// numpad 9 & Y, NORTH
				Move_Player_North(); break;
				
	//		case 0x32: 
			case VK_NUMPAD2: case VK_NUMPAD5: 	// numpad 2 & 5 
				Move_Player_SouthEast(); break;
	//		case 0x34: 
			case VK_NUMPAD4:  					// numpad 4
				Move_Player_SouthWest(); break;
	//		case 0x36: 
			case VK_NUMPAD6: 				 	// numpad 6
				Move_Player_NorthEast(); break;
	//		case 0x38: 
			case VK_NUMPAD8: 					// numpad 8
				Move_Player_NorthWest(); break;
				
		/*
		 * Version 1: If minimap is on, Arrow key not move
		 */
			case VK_DOWN: 		// DOWN Arrow
				if(Minimap == 0){
					Move_Player_SouthEast(); 
				}
				break;
			case VK_LEFT: 		// LEFT Arrow
				if(Minimap == 0){
					Move_Player_SouthWest();
				}
				break;
			case VK_RIGHT: 		// RIGHT Arrow
				if(Minimap == 0){
					Move_Player_NorthEast();
				}
				break;
			case VK_UP: 		// UP Arrow
				if(Minimap == 0){
					Move_Player_NorthWest();
				}
				break;
				
		/*
		 * Version 2: If minimap is on, Arrow key still move
		 * but Minimap cannot move anymore
		 * NOT finished yet
		 */	
//			case VK_DOWN: 		// DOWN Arrow
//				Move_Player_SouthEast();
//				if(Minimap == 1){
////				Move_Player_SouthEast(); 
//					return 1;
//				}
//				break;
//			case VK_LEFT: 		// LEFT Arrow
//				Move_Player_SouthWest();
//				if(Minimap == 1){
////				Move_Player_SouthWest();
//					return 1;
//				}
//				break;
//			case VK_RIGHT: 		// RIGHT Arrow
//				Move_Player_NorthEast();
//				if(Minimap == 1){
////				Move_Player_NorthEast();
//					return 1;
//				}
//				break;
//			case VK_UP: 		// UP Arrow
//				Move_Player_NorthWest();
//				if(Minimap == 1){
////				Move_Player_NorthWest();
//					return 1;
//				}
//				break;
	
			} 
			WritePositionValue();
		}
    }
    //return 1;		// This stop to pass message to next hook 
    return CallNextHookEx(NULL, nCode, wParam, lParam);	// Pass event to next Hook in the linked Queue
}

void GlobalKeyboardHook(void){
	HHOOK keyboardHook = SetWindowsHookExA(
		WH_KEYBOARD_LL,			// 钩子类型，WH_KEYBOARD_LL 为键盘钩子
		LowLevelKeyboardProc,	// 指向钩子函数的指针
		NULL,					// Dll 句柄
		0    					// ThreadID 不填则为全局钩子 
			/*
			 * The Hook is Global. I don't know how to set a specific one...
			 */
			
		);
    CheckIsKeyboardHookSuccess(keyboardHook);
    MSG msg; // 不可漏掉消息处理，不然程序会卡死
    while(1){
		// If there is a message in the Queue
		if (PeekMessageA(
			&msg,		// MSG 接收这个消息
			NULL,		// 检测消息的窗口句柄，NULL：检索当前线程所有窗口消息
			0,		// 检查消息范围中第一个消息的值，NULL：检查所有消息（必须和下面的同时为NULL）
			0,		// 检查消息范围中最后一个消息的值，NULL：检查所有消息
			PM_REMOVE	// 处理消息的方式，PM_REMOVE：处理后将消息从队列中删除
			)){
				TranslateMessage(&msg); // 把按键消息传递给字符消息
				DispatchMessageW(&msg); // 将消息分派给窗口程序
		}
        Sleep(DEFAULT_CPU_SLEEP_MILLISECONDS);    // ----Avoid high CPU Usage---- //
    }
	// Delete this hook 
    UnhookWindowsHookEx(keyboardHook);
}

void KeyboardListener(void){
	/*
	 * This is a Keyboard listener, it defines operations
	 * when your FOCUS is at this Hack app.
	 * I only enable Arrows in this function, because 
	 * there is conflict usage.
	 * In game, arrows are used to move the mini-map.
	 */
	while(1){
		if (_kbhit()){
			CheckIsSFClosed(); // ----Check before read and modify, prevent miswrite---- //
//			ReadPositionValue();
			switch(getch()){
				
				// ----Since the Global Keyboard Hook is imported, some lines are not required below---- //
//					// Numpad and TYFG
//				case '9': case 'Y': case 'y': // NORTH
//					Position_Val.Position_Y_Val -= MOVING_DISTANCE; break;
//				case '1': case 'F': case 'f': // SOUTH
//					Position_Val.Position_Y_Val += MOVING_DISTANCE; break;
//				case '7': case 'T': case 't': // WEST 
//					Position_Val.Position_X_Val -= MOVING_DISTANCE; break;
//				case '3': case 'G': case 'g': // EAST
//					Position_Val.Position_X_Val += MOVING_DISTANCE; break;
//				case '8': // UP 
//					Position_Val.Position_X_Val -= MOVING_DISTANCE; Position_Val.Position_Y_Val -= MOVING_DISTANCE; break;
//				case '2': // DOWN
//					Position_Val.Position_X_Val += MOVING_DISTANCE; Position_Val.Position_Y_Val += MOVING_DISTANCE; break;
//				case '4': // LEFT
//					Position_Val.Position_X_Val -= MOVING_DISTANCE; Position_Val.Position_Y_Val += MOVING_DISTANCE; break;
//				case '6': // RIGHT
//					Position_Val.Position_X_Val += MOVING_DISTANCE; Position_Val.Position_Y_Val -= MOVING_DISTANCE; break;
//				
//				case 224: //arrow keys
//					switch(getch()){
//						case 72: // UP 
//							Position_Val.Position_X_Val -= MOVING_DISTANCE; Position_Val.Position_Y_Val -= MOVING_DISTANCE; break;
//						case 80: // DOWN
//							Position_Val.Position_X_Val += MOVING_DISTANCE; Position_Val.Position_Y_Val += MOVING_DISTANCE; break;
//						case 75: // LEFT
//							Position_Val.Position_X_Val -= MOVING_DISTANCE; Position_Val.Position_Y_Val += MOVING_DISTANCE; break;
//						case 77: // RIGHT
//							Position_Val.Position_X_Val += MOVING_DISTANCE; Position_Val.Position_Y_Val -= MOVING_DISTANCE; break;
//					}
//					break;
					
					// ----More Functions---- //
				case 224: 
					getch(); break; // ----to passby the arrow keys---- //
				
				case 'h': case 'H':
					PrintHELP(); break;
				case 'J': case 'j':
					PrintPosition(); break;
				case 'K': case 'k':
					ChangeMOVING_DISTANCE(&MOVING_DISTANCE); break;
				case 'L': case 'l':
					ChangeMOVING_DELAY(&MOVING_DELAY); break;
				default: 
					break;
			} 
//			WritePositionValue();
			
			/*
				// ----Frequently print HELPs. Consider useless.---- //
			static int PressCounts = 0;
			if(++PressCounts >= NOTICE_COUNT){
				PressCounts -= NOTICE_COUNT;
				PrintHELP();
			}
			*/
		}
		Sleep(MOVING_DELAY);
		Sleep(DEFAULT_CPU_SLEEP_MILLISECONDS); 		// ----Avoid high CPU Usage---- //
	} 
} 

int main(int argc, char *argv[]){
		// ----Some basic settings---- //
	SetTheme_1();
	Print_APP_Version();
	SelectSFVersion(); // Select Language and Version
	SetTheme_2(); 
	SetAPPLanguage();
	OpenSF(); 
	GetSFBaseAddress(); 
	GetPositionAddress();
	ReadPositionValue();
	PrintPosition();
	SetTheme_3(APP_Language);
	PrintHELP();
	
		// ----use multi thread---- //
	pthread_t th1_KeyboardListener = 0;
	pthread_t th2_GlobalKeyboardHook = 0;
	pthread_create(&th1_KeyboardListener, NULL, (void*(*)(void*))KeyboardListener, NULL); 
	pthread_create(&th2_GlobalKeyboardHook, NULL, (void*(*)(void*))GlobalKeyboardHook, NULL); 
	pthread_join(th1_KeyboardListener, NULL);
	pthread_join(th2_GlobalKeyboardHook, NULL);
//	KeyboardListener();
//	GlobalKeyboardHook();

	SleepAndExit(DEFAULT_SLEEP_MILLISECONDS, NORMAL_EXIT);
}
