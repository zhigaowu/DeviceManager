#ifndef _ONVIF_AUTH_PROXY_HEADER_H_
#define _ONVIF_AUTH_PROXY_HEADER_H_

#include "OnvifProxy.h"

class OnvifAuthProxy : public OnvifProxy
{
public:
    OnvifAuthProxy();
    OnvifAuthProxy(const char* endpoint, const char* username, const char* password, int connect_timeout, int send_timeout, int recv_timeout);
    virtual ~OnvifAuthProxy();

protected:
    void addUsernameTokenDigest(const char* username, const char* password);

protected:
    char _username[32];
    char _password[32];

private:
    OnvifAuthProxy(const OnvifAuthProxy&);
    OnvifAuthProxy& operator=(const OnvifAuthProxy&);
};

#endif










