#ifndef _NGX_SSH_H_INCLUDED_
#define _NGX_SSH_H_INCLUDED_

#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_event.h>
#include <ngx_event_connect.h>

typedef struct {
    void                  **main_conf;
    void                  **srv_conf;
} ngx_ssh_conf_ctx_t;


typedef struct {
    ngx_sockaddr_t          sockaddr;
    socklen_t               socklen;

    /* server ctx */
    ngx_ssh_conf_ctx_t    *ctx;

    unsigned                bind:1;
    unsigned                wildcard:1;
    unsigned                ssl:1;
    unsigned                so_keepalive:2;
#if (NGX_HAVE_KEEPALIVE_TUNABLE)
    int                     tcp_keepidle;
    int                     tcp_keepintvl;
    int                     tcp_keepcnt;
#endif
    int                     backlog;
    int                     rcvbuf;
    int                     sndbuf;
} ngx_ssh_listen_t;


typedef struct {
    ngx_ssh_conf_ctx_t    *ctx;
    ngx_str_t               addr_text;
    ngx_uint_t              ssl;    /* unsigned   ssl:1; */
} ngx_ssh_addr_conf_t;

typedef struct {
    in_addr_t               addr;
    ngx_ssh_addr_conf_t    conf;
} ngx_ssh_in_addr_t;


typedef struct {
    /* ngx_ssh_in_addr_t or ngx_ssh_in6_addr_t */
    void                   *addrs;
    ngx_uint_t              naddrs;
} ngx_ssh_port_t;


typedef struct {
    int                     family;
    in_port_t               port;
    ngx_array_t             addrs;       /* array of ngx_ssh_conf_addr_t */
} ngx_ssh_conf_port_t;


typedef struct {
    ngx_ssh_listen_t       opt;
} ngx_ssh_conf_addr_t;


typedef struct {
    ngx_array_t             servers;     /* ngx_ssh_core_srv_conf_t */
    ngx_array_t             listen;      /* ngx_ssh_listen_t */
} ngx_ssh_core_main_conf_t;

typedef struct {
    ngx_str_t              *client;
    ngx_ssh_session_t     *session;
} ngx_ssh_log_ctx_t;
