
/*��������ƶ����ṩ����ؽӿ�*/
#ifndef _GIZ_EXTERN_H_
#define _GIZ_EXTERN_H_


#ifdef __cplusplus
extern "C"
{
#endif

#define GIZ_MQTT_KEEPALIVE_TIME	   30	/*mqtt�������ڣ���λΪ��*/


/*��ȡm2m port*/
extern int giz_get_m2mport(void);
/*��ȡdid,�����ص�ַ*/
extern char *giz_get_did(void);
/*��ȡssid*/
extern char *giz_get_wifi_ssid(void);
/*��ȡwifi key*/
extern char *giz_get_wifi_key(void);
/*���wifi���ã���ssid��key*/
extern void giz_clear_wifi_conf(void);
/*���ȫ�ֵ���Ϣ*/
extern void giz_clear_global_conf(void);

/*
*����������������ģʽ��������⼸��
*1. ���ȫ������
*2. ��������ģʽ
*3. �ٱ�������
*ͨ�������������豸�����󣬻����ָ��������ģʽ��
*/
extern void giz_only_set_confNet_conf(char confNetMode);







/*��ȡbActive�Ĳ�����Ϣ*/
extern BOOL giz_mqtt_get_var_active(void);
/*����bActive�Ĳ�����Ϣ*/
extern void giz_mqtt_set_var_active(BOOL set);
/*���ö��ĵ�topic-app2dev*/
extern void giz_mqtt_set_subTopic_app2dev(void);
/*����mqtt�������·�public��Ϣʱ�����д�����ȡ��Ϣ�����ڽ��ն�����*/
extern void giz_mqtt_event_public(void *pMessage);
/*�ڴ���������·���public��Ϣʱ������Ϣ���ն����У�ȡ��Ϣ�ڵ���д���*/
extern void giz_mqtt_client_public(void);
/*������Ϣ��������ƶԽ�ʱ���ж����Ϣ����ж���*/
extern void giz_mqtt_subscribe(void);


/*���ڳ�ʼ��*/
extern void giz_uart_init(void);
/*��uart���ڶ�����ȡbuf,��ʼ����giz���ڴ�������*/
extern void giz_parse_uart_rx_queue(void);


/*����������Ϣ*/
extern BOOL giz_read_conf(void);
/*��ȡ������Ϣ*/
extern BOOL giz_save_conf(void);

/*��������Ƶ���ز���ָ��*/
int giz_at_cmd_hadle(void *param);


/*---������豸ʵ�ֵĽӿڣ����豸��֧�ֿ�����Ψһ����---*/

/*
*�����豸���صĽӿڣ�TRUE - ����FALSE - ��
*��������������·�������ָ������ӿڣ������豸��ʵ�ָýӿ�
*/
extern void giz_key_switch_action(BOOL bon);

/*
*�����������Ĳ���
*����Ŀ��ذ��������仯������ô˽ӿڣ��Ա㱣����Ϣ����������״̬�ϱ�����������app
*/
extern void giz_switch_action_api(void);


/*���ÿ���״̬��status-0x01��ʾ����0x00��ʾ��, ״̬�����仯�����ϱ�״̬*/
extern void giz_timer_set_on_off_report(char status);


/*
*�ϱ����ݣ�רΪ�ⲿģ���ṩ�Ľӿ�,�ڴ˽ӿ��У���ȡ���õ����ݣ��翪�أ���ʱ�������ϱ���app����
*/
extern void giz_report_status_api(void);

/*
*�䳤�ֶ��ϱ����ݣ�רΪ�ⲿģ���ṩ�Ľӿ�,�ڴ˽ӿ��У���ȡ���õ����ݣ��翪�أ���ʱ�������ϱ���app����
*type��ʾ�ϱ���Щ�ֶ�,�緽־������GIZ_TIMER_REPORT_SWITCH֮�ඨ��
*/
extern void giz_report_unfix_status_api(int type);


/*���ӷ���tcpʧ�ܵĴ���ͳ��*/
extern void giz_add_send_tcp_fail_statistics(void);

/*Ϊ��֤���±���״̬һ�£����ϱ�����״̬��tcp���ķ���ʧ��ʱ������ô˽ӿ��ٴ��ϱ�״̬*/
extern void giz_timer_notify_report_status(void);


PROCESS_NAME(giz_cloud_mqtt_process);



#ifdef __cplusplus
}
#endif

#endif


