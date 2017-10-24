#ifndef	____UA_TIME_clock_Inc_H____
	   #define	____UA_TIME_clock_Inc_H____


//--------------------------------------------------------------
////	�÷�
/*

*/



//--------------------------------------------------------------
////	ͷ�ļ�
////	�ⲿ����ʱ��Ҫʹ�õ�
#include	"gcc_time.h"

#include	"uRan_Macro_Contiki.h"


//--------------------------------------------------------------
////	Define

#define	D_ActionTimer_Amount	5	//	��ʱ������
#define	D_ActionTimer_InvalidID	0xffffffff



//--------------------------------------------------------------
////	�ṹ��...����

typedef enum _EActionTimerMode{
	E_ActionTimerMode_Off = 0,
	E_ActionTimerMode_OneTime,
	E_ActionTimerMode_DayRepeat,
	E_ActionTimerMode_WeekRepeat,
	E_ActionTimerMode_MonthRepeat,
	E_ActionTimerMode_Delay,

	E_ActionTimerMode_Max,

	E_ActionTimerMode_StopBit = 0x80,
}EActionTimerMode;

typedef void (*PF_ActionTimer_CallBack)(void * pPara);
typedef struct _SActionTimer
{
	UID128	uID;
	EActionTimerMode eMode;
	TDWORD	dwRepeatFlag;		//	��|��ѭ����flag
	union {
	struct tm	sTm;			//	�Ƚ�������
	TDWORD	dwSec;				//	unixʱ��, ֻ��������ʱ
	} u;
	PF_ActionTimer_CallBack pfHdl;
	TBYTE	btSocket;			//	��ڱ��
	TBYTE	btOnOff;
	TBYTE	btRev0;
	TBYTE	btRev1;
} SActionTimer;

// ֻ��������/��ȡ
typedef struct _SActionSetTimerInfo
{
	TBYTE	btIndex;
	TBYTE	btMode;				//	EActionTimerMode
	TBYTE	btSocket;			//	��ڱ��
	TBYTE	btOnOff;
	TDWORD	dwSec;				//	unixʱ��/��ʱ,
	TDWORD	dwRepeatFlag;		//	��|��ѭ����flag
} SActionSetTimerInfo;


//--------------------------------------------------------------
////	��������
//----------------------------------------
extern TDWORD	R_dwSecCounter;
extern struct tm system_time_now;

//--------------------------------------------------------------
////	Macro
//--------------------------------------



//--------------------------------------------------------------
////	����
//----------------------------------------

extern void system_time_init(TDWORD dwUnixTime, char * szTime);
extern int	F_ActionTimer_GetTimerList(SActionSetTimerInfo * pTimer, int * piCount);
extern int	F_ActionTimer_Add2(UID128 *puID,  TDWORD dwUnixTime, EActionTimerMode eMode, TBYTE btSocket, TBYTE btOnOff);
extern int	F_ActionTimer_Add3(SActionSetTimerInfo *pTimer);
extern int	F_ActionTimer_DelAll(void);
extern ERetErr	F_ActionTimer_Del3(TBYTE btIndex);
extern ERetErr	F_ActionTimer_Stop3(TBYTE btIndex);
extern ERetErr	F_ActionTimer_Start3(TBYTE btIndex);
extern void F_ActionTimer_Enable(int bEn);

extern void	F_ActionTimer_ATcmd_InitClock(TDWORD dwUnixTime, char * szTime);
extern void	F_ActionTimer_ATcmd_Add(int iMode, int iOnOff);


#endif

