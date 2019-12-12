#ifndef _ONVIF_DEVICE_PROXY_HEADER_H_
#define _ONVIF_DEVICE_PROXY_HEADER_H_

#include "Proxy/OnvifAuthProxy.h"

class OnvifDeviceProxy : public OnvifAuthProxy
{
public:
    OnvifDeviceProxy();
    OnvifDeviceProxy(const char* endpoint, const char* username, const char* password, int connect_timeout, int send_timeout, int recv_timeout);
    ~OnvifDeviceProxy();

    int GetCapabilities(struct _tds__GetCapabilitiesResponse& capabilities, enum tt__CapabilityCategory category = tt__CapabilityCategory__All);

    int GetMediaProfiles(struct _trt__GetProfilesResponse& profiles);

    int GetMediaUri(struct _trt__GetStreamUriResponse& uri, enum tt__TransportProtocol protocol = tt__TransportProtocol__RTSP);

    int GetDeviceInformation(struct _tds__GetDeviceInformationResponse& deviceInfomation);

private:
    struct _tds__GetCapabilitiesResponse _capcities;
    struct _trt__GetProfilesResponse _media;

private:
    OnvifDeviceProxy(const OnvifDeviceProxy&);
    OnvifDeviceProxy& operator=(const OnvifDeviceProxy&);
};

#endif










