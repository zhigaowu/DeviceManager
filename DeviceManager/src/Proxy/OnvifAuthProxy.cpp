
#include "OnvifAuthProxy.h"

#include "gsoap/wsseapi.h"

OnvifAuthProxy::OnvifAuthProxy()
    : OnvifProxy()
{}

OnvifAuthProxy::OnvifAuthProxy(const char* endpoint, const char* username, const char* password, int connect_timeout, int send_timeout, int recv_timeout)
    : OnvifProxy(endpoint, connect_timeout, send_timeout, recv_timeout)
{
    if (username)
    {
        strncpy(_username, username, sizeof(_username) - 1);
    }
    if (password)
    {
        strncpy(_password, password, sizeof(_password) - 1);
    }
}

OnvifAuthProxy::~OnvifAuthProxy()
{
}

void OnvifAuthProxy::addUsernameTokenDigest(const char* username, const char* password)
{
    soap_wsse_add_UsernameTokenDigest(_proxy, "user", username, password);
}

