// A minimal Win32 console app

#include <stdio.h>
#include <string.h>
#include "dbf.h"
#include "unit.h"
#include "fleet.h"
#include "func.h"

static void dispVal(void);
static void dispVal2(void);
static void setVal(void);
static void setVal2(void);

void main() {
//	struct HEAD *hp =  &head;	// for debug
//	struct CHEAT *cp = &cheat;	//  for debug
	
	if (readFile() != EOF) {
		if (pref.mode) { // SENRYAKU
			dispVal();
			setVal();
			setVal2();
		} else {		// SENJUTSU
			dispVal2();
			setVal2();
		}
		writeFile();
	}
	sprintf(lineBuf, "[%s] - CheatDB2 version 1.01", pref.fName);
	msg(lineBuf);
	input();
	exit(0);
}

static void dispVal(void) {
	int i, j;
	unsigned short nI, tI;
	float x, y;
	char buf[64];

	sprintf(lineBuf, "%s\n", head.com);
	display(lineBuf);
	sprintf(lineBuf, "%s:%ld%s999999    ", 
			jpString[4], cheat.jInfo.point, jpString[10]);
	display(lineBuf);
	sprintf(lineBuf, "%s:%d%s99\n", jpString[5], 
			cheat.jInfo.isiki, jpString[10]);
	display(lineBuf);
	x = (float )(nI = cheat.jInfo.nIndust);
	y = (float )(tI = cheat.jInfo.tIndust);
	sprintf(lineBuf, "%s:(%d/%d)%d\%%%s100\%    ", jpString[6],
			nI, tI, (int )((x / y) * 100.0), jpString[10]);
	display(lineBuf);
	sprintf(lineBuf, "%s:%d%s%d\n", jpString[7], cheat.jInfo.techP, 
		jpString[10], pref.tp[0] == 9999 ? cheat.jInfo.techP : pref.tp[0]);
	display(lineBuf);
	
	for (i = 0;i < 20; i++) {
		j = cheat.jBuilt.plane[i].id;
		if (j < 525) memcpy(buf, unit001[j - 1].name, 20);
		else memcpy(buf, devUnit[j - 525 - 1].name, 20);
		buf[20] = '\0'; adjStrlen(buf, 20);
		if (cheat.jBuilt.plane[i].id != 0x0000) {
			sprintf(lineBuf, "%s:#%03d/%04d%s%s#500/1%s | ",
				buf, cheat.jBuilt.pNum[i], cheat.jBuilt.plane[i].days, 
				jpString[9], jpString[10], jpString[9]);
			display(lineBuf);
		} else if (cheat.jBuilt.ship[i].id != 0x0000) {
			display("                                           | ");
		} else  {
			continue;
		}
		
		if (cheat.jBuilt.ship[i].id != 0x0000) {
			memcpy(buf, cheat.jBuilt.snames[i].sName, 10);
			buf[10] = '\0'; adjStrlen(buf, 10);
			sprintf(lineBuf, "%s:%d%s%s1%s\n",
				buf, cheat.jBuilt.ship[i].days,
				jpString[9], jpString[10], jpString[9]);
			display(lineBuf);
		} else {
			display("\n");
		}
	}
}

static void dispVal2(void) {
	int i;
	static char *key[] = {"JPU1=", "USU1=", "UKU1=", "DEU1=", "RUU1=",
						  "NLU1=", "AUU1=", "THU1=", "INU1=", "CHU1=",};
						  
	sprintf(lineBuf, "%s\n", head.com);
	display(lineBuf);
	sprintf(lineBuf, "%s\n", jpString[38]);
	display(lineBuf);
	for(i = 0; i  < 10; i++) {
		sprintf(lineBuf, " %s%c\n", key[i], pref.unit1[i] ? 'Y':'N');
		display(lineBuf);
	}
	sprintf(lineBuf, "%s\n", jpString[39]);
	display(lineBuf);
}

static void setVal(void) {
	int i, j, c;

	// change country param of Japan
	cheat.jInfo.point = 999999L;
	cheat.jInfo.isiki = 99;
	cheat.jInfo.nIndust = cheat.jInfo.tIndust;
	
	// change built ship&plane of Japan
	for (i = 0;i < 20; i++) {
		if (cheat.jBuilt.plane[i].id != 0x0000) {
			cheat.jBuilt.plane[i].days = 1;
			cheat.jBuilt.pNum[i] = 500;
		}
		
		if (cheat.jBuilt.ship[i].id != 0x0000) {
			cheat.jBuilt.ship[i].days = 1;
		}
	}
	
	// change Tech Point Japan....USSR
	if (pref.tp[0] != 9999) cheat.jInfo.techP = pref.tp[0]; // Japan
	for (i = 1; i < 5; i++)
		if (pref.tp[i] != 9999) cheat.countrys[i - 1].techP = pref.tp[i];

	// change Base param
	for (i = 0; i < 223; i++) {
		struct BASE *bp = &(cheat.base[i]);
		
		c = bp->country;
		if (c > 9) continue;
		if (pref.base1[c]) { // goods,wDays&transShip
			bp->goods = 60000; bp->wDays = 0;
			for(j = 0; j < 8; j++) 
				if ((bp->fc[j].stat & 0x0f) == 2 && bp->fc[j].type == 2) {
					if (bp->transShip < 5) bp->transShip = 5; 
					break;
			}
		}
		if (pref.base1[c]) 
			for(j = 0; j < 8; j++) 
				if ((bp->fc[j].stat & 0x0f) == 2) {
					bp->fc[j].stat = 2; // 0x82->0x02, repair  
					bp->fc[j].end50 = 12500 / 50;// endrunce of Base facility
					bp->fc[j].endrunce = 12500;
				}
	}
}

void  setVal2() {
	int i,c,j;
	static struct ELEMENT *es[10] = {JPelem, USelem, UKelem, DEelem, RUelem,
								     NLelem, AUelem, THelem, INelem, CHelem,};
	struct ELEMENT *ep;							     
	static int eSize[10] = {sizeof(JPelem)/sizeof(struct ELEMENT),
		sizeof(USelem)/sizeof(struct ELEMENT), sizeof(UKelem)/sizeof(struct ELEMENT),
		sizeof(DEelem)/sizeof(struct ELEMENT), sizeof(RUelem)/sizeof(struct ELEMENT),
		sizeof(NLelem)/sizeof(struct ELEMENT), sizeof(AUelem)/sizeof(struct ELEMENT),
		sizeof(THelem)/sizeof(struct ELEMENT), sizeof(INelem)/sizeof(struct ELEMENT),
		sizeof(CHelem)/sizeof(struct ELEMENT),};
	struct UNIT *up;
		
	// change Unit param
	for(c = 0; c < 10; c++) {
		if (pref.unit1[c] == 0) continue;
		ep = es[c];
		for(i = 0; i < eSize[c]; i++) {
			if (ep[i].pad00 == 0) continue; // pad00: unknown flag
			j = ep[i].type;
			ep[i].pract = 250; ep[i].spirit = 99; // Army,Air,Sub&Ship
			if (j < 525) up = &(unit001[j]);	// Type in unit001.db2
			else up = &(devUnit[j - 525]);		// developed Type
			switch(up->unitID) {
			case 0x00:// No Unit
				break;
			case 0x01:// Army
				ep[i].endrunce[0] = 500;
				break;
			case 0x20: case 0x21: case 0x22: case 0x23: case 0x24: case 0x25:
			case 0x26:// Sub
				ep[i].endrunce[0] = up->endrunce;
				for (j = 0; j < 7; j++) 
					if(up->wepon[j].weponID >= 145 && up->wepon[j].armoORtower != 0xff)
						ep[i].armoNum[j].n[0] = up->wepon[j].armoORtower;
				ep[i].goods = up->supply;
				ep[i].fuel = up->distance;
				ep[i].accident = 0;
				ep[i].decSpeed1 = 0;
				ep[i].decSpeed2 = 0;
				break;
			case 0x80: case 0x81: case 0x82: case 0x83: case 0x84: case 0x85:
			case 0x86: case 0x87: case 0x88: case 0x89: case 0x8a: case 0x8b:
			case 0x8c: case 0x8d: case 0x8e: case 0x8f: case 0x90: case 0x91:// Ship
				for (j = 0; j < 5; j++)
					ep[i].endrunce[j] = up->endrunce;
				for (j = 0; j < 7; j++) 
					if(up->wepon[j].weponID >= 145 && up->wepon[j].armoORtower != 0xff)
						ep[i].armoNum[j].n[0] = up->wepon[j].armoORtower;
				ep[i].goods = up->supply;
				ep[i].fuel = up->distance;
				ep[i].accident = 0;
				ep[i].decSpeed1 = 0;
				ep[i].decSpeed2 = 0;
				break;
			}
		}
	}
}
