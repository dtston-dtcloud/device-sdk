#ifndef _KEY_H_
#define _KEY_H_

#include "UAConfig.h"

#ifdef	____D_UA_KEY_DEMO_SUPPORT____

//#define LED_original_value  0            //��ʼ״̬
//#define LED_gpio  GPIO_15                 //  led��


//#define RELAY_gpio  GPIO_8              //�̵���
//#define RELAY_original_value  0        //��ʼ״̬

#endif


#ifdef	____D_UA_KEY_DEMO_SUPPORT____
//=========================����ģ������=============================================================
#define  key_original_value  1		   //������ʼ״̬�ߵ�ƽ1 ���µ͵�ƽ 0 ��Ӳ�����������

#define  DOUBLE_PRESS  0			   //�Ƿ���˫������     ��1   �� 0

#ifdef	____D_Project_UA420_STYLE____
#define  KEY_GPIO   GPIO_15
#elif defined(____D_Project_UA402_CloudModule____)
#define  KEY_GPIO   GPIO_8
#elif defined(__CUSTOMER_WYYL__)
#define KEY_GPIO   GPIO_3
#define	KEY_PRESS_LEVEL	1			// ���¸ߵ�ƽ
#else
//  ____D_Project_UA402_STYLE____
#define KEY_GPIO   GPIO_8
#define KEY_PRESS_LEVEL 0		// ���µ͵�ƽ
#endif
//#define  KEY_IQR_ON       //�Ƿ����жϴ���    define��     //#defineû��


#define KEY_LONG_DOWN_SMART_LINK 3 		/*�������������Ͻ�������ģʽ����λΪ��*/
#define KEY_LONG_DOWN_SOFTAP_LINK 10	/*�������������Ͻ���softap����ģʽ����λΪ��*/

#define KEY_DOWN_LONG_TIME			(3000)	// 3000 ms
#define KEY_DOWN_LONG_LONG_TIME		(9000)	// 6000 ms


//==========================��ʱ����תʱ��==================================
#define	key_Time_ms		50			   //50msһ��ִ��
#define  Shake_Time 1				   //����ʱ��      50ms     ���������������ֲ�������
#define  Double_Press_Time 5		   //˫�����ʱ��  250ms    ����˫���ڴ˵�������ʶ��ʱ��
#define  Double_Press_Timeout  10	   //˫����ʼ��ʱʱ��    500ms

#ifdef	____D_UA_LAMPGATE_SUPPORT____
#define  Press_Long_Time   (5000 / key_Time_ms )
													//����ʱ��      5 000ms
#define  Press_Long_long_Time  (10000 / key_Time_ms )
														//������ʱ��    10 000ms
#elif defined(____D_Project_UA402_CloudModule____)
#define  Press_Long_Time   (3000 / key_Time_ms )
													//����ʱ��      5 000ms
#define  Press_Long_long_Time  (10000 / key_Time_ms )
														//������ʱ��    10 000ms
#else
#define  Press_Long_Time   200	   //����ʱ��      10 000ms
#define  Press_Long_long_Time  220 //������ʱ��    22 000ms
#endif

//===========================================================================
//���弸���龰״̬
enum
{
	BUTTON_PRESS_NONE = 0,
	BUTTON_PRESS_DOWN,
	BUTTON_PRESS_UP,
	BUTTON_DOUBLE_PRESS_DOWN,
	BUTTON_PRESS_DOWN_LONG1,
	BUTTON_PRESS_DOWN_LONG2
};

 //���弸�ְ�������
enum
{
	APP_BUTTON_PRESS_NONE1 = 0,
	APP_BUTTON_PRESS_NONE2,

	APP_BUTTON_ACTION_CLICK,

	APP_BUTTON_ACTION_WAIT_DOUBLE_CLICK,
	APP_BUTTON_ACTION_DOUBLE_CLICK_Down,
	APP_BUTTON_ACTION_DOUBLE_CLICK_NO_UP,
	APP_BUTTON_ACTION_DOUBLE_CLICK,

	APP_BUTTON_ACTION_LONG_PRESS,
	APP_BUTTON_ACTION_LONG_PRESS_NO_UP,

	APP_BUTTON_ACTION_LONG_LONG_PRESS,
	APP_BUTTON_ACTION_LONG_LONG_PRESS_NO_UP
};

#endif



//----------------------------------------
extern void F_KEY_Init(void);

#endif
