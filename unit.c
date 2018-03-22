// A minimal Win32 console app

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dbf.h"
#include "unit.h"
#include "fleet.h"
#include "func.h"

static int readWpn(void),readWpnGun(void),readU001(void);
static long expand(unsigned char *, unsigned char *, long);
static void printElem(struct ELEMENT *,int);
static void testElem(struct ELEMENT *e, int num);

int readUnit(FILE   *fp)
{
	long size;
	char *buf;
	
	if (1 != fread(&size, sizeof(long), 1, fp)) {
		sprintf(lineBuf, "%s:Cannot read JP unit size\n", jpString[0]);
		msg(lineBuf);
		return EOF;
	}
	// read JP ship&plane&army
	buf = malloc(size);
	if (buf == NULL)  {
		sprintf(lineBuf, "%s:at JP Unit\n", jpString[2]);
		msg(lineBuf);
		return EOF;
	}
	if (1 != fread(buf, size, 1, fp)) {
		sprintf(lineBuf, "%s:Cannot Read JP ship&plane&army\n", jpString[0]);
		msg(lineBuf);
		free(buf);
		return EOF;
	}
	size = expand((unsigned char *)buf, (unsigned char *)JPelem, size);
	if (size != sizeof(JPelem)) {
		free(buf);
		sprintf(lineBuf, "%s:JP Unit size ERROR!(%ld/%ld)\n", jpString[0], size, sizeof(JPelem));
		msg(lineBuf);
		return EOF;
	}
	free(buf);

	if (1 != fread(&size, sizeof(long), 1, fp)) {
		sprintf(lineBuf, "%s:Cannot read US unit size\n", jpString[0]);
		msg(lineBuf);
		return EOF;
	}
	// read US ship&plane&army
	buf = malloc(size);
	if (buf == NULL)  {
		sprintf(lineBuf, "%s:at US Unit\n", jpString[2]);
		msg(lineBuf);
		return EOF;
	}
	if (1 != fread(buf, size, 1, fp)) {
		sprintf(lineBuf, "%s:Cannot Read US ship&plane&army\n", jpString[0]);
		msg(lineBuf);
		free(buf);
		return EOF;
	}
	size = expand((unsigned char *)buf, (unsigned char *)USelem, size);
	if (size != sizeof(USelem)) {
		free(buf);
		sprintf(lineBuf, "%s:US Unit size ERROR!(%ld/%ld)\n", jpString[0], size, sizeof(USelem));
		msg(lineBuf);
		return EOF;
	}
	free(buf);

	if (1 != fread(&size, sizeof(long), 1, fp)) {
		sprintf(lineBuf, "%s:Cannot read UK unit size\n", jpString[0]);
		msg(lineBuf);
		return EOF;
	}
	// read UK ship&plane&army
	buf = malloc(size);
	if (buf == NULL)  {
		sprintf(lineBuf, "%s:at UK Unit\n", jpString[2]);
		msg(lineBuf);
		return EOF;
	}
	if (1 != fread(buf, size, 1, fp)) {
		sprintf(lineBuf, "%s:Cannot Read UK ship&plane&army\n", jpString[0]);
		msg(lineBuf);
		free(buf);
		return EOF;
	}
	size = expand((unsigned char *)buf, (unsigned char *)UKelem, size);
	if (size != sizeof(UKelem)) {
		free(buf);
		sprintf(lineBuf, "%s:UK Unit size ERROR!(%ld/%ld)\n", jpString[0], size, sizeof(UKelem));
		msg(lineBuf);
		return EOF;
	}
	free(buf);

	if (1 != fread(&size, sizeof(long), 1, fp)) {
		sprintf(lineBuf, "%s:Cannot read DE unit size\n", jpString[0]);
		msg(lineBuf);
		return EOF;
	}
	// read DE ship&plane&army
	buf = malloc(size);
	if (buf == NULL)  {
		sprintf(lineBuf, "%s:at DE Unit\n", jpString[2]);
		msg(lineBuf);
		return EOF;
	}
	if (1 != fread(buf, size, 1, fp)) {
		sprintf(lineBuf, "%s:Cannot Read DE ship&plane&army\n", jpString[0]);
		msg(lineBuf);
		free(buf);
		return EOF;
	}
	size = expand((unsigned char *)buf, (unsigned char *)DEelem, size);
	if (size != sizeof(DEelem)) {
		free(buf);
		sprintf(lineBuf, "%s:DE Unit size ERROR!(%ld/%ld)\n", jpString[0], size, sizeof(DEelem));
		msg(lineBuf);
		return EOF;
	}
	free(buf);

	
	if (1 != fread(&size, sizeof(long), 1, fp)) {
		sprintf(lineBuf, "%s:Cannot read RU unit size\n", jpString[0]);
		msg(lineBuf);
		return EOF;
	}
	// read RU plane&army
	buf = malloc(size);
	if (buf == NULL)  {
		sprintf(lineBuf, "%s:at JP Unit\n", jpString[2]);
		msg(lineBuf);
		return EOF;
	}
	if (1 != fread(buf, size, 1, fp)) {
		sprintf(lineBuf, "%s:Cannot Read RU plane&army\n", jpString[0]);
		msg(lineBuf);
		free(buf);
		return EOF;
	}
	size = expand((unsigned char *)buf, (unsigned char *)RUelem, size);
	if (size != sizeof(RUelem)) {
		free(buf);
		sprintf(lineBuf, "%s:RU Unit size ERROR!(%ld/%ld)\n", jpString[0], size, sizeof(RUelem));
		msg(lineBuf);
		return EOF;
	}
	free(buf);

	if (1 != fread(&size, sizeof(long), 1, fp)) {
		sprintf(lineBuf, "%s:Cannot read NL unit size\n", jpString[0]);
		msg(lineBuf);
		return EOF;
	}
	// read NL army
	buf = malloc(size);
	if (buf == NULL)  {
		sprintf(lineBuf, "%s:at NL Unit\n", jpString[2]);
		msg(lineBuf);
		return EOF;
	}
	if (1 != fread(buf, size, 1, fp)) {
		sprintf(lineBuf, "%s:Cannot Read NL army\n", jpString[0]);
		msg(lineBuf);
		free(buf);
		return EOF;
	}
	size = expand((unsigned char *)buf, (unsigned char *)NLelem, size);
	if (size != sizeof(NLelem)) {
		free(buf);
		sprintf(lineBuf, "%s:NL Unit size ERROR!(%ld/%ld)\n", jpString[0], size, sizeof(NLelem));
		msg(lineBuf);
		return EOF;
	}
	free(buf);
	
	if (1 != fread(&size, sizeof(long), 1, fp)) {
		sprintf(lineBuf, "%s:Cannot read AU unit size\n", jpString[0]);
		msg(lineBuf);
		return EOF;
	}
	// read AU army
	buf = malloc(size);
	if (buf == NULL)  {
		sprintf(lineBuf, "%s:at AU Unit\n", jpString[2]);
		msg(lineBuf);
		return EOF;
	}
	if (1 != fread(buf, size, 1, fp)) {
		sprintf(lineBuf, "%s:Cannot Read AU army\n", jpString[0]);
		msg(lineBuf);
		free(buf);
		return EOF;
	}
	size = expand((unsigned char *)buf, (unsigned char *)AUelem, size);
	if (size != sizeof(AUelem)) {
		free(buf);
		sprintf(lineBuf, "%s:AU Unit size ERROR!(%ld/%ld)\n", jpString[0], size, sizeof(AUelem));
		msg(lineBuf);
		return EOF;
	}
	free(buf);

	if (1 != fread(&size, sizeof(long), 1, fp)) {
		sprintf(lineBuf, "%s:Cannot read TH unit size\n", jpString[0]);
		msg(lineBuf);
		return EOF;
	}
	// read TH army
	buf = malloc(size);
	if (buf == NULL)  {
		sprintf(lineBuf, "%s:at TH Unit\n", jpString[2]);
		msg(lineBuf);
		return EOF;
	}
	if (1 != fread(buf, size, 1, fp)) {
		sprintf(lineBuf, "%s:Cannot Read TH army\n", jpString[0]);
		msg(lineBuf);
		free(buf);
		return EOF;
	}
	size = expand((unsigned char *)buf, (unsigned char *)THelem, size);
	if (size != sizeof(THelem)) {
		free(buf);
		sprintf(lineBuf, "%s:TH Unit size ERROR!(%ld/%ld)\n", jpString[0], size, sizeof(THelem));
		msg(lineBuf);
		return EOF;
	}
	free(buf);
	
	if (1 != fread(&size, sizeof(long), 1, fp)) {
		sprintf(lineBuf, "%s:Cannot read IN unit size\n", jpString[0]);
		msg(lineBuf);
		return EOF;
	}
	// read IN army
	buf = malloc(size);
	if (buf == NULL)  {
		sprintf(lineBuf, "%s:at IN Unit\n", jpString[2]);
		msg(lineBuf);
		return EOF;
	}
	if (1 != fread(buf, size, 1, fp)) {
		sprintf(lineBuf, "%s:Cannot Read IN army\n", jpString[0]);
		msg(lineBuf);
		free(buf);
		return EOF;
	}
	size = expand((unsigned char *)buf, (unsigned char *)INelem, size);
	if (size != sizeof(INelem)) {
		free(buf);
		sprintf(lineBuf, "%s:IN Unit size ERROR!(%ld/%ld)\n", jpString[0], size, sizeof(INelem));
		msg(lineBuf);
		return EOF;
	}
	free(buf);
	
	if (1 != fread(&size, sizeof(long), 1, fp)) {
		sprintf(lineBuf, "%s:Cannot read CH unit size\n", jpString[0]);
		msg(lineBuf);
		return EOF;
	}
	// read CH army
	buf = malloc(size);
	if (buf == NULL)  {
		sprintf(lineBuf, "%s:at CH Unit\n", jpString[2]);
		msg(lineBuf);
		return EOF;
	}
	if (1 != fread(buf, size, 1, fp)) {
		sprintf(lineBuf, "%s:Cannot Read CH army\n", jpString[0]);
		msg(lineBuf);
		free(buf);
		return EOF;
	}
	size = expand((unsigned char *)buf, (unsigned char *)CHelem, size);
	if (size != sizeof(CHelem)) {
		free(buf);
		sprintf(lineBuf, "%s:CH Unit size ERROR!(%ld/%ld)\n", jpString[0], size, sizeof(CHelem));
		msg(lineBuf);
		return EOF;
	}
	free(buf);
	
	if (1 != fread(&size, sizeof(long), 1, fp)) {
		sprintf(lineBuf, "%s:Cannot read XX unit size\n", jpString[0]);
		msg(lineBuf);
		return EOF;
	}
	// read XX Unit
	fileMap.XXelem.size = size;
	if (NULL == (fileMap.XXelem.buf = malloc(fileMap.XXelem.size))) {
		sprintf(lineBuf, "%s:in XX Unit\n", jpString[2]);
		msg(lineBuf);
		return EOF;
	}
	if (1 != fread(fileMap.XXelem.buf, fileMap.XXelem.size, 1, fp)) {
		sprintf(lineBuf, "%s:Cannot Read XX unit\n", jpString[0]);
		msg(lineBuf);
		free(buf);
		return EOF;
	}
	
	if (readWpnGun()) return EOF;		// read wpgun.db2
	if (readWpn()) return EOF;			// read wpn.db2
	if (readU001()) return EOF; 		// reead unit001.db2

//	testElem(JPelem, sizeof(JPelem)/sizeof(struct ELEMENT));
//	printElem(DEelem, sizeof(DEelem)/sizeof(struct ELEMENT));
	
	return 0;
}

static int readWpnGun(void) {
//	int i;
	FILE *fp;
//	FILE *o;
//	char buf[16];
	
	if ((fp = fopen("wpgun.db2", "rb")) == NULL) {
		sprintf(lineBuf, "%s\n", jpString[17]);
		msg(lineBuf);
		return EOF;
		}
	if (1 != fread(&wpnGun, sizeof(wpnGun), 1, fp)) {
		sprintf(lineBuf, "%s\n", jpString[18]);
		msg(lineBuf);
		fclose(fp);
		return EOF;
	}
	fclose(fp);
#if 0	
	o = fopen("out.txt", "w");
	for (i = 0; i < 144; i++) {
		fprintf(o, "%02x ", wpnGun[i].id);
		makeGunName(i, buf);
		fprintf(o, "%s ", buf);
		fprintf(o, "%02d ", wpnGun[i].range);
		fprintf(o, "%03d ", wpnGun[i].time);
		fprintf(o, "[%03d", wpnGun[i].eArmor.power);
		fprintf(o, "/%02d", wpnGun[i].eArmor.suf);
		fprintf(o, "/%02d", wpnGun[i].eArmor.gnd);
		fprintf(o, "/%02d", wpnGun[i].eArmor.sub);
		fprintf(o, "/%02d", wpnGun[i].eArmor.airL);
		fprintf(o, "/%02d", wpnGun[i].eArmor.airM);
		fprintf(o, "/%02d]", wpnGun[i].eArmor.airH);
		fprintf(o, "[%03d", wpnGun[i].eNormal.power);
		fprintf(o, "/%02d", wpnGun[i].eNormal.suf);
		fprintf(o, "/%02d", wpnGun[i].eNormal.gnd);
		fprintf(o, "/%02d", wpnGun[i].eNormal.sub);
		fprintf(o, "/%02d", wpnGun[i].eNormal.airL);
		fprintf(o, "/%02d", wpnGun[i].eNormal.airM);
		fprintf(o, "/%02d]", wpnGun[i].eNormal.airH);
		fprintf(o, "[%03d", wpnGun[i].eAAir.power);
		fprintf(o, "/%02d", wpnGun[i].eAAir.suf);
		fprintf(o, "/%02d", wpnGun[i].eAAir.gnd);
		fprintf(o, "/%02d", wpnGun[i].eAAir.sub);
		fprintf(o, "/%02d", wpnGun[i].eAAir.airL);
		fprintf(o, "/%02d", wpnGun[i].eAAir.airM);
		fprintf(o, "/%02d]", wpnGun[i].eAAir.airH);
		fprintf(o, "\n");
	}
	fclose(o);
#endif	
	return 0;
}

static int readWpn(void) {
	FILE *fp;
	
	if ((fp = fopen("wpn.db2", "rb")) == NULL) {
		sprintf(lineBuf, "%s\n", jpString[15]);
		msg(lineBuf);
		return EOF;
		}
	if (1 != fread(&armo, sizeof(armo), 1, fp)) {
		sprintf(lineBuf, "%s\n", jpString[16]);
		msg(lineBuf);
		fclose(fp);
		return EOF;
	}
	fclose(fp);
	return 0;
}

static int readU001(void) {
	FILE *fp;
//	FILE *o;
//	int i;
//	char buf[21];
	
	if ((fp = fopen("unit001.db2", "rb")) == NULL) {
		sprintf(lineBuf, "%s\n", jpString[30]);
		msg(lineBuf);
		return EOF;
		}
	if (1 != fread(&unit001, sizeof(unit001), 1, fp)) {
		sprintf(lineBuf, "%s\n", jpString[31]);
		msg(lineBuf);
		fclose(fp);
		return EOF;
	}
	fclose(fp);
#if 0
	buf[20] = '\0';
	fp = fopen("out.txt", "w");
	for(i = 0; i < 525; i++) {
		memcpy(buf, unit001[i].name, 20);
//		if(unit001[i].toLoadType)
//			fprintf(fp, "%s:%02x\n", buf, unit001[i].toLoadType);
		if(unit001[i].loadType)
			fprintf(fp, "%s:%02x\n", buf, unit001[i].loadType);
	}
	fclose(fp);
#endif
	return 0;
}

void makeGunName(int idx, char *s) {
	int i;
	char buf[16];
	
	sprintf(s, "%d", wpnGun[idx].size);
	i = strlen(s);
	s[i] = s[i - 1];
	s[i - 1] = '.';
	s[i + 1] = '\0';
	strcat(s, "cm");
	sprintf(buf, "%d", wpnGun[idx].length);
	strcat(s, buf);
	strcat(s, jpString[19]);
}

void adjStrlen(char *s, int len) {
	int  i, end;
	
	end = strlen(s);
	for (i = end; i < len; i++)
		s[i] = ' ';
	s[len] = '\0';
}

int getEngID(struct UNIT *u)
{
	if (u->lowFuel == 7 && u->midFuel == 10 && u->fulFuel == 30 &&
		u->uLowFuel == 0 && u->uMidFuel == 0 && u->uFulFuel == 0)
		return 0;// Gezel-1
	else if (u->lowFuel == 10 && u->midFuel == 10 && u->fulFuel == 10 &&
		u->uLowFuel == 0 && u->uMidFuel == 0 && u->uFulFuel == 0)
		return 1;// Gezel-2
	else if (u->lowFuel == 7 && u->midFuel == 10 && u->fulFuel == 15 &&
		u->uLowFuel == 0 && u->uMidFuel == 0 && u->uFulFuel == 0)
		return 2;// Walter
	else if (u->lowFuel == 0 && u->midFuel == 0 && u->fulFuel == 0 &&
		u->uLowFuel == 0 && u->uMidFuel == 0 && u->uFulFuel == 0)
		return 3;// Atomic
	else if (u->lowFuel == 7 && u->midFuel == 10 && u->fulFuel == 20 &&
		u->uLowFuel == 0 && u->uMidFuel == 0 && u->uFulFuel == 0)
		return 4;// Air-1
	else if (u->lowFuel == 5 && u->midFuel == 10 && u->fulFuel == 15 &&
		u->uLowFuel == 0 && u->uMidFuel == 0 && u->uFulFuel == 0)
		return 5;// Air-2
	else if (u->lowFuel == 7 && u->midFuel == 10 && u->fulFuel == 30 &&
		u->uLowFuel == 5 && u->uMidFuel == 10 && u->uFulFuel == 30)
		return 6;// Sub
	else if (u->lowFuel == 5 && u->midFuel == 10 && u->fulFuel == 30 &&
		u->uLowFuel == 0 && u->uMidFuel == 0 && u->uFulFuel == 0)
		return 7;// Grand
	else 
		return 8;
}

void setEngine(struct UNIT *u, int idx)
{
	switch(idx) {
		case 0: // Gezel-1
	    	u->lowFuel = 7; u->midFuel = 10; u->fulFuel = 30;
			u->uLowFuel = 0; u->uMidFuel = 0; u->uFulFuel = 0;
			break;
		case 1: // Gezel-2
			u->lowFuel = 10; u->midFuel = 10; u->fulFuel = 10;
			u->uLowFuel = 0; u->uMidFuel = 0; u->uFulFuel = 0;
			break;
		case 2: // Walter
			u->lowFuel = 7; u->midFuel = 10; u->fulFuel = 15;
			u->uLowFuel = 0; u->uMidFuel = 0; u->uFulFuel = 0;
			break;
		case 3: // Atomic
			u->lowFuel = 0; u->midFuel = 0; u->fulFuel = 0;
			u->uLowFuel = 0; u->uMidFuel = 0; u->uFulFuel = 0;
			break;
		case 4: // Air-1
			u->lowFuel = 7; u->midFuel = 10; u->fulFuel = 20;
			u->uLowFuel = 0; u->uMidFuel = 0; u->uFulFuel = 0;
			break;
		case 5: // Air-2
			u->lowFuel = 5; u->midFuel = 10; u->fulFuel = 15;
			u->uLowFuel = 0; u->uMidFuel = 0; u->uFulFuel = 0;
			break;
		case 6: // Sub
			u->lowFuel = 7; u->midFuel = 10; u->fulFuel = 30;
			u->uLowFuel = 5; u->uMidFuel = 10; u->uFulFuel = 30;
			break;
		case 7: // Grand
			u->lowFuel = 5; u->midFuel = 10; u->fulFuel = 30;
			u->uLowFuel = 0; u->uMidFuel = 0; u->uFulFuel = 0;
			break;
	}
}

int getLoadID(struct UNIT *u) {

	if((0x40 <= u->unitID && u->unitID < 0x80) || u->unitID == 0x01) {
		switch(u->toLoadType) { // Plane or Army
			case 0x80:return 0;
			case 0x64:return 1;
			case 0x20:return 2;
			case 0x08:return 3;
			case 0x04:return 4;
			case 0xa0:return 5;
		}
	} else {
		switch(u->loadType) { // Sub or Ship
			case 0x80:return 0;
			case 0x40:return 1;
			case 0x20:return 2;
			case 0x08:return 3;
			case 0x04:return 4;
		}
	}
	return -1;
}

int setLoadType(struct UNIT *u, int idx) {

	if((0x40 <= u->unitID && u->unitID < 0x80) || u->unitID == 0x01) {
		switch(idx) { // Plane or Army
			case 0: u->toLoadType = 0x80; break;
			case 1: u->toLoadType = 0x64; break;
			case 2: u->toLoadType = 0x20; break;
			case 3: u->toLoadType = 0x08; break;
			case 4: u->toLoadType = 0x04; break;
			case 5: u->toLoadType = 0x0a; break;
		}
	} else {
		switch(idx) { // Sub or Ship
			case 0:u->loadType = 0x80; break;
			case 1:u->loadType = 0x40; break;
			case 2:u->loadType = 0x20; break;
			case 3:u->loadType = 0x08; break;
			case 4:u->loadType = 0x04; break;
		}
	}
	return -1;
}

static long expand(unsigned char *buf, unsigned char *u, long bSize)
{
	long i, j, size;
	unsigned char buf3[3];
	
	for(i = 0, size = 0; i < bSize - 2; i++) {
		buf3[0] = buf[i];
		buf3[1] = buf[i + 1];
		buf3[2] = buf[i + 2];
		if (buf3[0] == buf3[1]) {
			for(j = 0; j < buf3[2]; j++)
				u[size + j] = buf3[0];
			size += buf3[2];
			i += 2;
		} else {
			u[size] = buf[i];
			size++;
		}
	}
	return size;
}

static void printElem(struct ELEMENT *e, int num) {
	int i, j;
	FILE *fp1; //,*fp2, *fp3;
	
	fp1 = fopen("out1.txt", "w");
//	fp2 = fopen("out2.txt", "w");
//	fp3 = fopen("out3.txt", "w");
	for (i = 0; i < num; i++) {
		fprintf(fp1, "%02x", e[i].pad00);
		fprintf(fp1, ":%04x", e[i].type);
		memcpy(lineBuf, e[i].name, 20);
		adjStrlen(lineBuf, 20);
		fprintf(fp1, "%s", lineBuf);
		for(j = 0; j < 2; j++) 
			fprintf(fp1, " %02x", e[i].pad01[j]);
		for(j = 0; j < 5; j++) 
			fprintf(fp1, ":%05d", e[i].endrunce[j]);
		for(j = 0; j < 7; j++) 
			fprintf(fp1, ":%05d", e[i].wEndrunce[j]);
		for(j = 0; j < 5; j++) 
			fprintf(fp1, " %02x", e[i].pad02[j]);
//		fprintf(fp1, "\n");

//		fprintf(fp2, "%s", lineBuf);
		fprintf(fp1, ":%03d", e[i].pract);
		fprintf(fp1, ":%02d", e[i].spirit);
		fprintf(fp1, ":%05d", e[i].fuel);
		fprintf(fp1, ":%05d", e[i].goods);
		for(j = 0; j < 5; j++)
			fprintf(fp1, " %02x", e[i].pad03[j]);
		fprintf(fp1, ":%02x", e[i].accident);
		for(j = 0; j < 2; j++)
			fprintf(fp1, " %02x", e[i].pad04[j]);
		fprintf(fp1, ":%03d", e[i].decSpeed1);
		fprintf(fp1, ":%03d", e[i].decSpeed2);
		fprintf(fp1, ":%03d", e[i].incSpeed);
		for(j = 0; j < 9; j++)
			fprintf(fp1, " %02x", e[i].pad05[j]);
		for(j = 0; j < 7; j++) 
			fprintf(fp1, ":%03d", e[i].gunNum[j]);
		for(j = 0; j < 7; j++) 
			fprintf(fp1, "(%03d,%03d,%03d)", e[i].armoNum[j].n[0],
				e[i].armoNum[j].n[1],e[i].armoNum[j].n[2]);
		for(j = 0; j < 12; j++)
			fprintf(fp1, " %02x", e[i].pad06[j]);
		fprintf(fp1, "\n");
	}
	fclose(fp1);
//	fclose(fp2);
//	fclose(fp3);
}

#if 0
static void testElem(struct ELEMENT *e, int num) {
	int i, j;
	FILE *fp1;
	static int b = 0;
	static char z[8][5] = {
	{0x10, 1, 2, 0, 0,},
	{0x20, 1, 2, 0, 0,},
	{0x30, 1, 2, 0, 0,},
	{0x40, 1, 2, 0, 0,},
	{0x50, 1, 2, 0, 0,},
	{0x60, 1, 2, 0, 0,},
	{0x70, 1, 2, 0, 0,},
	{0x80, 1, 2, 0, 0,},
	};
	
	fp1 = fopen("test.txt", "w");
	for (i = 0; i < num; i++) {
		if (!e[i].type) continue;
		j = unit001[e[i].type].unitID;
		if (j < 0x80 || j > 0x91) continue; 
		memcpy(lineBuf, e[i].name, 20);
		adjStrlen(lineBuf, 20);
		fprintf(fp1, "%s", lineBuf);
		memcpy(&(e[i].pad03[5]), &z[b], 5);
		for(j = 5; j < 10; j++)
			fprintf(fp1, " %02x", e[i].pad03[j]);
		fprintf(fp1, "\n");
		b++;
		if (b == 8) break;
	}
	fclose(fp1);
}
#endif
				