# ShadowFlareWallHack
ShadowFlare WallHack is a hack of the game, aiming to allow players move their characters by keyboard. Since it can operate the memory directly, you can walk through walls and explore the SF world much more freely.



## 现支持版本 Supported Versions/Languages
* [1].   繁體中文   CHT 2.004.000
* [2].   简体中文   CHN 2.004.000
* [3].   ENGLISH    ENG 2.004.000
* [4].   日本語     JPN 1.004.003
* [5].   Korean     KOR 2.004.001

NOTICE: I don't have the ORIGINAL KOR ShadowFlare.exe . I only got a copy from the Chinese Community, Which the exe is packed (shelled?) by a member.
I'm not sure whether this Korean version's addresses are same as the original copy.

## 使用方法 How to use
*1. 打开神兵游戏, 读取存档  
*2. 打开此修改器, 摁数字键选择游戏版本  
*3. 使用方向键向上下左右移动/ 使用小键盘进行8方向移动/ 使用T Y F G进行斜方向移动  

*1. Open ShadowFlare Game, load your Savefile  
*2. Open this hack, press number keys to select game version  
*3. Use Arrows/Numpads/TYFG to move.  

## 游戏中的方位 Directions in Game
"北"在游戏中指向屏幕右上角。  
 "North" in game stand for the upper right of the screen.
 
 游戏中的X轴从西向东，按箭头方向X值变大。  
 游戏中的Y轴从北向南，按箭头方向Y值变大。  
 X 和 Y 均为4字节整数。溢出不会影响游戏正常运行。  
 The "X" axis points from West to East, and value increases at the same time.  
 The "Y" axis points from North to South, and value increases at the same time.  
 The values are 4-bytes integers. Overflow doesn't have a impact in game.  

## 编译说明 Compile description
I used DEV_CPP 5.10 with gcc and mingw64 to compile this project.  
One thing should be noticed is that this project use psapi.h
If you are using the same environment with me, you should include "mingw64\x86_64-w64-mingw32\include" again to make sure psapi.h is included.

