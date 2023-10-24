# 更新日志 Update Log
#### v1.0
-- 初步实现了修改坐标的功能  

-- Initially realize the functions of modifying memory.  


#### v1.1
-- 支持繁中版游戏  
-- 探索兼容多语言版本的可能  

-- support CHT version.  
-- exploring possibility to compatible with more versions (languages).  


#### v1.2
-- 第一个稳定、成型的exe文件, 不需要每次都重新编译源代码了  
-- 需要自行输入坐标地址(可通过Cheat Engine搜索)  
-- 使用T Y F G来进行移动  

-- First stable release version.  
-- Need user to input position address. (Can be searched by Cheat Engine)  
-- Use T Y F G to move.  


#### v1.3
-- 重构代码逻辑  
-- 明确了各项数据类型, 减少出bug可能性  
-- 可以使用小键盘或方向键进行移动了  
-- 保留TYFG键的移动功能并改为东西南北方向移动  
-- 可以修改移动速度(L键)和移动时间间隔(K键)了  
-- 新增了比较友好的交互提示  
-- 改了一下窗口大小  

-- redesign code logics
-- more precise and accuried data types, less bug  
-- use numpad(keypad) to move  
-- remain the function to move by T Y F G  
-- able to change the moving distance and delay  
-- more user-friendly output  
-- change the size of the CLI window  


#### v1.4 (不稳定版本 Unstable version)
-- 继续重构代码逻辑中  
-- 添加了繁体中文2.004.000版本的自动寻址  
-- 添加了自选游戏语言和版本的功能(此功能暂时只支持繁中)  
-- 自动检测游戏是否打开, 未打开则自动退出, 避免对内存的误修改  

-- continue to rewrite functions  
-- support auto-addressing on CHT 2.004.000 version  
-- support multi-versions, and user can choose themselves (tamporarily support CHT only)  
-- detect whether SF game is open before searching values  


#### v1.5 Sep 2, 2022 (UTF +8:00)
-- 支持简中、英语、日语、韩语版的自动寻址了  
-- 可以使用方向键进行移动了 (会与移动小地图冲突)  
-- 修复了进入其他地图时读写失败的bug  
-- 使用全局钩子与多线程初步实现了后台运行  
-- 由于钩子与多线程的引入, 大幅修改了代码逻辑, 进行了代码解耦合  
-- 在修改数据之前自动检测游戏是否关闭, 避免内存误修改  
-- 优化了一些信息的展示方式和内容  
-- 删除了不必要的变量  
-- 已知bug: 全局钩子引起的误操作  
-- 暂不支持与多开、分辨率修改器的兼容  

-- Now supporting CHT/ CHS/ ENG/ JPN/ KOR version of ShadowFlare!  
-- Arrow keys are now available to move character! (conflict with moving Minimap)  
-- repair errors while trying to move position after enter another map  
-- use Global KeyboardHook, enable user to move with this hack running background  
-- import multi-thread to realize functions, so have to reduce the coupling of the code  
-- detect whether ShadowFlare is open before modify the memory, avoiding miswrite to memory  
-- optimize way to display information  
-- delete unnecessory variables  
-- KNOWN PROBLEM: Since the Keyboard Hook is global, the value will be changed even though user is typing in other applications.  
-- currently not compatible with "Resolution Hack" and multi-copies (open more than one terminal of ShadowFlare in one PC).  


#### v1.6 Oct 24, 2023 (UTF +8:00)
-- 药品快捷键不再与本修改器冲突了  
-- 小地图打开时，方向键不会移动人物  
-- 全屏标签页打开时，人物不会移动  
-- 将大量变量和宏定义到库函数中  
-- 库函数记录了若干地址, 可用于后续功能拓展  
-- 更改程序显示编码。对中文使用GB2312，其他使用UTF-8  
-- 更正了日语版本的寻址错误  
-- 增加更多注释  
-- 若干小优化  

-- Tablet Hotkeys (1-8 on main Keyboard) do not move character anymore.  
-- Arrow keys do not move character while Minimap is open.  
-- Do not move character while Full-window tabs (like the HELP page, Quest page, and BlackJack) is open.  
-- define the constants and macros in the .h libraries.  
-- the libraries records many addresses, which may be used to extend functions.  
-- change the display coding. For CHT/CHN, use GB2312. For others, use UTF-8.  
-- rectify the wrong KOR version addresses  
-- more English comments  
-- more bugs fixed  




#### TODO:
指定进程钩子  
根据是否开启小地图 开启方向键  √  
使用宽字符?  
拓展其他功能 开启传点之类  
寻找魔法、任务等地址  
按键释放技能  

