/*
 * tcp_server.h
 *
 *  Created on: Feb 11, 2018
 *      Author: chenm
 */

#ifndef TCP_SERVER_H_
#define TCP_SERVER_H_

#include <stdint.h>
#include "lwip/opt.h"
#include "lwip/err.h"
#include "lwip/pbuf.h"
#include "lwip/debug.h"
#include "lwip/stats.h"
#include "lwip/tcp.h"
#include "lwip/memp.h"
#include "lwip/mem.h"
//////////////////////////////////////////////////////////////////////////////////

#define TCP_SERVER_RX_BUFSIZE   2000    //定义tcp server最大接收数据长度
#define TCP_SERVER_PORT         8088    //定义tcp server的端口

//tcp服务器连接状态
enum tcp_server_states
{
    ES_TCPSERVER_NONE = 0,      //没有连接
    ES_TCPSERVER_ACCEPTED,      //有客户端连接上了
    ES_TCPSERVER_CLOSING,       //即将关闭连接
};
//LWIP回调函数使用的结构体
struct tcp_server_struct
{
    uint8_t state;               //当前连接状
    struct tcp_pcb *pcb;    //指向当前的pcb
    struct pbuf *p;         //指向接收/或传输的pbuf
};

void tcp_server_test(void);//TCP Server测试函数
err_t tcp_server_accept(void *arg,struct tcp_pcb *newpcb,err_t err);
err_t tcp_server_recv(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err);
void tcp_server_error(void *arg,err_t err);
err_t tcp_server_poll(void *arg, struct tcp_pcb *tpcb);
err_t tcp_server_sent(void *arg, struct tcp_pcb *tpcb, u16_t len);
void tcp_server_senddata(struct tcp_pcb *tpcb, struct tcp_server_struct *es);
void tcp_server_connection_close(struct tcp_pcb *tpcb, struct tcp_server_struct *es);
void tcp_server_remove_timewait(void);
void tcp_server_test(void);

#endif /* TCP_SERVER_H_ */
