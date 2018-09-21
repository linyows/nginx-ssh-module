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

#define NGX_SSH_MODULE         0x4C49414D     /* "SSH" */

#define NGX_SSH_MAIN_CONF      0x02000000
#define NGX_SSH_SRV_CONF       0x04000000


#define NGX_SSH_MAIN_CONF_OFFSET  offsetof(ngx_ssh_conf_ctx_t, main_conf)
#define NGX_SSH_SRV_CONF_OFFSET   offsetof(ngx_ssh_conf_ctx_t, srv_conf)


#define ngx_ssh_get_module_ctx(s, module)     (s)->ctx[module.ctx_index]
#define ngx_ssh_set_ctx(s, c, module)         s->ctx[module.ctx_index] = c;
#define ngx_ssh_delete_ctx(s, module)         s->ctx[module.ctx_index] = NULL;


#define ngx_ssh_get_module_main_conf(s, module)                             \
    (s)->main_conf[module.ctx_index]
#define ngx_ssh_get_module_srv_conf(s, module)  (s)->srv_conf[module.ctx_index]

#define ngx_ssh_conf_get_module_main_conf(cf, module)                       \
    ((ngx_ssh_conf_ctx_t *) cf->ctx)->main_conf[module.ctx_index]
#define ngx_ssh_conf_get_module_srv_conf(cf, module)                        \
    ((ngx_ssh_conf_ctx_t *) cf->ctx)->srv_conf[module.ctx_index]


void ngx_ssh_init_connection(ngx_connection_t *c);

ngx_int_t ngx_ssh_salt(ngx_ssh_session_t *s, ngx_connection_t *c,
    ngx_ssh_core_srv_conf_t *cscf);
ngx_int_t ngx_ssh_auth_login_username(ngx_ssh_session_t *s,
    ngx_connection_t *c, ngx_uint_t n);
ngx_int_t ngx_ssh_auth_login_password(ngx_ssh_session_t *s,
    ngx_connection_t *c);
ngx_int_t ngx_ssh_auth_cram_md5_salt(ngx_ssh_session_t *s,
    ngx_connection_t *c, char *prefix, size_t len);
ngx_int_t ngx_ssh_auth_cram_md5(ngx_ssh_session_t *s, ngx_connection_t *c);
ngx_int_t ngx_ssh_auth_external(ngx_ssh_session_t *s, ngx_connection_t *c,
    ngx_uint_t n);
ngx_int_t ngx_ssh_auth_parse(ngx_ssh_session_t *s, ngx_connection_t *c);

void ngx_ssh_send(ngx_event_t *wev);
ngx_int_t ngx_ssh_read_command(ngx_ssh_session_t *s, ngx_connection_t *c);
void ngx_ssh_auth(ngx_ssh_session_t *s, ngx_connection_t *c);
void ngx_ssh_close_connection(ngx_connection_t *c);
void ngx_ssh_session_internal_server_error(ngx_ssh_session_t *s);
u_char *ngx_ssh_log_error(ngx_log_t *log, u_char *buf, size_t len);


char *ngx_ssh_capabilities(ngx_conf_t *cf, ngx_command_t *cmd, void *conf);


/* STUB */
void ngx_ssh_proxy_init(ngx_ssh_session_t *s, ngx_addr_t *peer);
void ngx_ssh_auth_http_init(ngx_ssh_session_t *s);
/**/


extern ngx_uint_t    ngx_ssh_max_module;
extern ngx_module_t  ngx_ssh_core_module;


#endif /* _NGX_SSH_H_INCLUDED_ */
