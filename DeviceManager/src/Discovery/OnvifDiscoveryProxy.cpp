
#include "OnvifDiscoveryProxy.h"
#include "stdsoap2.h"

static const char* const discovery_endpoint = "soap.udp://239.255.255.250:3702/";

OnvifDiscoveryProxy::OnvifDiscoveryProxy()
    : OnvifProxy()
{
    sprintf(_endpoint, discovery_endpoint);
}

OnvifDiscoveryProxy::OnvifDiscoveryProxy(int send_timeout, int recv_timeout)
    : OnvifProxy(discovery_endpoint, send_timeout, send_timeout, recv_timeout)
{
}

OnvifDiscoveryProxy::~OnvifDiscoveryProxy()
{
}

int OnvifDiscoveryProxy::BroadcastProbe()
{
    static char* was_To = "urn:schemas-xmlsoap-org:ws:2005:04:discovery";
    static char* was_Action = "http://schemas.xmlsoap.org/ws/2005/04/discovery/Probe";

    struct wsdd__ProbeType req;
    struct wsdd__ScopesType scopes;

    soap_default_wsdd__ScopesType(_proxy, &scopes);
    scopes.__item = "";
    soap_default_wsdd__ProbeType(_proxy, &req);
    req.Scopes = &scopes;
    req.Types = "tdn:NetworkVideoTransmitter";

    resetHeader();

    _header.wsa5__Action = was_To;
    _header.wsa5__To = was_Action;
    
    updateHeaderMessageId();

    return soap_send___wsdd__Probe(_proxy, _endpoint, NULL, &req);
}

int OnvifDiscoveryProxy::ReceiveProbeMatch(struct __wsdd__ProbeMatches& resp)
{
    return soap_recv___wsdd__ProbeMatches(_proxy, &resp);
}
