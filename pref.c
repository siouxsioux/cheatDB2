// A minimal Win32 console app

#include <stdio.h>
#include <string.h>
#include "dbf.h"
#include "unit.h"
#include "fleet.h"
#include "func.h"

static int scanLine(char *);
static int getCidx(char *);
static FILE *fp;

int checkPref(void) {
	if ((fp = fopen("cheatprf.txt" ,"r")) == NULL) {
		return 1;
	} else {
		fclose(fp);
		return 0;
	}
}

int makePref(void) {
	if ((fp = fopen("cheatprf.txt" ,"w")) == NULL) {
		return 1;
	} else {
		fputs("FN=user01.db2 *ファイル名 \"FN=user##.db2\" [##=01-10]\n", fp);
		fputs("JPTP=9999 *日本技術力P \"JPTP=####\" [####=0-3000,9999=変更なし]\n" ,fp);
		fputs("USTP=9999 *米国技術力P \"USTP=####\" [####=0-3000,9999=変更なし]\n" ,fp);
		fputs("UKTP=9999 *英国技術力P \"UKTP=####\" [####=0-3000,9999=変更なし]\n" ,fp);
		fputs("DETP=9999 *独国技術力P \"DETP=####\" [####=0-3000,9999=変更なし]\n" ,fp);
		fputs("RUTP=9999 *ソ連技術力P \"RUTP=####\" [####=0-3000,9999=変更なし]\n" ,fp);
		fputs("JPB1=N *日本基地情報1 \"JPB1=Y/N\" [Y=備蓄P=60000,輸送船=5/N=変更なし]\n" ,fp);
		fputs("USB1=N *米国基地情報1 \"USB1=Y/N\" [Y=備蓄P=60000,輸送船=5/N=変更なし]\n" ,fp);
		fputs("UKB1=N *英国基地情報1 \"UKB1=Y/N\" [Y=備蓄P=60000,輸送船=5/N=変更なし]\n" ,fp);
		fputs("DEB1=N *独国基地情報1 \"DEB1=Y/N\" [Y=備蓄P=60000,輸送船=5/N=変更なし]\n" ,fp);
		fputs("RUB1=N *ソ連基地情報1 \"RUB1=Y/N\" [Y=備蓄P=60000,輸送船=5/N=変更なし]\n" ,fp);
		fputs("NLB1=N *蘭国基地情報1 \"NLB1=Y/N\" [Y=備蓄P=60000,輸送船=5/N=変更なし]\n" ,fp);
		fputs("AUB1=N *豪州基地情報1 \"AUB1=Y/N\" [Y=備蓄P=60000,輸送船=5/N=変更なし]\n" ,fp);
		fputs("THB1=N *タイ基地情報1 \"THB1=Y/N\" [Y=備蓄P=60000,輸送船=5/N=変更なし]\n" ,fp);
		fputs("INB1=N *印度基地情報1 \"INB1=Y/N\" [Y=備蓄P=60000,輸送船=5/N=変更なし]\n" ,fp);
		fputs("CHB1=N *中国基地情報1 \"CHB1=Y/N\" [Y=備蓄P=60000,輸送船=5/N=変更なし]\n" ,fp);
#if 0
		fputs("JPB2=N *日本基地情報1 \"JPB2=Y/N\" [Y=施設耐久力=12500/N=変更なし]\n" ,fp);
		fputs("USB2=N *米国基地情報1 \"USB2=Y/N\" [Y=施設耐久力=12500/N=変更なし]\n" ,fp);
		fputs("UKB2=N *英国基地情報1 \"UKB2=Y/N\" [Y=施設耐久力=12500/N=変更なし]\n" ,fp);
		fputs("DEB2=N *独国基地情報1 \"DEB2=Y/N\" [Y=施設耐久力=12500/N=変更なし]\n" ,fp);
		fputs("RUB2=N *ソ連基地情報1 \"RUB2=Y/N\" [Y=施設耐久力=12500/N=変更なし]\n" ,fp);
		fputs("NLB2=N *蘭国基地情報1 \"NLB2=Y/N\" [Y=施設耐久力=12500/N=変更なし]\n" ,fp);
		fputs("AUB2=N *豪州基地情報1 \"AUB2=Y/N\" [Y=施設耐久力=12500/N=変更なし]\n" ,fp);
		fputs("THB2=N *タイ基地情報1 \"THB2=Y/N\" [Y=施設耐久力=12500/N=変更なし]\n" ,fp);
		fputs("INB2=N *印度基地情報1 \"INB2=Y/N\" [Y=施設耐久力=12500/N=変更なし]\n" ,fp);
		fputs("CHB2=N *中国基地情報1 \"CHB2=Y/N\" [Y=施設耐久力=12500/N=変更なし]\n" ,fp);
#endif
		fputs("JPU1=N *日本UNIT情報1 \"JPU1=Y/N\" [Y=練度=A,士気=99,etc/N=変更なし]\n" ,fp);
		fputs("USU1=N *米国UNIT情報1 \"USU1=Y/N\" [Y=練度=A,士気=99,etc/N=変更なし]\n" ,fp);
		fputs("UKU1=N *英国UNIT情報1 \"UKU1=Y/N\" [Y=練度=A,士気=99,etc/N=変更なし]\n" ,fp);
		fputs("DEU1=N *独国UNIT情報1 \"DEU1=Y/N\" [Y=練度=A,士気=99,etc/N=変更なし]\n" ,fp);
		fputs("RUU1=N *ソ連UNIT情報1 \"RUU1=Y/N\" [Y=練度=A,士気=99,etc/N=変更なし]\n" ,fp);
		fputs("NLU1=N *蘭国UNIT情報1 \"NLU1=Y/N\" [Y=練度=A,士気=99,etc/N=変更なし]\n" ,fp);
		fputs("AUU1=N *豪州UNIT情報1 \"AUU1=Y/N\" [Y=練度=A,士気=99,etc/N=変更なし]\n" ,fp);
		fputs("THU1=N *タイUNIT情報1 \"THU1=Y/N\" [Y=練度=A,士気=99,etc/N=変更なし]\n" ,fp);
		fputs("INU1=N *印度UNIT情報1 \"INU1=Y/N\" [Y=練度=A,士気=99,etc/N=変更なし]\n" ,fp);
		fputs("CHU1=N *中国UNIT情報1 \"CHU1=Y/N\" [Y=練度=A,士気=99,etc/N=変更なし]\n" ,fp);
		fclose(fp);
		return 0;
	}
}

int readPref(void) {
	char s[256];
	
	if ((fp = fopen("cheatprf.txt", "r")) == NULL) {
		sprintf(lineBuf, "%s:chaetprf.txt cannot open\n", jpString[0]);
		msg(lineBuf);
		return 1;
		}
	while (NULL != fgets(s, 256, fp)) {
		if (scanLine(s)) {
			sprintf(lineBuf, "%s:%s\n",jpString[1], s);
			msg(lineBuf);
			return 1;
		}
	}
	fclose(fp);
	return 0;
}

static int scanLine(char *s) {
	int i, c;
	char fn[14];
//	volatile long key;
	
	if (strlen(s) < 6) return 1; // |XXXX=n|
	if (strncmp("FN=", s, 3) == 0) {
		for (i = 1; i <= 10; i++) {
			sprintf(fn, "user%02d.db2", i);
			if (strncmp(fn, s + 3, 10) == 0) {
				strcpy(pref.fName, fn);
				return 0;
			}
		}
		return 1;
	} else if (strncmp("TP=", s + 2, 3) == 0) {
		if ((c = getCidx(s)) == -1) return 1;
		i = atoi(s + 5);
		if ((0 <= i && i <= 3000) || i == 9999) {
			pref.tp[c] = i;
			return 0;
		} else {
			return 1;
		}
	} else if (strncmp("B1=", s + 2, 3) == 0) {
		if ((c = getCidx(s)) == -1) return 1;
		if (s[5] == 'Y'|| s[5] == 'y') {
			pref.base1[c] = 1;
			return 0;
		} else if (s[5] == 'N'|| s[5] == 'n') {
			pref.base1[c] = 0;
			return 0;
		} else {
			return 1;
		}
	} else if (strncmp("U1=", s + 2, 3) == 0) {
		if ((c = getCidx(s)) == -1) return 1;
		if (s[5] == 'Y'|| s[5] == 'y') {
			pref.unit1[c] = 1;
			return 0;
		} else if (s[5] == 'N'|| s[5] == 'n') {
			pref.unit1[c] = 0;
			return 0;
		} else {
			return 1;
		}
	} else {
		return 1;
	}
}	 

static int getCidx(char *s) {
	if (strncmp("JP", s, 2) == 0) return 0;
	else if (strncmp("US", s, 2) == 0) return 1;
	else if (strncmp("UK", s, 2) == 0) return 2;
	else if (strncmp("DE", s, 2) == 0) return 3;
	else if (strncmp("RU", s, 2) == 0) return 4;
	else if (strncmp("NL", s, 2) == 0) return 5;
	else if (strncmp("AU", s, 2) == 0) return 6;
	else if (strncmp("TH", s, 2) == 0) return 7;
	else if (strncmp("IN", s, 2) == 0) return 8;
	else if (strncmp("CH", s, 2) == 0) return 9;
	else return -1;
}		