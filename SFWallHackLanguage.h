/*
 * File Name: 			SFWallHackLanguage.h
 * Author: 				Richard Li
 * Last Modified Date: 	Oct 24, 2023 (UTC +8:00)
 *
 * This file is part of the SF Wall Hack program. 
 * This file includes the defination of the languages
 * and corresponding sentences (strings)
 * 
 */

#ifndef _SF_WALLHACK_LANGUAGE
#define _SF_WALLHACK_LANGUAGE

#define LANGUAGE_COUNT 3
#define SENTENCE_COUNT 35
/*
 * CHT: Chinese (Traditional) (GBK or UTF-8, not Big5) 		currently GBK
 * CHS:	Chinese (Simplifled)								currently GBK
 * ENG: English
 */

const char *APP_STRINGS[LANGUAGE_COUNT+1][SENTENCE_COUNT] = {
{ 0 /* This line is to align the array index 0*/
}, {
	  "CHT"
	, "版本選擇"						//1
	, "請按對應的數字鍵以選擇:"
	, "輸入有誤, 請重新選擇:"
    
	, "----找到了ShadowFlare窗口:"
	, "----獲得了TID:"
	, "----獲得了PID:"					//6
	, "----獲得了進程句柄:"
	, "----獲得了程式各個模塊基地址"
	, "----ShadowFlare.exe基址:"
	, "X的內存地址:"
	, "Y的內存地址:"					//11
    
	, "使用方向鍵/小鍵盤進行移動(可長摁)"
	, "或使用 [G]:東  [F]:南  [T]:西  [Y]:北"
	, "[J]鍵記錄當前位置"
	, "[K]鍵更改單次移動距離"
	, "[L]鍵更改移動時間間隔(毫秒)"
    
	, "設定新的移動距離(建議50-1000):"
	, "距離不可設定為負數!"
	, "距離過大易卡頓/飛出地圖邊界"
	, "當前移動距離為:"
	, "設定新的時間間隔(毫秒)(建議0-200):"
	, "時間間隔不可設定為負數!"
	, "太慢了吧?"
	, "當前時間間隔為:"
	, "自動恢復為默認值:"
	, "修改成功!"
    
	, "錯誤: 未能找到ShadowFlare窗口, 將自動退出"
	, "錯誤: 未能獲得TID, 將自動退出"
	, "錯誤: 未能獲獲得PID, 將自動退出"
	, "錯誤: 未能獲取ShadowFlare句柄, 將自動退出"
	, "錯誤: 未能獲取各模塊加載基址, 將自動退出"
	, "錯誤: 讀內存失敗, 將自動退出"
	, "錯誤: 設置鍵盤HOOK失敗, 將自動退出"
	, "錯誤: 檢測到ShadowFlare已關閉, 將自動退出"
}, {
	  "CHS"
	, "版本选择"						//1
	, "按对应游戏语言和版本的数字按键:"
	, "输入有误, 请重新选择:"
    
	, "----已找到ShadowFlare窗口:"
	, "----已获取TID:"
	, "----已获取PID:"					//6
	, "----已获取进程句柄: "
	, "----已获取各模块加载基址"
	, "----程序基址为:"
	, "X的地址为"
	, "Y的地址为"						//11
    
	, "使用方向键/小键盘进行移动(可长摁)"
	, "或使用 [G]:东  [F]:南  [T]:西  [Y]:北"
	, "[J]: 输出当前位置"
	, "[K]: 更改单次移动的距离"
	, "[L]: 更改每次移动时间间隔(单位:毫秒)"		//16
    
	, "设置新的移动距离(建议50-1000):"
	, "距离不能为负数!"
	, "距离过大会导致卡顿或飞出边界!"
	, "当前移动距离为:"
	, "设置新的时间间隔(毫秒)(建议0-200):"	//21
	, "时间间隔不能为负数!"
	, "这也太慢了吧???"
	, "当前时间间隔为:"
	, "自动修改为默认值:"
	, "修改成功!"									//26
    
	, "错误: 未能找到ShadowFlare窗口, 将自动退出"
	, "错误: 未能获取TID, 将自动退出"
	, "错误: 未能获取PID, 将自动退出"
	, "错误: 未能获取ShadowFlare句柄, 将自动退出"
	, "错误: 未能获取各模块加载基址, 将自动退出"	//31
	, "错误: 读内存失败, 将自动退出"
	, "错误: 设置键盘钩子失败, 将自动退出"
	, "错误: 检测到ShadowFlare已关闭, 将自动退出"	
}, {
	  "ENG"
	, "Select Game Version and Language"		//1
	, "Press the correspond number key:"
	, "Wrong input, select again."
    
	, "----ShadowFlare Window located at:"
	, "----TID obtained. TID:"
	, "----PID obtained. PID:"					//6
	, "----Handle obtained. HANDLE:"
	, "----Module base addr obtained"
	, "----Base address of Shadowflare.exe: "
	, "The Address of X:"
	, "The Address of Y:"						//11
    
	, "(Long) Press Arrows or Keypads to move"
	, "Or [G]:East  [F]:South  [T]:West  [Y]:North"
	, "[J] print current cooradinate"
	, "[K] change the moving distance at a time"
	, "[L] change the delay between movements (ms)"		//16
	   
	, "New distance (Recommand 50-1000):"
	, "Can't set a negative distance value!"
	, "Too large, may cause lag/ map out of bound"
	, "Current moving distance:"
	, "New delay value(Recommand 0-200):"	//21
	, "Can't set a negative delay value!"
	, "Isn't it too slow :( ???"
	, "Curent moving delay:"
	, "Auto set to default value:"
	, "New value set successfully!"						//26
	   
	, "Err: ShadowFlare.exe Window not found."
	, "Err: Failed to get ShadowFlare TID."
	, "Err: Failed to get ShadowFlare PID."
	, "Err: Failed to get ShadowFlare HANDLE."
	, "Err: Failed to get Process Modules."				//31
	, "Err: Failed to read Memory."
	, "Err: Failed to set Keyboard Hook."
	, "Err: ShadowFlare is already Closed."
}
};


// ----These are the unused Wide character strings---- // 
//const wchar_t *LINE_SEPARATER = L"========================================\n";
//const wchar_t *APP_STRINGS[LANGUAGE_COUNT+1][SENTENCE_COUNT] = {
//{ 0 /* This line is to align the array index 0*/
//}, {
//	  L"CHT"
//	, L"版本選擇"						//1
//	, L"請按對應的數字鍵以選擇:"
//	, L"輸入有誤, 請重新選擇:"
//    
//	, L"----找到了ShadowFlare窗口"
//	, L"----獲得了TID:"
//	, L"----獲得了PID:"					//6
//	, L"----獲得了進程句柄:"
//	, L"----獲得了程式各個模塊基地址"
//	, L"----ShadowFlare.exe基址:"
//	, L"X的內存地址:"
//	, L"Y的內存地址:"					//11
//    
//	, L"使用方向鍵/小鍵盤進行移動(可長摁)"
//	, L"或使用 [G]:東  [F]:南  [T]:西  [Y]:北"
//	, L"[J]鍵記錄當前位置"
//	, L"[K]鍵更改單次移動距離"
//	, L"[L]鍵更改移動時間間隔(毫秒)"
//    
//	, L"設定新的移動距離(建議50-1000):"
//	, L"距離不可設定為負數!"
//	, L"距離過大易卡頓/飛出地圖邊界"
//	, L"當前移動距離為:"
//	, L"設定新的時間間隔(毫秒)(建議0-200):"
//	, L"時間間隔不可設定為負數!"
//	, L"太慢了吧?"
//	, L"當前時間間隔為:"
//	, L"自動恢復為默認值:"
//	, L"修改成功!"
//    
//	, L"錯誤: 未能找到ShadowFlare窗口, 將自動退出"
//	, L"錯誤: 未能獲得TID, 將自動退出"
//	, L"錯誤: 未能獲獲得PID, 將自動退出"
//	, L"錯誤: 未能獲取ShadowFlare句柄, 將自動退出"
//	, L"錯誤: 未能獲取各模塊加載基址, 將自動退出"
//	, L"錯誤: 讀內存失敗, 將自動退出"
//	, L"錯誤: 設置鍵盤HOOK失敗, 將自動退出"
//	, L"錯誤: 檢測到ShadowFlare已關閉, 將自動退出"
//}, {
//	  L"CHS"
//	, L"版本选择"						//1
//	, L"按对应游戏语言和版本的数字按键:"
//	, L"输入有误, 请重新选择:"
//    
//	, L"----已找到ShadowFlare窗口"
//	, L"----已获取TID:"
//	, L"----已获取PID:"					//6
//	, L"----已获取进程句柄: "
//	, L"----已获取各模块加载基址"
//	, L"----程序基址为:"
//	, L"X的地址为"
//	, L"Y的地址为"						//11
//    
//	, L"使用方向键/小键盘进行移动(可长摁)"
//	, L"或使用 [G]:东  [F]:南  [T]:西  [Y]:北"
//	, L"[J]: 输出当前位置"
//	, L"[K]: 更改单次移动的距离"
//	, L"[L]: 更改每次移动时间间隔(单位:毫秒)"		//16
//    
//	, L"设置新的移动距离(建议50-1000):"
//	, L"距离不能为负数!"
//	, L"距离过大会导致卡顿或飞出边界!"
//	, L"当前移动距离为:"
//	, L"设置新的时间间隔(毫秒)(建议0-200):"	//21
//	, L"时间间隔不能为负数!"
//	, L"这也太慢了吧???"
//	, L"当前时间间隔为:"
//	, L"自动修改为默认值:"
//	, L"修改成功!"									//26
//    
//	, L"错误: 未能找到ShadowFlare窗口, 将自动退出"
//	, L"错误: 未能获取TID, 将自动退出"
//	, L"错误: 未能获取PID, 将自动退出"
//	, L"错误: 未能获取ShadowFlare句柄, 将自动退出"
//	, L"错误: 未能获取各模块加载基址, 将自动退出"	//31
//	, L"错误: 读内存失败, 将自动退出"
//	, L"错误: 设置键盘钩子失败, 将自动退出"
//	, L"错误: 检测到ShadowFlare已关闭, 将自动退出"	
//}, {
//	  L"ENG"
//	, L"Select Game Version and Language"		//1
//	, L"Press the correspond number key:"
//	, L"Wrong input, select again."
//    
//	, L"----ShadowFlare Window located"
//	, L"----TID obtained. TID:"
//	, L"----PID obtained. PID:"					//6
//	, L"----Handle obtained. HANDLE:"
//	, L"----Module base addr obtained"
//	, L"----Base address of Shadowflare.exe: "
//	, L"The Address of X:"
//	, L"The Address of Y:"						//11
//    
//	, L"(Long) Press Arrows or Keypads to move"
//	, L"Or [G]:East  [F]:South  [T]:West  [Y]:North"
//	, L"[J] print current cooradinate"
//	, L"[K] change the moving distance at a time"
//	, L"[L] change the delay between movements (ms)"		//16
//	   
//	, L"New distance (Recommand 50-1000):"
//	, L"Can't set a negative distance value!"
//	, L"Too large, may cause lag/ map out of bound"
//	, L"Current moving distance:"
//	, L"New delay value(Recommand 0-200):"	//21
//	, L"Can't set a negative delay value!"
//	, L"Isn't it too slow :( ???"
//	, L"Curent moving delay:"
//	, L"Auto set to default value:"
//	, L"New value set successfully!"						//26
//	   
//	, L"Err: ShadowFlare.exe Window not found."
//	, L"Err: Failed to get ShadowFlare TID."
//	, L"Err: Failed to get ShadowFlare PID."
//	, L"Err: Failed to get ShadowFlare HANDLE."
//	, L"Err: Failed to get Process Modules."				//31
//	, L"Err: Failed to read Memory."
//	, L"Err: Failed to set Keyboard Hook."
//	, L"Err: ShadowFlare is already Closed."
//}
//};



#endif /* SFWallHackLanguage.h */
