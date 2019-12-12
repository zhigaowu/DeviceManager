
#include "OnvifDeviceProxy.h"

#include "stdsoap2.h"


OnvifDeviceProxy::OnvifDeviceProxy()
    : OnvifAuthProxy()
    , _capcities()
    , _media()
{
}

OnvifDeviceProxy::OnvifDeviceProxy(const char* endpoint, const char* username, const char* password, int connect_timeout, int send_timeout, int recv_timeout)
    : OnvifAuthProxy(endpoint, username, password, connect_timeout, send_timeout, recv_timeout)
    , _capcities()
    , _media()
{
}

OnvifDeviceProxy::~OnvifDeviceProxy()
{
}

int OnvifDeviceProxy::GetCapabilities(struct _tds__GetCapabilitiesResponse& capcities, enum tt__CapabilityCategory category)
{
    struct _tds__GetCapabilities req;
    enum tt__CapabilityCategory categories[1] = { category };

    req.__sizeCategory = sizeof(categories)/sizeof(tt__CapabilityCategory);
    req.Category = categories;

    addUsernameTokenDigest(_username, _password);
    
    int res = soap_call___tds__GetCapabilities(_proxy, _endpoint, "http://www.onvif.org/ver10/device/wsdl/GetCapabilities", &req, &_capcities);
    if (SOAP_OK == res)
    {
        capcities = _capcities;
    }
    return res;
}

int OnvifDeviceProxy::GetMediaProfiles(struct _trt__GetProfilesResponse& profiles)
{
    if (_capcities.Capabilities)
    {
        struct _trt__GetProfiles req;

        addUsernameTokenDigest(_username, _password);

        int res = soap_call___trt__GetProfiles(_proxy, _capcities.Capabilities->Media->XAddr, "http://www.onvif.org/ver10/media/wsdlGetProfile/", &req, &_media);
        if (SOAP_OK == res)
        {
            profiles = _media;
        }
        return res;
    } 
    else
    {
        return SOAP_CLI_FAULT;
    }
}

int OnvifDeviceProxy::GetMediaUri(struct _trt__GetStreamUriResponse& uri, enum tt__TransportProtocol protocol)
{
    if (_capcities.Capabilities && _media.Profiles)
    {
        struct tt__Transport Transport;
        Transport.Protocol = protocol;
        Transport.Tunnel = 0;

        struct tt__StreamSetup StreamSetup;
        StreamSetup.Stream = tt__StreamType__RTP_Unicast;
        StreamSetup.Transport = &Transport;
        StreamSetup.__size = 1;
        StreamSetup.__any = NULL;
        StreamSetup.__anyAttribute = NULL;

        struct _trt__GetStreamUri req;
        req.StreamSetup = &StreamSetup;
        req.ProfileToken = _media.Profiles->token;

        addUsernameTokenDigest(_username, _password);

        return soap_call___trt__GetStreamUri(_proxy, _capcities.Capabilities->Media->XAddr, "http://www.onvif.org/ver10/media/wsdl/GetStreamUri", &req, &uri);
    }
    else
    {
        return SOAP_CLI_FAULT;
    }
}

int OnvifDeviceProxy::GetDeviceInformation(struct _tds__GetDeviceInformationResponse& deviceInfomation)
{
    struct _tds__GetDeviceInformation req;

    addUsernameTokenDigest(_username, _password);

    return soap_call___tds__GetDeviceInformation(_proxy, _endpoint, "http://www.onvif.org/ver10/device/wsdl/GetDeviceInformation", &req, &deviceInfomation);
}


