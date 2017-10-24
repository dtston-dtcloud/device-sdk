#ifndef _ESP_T_LIB_V1_H
#define _ESP_T_LIB_V1_H

#include "c_types.h"

#include "mem.h"
#include "ets_sys.h"
#include "osapi.h"

#include "user_interface.h"
#include "smartconfig.h"
#include <stdio.h>
#include "eagle_soc.h"

#include "espconn.h"



#define TEST_ENV
//#define FORMAL_ENV


typedef unsigned int  		dt_u32;
typedef unsigned short   	dt_u16;
typedef unsigned char       dt_u8;
typedef int                 dt_s32;
typedef short               dt_s16;
typedef char                dt_s8;
typedef void                dt_v;


typedef void (*user_recv_callback_t)(dt_u8 *data, dt_u16 len);
typedef void (*user_send_callback_t)(void);
typedef void (*user_disconnect_callback_t)(void);


typedef struct 
{
	user_recv_callback_t recv_callback;
	user_send_callback_t user_send_callback;
	user_disconnect_callback_t user_disconnect_callback;
}user_callback_t;

typedef struct 
{
	dt_u8  mac[6];
	dt_u8  ip[4];
	dt_u16 type_value;
}wifi_station_info_t;


/*func name:    dt_start_udp_server
**function:     start udp service
**param:        param1:wifi_station_info_t type pointer,The MAC address is an array of 6 bytes, 
**                     the IP address is an array of 4 bytes, the typevalue is assigned by the SHENZHIYUN, and each product corresponds to a product type
**return:       none
*/
/*������        :dt_start_udp_server
**����          :��UDP����
**����          :wifi_station_info_t ���͵�ָ�룬mac��ַΪ6�ֽ����飬IP��ַΪ4�ֽ����飬typevalue���������Ʒ���ģ�ÿһ����Ʒ��Ӧһ����Ʒ����
**����ֵ        :��
*/
void ICACHE_FLASH_ATTR dt_start_udp_server(wifi_station_info_t *wifi_staticon_infom);







/*func name:    dt_start_tcp_server
**function:     start tcp service
**param:        param1:user_callback_t type pointer,user can register recvcallback/disconnect callback/send callback,if you don't want to register,
**                     You can pass a NULL,However, if you do not register recv_callback, you will not receive data
**              param2:wifi_station_info_t type pointer,The MAC address is an array of 6 bytes, 
**                     the IP address is an array of 4 bytes, the typevalue is assigned by the deep wisdom cloud, and each product corresponds to a product type
**return:       1-Success,else-fail 
*/
/*������        :dt_start_tcp_server
**����          :��TCP����
**����          :1.user_callback_t ���͵�ָ�룬�û�����ע����ջص��������Ͽ����ӻص����������ͻص�����������㲻��ע�ᣬ����Դ���һ��NULL�����ǣ������ע��
**                  recv_callback,�����ղ���tcp������������
**               2.wifi_station_info_t ���͵�ָ�룬mac��ַΪ6�ֽ����飬IP��ַΪ4�ֽ����飬typevalue���������Ʒ���ģ�ÿһ����Ʒ��Ӧһ����Ʒ����
**return         1-�ɹ�  ��1-ʧ��
*/
dt_s32 ICACHE_FLASH_ATTR dt_start_tcp_server(user_callback_t *user_callback,wifi_station_info_t *wifi_station_infom);




/*func name:    dt_start_mqtt_server
**function:     start mqtt remote service MQTT is a remote data sending and receiving service, which is forwarded by the server
**param:        param1:user_callback_t type pointer,user can register recvcallback/disconnect callback/send callback,if you don't want to register,
**                     You can pass a NULL,However, if you do not register recv_callback, you will not receive data
**              param2:wifi_station_info_t type pointer,The MAC address is an array of 6 bytes, 
**                     the IP address is an array of 4 bytes, the typevalue is assigned by the deep wisdom cloud, and each product corresponds to a product type
**return:      1-Success,else-fail 

*/
/*������        :dt_start_mqtt_server
**����          :��MQTT����MQTT��Զ�������շ�����ͨ������������ת��
**����          :1.user_callback_t ���͵�ָ�룬�û�����ע����ջص��������Ͽ����ӻص����������ͻص�����������㲻��ע�ᣬ����Դ���һ��NULL�����ǣ������ע��
**                  recv_callback,�����ղ���MQTT������������
**               2.wifi_station_info_t ���͵�ָ�룬mac��ַΪ6�ֽ����飬IP��ַΪ4�ֽ����飬typevalue���������Ʒ���ģ�ÿһ����Ʒ��Ӧһ����Ʒ����
**����          -1-ʧ�ܣ�1-�ɹ�
*/
dt_s32 ICACHE_FLASH_ATTR dt_start_mqtt_server(user_callback_t *user_callback,wifi_station_info_t *wifi_station_infom);





/*func name:     check_wheather_connect_cloud
**function       Check whether the WiFi module is connected to the external network��If the connection is broken, there is a reconnection mechanism, 
**               do not need to repeat the call dt_start_mqtt_server
**param          none
**return         1-Success,else-fail    
*/

/*������:        check_wheather_connect_cloud
**����           ���WiFiģ����û����������(��mqtt����)�������;�ϵ����ӣ����������ƣ�����Ҫ�ظ�����dt_start_mqtt_server
**
**����           ��
**����ֵ         1-�ɹ�  ��1-ʧ��
*/
dt_s32 ICACHE_FLASH_ATTR check_wheather_connect_cloud(void);





/*func name:     dt_send_data_to_app_clound
**function       Check whether the WiFi module is connected to the external network��If the connection is broken, there is a reconnection mechanism, 
**               do not need to repeat the call dt_start_mqtt_server
**param          1.Data array pointer
**               2.Length of data to send
**               3.Need to send the destination: the default is 0, and sent to the APP and the background, when set to 1:
				   only the near field transmission, APP in the same LAN network can receive data, remote data can not receive,When set to 2, only remote transmission.
**return         1-Success (here refers to the success of the function call, the data sent to the success of the callback function to determine),else-fail    
*/

/*������:        dt_send_data_to_app_clound
**����           �������ݸ�APP�ͺ�̨��Զ�̿���ʱ��ֻ�к�̨�������ܽ������ݽ���
**
**����           1.��Ҫ���͵���������ָ��
**               2.��Ҫ���͵����ݳ���
**               3.��Ҫ���͵�Ŀ�ĵ�:Ĭ��Ϊ0��ͬʱ���͸�APP�ͺ�̨��������Ϊ1ʱ:ֻ���н������ͣ�APP��ͬһ�������������յ����ݣ�Զ���ղ������ݣ�
				   ������Ϊ2ʱ��ֻ����Զ�̷��͡�
**����ֵ         1-�ɹ�(����ָ�������óɹ������ݷ��ͳɹ���ȥ���ͻص����������ж�)  ��1-ʧ��
*/
dt_s32 ICACHE_FLASH_ATTR dt_send_data_to_app_clound(dt_u8 *data,dt_u16 data_len,dt_u8 flag);



#endif

