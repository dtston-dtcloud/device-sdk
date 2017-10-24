
/*net.c��ͷ�ļ�*/

#ifndef __NET_H_H__
#define __NET_H_H__

#include "uart_cmd.h"

#define MAX_NET_LINE_NR	HX_SOCKET_NUM			// һ������һ������


typedef void (*net_handle_rcv_cb)(net_line_t *pnet);

typedef enum 
{
	NET_SEND_OK = 0,
	NET_SEND_NO_LINE,
	NET_SEND_FAIL,
	NET_SEND_INVLIAD_PARAM
} net_line_send_status_t;


extern void init_net_buff();
extern net_line_t* get_net_line(int sock);
extern void net_send_tx_queue(int sock, int resend, tcp_send_cb fn);
extern void net_tcp_send_cb(int ocket, char *buf, int len, Boolean resend);
extern net_line_t* register_net_line(int sock);
extern Boolean unregister_net_line(int sock);
extern void tcp_send_ok_callback(int sock, tcp_send_cb fn);

/*������е�buf��Ϣ*/
extern void unregister_net_line_all(void);

/*��ѯ���е�net_line��������ն����еı���*/
extern void net_line_handle_rcv_pkt(net_handle_rcv_cb fn);
/*��ѯ���е�net_line�������ն�����û�нڵ�*/
extern Boolean net_line_rx_que_using(void);

Boolean net_has_active_conn();

net_line_send_status_t net_send_all_lines_packet(socket_send_fn_t fn_send, void *node);

typedef void (*fn_connect_ap_t)(void);

extern fn_connect_ap_t func_connect_ap;			// �������纯��
extern fn_connect_ap_t cb_reconnect_ap;		// ����֮����������AP����
extern fn_connect_ap_t cb_disconnect_ap;		// ������Ļص�

#endif

