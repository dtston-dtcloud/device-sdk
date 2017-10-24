#ifndef __MQTT_H__
#define __MQTT_H__

#include "espconn.h"

#define DT_TEST_SERVER

extern uint8_t dt_ping_lose_count;    //mqtt������������
extern char forbid_search_flag;

enum mqtt_status
{
	MQTT_FAIL=0,	        //mqttʧ��
	MQTT_SUCCESS,	        //mqtt���ⶩ�ĳɹ�
	MQTT_CONNECT_FAIL,      //mqtt��������ʧ��
	MQTT_SUBSCRIBE_FAIL,    //mqtt��������ʧ��
}dt_mqtt_status;



struct mqtt_subscribe{
	uint8_t get_subscribe_data_flag;	//���ĵ������յ����ݱ�ʶ��
	uint8_t uart_len;					//���ĵ������յ������ݽ�����Ĵ������ݳ���
	uint8_t uart_data_array[255];		//���ĵ������յ������ݽ�����Ĵ�����������
};
struct mqtt_subscribe dt_mqtt_subscribe;



/********************************************************/
/*���ܣ�ģ���Զ����������Ʒ�����*/
/*���������product_type_value ---- ��Ʒ�����������ò�����˾�ṩ*/
/*���أ���*/
/*ע:���øú���֮ǰ����������·�����������л����� ����dt_mqtt_status=1��*/
/********************************************************/
void ICACHE_FLASH_ATTR dt_remote_control_init(uint16_t product_type_value);


/********************************************************/
/*���ܣ�Զ�̷�������*/
/*���������char *uart_data ------------- �������ݣ��ַ�����ʽ��*/
/*���أ���*/
/*ע:���øú���֮ǰ����������·�����������л����� ����dt_mqtt_status=1��*/
/********************************************************/
void ICACHE_FLASH_ATTR dt_remote_send_data(char *uart_data);


#endif
