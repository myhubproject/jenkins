#include	"menu.h"
#include	<math.h>

void 		GetToken(void);
int 		isdelim(char Flag);
void 		DispError(int ErrCode);
void 		CalResult(char Operate, long double *Result, 
			  long double *MidResult);
void 		PutTokenBack(void);
void 		ItemKh(long double *Result);
void 		ItemAddSign(long double *Result);
void 		ItemZs(long double *Result);
void 		ItemMult(long double *Result);
void 		ItemAdd(long double *Result);
void 		GetExpress(long double *Result);
#define		DELIMITER	1
#define 	VARIABLE	2
#define		NUMBER		3
char		*Bds;		//�ַ������ʽ
char		Token[1000];
char		TokenType;
char		ErrFlag=0;

//�˾䷨������Ϊ�ݹ��½��䷨������
//���ʽ�䷨�������Ĺ�����
//���ʽ=��[+��][-��]
//��=����[*����][/����]
//����=����,��, ����ʽ 
//�˱��ʽ�ɽ��� + - * / % ^ ( ) �ͳ���
//��((10+100)*2+12+32/12)-100/2*34

//������Ϊ�䷨������������
void GetExpress(long double *Result)
{
	GetToken();
	if(!Token[0])
	{
		DispError(2);
		return;
	}
	ItemAdd(Result);
}

//������Ϊ�������, ���
void ItemAdd(long double *Result)
{
	char			Operate;
	long double		MidResult;		
	ItemMult(Result);
	for(;(Operate=Token[0])=='+'||Operate=='-';)
	{
		GetToken();
		ItemMult(&MidResult);
		CalResult(Operate, Result, &MidResult);
	}
}

//������Ϊ��������˻����
void ItemMult(long double *Result)
{
	char			Operate;	
	long double		MidResult;
	ItemZs(Result);
	for(;(Operate=Token[0])=='*'||Operate=='/'||Operate=='%';)
	{
		GetToken();
		ItemZs(&MidResult);
		CalResult(Operate, Result, &MidResult);
	}
}

//������Ϊָ������
void ItemZs(long double *Result)
{
	long double		MidResult;
	ItemAddSign(Result);
	if(Token[0]=='^')
	{
		GetToken();
		ItemZs(&MidResult);
		CalResult('^', Result, &MidResult);
	}
}

//������������,����
void ItemAddSign(long double *Result)
{
	char	Operate=0;
	if((TokenType==DELIMITER)&&(Token[0]=='+'||Token[0]=='-'))
	{
		Operate=Token[0];
		GetToken();
	}
	ItemKh(Result);
	if(Operate)
	{
		if(Operate=='-')
			*Result*=-1;
	}
}

//���������������еı��ʽ
void ItemKh(long double *Result)
{
	if((TokenType==DELIMITER)&&(Token[0]=='('))
	{
		GetToken();
		ItemAdd(Result);
		if(Token[0]!=')')
			DispError(1);
		GetToken();
	}
	else	//ȡ������ʵ��ֵ
	{
		if(TokenType==NUMBER)
		{
			*Result=(long double)atof(Token);
			GetToken();
		}
		else
			DispError(0);
	}
}

//�����Ʒ���������
void PutTokenBack(void)
{
	char	*p;
	p=Token;
	for(;*p;p++)	Bds--;
}

//����������ָ������������
void CalResult(char Operate, long double *Result, long double *MidResult)
{
	switch(Operate)
	{
		case '+':	*Result+=*MidResult; break;
		case '-':	*Result-=*MidResult; break;
		case '*':	*Result*=*MidResult; break;
		case '/':	
				if(*MidResult==0.00)
					*Result=0;
				else
					*Result/=*MidResult; 
				break;
		case '%':	*Result=(long)(*Result)%(long)(*MidResult);
				break;
		case '^':	*Result=pow(*Result, *MidResult);
				break;
	}
}

void DispError(int ErrCode)
{
	char	Str[2000];
	static char *ErrMsg[]=
	{
		"�﷨����",
		"Բ���������",
		"���ʽ������"
	};
	sprintf(Str,"%s %s",ErrMsg[ErrCode],Bds);
	DispMenuPro(Str);
	ErrFlag=1;
}

//��������FlagΪһ���ֽ��, �򷵻� 1
int isdelim(char Flag)
{
	if(strchr("+-/*%^=()",Flag)||Flag==9||Flag=='\r'||Flag==0)
		return 1;
	return 0;
}

//��������ȡ��һ������
void GetToken(void)
{
	char 	*Tmpp;
	TokenType=0;
	Tmpp=Token;
	for(;isspace(*Bds);Bds++);
	if(strchr("+-*/%^=()",*Bds))
	{
		*Tmpp++=*Bds++;	
		TokenType=DELIMITER;
	}
	else if(isalpha(*Bds))
	{
		for(;!isdelim(*Bds);)  *Tmpp++=*Bds++;
		TokenType=VARIABLE;
	}
	else if(isdigit(*Bds))
	{
		for(;!isdelim(*Bds);)  *Tmpp++=*Bds++;
		TokenType=NUMBER;
	}
	*Tmpp=0;
}

#define		LineStart		13
#define		LineEnd			18

//������һ�����ʽ�䷨������
void main(void)
{
	long double		Answer;
	char			*p;
	char			P[1000];
	char			Str[180];
	char			Str2[180];
	char			Str1[LineEnd-LineStart+1][80];
	long double		Result1;
	long double		Result2;
	long double		Result3;
	int				iLine=13, iTmp;
	InitScr();
	DispWord(4,0,"SunYard ��  ��  ��",NormalMidMode);
	DispWord(5,0,"======================",NormalMidMode);
	DispWord(20,0,"cls=��� [�ۼӺ�] res=[�ۼӺ�] - [��һ�μ���ֵ] quit=�˳�",
			 NormalMidMode);
	DispWord(21,0,"get [1-6]=ȡ�ڼ������ʽ",NormalMidMode);
	for(iTmp=0;iTmp<LineEnd-LineStart+1;iTmp++)
		Str1[iTmp][0]=0;
	Str[0]=0;
	P[0]=0;
	for(Result2=0,Result1=0;;)
	{
		sprintf(Str,"%Lf",Result2);
		for(p=&Str[strlen(Str)-1];p>Str;p--)
		{
			if(*p=='0')
				*p=0;
			else if(*p=='.')
			{
				*p=0;
				break;
			}
			else
				break;
		}
		if((p=strchr(Str,'.'))==NULL||strlen(p+1)<2)
			sprintf(Str,"%.2lf",atof(Str));
		ChBankNum(Str);
		sprintf(Str2,"�ۼӺ�:%21s",Str);
		Str2[56]=0;
		DispMsg(7,12,InitNormalMode,58,"%s",Str2);
		if(strstr(Str2,"��")==NULL)
		{
			DispMsg(7,12,InitNormalMode,58,"�ۼӺ�:Error");
			Result2=0;
		}
		sprintf(Str,"%Lf",Result1);
		for(p=&Str[strlen(Str)-1];p>Str;p--)
		{
			if(*p=='0')
				*p=0;
			else if(*p=='.')
			{
				*p=0;
				break;
			}
			else
				break;
		}
		if((p=strchr(Str,'.'))==NULL||strlen(p+1)<2)
			sprintf(Str,"%.2lf",atof(Str));
		ChBankNum(Str);
		sprintf(Str2,"��һ�μ���ֵ:%15s",Str);
		Str2[56]=0;
		DispMsg(10,12,InitNormalMode,58,"%s",Str2);
		if(strstr(Str2,"��")==NULL)
		{
			DispMsg(10,12,InitNormalMode,58,"��һ�μ���ֵ:Error",Str);
			Result1=0;
		}
		Result1=0;
		DispRanc(6,10,8,70,DrawMode);
		DispRanc(9,10,11,70,DrawMode);
		DispRanc(12,10,19,70,DrawMode);
		Accept(iLine,12,P,58,0,0,StrMode);
		if(strstr(P,"quit"))
			break;
		if(strstr(P,"cls"))
		{
			Result2=0;
			Str[0]=0;
			continue;
		}
		if(strstr(P,"res"))
		{
			Result2+=Result3;
			Str[0]=0;
			Result3=0;
			continue;
		}
		if(strstr(P,"get"))
		{
			GetFormStr(' ',' ',1,P,Str2);
			if(atoi(Str2)>=1&&atoi(Str2)<=6)
			{
				memset(P,0,1000);
				strcpy(P,Str1[atoi(Str2)-1]);
				continue;
			}
			Str2[0]=0;
			memset(P,0,1000);
		}

		Result1=0;
		Bds=P;
		GetExpress(&Result1);
		if(ErrFlag)
		{
			ErrFlag=0;
			Result1=0;
		}
		Result2+=Result1;
		iLine++;
		if(iLine>LineEnd)
		{
			for(iTmp=1;iTmp<LineEnd-LineStart;iTmp++)
				strcpy(Str1[iTmp-1],Str1[iTmp]);
			strcpy(Str1[LineEnd-LineStart-1],P);
			iLine=LineEnd;
			DispRanc(12,10,19,70,ClrMode);
			DispRanc(12,10,19,70,DrawMode);
			for(iTmp=0;iTmp<LineEnd-LineStart;iTmp++)
				DispWord(LineStart+iTmp,12,Str1[iTmp],NormalMode);
		}
		else
			strcpy(Str1[iLine-LineStart-1],P);
		Result3=Result1*-1;
		memset(P,0,1000);
	}
	EndWin();
}
