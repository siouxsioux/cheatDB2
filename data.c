#include <stdio.h>
#include <string.h>
#include "dbf.h"
#include "unit.h"
#include "fleet.h"
#include "func.h"

struct pref pref;
struct CHEAT cheat;
struct HEAD head;
struct UNIT devUnit[165];
struct WPNGUN wpnGun[144];
struct ARMO armo[124];
struct UNIT unit001[525];
struct FLEET JPfleet[16];
struct FLEET USfleet[16];
struct FLEET UKfleet[16];
struct FLEET DEfleet[16];
struct ELEMENT JPelem[850];
struct ELEMENT USelem[2040];
struct ELEMENT UKelem[600];
struct ELEMENT DEelem[1550];
struct ELEMENT RUelem[400];
struct ELEMENT NLelem[45];
struct ELEMENT AUelem[100];
struct ELEMENT THelem[25];
struct ELEMENT INelem[80];
struct ELEMENT CHelem[100];
char   fUNK11[12409];
struct FILEMAP fileMap;

char lineBuf[1024];
char jpString[][80] = {
	"�����G���[",				// #0
	"cheatprf.txt�Ɍ�肪����܂�.",	// #1
	"�������s��",				// #2
	"RETURN�L�[�������ƏI�����܂�......",	// #3
	"����",					// #4
	"�����ӎ�",				// #5
	"�H�Ɨ�",				// #6
	"�Z�p��",				// #7
	"�q��@",				// #8
	"��",					// #9
	"��",					// #10
	"�͑D",					// #11
	"�����܂���.",			// #12
	"���J���܂���.",			// #13
	"�͓��e����,���̓o�[�W�������Ⴂ�܂�.",	// #14
	"wpn.db2���J���܂���.",			// #15
	"wpn.db2�Ɉُ킪����܂�.",		// #16
	"wpgun.db2���J���܂���.",		// #17
	"wpgun.db2�Ɉُ킪����܂�.",		// #18
	"���a�C",		// #19
	"��",			// #20
	"�C��(����)",	// #21
	"�C��(����)",	// #22
	"��ƃt�@�C��",	// #23
	"�C��",			// #24
	"�m�b�g(����)",	// #25
	"�m�b�g(����)",	// #26
	"�m�b�g",	// #27
	"�b",		// #28
	"��",		// #29
	"unit001.db2���J���܂���.",	// #30
	"unit001.db2�Ɉُ킪����܂�.",	// #31
	"�L��",				// #32
	"����",				// #33
	"���ڕ��햼          �e��    �ː�    �ˊE(�O/��/��)��    �˒�����    ���U����", // #34
	"�̏������ݒ��ɃG���[.", 	// #35
	"�������ł��܂���.",		// #36
	"�̍X�V���ł��܂���.",	// #37
	"��p���[�h�ł�",		// #38
	"�̎w��݂̂��������܂�.",// #39
};

char unitArmy[][16] = {
	"���㕔��",	// #01
};

char unitSub[][16] = { 
	"������",	// #20
	"���������",	// #21
	"�A��������",	// #22
	"�x��������",	// #23
	"�⋋������",	// #24
	"���q�͐�����",	// #25
	"�C���v��",	// #26
};

char unitAir[][16] = {
	"�͏�퓬�@",	// #40
	"�͏㔚���@",	// #41
	"�͏�U���@",	// #42
	"�͏��@�@",	// #43
	"�͏㗋���@",	// #44
	"�퓬�@",	// #45
	"�P���@",	// #46
	"��@�@",	// #47
	"�����@",	// #48
	"�ǒn�퓬�@",	// #49
	"���d��s��",	// #4A
	"��s��",	// #4B
	"�헪�����@",	// #4C
	"�ΐ������@",	// #4D
	"����퓬�@",	// #4E
	"����U���@",	// #4F
	"���㔚���@",	// #50
	"�����@�@",	// #51
	"����U���@",	// #52
	"���㔚���@",	// #53
	"�U���@",	// #54
	"���ꔚ���@",	// #55
	"������s��",	// #56
	"�����@�@",	// #57
	"�󒆐��",	// #58
	"��Ԑ퓬�@",	// #59
	"�~�Ջ@",	// #5A
	"���q�͔����@",	// #5B
	"�d�v���@",	// #5C
};

char unitShip[][16] = {
	"���",			// #80
	"�b�l���",		// #81
	"���",			// #82
	"�y���",		// #83
	"����@���",		// #84
	"�d���m��",		// #85
	"�y���m��",		// #86
	"�쒀��",		// #87
	"�h��쒀��",		// #88
	"���q�͐��",		// #89
	"���q�͍q����",	// #8A
	"���q�͋��",		// #8B
	"���q�͏��m��",		// #8C
	"�C�[�W�X���m��",	// #8D
	"�C�[�W�X�쒀��",	// #8E
	"�X�R���",		// #8F
	"�A���D",		// #90
	"�C�|�W�X���",		// #91
};

char srcShip[][16] = {
	"�͎�:",			// #0
	"����:",				// #1
	"�͖�:",			// #2
	"������p:",			// #3 ...P
	"�q������:",			// #4 ...RI(SUIJOU)
	"�q������:",			// #5 ...RI(SUIJOU)
	"�@��:",			// #6
	"���ڃ^�C�v:",			// #7
	"���ڗe��:",			// #8
	"�o��Z�p��:",			// #9 ...P
	"�ϋv:",			// #10
	"�h��:",			// #11 ...cmBOUGYO
	"�h�����:",			// #12
	"�ő呬��:",			// #13 ...NOT(SUIJOU)
	"�ő呬��:",			// #14 ...NOT(SUICHYU)
	"���㑬�x:",			// #15 ...BYOU/10m
	"���q���x:",			// #16 ...BYOU/10m
	"�ő���q�[�x:",		// #17 ...m
	"�������ː[�x:",		// #18
	"�΋���G:",			// #19 ...RI
	"�ΐ���:",			// #20 ...RI
	"�ΐ���:",			// #21 ...RI
	"�d�g�T�M�V:",			// #22
	"�d�g�Ə��V:",			// #23
	"�d�g�W�Q���u:",		// #24
	"���͎���:",			// #25 ...HUN
	"����:",			// #26
	"�⋋����:",			// #27 ...P
	"�o�����:",			// #28
};

char engName[][10] = {
	"�W�[�[��1",	// #0
	"�W�[�[��2",	// #1
	"�����^�[",	// #2
	"���q��",	// #3
	"�q��@1",	// #4
	"�q��@2",	// #5
	"������",	// #6
	"���㕔��",	// #7
	"�s��",		// #8
};

char loadName [][16] = {// toLoad    Load      str#
	"���͍ڋ@",	//   80       80        0
	"�����͐���@",	//   64       40        1
	"����@",	//   20       20        2
	"���㕔��",	//   08       08        3
	"���ꔚ���@",	//   04       04        4
	"���/����@",	//   a0     80/20       5
};

char countryName[][16] = {
	"���{",			// #0
	"�A�����J",		// #1
	"�C�M���X",		// #2
	"�h�C�c",		// #3
	"�\�A",			// #4
	"�I�����_",		// #5
	"�I�[�X�g�����A",// #6
	"�^�C",			// #7
	"�C���h",		// #8
	"����",			// #9
	"���̑�",		// #10
};

char armorName[][10] = {
	"�Ȃ�",		// #0
	"61cm�h��",	// #1
	"56cm�h��",	// #2
	"51cm�h��",	// #3
	"46cm�h��",	// #4
	"43cm�h��",	// #5
	"41cm�h��",	// #6
	"38cm�h��",	// #7
	"36cm�h��",	// #8
	"31cm�h��",	// #9
	"25cm�h��",	// #10
	"20cm�h��",	// #11
	"15cm�h��",	// #12
	"14cm�h��",	// #13
	"12cm�h��",	// #14
	"10cm�h��",	// #15
};

char armorTypeName[][10] = {
	"���S�h��",
	"�W���h��",
	"�Ȃ�",
};

char shootHighName[][8] = {
	"���[�x",	// #00  #F5
	"�[�[�x",	// #01  #F6
	"��[�x",	// #02  #F7
	"���[�x",	// #03  #F8
	"�O��",		// #04  #F9
	"�����",	// #05  #FA
	"���",		// #06  #FB
	"����",		// #07  #FC
	"����",		// #08  #FD
	"������",	// #09  #FE
	"������",	// #0A  #FF
	"�s��",		// #0B  #00
	"��",		// #0C  #01
};

char pTypeName[][16] = {
	"����",		// #0
	"�h�C�c����",	// #1
	"�h�C�c�񓯖�",	// #2
};