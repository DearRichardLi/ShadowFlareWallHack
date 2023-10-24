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
	, "�汾�x��"						//1
	, "Ո�������Ĕ����I���x��:"
	, "ݔ�����`, Ո�����x��:"
    
	, "----�ҵ���ShadowFlare����:"
	, "----�@����TID:"
	, "----�@����PID:"					//6
	, "----�@�����M�̾��:"
	, "----�@���˳�ʽ����ģ�K����ַ"
	, "----ShadowFlare.exe��ַ:"
	, "X�ăȴ��ַ:"
	, "Y�ăȴ��ַ:"					//11
    
	, "ʹ�÷����I/С�I�P�M���Ƅ�(���L��)"
	, "��ʹ�� [G]:�|  [F]:��  [T]:��  [Y]:��"
	, "[J]�Iӛ䛮�ǰλ��"
	, "[K]�I���Ćδ��ƄӾ��x"
	, "[L]�I�����Ƅӕr�g�g��(����)"
    
	, "�O���µ��ƄӾ��x(���h50-1000):"
	, "���x�����O����ؓ��!"
	, "���x�^���׿��D/�w���؈D߅��"
	, "��ǰ�ƄӾ��x��:"
	, "�O���µĕr�g�g��(����)(���h0-200):"
	, "�r�g�g�������O����ؓ��!"
	, "̫���˰�?"
	, "��ǰ�r�g�g����:"
	, "�Ԅӻ֏͞�Ĭ�Jֵ:"
	, "�޸ĳɹ�!"
    
	, "�e�`: δ���ҵ�ShadowFlare����, ���Ԅ��˳�"
	, "�e�`: δ�ܫ@��TID, ���Ԅ��˳�"
	, "�e�`: δ�ܫ@�@��PID, ���Ԅ��˳�"
	, "�e�`: δ�ܫ@ȡShadowFlare���, ���Ԅ��˳�"
	, "�e�`: δ�ܫ@ȡ��ģ�K���d��ַ, ���Ԅ��˳�"
	, "�e�`: �x�ȴ�ʧ��, ���Ԅ��˳�"
	, "�e�`: �O���I�PHOOKʧ��, ���Ԅ��˳�"
	, "�e�`: �z�y��ShadowFlare���P�], ���Ԅ��˳�"
}, {
	  "CHS"
	, "�汾ѡ��"						//1
	, "����Ӧ��Ϸ���ԺͰ汾�����ְ���:"
	, "��������, ������ѡ��:"
    
	, "----���ҵ�ShadowFlare����:"
	, "----�ѻ�ȡTID:"
	, "----�ѻ�ȡPID:"					//6
	, "----�ѻ�ȡ���̾��: "
	, "----�ѻ�ȡ��ģ����ػ�ַ"
	, "----�����ַΪ:"
	, "X�ĵ�ַΪ"
	, "Y�ĵ�ַΪ"						//11
    
	, "ʹ�÷����/С���̽����ƶ�(�ɳ���)"
	, "��ʹ�� [G]:��  [F]:��  [T]:��  [Y]:��"
	, "[J]: �����ǰλ��"
	, "[K]: ���ĵ����ƶ��ľ���"
	, "[L]: ����ÿ���ƶ�ʱ����(��λ:����)"		//16
    
	, "�����µ��ƶ�����(����50-1000):"
	, "���벻��Ϊ����!"
	, "�������ᵼ�¿��ٻ�ɳ��߽�!"
	, "��ǰ�ƶ�����Ϊ:"
	, "�����µ�ʱ����(����)(����0-200):"	//21
	, "ʱ��������Ϊ����!"
	, "��Ҳ̫���˰�???"
	, "��ǰʱ����Ϊ:"
	, "�Զ��޸�ΪĬ��ֵ:"
	, "�޸ĳɹ�!"									//26
    
	, "����: δ���ҵ�ShadowFlare����, ���Զ��˳�"
	, "����: δ�ܻ�ȡTID, ���Զ��˳�"
	, "����: δ�ܻ�ȡPID, ���Զ��˳�"
	, "����: δ�ܻ�ȡShadowFlare���, ���Զ��˳�"
	, "����: δ�ܻ�ȡ��ģ����ػ�ַ, ���Զ��˳�"	//31
	, "����: ���ڴ�ʧ��, ���Զ��˳�"
	, "����: ���ü��̹���ʧ��, ���Զ��˳�"
	, "����: ��⵽ShadowFlare�ѹر�, ���Զ��˳�"	
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
//	, L"�汾�x��"						//1
//	, L"Ո�������Ĕ����I���x��:"
//	, L"ݔ�����`, Ո�����x��:"
//    
//	, L"----�ҵ���ShadowFlare����"
//	, L"----�@����TID:"
//	, L"----�@����PID:"					//6
//	, L"----�@�����M�̾��:"
//	, L"----�@���˳�ʽ����ģ�K����ַ"
//	, L"----ShadowFlare.exe��ַ:"
//	, L"X�ăȴ��ַ:"
//	, L"Y�ăȴ��ַ:"					//11
//    
//	, L"ʹ�÷����I/С�I�P�M���Ƅ�(���L��)"
//	, L"��ʹ�� [G]:�|  [F]:��  [T]:��  [Y]:��"
//	, L"[J]�Iӛ䛮�ǰλ��"
//	, L"[K]�I���Ćδ��ƄӾ��x"
//	, L"[L]�I�����Ƅӕr�g�g��(����)"
//    
//	, L"�O���µ��ƄӾ��x(���h50-1000):"
//	, L"���x�����O����ؓ��!"
//	, L"���x�^���׿��D/�w���؈D߅��"
//	, L"��ǰ�ƄӾ��x��:"
//	, L"�O���µĕr�g�g��(����)(���h0-200):"
//	, L"�r�g�g�������O����ؓ��!"
//	, L"̫���˰�?"
//	, L"��ǰ�r�g�g����:"
//	, L"�Ԅӻ֏͞�Ĭ�Jֵ:"
//	, L"�޸ĳɹ�!"
//    
//	, L"�e�`: δ���ҵ�ShadowFlare����, ���Ԅ��˳�"
//	, L"�e�`: δ�ܫ@��TID, ���Ԅ��˳�"
//	, L"�e�`: δ�ܫ@�@��PID, ���Ԅ��˳�"
//	, L"�e�`: δ�ܫ@ȡShadowFlare���, ���Ԅ��˳�"
//	, L"�e�`: δ�ܫ@ȡ��ģ�K���d��ַ, ���Ԅ��˳�"
//	, L"�e�`: �x�ȴ�ʧ��, ���Ԅ��˳�"
//	, L"�e�`: �O���I�PHOOKʧ��, ���Ԅ��˳�"
//	, L"�e�`: �z�y��ShadowFlare���P�], ���Ԅ��˳�"
//}, {
//	  L"CHS"
//	, L"�汾ѡ��"						//1
//	, L"����Ӧ��Ϸ���ԺͰ汾�����ְ���:"
//	, L"��������, ������ѡ��:"
//    
//	, L"----���ҵ�ShadowFlare����"
//	, L"----�ѻ�ȡTID:"
//	, L"----�ѻ�ȡPID:"					//6
//	, L"----�ѻ�ȡ���̾��: "
//	, L"----�ѻ�ȡ��ģ����ػ�ַ"
//	, L"----�����ַΪ:"
//	, L"X�ĵ�ַΪ"
//	, L"Y�ĵ�ַΪ"						//11
//    
//	, L"ʹ�÷����/С���̽����ƶ�(�ɳ���)"
//	, L"��ʹ�� [G]:��  [F]:��  [T]:��  [Y]:��"
//	, L"[J]: �����ǰλ��"
//	, L"[K]: ���ĵ����ƶ��ľ���"
//	, L"[L]: ����ÿ���ƶ�ʱ����(��λ:����)"		//16
//    
//	, L"�����µ��ƶ�����(����50-1000):"
//	, L"���벻��Ϊ����!"
//	, L"�������ᵼ�¿��ٻ�ɳ��߽�!"
//	, L"��ǰ�ƶ�����Ϊ:"
//	, L"�����µ�ʱ����(����)(����0-200):"	//21
//	, L"ʱ��������Ϊ����!"
//	, L"��Ҳ̫���˰�???"
//	, L"��ǰʱ����Ϊ:"
//	, L"�Զ��޸�ΪĬ��ֵ:"
//	, L"�޸ĳɹ�!"									//26
//    
//	, L"����: δ���ҵ�ShadowFlare����, ���Զ��˳�"
//	, L"����: δ�ܻ�ȡTID, ���Զ��˳�"
//	, L"����: δ�ܻ�ȡPID, ���Զ��˳�"
//	, L"����: δ�ܻ�ȡShadowFlare���, ���Զ��˳�"
//	, L"����: δ�ܻ�ȡ��ģ����ػ�ַ, ���Զ��˳�"	//31
//	, L"����: ���ڴ�ʧ��, ���Զ��˳�"
//	, L"����: ���ü��̹���ʧ��, ���Զ��˳�"
//	, L"����: ��⵽ShadowFlare�ѹر�, ���Զ��˳�"	
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
