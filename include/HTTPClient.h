#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H

#include <string>
#include <curl/curl.h>

class HTTPClient
{
public:
    HTTPClient() = default;
    ~HTTPClient() = default;

    bool fetchHeaders(const std::string& url);

    long getStatusCode() const;
    curl_off_t getContentLength() const;
    std::string getContentType() const;
    bool supportsRangeRequests() const;

private:
    long statusCode = 0;
    curl_off_t contentLength = 0;
    std::string contentType;
    bool supportsRange = false;

    static size_t headerCallback(
        char* buffer,
        size_t size,
        size_t nitems,
        void* userdata);

    void parseHeader(const std::string& header);
};

#endif