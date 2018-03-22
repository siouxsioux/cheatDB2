struct WEPON
{
	unsigned short			weponID;		// 1-268, 0=N/A
	unsigned char			armoORtower;
	unsigned char			shootNum;
	unsigned char			fwShot;			// foword effect
	unsigned char			bkShot;			// back effect
	unsigned char			sdShot;			// side effect
	unsigned char			pad1;			// unknown
};

struct UNIT
{
	unsigned char			unitID;			// 01h,20-26h,40-5Ch,80-91h
	unsigned char			country;
	unsigned char			name[20];
	unsigned short			resource;		// resource for production
	unsigned short			distance;
	unsigned short			uDistance;		// under sea
	unsigned char			lowFuel;		// at low speed
	unsigned char			midFuel;		// at mid speed
	unsigned char			fulFuel;		// at high speed
	unsigned char			uLowFuel;		// under sea
	unsigned char			uMidFuel;		// under sea
	unsigned char			uFulFuel;		// under sea
	unsigned char			loadType;		// for ship
	unsigned char			toLoadType;		// for plane
	unsigned short			loadNum;
	unsigned short			combatG;		//  Combat  Movie #
	unsigned short			techP;			// Tech point
	unsigned short			endrunce;
	unsigned char			armor;			// aganst 0-61cm gun
	unsigned char			armorType;		// 0=perfect,1=consent,2=non
	unsigned short			speed;
	unsigned short			uSpeed;			// under sea
	unsigned short			upSpeed;
	unsigned short			downSpeed;
	unsigned short			maxHigh;		// or max depth
	unsigned char			pad06;
	unsigned char			shootHight;		// or dive bomb
	unsigned char			airView;
	unsigned char			seaView;
	unsigned char			uSeaView;
	unsigned char			rader;
	unsigned short			pad07;
	unsigned char			takeOffTime;
	unsigned char			move;
	unsigned short			pad08[2];
	unsigned short			supply;
	unsigned char			pType;			// 0=common,1=axis,2=deepBlue
	unsigned char			pad09;
	struct	WEPON			wepon[7];
};

struct WPNEFF
{
	unsigned short			power;		// attack power
	unsigned char			suf;		// effect on surface
	unsigned char			gnd;		// effect on ground
	unsigned char			sub;		// effect under sea
	unsigned char			airL;		// effect in low air
	unsigned char			airM;		// effect in mid air
	unsigned char			airH;		// effect in high air
};	 

struct WPNGUN {
	unsigned char 			id;
	unsigned char 			length;		// length of gun
	unsigned short 			size;		// size of gun (mm)
	unsigned char			range;		// mile
	unsigned char			time;		// time for next shooting(sec)
	struct WPNEFF 			eArmor;		// data of armored armo
	struct WPNEFF 			eNormal;	// data of normal armo
	struct WPNEFF 			eAAir;		// data of AA armo
};

struct ARMO
{
	unsigned char			id;
	unsigned char			time;
	unsigned char			name[16];
	unsigned char			range;
	unsigned char			pad0;
	struct WPNEFF 			effect;		// attack effect data
};

struct ARMONUM {
	unsigned char n[3];		// number of armored/normal/AA armo
};

struct ELEMENT {
	unsigned char pad00;
	unsigned short type;
	unsigned char name[20];
	unsigned char pad01[2];
	unsigned short endrunce[5]; // 0-all/fwd,1-left,2-right,3-aft,4-deck
	unsigned short wEndrunce[7];// endrunce of wepon 1-7 
	unsigned char pad02[5];
	unsigned char pract; 		// practice ?-250
	unsigned char spirit; 		// 0-99
	unsigned short fuel; 		// =distance, atomic=0xffff
	unsigned short goods;
	unsigned char pad03[5];
	unsigned char accident;	// 00-non,10-catapult,20-engine,40-flood,80-fire
	unsigned char pad04[2];
	unsigned char decSpeed1;	// nonZero:dec speed Knot/h by flood
	unsigned char decSpeed2;	// nonZero:dec speed Knot/h by fire
	unsigned char incSpeed;		// nonZero:inc speed Knot/h
	unsigned char pad05[9];
	unsigned char gunNum[7];	// Current number of Guns(only Gun)
	struct ARMONUM armoNum[7];
	unsigned char pad06[10];
};

