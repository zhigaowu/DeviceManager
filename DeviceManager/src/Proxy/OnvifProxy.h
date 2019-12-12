#ifndef _ONVIF_PROXY_HEADER_H_
#define _ONVIF_PROXY_HEADER_H_

#include "soapH.h"

class OnvifProxy
{
public:
    OnvifProxy();
    OnvifProxy(const char* endpoint, int connect_timeout, int send_timeout, int recv_timeout);
    virtual ~OnvifProxy();

protected:
    void resetHeader();
    void updateHeaderMessageId();

protected:
    struct SOAP_ENV__Header _header;
    struct soap* _proxy;

protected:
    char _endpoint[512];

protected:
    char _msgid[128];

private:
    OnvifProxy(const OnvifProxy&);
    OnvifProxy& operator=(const OnvifProxy&);
};

#endif










