#include	<stdio.h>
#include	"menu.h"
#include	"sqlsublib.c"

void InitAllSel(struct InputStru *P)
{
	static struct NrStru Nr[]=
	{
		{"End","End"},
	};
}


void main(int argc, char **argv)
{
	$char	DbName[80];
	char	ScrPic[][100]=
	{
"�㽭ʡ������ҵ���շ�ר���վ� ",
"============================",
"���������������Щ����������������������Щ��������Щ���������������",
"��ִ�յ�λ���멦@S30                  ���ɿ����ک�@i            ��",
"���������������੤���������������������੤�������੤��������������",
"��ִ�յ�λ���Ʃ�@i24                  ����    �쩦@D8           ��",
"���������������੤���������������������੤�������੤��������������",
"��Ʊ ��  �� �ͩ�@i24                  ���ɿ���ũ�@D8           ��",
"���������������੤���������������������੤�������੤��������������",
"���շ���Ŀ���Ʃ�@K                    ��Ʊ��ʼ�ũ�@S20          ��",
"���������������੤���������������������੤�������੤��������������",
"����        �@B14.2                ��Ʊ��ֹ�ũ�@S20          ��",
"���������������ة����������������������ة��������ة���������������",
"End",
	};
	char	*Str;
	struct InputStru 	Input;

	InitScr();	

	ScInputStru(&Input, ScrPic);
//	InitAllSel(&Input);
	InitSeq(&Input,"1,6,2,7,3,8,4,9,5,10");
	for(;;)
	{
		ActiveInput(&Input);
		Input.InputNum++;
		if(Input.InputNum==1)
			PutInputValue(&Input,3,"19990101");
		if(Input.InputNum>Input.InputMax)
			break;
	}
	EndInput(&Input);
	/*_GetDBName(DbName,1);
	$database $DbName;
	if(CheckDBErr("�����ݿ��",0))
		return;
	$close database;*/
	EndWin();
}
