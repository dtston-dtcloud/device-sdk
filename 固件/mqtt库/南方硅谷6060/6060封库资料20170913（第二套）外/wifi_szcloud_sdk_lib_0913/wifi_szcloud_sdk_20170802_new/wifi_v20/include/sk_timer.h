
/*������ʱ�������ݽṹ�������ӿ�*/
#ifndef __SK_TIMER_H_H__
#define __SK_TIMER_H_H__

#include "ntp_client.h"

#define SK_TIMER_NUM 8 		/*���֧��8����ʱ���ڵ�*/
#define SK_TIMER_INVALID_ID 0XFF	/*��Ч�ڵ��־*/

#define SK_INVALID_TIME_ZONE 55


#define SK_ON	0x1
#define SK_OFF	0x0

/*ϵͳ�б���Ķ�ʱ���ڵ�*/
typedef struct sk_timer_s
{		
	U8 timer_id;		/*��ʱ��Ψһid������ʱ������APP���ɣ��豸�ᱣ��, 0xFF��ʾ�ö�ʱ����Ч*/
	char timeZone;		/*ʱ��*/
	char timer_action;	/*��ʱ���Ķ���, 0x00��ʾ�ص����أ�0x01 ��ʾ��������*/
	char week_flag; 	/*0~6 bit ��ʾ��һ�������Ƿ������ظ���������λ��ʾ�����ظ�,0x00��ʾִ��һ�ζ�ʱ*/
	U32 time;			/*�����Ч��ʱ�̵�λΪ��*/
} __attribute__ ((packed)) sk_timer_t;

	
extern sk_timer_t gSkTimer[SK_TIMER_NUM];	/*��ʱ���ڵ���*/

struct tm current_daytime;

/*��������ʱ���ڵ���ⲿ��������Ӧ��ģ��ʵ�ּ�����*/
typedef void (*sk_handle_timer_fun)(sk_timer_t *ptimer, void *param, int size, int timeCount);

#define SK_TIMER_DEBUG_ON 1

#if SK_TIMER_DEBUG_ON
#define SK_TIMER_DEBUG(fmt,...) printf(fmt, ##__VA_ARGS__)
#else
#define SK_TIMER_DEBUG(fmt,...)
#endif


/*��ʼ����ʱ���ڵ�*/
extern void init_sk_timer(void);

/*�������еĶ�ʱ���ڵ㣬����fun����fun��Ӧ��ģ��ʵ�ּ�����,����ֵΪ�������Ч�ڵ����*/
extern int sk_for_each_handle(sk_handle_timer_fun fun, void *param, int size);

/*��ӻ����timer�ڵ�, ����ֵ��TRUE - ��ӳɹ������򣬲���ʧ��*/
extern BOOL sk_add_timer(sk_timer_t *ptimer);

/*ɾ��timer�ڵ�*/
extern BOOL sk_del_timer(U8 timerId);

/*ɾ����ʱ���ڵ�, ��������֯��ʱ����*/
extern BOOL sk_remove_timer(int timerId);

/*����������Ϣ*/
extern BOOL sk_save_conf(void);

/*��ʾ��ʱ�ڵ�*/
extern void sk_timer_show(void);

void sk_print_timer_list();

void sk_timer_test();

void sk_timer_check_callback(U32 current_second);

/*��С�����������*/
extern void sk_sort_timer(sk_timer_t *parray);

/*
*	���ú����ӿ�֮ǰ,�ȳ�ʼ��my_timer_list
*/
extern void sk_timer_task_init(sk_timer_t *parray);

/*
 * ����ʱ���������뵽outdata�У�size Ϊoutdata��С, ����ֵΪ��ռ�ô�С, -1 ��ʾʧ��
 */
int sk_timer_get_list(U8 *outdata, int size);

/*���һ��timer�ڵ�ŵ�param����Ӧ��buf��*/
void sk_timer_fill_one_timer(sk_timer_t *ptimer, char *buf, int size);

#endif

