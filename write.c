// A minimal Win32 console app

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dbf.h"
#include "unit.h"
#include "fleet.h"
#include "func.h"

static int freeMem(void);
static long compress(void * ,unsigned char *, long);
static long expand(unsigned char *, unsigned char *, long);

int writeFile(void) {
//	int i;
	FILE *fp;
	unsigned char tBuf[sizeof(USelem)];
	long tSize;
	
	if (NULL == (fp = fopen("user99.db2", "w+b"))) 
		goto fail0;
	// header
	if (1 != fwrite(&head, sizeof(struct HEAD), 1, fp)) 
		goto fail;
	fwrite(&(fileMap.vUNK01.size), sizeof(short), 1, fp);
	if (fwrite(fileMap.vUNK01.buf, (long )fileMap.vUNK01.size, 1, fp) != 1)
		goto fail;
	fwrite(&(fileMap.vUNK02.size), sizeof(short), 1, fp);
	if (fwrite(fileMap.vUNK02.buf, (long )fileMap.vUNK02.size, 1, fp) != 1)
		goto fail;
	fwrite(&(fileMap.vUNK03.size), sizeof(short), 1, fp);
	if (fwrite(fileMap.vUNK03.buf, (long )fileMap.vUNK03.size, 1, fp) != 1)
		goto fail;
	fwrite(&(fileMap.vUNK04.size), sizeof(short), 1, fp);
	if (fwrite(fileMap.vUNK04.buf, (long )fileMap.vUNK04.size, 1, fp) != 1)
		goto fail;
	fwrite(&(fileMap.vUNK05.size), sizeof(short), 1, fp);
	if (fwrite(fileMap.vUNK05.buf, (long )fileMap.vUNK05.size, 1, fp) != 1)
		goto fail;
	fwrite(&(fileMap.vUNK06.size), sizeof(short), 1, fp);
	if (fwrite(fileMap.vUNK06.buf, (long )fileMap.vUNK06.size, 1, fp) != 1)
		goto fail;
	fwrite(&(fileMap.vUNK07.size), sizeof(short), 1, fp);
	if (fwrite(fileMap.vUNK07.buf, (long )fileMap.vUNK07.size, 1, fp) != 1)
		goto fail;
	// cheat
	if(fwrite(&cheat, sizeof(cheat), 1, fp) != 1)
		goto fail;
	// fleet
	fwrite(&(fileMap.vFLTjp.size), sizeof(short), 1, fp);
	if (fwrite(fileMap.vFLTjp.buf, (long )fileMap.vFLTjp.size, 1, fp) != 1)
		goto fail;
	fwrite(&(fileMap.vFLTus.size), sizeof(short), 1, fp);
	if (fwrite(fileMap.vFLTus.buf, (long )fileMap.vFLTus.size, 1, fp) != 1)
		goto fail;
	fwrite(&(fileMap.vFLTuk.size), sizeof(short), 1, fp);
	if (fwrite(fileMap.vFLTuk.buf, (long )fileMap.vFLTuk.size, 1, fp) != 1)
		goto fail;
	fwrite(&(fileMap.vFLTde.size), sizeof(short), 1, fp);
	if (fwrite(fileMap.vFLTde.buf, (long )fileMap.vFLTde.size, 1, fp) != 1)
		goto fail;
	fwrite(&(fileMap.vFLTxx.size), sizeof(short), 1, fp);
	if (fwrite(fileMap.vFLTxx.buf, (long )fileMap.vFLTxx.size, 1, fp) != 1)
		goto fail;
	fwrite(&(fileMap.vUNKjp.size), sizeof(short), 1, fp);
	if (fwrite(fileMap.vUNKjp.buf, (long )fileMap.vUNKjp.size, 1, fp) != 1)
		goto fail;
	fwrite(&(fileMap.vUNKus.size), sizeof(short), 1, fp);
	if (fwrite(fileMap.vUNKus.buf, (long )fileMap.vUNKus.size, 1, fp) != 1)
		goto fail;
	fwrite(&(fileMap.vUNKuk.size), sizeof(short), 1, fp);
	if (fwrite(fileMap.vUNKuk.buf, (long )fileMap.vUNKuk.size, 1, fp) != 1)
		goto fail;
	fwrite(&(fileMap.vUNKde.size), sizeof(short), 1, fp);
	if (fwrite(fileMap.vUNKde.buf, (long )fileMap.vUNKde.size, 1, fp) != 1)
		goto fail;
	fwrite(&(fileMap.vUNKxx.size), sizeof(short), 1, fp);
	if (fwrite(fileMap.vUNKxx.buf, (long )fileMap.vUNKxx.size, 1, fp) != 1)
		goto fail;
	// unit
	tSize = compress(JPelem, tBuf, sizeof(JPelem));
	fwrite(&tSize, sizeof(long), 1, fp);
	if (fwrite(tBuf, tSize, 1, fp) != 1)
		goto fail;
//	printf("%ld/%ld\n", expand(tBuf, (unsigned char *)JPelem, tSize), sizeof(JPelem));
	tSize = compress(USelem, tBuf, sizeof(USelem));
	fwrite(&tSize, sizeof(long), 1, fp);
	if (fwrite(tBuf, tSize, 1, fp) != 1)
		goto fail;
//	printf("%ld/%ld\n", expand(tBuf, (unsigned char *)USelem, tSize), sizeof(USelem));
	tSize = compress(UKelem, tBuf, sizeof(UKelem));
	fwrite(&tSize, sizeof(long), 1, fp);
	if (fwrite(tBuf, tSize, 1, fp) != 1)
		goto fail;
//	printf("%ld/%ld\n", expand(tBuf, (unsigned char *)UKelem, tSize), sizeof(UKelem));
	tSize = compress(DEelem, tBuf, sizeof(DEelem));
	fwrite(&tSize, sizeof(long), 1, fp);
	if (fwrite(tBuf, tSize, 1, fp) != 1)
		goto fail;
//	printf("%ld/%ld\n", expand(tBuf, (unsigned char *)DEelem, tSize), sizeof(DEelem));
	tSize = compress(RUelem, tBuf, sizeof(RUelem));
	fwrite(&tSize, sizeof(long), 1, fp);
	if (fwrite(tBuf, tSize, 1, fp) != 1)
		goto fail;
//	printf("%ld/%ld\n", expand(tBuf, (unsigned char *)RUelem, tSize), sizeof(RUelem));
	tSize = compress(NLelem, tBuf, sizeof(NLelem));
	fwrite(&tSize, sizeof(long), 1, fp);
	if (fwrite(tBuf, tSize, 1, fp) != 1)
		goto fail;
	tSize = compress(AUelem, tBuf, sizeof(AUelem));
	fwrite(&tSize, sizeof(long), 1, fp);
	if (fwrite(tBuf, tSize, 1, fp) != 1)
		goto fail;
	tSize = compress(THelem, tBuf, sizeof(THelem));
	fwrite(&tSize, sizeof(long), 1, fp);
	if (fwrite(tBuf, tSize, 1, fp) != 1)
		goto fail;
	tSize = compress(INelem, tBuf, sizeof(INelem));
	fwrite(&tSize, sizeof(long), 1, fp);
	if (fwrite(tBuf, tSize, 1, fp) != 1)
		goto fail;
	tSize = compress(CHelem, tBuf, sizeof(CHelem));
	fwrite(&tSize, sizeof(long), 1, fp);
	if (fwrite(tBuf, tSize, 1, fp) != 1)
		goto fail;
	fwrite(&(fileMap.XXelem.size), sizeof(long), 1, fp);
	if (fwrite(fileMap.XXelem.buf, fileMap.XXelem.size, 1, fp) != 1)
		goto fail;
	// unkown (fix size?)
	if (fwrite(fUNK11, 12409, 1, fp) != 1)
		goto fail;
	// develped unit
	tSize = compress(devUnit, tBuf, sizeof(devUnit));
	fwrite(&tSize, sizeof(short), 1, fp);
	if (fwrite(tBuf, tSize, 1, fp) != 1)
		goto fail;
	// tail
	if (fwrite(fileMap.tail.buf, fileMap.tail.size, 1, fp) != 1)
		goto fail;

	freeMem();
	fclose(fp);
#if 1
	if (remove(pref.fName) != 0) {
		sprintf(lineBuf, "%s%s\n", pref.fName, jpString[37]);
		msg(lineBuf);
		return EOF;
	}
	if (rename("user99.db2", pref.fName) != 0) {
		sprintf(lineBuf, "%suser99.db2%s\n", jpString[23], jpString[36]);
		msg(lineBuf);
		return EOF;
	}
#endif
	return 0;
fail0:
	fclose(fp);
	remove("user99.db2");
	sprintf(lineBuf, "%suser99.db2%s\n", jpString[23], jpString[12]);
	msg(lineBuf); // file cannot creat
	return EOF;
fail:
	fclose(fp);
	sprintf(lineBuf, "%suser99.db2%s\n", jpString[23], jpString[35]);
	msg(lineBuf); // file cannot write
	if (0 != remove("user99.db2")) {
		sprintf(lineBuf, "%suser99.db2%s\n", jpString[23], jpString[36]);
		msg(lineBuf);
	}
	return EOF;
}

static int freeMem(void) {
//	int i;
	
	free(fileMap.vUNK01.buf);
	free(fileMap.vUNK02.buf);
	free(fileMap.vUNK03.buf);
	free(fileMap.vUNK04.buf);
	free(fileMap.vUNK05.buf);
	free(fileMap.vUNK06.buf);
	free(fileMap.vUNK07.buf);
	free(fileMap.vFLTjp.buf);
	free(fileMap.vFLTus.buf);
	free(fileMap.vFLTuk.buf);
	free(fileMap.vFLTde.buf);
	free(fileMap.vFLTxx.buf);
	free(fileMap.vUNKjp.buf);
	free(fileMap.vUNKus.buf);
	free(fileMap.vUNKuk.buf);
	free(fileMap.vUNKde.buf);
	free(fileMap.vUNKxx.buf);
	free(fileMap.XXelem.buf);
	free(fileMap.tail.buf);
}

static long compress(	void *src ,			// expanded buffer addr.
						unsigned char *dst, // compress buffer addr.
						long sSize) 		// expaned buffer size
{
	long i; 				// index of src buffer 
	long j; 				// index of dst buffer
	int r;					// [nn][nn][r]
	int stat;				// 0 = normal / 1 = compress
	unsigned char *s = src;	// expanded buffer addr.
	
	for(i = 0, j = 0; i < sSize - 1; i++, j++) {// loop 0 to sSize - 1
		if(s[i] == s[i  + 1]) {		// compress store
			stat = 1;
			// store same 2 byte
			dst[j] = s[i];
			dst[j + 1] = s[i + 1];
			j += 2;
			// skip & count
			for(r = 2, i++; s[i] == s[i + 1] && r <= 0xfc && i < sSize - 1; r++, i++);
			// store j(3rd byte)
			dst[j] = r;
		} else {		// normal store
			stat = 0;
			dst[j] = s[i];
		}
	}
	// store last data	
	if (stat) {
		if (r == 0xfd) dst[j - 1]++;
		return j;
	} else {
		dst[j] = s[i]; 
		return j + 1;
	}
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

