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
"浙江省行政事业性收费专用收据 ",
"============================",
"┌──────┬───────────┬────┬───────┐",
"│执收单位代码│@S30                  │缴款日期│@i            │",
"├──────┼───────────┼────┼───────┤",
"│执收单位名称│@i24                  │字    轨│@D8           │",
"├──────┼───────────┼────┼───────┤",
"│票 据  类 型│@i24                  │缴款书号│@D8           │",
"├──────┼───────────┼────┼───────┤",
"│收费项目名称│@K                    │票据始号│@S20          │",
"├──────┼───────────┼────┼───────┤",
"│金        额│@B14.2                │票据止号│@S20          │",
"└──────┴───────────┴────┴───────┘",
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
	if(CheckDBErr("打开数据库错",0))
		return;
	$close database;*/
	EndWin();
}
