struct HEAD
{
	unsigned char ver[18];
	unsigned char com[80];
	unsigned char pad00[311];
};

struct CINFO
{
	unsigned char	name[16];
	unsigned char	unk011;
	unsigned char	unk012;
	unsigned char	unk013;
	unsigned long	point;
	unsigned short	techP;
	unsigned short	isiki;
	unsigned short	nIndust;
	unsigned short	tIndust;
	unsigned long	solder;
	unsigned char	relateJP;
	unsigned char	relateUS;
	unsigned char	relateUK;
	unsigned char	relateDE;
	unsigned char	relateRU;
	unsigned char	relateNE;
	unsigned char	relateAU;
	unsigned char	relateTI;
	unsigned char	relateID;
	unsigned char	relateCH;
	unsigned short	unk041;
	unsigned short	unk042;
	unsigned short	unk043;
	unsigned short	unk044;
	unsigned short	unk045;
	unsigned short	unk046;
};

struct BUILT
{
	unsigned short	id;
	unsigned short	days;
};

struct SNAME
{
	unsigned char	sName[20];
};

struct BINFO
{
	struct BUILT	ship[20];
	struct BUILT	plane[20];
	struct SNAME	snames[20];
	unsigned short	pNum[20];
};

struct FACILITY
{
	unsigned char stat;		// 0x?0:non,0x?1:invisible,0x?2:visible
							// 0x8?:repairing now, 0x0?:normal
	unsigned char type;		// 0:command,1:air port,.....
	unsigned char pad00;
	unsigned char end50;	// endrunce/50
	unsigned short endrunce;
	unsigned char pad01[8];
};
	
struct BASE
{
	unsigned char type;
	unsigned char country;
	unsigned char name[16];	
	unsigned char sName[3];
	unsigned char num;
	unsigned char pad00[4];
	unsigned short product;
	unsigned short goods;
	unsigned char pad01[2];
	unsigned char transShip;
	unsigned char wDays;	// waiting days for goods
	unsigned char pad02[7];
	struct FACILITY fc[8];
};

struct PERSON
{
	unsigned char flag;// 80=Admiral,01=live,03=dead,04=surrender
	unsigned char country;
	unsigned char name[16];
	unsigned char pad00[7];
};

struct CHEAT
{
	unsigned char	xData[3221];
	struct CINFO	jInfo;
	struct CINFO	countrys[9];
	unsigned char	yData[1453];
	struct BINFO	jBuilt;
	struct BINFO	builts[3];
	unsigned char	zData[3360];
	struct BASE		base[223];
	struct PERSON	person[23];
};

struct pref
{
	int mode;					// 0 = SENJUTSU, 1 = SENRYAKU
	char fName[11];
	unsigned short tp[10];		// tech point
	unsigned short base1[10];	// goods in base = 60000
						 		// Transport ship = 5
								// endrunce of Base facility = 12500
	unsigned short unit1[10];	// endrunce unit = MAX, practice = 250(A)
					   	 		// spilit = 99, fuel = MAX, goods = MAX
						 		// armo = MAX
};

struct FILE_sREC {
	short size;
	void *buf;
};

struct FILE_lREC {
	long size;
	void *buf;
};

struct FILEMAP {
//	struct HEAD haed;
	struct FILE_sREC vUNK01;
	struct FILE_sREC vUNK02;
	struct FILE_sREC vUNK03;
	struct FILE_sREC vUNK04;
	struct FILE_sREC vUNK05;
	struct FILE_sREC vUNK06;
	struct FILE_sREC vUNK07;
//	struct CHEAT cheat;
	struct FILE_sREC vFLTjp;
	struct FILE_sREC vFLTus;
	struct FILE_sREC vFLTuk;
	struct FILE_sREC vFLTde;
	struct FILE_sREC vFLTxx;
	struct FILE_sREC vUNKjp;
	struct FILE_sREC vUNKus;
	struct FILE_sREC vUNKuk;
	struct FILE_sREC vUNKde;
	struct FILE_sREC vUNKxx;
// 	struct ELEMENT JPelem[850];
//	struct ELEMENT USelem[2040];
//	struct ELEMENT UKelem[600];
//	struct ELEMENT DEelem[1550];
//	struct ELEMENT RUelem[400];
//	struct ELEMENT NLelem[45];
//	struct ELEMENT AUelem[100];
//	struct ELEMENT THelem[25];
//	struct ELEMENT INelem[80];
//	struct ELEMENT CHelem[100];
	struct FILE_lREC XXelem;
//	char   fUNK11[12409];
//	struct UNIT devUnit[165];
	struct FILE_lREC tail;
};
	