// A minimal Win32 console app

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dbf.h"
#include "unit.h"
#include "fleet.h"
#include "func.h"

static int expand(unsigned char *, unsigned char *, int);

int readFleet(FILE   *fp)
{
	int size;
	// read JP fleet
	fread(&(fileMap.vFLTjp.size), sizeof(short), 1, fp);
	if (NULL  == (fileMap.vFLTjp.buf = malloc(fileMap.vFLTjp.size))) {
		sprintf(lineBuf, "%s:in JP Fleet\n", jpString[2]);
		goto fail;
	}
	if (1 != fread(fileMap.vFLTjp.buf, fileMap.vFLTjp.size, 1, fp)) {
		sprintf(lineBuf, "%s:Cannot read JP Fleet\n", jpString[0]);
		goto fail;
	}
	size = expand(fileMap.vFLTjp.buf, (unsigned char *)JPfleet, fileMap.vFLTjp.size);
	// read US fleet	
	fread(&(fileMap.vFLTus.size), sizeof(short), 1, fp);
	if (NULL  == (fileMap.vFLTus.buf = malloc(fileMap.vFLTus.size))) {
		sprintf(lineBuf, "%s:in US Fleet\n", jpString[2]);
		goto fail;
	}
	if (1 != fread(fileMap.vFLTus.buf, fileMap.vFLTus.size, 1, fp)) {
		sprintf(lineBuf, "%s:Cannot read US Fleet\n", jpString[0]);
		goto fail;
	}
	size = expand(fileMap.vFLTus.buf, (unsigned char *)USfleet, fileMap.vFLTus.size);
	// read UK fleet
	fread(&(fileMap.vFLTuk.size), sizeof(short), 1, fp);
	if (NULL  == (fileMap.vFLTuk.buf = malloc(fileMap.vFLTuk.size))) {
		sprintf(lineBuf, "%s:in UK Fleet\n", jpString[2]);
		goto fail;
	}
	if (1 != fread(fileMap.vFLTuk.buf, fileMap.vFLTuk.size, 1, fp)) {
		sprintf(lineBuf, "%s:Cannot read UK Fleet\n", jpString[0]);
		goto fail;
	}
	size = expand(fileMap.vFLTuk.buf, (unsigned char *)UKfleet, fileMap.vFLTuk.size);
	// read DE fleet
	fread(&(fileMap.vFLTde.size), sizeof(short), 1, fp);
	if (NULL  == (fileMap.vFLTde.buf = malloc(fileMap.vFLTde.size))) {
		sprintf(lineBuf, "%s:in DE Fleet\n", jpString[2]);
		goto fail;
	}
	if (1 != fread(fileMap.vFLTde.buf, fileMap.vFLTde.size, 1, fp)) {
		sprintf(lineBuf, "%s:Cannot read DE Fleet\n", jpString[0]);
		goto fail;
	}
	size = expand(fileMap.vFLTde.buf, (unsigned char *)DEfleet, fileMap.vFLTde.size);
	// read zero padding(?)
	fread(&(fileMap.vFLTxx.size), sizeof(short), 1, fp);
	if (NULL  == (fileMap.vFLTxx.buf = malloc(fileMap.vFLTxx.size))) {
		sprintf(lineBuf, "%s:in vFLTxx\n", jpString[2]);
		goto fail;
	}
	if (1 != fread(fileMap.vFLTxx.buf, fileMap.vFLTxx.size, 1, fp)) {
		sprintf(lineBuf, "%s:Cannot read vFLTxxt\n", jpString[0]);
		goto fail;
	}
	// read unknown(JP?)
	fread(&(fileMap.vUNKjp.size), sizeof(short), 1, fp);
	if (NULL  == (fileMap.vUNKjp.buf = malloc(fileMap.vUNKjp.size))) {
		sprintf(lineBuf, "%s:in vUNKjp\n", jpString[2]);
		goto fail;
	}
	if (1 != fread(fileMap.vUNKjp.buf, fileMap.vUNKjp.size, 1, fp)) {
		sprintf(lineBuf, "%s:Cannot read vUNKjp\n", jpString[0]);
		goto fail;
	}
	// read unknown(US?)
	fread(&(fileMap.vUNKus.size), sizeof(short), 1, fp);
	if (NULL  == (fileMap.vUNKus.buf = malloc(fileMap.vUNKus.size))) {
		sprintf(lineBuf, "%s:in vUNKus\n", jpString[2]);
		goto fail;
	}
	if (1 != fread(fileMap.vUNKus.buf, fileMap.vUNKus.size, 1, fp)) {
		sprintf(lineBuf, "%s:Cannot read vUNKus\n", jpString[0]);
		goto fail;
	}
	// read unknown(UK?)
	fread(&(fileMap.vUNKuk.size), sizeof(short), 1, fp);
	if (NULL  == (fileMap.vUNKuk.buf = malloc(fileMap.vUNKuk.size))) {
		sprintf(lineBuf, "%s:in vUNKuk\n", jpString[2]);
		goto fail;
	}
	if (1 != fread(fileMap.vUNKuk.buf, fileMap.vUNKuk.size, 1, fp)) {
		sprintf(lineBuf, "%s:Cannot read vUNKuk\n", jpString[0]);
		goto fail;
	}
	// read unknown(DE?)
	fread(&(fileMap.vUNKde.size), sizeof(short), 1, fp);
	if (NULL  == (fileMap.vUNKde.buf = malloc(fileMap.vUNKde.size))) {
		sprintf(lineBuf, "%s:in vUNKde\n", jpString[2]);
		goto fail;
	}
	if (1 != fread(fileMap.vUNKde.buf, fileMap.vUNKde.size, 1, fp)) {
		sprintf(lineBuf, "%s:Cannot read vUNKde\n", jpString[0]);
		goto fail;
	}
	// read unknown(zero padding?)
	fread(&(fileMap.vUNKxx.size), sizeof(short), 1, fp);
	if (NULL  == (fileMap.vUNKxx.buf = malloc(fileMap.vUNKxx.size))) {
		sprintf(lineBuf, "%s:in vUNKxx\n", jpString[2]);
		goto fail;
	}
	if (1 != fread(fileMap.vUNKxx.buf, fileMap.vUNKxx.size, 1, fp)) {
		sprintf(lineBuf, "%s:Cannot read vUNKxx\n", jpString[0]);
		goto fail;
	}
	
	return 0;
fail:
	msg(lineBuf);
	return EOF;
}

static int expand(unsigned char *buf, unsigned char *u, int bSize)
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

