struct  FLEET {
	unsigned char magic;		// 0=non,80=port,04=repair,01=live
	unsigned char name[10];
	unsigned char pad0[6];
	unsigned char pad1;
	unsigned char commander;	// zero=no commander
	unsigned char pad2[6];
	unsigned short x0;		
	unsigned short y0;	
	unsigned short x1;		
	unsigned short y1;	
	unsigned short x2;		
	unsigned short y2;	
	unsigned short x3;		
	unsigned short y3;	
	unsigned short x4;		
	unsigned short y4;	
	unsigned short x5;		// present x	
	unsigned short y5;		// present y	
	unsigned char pad3[8];
};
