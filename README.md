Nginx SSH module
==

This ssh module for nginx.

Usage
--

```
ssh {
  proxy on;
  proxy_pass_error_message on;

  auth_http 127.0.0.1:58080/ssh_auth;

  server {
    listen 8022;
  }
}
```
