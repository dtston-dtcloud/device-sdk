
/*atcmd_mqtt.c��ͷ�ļ�*/
#ifndef _ATCMD_MQTT_H_
#define _ATCMD_MQTT_H_


#ifdef __cplusplus
extern "C"
{
#endif

#include "data_buff.h"

extern buff_queue_t ty_mqtt_tx_queue;
extern buff_queue_t ty_mqtt_rx_queue;

extern int AT_MQTT_INIT(stParam *param);
extern int AT_MQTT_AUTH(stParam *param);
extern int AT_MQTT_CONNECT(stParam *param);

/*���ö������⣬���������յ�����������ĸ������publish��Ϣ*/
extern int AT_MQTT_SUBSCRIBE(stParam *param);


/*
*�豸����publish����
*stParam�У�
*argv[0] - topic
*argv[1] - ���͵ı�������
*argv[2] - ���͵ı��ĳ��ȣ�ע���������ַ���������ʹ��ʱ����ת��Ϊ����
*/
extern int AT_MQTT_PUBLISH(stParam *param);


#ifdef __cplusplus
}
#endif

#endif


