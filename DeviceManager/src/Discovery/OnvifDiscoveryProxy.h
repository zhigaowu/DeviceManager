#ifndef _ONVIF_DISCOVERY_PROXY_HEADER_H_
#define _ONVIF_DISCOVERY_PROXY_HEADER_H_

#include "Proxy/OnvifProxy.h"

class OnvifDiscoveryProxy : virtual public OnvifProxy
{
public:
    OnvifDiscoveryProxy();
    OnvifDiscoveryProxy(int send_timeout, int recv_timeout);
    ~OnvifDiscoveryProxy();

    int BroadcastProbe();
    int ReceiveProbeMatch(struct __wsdd__ProbeMatches& resp);

private:
    OnvifDiscoveryProxy(const OnvifDiscoveryProxy&);
    OnvifDiscoveryProxy& operator=(const OnvifDiscoveryProxy&);
};

#endif










