#ifndef _HX_FLASH_OPT_H_
#define _HX_FLASH_OPT_H_

#include "data_buff.h"
#include "uart_cmd.h"
#include "hekr_cmd.h"
//#ifdef __TUYA_CLOUD_SUPPORT__
#include "tuya_http_inf.h"
//#endif
#define HX_SSID_LEN	33
#define HX_BSSID_LEN 13
#define HX_AP_SSID_KEYLEN	16

/*
*������Ϣ��flash�еĴ��:
----No 1------
*conf - 0.5K
*HX - 1K
*TUYA - 1.5K
*AC_CLOUD - 1K
----No 2------
*GIZ_CLOUD - 1K
*SK_TIMER - 1K

*�ڶ�дflash����ʱ����4KΪ��λ����������������֯ʱ��Ҳ��4KΪ��λ������������������������֯ʱ
*�ѷֳ�2�飬ͬʱ���豣֤��д����ʼ��ַҲ��4K�ı߽�
*ͬʱ�����ڵ�2��Ķ�д������GIZ_PARAM_OFFSETΪ��׼������Ľ���ƫ�Ƽ���
*/
#define HX_PARAM_OFFSET (0x200)
#define HX_PARAM_LEN (0x400)	/*1K����*/

#define TUYA_PARAM_OFFSET (HX_PARAM_OFFSET + HX_PARAM_LEN)
#define TUYA_SCHEMA_TABLE_OFFSET	(TUYA_PARAM_OFFSET + sizeof(tuya_cloud_info_t) + 32)
#define TUYA_SCHEMA_OBJ_OFFSET		(TUYA_SCHEMA_TABLE_OFFSET + sizeof(tuya_idx_entry_t) * TUYA_MAX_OBJ_NUM)
#define TUYA_PARAM_END	(TUYA_SCHEMA_OBJ_OFFSET + sizeof(tuya_obj_int_t) * TUYA_MAX_OBJ_NUM)
#define TUYA_PARAM_LEN 0x600	/*1.5K*/


//#if TUYA_SCHEMA_OBJ_OFFSET > (4 * 1024)
//#error "FLASH OFFSET IS BEYOND 4K"
//#endif

#define AC_CLOUD_PARAM_OFFSET (TUYA_PARAM_OFFSET + TUYA_PARAM_LEN)
#define AC_CLOUD_PARAM_LEN (0x400)	/*1K*/
#define AC_CLOUD_PARAM_END	(AC_CLOUD_PARAM_OFFSET + AC_CLOUD_PARAM_LEN)	/*120Ϊsizeof(ZC_ConfigDB)*/

/*------��2��4K------*/
#define GIZ_PARAM_OFFSET AC_CLOUD_PARAM_END
#define GIZ_PARAM_LEN	(0x400)	/*1K����*/
#define GIZ_PARAM_END (GIZ_PARAM_OFFSET + GIZ_PARAM_LEN)	/*�ر���ע����ǣ�GIZ_PARAM_END���ܳ���CFG_CUSTOMER_SIZE*/

#define CONF_SECOND_START GIZ_PARAM_OFFSET	/*��2��4k����ʼλ��,Ӧ��֤��ֵΪ0x1000*/

/*������ʱ��������*/
#define SK_PARAM_OFFSET GIZ_PARAM_END
#define SK_PARAM_LEN	(0x400)	/*1K����*/
#define SK_PARAM_END (SK_PARAM_OFFSET + SK_PARAM_LEN)	/*�ر���ע����ǣ�SK_PARAM_LEN���ܳ���CFG_CUSTOMER_SIZE*/




Boolean hx_write_conf();
void hx_update_parameter(int *p_esp_char, int * p_esp_time, int * p_atpt_time, int * p_frame_length,
		hx_uart_t *p_uart, int *p_gpio_mode, Boolean *p_data_flag, hx_sock_t *p_sock_info);
void hx_update_conn_parameter(char *ssid, char *bssid, char *key);
void hx_init_conn_parameter(char *ssid, char *bssid, char *key);
Boolean hx_init_parameter(int *p_esp_char, int * p_esp_time, int * p_atpt_time, int * p_frame_length,
		hx_uart_t *p_uart, int *p_gpio_mode,  Boolean *p_data_flag, hx_sock_t *p_sock_info, Boolean *p_ap_mode,  U8 *p_gpio1_status);

Boolean hx_init_parameter_2();

void hx_update_echo_flag(Boolean *p_flag);
Boolean hx_init_echo_flag(Boolean *p_flag);
Boolean hx_init_smtlnk_flag(char *p_flag);
void hx_update_smtlnk_flag(char *p_flag);

#define HX_SMARTCONF_LINK	1			// smart conf ��ʽ����
#define HX_SOFTAP_LINK		2			// softap ��ʽ����
#define HX_AIRKISS_LINK		3			// Airkiss ��ʽ����

Boolean hx_update_ap_conf(U8 *encrypt_mode, char *ssid, char *key);
Boolean hx_get_ap_conf(U8 *encrypt_mode, char *ssid, int ssid_len, char *key, int key_len);

void hekr_update_conn_parameter(char *token, char *ctrlKey, char *bindKey);
void hekr_init_conn_parameter(char *token, char *ctrlKey, char *bindKey);

char * hx_get_ssid();
char * hx_get_passwd();

Boolean tuya_read_conf_help(int offset, void *ptr, int len);
Boolean tuya_save_conf_help(int offset, void *ptr, int len);

void hx_init_web_sec_info();
char * hx_get_web_username();
char * hx_get_web_password();
Boolean hx_update_web_username(char *name, char *pass);
int hx_get_uart_bdrate();
const char *hx_get_bdrate_string();
Boolean hx_update_uart_bdrate(int rate);

#ifdef __TUYA_CLOUD_SUPPORT__
Boolean tuya_read_conf();
Boolean tuya_save_conf();
#endif

/*��ȡ����ģʽ*/
extern char hx_get_smtlnk_flag(void);

/*
*startΪ���ݶ�д����ʼλ��,Ϊһ���ƫ��
*
*������������ÿ4KΪһ����λ��������������д�ģ��ʵ���д��λ����������˵�1��4k����������2��4k�ж�д���Դ�����
*Ϊʵ�������Ķ�д��ʽ�����ṩһͳһ�ӿڣ����µ���������������˼·����
*a. ͨ��start����ȡ���ڵڼ���4K�� 
*b. ͨ���ڵڼ���4k�У��ɻ�ȡ�����д�ľ�����ʼλ�ã�ͬʱ�����ɻ�ȡ���ڼ���4k��ƫ�Ʋ�ֵ
*c. Ϊ��֤��ȷ����������ص��ж�
*
*�ر�ע��: Ӧ��ģ���ڶ����������ļ���flash�еĴ��ʱ��ע�������屣֤����1��4k�ڣ����2��4K��
*/
extern BOOL conf_read_help(U32 start, void *ptr, int len);
extern BOOL conf_save_help(U32 start, void *ptr, int len);

#endif

