// A minimal Win32 console app

#include <stdio.h>
#include <string.h>
#include "dbf.h"
#include "unit.h"
#include "fleet.h"
#include "func.h"

static int expand(unsigned char *, unsigned char *, int);
static void printUnit(void);

int readMakeUnit(FILE *fp) 
{
	short size;
	unsigned char *buf;
		
	if (1 != fread(&size, sizeof(short), 1, fp)) {
		sprintf(lineBuf, "%s:Cannot Read DevelopUnit size\n", jpString[0]);
		msg(lineBuf);
		return EOF;
	}

	buf = (unsigned char *)malloc(size);
	if (buf == NULL)  {
		sprintf(lineBuf, "%s:at DevelopUnit\n", jpString[2]);
		msg(lineBuf);
		return EOF;
	}
	if (1 != fread(buf, size, 1, fp)) {
		sprintf(lineBuf, "%s:Cannot Read DevelopUnit\n", jpString[0]);
		msg(lineBuf);
		free(buf);
		return EOF;
	}

	if (expand(buf, (unsigned char *)devUnit, size) != 0) {
		free(buf);
		return EOF;
	}
	free(buf);
//	printUnit();
	return 0;
}

static int expand(unsigned char *buf, unsigned char *u, int bSize)
{
	int i, j, size;
	unsigned  char buf3[3];
	
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
	if (size != 21450) {
		sprintf(lineBuf, "%s:DevelopUnit size ERROR!\n", jpString[0]);
		msg(lineBuf);
		return 1;
	}
	return 0;
}
			
static void printUnit(void)
{
	int i;
	
	for(i = 0; i < 165; i++)
		if (devUnit[i].unitID != 0)
			printf("%d:%s\n", i,devUnit[i].name);
}

