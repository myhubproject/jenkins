//此程序取得系统时间有效期为到2038年1月份	调用函数为 GetSysData();
//time_t类型为long	以秒计算可以计数68年    系统以1970年为开始时间
#ifndef			_BankMenu
#define			_BankMenu
#endif
#ifndef			_BankMenu1
#define			_BankMenu1
#endif

#include		<time.h>
#include		"menu.h"


void			DispMenuPro(char *Str);
char 			SysCall(char *comm);
void 			DispWord(int x,int y,char *Str,char Mode);
int			GetKey(void);
int			GetKey1(void);
void 			DispMenuItem(struct MenuOptStru *Menu, char Mode);
void 			DispMenuHead(void);
void 			GetFormStr(char Fgch1, char Fgch2, int Num, 
				char *Str, char *Str1);
void 			Clock(int Sencond);

short			_ShiftF1 = 391;
short			_ShiftF2 = 403;
short			_ShiftF3 = 393;
short			_ShiftF4 = 394;
short			_ShiftF5 = 395;
short			_ShiftF6 = 396;
short			_ShiftF7 = 397;
short			_ShiftF8 = 398;
short			_ShiftF9 = 337;
short			_ShiftF10 = 400;
short			_ShiftF11 = 401;
short			_ShiftF12 = 402;
short			_CtrlF1 = 378;
short			_CtrlF2 = 379;
short			_CtrlF3 = 380;
short			_CtrlF4 = 381;
short			_CtrlF5 = 382;
short			_CtrlF6 = 383;
short			_CtrlF7 = 384;
short			_CtrlF8 = 386;
short			_CtrlF9 = 387;
short			_CtrlF10 = 388;
short			_CtrlF11 = 389;
short			_CtrlF12 = 390;
short			_F1 = 265;
short			_F2 = 266;
short			_F3 = 267;
short			_F4 = 268;
short			_F5 = 269;
short			_F6 = 270;
short			_F7 = 271;
short			_F8 = 272;
short			_F9 = 273;
short			_F10 = 274;
short			_F11 = 275;
short			_F12 = 276;
short			_Left = 260;
short			_Right = 261;
short			_Up = 259;
short			_Down = 258;
short			_Keypad = 350;
short			_PrintScr = 346;
short			_Insert = 331;
short			_Home = 262;
short			_End = 360;
short			_Pgup = 339;
short			_Pgdn = 338;
short			_BackSpace = 8;
short			_Tab = 9;
short			_Enter = 13;
short			_Esc = 27;
#define			_DelKey  999
short			KeyBuf[52];
int			ScrEx=23;	//屏幕最未行
int		 	ScrEy=78;	//屏幕最未列

struct MenuOptStru		*MenuArry;
struct MenuOptStru		*CurrentMenu;
struct OpeAccessStru		*OpeAccess;
struct SysParStru		SysPar;
struct SysTranStru		SysTran;
char				ProMode=MenuMode;
char				EditMenuPass[]="flq";
char				MenuFilePass[]="feiliqiang";
char				FixPass[80];
char				SysTime[20];
char				SysPro[180];
short				KeyValue;
char				ClockFlag=0;
static char ConfDir[]="../jlconf";

static struct sembuf icb_lock[2]={0,0,0,0,1,0};
static struct sembuf icb_unlock[1]={0,-1,IPC_NOWAIT};

//此函数转换为银行数字
void ChBankNum(char *Str)
{
	char		*P, *P1;
	char		Str1[80];
	int		Tmpi;

	memset(Str1,' ',80);
	Str1[79]=0;
	if((P=strchr(Str,'.'))!=NULL)
		strcpy(&Str1[79-strlen(P)],P);
	if((P1=strchr(Str1,'.'))!=NULL)
		P1--;
	else
		P1=&Str1[78];

	if((P=strchr(Str,'.'))!=NULL)
		P--;
	else
		P=&Str[strlen(Str)-1];

	for(Tmpi=1;P>=Str; P--,Tmpi++)
	{
		*P1--=*P;
		if(Tmpi==3&&P>Str&&*(P-1)!='-'&&*(P-1)!='+')
		{
			*P1--=',';
			Tmpi=0;
		}
		
	}
	for(P=Str1;*P==' ';P++);
	strcpy(Str,P);	
}

void WriteHard(char *FileName)
{
	FILE	*fp;
	if((fp=fopen(FileName, "wt"))==NULL)
		return;
	fprintf(fp,"%s,%s,%s,%c,%s,%s,%s,%s,%s,%s,%s,%s.\n",
	SysPar.Term, SysPar.Printer,SysPar.Password,SysPar.ClockFlag,
	SysPar.Jrdmdy,SysPar.Dcdmdy,SysPar.Zdfd, SysPar.Zdhy, SysPar.Hjj,
	SysPar.Zjj, SysPar.PrintInit, SysPar.Printhy);
	fclose(fp);
}

int WriteAllKey(char *FileName, char Mode)
{
	int		i, j;
	FILE 		*fp;
	if((fp=fopen(FileName, "wt"))==NULL)
		return 0;
	fprintf(fp,"ShiftF1,%d\n",KeyBuf[0]);
	fprintf(fp,"ShiftF2,%d\n",KeyBuf[1]);
	fprintf(fp,"ShiftF3,%d\n",KeyBuf[2]);
	fprintf(fp,"ShiftF4,%d\n",KeyBuf[3]);
	fprintf(fp,"ShiftF5,%d\n",KeyBuf[4]);
	fprintf(fp,"ShiftF6,%d\n",KeyBuf[5]);
	fprintf(fp,"ShiftF7,%d\n",KeyBuf[6]);
	fprintf(fp,"ShiftF8,%d\n",KeyBuf[7]);
	fprintf(fp,"ShiftF9,%d\n",KeyBuf[8]);
	fprintf(fp,"ShiftF10,%d\n",KeyBuf[9]);
	fprintf(fp,"ShiftF11,%d\n",KeyBuf[10]);
	fprintf(fp,"ShiftF12,%d\n",KeyBuf[11]);

	fprintf(fp,"CtrlF1,%d\n",KeyBuf[12]);
	fprintf(fp,"CtrlF2,%d\n",KeyBuf[13]);
	fprintf(fp,"CtrlF3,%d\n",KeyBuf[14]);
	fprintf(fp,"CtrlF4,%d\n",KeyBuf[15]);
	fprintf(fp,"CtrlF5,%d\n",KeyBuf[16]);
	fprintf(fp,"CtrlF6,%d\n",KeyBuf[17]);
	fprintf(fp,"CtrlF7,%d\n",KeyBuf[18]);
	fprintf(fp,"CtrlF8,%d\n",KeyBuf[19]);
	fprintf(fp,"CtrlF9,%d\n",KeyBuf[20]);
	fprintf(fp,"CtrlF10,%d\n",KeyBuf[21]);
	fprintf(fp,"CtrlF11,%d\n",KeyBuf[22]);
	fprintf(fp,"CtrlF12,%d\n",KeyBuf[23]);

	fprintf(fp,"F1,%d\n",KeyBuf[24]);
	fprintf(fp,"F2,%d\n",KeyBuf[25]);
	fprintf(fp,"F3,%d\n",KeyBuf[26]);
	fprintf(fp,"F4,%d\n",KeyBuf[27]);
	fprintf(fp,"F5,%d\n",KeyBuf[28]);
	fprintf(fp,"F6,%d\n",KeyBuf[29]);
	fprintf(fp,"F7,%d\n",KeyBuf[30]);
	fprintf(fp,"F8,%d\n",KeyBuf[31]);
	fprintf(fp,"F9,%d\n",KeyBuf[32]);
	fprintf(fp,"F10,%d\n",KeyBuf[33]);
	fprintf(fp,"F11,%d\n",KeyBuf[34]);
	fprintf(fp,"F12,%d\n",KeyBuf[35]);

	fprintf(fp,"Left,%d\n",KeyBuf[36]);
	fprintf(fp,"Right,%d\n",KeyBuf[37]);
	fprintf(fp,"Up,%d\n",KeyBuf[38]);
	fprintf(fp,"Down,%d\n",KeyBuf[39]);
	fprintf(fp,"Keypad,%d\n",KeyBuf[40]);
	fprintf(fp,"PrintScr,%d\n",KeyBuf[41]);
	fprintf(fp,"Insert,%d\n",KeyBuf[42]);
	fprintf(fp,"Home,%d\n",KeyBuf[43]);
	fprintf(fp,"End,%d\n",KeyBuf[44]);
	fprintf(fp,"Pgup,%d\n",KeyBuf[45]);
	fprintf(fp,"Pgdn,%d\n",KeyBuf[46]);
	fprintf(fp,"BackSpace,%d\n",KeyBuf[47]);
	fprintf(fp,"Tab,%d\n",KeyBuf[48]);
	fprintf(fp,"Enter,%d\n",_Enter);
	fprintf(fp,"Esc,%d\n",KeyBuf[50]);
	fclose(fp);
	return 1;
}

void ReadHard(char *FileName)
{
	FILE	*fp;
	char	Str[400], Str1[40];
	if((fp=fopen(FileName,"rt"))==NULL)
		return;
	fgets(Str,400,fp);
	GetFormStr(',', ',', 0, Str, Str1);
	strcpy(SysPar.Term, Str1);
	GetFormStr(',', ',', 1, Str, Str1);
	strcpy(SysPar.Printer, Str1);
	GetFormStr(',', ',', 2, Str, Str1);
	strcpy(SysPar.Password, Str1);
	GetFormStr(',', ',', 3, Str, Str1);
	SysPar.ClockFlag=Str1[0];

	GetFormStr(',',',',4,Str, Str1);
	strcpy(SysPar.Jrdmdy,Str1);
	GetFormStr(',',',',5,Str, Str1);
	strcpy(SysPar.Dcdmdy,Str1);
	GetFormStr(',',',',6,Str, Str1);
	strcpy(SysPar.Zdfd,Str1);
	GetFormStr(',',',',7,Str, Str1);
	strcpy(SysPar.Zdhy,Str1);
	GetFormStr(',',',',8,Str, Str1);
	strcpy(SysPar.Hjj,Str1);
	GetFormStr(',',',',9,Str, Str1);
	strcpy(SysPar.Zjj,Str1);
	GetFormStr(',',',',10,Str, Str1);
	strcpy(SysPar.PrintInit,Str1);
	GetFormStr(',','.',11,Str, Str1);
	strcpy(SysPar.Printhy,Str1);

	if(SysPar.ClockFlag=='1')
	{
		signal(SIGALRM, Clock);
		alarm(1);
	}
	else
		alarm(0);
	fclose(fp);
}

void ReadAllKey(char *FileName)
{
	FILE	*fp;
	if((fp=fopen(FileName,"rt"))==NULL)
		return;
	fscanf(fp,"ShiftF1,%d\n",&_ShiftF1);
	fscanf(fp,"ShiftF2,%d\n",&_ShiftF2);
	fscanf(fp,"ShiftF3,%d\n",&_ShiftF3);
	fscanf(fp,"ShiftF4,%d\n",&_ShiftF4);
	fscanf(fp,"ShiftF5,%d\n",&_ShiftF5);
	fscanf(fp,"ShiftF6,%d\n",&_ShiftF6);
	fscanf(fp,"ShiftF7,%d\n",&_ShiftF7);
	fscanf(fp,"ShiftF8,%d\n",&_ShiftF8);
	fscanf(fp,"ShiftF9,%d\n",&_ShiftF9);
	fscanf(fp,"ShiftF10,%d\n",&_ShiftF10);
	fscanf(fp,"ShiftF11,%d\n",&_ShiftF11);
	fscanf(fp,"ShiftF12,%d\n",&_ShiftF12);

	fscanf(fp,"CtrlF1,%d\n",&_CtrlF1);
	fscanf(fp,"CtrlF2,%d\n",&_CtrlF2);
	fscanf(fp,"CtrlF3,%d\n",&_CtrlF3);
	fscanf(fp,"CtrlF4,%d\n",&_CtrlF4);
	fscanf(fp,"CtrlF5,%d\n",&_CtrlF5);
	fscanf(fp,"CtrlF6,%d\n",&_CtrlF6);
	fscanf(fp,"CtrlF7,%d\n",&_CtrlF7);
	fscanf(fp,"CtrlF8,%d\n",&_CtrlF8);
	fscanf(fp,"CtrlF9,%d\n",&_CtrlF9);
	fscanf(fp,"CtrlF10,%d\n",&_CtrlF10);
	fscanf(fp,"CtrlF11,%d\n",&_CtrlF11);
	fscanf(fp,"CtrlF12,%d\n",&_CtrlF12);

	fscanf(fp,"F1,%d\n",&_F1);
	fscanf(fp,"F2,%d\n",&_F2);
	fscanf(fp,"F3,%d\n",&_F3);
	fscanf(fp,"F4,%d\n",&_F4);
	fscanf(fp,"F5,%d\n",&_F5);
	fscanf(fp,"F6,%d\n",&_F6);
	fscanf(fp,"F7,%d\n",&_F7);
	fscanf(fp,"F8,%d\n",&_F8);
	fscanf(fp,"F9,%d\n",&_F9);
	fscanf(fp,"F10,%d\n",&_F10);
	fscanf(fp,"F11,%d\n",&_F11);
	fscanf(fp,"F12,%d\n",&_F12);

	fscanf(fp,"Left,%d\n",&_Left);
	fscanf(fp,"Right,%d\n",&_Right);
	fscanf(fp,"Up,%d\n",&_Up);
	fscanf(fp,"Down,%d\n",&_Down);
	fscanf(fp,"Keypad,%d\n",&_Keypad);
	fscanf(fp,"PrintScr,%d\n",&_PrintScr);
	fscanf(fp,"Insert,%d\n",&_Insert);
	fscanf(fp,"Home,%d\n",&_Home);
	fscanf(fp,"End,%d\n",&_End);
	fscanf(fp,"Pgup,%d\n",&_Pgup);
	fscanf(fp,"Pgdn,%d\n",&_Pgdn);
	fscanf(fp,"BackSpace,%d\n",&_BackSpace);
	fscanf(fp,"Tab,%d\n",&_Tab);
	fscanf(fp,"Enter,%d\n",&_Enter);
	fscanf(fp,"Esc,%d\n",&_Esc);
	fclose(fp);
}

char AcceptKey(int x, int y, char *Str, short *P, char Mode)
{
	int	Key;
	char	Str1[20];
	DispWord(x,y,Str,RefreshMode);
	if(!Mode)
	{
		sprintf(Str1,"%d",*P);
		DispWord(x,y+16,Str1,RefreshMode);
		return 1;
	}
	for(;(Key=GetKey1())!=_Enter;)
	{
		if(Key=='i'||Key=='I')
		{
			DispWord(x,y+16,"          ",RefreshMode);
			DispWord(x,y+16,"0",RefreshMode);
			Str1[0]=0;
			*P=0;
			break;
		}
		else if(Key=='q'||Key=='Q')
			return 0;
		else
		{
			DispWord(x,y+16,"          ",RefreshMode);
			sprintf(Str1,"%d",Key);
			DispWord(x,y+16,Str1,RefreshMode);
			*P=Key;
		}
	}
	Accept(x,y+16,Str1,4,0,StrNumMode);
	*P=atoi(Str1);
	return 1;
}

char AcceptAllKey(char Mode)
{
	char Str1[2];
	if(!AcceptKey(2,1,"ShiftF1=",&KeyBuf[0],Mode)) return 0;
	if(!AcceptKey(3,1,"ShiftF2=",&KeyBuf[1],Mode)) return 0;
	if(!AcceptKey(4,1,"ShiftF3=",&KeyBuf[2],Mode)) return 0;
	if(!AcceptKey(5,1,"ShiftF4=",&KeyBuf[3],Mode)) return 0;
	if(!AcceptKey(6,1,"ShiftF5=",&KeyBuf[4],Mode)) return 0;
	if(!AcceptKey(7,1,"ShiftF6=",&KeyBuf[5],Mode)) return 0;
	if(!AcceptKey(8,1,"ShiftF7=",&KeyBuf[6],Mode)) return 0;
	if(!AcceptKey(9,1,"ShiftF8=",&KeyBuf[7],Mode)) return 0;
	if(!AcceptKey(10,1,"ShiftF9=",&KeyBuf[8],Mode)) return 0;
	if(!AcceptKey(11,1,"ShiftF10=",&KeyBuf[9],Mode)) return 0;
	if(!AcceptKey(12,1,"ShiftF11=",&KeyBuf[10],Mode)) return 0;
	if(!AcceptKey(13,1,"ShiftF12=",&KeyBuf[11],Mode)) return 0;

	if(!AcceptKey(14,1,"CtrlF1=",&KeyBuf[12],Mode)) return 0;
	if(!AcceptKey(15,1,"CtrlF2=",&KeyBuf[13],Mode)) return 0;
	if(!AcceptKey(16,1,"CtrlF3=",&KeyBuf[14],Mode)) return 0;
	if(!AcceptKey(17,1,"CtrlF4=",&KeyBuf[15],Mode)) return 0;
	if(!AcceptKey(18,1,"CtrlF5=",&KeyBuf[16],Mode)) return 0;
	if(!AcceptKey(19,1,"CtrlF6=",&KeyBuf[17],Mode)) return 0;
	if(!AcceptKey(2,27,"CtrlF7=",&KeyBuf[18],Mode)) return 0;
	if(!AcceptKey(3,27,"CtrlF8=",&KeyBuf[19],Mode)) return 0;
	if(!AcceptKey(4,27,"CtrlF9=",&KeyBuf[20],Mode)) return 0;
	if(!AcceptKey(5,27,"CtrlF10=",&KeyBuf[21],Mode)) return 0;
	if(!AcceptKey(6,27,"CtrlF11=",&KeyBuf[22],Mode)) return 0;
	if(!AcceptKey(7,27,"CtrlF12=",&KeyBuf[23],Mode)) return 0;

	if(!AcceptKey(8,27,"F1=",&KeyBuf[24],Mode)) return 0;
	if(!AcceptKey(9,27,"F2=",&KeyBuf[25],Mode)) return 0;
	if(!AcceptKey(10,27,"F3=",&KeyBuf[26],Mode)) return 0;
	if(!AcceptKey(11,27,"F4=",&KeyBuf[27],Mode)) return 0;
	if(!AcceptKey(12,27,"F5=",&KeyBuf[28],Mode)) return 0;
	if(!AcceptKey(13,27,"F6=",&KeyBuf[29],Mode)) return 0;
	if(!AcceptKey(14,27,"F7=",&KeyBuf[30],Mode)) return 0;
	if(!AcceptKey(15,27,"F8=",&KeyBuf[31],Mode)) return 0;
	if(!AcceptKey(16,27,"F9=",&KeyBuf[32],Mode)) return 0;
	if(!AcceptKey(17,27,"F10=",&KeyBuf[33],Mode)) return 0;
	if(!AcceptKey(18,27,"F11=",&KeyBuf[34],Mode)) return 0;
	if(!AcceptKey(19,27,"F12=",&KeyBuf[35],Mode)) return 0;

	if(!AcceptKey(2,54,"Left=",&KeyBuf[36],Mode)) return 0;
	if(!AcceptKey(3,54,"Right=",&KeyBuf[37],Mode)) return 0;
	if(!AcceptKey(4,54,"Up=",&KeyBuf[38],Mode)) return 0;
	if(!AcceptKey(5,54,"Down=",&KeyBuf[39],Mode)) return 0;
	if(!AcceptKey(6,54,"Keypad=",&KeyBuf[40],Mode)) return 0;
	if(!AcceptKey(7,54,"PrintScr=",&KeyBuf[41],Mode)) return 0;
	if(!AcceptKey(8,54,"Insert=",&KeyBuf[42],Mode)) return 0;
	if(!AcceptKey(9,54,"Home=",&KeyBuf[43],Mode)) return 0;
	if(!AcceptKey(10,54,"End=",&KeyBuf[44],Mode)) return 0;
	if(!AcceptKey(11,54,"Pgup=",&KeyBuf[45],Mode)) return 0;
	if(!AcceptKey(12,54,"Pgdn=",&KeyBuf[46],Mode)) return 0;
	if(!AcceptKey(13,54,"BackSpace=",&KeyBuf[47],Mode)) return 0;
	if(!AcceptKey(14,54,"Tab=",&KeyBuf[48],Mode)) return 0;
	KeyBuf[49]=13;
	if(!AcceptKey(16,54,"Esc=",&KeyBuf[50],Mode)) return 0;
	if(Mode)
	{
		DispWord(17,54,"是否保留新键值(1/0):",RefreshMode);
		for(;;)
		{
			Accept(17,76,Str1,1,0,InitStrNumMode);
				if(Str1[0]=='0'||Str1[0]=='1')
					break;
		}
		if(Str1[0]=='0')
			return 0;
	}
	else
		Accept(17,76,Str1,1,0,InitStrNumMode);
	return 1;
}

int CheckAllKey(char *Str)
{
	if(strcmp("ShiftF1",Str)==0) return _ShiftF1;
	if(strcmp("ShiftF2",Str)==0) return _ShiftF2;
	if(strcmp("ShiftF3",Str)==0) return _ShiftF3;
	if(strcmp("ShiftF4",Str)==0) return _ShiftF4;
	if(strcmp("ShiftF5",Str)==0) return _ShiftF5;
	if(strcmp("ShiftF6",Str)==0) return _ShiftF6;
	if(strcmp("ShiftF7",Str)==0) return _ShiftF7;
	if(strcmp("ShiftF8",Str)==0) return _ShiftF8;
	if(strcmp("ShiftF9",Str)==0) return _ShiftF9;
	if(strcmp("ShiftF10",Str)==0) return _ShiftF10;
	if(strcmp("ShiftF11",Str)==0) return _ShiftF11;
	if(strcmp("ShiftF12",Str)==0) return _ShiftF12;
	if(strcmp("CtrlF1",Str)==0) return _CtrlF1;
	if(strcmp("CtrlF2",Str)==0) return _CtrlF2;
	if(strcmp("CtrlF3",Str)==0) return _CtrlF3;
	if(strcmp("CtrlF4",Str)==0) return _CtrlF4;
	if(strcmp("CtrlF5",Str)==0) return _CtrlF5;
	if(strcmp("CtrlF6",Str)==0) return _CtrlF6;
	if(strcmp("CtrlF7",Str)==0) return _CtrlF7;
	if(strcmp("CtrlF8",Str)==0) return _CtrlF8;
	if(strcmp("CtrlF9",Str)==0) return _CtrlF9;
	if(strcmp("CtrlF10",Str)==0) return _CtrlF10;
	if(strcmp("CtrlF11",Str)==0) return _CtrlF11;
	if(strcmp("CtrlF12",Str)==0) return _CtrlF12;
	if(strcmp("F1",Str)==0) return _F1;
	if(strcmp("F2",Str)==0) return _F2;
	if(strcmp("F3",Str)==0) return _F3;
	if(strcmp("F4",Str)==0) return _F4;
	if(strcmp("F5",Str)==0) return _F5;
	if(strcmp("F6",Str)==0) return _F6;
	if(strcmp("F7",Str)==0) return _F7;
	if(strcmp("F8",Str)==0) return _F8;
	if(strcmp("F9",Str)==0) return _F9;
	if(strcmp("F10",Str)==0) return _F10;
	if(strcmp("F11",Str)==0) return _F11;
	if(strcmp("F12",Str)==0) return _F12;
	if(strcmp("Left",Str)==0) return _Left;
	if(strcmp("Right",Str)==0) return _Right;
	if(strcmp("Up",Str)==0) return _Up;
	if(strcmp("Down",Str)==0) return _Down;
	if(strcmp("Keypad",Str)==0) return _Keypad;
	if(strcmp("PrintScr",Str)==0) return _PrintScr;
	if(strcmp("Insert",Str)==0) return _Insert;
	if(strcmp("Home",Str)==0) return _Home;
	if(strcmp("End",Str)==0) return _End;
	if(strcmp("Pgup",Str)==0) return _Pgup;
	if(strcmp("Pgdn",Str)==0) return _Pgdn;
	if(strcmp("BackSpace",Str)==0) return _BackSpace;
	if(strcmp("Tab",Str)==0) return _Tab;
	if(strcmp("Enter",Str)==0) return _Enter;
	if(strcmp("Esc",Str)==0) return _Esc;
	return -1;
}

void KeyFz(void)
{
	KeyBuf[0]=_ShiftF1;
	KeyBuf[1]=_ShiftF2;
	KeyBuf[2]=_ShiftF3;
	KeyBuf[3]=_ShiftF4;
	KeyBuf[4]=_ShiftF5;
	KeyBuf[5]=_ShiftF6;
	KeyBuf[6]=_ShiftF7;
	KeyBuf[7]=_ShiftF8;
	KeyBuf[8]=_ShiftF9;
	KeyBuf[9]=_ShiftF10;
	KeyBuf[10]=_ShiftF11;
	KeyBuf[11]=_ShiftF12;
	KeyBuf[12]=_CtrlF1;
	KeyBuf[13]=_CtrlF2;
	KeyBuf[14]=_CtrlF3;
	KeyBuf[15]=_CtrlF4;
	KeyBuf[16]=_CtrlF5;
	KeyBuf[17]=_CtrlF6;
	KeyBuf[18]=_CtrlF7;
	KeyBuf[19]=_CtrlF8;
	KeyBuf[20]=_CtrlF9;
	KeyBuf[21]=_CtrlF10;
	KeyBuf[22]=_CtrlF11;
	KeyBuf[23]=_CtrlF12;
	KeyBuf[24]=_F1;
	KeyBuf[25]=_F2;
	KeyBuf[26]=_F3;
	KeyBuf[27]=_F4;
	KeyBuf[28]=_F5;
	KeyBuf[29]=_F6;
	KeyBuf[30]=_F7;
	KeyBuf[31]=_F8;
	KeyBuf[32]=_F9;
	KeyBuf[33]=_F10;
	KeyBuf[34]=_F11;
	KeyBuf[35]=_F12;
	KeyBuf[36]=_Left;
	KeyBuf[37]=_Right;
	KeyBuf[38]=_Up;
	KeyBuf[39]=_Down;
	KeyBuf[40]=_Keypad;
	KeyBuf[41]=_PrintScr;
	KeyBuf[42]=_Insert;
	KeyBuf[43]=_Home;
	KeyBuf[44]=_End;
	KeyBuf[45]=_Pgup;
	KeyBuf[46]=_Pgdn;
	KeyBuf[47]=_BackSpace;
	KeyBuf[48]=_Tab;
	KeyBuf[49]=_Enter;
	KeyBuf[50]=_Esc;
}

void LoadKey(void)
{
	_ShiftF1=KeyBuf[0];
	_ShiftF2=KeyBuf[1];
	_ShiftF3=KeyBuf[2];
	_ShiftF4=KeyBuf[3];
	_ShiftF5=KeyBuf[4];
	_ShiftF6=KeyBuf[5];
	_ShiftF7=KeyBuf[6];
	_ShiftF8=KeyBuf[7];
	_ShiftF9=KeyBuf[8];
	_ShiftF10=KeyBuf[9];
	_ShiftF11=KeyBuf[10];
	_ShiftF12=KeyBuf[11];
	_CtrlF1=KeyBuf[12];
	_CtrlF2=KeyBuf[13];
	_CtrlF3=KeyBuf[14];
	_CtrlF4=KeyBuf[15];
	_CtrlF5=KeyBuf[16];
	_CtrlF6=KeyBuf[17];
	_CtrlF7=KeyBuf[18];
	_CtrlF8=KeyBuf[19];
	_CtrlF9=KeyBuf[20];
	_CtrlF10=KeyBuf[21];
	_CtrlF11=KeyBuf[22];
	_CtrlF12=KeyBuf[23];
	_F1=KeyBuf[24];
	_F2=KeyBuf[25];
	_F3=KeyBuf[26];
	_F4=KeyBuf[27];
	_F5=KeyBuf[28];
	_F6=KeyBuf[29];
	_F7=KeyBuf[30];
	_F8=KeyBuf[31];
	_F9=KeyBuf[32];
	_F10=KeyBuf[33];
	_F11=KeyBuf[34];
	_F12=KeyBuf[35];
	_Left=KeyBuf[36];
	_Right=KeyBuf[37];
	_Up=KeyBuf[38];
	_Down=KeyBuf[39];
	_Keypad=KeyBuf[40];
	_PrintScr=KeyBuf[41];
	_Insert=KeyBuf[42];
	_Home=KeyBuf[43];
	_End=KeyBuf[44];
	_Pgup=KeyBuf[45];
	_Pgdn=KeyBuf[46];
	_BackSpace=KeyBuf[47];
	_Tab=KeyBuf[48];
	_Enter=KeyBuf[49];
	_Esc=KeyBuf[50];
}
//此四函数指针给signal()保存原先的软中断的处理例程  ??
void (*icbhup)(int);
void (*icbint)(int);
void (*icbquit)(int);
void (*icbterm)(int);

void IntProcess(int Tmpi)
{
	KeyValue=_DelKey;
	signal(SIGINT,IntProcess);
	signal(SIGQUIT,IntProcess);
}

void set_sig(void) // get signal
{
	icbhup=signal(SIGHUP,SIG_IGN);
	icbint=signal(SIGINT,IntProcess);
	icbquit=signal(SIGQUIT,IntProcess);
	icbterm=signal(SIGTERM,SIG_IGN);
}

void unset_sig(void) // free signal
{
	signal(SIGHUP,icbhup);
	signal(SIGINT,icbint);
	signal(SIGQUIT,icbquit);
	signal(SIGTERM,icbterm);
}
//此函数分配共享内存
//Pid 为共享内存的代号
//Leng为共享内存的长度
//成功 1 失败返回 0
char CreatShareMem(long Pid, long Leng)
{
	int 		icbshmid;
	int 		icbsemid;
	char 		*Buf;
	union semun
	{
		int 			val;
		struct semid_ds 	*buf;
		unsigned short 		*array;
	} sem_arg;

	struct semid_ds sem_buf;
	struct shmid_ds shm_buf;

	set_sig();
	if((icbsemid=semget(Pid,1,IPC_CREAT|IPC_EXCL|0660))<0)
	{
		unset_sig();
		return 0;
	}

	sem_arg.buf=&sem_buf;
	sem_buf.sem_perm.uid=getuid();
	sem_buf.sem_perm.gid=getgid();
	sem_buf.sem_perm.mode=0666;

	if(semctl(icbsemid,1,IPC_SET,sem_arg)<0)
	{
		unset_sig();
		return 0;
	}

	if(semop(icbsemid,&icb_lock[0],2)<0)    //共享内存权限检查
	{
		unset_sig();
		return 0;
	}

	if((icbshmid=shmget(Pid,Leng*sizeof(char),\
    	    IPC_CREAT|IPC_EXCL|0660))<0)
	{
		semop(icbsemid,&icb_unlock[0],1);
		unset_sig();
		return 0;
	}
	shm_buf.shm_perm.uid=getuid();
	shm_buf.shm_perm.gid=getgid();
	shm_buf.shm_perm.mode=0666;

	if(shmctl(icbshmid,IPC_SET,&shm_buf)<0)
	{
		semop(icbsemid,&icb_unlock[0],1);
		unset_sig();
		return 0;
	}
	if((Buf=(char *)shmat(icbshmid,(char *)0,0))==NULL)
	{
		semop(icbsemid,&icb_unlock[0],1);
		unset_sig();
		return 0;
	}
	shmdt((char *)Buf);
	semop(icbsemid,&icb_unlock[0],1);
	unset_sig();
	return 1;
}

//删除共享内存
//Pid为共享内存代码
void DelShareMem(long Pid)
{
	union semun
	{
		int 			val;
		struct semid_ds 	*buf;
		unsigned short 		*array;
	} sem_arg;

	struct semid_ds 	sem_buf;
	struct shmid_ds 	shm_buf;
	int 			icbshmid;
	int 			icbsemid;

	set_sig();
	icbsemid=semget(Pid,1,0);
 	sem_arg.buf = &sem_buf;
	semctl(icbsemid,1,IPC_RMID,sem_arg);
	icbshmid=shmget(Pid,10,0);
	shmctl(icbshmid,IPC_RMID,&shm_buf);
	unset_sig();
}

//此函数读写共享内存
//Pid为共享内存代码
//Leng为此共享内存长度
//ShareBuf为共享内存数据指针
//Buf为数据指针
//ShareStart 为共享内存起始地址
//CopyLeng为需要存取的数据长度
//Mode == Share2MemMode Mem2ShareMode
//成功返回 1 失败返回 0 
char AccessShareMem(long Pid, long Leng, char *Buf, long ShareStart, 
			long CopyLeng, char Mode)
{
	int 		icbshmid;
	int 		icbsemid;
	char		*ShareBuf;

	set_sig();
	icbsemid=semget((key_t)Pid,1,0);
	if(semop(icbsemid,&icb_lock[0],2)<0)
	{
		unset_sig();
		return 0;
	}
	if((icbshmid=shmget(Pid,Leng,0))<0)
	{
		semop(icbsemid,&icb_unlock[0],1);
		unset_sig();
		return 0;
	}

	if((ShareBuf=(char *)shmat(icbshmid,(char *)0,0))==NULL)
	{
		semop(icbsemid,&icb_unlock[0],1);
		unset_sig();
		return 0;
	}
	if(Mode==Share2MemMode)
		memcpy(Buf, ShareBuf+ShareStart, CopyLeng);
	else if(Mode==Mem2ShareMode)
		memcpy(ShareBuf+ShareStart, Buf, CopyLeng);
	else return 0;
	shmdt((char *)ShareBuf);
	semop(icbsemid,&icb_unlock[0],1);
	unset_sig();
	return(1);
}

long GetPid(void)
{
	char	Str[40];
	long	i, j;
	strcpy(Str, (char *)ttyname(0));
	for(i=0,j=0;Str[i];i++)
		j+=Str[i];
	return j;
}

char GetReturn(void)
{
	long			Pid;
	long			i;

	Pid=GetPid();
	if(!AccessShareMem(Pid, sizeof(struct ReturnStru),
 	(char *)(&_return),0,sizeof(struct ReturnStru), Share2MemMode))
	{
		DelShareMem(Pid);
		_returnnr.ReturnFlag=0;
		return 0;
	}
	else
		_returnnr.ReturnFlag=1;
	i=_return.Leng;

	if(_return.ResultLeng)
	{
		if((_returnnr.Result=(char *)malloc(_return.ResultLeng))==NULL)
		{
			_returnnr.Flag=0;
			DelShareMem(Pid);
			return 0;
		}
	}
	else
		_returnnr.Result=NULL;

	if(!AccessShareMem(Pid, i, (char *)(&_returnnr.Flag),
	_return.FlagStart, 1, Share2MemMode))
	{
		DelShareMem(Pid);
		return 0;
	}

	if(_returnnr.Result)
	{
		if(!AccessShareMem(Pid, i, (char *)(_returnnr.Result),
		_return.ResultStart, _return.ResultLeng, Share2MemMode))
		{
			DelShareMem(Pid);
			return 0;
		}
	}
	DelShareMem(Pid);
	return 1;
}

char  PutSec(char *FileName, char *Pass)
{
	FILE 	*fp, *fp1;
	char	Str[180];
	int	i, j, k;
	if((fp=fopen(FileName,"rb"))==NULL)
		return 0;
	strcat(FileName, ".bak");
	if((fp1=fopen(FileName,"wb"))==NULL)
		return 0;
	for(k=0;;)
	{
		i=fread(Str, sizeof(char), 180, fp);
		for(j=0;j<i;j++)
		{
			Str[j]^=Pass[k%strlen(Pass)];
			k++;
		}
		fwrite(Str, sizeof(char), i, fp1);
		if(i<180)
			break;
	}
	fclose(fp);
	fclose(fp1);
	return 1;
}

//此函数得到字符串中以Fgch1 和 Fgch2 分隔的那部分
void GetFormStr(char Fgch1, char Fgch2, int Num, char *Str, char *Str1)
{
	int	i;
	char	Fgchs[2];
	char	*p;
	char 	*p1;

	Fgchs[0]=Fgch1;
	Fgchs[1]=0;
	p1=p=Str;
	for(i=0;i<Num;i++)
	{
		p1=strstr(p,Fgchs);
		if(p1)
			p=p1+1;
		else
			break;
	}
	if(p1==NULL)
	{
		Str1[0]=0;
		return;
	}
	if(*p1==Fgchs[0])
		p1++;
	Fgchs[0]=Fgch2;
	Fgchs[1]=0;
	if((p=strstr(p1,Fgchs))==NULL)
	{
		Str1[0]=0;
		return;
	}
	memcpy(Str1, p1, p-p1);
	Str1[p-p1]=0;
}

//此函数生成系统数据
//成功返回 1 失败返回 0
char  GetSysData(char *FileName)
{
	char		Str[400];
	char		Str1[180];
	char		Str2[180];
	char		*p;
	int		i;
	FILE		*fp;
	time_t		t1;
	struct tm 	*t2;
	if((fp=fopen(FileName,"rt"))==NULL)
	{
		printf("Can't open sysdat file %s\n",FileName);
		return 0;
	}

	Str[0]=0;
	fgets(Str,400,fp);
	GetFormStr(',', '.', 20, Str, Str1);
	if(Str[0]==0||Str[0]!='#'||strcmp(Str1,"lpf")!=0)
	{
		printf("Not Menu File, Program exit!\n");
		return 0;
	}

	GetFormStr('#', ',', 0, Str, Str1);
	SysPar.Flag=atoi(Str1);
	GetFormStr(',', ',', 3, Str, Str1);
	strcpy(SysPar.ExeResFileName,Str1);
	for(i=0;SysPar.ExeResFileName[i]==' ';i++);
	memmove(SysPar.ExeResFileName, &SysPar.ExeResFileName[i],\
	strlen(&SysPar.ExeResFileName[i])+1);
	GetFormStr(',', ',', 4, Str, Str1);
	strcpy(SysPar.MenuFileName,Str1);
	for(i=0;SysPar.MenuFileName[i]==' ';i++);
	memmove(SysPar.MenuFileName, &SysPar.MenuFileName[i],\
	strlen(&SysPar.MenuFileName[i])+1);
	for(i=strlen(SysPar.MenuFileName)-1;i>=0;i--)
	{
		if(SysPar.MenuFileName[i]=='/')
		{
			memmove(SysPar.MenuFileName, &SysPar.MenuFileName[i+1],\
			strlen(&SysPar.MenuFileName[i+1])+1);
		}
	}
	//sprintf(Str1,"%s",SysPar.MenuFileName);
	//strcpy(SysPar.MenuFileName,Str1);
	sprintf(Str1,"%s",FileName);
	Str1[strlen(Str1)-4]=0;
	strcpy(Str2,Str1);
	for(i=strlen(Str2)-1;i>=0;i--)
	{
		if(Str2[i]=='/')
			memmove(Str2, &Str2[i+1],strlen(&Str2[i+1])+1);
	}
	if(strcmp(Str2,SysPar.MenuFileName))
	{
		printf("Menu File not equal Menuctrl file , Program exit! [%s] %s\n",Str1,SysPar.MenuFileName);
		return 0;
	}
	strcpy(SysPar.MenuFileName, Str1);
	GetFormStr(',', ',', 5, Str, Str1);
	SysPar.QdCtrl=atoi(Str1);
	GetFormStr(',', ',', 6, Str, Str1);
	SysPar.AccessCtrl=atoi(Str1);

	GetFormStr(',', ',', 7, Str, Str1);
	strcpy(SysPar.DataBaseName1,Str1);
	for(i=0;SysPar.DataBaseName1[i]==' ';i++);
	memmove(SysPar.DataBaseName1, &SysPar.DataBaseName1[i],\
	strlen(&SysPar.DataBaseName1[i])+1);
	GetFormStr(',', ',', 8, Str, Str1);
	if(Str1[0]!='1'&&Str1[0]!='2')	 Str1[0]='1';
	SysPar.DBType1=Str1[0];

	GetFormStr(',', ',', 9, Str, Str1);
	strcpy(SysPar.DataBaseName2,Str1);
	for(i=0;SysPar.DataBaseName2[i]==' ';i++);
	memmove(SysPar.DataBaseName2, &SysPar.DataBaseName2[i],\
	strlen(&SysPar.DataBaseName2[i])+1);
	GetFormStr(',', ',', 10, Str, Str1);
	if(Str1[0]!='1'&&Str1[0]!='2')	 Str1[0]='1';
	SysPar.DBType2=Str1[0];

	GetFormStr(',', ',', 11, Str, Str1);
	strcpy(SysPar.DataBaseName3,Str1);
	for(i=0;SysPar.DataBaseName3[i]==' ';i++);
	memmove(SysPar.DataBaseName3, &SysPar.DataBaseName3[i],\
	strlen(&SysPar.DataBaseName3[i])+1);
	GetFormStr(',', ',', 12, Str, Str1);
	if(Str1[0]!='1'&&Str1[0]!='2')	 Str1[0]='1';
	SysPar.DBType3=Str1[0];

	GetFormStr(',', ',', 13, Str, Str1);
	strcpy(SysPar.DataBaseName4,Str1);
	for(i=0;SysPar.DataBaseName4[i]==' ';i++);
	memmove(SysPar.DataBaseName4, &SysPar.DataBaseName4[i],\
	strlen(&SysPar.DataBaseName4[i])+1);
	GetFormStr(',', ',', 14, Str, Str1);
	if(Str1[0]!='1'&&Str1[0]!='2')	 Str1[0]='1';
	SysPar.DBType4=Str1[0];

	GetFormStr(',', ',', 15, Str, Str1);
	strcpy(SysPar.DataBaseName5,Str1);
	for(i=0;SysPar.DataBaseName5[i]==' ';i++);
	memmove(SysPar.DataBaseName5, &SysPar.DataBaseName5[i],\
	strlen(&SysPar.DataBaseName5[i])+1);
	GetFormStr(',', ',', 16, Str, Str1);
	if(Str1[0]!='1'&&Str1[0]!='2')	 Str1[0]='1';
	SysPar.DBType5=Str1[0];

	GetFormStr(',', ',', 17, Str, Str1);
	strcpy(SysPar.DataBaseName6,Str1);
	for(i=0;SysPar.DataBaseName6[i]==' ';i++);
	memmove(SysPar.DataBaseName6, &SysPar.DataBaseName6[i],\
	strlen(&SysPar.DataBaseName6[i])+1);
	GetFormStr(',', ',', 18, Str, Str1);
	if(Str1[0]!='1'&&Str1[0]!='2')	 Str1[0]='1';
	SysPar.DBType6=Str1[0];

	GetFormStr(',', ',', 19, Str, Str1);
	Str1[ScrEy-18]=0;
	strcpy(SysPar.GsName, Str1);

	fclose(fp);
	SysPar.Term[0]=0;
	SysPar.Printer[0]=0;
	SysPar.Password[0]=0;
	SysPar.ClockFlag='1';
	SysPar.Jrdmdy[0]=0;
	SysPar.Dcdmdy[0]=0;
	SysPar.Zdfd[0]=0;
	SysPar.Zdhy[0]=0;
	SysPar.Hjj[0]=0;
	SysPar.Zjj[0]=0;
	SysPar.PrintInit[0]=0;
	SysPar.Printhy[0]=0;
	if(SysPar.OpeNo[0]==0)
		SysPar.OpeNo[0]=0;

	strcpy(SysPar.ttyname, (char *)ttyname(0)+5);
	SysPar.ProcessId=GetPid();
	t1=time(0);
	t2=localtime(&t1);

	SysPar.Year=t2->tm_year+1900;
	SysPar.Month=t2->tm_mon+1;
	SysPar.Day=t2->tm_mday;
	SysPar.Week=t2->tm_wday;
	SysPar.Today=t2->tm_yday+1;

	sprintf(SysPar.SysDate,"%04d%02d%02d",
		t2->tm_year+1900,t2->tm_mon+1, t2->tm_mday);
	sprintf(SysPar.KeyFile,"%s/%skey.dat",ConfDir,SysPar.ttyname);
	return 1;
}

void parse(char *buf,char **args)
{
	while(*buf!='\0')
	{
		while((*buf==' ')||(*buf=='\t') || (*buf=='\n'))
		*buf++=0;
		*args++=buf;
		while((*buf!='\0')&&(*buf!=' ')&&(*buf!='\t')&&(*buf!='\n')) buf++;
 	}
	*args=0;
}

//此函数传送系统信息到共享内存以便子进程使用
char TranSysPar(void)
{
	long			i;
	long			Leng, Leng1, Leng2, Leng3;

	SysTran.Deep=0;
	DelShareMem(SysPar.ProcessId);
	Leng=sizeof(struct SysTranStru);

	SysTran.MenuStart=Leng;
	for(i=0;MenuArry&&(MenuArry+i)->MenuNum;i++)
	Leng1=i*sizeof(struct MenuOptStru);
	SysTran.MenuLeng=Leng1;

	SysTran.OpeAccessStart=Leng+Leng1;
	for(i=0;OpeAccess&&(OpeAccess+i)->OpeCode;i++);
	Leng2=i*sizeof(struct OpeAccessStru);
	SysTran.OpeAccessLeng=Leng2;

	SysTran.SysInfStart=Leng+Leng1+Leng2;
	Leng3=sizeof(struct SysParStru);
	SysTran.SysInfLeng=Leng3;
	
	SysTran.KeyStart=Leng+Leng1+Leng2+Leng3;
	SysTran.KeyLeng=sizeof(KeyBuf);

	i=Leng+Leng1+Leng2+Leng3+sizeof(KeyBuf)+6;
	if(i%2)		i++;
	SysTran.ShareMemSize=i;
	SysTran.CheckNum=SysTran.CurrentMenuNum+SysTran.CallFlag+
			 SysTran.ShareMemSize+
			 SysTran.MenuStart+SysTran.MenuLeng+
			 SysTran.OpeAccessStart+SysTran.OpeAccessLeng+
			 SysTran.SysInfStart+SysTran.SysInfLeng+
			 SysTran.KeyStart+SysTran.KeyLeng;
	if(CreatShareMem(SysPar.ProcessId, i)==0)
	{
		DispMenuPro("不能创建共享内存");
		getchar();
		return 0;
	}
	
	if(!AccessShareMem(SysPar.ProcessId, i, 
	(char *)(&SysTran),0, Leng, Mem2ShareMode))
	{
		DispMenuPro("把系统参数拷贝到共享内存出错");
		getchar();
		return 0;
	}

	if(SysTran.MenuLeng)
	{
		if(!AccessShareMem(SysPar.ProcessId, i, 
		(char *)(MenuArry),SysTran.MenuStart, SysTran.MenuLeng, Mem2ShareMode))
		{
			DispMenuPro("把系统参数拷贝到共享内存出错");
			getchar();
			return 0;
		}
	}

	if(SysTran.OpeAccessLeng)
	{
		if(!AccessShareMem(SysPar.ProcessId, i, 
		(char *)(OpeAccess),SysTran.OpeAccessStart, SysTran.OpeAccessLeng, 
		Mem2ShareMode))
		{
			DispMenuPro("把系统参数拷贝到共享内存出错");
			getchar();
			return 0;
		}
	}

	if(!AccessShareMem(SysPar.ProcessId, i, (char *)(&SysPar),
	SysTran.SysInfStart, SysTran.SysInfLeng, Mem2ShareMode))
	{
		DispMenuPro("把系统参数拷贝到共享内存出错");
		getchar();
		return 0;
	}

	KeyFz();
	KeyBuf[51]=ScrEx;
	if(!AccessShareMem(SysPar.ProcessId, i, (char *)(KeyBuf),
	SysTran.KeyStart, SysTran.KeyLeng, Mem2ShareMode))
	{
		DispMenuPro("把系统参数拷贝到共享内存出错");
		getchar();
		return 0;
	}
	return 1;
}

char execute(char **args)
{
	int 	status, Pid;
	char 	Str[80], Flag=1;

	if(!TranSysPar())
		return;
	if((Pid=fork())<0)
 	{
		DispMenuPro("创建子进程失败, 敲回车继续!");
		for(;GetKey1()!=_Enter;);
		return 0;
	}

	if(Pid==0)
	{
		if(execvp(*args,args)==-1)
		{
			Flag=0;
			DispMenuPro("无此命令, 敲回车继续!");
			for(;GetKey1()!=_Enter;);
			Pid=getpid();		
			sprintf(Str, "kill -9 %d", Pid);
			system(Str);
		}
	}
	for(;wait(&status)!=Pid;);
	if(Flag==0) 	return 0;
	else  		return 1;
}

char SysCall(char *comm)
{
	char 	comm1[80];
	char 	*args[64];
	char	Str1[40];
	char	Flag;
	int	i;

	strcpy(comm1,comm);
	for(i=0, Flag=0;comm1[i];i++)
	{
		if(comm1[i]=='@')
		{
			memmove(&comm1[i], &comm1[i+1], strlen(&comm1[i+1])+1);
			Flag=1;
		}
	}
	if(SysPar.QdCtrl&&!SysPar.OpeNo[0]&&Flag==0)
	{
		DispMenuPro("请签到后再使用此功能, 敲回车继续!");
		for(;GetKey1()!=_Enter;);
		return 0;
	}
	alarm(0);
	parse(comm1,args);
	if(execute(args))
	{
		if(GetReturn())
		{
			GetFormStr(',',',', 0, _returnnr.Result, Str1); 
			if(strcmp(Str1,"login")==0)
			{
				GetFormStr(',',',', 1, _returnnr.Result, Str1); 
				SysPar.OpeWhere=atoi(Str1);
				GetFormStr(',',',', 2, _returnnr.Result, Str1); 
				strcpy(SysPar.OpeNo,Str1);
				GetFormStr(',',',', 3, _returnnr.Result, Str1); 
				strcpy(SysPar.OpeName,Str1);
				GetFormStr(',',',', 4, _returnnr.Result, Str1); 
				SysPar.Level=atoi(Str1);
			}
			if(strcmp(Str1,"loginout")==0)
			{
				GetFormStr(',',',', 1, _returnnr.Result, Str1); 
				if(atoi(Str1)==1)
					SysPar.OpeNo[0]=0;
			}
		}
		if(SysPar.ClockFlag=='1')
		{
			signal(SIGALRM, Clock);
			alarm(1);
		}
		return 1;
	}
	else
	{
		if(SysPar.ClockFlag=='1')
		{
			signal(SIGALRM, Clock);
			alarm(1);
		}
		return 0;
	}
}

//此函数分配菜单结构的指针空间
//FileName为菜单的数据文件
//Menu为菜单结构指针
//成功Menu为非空,否则返加NULL
int MallocMenuStru(char *FileName)
{
	FILE 		*fp;
	char		Str[300];
	char		*p, *p1;
	int		MenuCount=0;
	if((fp=fopen(FileName,"rt")))
	{
		for(;fgets(Str,300,fp)!=NULL;)
		{
			if((p=strstr(Str,"/*")))
			{
				if((p1=strstr((p+1),"*/")))
					memmove(p, p1+2, strlen(p1+2)+1);
				else
					*p=0;
			}
			if(Str[0]!='@')
			{
				MenuCount++;
				continue;
			}
			else
				MenuCount++;
		}
	}
	fclose(fp);
	MenuCount++;
	if(MenuCount%2)
		MenuCount++;
	MenuArry=(struct MenuOptStru *)\
			malloc(MenuCount*sizeof(struct MenuOptStru));
	return MenuCount;
}


//此函数读入菜单结构的内容
//FileName为菜单的数据文件
//Menu为菜单结构指针
void InitMenuStru(char *FileName, struct MenuOptStru *Menu, int MenuCount)
{
	FILE 		*fp;
	char		Str[300], Str1[80];
	char		*p, *p1;
	int			i;
	for(i=0;i<MenuCount;i++)
	{
		(Menu+i)->LOpt=NULL;
		(Menu+i)->ROpt=NULL;
		(Menu+i)->UOpt=NULL;
		(Menu+i)->DOpt=NULL;
		(Menu+i)->Sx=0;
		(Menu+i)->Sy=0;
		(Menu+i)->RanSx=0;
		(Menu+i)->RanSy=0;
		(Menu+i)->RanEx=0;
		(Menu+i)->RanEy=0;
		(Menu+i)->MenuNum=0;
		(Menu+i)->MenuName[0]=0;
		(Menu+i)->ProInf[0]=0;
		(Menu+i)->Command[0]=0;
		(Menu+i)->JyCode=0;
		(Menu+i)->HotKey[0]=0;
	}

	if(!(fp=fopen(FileName,"rt")))
		return;

	for(i=0;fgets(Str,300,fp)!=NULL;)
	{
		if((p=strstr(Str,"/*")))
		{
			if((p1=strstr((p+1),"*/")))
				memmove(p, p1+2, strlen(p1+2)+1);
			else
				*p=0;
		}
		if(Str[0]!='@')
			continue;
		else
		{
			GetFormStr('@', ',', 1, Str, (Menu+i)->ProInf);
			(Menu+i)->MenuNum=atoi((Menu+i)->ProInf);
			if((Menu+i)->MenuNum<0)
			{
				(Menu+i)->MenuNum=0;
				continue;
			}
			GetFormStr(',', ',', 1, Str, (Menu+i)->MenuName);
			GetFormStr(',', ',', 2, Str, (Menu+i)->Command);
			GetFormStr(',', ',', 3, Str, (Menu+i)->ProInf);
			GetFormStr(',', ',', 4, Str, Str1);
			(Menu+i)->JyCode=atoi(Str1);
			GetFormStr(',', ',', 5, Str, (Menu+i)->HotKey);
			if(CheckAllKey((Menu+i)->HotKey)==-1)
				(Menu+i)->HotKey[0]=0;
			//GetFormStr(',', '.', 6, Str, Str1);
			i++;
		}
	}
	fclose(fp);
}

//本函数找到一个菜单项的前一级, 后一级, 左一级, 右一级
//MaxMenuNum为本级菜单中MenuNum最大项
//MaxMenuNum为本级菜单中MenuNum最小项
//LCloseMenuNum为最左靠近形参MenuNum的菜单项
//RCloseMenuNum为最右靠近形参MenuNum的菜单项
void FindMenu(struct MenuOptStru *MenuA, struct MenuOptStru *FindMenu[], long MenuNum)
{
	char 	cFlag;
	int		i, j, k, Max, Min, LCloseMenuNum, RCloseMenuNum;
	long 	MaxMenuNum, MinMenuNum;
	for(i=0,cFlag=0;(MenuA+i)->MenuNum!=0;i++)			//找到菜单的前一级
	{
		if(MenuNum/100==0)
		{
			FindMenu[0]=NULL;
			cFlag=1;
			break;
		}
		else if((MenuA+i)->MenuNum==MenuNum/100)
		{
			FindMenu[0]=MenuA+i;
			cFlag=1;
			break;
		}
	}
	if(!cFlag) 	FindMenu[0]=NULL;

	MaxMenuNum=MenuNum*100+99;			//找到菜单的后一级
	MinMenuNum=MenuNum*100;
	for(i=0,cFlag=0,j=0;(MenuA+i)->MenuNum!=0;i++)
	{
		if((MenuA+i)->MenuNum<=MaxMenuNum&&(MenuA+i)->MenuNum>MinMenuNum)
		{
			j=i;
			cFlag=1;
			MaxMenuNum=(MenuA+i)->MenuNum;
		}
	}
	if(!cFlag)	FindMenu[1]=NULL;
	else      	FindMenu[1]=MenuA+j;

	MinMenuNum=MenuNum/100*100+99;			//找到同级菜单中的最大级
	MaxMenuNum=MenuNum/100*100;
	for(i=0,cFlag=0,j=0;(MenuA+i)->MenuNum!=0;i++)
	{
		if((MenuA+i)->MenuNum>MaxMenuNum&&(MenuA+i)->MenuNum<=MinMenuNum)
		{
			if((MenuA+i)->MenuNum>MaxMenuNum)
			{
				MaxMenuNum=(MenuA+i)->MenuNum;
				j=i;
				cFlag=1;
			}
		}
	}
	if(!cFlag)	Max=-1;
	else		Max=j;
	MinMenuNum=MenuNum/100*100+99;			//找到同级菜单中的最小级
	MaxMenuNum=MenuNum/100*100;
	for(i=0,cFlag=0,j=0;(MenuA+i)->MenuNum!=0;i++)
	{
		if((MenuA+i)->MenuNum>MaxMenuNum&&(MenuA+i)->MenuNum<=MinMenuNum)
		{
			if((MenuA+i)->MenuNum<MinMenuNum)
			{
				MinMenuNum=(MenuA+i)->MenuNum;
				j=i;
				cFlag=1;
			}
		}
	}
	if(!cFlag)	Min=-1;
	else		Min=j;

	MinMenuNum=MenuNum/100*100+99;			//找到同级菜单中的最左级
	MaxMenuNum=MenuNum/100*100;
	for(i=0,cFlag=0,j=0,k=100;(MenuA+i)->MenuNum!=0;i++)
	{
		if((MenuA+i)->MenuNum>MaxMenuNum&&(MenuA+i)->MenuNum<=MinMenuNum)
		{
			if((MenuA+i)->MenuNum<MenuNum)
			{
				if(MenuNum-(MenuA+i)->MenuNum<k)
				{
					k=(int)(MenuNum-(MenuA+i)->MenuNum);
					j=i;
					cFlag=1;
				}
			}
		}
	}
	if(!cFlag)	LCloseMenuNum=-1;
	else		LCloseMenuNum=j;

	MinMenuNum=MenuNum/100*100+99;			//找到同级菜单中的最右级
	MaxMenuNum=MenuNum/100*100;
	for(i=0,cFlag=0,j=0,k=100;(MenuA+i)->MenuNum!=0;i++)
	{
		if((MenuA+i)->MenuNum>MaxMenuNum&&(MenuA+i)->MenuNum<=MinMenuNum)
		{
			if((MenuA+i)->MenuNum>MenuNum)
			{
				if((MenuA+i)->MenuNum-MenuNum<k)
				{
					k=(int)((MenuA+i)->MenuNum-MenuNum);
					j=i;
					cFlag=1;
				}
			}
		}
	}
	if(!cFlag)	RCloseMenuNum=-1;
	else		RCloseMenuNum=j;

	if(RCloseMenuNum==-1)       			//生成菜单中的左右级
	{
		if(Min!=-1)
			RCloseMenuNum=Min;
	}

	if(LCloseMenuNum==-1)
	{
		if(Max!=-1)
			LCloseMenuNum=Max;
	}
	if(LCloseMenuNum!=-1)
		FindMenu[2]=MenuA+LCloseMenuNum;
	else
		FindMenu[2]=NULL;

	if(RCloseMenuNum!=-1)
		FindMenu[3]=MenuA+RCloseMenuNum;
	else
		FindMenu[3]=NULL;
}

//此函数生成各菜单项在屏幕中的位置
//此函数是递归函数
//Mode为一级菜单置计算, Mode=AutoCalMode为自动计算, Mode=CalMode为定义计算
void ScMenuDist(struct MenuOptStru *MenuA, char Mode)
{
	int			i, Tmp;
	int			Lengx, Lengy, StrLeng;
	long		MenuNum;

	if(MenuA==NULL)		return;
	MenuNum=MenuA->MenuNum/100*100+99;
	if(MenuNum<100)
	{
		Lengx=OneMenuStartX;
		Lengy=OneMenuStartY;
		if(Mode!=AutoCalMode)
		{
			for(i=0;(MenuA+i)->MenuNum<MenuNum&&(MenuA+i)->MenuNum!=0;i++)
			{
				(MenuA+i)->Sx=Lengx;
				(MenuA+i)->Sy=Lengy;
				Lengy+=strlen((MenuA+i)->MenuName)+OneMenuDist;
				if(Lengy>ScrEy)
				{
					Lengy=0;
					Lengx+=1;
					(MenuA+i)->Sx=Lengx;
					(MenuA+i)->Sy=Lengy;
					Lengy=strlen((MenuA+i)->MenuName)+OneMenuDist; 
				}
			}
		}
		else
		{
			StrLeng=0;
			for(i=0;(MenuA+i)->MenuNum<MenuNum&&(MenuA+i)->MenuNum!=0;i++)
				StrLeng+=strlen((MenuA+i)->MenuName);

			StrLeng=ScrEy-OneMenuStartY-StrLeng;
			if(i>1)
				i--;
			Tmp=StrLeng-StrLeng/i*i;	
			StrLeng/=i;
			
			if(StrLeng<0) 		StrLeng=0;
			Lengx=OneMenuStartX;
			Lengy=OneMenuStartY;
			for(i=0;(MenuA+i)->MenuNum<MenuNum&&(MenuA+i)->MenuNum!=0;i++)
			{
				(MenuA+i)->Sx=Lengx;
				(MenuA+i)->Sy=Lengy;
				if(Tmp>0)
				{
					Lengy+=strlen((MenuA+i)->MenuName)+StrLeng+1;
					Tmp--;
				}
				else
					Lengy+=strlen((MenuA+i)->MenuName)+StrLeng;
			}
		}
		for(i=0;(MenuA+i)->MenuNum<MenuNum&&(MenuA+i)->MenuNum!=0;i++)
			ScMenuDist((MenuA+i)->DOpt, Mode);
	}
	else if(MenuNum<10000)    //二级菜单
	{
		Lengx=MenuA->UOpt->Sx + TwoMenuKStartX;
		Lengy=MenuA->UOpt->Sy + TwoMenuKStartY;
		MenuA->UOpt->RanSx=Lengx;
		MenuA->UOpt->RanSy=Lengy;
		Lengx+=TwoMenuStartX;
		Lengy+=TwoMenuStartY;

		for(i=0, StrLeng=0;(MenuA+i)->MenuNum<MenuNum&&
			(MenuA+i)->MenuNum!=0;i++)
		{
			if(strlen((MenuA+i)->MenuName)>StrLeng)
				StrLeng=strlen((MenuA+i)->MenuName);
		}

		if(StrLeng%2) 	StrLeng+=1;
		if(Lengy+StrLeng+2>ScrEy)
		{
			Lengy=ScrEy-StrLeng-4;
			MenuA->UOpt->RanSy=Lengy;
			Lengy+=TwoMenuStartY;
		}

		for(i=0;(MenuA+i)->MenuNum<MenuNum&&
			(MenuA+i)->MenuNum!=0;i++)
		{
			(MenuA+i)->Sx=Lengx;
			(MenuA+i)->Sy=Lengy;
			if((MenuA+i)->MenuName[0]=='-')	Lengx+=FgDist;
			else 							Lengx+=TwoMenuDist;
		}

		MenuA->UOpt->RanEx=Lengx - TwoMenuDist + TwoMenuKStartX;
		MenuA->UOpt->RanEy=Lengy + StrLeng + TwoMenuKStartY;
		for(i=0;(MenuA+i)->MenuNum<MenuNum&&(MenuA+i)->MenuNum!=0;i++)
			ScMenuDist((MenuA+i)->DOpt, Mode);
	}
	else
	{
		Lengx=MenuA->UOpt->Sx + ThrMenuKStartX;
		Lengy=MenuA->UOpt->UOpt->RanEy + ThrMenuKStartY + 2;
		MenuA->UOpt->RanSx=Lengx;
		MenuA->UOpt->RanSy=Lengy;
		Lengx+=ThrMenuStartX;
		Lengy+=ThrMenuStartY;

		for(i=0, StrLeng=0;(MenuA+i)->MenuNum<MenuNum&&
			(MenuA+i)->MenuNum!=0;i++)
		{
			if(strlen((MenuA+i)->MenuName)>StrLeng)
				StrLeng=strlen((MenuA+i)->MenuName);
		}

		if(StrLeng%2) 	StrLeng+=1;

		if(Lengy+StrLeng+2>ScrEy||MenuA->UOpt->Sy<MenuA->UOpt->UOpt->Sy)
		{
			Lengy=MenuA->UOpt->Sy-StrLeng-6;
			MenuA->UOpt->RanSy=Lengy;
			Lengy+=TwoMenuStartY;
		}

		for(i=0;(MenuA+i)->MenuNum<MenuNum&&(MenuA+i)->MenuNum!=0;\
			i++)
		{
			(MenuA+i)->Sx=Lengx;
			(MenuA+i)->Sy=Lengy;
			if((MenuA+i)->MenuName[0]=='-')	Lengx+=FgDist;
			else 							Lengx+=ThrMenuDist;
		}

		MenuA->UOpt->RanEx=Lengx + ThrMenuKStartX;
		MenuA->UOpt->RanEy=Lengy + StrLeng + ThrMenuKStartY;
		for(i=0;(MenuA+i)->MenuNum<MenuNum&&(MenuA+i)->MenuNum!=0;i++)
			ScMenuDist((MenuA+i)->DOpt, Mode);
	}
}

void MenuInit(char *FileName, char Mode)
{
	struct MenuOptStru 		*Find[4];
	int						i, j, k;
	struct MenuOptStru 		TmpMenu, *Menu;

	i=MallocMenuStru(FileName); //扫描并分配菜单数据结构空间
	if(!MenuArry)
	{
		printf("MenuStruFile is NULL, Error from MenuInit() %d\n",i);
		exit(0);
	}
	Menu=MenuArry;
	InitMenuStru(FileName, Menu, i); //读入菜单结构内容
	for(i=0;(Menu+i)->MenuNum!=0;i++);//对各菜单项按MenuNum进行冒泡排序
	if(i==0)
	{
		strcpy(Menu->MenuName,"Please Add Menu");
		Menu->MenuNum=1;
	}
	for(j=i-1;j>=0;j--)
	{
		for(k=0;k<j;k++)
			if((Menu+k)->MenuNum>(Menu+k+1)->MenuNum)
			{
				TmpMenu=*(Menu+k);
				*(Menu+k)=*(Menu+k+1);
				*(Menu+k+1)=TmpMenu;
			}
	}

	for(j=0;(Menu+j)->MenuNum!=0;j++)//删除大于五级的菜单项
	{
		if((Menu+j)->MenuNum>1000000000l)
		{
			*(Menu+j)=*(Menu+i);
			break;
		}
	}

	for(i=0;Menu[i].MenuNum!=0;i++)//把各菜单项连成十字链表
	{
		FindMenu(Menu, Find, Menu[i].MenuNum);
		Menu[i].UOpt=Find[0];
		Menu[i].DOpt=Find[1];
		Menu[i].LOpt=Find[2];
		Menu[i].ROpt=Find[3];
	}
	ScMenuDist(Menu, Mode);	//此函数生成各菜单项在屏幕中的位置,对边界没有控制
}

int GetKey(void)
{
	int			i, j,x,y;
	char	Str[200];
	struct MenuOptStru	*P;
	cbreak();
	nonl();
	noecho();
	idlok(stdscr,TRUE);
	keypad(stdscr,1);
	for(KeyValue=0;;)
	{
		if(KeyValue==_DelKey)
			break;
		if((j=getch())!=-1)
		{
			KeyValue=j;
			if(j==27)
			{
				nodelay(stdscr, TRUE);
				for(i=0;i<4;)
				{
					if((j=getch())!=-1)
					{
						if(j==27)
						{
							ungetch(27);
							break;
						}
						KeyValue+=j;
					}
					else
						i++;
				}
				nodelay(stdscr, FALSE);
			}
			break;
		}
	}
	if(KeyValue==12)
		wrefresh(curscr);
	for(P=MenuArry,j=0;(P+j)->MenuNum;j++)
	{
		i=CheckAllKey((P+j)->HotKey);
		if(i==KeyValue&&i!=-1)
		{
			SysTran.CallFlag=1;
			SysTran.CurrentMenuNum=CurrentMenu->MenuNum;
			SysCall((P+j)->Command);
			DispWord(OneMenuStartX,ScrEy-2,"  ", NormalMode1);
			wrefresh(curscr);
			DispMenuHead();
			for(;CurrentMenu->UOpt;CurrentMenu=CurrentMenu->UOpt);
			DispMenuItem(CurrentMenu, NormalMode);
			SysTran.CallFlag=0;
		}
	}
	return KeyValue;
}

int GetKey1(void)
{
	int 	i, j,x,y;
	char	Str[200];
	cbreak();
	nonl();
	noecho();
	idlok(stdscr,TRUE);
	keypad(stdscr,1);
	for(KeyValue=0;;)
	{
		if(KeyValue==999)
			break;
		if((j=getch())!=-1)
		{
			KeyValue=j;
			if(j==27)
			{
				nodelay(stdscr, TRUE);
				for(i=0;i<4;)
				{
					if((j=getch())!=-1)
					{
						if(j==27)
						{
							ungetch(27);
							break;
						}
						KeyValue+=j;
					}
					else
						i++;
				}
				nodelay(stdscr, FALSE);
			}
			break;
		}
	}
	if(KeyValue==12)
		wrefresh(curscr);
	return KeyValue;
}

//此函数显示字符串
//Mode FbMode=反白显示, NormalMode=正常显示 
//此两个宏是不refresh() FbMode1 NormalMode1
void DispWord(int x,int y,char *Str,char Mode)
{
	if(x<0 || x>ScrEx + 1 || y<0 || y>ScrEy)
		return;
	if(y+strlen(Str)>ScrEy)
		return;
	if(Mode==FbMode)	
		standout();
	mvaddstr(x,y, Str);
	if(Mode==FbMode)
		standend();
	if(Mode==FbMode||Mode==NormalMode1)
		refresh();
}

//此函数显示一个矩形框或清除一个矩形区域
//Mode=DrawMode   Mode=ClrMode
void DispRanc(int x,int y, int x1, int y1, char Mode)
{
	int			i;
	char		Str1[81];
	char 		Str2[81];

	//if(x<0 || x>x1 || x1>ScrEx || y<0 || y>y1 || y1>ScrEy)
//		return;
 	if((x==x1)&&(y==y1))
    	return;
	if((y1-y)%2==0)
	{
		if(y1<ScrEy) 			y1++;
		else if(y>0)			y--;
		else					y++;
	}
	if(Mode==DrawMode)
	{
		memset(Str1,0,80);
		memset(Str2,0,80);
		strcpy(Str1,"┌");
		strcpy(Str2,"└");
		for(i=y+2;i<y1-2;i+=2)
		{
			strcat(Str1,"─");
			strcat(Str2,"─");
		}	
   		strcat(Str1,"┐");
		strcat(Str2,"┘");

		DispWord(x,y,Str1,NormalMode1);
		for(i=x+1;i<x1;i++)
		{
		//	memset(Str1,0,80);
		//	memset(Str1,' ',y1-y+1-4);
			DispWord(i,y,"│",NormalMode1);
		//	DispWord(i,y+2,Str1,NormalMode1);
			DispWord(i,y1-1,"│",NormalMode1);
		}
		DispWord(x1,y,Str2,NormalMode1);
	} 
	else if(Mode==ClrMode)
	{
		memset(Str1,0,80);
		memset(Str1,' ',y1-y+1);
		for(i=x;i<=x1;i++)
			DispWord(i,y,Str1,NormalMode1);
	}
	else if(Mode==ClrMode1)
	{
		move(OneMenuStartX + 1,0);
		clrtobot();
	}
}

//此函数显示一个矩形框或清除一个矩形区域
//Mode=DrawMode   Mode=ClrMode
void DispFgx(int x,int y, int y1)
{
	int			i;
	char		Str1[81];

	if(x<0 || x>ScrEx || y<0 || y>y1 || y1>ScrEy)
		return;
 	if((y==y1))
    	return;
	if((y1-y)%2==0)
	{
		if(y1<ScrEy) 		y1++;
		else if(y>0) 		y--;
		else 				y++;
	}
	memset(Str1,0,80);
	strcpy(Str1,"├");
	for(i=y;i<y1-2;i+=2)
		strcat(Str1,"─");
   	strcat(Str1,"┤");
	DispWord(x,y-2,Str1,NormalMode);
}

//此函数显示菜单亮条
void DispMenuItem(struct MenuOptStru *Menu, char Mode)
{
	if(Menu->MenuName[0]=='-')
	{
		move(ScrEx, 78);
		refresh();
		return;
	}
	if(Mode==NormalMode)
	{
		if(Menu->UOpt!=NULL)
			DispWord(Menu->Sx, Menu->Sy, Menu->MenuName, FbMode);
		else
			DispWord(Menu->Sx, Menu->Sy, Menu->MenuName, NormalMode);
		move(ScrEx, 78);
		refresh();
	}
	else 
	{
		if(Menu->UOpt!=NULL)
			DispWord(Menu->Sx, Menu->Sy, Menu->MenuName, NormalMode);
		else
		{
			DispWord(Menu->Sx, Menu->Sy, Menu->MenuName, FbMode);
			move(ScrEx, 78);
			refresh();
		}
	}
}

//此函数显示提示信息
void DispMenuPro(char *Str)
{
	char 		Str1[181];
	char 		Str2[100];
	memset(Str1,0,180);
	strcpy(Str1, "提示:");
	memset(&Str1[5],0,sizeof(Str1)-strlen(Str1));
	if(strlen(Str)>ProLeng-strlen(Str1))
		Str[ProLeng-strlen(Str1)]=0;
	strcat(Str1,Str);
	memset(&Str1[strlen(Str1)], ' ', ScrEy-strlen(Str1));
	DispWord(ScrEx,0,Str1, FbMode);
}

//此函数显示一级菜单
void DispMenuHead(void)
{
	char 					Str[800];
	char					Space[180];
	int						i;
	strcpy(Str, MenuArry->MenuName);
	memset(Space,' ',ScrEy);
	for(i=1;(MenuArry+i)->MenuNum<100&&(MenuArry+i)->MenuNum;i++)
	{
		strncat(Str,Space,(MenuArry+i)->Sy-(MenuArry+i-1)->Sy\
				-strlen((MenuArry+i-1)->MenuName));
		strcat(Str,(MenuArry+i)->MenuName);
	}
	if(strlen(Str)<ScrEy)
	{
		strncpy(&Str[strlen(Str)], Space, ScrEy-strlen(Str));
		Str[ScrEy-1]=0;	
	}
	DispWord(0,1,"[ 菜 单 系 列 ]",NormalMode);
	DispWord(0,16,"★ 浙江舟山定海城市信用社主机管理系统 ★", NormalMode);
	mvprintw(1,1,"──────────────────────────────────────");
	DispWord(MenuArry->Sx, MenuArry->Sy, Str, FbMode);
}

//此函数显示二级以下的一个菜单
//Mode = DrawMode, ClrMode
void DispMenuTwo(struct MenuOptStru *Menu, char Mode)
{
	int 					MenuNum, i;
	if(Mode==DrawMode)
	{
		DispRanc(Menu->UOpt->RanSx, Menu->UOpt->RanSy, Menu->UOpt->RanEx, 
				 Menu->UOpt->RanEy, DrawMode);
		MenuNum=Menu->MenuNum/100*100+99;
		Menu=Menu->UOpt->DOpt;
		for(i=0;(Menu+i)->MenuNum<MenuNum&&(Menu+i)->MenuNum;i++)
		{
			if((Menu+i)->MenuName[0]=='-')
				DispFgx((Menu+i)->Sx,(Menu+i)->Sy, (Menu+i)->UOpt->RanEy);
			else
				DispWord((Menu+i)->Sx,(Menu+i)->Sy,(Menu+i)->MenuName,\
							NormalMode);
		}
	}
	else if(Mode==ClrMode)
	{
		Menu=Menu->UOpt;
		DispRanc(Menu->RanSx, Menu->RanSy, Menu->RanEx, Menu->RanEy, ClrMode);
	}
}

//此函数显示二级以下的所有菜单
//Menu为最未级指针
void DispMenuTwoAll(struct MenuOptStru *Menu, char Mode)
{
	if(Mode==ClrMode1)
	{
		DispRanc(1, 0, 23, 79, ClrMode1);
		return;
	}
	
	for(;Menu->UOpt;Menu=Menu->UOpt)
	{
		if(Menu->UOpt==NULL)
			break;
		DispMenuTwo(Menu->UOpt->DOpt, Mode);
		if(Mode==DrawMode)
			DispMenuItem(Menu, NormalMode);
	}
}

static char	_PointFlag=0;
static char	_StrFlag=0;
static char	_InsertFlag=0;
static char 	__cTmp=0;

long double atolf(char *Str)
{
	long double	dTmp;
	if(Str[0]==0)
		return 0;
	sscanf(Str,"%Lf",&dTmp);
	return dTmp;
}
 
long double lfabs(long double a)
{
	if(a<0)
		return a*-1;
	else
		return a;
}

//此函数接收一个字符
//Leng为小数点后的位数
//返回光标移动的列数
int GetChar(char *Str, int Leng1, char Mode)
{
	int		Key, Key1;
	char	ReturnFlag=0;
	Str[0]=0;
	for(;;)
	{
		Key=GetKey();
		if(Key<127&&iscntrl(Key&0x7F)) //控制字符忽略
			return Key;
		if(Key>126)
		{
				nodelay(stdscr, TRUE);
				if(Key1=getch())
				{
					if(Key1<126)
						ReturnFlag=1;
				}
				else
					ReturnFlag=1;
				nodelay(stdscr, FALSE);
	    		if((Mode==BankNumMode||Mode==InitBankNumMode||
		   		Mode==SignBankNumMode||Mode==InitSignBankNumMode)&&!_PointFlag)
					if(Key==_Left&&ReturnFlag)
						return _BackSpace;
			if(ReturnFlag)
				return Key;
		}

		if(Mode==StrMode||Mode==InitStrMode||
		   Mode==PasswdMode||Mode==InitPasswdMode)
		{
			if(_StrFlag==1)
			{
				if(isdigit(Key))
				{
					Str[0]=Key;
					Str[1]=0;
					return 0;
				}
			}
			else
			{
				Str[0]=Key;
				if(Key>126)
				{
					Str[1]=Key1;
					Str[2]=0;
				}
				else
					Str[1]=0;
				return 0;
			}
		}

		if(Mode==NumMode||Mode==SignNumMode||
		   Mode==BankNumMode||Mode==SignBankNumMode||
	       Mode==InitNumMode||Mode==InitSignNumMode||
		   Mode==InitBankNumMode||Mode==InitSignBankNumMode)
		{
			if(isdigit(Key)||(Key=='.'&&Leng1>0&&!_PointFlag)||
			   Key=='+'||Key=='-')
			{
				if(Key=='.')
				{
					_PointFlag=1;
					return Key;
				}
				if(Key=='+'||Key=='-')
					return Key;
				Str[0]=Key;
				Str[1]=0;
				return 0;
			}
		}
		if(Mode==DateMode || Mode==InitDateMode)
		{
			if(isdigit(Key))
			{
				Str[0]=Key;
				Str[1]=0;
				return 0;
			}
		}
	}
}

//此函数用退格键删除一个字符
int DelChar(unsigned char *Str, char Mode, int Leng,int Cury0,int Cury1)
{
	if(Mode==StrMode||Mode==InitStrMode||
	   Mode==PasswdMode||Mode==InitPasswdMode)
	{
		if(Cury0>0)
		{
			if(Cury0-1>0&&Str[Cury0-1]>126)
			{
				if(Cury0-1<0)
					Cury0++;
				memmove(&Str[Cury0-2],&Str[Cury0],
					    strlen((char *)&Str[Cury0])+1);
				return 2;
			}
			else
			{
				memmove(&Str[Cury0-1],&Str[Cury0],
					    strlen((char *)&Str[Cury0])+1);
				return 1;
			}
		}
		else if(strlen((char *)Str)>1)
		{
			memmove(Str,Str+1,strlen((char *)(Str+1))+1);
		}
		else
			Str[0]=0;
		return -1;
	}

	else if(Mode==NumMode||Mode==SignNumMode|| 
	   		Mode==InitNumMode||Mode==InitSignNumMode)
	{
		if(_PointFlag)
		{
			if(Str[Cury0+Cury1-1]=='.')
			{
				_PointFlag=0;
//jkjfix1
			//	Str[Cury0+Cury1-1]=0;
				return -1;
			}
			else
			{
				if(Str[Cury0+Cury1-1]!=0)
				{
					Str[Cury0+Cury1-1]='0';
					return 1;
				}
			}
		}	
		else
		{
			if(Cury0>0)
			{
				memmove(&Str[Cury0-1],&Str[Cury0],
					strlen((char *)&Str[Cury0])+1);
				return 1;
			}
			else
			{
				if(strlen((char *)Str)>1)
					memmove(Str,Str+1,strlen((char *)(Str+1))+1);
				else
					Str[0]=0;
				return -2;
			}
		}
	}

	else if(Mode==BankNumMode||Mode==SignBankNumMode|| 
	   Mode==InitBankNumMode||Mode==InitSignBankNumMode)
	{
		if(_PointFlag)
		{
			if(Str[Cury0+Cury1-1]=='.')
			{
				_PointFlag=0;
//jkjfix2
//				Str[Cury0+Cury1-1]=0;
				return -1;
			}
			else
			{
				if(Str[Cury0+Cury1-1]!=0)
				{
					Str[Cury0+Cury1-1]='0';
					return 1;
				}
			}
		}	
		else
		{
			if(Cury0>0)
			{
				memmove(&Str[Cury0-1],&Str[Cury0],
					strlen((char *)&Str[Cury0])+1);
				return 1;
			}
			else
			{
				if(strlen((char *)Str)>1)
					memmove(Str,Str+1,strlen((char *)(Str+1))+1);
				else
					Str[0]=0;
				return -2;
			}
		}
	}

	if(Mode==DateMode || Mode==InitDateMode)
	{
		if(strlen((char *)Str)>0)
		{
			Str[strlen((char *)Str)-1]=0;
			return 1;
		}
		else
			return 0;
	}
	return 0;
}

//银行数字长度计算
int CalBankLeng(int Leng, int Leng1, char Mode)
{
	int	Tmpi;
	Tmpi=Leng+Leng/3-1;
	if(Leng%3)
		Tmpi++;
	if(Leng1)
		Tmpi+=Leng1+1;
/*	if(Mode==SignBankNumMode&&Mode==InitSignBankNumMode)*/
		Tmpi++;
	return Tmpi;
}

//银行数字转换
void ChangeStr(char *NewStr, char *OldStr, char Mode, int Leng, int Leng1)
{
	int		Tmpi;
	char	Str[400];
	Tmpi=CalBankLeng(Leng, Leng1, Mode);
	ChBankNum(NewStr);
	ChBankNum(OldStr);
	memset(Str,' ',Tmpi);
	strcpy(&Str[Tmpi-strlen(NewStr)], NewStr);
	Str[Tmpi]=0;
	strcpy(NewStr,Str);

	memset(Str,' ',Tmpi);
	strcpy(&Str[Tmpi-strlen(OldStr)], OldStr);
	Str[Tmpi]=0;
	strcpy(OldStr,Str);
}

//将日期数字转换成yyyy/mm/dd形式
void ChangeDate(char *NewStr, char *OldStr, char Mode)
{
	int		Tmpi;
	char	Str1[20], Str2[20];
	char	*P, *P1;
	char	cFlag, cFlag1;

	if(!isdigit(NewStr[0])&&NewStr[0]!=0)
		NewStr[0]=0;
	if(!isdigit(OldStr[0])&&OldStr[0]!=0)
		OldStr[0]=0;
	sprintf(Str1,"%d",atoi(NewStr));
	sprintf(Str2,"%d",atoi(OldStr));
	P=Str1;
	P1=Str2;
	for(Tmpi=0,cFlag=0,cFlag1=0;Tmpi<8;Tmpi++,P++,P1++)
	{
		if(cFlag)
			*P='0';
		else if(*P==0)
		{
			*P='0';
			cFlag=1;
		}
		if(cFlag1)
			*P1=' ';
		else if(*P1==0)
		{
			*P1=' ';
			cFlag1=1;
		}
	}
	Str1[8]=0;
	Str2[8]=0;
	memmove(NewStr,Str1,4);
	NewStr[4]='/';
	memmove(NewStr+5,Str1+4,2);
	NewStr[7]='/';
	memmove(NewStr+8,Str1+6,2);
	NewStr[10]=0;

	memmove(OldStr,Str2,4);
	OldStr[4]='.';
	memmove(OldStr+5,Str2+4,2);
	OldStr[7]='.';
	memmove(OldStr+8,Str2+6,2);
	OldStr[10]=0;
}

void ChNum(char *Str, long double Val, int Leng1)
{
	char Str1[80];
	Str[0]=0;
	sprintf(Str1,"%c.%dLf",'%',Leng1);
	sprintf(Str,Str1,Val);
}

void DispStr(int x,int y,char *NewStr,char *OldStr,int Leng,int Leng1,int Cury0, int Cury1, char Mode)
{
	//char	*P, *P1, Str[3];
	int		Tmpi, Tmpj;
	char		Str[400];

	if(_InsertFlag)
	{
		if(!__cTmp)
			OldStr[0]=0;
		__cTmp=1;
	}
	else
	{
		if(__cTmp)
			OldStr[0]=0;
		__cTmp=0;
	}

	if(strlen(NewStr)>=strlen(OldStr))
		Tmpi=strlen(NewStr);
	else
		Tmpi=strlen(OldStr);
	memset(OldStr,' ',Tmpi);
	OldStr[Tmpi]=0;
	mvaddstr(x,y,OldStr);
	if(Mode==InitPasswdMode||Mode==PasswdMode)
	{
		memset(Str,'*',strlen(NewStr));
		Str[strlen(NewStr)]=0;
	}
	else
		strcpy(Str,NewStr);
	if(_InsertFlag)
		attron(A_BOLD);
		//standout();	
	mvaddstr(x,y,Str);
	if(_InsertFlag)
		attroff(A_BOLD);
		//standend();	

/*	for(P=NewStr, P1=OldStr, Tmpj=0; Tmpj<Tmpi;Tmpj++)
	{
		if(*P!=*P1)//||*P==*P1&&*P<0)
		{
			mvaddch(x,y+Tmpj,' ');
			if(*P)
			{
				if(Mode==InitPasswdMode||Mode==PasswdMode)
					mvaddch(x,y+Tmpj,'*');
				else
				{
					if(_InsertFlag)
						standout();	
					if(Tmpj==0&&_InsertFlag&&*P<0&&*(P+1))
					{
						Str[0]=*P;
						Str[1]=*++P;
						P1++;
						Str[2]=0;
						mvaddstr(x,y+Tmpj++,Str);
					}
					else
						mvaddch(x,y+Tmpj,*P);
					if(_InsertFlag)
						standend();	
				}
			}
		}
		if(*P)
			P++;
		if(*P1)
			P1++;
	}*/
	if(Mode==BankNumMode||Mode==SignBankNumMode||
	   Mode==InitBankNumMode||Mode==InitSignBankNumMode)
	{
		Tmpi=CalBankLeng(Leng,Leng1,Mode);
		if(_PointFlag)
		{
//jkjfix3
			if(Cury1>=Leng1)
				move(x,y+Tmpi-Leng1-1+Leng1);
			else
				move(x,y+Tmpi-Leng1+Cury1);
		}
		else
			move(x,y+Tmpi-Leng1-1);
	}
	else if(Mode==NumMode||Mode==SignNumMode||
	   Mode==InitNumMode||Mode==InitSignNumMode)
	{
//jkjfix4
		if(_PointFlag)
		{
			if(Cury1>=Leng1)
				move(x,y+Cury0+Leng1-1);
			else
				move(x,y+Cury0+Cury1);
		}
		else
		{
			if(Leng1>0)
				move(x,y+Cury0);
			else
			{
				if(Cury0>=Leng)
					move(x,y+Cury0-1);
				else
					move(x,y+Cury0);
			}
		}
	}
	else if(Mode!=DateMode&&Mode!=InitDateMode)
	{
		if(Cury0>=Leng)
			move(x,y+Leng-1);
		else
			move(x,y+Cury0);
	}
	else
	{
		if(Cury0>=10)
			move(x,y+9);
		else
			move(x,y+Cury0);
	}
	refresh();
}

void InitVar(void)
{
	_InsertFlag=0;
	__cTmp=0;
}

//此函数接收数字,字符串, 银行数字
//Mode = NumMode
//Mode = BankNumMode
//Mode = StrMode;
//Mode = PasswdStrMode;
//Mode = DateMode;
//Mode = StrNumMode;
//Mode = InitNumMode
//Mode = InitBankNumMode
//Mode = InitStrMode;
//Mode = InitPasswdMode;
//Mode = InitDateMode;
//Mode = InitStrNumMode;
//Leng   为字符串长度或数字的总长度
//Leng1  为小数点后面的位数
int Accept(int x, int y, char *Str, int Leng, int Leng1, char Mode)
{
	char	NewStr[400], OldStr[400];
	char	TmpStr1[400],TmpStr2[400];
	char	*p;

	int	Sign=1,OldSign=1;
	int	Tmpi, Tmpj, Cury0, Cury1;
	int	Key;

	InitVar();
	if(!Str[0])
		if(Mode>19)
			Mode-=20;
	if(Mode==BankNumMode||Mode==InitBankNumMode||
	   Mode==SignBankNumMode||Mode==InitSignBankNumMode)
	{
		Tmpi=CalBankLeng(Leng,Leng1,Mode);
		memset(TmpStr1,' ',Tmpi);
		TmpStr1[Tmpi]=0;
	}
	else if(Mode==NumMode||Mode==InitNumMode)
	{
		if(Leng1>0)
		{
			memset(TmpStr1,' ',Leng+Leng1+1);
			TmpStr1[Leng+Leng1+1]=0;
		}
		else
		{
			memset(TmpStr1,' ',Leng);
			TmpStr1[Leng]=0;
		}
	}
	else if(Mode==SignNumMode||Mode==InitSignNumMode)
	{
		if(Leng1>0)
		{
			memset(TmpStr1,' ',Leng+Leng1+2);
			TmpStr1[Leng+Leng1+2]=0;
		}
		else
		{
			memset(TmpStr1,' ',Leng+1);
			TmpStr1[Leng+1]=0;
		}
	}
	else if(Mode==DateMode||Mode==InitDateMode)
	{
		memset(TmpStr1,' ',Leng+2);
		TmpStr1[Leng+2]=0;
	}
	else
	{
		memset(TmpStr1,' ',Leng);
		TmpStr1[Leng]=0;
	}
	DispWord(x,y,TmpStr1,RefreshMode);
	
	if(strlen(Str)>Leng+Leng1)
		Str[Leng+Leng1]=0;

	_StrFlag=0;
	if(Mode==InitStrNumMode||Mode==StrNumMode)
	{
		if(Mode==InitStrNumMode)
			Mode=InitStrMode;
		else 
			Mode=StrMode;
		_StrFlag=1;
	}

	_PointFlag=0;
	Cury0=0;
	Cury1=0;
	memset(NewStr,0,400);
	memset(OldStr,0,400);
	memset(TmpStr1,0,400);
	memset(TmpStr2,0,400);
	if(Mode==InitDateMode||Mode==DateMode)
	{
		Leng1=0;
		Leng=8;
	}
	if(Mode==SignNumMode||Mode==InitSignNumMode)
	{
		mvaddch(x,y,' ');
		y++;
	}
	if(Mode<20)  //初始化字符串
	{
		NewStr[0]=0;
		OldStr[0]=0;
		Str[0]=0;
	}
	if((Mode==BankNumMode||Mode==SignBankNumMode||
	   Mode==InitBankNumMode||Mode==InitSignBankNumMode||
	   Mode==NumMode||Mode==SignNumMode||
	   Mode==InitNumMode||Mode==InitSignNumMode))
	{
		ChNum(NewStr, lfabs(atolf(Str)), Leng1);
		if(atolf(Str)<0)
			Sign=-1;
		strcpy(Str,NewStr);
		OldStr[0]=0;
		if(Leng1==0)
			NewStr[Leng]=0;
		else
			NewStr[Leng+1+Leng1]=0;
	}
	else if(Mode>19)
	{
		strcpy(NewStr,Str);
		OldStr[0]=0;
	}

	if(Leng1)   //计算接收字符串的长度
		Tmpj=Leng+Leng1+1;
	else
		Tmpj=Leng;

	//初始化后首次显示字符串
/*	if(Mode>6||Mode==InitBankNumMode||Mode==InitSignBankNumMode||
	   Mode==InitNumMode||Mode==InitSignNumMode)*/
	{
		if(Mode==BankNumMode||Mode==SignBankNumMode||
		   Mode==InitBankNumMode||Mode==InitSignBankNumMode)
		{
			ChNum(TmpStr1, Sign*lfabs(atolf(NewStr)), Leng1);
			TmpStr2[0]=0;
			ChangeStr(TmpStr1, TmpStr2, Mode, Leng, Leng1);
			DispStr(x,y,TmpStr1,TmpStr2,Leng,Leng1,Cury0,Cury1,Mode);
		}
		else if(Mode==NumMode||Mode==SignNumMode||
	   	   Mode==InitNumMode||Mode==InitSignNumMode)
		{
			if(Sign<0)
				mvaddch(x,y-1,'-');
			strcpy(TmpStr1, NewStr);
			memset(TmpStr2,100,0);
			memset(TmpStr2,' ',strlen(NewStr));
			mvaddstr(x,y,TmpStr2);
			TmpStr2[0]=0;
			DispStr(x,y,TmpStr1,TmpStr2,Leng,Leng1,Cury0,Cury1,Mode);
		}
		else
		{
			strcpy(TmpStr1, NewStr);
			memset(TmpStr2,100,0);
			memset(TmpStr2,' ',strlen(NewStr));
			mvaddstr(x,y,TmpStr2);
			TmpStr2[0]=0;
			if(Mode==InitDateMode||Mode==DateMode)
			{
				ChangeDate(TmpStr1, TmpStr2,Mode);
				mvaddstr(x,y,TmpStr1);
				move(x,y);
				refresh();
			}
			else
				DispStr(x,y,TmpStr1,TmpStr2,Leng,Leng1,Cury0,Cury1,Mode);
		}
	}

	if(Mode==BankNumMode)
	{
		if((p=strchr(NewStr,'.')))
			Cury0=p-NewStr;
		else
			Cury0=strlen(NewStr);
	}

	for(;;)
	{
		strcpy(OldStr,NewStr);
		Key=GetChar(TmpStr2,Leng1, Mode);
		if(ProMode==JymMode)
			if(Key==_Tab)
				return Key;
		if(Key==0)
		{
			if(!_PointFlag)   		//没有小数点处理
			{
				if(TmpStr2[0]&&Cury0<Leng)
				{
					if(NewStr[Cury0]==0)
					{
						if(Cury0==0&&TmpStr2[0]=='0')
						{
						if((Mode==BankNumMode||Mode==SignBankNumMode||
						   Mode==InitBankNumMode||Mode==InitSignBankNumMode||
						   Mode==NumMode||Mode==SignNumMode||
						   Mode==InitNumMode||Mode==InitSignNumMode))
							continue;
						}
						NewStr[Cury0++]=TmpStr2[0];
						NewStr[Cury0]=0;
					}
					else
					{
						if(Mode==BankNumMode||Mode==SignBankNumMode||
						   Mode==InitBankNumMode||Mode==InitSignBankNumMode||
						   Mode==NumMode||Mode==SignNumMode||
						   Mode==InitNumMode||Mode==InitSignNumMode)
						{
							if(Cury0>=0&&NewStr[Cury0]=='.')
							{
								memmove(&NewStr[Cury0+1],&NewStr[Cury0],
										strlen(&NewStr[Cury0])+1);
								NewStr[Cury0++]=TmpStr2[0];
							}
							else
							{
								if(Cury0==0&&TmpStr2[0]=='0')
									NewStr[Cury0]=TmpStr2[0];
								else
									NewStr[Cury0++]=TmpStr2[0];
							}
						}
						else
						{
							if(NewStr[Cury0]==0)
							{
								NewStr[Cury0++]=TmpStr2[0];
								NewStr[Cury0]=0;
							}
							else
							{
								if(_InsertFlag)
								{
									memmove(NewStr+1+Cury0,NewStr+Cury0,
									    strlen(NewStr+Cury0)+1);
									NewStr[Cury0++]=TmpStr2[0];
									NewStr[Leng]=0;
								}
								else
									NewStr[Cury0++]=TmpStr2[0];
							}
						}
					}
					if(TmpStr2[1]&&Cury0<Leng)
					{
						if(NewStr[Cury0]==0)
						{
							NewStr[Cury0++]=TmpStr2[1];
							NewStr[Cury0]=0;
						}
						else
						{
								if(_InsertFlag)
								{
									memmove(NewStr+1+Cury0,NewStr+Cury0,
									    strlen(NewStr+Cury0)+1);
									NewStr[Cury0++]=TmpStr2[1];
									NewStr[Leng]=0;
								}
								else
									NewStr[Cury0++]=TmpStr2[1];
						}
					}
				}
				else if((Mode==BankNumMode||Mode==SignBankNumMode||
					    Mode==InitBankNumMode||Mode==InitSignBankNumMode||
					    Mode==NumMode||Mode==SignNumMode||
					    Mode==InitNumMode||Mode==InitSignNumMode)&&
						Leng1>0&&TmpStr2[0])
				{
//jkjfix
				/*	if(NewStr[Cury0]!='.')
					{
						NewStr[Cury0]='.';
						NewStr[Cury0+1]=0;
					}
					Cury0+=1;
					_PointFlag=1;*/
				}
				else 
				{
					//jkjfix5
					if((unsigned char)TmpStr2[0]<126)
					{
						NewStr[Leng-1]=TmpStr2[0];
						NewStr[Leng]=0;
					}
				}
			}
			else		//有小数点处理
			{
				if(TmpStr2[0]&&Cury1<Leng1)
				{
					if(NewStr[Cury0+Cury1]==0)
					{
					//jkjfix
						NewStr[Cury0+Cury1++]=TmpStr2[0];
						NewStr[Cury0+Cury1]=0;
					}
					else
						NewStr[Cury0+Cury1++]=TmpStr2[0];
				}
				else
				{
				//jkjfix
					NewStr[Cury0+Leng1-1]=TmpStr2[0];
					NewStr[Cury0+Leng1]=0;
				}
			}
		}
		else if(Key=='.'&&(Mode==BankNumMode||Mode==SignBankNumMode|| 
	   		    Mode==InitBankNumMode||Mode==InitSignBankNumMode||
			    Mode==NumMode||Mode==SignNumMode|| 
			    Mode==InitNumMode||Mode==InitSignNumMode)&&Leng1>0)
		{
			if(!(Mode==BankNumMode||Mode==SignBankNumMode|| 
	   		    Mode==InitBankNumMode||Mode==InitSignBankNumMode))
				if(Cury0==0)
					NewStr[Cury0++]='0';
			if(NewStr[0]==0)
					NewStr[Cury0++]='0';
				
			if((p=strchr(NewStr,'.')))
			{
				memmove(NewStr+Cury0,p,strlen(p)+1);
				if(NewStr[0]=='.')
				{
					memmove(NewStr+1,NewStr,strlen(NewStr)+1);
					NewStr[0]='0';
				}
				p=strchr(NewStr,'.');
				Cury0=p-NewStr+1;
			}
			else
			{
				NewStr[Cury0++]=Key;
				NewStr[Cury0]=0;
			}
		}
		else if(Key=='+'||Key=='-')
		{
//jkj
			if(!(Mode==SignBankNumMode||Mode==InitSignBankNumMode||
			   Mode==SignNumMode||Mode==InitSignNumMode))
				OldSign=Sign=1;
			else
			{
				OldSign=Sign;
				if(Key=='-')
				{
					if(Sign<0)
						Sign=1;
					else
						Sign=-1;
				}
				else
					Sign=1;
			}
		}
		else if(Key==_BackSpace)
		{
			strcpy(OldStr,NewStr);
			if(!(Tmpi=DelChar((unsigned char *)NewStr,Mode,Leng,Cury0,Cury1)))
				continue;
			if((Mode==BankNumMode||Mode==SignBankNumMode|| 
	   		    Mode==InitBankNumMode||Mode==InitSignBankNumMode||
			    Mode==NumMode||Mode==SignNumMode|| 
			    Mode==InitNumMode||Mode==InitSignNumMode)&&Leng1>0)
			{
				if(_PointFlag)
				{
					Cury1-=1;
					if(Cury1<0)
						Cury1=0;
				}
				else
				{
					Cury0-=1;
					if(Cury0<0)
					{
						Cury0=0;
						ChNum(NewStr, lfabs(atolf(NewStr)), Leng1);
					}
				}
			}
			else
			{
				if(Tmpi>0)
				{
					Cury0-=Tmpi;
					if(Cury0<0)
						Cury0=0;
				}
			}
		}
		else if(Key==_Enter)
		{
			InitVar();
			OldStr[0]=0;
		}
		else if(Key==_Left)
		{
			if(!(Mode==BankNumMode||Mode==SignBankNumMode|| 
	   		    Mode==InitBankNumMode||Mode==InitSignBankNumMode||
			    Mode==NumMode||Mode==SignNumMode|| 
			    Mode==InitNumMode||Mode==InitSignNumMode))
			{
//jkjfix
				if(Cury0>=Leng&&Leng>1)
					Cury0=Leng-2;
				else
					Cury0--;
				if(Cury0<0)
					Cury0=0;
			}
			else
			{
				if(_PointFlag)
				{
	//jkjfix
					if(Cury1>=Leng1&&Leng1>1)
						Cury1=Leng1-2;
					else
						Cury1--;
					if(Cury1==-1)
						_PointFlag=0;
					if(Cury1<0)
					{
						Cury1=0;
						Cury0-=1;
					}
				}
				else
				{
					if(!(Mode==BankNumMode||Mode==SignBankNumMode|| 
	   		    		Mode==InitBankNumMode||Mode==InitSignBankNumMode))
					{
//jkjfix
			    		if((Mode==NumMode||Mode==SignNumMode|| 
			    		Mode==InitNumMode||Mode==InitSignNumMode)&&Leng1==0)
						{
							if(Cury0>=Leng&&Leng>1)
								Cury0=Leng-2;
							else
							{
								Cury0--;
								if(Cury0<0)
									Cury0=0;
							}
						}
						else
						{
							Cury0--;
							if(Cury0<0)
								Cury0=0;
						}
					}
				}
			}
		}
		else if(Key==_Right)
		{
			if(Mode==InitDateMode||Mode==DateMode)
			{
				if(NewStr[Cury0]==0&&Cury0<Leng)
				{
					NewStr[Cury0++]='0';
					NewStr[Cury0]=0;
				}
				else if(Cury0<Leng)
					Cury0++;
			}
			else if(!(Mode==BankNumMode||Mode==SignBankNumMode|| 
	   		    Mode==InitBankNumMode||Mode==InitSignBankNumMode||
			    Mode==NumMode||Mode==SignNumMode|| 
			    Mode==InitNumMode||Mode==InitSignNumMode))
			{
				if(Cury0+1<Leng)
				{
					if(NewStr[Cury0+1]!=0)
						Cury0++;
					else
					{
						NewStr[Cury0+2]=0;
						Cury0++;
						if(NewStr[Cury0-1]==0)
							Cury0--;
					}
				}
			}
			else
			{
				if(_PointFlag)
				{
					if(Cury1<Leng1)
						Cury1++;
				}
				else
				{
					if(!(Mode==BankNumMode||Mode==SignBankNumMode|| 
	   		    		Mode==InitBankNumMode||Mode==InitSignBankNumMode))
					{
						if((NewStr[Cury0+1]==0||NewStr[Cury0+1]=='.'
						   ||NewStr[Cury0]=='.')&&Leng1>0)
						{
							if(NewStr[Cury0+1]==0&&NewStr[Cury0]!='.')
							{
								NewStr[Cury0+1]='.';
								NewStr[Cury0+2]='0';
								NewStr[Cury0+3]='0';
								NewStr[Cury0+4]=0;
							}
							if(NewStr[Cury0]=='.')
								_PointFlag=1;
							if(Cury0+1<Leng&&NewStr[Cury0+1])
								Cury0++;
							else
								Cury0=Leng;
						}
						else if(Cury0+1<Leng)
						{
							if(NewStr[Cury0+1])
								Cury0++;
							else if(Leng1==0)
							{
								NewStr[Cury0+2]=0;
								Cury0++;
								if(NewStr[Cury0-1]==0||NewStr[0]==0||
								   NewStr[0]=='0')
									Cury0--;
							}
						}
					}
					else if(!_PointFlag&&Leng1)
					{
						_PointFlag=1;
						if((p=strchr(NewStr,'.')))
							Cury0=p-NewStr+1;
						Cury1=0;
					}
				}
			}
		}
		else if(Key==_DelKey)
		{
			if(!(Mode==BankNumMode||Mode==SignBankNumMode|| 
	   		    Mode==InitBankNumMode||Mode==InitSignBankNumMode))
			{
				if(Mode==NumMode||Mode==SignNumMode|| 
			    Mode==InitNumMode||Mode==InitSignNumMode)
				{
					strcpy(OldStr,NewStr);
					if(NewStr[Cury0]!=0&&NewStr[Cury0]!='.'&&!_PointFlag)
				memmove(NewStr+Cury0, NewStr+Cury0+1,strlen(NewStr+Cury0+1)+1);
				}
				else
				{
				strcpy(OldStr,NewStr);
				if(NewStr[Cury0]!=0)
				memmove(NewStr+Cury0, NewStr+Cury0+1,strlen(NewStr+Cury0+1)+1);
				}
			}
		}
		else if(Key==_Home)
		{
			if(!(Mode==BankNumMode||Mode==SignBankNumMode||
		   	   Mode==InitBankNumMode||Mode==InitSignBankNumMode))
			{
				if((Mode==NumMode||Mode==SignNumMode||
	   	   		   Mode==InitNumMode||Mode==InitSignNumMode)&&Leng1==0)
					Cury0=0;
				if(!(Mode==NumMode||Mode==SignNumMode||
	   	   		   Mode==InitNumMode||Mode==InitSignNumMode))
					Cury0=0;
			}
		}
		else if(Key==_End)
		{
			if(!(Mode==BankNumMode||Mode==SignBankNumMode||
		   	   Mode==InitBankNumMode||Mode==InitSignBankNumMode))
			{
				if((Mode==NumMode||Mode==SignNumMode||
	   	   		   Mode==InitNumMode||Mode==InitSignNumMode)&&Leng1==0)
				{
					Cury0=strlen(NewStr);
					if(NewStr[0]==0||NewStr[0]=='0')
						Cury0=0;
				}
				if(!(Mode==NumMode||Mode==SignNumMode||
	   	   		   Mode==InitNumMode||Mode==InitSignNumMode))
					Cury0=strlen(NewStr);
			}
		}
		else if(Key=='')  //jkjfix
		{
			strcpy(NewStr,Str);
			Cury0=Cury1=0;
			if(Mode==BankNumMode)
			{
				if((p=strchr(NewStr,'.')))
					Cury0=p-NewStr;
				else
					Cury0=strlen(NewStr);
			}
			_PointFlag=0;
		}
		else if(Key==_Insert)
		{
			if(!(Mode==BankNumMode||Mode==SignBankNumMode|| 
	   		    Mode==InitBankNumMode||Mode==InitSignBankNumMode||
			    Mode==NumMode||Mode==SignNumMode|| 
			    Mode==InitNumMode||Mode==InitSignNumMode))
				if(Leng>1)
					_InsertFlag=~_InsertFlag;
		}
		else if(Key=='')
		{
			if(Mode==StrMode||Mode==InitStrMode||
		   	Mode==PasswdMode||Mode==InitPasswdMode)
				NewStr[Cury0]=0;
			Cury0--;
			if(Cury0<0)
				Cury0=0;
		}
		else if(Key=='')
		{
			if(Mode==StrMode||Mode==InitStrMode||
		   		Mode==PasswdMode||Mode==InitPasswdMode)
			{
			memmove(NewStr,&NewStr[Cury0],strlen(&NewStr[Cury0])+1);
			Cury0=Cury1=0;
			}
		}
		else if(Key=='')
		{
			Cury0=Cury1=0;
			NewStr[0]=0;
		}


		if(Mode==BankNumMode||Mode==SignBankNumMode||
		   Mode==InitBankNumMode||Mode==InitSignBankNumMode)
		{
			ChNum(TmpStr1, Sign*lfabs(atolf(NewStr)), Leng1);
			ChNum(TmpStr2, OldSign*lfabs(atolf(OldStr)), Leng1);
			ChangeStr(TmpStr1, TmpStr2, Mode, Leng, Leng1);
			DispStr(x,y,TmpStr1,TmpStr2,Leng,Leng1,Cury0,Cury1,Mode);
			ChNum(NewStr, lfabs(atolf(NewStr)), Leng1);
			if((p=strchr(NewStr,'.')))
			{
				Tmpj=p-NewStr;
				if(Cury0>Tmpj)
					_PointFlag=1;
			}
			OldSign=Sign;
		}
		else if(Mode==NumMode||Mode==SignNumMode||
	   	   Mode==InitNumMode||Mode==InitSignNumMode)
		{
			if(Mode==SignNumMode||Mode==InitSignNumMode)
			{
				if(Sign<0)
					mvaddch(x,y-1,'-');
				else
					mvaddch(x,y-1,' ');
			}
			ChNum(TmpStr1, lfabs(atolf(NewStr)), Leng1);
			ChNum(TmpStr2, lfabs(atolf(OldStr)), Leng1);
			DispStr(x,y,TmpStr1,TmpStr2,Leng,Leng1,Cury0,Cury1,Mode);
			if((p=strchr(NewStr,'.')))
			{
				Tmpj=p-NewStr;
				if(Cury0>Tmpj)
					_PointFlag=1;
			}
			ChNum(NewStr, lfabs(atolf(NewStr)), Leng1);
		}
		else
		{
			strcpy(TmpStr1, NewStr);
			strcpy(TmpStr2, OldStr);
			if(Mode==InitDateMode||Mode==DateMode)
			{
				ChangeDate(TmpStr1, TmpStr2,Mode);
				if(Cury0>3&&Cury0<6)
					Tmpj=Cury0+1;
				else if(Cury0<4)
					Tmpj=Cury0;
				else
					Tmpj=Cury0+2;
				DispStr(x,y,TmpStr1,TmpStr2,Leng,Leng1,Tmpj,Cury1,Mode);
			}
			else
				DispStr(x,y,TmpStr1,TmpStr2,Leng,Leng1,Cury0,Cury1,Mode);
		}
		if(Key==_Enter)
			break;
	}
	strcpy(Str,NewStr);
}

//接收单个字符
//InitVal 为字符的初始值
//ValStr 为字符的应该输入的值,ValStr为空则字符为所有ASCII字符
char AcceptChar(int x, int y, char InitVal,char *ValStr)
{
	char	Str[3];
	if(isalnum(InitVal))
		Str[0]=InitVal;
	else
		Str[0]=0;
	Str[1]=0;
	for(;;)
	{
		Accept(x,y,Str,1,0,StrMode);
		if(Str[0]&&(strchr(ValStr,Str[0])||ValStr==NULL))
			break;
	}
	return Str[0];
}

void WriteMenuStru(struct MenuOptStru *Menu, FILE *fp)
{
	struct MenuOptStru *P1;
	P1=Menu;
	fprintf(fp,"#%d,%s,%s,%s,%s,%d,%d,%s,%c,%s,%c,%s,%c,%s,%c,%s,%c,%s,%c,%s,lpf.\n", 		
		SysPar.Flag, SysPar.KeyFile, SysPar.HardFile,
		SysPar.ExeResFileName, SysPar.MenuFileName, SysPar.QdCtrl,
		SysPar.AccessCtrl, SysPar.DataBaseName1,SysPar.DBType1,
		SysPar.DataBaseName2,SysPar.DBType2,
		SysPar.DataBaseName3,SysPar.DBType3,
		SysPar.DataBaseName4,SysPar.DBType4,
		SysPar.DataBaseName5,SysPar.DBType5, 
		SysPar.DataBaseName6,SysPar.DBType6,SysPar.GsName);
	for(;P1&&P1->MenuNum!=0;)
	{
		if(P1&&P1->MenuNum>0)
		{
			fprintf(fp, "@%ld,%s,%s,%s,%ld,%s,0.\n", 
				P1->MenuNum, P1->MenuName,
				P1->Command, P1->ProInf,
				P1->JyCode, P1->HotKey);
		}
		P1++;
	}
}


/*void WriteMenuStru(struct MenuOptStru *Menu, FILE *fp)
{
	struct MenuOptStru *P1, *P2;
	P1=P2=Menu;
	for(;P1&&P1->MenuNum;)
	{
		if(P1&&P1->MenuNum>0)
		{
			fprintf(fp, "@%ld,%s,%s,%s,%ld,%ld,0.\n", 
				P1->MenuNum, P1->MenuName,
				P1->Command, P1->ProInf,
				P1->JyCode, P1->HotKye);
		}
		if(P1->DOpt&&P1->MenuNum>0)
			WriteMenuStru(P1->DOpt, fp);
		P1=P1->ROpt;
		if(P1==P2)
			break;
	}
}*/

char  DispEditCtrl(char *Str1, char MenuAccept[][81], char Mode)
{
	char		Str[400];
	char		Key[3];
	FILE 		*fp;
	char		Flag[6][2];
	DispRanc(OneMenuStartX + 1, 0, ScrEx-1, ScrEy-2, ClrMode);
	DispWord(4,27,Str1,NormalMode);
	DispWord(5,24,"============================",NormalMode);
	DispWord(7,3,"保存文件标志:",NormalMode);
	DispWord(8,3,"结果保存文件:",NormalMode);
	DispWord(9,3,"菜单文件名:",NormalMode);
	DispWord(10,3,"系统签到控制:",NormalMode);
	DispWord(11,3,"系统权限控制:",NormalMode);
	DispWord(12,3,"系统数据库名1:",NormalMode);
	DispWord(13,3,"系统数据库名2:",NormalMode);
	DispWord(14,3,"系统数据库名3:",NormalMode);
	DispWord(15,3,"系统数据库名4:",NormalMode);
	DispWord(16,3,"系统数据库名5:",NormalMode);
	DispWord(17,3,"系统数据库名6:",NormalMode);
	DispWord(18,3,"公司名称:",NormalMode);
	DispRanc(6, 1, 19, ScrEy-2, DrawMode);
	refresh();
	if(Mode!=3)
	{
		sprintf(MenuAccept[1],"%d",SysPar.Flag);
		strcpy(MenuAccept[2],SysPar.ExeResFileName);
		strcpy(MenuAccept[3],SysPar.MenuFileName);
		sprintf(MenuAccept[4],"%d",SysPar.QdCtrl);
		sprintf(MenuAccept[5],"%d",SysPar.AccessCtrl);

		strcpy(MenuAccept[6],SysPar.DataBaseName1);
		strcpy(MenuAccept[7],SysPar.DataBaseName2);
		strcpy(MenuAccept[8],SysPar.DataBaseName3);
		strcpy(MenuAccept[9],SysPar.DataBaseName4);
		strcpy(MenuAccept[10],SysPar.DataBaseName5);
		strcpy(MenuAccept[11],SysPar.DataBaseName6);
		strcpy(MenuAccept[12],SysPar.GsName);

		Accept(7, 17,MenuAccept[1], 1, 0 ,NumMode);
		Accept(8, 17,MenuAccept[2], 20, 0 ,StrMode);
		Accept(9,17,MenuAccept[3], 39, 0 ,StrMode);
		Accept(10,17,MenuAccept[4], 1, 0 ,NumMode);
		Accept(11,17,MenuAccept[5], 1, 0 ,NumMode);

		Accept(12,17,MenuAccept[6], 40, 0 ,StrMode);
		for(;;)
		{
			DispWord(12,45,"数据库类型:(ONLINE=1 SE=2)",RefreshMode);
			Accept(12,73,Flag[0], 1, 0 ,InitStrMode);
			if(Flag[0][0]>='1'&&Flag[0][0]<='2')
				break;
		}
		Accept(13,17,MenuAccept[7], 40, 0 ,StrMode);
		for(;;)
		{
			DispWord(13,45,"数据库类型:(ONLINE=1 SE=2)",RefreshMode);
			Accept(13,73,Flag[1], 1, 0 ,InitStrMode);
			if(Flag[1][0]>='1'&&Flag[1][0]<='2')
				break;
		}
		Accept(14,17,MenuAccept[8], 40, 0 ,StrMode);
		for(;;)
		{
			DispWord(14,45,"数据库类型:(ONLINE=1 SE=2)",RefreshMode);
			Accept(14,73,Flag[2], 1, 0 ,InitStrMode);
			if(Flag[2][0]>='1'&&Flag[2][0]<='2')
				break;
		}
		Accept(15,17,MenuAccept[9], 40, 0 ,StrMode);
		for(;;)
		{
			DispWord(15,45,"数据库类型:(ONLINE=1 SE=2)",RefreshMode);
			Accept(15,73,Flag[3], 1, 0 ,InitStrMode);
			if(Flag[3][0]>='1'&&Flag[3][0]<='2')
				break;
		}
		Accept(16,17,MenuAccept[10], 40, 0 ,StrMode);
		for(;;)
		{
			DispWord(16,45,"数据库类型:(ONLINE=1 SE=2)",RefreshMode);
			Accept(16,73,Flag[4], 1, 0 ,InitStrMode);
			if(Flag[4][0]>='1'&&Flag[4][0]<='2')
				break;
		}
		Accept(17,17,MenuAccept[11], 40, 0 ,StrMode);
		for(;;)
		{
			DispWord(17,45,"数据库类型:(ONLINE=1 SE=2)",RefreshMode);
			Accept(17,73,Flag[5], 1, 0 ,InitStrMode);
			if(Flag[5][0]>='1'&&Flag[5][0]<='2')
				break;
		}
		Accept(18,17,MenuAccept[12], 70, 0 ,StrMode);

		SysPar.Flag=MenuAccept[1][0]-'0';
		strcpy(SysPar.ExeResFileName,MenuAccept[2]);
		strcpy(SysPar.MenuFileName,MenuAccept[3]);
		SysPar.QdCtrl=MenuAccept[4][0]-'0';
		SysPar.AccessCtrl=MenuAccept[5][0]-'0';

		strcpy(SysPar.DataBaseName1, MenuAccept[6]);
		SysPar.DBType1=Flag[0][0];
		strcpy(SysPar.DataBaseName2, MenuAccept[7]);
		SysPar.DBType2=Flag[1][0];
		strcpy(SysPar.DataBaseName3, MenuAccept[8]);
		SysPar.DBType3=Flag[2][0];
		strcpy(SysPar.DataBaseName4, MenuAccept[9]);
		SysPar.DBType4=Flag[3][0];
		strcpy(SysPar.DataBaseName5, MenuAccept[10]);
		SysPar.DBType5=Flag[4][0];
		strcpy(SysPar.DataBaseName6, MenuAccept[11]);
		SysPar.DBType6=Flag[5][0];

		strcpy(SysPar.GsName, MenuAccept[12]);
	}

	for(;;)
	{
		DispWord(20,3,"是否确认:(1/0)[ ]",NormalMode);
		Accept(20,18,Key, 1, 0 ,InitStrNumMode);
		if(Key[0]>='0'&&Key[1]<='1')
			break;
	}

	if(Key[0]=='1')
	{
		sprintf(Str, "%s.bak", SysPar.MenuFileName);
		if((fp=fopen(Str,"wt"))==NULL)
		{
			DispMenuPro("Can't open write txt");
			getchar();
			return;
		}
		WriteMenuStru(MenuArry, fp);
		fclose(fp);
		strcat(SysPar.MenuFileName,".bak");
		PutSec(SysPar.MenuFileName, MenuFilePass);
		SysPar.MenuFileName[strlen(SysPar.MenuFileName)-8]=0;
		sprintf(Str,"mv %s.bak.bak %s",SysPar.MenuFileName,
					SysPar.MenuFileName);
		system(Str);
		return 1;
	}
	else
	{
		PutSec(SysPar.MenuFileName, MenuFilePass);
		SysPar.MenuFileName[strlen(SysPar.MenuFileName)-4]=0;
	}
	return 0;
}

char  DispEditMach(char *Str1)
{
	char		Str[100];
	char		Str2[100];
	char		Key[4];
	char		cFlag;
	FILE 		*fp;
	struct SysParStru   Tmp;
	Tmp=SysPar;
	DispRanc(OneMenuStartX + 1, 0, ScrEx-1, ScrEy-2, ClrMode);
	DispWord(3,27,Str1,NormalMode);
	DispWord(4,24,"============================",NormalMode);
	DispWord(6,3,"终端类型: ",NormalMode);
	DispWord(7,3,"打印机类型:",NormalMode);
	DispWord(8,3,"密码器类型:",NormalMode);
	DispWord(9,3,"时钟开关:",NormalMode);
	DispWord(10,3,"屏隔行数:",NormalMode);
	DispWord(11,3,"屏隔列数:",NormalMode);
	DispWord(12,3,"进入透明打印:",NormalMode);
	DispWord(13,3,"退出透明打印:",NormalMode);
	DispWord(14,3,"打印字体放大:",NormalMode);
	DispWord(15,3,"打印字体还原:",NormalMode);
	DispWord(16,3,"打印行间距:",NormalMode);
	DispWord(17,3,"打印字间距:",NormalMode);
	DispWord(18,3,"初始化打印机:",NormalMode);
	DispWord(19,3,"打印换页:",NormalMode);
	DispRanc(5, 1, 20, ScrEy-2, DrawMode);
	refresh();
	Accept(6, 17,SysPar.Term, 10, 0 ,StrMode);
	Accept(7, 17,SysPar.Printer,20, 0 ,StrMode);
	Accept(8,17,SysPar.Password, 20, 0 ,StrMode);
	sprintf(Str,"%d",ScrEx);
	Key[0]=SysPar.ClockFlag;
	Key[1]=0;
	Accept(9,17,Key,1,0,StrNumMode);
	SysPar.ClockFlag=Key[0];
	Accept(10,17,Str, 2, 0 ,StrNumMode);
	ScrEx=atoi(Str);
	sprintf(Str,"%d",ScrEy);
	Accept(11,17,Str, 10, 0 ,StrNumMode);

	DispMenuPro("输入打印命令格式为:两位10进制数字+加字符,数字被转为ASC码");

	sprintf(Str,"%02d%s",SysPar.Jrdmdy[0],&SysPar.Jrdmdy[1]);
	strcpy(SysPar.Jrdmdy, Str);
	Accept(12,17,SysPar.Jrdmdy, 10, 0 ,StrMode);
	strcpy(Str, SysPar.Jrdmdy);
	memmove(Key,Str,2);
	Key[2]=0;
	cFlag=atoi(Key);
	sprintf(SysPar.Jrdmdy,"%c%s",cFlag,&Str[2]);

	sprintf(Str,"%02d%s",SysPar.Dcdmdy[0],&SysPar.Dcdmdy[1]);
	strcpy(SysPar.Dcdmdy, Str);
	Accept(13,17,SysPar.Dcdmdy, 10, 0 ,StrMode);
	strcpy(Str, SysPar.Dcdmdy);
	memmove(Key,Str,2);
	Key[2]=0;
	cFlag=atoi(Key);
	sprintf(SysPar.Dcdmdy,"%c%s",cFlag,&Str[2]);

	sprintf(Str,"%02d%s",SysPar.Zdfd[0],&SysPar.Zdfd[1]);
	strcpy(SysPar.Zdfd, Str);
	Accept(14,17,SysPar.Zdfd, 10, 0 ,StrMode);
	strcpy(Str, SysPar.Zdfd);
	memmove(Key,Str,2);
	Key[2]=0;
	cFlag=atoi(Key);
	sprintf(SysPar.Zdfd,"%c%s",cFlag,&Str[2]);

	sprintf(Str,"%02d%s",SysPar.Zdhy[0],&SysPar.Zdhy[1]);
	strcpy(SysPar.Zdhy, Str);
	Accept(15,17,SysPar.Zdhy, 10, 0 ,StrMode);
	strcpy(Str, SysPar.Zdhy);
	memmove(Key,Str,2);
	Key[2]=0;
	cFlag=atoi(Key);
	sprintf(SysPar.Zdhy,"%c%s",cFlag,&Str[2]);

	sprintf(Str,"%02d%s",SysPar.Hjj[0],&SysPar.Hjj[1]);
	strcpy(SysPar.Hjj, Str);
	Accept(16,17,SysPar.Hjj, 10, 0 ,StrMode);
	strcpy(Str, SysPar.Hjj);
	memmove(Key,Str,2);
	Key[2]=0;
	cFlag=atoi(Key);
	sprintf(SysPar.Hjj,"%c%s",cFlag,&Str[2]);

	sprintf(Str,"%02d%s",SysPar.Zjj[0],&SysPar.Zjj[1]);
	strcpy(SysPar.Zjj, Str);
	Accept(17,17,SysPar.Zjj, 10, 0 ,StrMode);
	strcpy(Str, SysPar.Zjj);
	memmove(Key,Str,2);
	Key[2]=0;
	cFlag=atoi(Key);
	sprintf(SysPar.Zjj,"%c%s",cFlag,&Str[2]);

	sprintf(Str,"%02d%s",SysPar.PrintInit[0],&SysPar.PrintInit[1]);
	strcpy(SysPar.PrintInit, Str);
	Accept(18,17,SysPar.PrintInit, 10, 0 ,StrMode);
	strcpy(Str, SysPar.PrintInit);
	memmove(Key,Str,2);
	Key[2]=0;
	cFlag=atoi(Key);
	sprintf(SysPar.PrintInit,"%c%s",cFlag,&Str[2]);

	sprintf(Str,"%02d%s",SysPar.Printhy[0],&SysPar.Printhy[1]);
	strcpy(SysPar.Printhy, Str);
	Accept(19,17,SysPar.Printhy, 10, 0 ,StrMode);
	strcpy(Str, SysPar.Printhy);
	memmove(Key,Str,2);
	Key[2]=0;
	cFlag=atoi(Key);
	sprintf(SysPar.Printhy,"%c%s",cFlag,&Str[2]);
	for(;;)
	{
		DispWord(21,3,"是否确认:(1/0)[ ]",NormalMode);
		Accept(21,18,Key, 1, 0 ,InitStrNumMode);
		if(Key[0]>='0'&&Key[1]<='1')
			break;
	}

	if(Key[0]=='1')
	{
		for(;;)
		{
			DispWord(21,3,"请输入文件名:       ",NormalMode);
			Accept(21,17,Str,80, 0 ,InitStrMode);
			if((fp=fopen(Str,"wt"))==NULL)
			{
				DispMenuPro("Can't open write txt");
				getchar();
			}
			else
				break;
		}
		fclose(fp);
		WriteHard(Str);
		PutSec(Str, MenuFilePass);
		Str[strlen(Str)-4]=0;
		sprintf(Str2,"mv %s.bak %s",Str, Str);
		system(Str2);
		SysPar=Tmp;
		return 1;
	}
	SysPar=Tmp;
	return 0;
}

char  DispEditMenu(char *Str1, char MenuAccept[][81], struct MenuOptStru *P, char Mode)
{
	char		Str[400];
	char		Key[3];
	int		i;
	FILE 		*fp;
	DispRanc(OneMenuStartX + 1, 0, ScrEx-1, ScrEy-2, ClrMode);
	DispWord(4,27,Str1,NormalMode);
	DispWord(5,24,"============================",NormalMode);
	DispWord(7,3,"菜单项代码  :",NormalMode);
	sprintf(Str, "%ld", P->MenuNum);
	DispWord(7,37,Str,NormalMode);
	DispWord(8,3,"菜单项名称  :",NormalMode);
	DispWord(8,37,P->MenuName,NormalMode);
	DispWord(9,3,"调 用 函 数 :",NormalMode);
	DispWord(9,37,P->Command,NormalMode);
	DispWord(10,3,"简 易 提 示 :",NormalMode);
	DispWord(10,37,P->ProInf,NormalMode);
	DispWord(11,3,"交 易 代 码 :",NormalMode);
	sprintf(Str, "%ld", P->JyCode);
	DispWord(11,37,Str,NormalMode);
	DispWord(12,3,"热        键:",NormalMode);
	DispMenuPro("按 i 键不输入热键");
	DispWord(12,37,P->HotKey,NormalMode);
	DispWord(13,3,"程序处理条件:",NormalMode);
	DispRanc(6, 1, 14, ScrEy-2, DrawMode);
	refresh();
	if(Mode!=3)
	{
		strcpy(MenuAccept[1],P->MenuName);
		strcpy(MenuAccept[2],P->Command);
		strcpy(MenuAccept[3],P->ProInf);
		sprintf(MenuAccept[4], "%ld", P->JyCode);
		sprintf(MenuAccept[5], "%s", P->HotKey);
		Accept(8, 17,MenuAccept[1], MenuNameLeng-1, 0 ,StrMode);
		Accept(9, 17,MenuAccept[2], CommLeng-1, 0 ,StrMode);
		Accept(10,17,MenuAccept[3], ProLeng, 0 ,StrMode);
		Accept(11,17,MenuAccept[4], 3, 0 ,StrNumMode);
		for(;;)
		{
			Accept(12,17,MenuAccept[5], 10, 0 ,StrMode);
			if(MenuAccept[5][0]!='i')
			{
				if((i=CheckAllKey(MenuAccept[5]))==-1)
				{
					DispMenuPro("无此键, 请查看键的名称");
					for(;GetKey1()!=_Enter;);
					DispMenuPro("按 i 键不输入热键");
				}
				else
				{
					DispWord(12,37,"           ",NormalMode);
					DispWord(12,37,MenuAccept[5],RefreshMode);
					break;
				}
			}
			else
				break;
		}
		Accept(13,17,MenuAccept[6], 50, 0 ,InitStrMode);
		strcpy(P->MenuName,MenuAccept[1]);
		strcpy(P->Command,MenuAccept[2]);
		strcpy(P->ProInf,MenuAccept[3]);
		P->JyCode=atoi(MenuAccept[4]);
		if(MenuAccept[5][0]=='i')
			MenuAccept[5][0]=0;
		strcpy(P->HotKey,MenuAccept[5]);
	}
	for(;;)
	{
		DispWord(15,3,"是否确认:(1/0)[ ]",NormalMode);
		Accept(15,18,Key, 1, 0 ,InitStrNumMode);
		if(Key[0]>='0'&&Key[1]<='1')
			break;
	}

	if(Key[0]=='1')
	{
		sprintf(Str, "%s.bak", SysPar.MenuFileName);
		if((fp=fopen(Str,"wt"))==NULL)
		{
			DispMenuPro("Can't open write txt");
			getchar();
			return;
		}
		WriteMenuStru(MenuArry, fp);
		if(Mode!=3&&Mode!=4)
		{
			fprintf(fp, "@%ld,%s,%s,%s,%ld,%s,0.\n", 
				P->MenuNum,P->MenuName,
				P->Command,P->ProInf,
				P->JyCode, P->HotKey);
		}
		fclose(fp);
		strcat(SysPar.MenuFileName,".bak");
		PutSec(SysPar.MenuFileName, MenuFilePass);
		SysPar.MenuFileName[strlen(SysPar.MenuFileName)-8]=0;
		sprintf(Str,"mv %s.bak.bak %s",SysPar.MenuFileName,
					SysPar.MenuFileName);
		system(Str);
		return 1;
	}
	else
	{
		PutSec(SysPar.MenuFileName, MenuFilePass);
		SysPar.MenuFileName[strlen(SysPar.MenuFileName)-4]=0;
	}
	return 0;
}

void ScMenuNum(struct MenuOptStru *Menu, long MenuNum)
{
	long		i;
	struct MenuOptStru *P1, *P2;
	P1=P2=Menu;
	i=MenuNum+1;
	for(;P1&&P1->MenuNum;)
	{
		if(P1)
		{
			if(P1->MenuNum>0)
				P1->MenuNum=i++;
		}
		if(P1->DOpt&&P1->MenuNum>0)
			ScMenuNum(P1->DOpt, P1->MenuNum*100);
		P1=P1->ROpt;
		if(P1==P2)
			break;
	}
}

void EditMenuStru(struct MenuOptStru *Menu)
{
	char 					Str[80];
	char					Password[20];
	int						Choice;
	int						i, j;
	char					MenuAccept[15][81];
	char					ManagerPass[4];
	struct MenuOptStru   	P, *P1, *P2;
	P=*Menu;
	//strcpy(MenuAccept[0],FixPass);
	//strcat(MenuAccept[0], "flq");
//	strcat(MenuAccept[0], SysPar.SysDate);
	DispWord(12,34,"请输入密码:", NormalMode);
	refresh();
	//Accept(12,46,Str,strlen(MenuAccept[0]), 0 ,InitPasswdMode);
	Accept(12,46,ManagerPass,0,0,InitPasswdMode);
	if(strcmp(ManagerPass,"fcywda")==0)
	{
		for(;;)
		{
			DispRanc(OneMenuStartX + 1, 0, ScrEx-1, ScrEy-1, ClrMode);
			DispWord(5,32,"编辑菜单选项",NormalMode);
			DispWord(6,25,"============================",NormalMode);
			DispWord(8, 27,"1. 此菜单项上增一菜单项",NormalMode);
			DispWord(9, 27,"2. 此菜单项下增一菜单项",NormalMode);
			DispWord(10,27,"3. 删 除 此 菜 单 选 项",NormalMode);
			DispWord(11,27,"4. 删 除 下 一 菜 单 项",NormalMode);
			DispWord(12,27,"5. 修 改 此 菜 单 选 项",NormalMode);
			DispWord(13,27,"6. 增 加 下 一 级 菜 单",NormalMode);
			DispWord(14,27,"7. 查 看 键 的 热 键 值 ",NormalMode);
			DispWord(15,27,"8. 修 改 菜 单 控 制 值 ",NormalMode);
			DispWord(16,27,"0. 退                出",NormalMode);
			DispRanc(7,23,17,53,DrawMode);
			for(;;)
			{
				DispWord(19,30,"请选择:【   】", NormalMode1);
				Accept(19,40,Str,2, 0 ,InitNumMode);
				if(!isdigit(Str[0]))
					continue;
				Choice=atoi(Str);
				if(Choice>=0&&Choice<=10)
					break;
			}
			if(Choice==0)
				break;
			if(Choice==1)
			{
				P2=MenuArry;
				P.MenuNum=Menu->MenuNum;
				P.LOpt=Menu->LOpt;
				P.ROpt=Menu;
				P.DOpt=NULL;
				P.UOpt=NULL;

				if(Menu->UOpt)
				{
					if(Menu->UOpt->DOpt==Menu)
						Menu->UOpt->DOpt=&P;
				}
				else
				{
					if(Menu==MenuArry)
						MenuArry=&P;
				}
					
				Menu->LOpt->ROpt=&P;
				Menu->LOpt=&P;

				ScMenuNum(MenuArry,0);
				MenuArry=P2;
				if(DispEditMenu("此菜单项上增一菜单项", MenuAccept, &P, 1))
				free(MenuArry);
				sprintf(Str,"%s.bak",SysPar.MenuFileName);
				MenuInit(Str, AutoCalMode);
				sprintf(Str, "rm %s.bak", 
						SysPar.MenuFileName);	
				system(Str);
				break;
			}
			if(Choice==2)
			{
				P2=MenuArry;
				P.MenuNum=Menu->MenuNum;
				P.LOpt=Menu;
				P.ROpt=Menu->ROpt;
				P.DOpt=NULL;
				P.UOpt=NULL;

				Menu->ROpt->LOpt=&P;
				Menu->ROpt=&P;

				ScMenuNum(MenuArry,0);
				MenuArry=P2;
				DispEditMenu("此菜单项下增一菜单项", MenuAccept, &P, 2);
				free(MenuArry);
				sprintf(Str,"%s.bak",SysPar.MenuFileName);
				MenuInit(Str, AutoCalMode);
				sprintf(Str, "rm %s.bak", 
						SysPar.MenuFileName);	
				system(Str);
				break;
			}

			if(Choice==3||Choice==4)
			{
				P2=MenuArry;
				if(Choice==4)
					Menu=Menu->ROpt;
				if(Menu->DOpt)
				{
					DispMenuPro("有下一级菜单,不能删除,敲任一键继续!");
					getchar();
					DispMenuPro(Menu->ProInf);
					continue;
				}
				Menu->MenuNum=-1;
				ScMenuNum(MenuArry,0);
				MenuArry=P2;
				DispEditMenu("删 除 此 菜 单 选 项", MenuAccept, &P, 3);
				free(MenuArry);
				sprintf(Str,"%s.bak",SysPar.MenuFileName);
				MenuInit(Str, AutoCalMode);
				sprintf(Str, "rm %s.bak", 
						SysPar.MenuFileName);	
				system(Str);
				break;
			}
			if(Choice==5)
			{
				DispEditMenu("修 改 此 菜 单 选 项", MenuAccept, Menu, 4);
				free(MenuArry);
				sprintf(Str,"%s.bak",SysPar.MenuFileName);
				MenuInit(Str, AutoCalMode);
				sprintf(Str, "rm %s.bak", 
						SysPar.MenuFileName);	
				system(Str);
				break;
			}
			if(Choice==6)
			{
				P1=Menu;
				if(P1->DOpt)
				{
					DispMenuPro("已有下一级菜单,不能增加,敲任一键继续!");
					getchar();
					DispMenuPro(Menu->ProInf);
					continue;
				}
				if(P1->MenuNum>100000000)
				{
					DispMenuPro("菜单不能大于四级,不能增加,敲任一键继续!");
					getchar();
					DispMenuPro(Menu->ProInf);
					continue;
				}
				P1->DOpt=&P;
				P.MenuNum=P1->MenuNum*100+1;
				P.DOpt=NULL;
				P.UOpt=P1;
				P.LOpt=P.ROpt=&P;
				ScMenuNum(MenuArry,0);
				DispEditMenu("增 加 下 一 级 菜 单", MenuAccept, &P, 5);
				free(MenuArry);
				sprintf(Str,"%s.bak",SysPar.MenuFileName);
				MenuInit(Str, AutoCalMode);
				sprintf(Str, "rm %s.bak", 
						SysPar.MenuFileName);	
				system(Str);
				break;
			}
			if(Choice==7)
			{
				DispRanc(OneMenuStartX + 1, 0, ScrEx-1, ScrEy-2, ClrMode);
				mvaddstr(10,10,"This Key Value=");
				refresh();
				DispMenuPro("按小写 q 退出热键值测试程序");
				for(;(i=GetKey1())!='q';)
				{
					for(j=0;j<30;j++)
					{
						mvprintw(10,j+10," ");
						refresh();
					}
					mvprintw(10,10,"This Key Value=%d",i);	
					refresh();
				}
				DispRanc(OneMenuStartX + 1, 0, ScrEx-1, ScrEy-2, ClrMode);
				DispMenuPro(" ");
			}

			if(Choice==8)
			{
				DispRanc(OneMenuStartX + 1, 0, ScrEx-1, ScrEy-2, ClrMode);
				DispEditCtrl("修改菜单控制选项", MenuAccept, 8);
				DispRanc(OneMenuStartX + 1, 0, ScrEx-1, ScrEy-2, ClrMode);
				sprintf(Str,"%s.bak",SysPar.MenuFileName);
				GetSysData(Str);
				sprintf(Str, "rm %s.bak", 
						SysPar.MenuFileName);	
				system(Str);
				DispMenuPro(" ");
			}
			else 
			{
				beep();
				DispMenuPro("Your Select is error!");
				getch();
			}
		}
	}
}

void DispMenu(struct MenuOptStru *Menu)
{
	int 					i, Key, MenuNum;
	struct MenuOptStru		*P, *P1, *P2, *P3;
	char					Str[100];
	char					Str1[81];
	long					Jym;
	
	initscr();
	P=Menu;
	DispMenuHead();
	DispMenuItem(P, NormalMode);
	DispMenuPro(P->ProInf);
	for(;;)
	{
		CurrentMenu=P;
		if(ProMode==MenuMode)
		{
			Key=GetKey();
			if(Key==6)
			{
				if((Key=GetKey())==26)
				{
					DispMenuTwoAll(P, ClrMode);
					EditMenuStru(P);
					DispMenuTwoAll(P, ClrMode1);
					DispMenuPro(MenuArry->ProInf);
					DispMenuHead();
					DispMenuItem(MenuArry, NormalMode);
					P=MenuArry;
					continue;
				}
			}
	
			if(Key==_Enter||Key==_Down&&P->UOpt==NULL)
			{
				if(P->DOpt)
				{
					P=P->DOpt;
					DispMenuPro(P->ProInf);
					DispMenuTwo(P, DrawMode);
					DispMenuItem(P, NormalMode);
				}
				else
				{
					if(strstr(P->MenuName,"退")&&
						strstr(P->MenuName,"出")||
						strstr(P->MenuName,"exit")||
						strstr(P->MenuName,"Exit")||
						strstr(P->MenuName,"EXIT")||
						strstr(P->MenuName,"Quit")||
						strstr(P->MenuName,"quit")|| 
						strstr(P->MenuName,"QUIT"))
					{
						endwin();
						return;
					}
					if(strstr(P->MenuName,"键")&&
					   strstr(P->MenuName,"盘")&&
					   strstr(P->MenuName,"键")&&
					   strstr(P->MenuName,"值"))
					{
						DispMenuTwoAll(P, ClrMode1);
						DispMenuPro("按 q 不保留键值退出, 按 i 此键无效");
						if(AcceptAllKey(1))
						{
							for(;;)
							{
								DispWord(ScrEx-2,10,"请输入键盘值文件名:",RefreshMode);
								Accept(ScrEx-1,3,Str,80, 0 ,InitStrMode);
								if(WriteAllKey(Str, DrawMode))
									break;
							}
							PutSec(Str, MenuFilePass);
							Str[strlen(Str)-4]=0;
							sprintf(Str1,"mv %s.bak %s",Str, Str);
							system(Str1);
						}
						DispMenuTwoAll(P, ClrMode1);
						DispMenuPro(P->ProInf);
						DispMenuTwoAll(P, DrawMode);
						continue;
					}
					if(strstr(P->MenuName,"硬")&&
					   strstr(P->MenuName,"件")&&
					   strstr(P->MenuName,"参")&&
					   strstr(P->MenuName,"数"))
					{
						DispMenuTwoAll(P, ClrMode);
						DispEditMach("修改硬件类型选项");
						DispMenuTwoAll(P, ClrMode1);
						DispMenuPro(P->ProInf);
						DispMenuTwoAll(P, DrawMode);
						continue;
					}
					if(P->Command[0]==0)
					{
						DispMenuPro("此功能未开通,敲回车继续!");
						for(;GetKey()!=_Enter;);
						DispMenuPro(P->ProInf);
					}
					else
					{
						SysTran.CurrentMenuNum=P->MenuNum;
						if(SysCall(P->Command))
						{
							DispWord(OneMenuStartX,ScrEy-2,"  ", NormalMode1);
							wrefresh(curscr);
							DispMenuHead();
							P1=P;
							for(;P1->UOpt;P1=P1->UOpt);
							DispMenuItem(P1, NormalMode);
						}
						else
						{
							//DispMenuPro("                          ");
							DispMenuPro(P->ProInf);
						}
					}
				}
				continue;
			}

			if(Key==_Esc||Key=='0')
			{
				if(P->UOpt)
				{
					DispMenuTwo(P, ClrMode);
					P=P->UOpt;
					DispMenuPro(P->ProInf);
				}
			}
	
			if(Key==_Right)
			{
				if(P->UOpt==NULL)
				{
					DispMenuItem(P, !NormalMode);
					P=P->ROpt;
					DispMenuPro(P->ProInf);
					DispMenuItem(P, NormalMode);
				}
				else
				{
					if(P->DOpt&&P->Sy<P->DOpt->Sy)
					{
							P=P->DOpt;
							DispMenuPro(P->ProInf);
							DispMenuTwo(P, DrawMode);
							DispMenuItem(P, NormalMode);
					}
					else
					{
						if(P->MenuNum>10000&&P->UOpt->UOpt->RanEy > P->Sy)
						{
							DispMenuTwo(P, ClrMode);
							P=P->UOpt;
							DispMenuPro(P->ProInf);
						}
						else
						{
							DispMenuTwoAll(P, ClrMode1);
							for(;;)
							{
								if(P->UOpt) 		P=P->UOpt;
								else 				break;
							}
							P=P->ROpt;
							if(P->DOpt)
							{
								DispMenuPro(P->DOpt->ProInf);
								DispMenuItem(P->LOpt, !NormalMode);
								DispMenuItem(P, NormalMode);
								P=P->DOpt;
								DispMenuTwo(P, DrawMode);
								DispMenuItem(P, NormalMode);
							}
							else
							{
								DispMenuPro(P->ProInf);
								DispMenuItem(P->LOpt, !NormalMode);
								DispMenuItem(P, NormalMode);
							}
						}
					}
				}
			}

			if(Key==_Left)
			{
				if(P->UOpt==NULL)	//一级菜单移动
				{
					DispMenuItem(P, !NormalMode);
					P=P->LOpt;
					DispMenuPro(P->ProInf);
					DispMenuItem(P, NormalMode);
				}
				else
				{
					if(P->DOpt&&P->Sy>P->DOpt->Sy)    //左键移动移出下一级菜单
					{
							P=P->DOpt;
							DispMenuPro(P->ProInf);
							DispMenuTwo(P, DrawMode);
							DispMenuItem(P, NormalMode);
					}
					else
					{
						//左键回到上一级
						if(P->MenuNum>10000&&P->UOpt->UOpt->RanEy < P->Sy)
						{
							DispMenuTwo(P, ClrMode);
							P=P->UOpt;
							DispMenuPro(P->ProInf);
						}
						else	//移到下一个一级菜单
						{
							DispMenuTwoAll(P, ClrMode1);
							for(;;)
							{
								if(P->UOpt) 		P=P->UOpt;
								else 				break;
							}
							P=P->LOpt;
							if(P->DOpt)
							{
								DispMenuPro(P->DOpt->ProInf);
								DispMenuItem(P->ROpt, !NormalMode);
								DispMenuItem(P, NormalMode);
								P=P->DOpt;
								DispMenuTwo(P, DrawMode);
								DispMenuItem(P, NormalMode);
							}
							else
							{
								DispMenuPro(P->ProInf);
								DispMenuItem(P->ROpt, !NormalMode);
								DispMenuItem(P, NormalMode);
							}
						}
					}
				}
			}

			if(Key==_Up&&P->UOpt)
			{
				DispMenuItem(P, !NormalMode);
				P=P->LOpt;
				if(P->MenuName[0]=='-')
					P=P->LOpt;	
				DispMenuPro(P->ProInf);
				DispMenuItem(P, NormalMode);
			}
	
			if(Key==_Down&&P->UOpt)
			{
				DispMenuItem(P, !NormalMode);
				P=P->ROpt;
				if(P->MenuName[0]=='-')
					P=P->ROpt;
				DispMenuPro(P->ProInf);
				DispMenuItem(P, NormalMode);
			}

			if(Key==_Tab)
			{
				ProMode=JymMode;
				continue;
			}

			if(Key>='1'&&Key<='9'||Key>='a'&&Key<='z')
			{
				if(Key>='a')		Key=Key-'a'+10;
				else				Key=Key-'1'+1;
				P2=P1=P;
				MenuNum=P->MenuNum/100*100+99;
				if(P1->UOpt)
				{
					P1=P1->UOpt->DOpt;
					for(i=0;(P1+i)->MenuNum!=0&&(P1+i)->MenuNum<MenuNum;i++)
					{
						if((P1+i)->MenuNum%100==Key)
						{
							P=P1+i;
							break;
						}
					}
					if(P2!=P)
					{
						if(P->MenuName[0]=='-')
							P=P->ROpt;
						DispMenuItem(P2, !NormalMode);
						DispMenuPro(P->ProInf);
						DispMenuItem(P, NormalMode);
					}
				}
				else
				{
					P2=P;
					P1=MenuArry;
					for(i=0;(P1+i)->MenuNum!=0&&(P1+i)->MenuNum<MenuNum;i++)
					{
						if((P1+i)->MenuNum%100==Key)
						{
							P=P1+i;
							break;
						}
					}
					if(P2!=P)
					{
						DispMenuPro(P->ProInf);
						DispMenuItem(P, NormalMode);
						DispMenuItem(P2, !NormalMode);
					}
				}
			}
		}
		else 
		{
			DispMenuTwoAll(P, ClrMode1);
			DispMenuPro(MenuArry->ProInf);
			DispMenuHead();
			DispMenuItem(MenuArry, NormalMode);
			for(;;)
			{
				DispWord(ScrEx - 1, 69, "【     】", NormalMode);
				if(Accept(ScrEx - 1,72,Str,3, 0 ,InitStrNumMode)==_Tab)
				{
					ProMode=MenuMode;
					refresh();
					DispWord(ScrEx - 1, 69, "         ", NormalMode);
					move(ScrEx, 78);
					refresh();
						
					P=MenuArry;
					DispMenuPro(P->ProInf);
					DispMenuHead();
					DispMenuItem(P, NormalMode);
					break;
				}
				Jym=atoi(Str);
				if(!Jym)
					continue;
				Str[0]=0;
				for(i=0, P=NULL;(MenuArry+i)->MenuNum;i++)
				{
					if((MenuArry+i)->JyCode==Jym)
					{
						P=MenuArry+i;
						break;
					}
				}
				if(P==NULL)
					continue;
				SysTran.CurrentMenuNum=P->MenuNum;
				if(strstr(P->MenuName, "退")&&
					strstr(P->MenuName, "出")||
					strstr(P->MenuName,"exit")||
					strstr(P->MenuName,"Exit")||
					strstr(P->MenuName,"EXIT")||
					strstr(P->MenuName,"Quit")||
					strstr(P->MenuName,"quit")||
					strstr(P->MenuName,"QUIT"))
				{
					endwin();
					return;
				}
				if(P->Command[0]==0)
				{
					DispMenuPro("此功能未开通,敲回车继续!");
					for(;GetKey()!=_Enter;);
					DispMenuPro(P->ProInf);
				}
				else if(SysCall(P->Command))
				{
					wrefresh(curscr);
					//endwin();
					//initscr();
				}
				//DispMenuPro(MenuArry->ProInf);
				//DispMenuHead();
				//DispMenuItem(MenuArry, NormalMode);
			}
		}
	}
}

void Clock(int Sencond)
{
	time_t		t1;
	struct tm 	*t2;
	int		x,y;

	savetty();
	if(SysPar.ClockFlag=='1')
	{
		t1=time(0);
		t2=localtime(&t1);
		sprintf(SysTime,"[%04d/%02d/%02d %02d:%02d:%02d]", 
			t2->tm_year+1900,t2->tm_mon+1,t2->tm_mday,t2->tm_hour,t2->tm_min, t2->tm_sec);
		getyx(stdscr,x,y);
		DispWord(0,57,SysTime,NormalMode);
		move(x,y);
		refresh();
	}
	signal(SIGINT, IntProcess);
	signal(SIGQUIT, IntProcess);
	signal(SIGALRM, Clock);
	alarm(1);
	resetty();
}


void main(int argc, char **argv)
{
	long				Pid;
	long				Leng;
	char				Buf[100];
	FILE				*fp;

	if(argc<2)
	{
		printf("Usage:%s MenuCtrlFile\n", argv[0]);
		exit(0);
	}
	if((fp=fopen("/usr/bin/euc/vsh","rt"))==NULL)
		exit(0);
	else
	{
		fgets(FixPass,9,fp);
		FixPass[strlen(FixPass)-1]=0;
		fclose(fp);
	}
	if((fp=fopen(argv[1],"rt"))==NULL&&strcmp(argv[2],"creat")==0)
	{
		fclose(fp);
		fp=fopen(argv[1],"wt");
		fprintf(fp,"#1,,,%sres.dat,%s,1,1,,,,,,,,,,,,,浙江城市商业银行,lpf.\n",
			argv[1],argv[1]);
		fclose(fp);
		strcpy(Buf,argv[1]);
		PutSec(Buf, MenuFilePass);
		sprintf(Buf,"mv %s.bak %s",argv[1], argv[1]);
		system(Buf);
	}
	else
	{
		if(fp==NULL)
		{
			printf("Can't Open MenuFile\n");
			return;
		}
	}

	strcpy(Buf,argv[1]);
	PutSec(Buf, MenuFilePass);
	if(GetSysData(Buf)==0)
	{
		sprintf(Buf, "rm %s.bak", argv[1]);	
		system(Buf);
		return;
	}
	signal(SIGINT, IntProcess);
	signal(SIGQUIT, IntProcess);

	if(PutSec(SysPar.KeyFile, MenuFilePass))
	{
		ReadAllKey(SysPar.KeyFile);
		sprintf(Buf,"rm %s",SysPar.KeyFile);
		system(Buf);
		SysPar.KeyFile[strlen(SysPar.KeyFile)-4]=0;
		KeyFz();
	}
	if(SysPar.ClockFlag=='1')
	{
		signal(SIGALRM, Clock);
		alarm(1);
	}
	strcat(SysPar.MenuFileName,".bak");
	MenuInit(SysPar.MenuFileName, AutoCalMode);
	sprintf(Buf, "rm %s", SysPar.MenuFileName);	
	system(Buf);
	SysPar.MenuFileName[strlen(SysPar.MenuFileName)-4]=0;
	DispMenu(MenuArry);
	free(MenuArry);
	DelShareMem(SysPar.ProcessId);
}
