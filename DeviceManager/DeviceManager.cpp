
#include "Discovery/OnvifDiscoveryProxy.h"
#include "Device/OnvifDeviceProxy.h"

#include <iostream>

void test_discovery()
{
    OnvifDiscoveryProxy proxy(5, 5);
    int res = proxy.BroadcastProbe();
    while (res == SOAP_OK)
    {
        struct __wsdd__ProbeMatches resp;
        res = proxy.ReceiveProbeMatch(resp);
        if (res == SOAP_OK)
        {
            if (resp.wsdd__ProbeMatches)
            {
                std::cout << resp.wsdd__ProbeMatches->ProbeMatch->XAddrs << std::endl;
            }
            else
            {
                std::cout << "invalid response" << std::endl;
            }
        }
    }

    std::cout << "test_discovery done: " << res << std::endl;
}

void test_device()
{
    OnvifDeviceProxy proxy("http://192.168.2.133/onvif/device_service http://[fe80::66db:8bff:fe0f:77ff]/onvif/device_service", "admin", "admin123", 5, 5, 5);

    struct _tds__GetCapabilitiesResponse capabilities;
    int res = proxy.GetCapabilities(capabilities, tt__CapabilityCategory__Media);
    if (0 == res)
    {
        struct _trt__GetProfilesResponse profiles;
        res = proxy.GetMediaProfiles(profiles);

        struct _trt__GetStreamUriResponse uri;
        res = proxy.GetMediaUri(uri, tt__TransportProtocol__RTSP);
        std::cout << "Media URI: " << uri.MediaUri->Uri << std::endl;
    }

    struct _tds__GetDeviceInformationResponse deviceInfomation;
    res = proxy.GetDeviceInformation(deviceInfomation);
    std::cout << "Get device information: " << deviceInfomation.Manufacturer << std::endl;

    std::cout << "test_device done: " << res << std::endl;
}

int main(int argc, char* argv[])
{
    //test_discovery();
    test_device();

    std::cin >> argc;

    return 0;
}

