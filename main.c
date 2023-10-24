#include <wchar.h>
#include <stdio.h>
#include <stdlib.h> 
#include <windows.h> 
#include <conio.h> 
#include <memoryapi.h>
#include <psapi.h> 
#include <pthread.h>
//#include <locale.h>
#pragma comment(lib,"psapi.lib")

#define NOTICE_COUNT 15 
#define SF_VERSION_COUNT 5

#define DEFAULT_STEP 100
#define DEFAULT_SLEEP_TIME 10
#define DEFAULT_SLEEP_MILLISECONDS 3000
#define DEFAULT_CHECKIFSFCLOSED_WATING_MILLISICONDS 10 

//#define KNOWN_OFFSET_COUNT 2

const char APP_VERSION[] = "1.5";
const char LINE_SEPARATER[] = "========================================\n";

int STEP = DEFAULT_STEP; // 单次移动的距离 默认100 
int SLEEP_TIME = DEFAULT_SLEEP_TIME; // 每次移动的时间间隔 单位:毫秒 默认10 

HANDLE SF_Handle = NULL;

typedef struct _Posi_Addr{
	void* Position_X_Addr;
	void* Position_Y_Addr;
} Posi_Addr;
typedef struct _Posi_Val{
	DWORD Position_X_Val;
	DWORD Position_Y_Val;
} Posi_Val;
Posi_Addr Position_Addr = {NULL, NULL};
Posi_Val Position_Val = {0, 0};

typedef struct _Version{
	char* Language;
	char* VersionNumber;
	char* Info;
	char* WindowTitle;
} Version;
const Version GameVersions[SF_VERSION_COUNT] = {
	  {"CHT", "2.004.000", "繁體中文 CHT 2.004.000", "ShadowFlare for Window98/Me/2000/XP"}
	, {"CHS", "2.004.000", "简体中文 CHN 2.004.000", "ShadowFlare for Window98/Me/2000/XP"}
	, {"ENG", "2.004.000", "ENGLISH  ENG 2.004.000", "ShadowFlare for Window98/Me/2000"}
	, {"JPN", "2.004.000", "日本語   JPN 2.004.000", "SHADOW FLARE for Window98/Me/2000"}
	, {"KOR", "2.004.001", "Korea    KOR 2.004.001", "ShadowFlare for Windows98/Me/2000/XP"}
};

void SetTheme(void){
	system("title ShawdowFlare WallHack by Richard");
	system("mode con cols=50 lines=20"); 
	printf("%s", LINE_SEPARATER);
	printf("WallHack Version: %s\n", APP_VERSION); 
	printf("%s", LINE_SEPARATER);
}

void SleepAndExit(unsigned int SleepMilliseconds, int ExitCode){
	Sleep(SleepMilliseconds);
	exit(ExitCode);
}

int SelectSFVersion(void){
	printf("---版本选择 Select Game Version---\n"); 
	for(int i = 1; i <= SF_VERSION_COUNT; i++){
		printf("%d. ", i);
		puts(GameVersions[i-1].Info);
	} 
	printf("请按对应游戏语言和版本的数字按键:\n");
	
	int ver = 0;
	while(1){
		if(_kbhit()){ 
			ver = getch() - '0';//'0' == 48
			if(0 <= ver && ver <= SF_VERSION_COUNT)
				break;
			else
				printf("无对应版本, 请重新输入:\n");
		} 
	}
	system("cls");
	return ver; 
}

HANDLE OpenSF(char *name){
	HWND hWnd = FindWindow(NULL, name);
	if(hWnd == NULL){ // 未获取窗口句柄 
		printf("Err: ShadowFlare Window not found.\n");
		printf("未找到ShadowFlare窗口..程序将自动退出..\n");
		SleepAndExit(DEFAULT_SLEEP_MILLISECONDS, -1);
	}
	printf("----已找到ShadowFlare窗口!\n");
	DWORD PID = 0;
	DWORD TID = 0; 
	TID = GetWindowThreadProcessId(hWnd, &PID);
	if(TID == 0){ // 未获取TID 
		printf("Err: Failed to get TID.\n");
		printf("未能获取TID..程序将自动退出..\n");
		SleepAndExit(DEFAULT_SLEEP_MILLISECONDS, -1);
	}
	printf("----已获取TID! TID: %d\n", TID);
	if(PID == 0){ // 未获取PID 
		printf("Err: Failed to get PID.\n");
		printf("未能获取PID..程序将自动退出..\n");
		SleepAndExit(DEFAULT_SLEEP_MILLISECONDS, -1);
	}
	printf("----已获取PID! PID: %d\n", PID);
	HANDLE hnd = OpenProcess(PROCESS_ALL_ACCESS, TRUE, PID);
	if(hnd == 0){ // 未获取进程句柄 
		printf("Err: Failed to get ShadowFlare HANDLE.\n");
		printf("未能获取ShadowFlare句柄..程序将自动退出..\n");
		SleepAndExit(DEFAULT_SLEEP_MILLISECONDS, -1);
	}
	printf("----已获取进程句柄! HANDLE: %d\n", hnd);
	return hnd;
}

HMODULE GetSFBaseAddress(void){
	DWORD dwRet = 0;
	HMODULE hModule[128] = {0};
	int bRet = EnumProcessModulesEx(SF_Handle, (HMODULE*)hModule, sizeof(hModule), &dwRet, 0x03);
	int Module_Num = dwRet / sizeof(HMODULE);
	if(Module_Num == 0){
		printf("Err: Failed to get Process Modules.\n");
		printf("未能获取各模块加载基址..程序将自动退出..\n");
		SleepAndExit(DEFAULT_SLEEP_MILLISECONDS, -1);
	}
	printf("----已获取各模块加载基址!\n");
		// 打印各模块基址 
	/*
	char lpBaseName[129];
	for(int i = 0; i < Module_Num; i++){
		GetModuleBaseNameA(SF_Handle, hModule[i], lpBaseName, sizeof(lpBaseName));
		printf("%-3d %-50s基址: %#x\n", i, lpBaseName, hModule[i]);
	}
	*/
	printf("程序基址: %#X\n", hModule[0]);
	return hModule[0]; 
}

DWORD ReadVal(HANDLE hProcess, const void* addr){
	DWORD val;
	int ret = ReadProcessMemory(hProcess, (LPVOID)addr, &val, sizeof(DWORD), NULL);
	if(ret == 0){
		printf("Err: Failed to read Data.\n");
		printf("在试图读取内存时发送错误..程序将自动退出..\n");
		SleepAndExit(DEFAULT_SLEEP_MILLISECONDS, -1);
	}
	return val;
}
void CheckIsKeyboardHookSuccess(HHOOK keyboardHook){
	if (keyboardHook == 0){
		printf("Err: Keyboard Hook Failed.\n");
		printf("设置键盘钩子失败..程序将自动退出..\n");
		SleepAndExit(DEFAULT_SLEEP_MILLISECONDS, -1);
	}
}
void CheckIsSFClosed(void){
	DWORD flag = WaitForSingleObject(SF_Handle, DEFAULT_CHECKIFSFCLOSED_WATING_MILLISICONDS);
	if(flag == 0){
		printf("Err: ShadowFlare is Closed.\n");
		printf("检测到ShadowFlare已退出..程序将自动退出..\n");
		SleepAndExit(DEFAULT_SLEEP_MILLISECONDS, -1);
	}
}
void GetPositionAddress(void* Base_Addr, int SF_Version){
		// Address Offsets	
	unsigned long long Offset1 = SF_Version == 1? 0x8C85C: 
								SF_Version == 2? 0x8C8F4: 
								SF_Version == 3? 0x8CE0C: 
								SF_Version == 4? 0x8CA7C: 
								SF_Version == 5? 0x8C85C: 
								0;
	unsigned long long Offset2 = 0x4; 
	unsigned long long Offset3 = 0x0;
	unsigned long long Offset4X = 0x2E0;
	unsigned long long Offset4Y = 0x2E4;
	 
	DWORD Addr1_Val = ReadVal(SF_Handle, Base_Addr + Offset1);
	void *Addr1_P = (void*)((unsigned long long)Addr1_Val);
	//printf("第1次寻址: *(%#X + %#X) -> %#X\n", Base_Addr, Offset1, Addr1_P);
	DWORD Addr2_Val = ReadVal(SF_Handle, Addr1_P + Offset2);
	void *Addr2_P = (void*)((unsigned long long)Addr2_Val);
	//printf("第2次寻址: *(%#X + %#X) -> %#X\n", Addr1_P, Offset2, Addr2_P);
	DWORD Addr3_Val = ReadVal(SF_Handle, Addr2_P + Offset3);
	void *Addr3_P = (void*)((unsigned long long)Addr3_Val);
	//printf("第3次寻址: *(%#X + %#X) -> %#X\n", Addr2_P, Offset3, Addr3_P);
	Position_Addr.Position_X_Addr = Addr3_P + Offset4X;
	printf("X地址为: %#X\n", Position_Addr.Position_X_Addr);
	//printf("X地址为: %#X + %#X = %#X\n", Addr3_P, Offset4X, Position_Addr.Position_X_Addr);
	Position_Addr.Position_Y_Addr = Addr3_P + Offset4Y;
	printf("Y地址为: %#X\n", Position_Addr.Position_Y_Addr);
	//printf("Y地址为: %#X + %#X = %#X\n", Addr3_P, Offset4Y, Position_Addr.Position_Y_Addr);
}

void ReadPositionValue(void){
	Position_Val.Position_X_Val = ReadVal(SF_Handle, Position_Addr.Position_X_Addr);
	Position_Val.Position_Y_Val = ReadVal(SF_Handle, Position_Addr.Position_Y_Addr);
}

void WritePositionValue(void){
	WriteProcessMemory(SF_Handle, (LPVOID)Position_Addr.Position_X_Addr, (LPCVOID)&(Position_Val.Position_X_Val), sizeof(DWORD), NULL);
	WriteProcessMemory(SF_Handle, (LPVOID)Position_Addr.Position_Y_Addr, (LPCVOID)&(Position_Val.Position_Y_Val), sizeof(DWORD), NULL);
} 

void PrintNotice(void){
	printf("%s", LINE_SEPARATER); 
	printf("使用方向键/小键盘进行移动(可长摁)\n");
	printf("或使用 G: 东  F: 南  T: 西  Y: 北\n");
	printf("J: 输出当前位置  ");
	printf("K: 更改单次移动的距离\n"); //建议值50~1000 
	printf("L: 更改每次移动时间间隔(单位:毫秒)\n");	//建议值0~200
	printf("%s", LINE_SEPARATER); 
} 

void ChangeSTEP(int *STEP){
	printf("%s", LINE_SEPARATER); 
	printf("新的移动距离(建议50-1000, 默认100):\n");
	int temp = 0;
	int isChanged = 0;
	scanf("%d", &temp);
	if (temp < 0) printf("距离不能为负数!\n"); 
	else if(temp < 10) printf("距离太小了吧..\n"); 
	else if(temp > 1001) printf("距离过大会导致卡顿或飞出边界!\n");
	else isChanged = 1;
	
	if (isChanged == 0){
		*STEP = DEFAULT_STEP;
		printf("自动修改为默认值 (%d)\n", *STEP);
	}else{
		*STEP = temp;
		printf("修改成功\n");
	}
	printf("当前速度为%d\n", *STEP);
	printf("%s", LINE_SEPARATER); 
}

void ChangeSLEEP_TIME(int *SLEEP_TIME){
	printf("%s", LINE_SEPARATER); 
	printf("新的时间间隔(单位:毫秒)(建议0-200, 默认10):\n");
	int temp = 0;
	int isChanged = 0;
	scanf("%d", &temp);
	if (temp < 0) printf("时间间隔不能为负数!\n"); 
	else if(temp > 201) printf("这也太慢了吧???\n");
	else isChanged = 1;
	
	if (isChanged == 0){
		*SLEEP_TIME = DEFAULT_SLEEP_TIME;
		printf("自动修改为默认值 (%d)\n", *SLEEP_TIME);
	}else{
		*SLEEP_TIME = temp;
		printf("修改成功\n");
	}
	printf("当前时间间隔为%d\n", *SLEEP_TIME);
	printf("%s", LINE_SEPARATER); 
} 
void PrintPosition(void){
	ReadPositionValue();
	printf("X:%u Y:%u\n", Position_Val.Position_X_Val, Position_Val.Position_Y_Val);
}
LRESULT CALLBACK LowLevelKeyboardProc(
	int nCode,		// 规定钩子如何处理消息，小于 0 则直接 CallNextHookEx
	WPARAM wParam,	// 消息类型
	LPARAM lParam	// 指向某个结构体的指针，这里是 KBDLLHOOKSTRUCT（低级键盘输入事件）
	){
		
    KBDLLHOOKSTRUCT *ks = (KBDLLHOOKSTRUCT*)lParam;		// 包含低级键盘输入事件信息
//    if(ks->flags == 128 || ks->flags == 129 || ks->flags == 256){
    if(ks->flags == 0){ // 0: 按下 128: 抬起 
    	CheckIsSFClosed();
		ReadPositionValue();
			// 监控键盘
		char c;
		switch(ks->vkCode){
			case 0x31: case 0x61: case 0x46: // 1 F
				Position_Val.Position_Y_Val += STEP; break;
			case 0x33: case 0x63: case 0x47: // 3 G
				Position_Val.Position_X_Val += STEP; break;
			case 0x37: case 0x67: case 0x54: // 7 T
				Position_Val.Position_X_Val -= STEP; break;
			case 0x39: case 0x69: case 0x59: // 9 Y
				Position_Val.Position_Y_Val -= STEP; break;
				
			case 0x32: case 0x62: case 0x28: // 2 DOWN
				Position_Val.Position_X_Val += STEP; Position_Val.Position_Y_Val += STEP; break;
			case 0x34: case 0x64: case 0x25: // 4 LEFT
				Position_Val.Position_X_Val -= STEP; Position_Val.Position_Y_Val += STEP; break;
			case 0x36: case 0x66: case 0x27: // 6 RIGHT
				Position_Val.Position_X_Val += STEP; Position_Val.Position_Y_Val -= STEP; break;
			case 0x38: case 0x68: case 0x26: // 8 UP
				Position_Val.Position_X_Val -= STEP; Position_Val.Position_Y_Val -= STEP; break;
		} 
		WritePositionValue();
		
        //return 1;		// 使按键失效
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);	// 将消息传递给钩子链中的下一个钩子
}
void GlobalKeyboardHook(void){
	HHOOK keyboardHook = SetWindowsHookExA(
		WH_KEYBOARD_LL,			// 钩子类型，WH_KEYBOARD_LL 为键盘钩子
		LowLevelKeyboardProc,	// 指向钩子函数的指针
		NULL,					// Dll 句柄
		0    					// ThreadID 不填则为全局钩子 
		);
    CheckIsKeyboardHookSuccess(keyboardHook);
    MSG msg; // 不可漏掉消息处理，不然程序会卡死
    while(1){
		// 如果消息队列中有消息
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
        Sleep(10);    //避免CPU全负载运行
    }
	// 删除钩子
    UnhookWindowsHookEx(keyboardHook);
}

void KeyboardListener(void){
	while(1){
		if (_kbhit()){
			CheckIsSFClosed();
			ReadPositionValue();
			switch(getch()){
					// Numpad and TYFG
				case '9': case 'Y': case 'y': // NORTH
					Position_Val.Position_Y_Val -= STEP; break;
				case '1': case 'F': case 'f': // SOUTH
					Position_Val.Position_Y_Val += STEP; break;
				case '7': case 'T': case 't': // WEST 
					Position_Val.Position_X_Val -= STEP; break;
				case '3': case 'G': case 'g': // EAST
					Position_Val.Position_X_Val += STEP; break;
				case '8': // UP 
					Position_Val.Position_X_Val -= STEP; Position_Val.Position_Y_Val -= STEP; break;
				case '2': // DOWN
					Position_Val.Position_X_Val += STEP; Position_Val.Position_Y_Val += STEP; break;
				case '4': // LEFT
					Position_Val.Position_X_Val -= STEP; Position_Val.Position_Y_Val += STEP; break;
				case '6': // RIGHT
					Position_Val.Position_X_Val += STEP; Position_Val.Position_Y_Val -= STEP; break;
				
				case 224: //arrow keys
					switch(getch()){
						case 72: // UP 
							Position_Val.Position_X_Val -= STEP; Position_Val.Position_Y_Val -= STEP; break;
						case 80: // DOWN
							Position_Val.Position_X_Val += STEP; Position_Val.Position_Y_Val += STEP; break;
						case 75: // LEFT
							Position_Val.Position_X_Val -= STEP; Position_Val.Position_Y_Val += STEP; break;
						case 77: // RIGHT
							Position_Val.Position_X_Val += STEP; Position_Val.Position_Y_Val -= STEP; break;
					}
					break;
					// More Functions
				case 'J': case 'j':
					PrintPosition(); continue;
				case 'K': case 'k':
					ChangeSTEP(&STEP); continue;
				case 'L': case 'l':
					ChangeSLEEP_TIME(&SLEEP_TIME); continue;
				default: continue;
			} 
			WritePositionValue();
			static int PressCounting = 0;
			if(++PressCounting >= NOTICE_COUNT){
				PressCounting -= NOTICE_COUNT;
				PrintNotice();
			}
		}
		Sleep(SLEEP_TIME);
		Sleep(10); // 避免CPU全负载运行
	} 
} 

int main(int argc, char *argv[]){
	SetConsoleCP(65001); // using UTF-8 coding
	SetTheme();
	int SF_Version = SelectSFVersion(); // Select Language and Version
	SF_Handle = OpenSF(GameVersions[SF_Version - 1].WindowTitle); 
	HMODULE Base_hModule = GetSFBaseAddress(); 
	//void* Base_Addr = Base_hModule; // Base Addr is the Addr of 1st Module 
	GetPositionAddress(Base_hModule, SF_Version);
	ReadPositionValue();
	PrintPosition();
	PrintNotice();
		// use multi thread
	pthread_t th1_KeyboardListener = 0;
	pthread_t th2_GlobalKeyboardHook = 0;
	pthread_create(&th1_KeyboardListener, NULL, (void*(*)(void*))KeyboardListener, NULL); 
	pthread_create(&th2_GlobalKeyboardHook, NULL, (void*(*)(void*))GlobalKeyboardHook, NULL); 
	pthread_join(th1_KeyboardListener, NULL);
	pthread_join(th2_GlobalKeyboardHook, NULL);
//	KeyboardListener();
//	GlobalKeyboardHook();
	return 0;
}
