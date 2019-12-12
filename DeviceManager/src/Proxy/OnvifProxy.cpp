
#include "OnvifProxy.h"

#include "wsdd.nsmap"
#include "soapClientLib.c"

OnvifProxy::OnvifProxy()
    : _header()
{
    _proxy = soap_new();
    soap_set_namespaces(_proxy, namespaces);
    _proxy->connect_timeout = 5;
    _proxy->send_timeout = 5;
    _proxy->recv_timeout = 5;

    memset(_endpoint, 0, sizeof(_endpoint));
    memset(_msgid, 0, sizeof(_msgid));

    soap_default_SOAP_ENV__Header(_proxy, &_header);
    _header.wsa5__MessageID = _msgid;

    _proxy->header = &_header;
}

OnvifProxy::OnvifProxy(const char* endpoint, int connect_timeout, int send_timeout, int recv_timeout)
    : _header()
{
    _proxy = soap_new();
    soap_set_namespaces(_proxy, namespaces);
    _proxy->connect_timeout = connect_timeout;
    _proxy->send_timeout = send_timeout;
    _proxy->recv_timeout = recv_timeout;

    memset(_endpoint, 0, sizeof(_endpoint));
    strncpy(_endpoint, endpoint, sizeof(_endpoint) - 1);

    memset(_msgid, 0, sizeof(_msgid));

    soap_default_SOAP_ENV__Header(_proxy, &_header);
    _header.wsa5__MessageID = _msgid;

    _proxy->header = &_header;
}

OnvifProxy::~OnvifProxy()
{
    soap_end(_proxy);
    soap_destroy(_proxy);
    soap_free(_proxy);
}

void OnvifProxy::UpdateHeaderMessageId()
{
    static int uid_head = 1000;
    
    memset(_msgid, 0, sizeof(_msgid));
    sprintf(_msgid, "urn:uuid:%ud68a-1dd2-11b2-a105-010203040506", uid_head++);

    if (uid_head >= 10000)
    {
        uid_head = 1000;
    }
}
