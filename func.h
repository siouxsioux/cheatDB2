int  checkPerf(void);
int  makePref(void);
int  readPref(void);
int  readFleet(FILE *);
int  writeFile(void);
int  readUnit(FILE *);
int  readMakeUnit(FILE *);
int  readFile(void);
void makeGunName(int, char *);
void msg(char *);
int  getEngID(struct UNIT *);
void setEngine(struct UNIT *, int);
int  getLoadID(struct UNIT *);
int  getLoadType(struct UNIT *, int);
void adjStrlen(char *, int);

#if 1
//  DOS depend code
void input(void);
void display(char *);
void fileOut(char *);
//#else
// Windows depend code
#endif

extern char jpString[][80];
extern char lineBuf[1024];
extern struct pref pref;
extern struct HEAD head;
extern struct CHEAT cheat;
extern struct FLEET JPfleet[16];
extern struct FLEET USfleet[16];
extern struct FLEET UKfleet[16];
extern struct FLEET DEfleet[16];
extern struct ELEMENT JPelem[850];
extern struct ELEMENT USelem[2040];
extern struct ELEMENT UKelem[600];
extern struct ELEMENT DEelem[1550];
extern struct ELEMENT RUelem[400];
extern struct ELEMENT NLelem[45];
extern struct ELEMENT AUelem[100];
extern struct ELEMENT THelem[25];
extern struct ELEMENT INelem[80];
extern struct ELEMENT CHelem[100];
extern char   fUNK11[12409];
extern struct UNIT devUnit[165];
extern char unitArmy[][16];
extern char unitAir[][16];
extern char unitShip[][16];
extern char unitSub[][16];
extern struct WPNGUN wpnGun[144];
extern struct ARMO armo[124];
extern char srcShip[][16];
extern char engName[][10];
extern struct UNIT unit001[525];
extern char engName[][10];
extern char loadName[][16];
extern char countryName[][16];
extern char armorName[][10];
extern char armorTypeName[][10];
extern char shootHighName[][8];
extern char pTypeName[][16];
extern struct FILEMAP fileMap;