// A minimal Win32 console app

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dbf.h"
#include "unit.h"
#include "fleet.h"
#include "func.h"

static int scanHead(FILE *);
static int chkData(void);
static void printBase(void);

int readFile() {
//	int i;
	long t0, t1, t;
	FILE *fp;
	static char ver[] = "DBF2WIN95 USER5";
//	struct HEAD *hp =  &h;		// for debug
	struct CHEAT *cp = &cheat;	//  for debug
	
	if (checkPref()) {
		if (makePref()) {
			sprintf(lineBuf, "cheatprf.txt%s\n", jpString[12]);
			msg(lineBuf);
			return EOF;
		}
	}
	if (readPref()) {
		return EOF;
	}
	
	if (NULL == (fp = fopen(pref.fName, "r+b"))) {
		sprintf(lineBuf, "%s%s\n", pref.fName, jpString[13]);
		msg(lineBuf); // file cannot open
		return EOF;
	}
	if (1 != fread(&head, sizeof(struct HEAD), 1, fp) || 
			!memcmp(head.ver, ver, strlen(ver))) {
		sprintf(lineBuf, "%s%s\n", pref.fName, jpString[14]);
		msg(lineBuf); // version incorrect
		fclose(fp);
		return EOF;
	}
	if (memcmp("êÌó™", &(head.com[18]), 4) == 0)
		pref.mode = 1;
	else if (memcmp("êÌèp", &(head.com[18]), 4) == 0)
		pref.mode = 0;
	else {
		sprintf(lineBuf, "%s: Unknown mode:%s\n", jpString[0], head.com);
		msg(lineBuf); // mode is not SENJUTU or SENRYAKU
		fclose(fp);
		return EOF;
	}
	if (scanHead(fp) == EOF) {
		fclose(fp);
		return EOF; // can't read header
	}
	if(1 !=	fread(&cheat, sizeof(cheat), 1, fp))  {
		sprintf(lineBuf, "%s:cannot read struct CHEAT\n", jpString[0]);
		msg(lineBuf); // Cannot read cheatData
		fclose(fp);
		return  EOF;
	}
	if (chkData() != 0) {
		sprintf(lineBuf, "%s:cannot find country names\n", jpString[0]);
		msg(lineBuf); // CINF.name not found
		fclose(fp);
		return  EOF;
	}
	
//	printBase();
	
	if (readFleet(fp) == EOF) {
		fclose(fp);
		return  EOF;
	}

	if (readUnit(fp) == EOF) {
		fclose(fp);
		return  EOF;
	}

	if(1 !=	fread(fUNK11, 12409, 1, fp))  {	// read unkown
		sprintf(lineBuf, "%s:cannot read struct fUNK11\n", jpString[0]);
		msg(lineBuf); // Cannot read cheatData
		fclose(fp);
		return  EOF;
	}
	
	if (readMakeUnit(fp) == EOF) {
		fclose(fp);
		return  EOF;
	}
	
	t0 = ftell(fp);
	fseek(fp, 0L, SEEK_END);
	t1 = ftell(fp);
	t = t1 - t0;
	fseek(fp, -(t), SEEK_END);
	fileMap.tail.size = t;
	if (NULL == (fileMap.tail.buf = malloc(fileMap.tail.size))) {
		sprintf(lineBuf, "%s:in tail\n", jpString[2]);
		msg(lineBuf); // lack of memory in tail
		fclose(fp);
		return  EOF;
	}
	if(1 !=	fread(fileMap.tail.buf, fileMap.tail.size, 1, fp))  {	// read tail
		sprintf(lineBuf, "%s:cannot read tail\n", jpString[0]);
		msg(lineBuf); // Cannot read tail
		fclose(fp);
		return  EOF;
	}

	fclose(fp);
	return 0;
}

static int scanHead(FILE *fp) {

	fread(&(fileMap.vUNK01.size), sizeof(short), 1, fp);		// EE...EE
	if (NULL == (fileMap.vUNK01.buf = malloc(fileMap.vUNK01.size))) {
		sprintf(lineBuf,"%s: in vUNK01\n", jpString[2]);
		goto fail;
	}
	if(1 != fread(fileMap.vUNK01.buf, (long )fileMap.vUNK01.size, 1, fp)) {
		sprintf(lineBuf,"%s:stopped in vUNK01\n", jpString[0]);
		goto fail;
	}
	fread(&(fileMap.vUNK02.size), sizeof(short), 1, fp);		// 02...02
	if (NULL == (fileMap.vUNK02.buf = malloc(fileMap.vUNK02.size))) {
		sprintf(lineBuf,"%s: in vUNK02\n", jpString[2]);
		goto fail;
	}
	if(1 != fread(fileMap.vUNK02.buf, (long )fileMap.vUNK02.size, 1, fp)) {
		sprintf(lineBuf,"%s:stopped in vUNK02\n", jpString[0]);
		goto fail;
	}
	fread(&(fileMap.vUNK03.size), sizeof(short), 1, fp);		// CD CD
	if (NULL == (fileMap.vUNK03.buf = malloc(fileMap.vUNK03.size))) {
		sprintf(lineBuf,"%s: in vUNK03\n", jpString[2]);
		goto fail;
	}
	if(1 != fread(fileMap.vUNK03.buf, (long )fileMap.vUNK03.size, 1, fp)) {
		sprintf(lineBuf,"%s:stopped in vUNK03\n", jpString[0]);
		goto fail;
	}
	fread(&(fileMap.vUNK04.size), sizeof(short), 1, fp);		// CD CD
	if (NULL == (fileMap.vUNK04.buf = malloc(fileMap.vUNK04.size))) {
		sprintf(lineBuf,"%s: in vUNK04\n", jpString[2]);
		goto fail;
	}
	if(1 != fread(fileMap.vUNK04.buf, (long )fileMap.vUNK04.size, 1, fp)) {
		sprintf(lineBuf,"%s:stopped in vUNK04\n", jpString[0]);
		goto fail;
	}
	fread(&(fileMap.vUNK05.size), sizeof(short), 1, fp);		//  CD CD
	if (NULL == (fileMap.vUNK05.buf = malloc(fileMap.vUNK05.size))) {
		sprintf(lineBuf,"%s: in vUNK05\n", jpString[2]);
		goto fail;
	}
	if(1 != fread(fileMap.vUNK05.buf, (long )fileMap.vUNK05.size, 1, fp)) {
		sprintf(lineBuf,"%s:stopped in vUNK05\n", jpString[0]);
		goto fail;
	}
	fread(&(fileMap.vUNK06.size), sizeof(short), 1, fp);		//  CD CD
	if (NULL == (fileMap.vUNK06.buf = malloc(fileMap.vUNK06.size))) {
		sprintf(lineBuf,"%s: in vUNK06\n", jpString[2]);
		goto fail;
	}
	if(1 != fread(fileMap.vUNK06.buf, (long )fileMap.vUNK06.size, 1, fp)) {
		sprintf(lineBuf,"%s:stopped in vUNK06\n", jpString[0]);
		goto fail;
	}
	fread(&(fileMap.vUNK07.size), sizeof(short), 1, fp);		//  CD CD
	if (NULL == (fileMap.vUNK07.buf = malloc(fileMap.vUNK07.size))) {
		sprintf(lineBuf,"%s: in vUNK07\n", jpString[2]);
		goto fail;
	}
	if(1 != fread(fileMap.vUNK07.buf, (long )fileMap.vUNK07.size,  1, fp)) {
		sprintf(lineBuf,"%s:stopped in vUNK07\n", jpString[0]);
		goto fail;
	}
	return 0;
fail:
	msg(lineBuf);
	return EOF;
}

static int chkData(void) {

	if( cheat.jInfo.name[0] != 0x93) return EOF;
	if( cheat.jInfo.name[1] != 0xfa) return EOF; 		// Nichi
	if( cheat.countrys[0].name[0] != 0x95) return EOF;
	if( cheat.countrys[0].name[1] != 0xC4) return EOF;	 // Bai
	if( cheat.countrys[1].name[0] != 0x89) return EOF;
	if( cheat.countrys[1].name[1] != 0x70) return EOF;	 // Ei
	return 0;
}

static void printBase() {
	int i, j, k;
	FILE *fp;
	static char *buf[17];
	
	fp = fopen("out.txt", "w");
	for(i = 0; i < 223; i++) {
		fprintf(fp, "[#%03d]%02x:", cheat.base[i].num, cheat.base[i].type);
		fprintf(fp, "%c", cheat.base[i].sName[0]);
		fprintf(fp, "%c%c:", cheat.base[i].sName[1], cheat.base[i].sName[2]);
		memcpy(buf, cheat.base[i].name, 16);
		fprintf(fp, "%s:", buf);
		j = cheat.base[i].country;
		fprintf(fp, "%s:", countryName[j]);
		fprintf(fp, "%d:%d:%d\n", cheat.base[i].product, 
				cheat.base[i].goods, cheat.base[i].transShip);

		for(k = 0; k < 8; k++) {
			fprintf(fp, "(%02x|%02x)", cheat.base[i].fc[k].stat, 
					cheat.base[i].fc[k].type);
			fprintf(fp, "%05d/", cheat.base[i].fc[k].endrunce);
		}
		fprintf(fp, "\n");

		for(k = 0; k < 8; k++) {
			fprintf(fp, " S%02", cheat.base[i].fc[k].stat);
			fprintf(fp, " T%02", cheat.base[i].fc[k].type);
			fprintf(fp, " %02", cheat.base[i].fc[k].pad00);
			fprintf(fp, " e%02", cheat.base[i].fc[k].end50);
			fprintf(fp, " E%02", cheat.base[i].fc[k].endrunce);
			for (j = 0; j < 8; j++)
				fprintf(fp, " %02x",cheat.base[i].fc[k].pad01[j]);
		}
		fprintf(fp, "\n");

	}
	fclose(fp);
}

