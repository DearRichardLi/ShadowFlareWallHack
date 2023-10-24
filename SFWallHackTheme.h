/*
 * File Name: 			SFWallHackTheme.h
 * Author: 				Richard Li
 * Last Modified Date: 	Oct 24, 2023 (UTC +8:00)
 *
 * This file is part of the SF Wall Hack program. 
 * This file contains the theme sets.
 */

#ifndef _SF_WALLHACK_THEME
#define _SF_WALLHACK_THEME

const char APP_VERSION[] = "1.6";
const char *LINE_SEPARATER = "========================================\n";

void Print_APP_Version(void){
	printf("%s", LINE_SEPARATER);
	printf("**** WallHack Version: %s ****\n", APP_VERSION); 
	printf("%s", LINE_SEPARATER);
}
void SetTheme_1(void){
	system("title ShawdowFlare WallHack by Richard");
	system("mode con cols=50 lines=20"); 
	setlocale(LC_ALL, "");
}
void SetTheme_2(void){
	system("cls");
	system("title Press [H] for HELPs");
}
void SetTheme_3(int APP_Language){
	switch (APP_Language){
		case 1: case 2: // ----Chinese GBK----//
			/*
			 * TODO: Turn every character into UTF-8 
			 */
			SetConsoleCP(936); break;
		case 3: // ----ENG----//
			SetConsoleCP(65001); break;
		case 4: case 5:
			/*
			 * TODO: I dont know how to support JIP(JPN) or KOR 
			 */
		default:
			SetConsoleCP(65001);
			/*
			 * 936:   ANSI(GB2312)
			 * 65001: UTF-8
			 */
	}
}

#endif /* SFWallHackTheme.h */ 
