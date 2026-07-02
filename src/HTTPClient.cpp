#include "HTTPClient.h"

#include <curl/curl.h>
#include <iostream>
size_t HTTPClient::headerCallback(
    char* buffer,
    size_t size,
    size_t nitems,
    void* userdata)
{
    size_t totalSize = size * nitems;

    HTTPClient* client =
        static_cast<HTTPClient*>(userdata);

    client->parseHeader(
        std::string(buffer, totalSize));

    return totalSize;
}
#include <algorithm>
#include <cctype>

void HTTPClient::parseHeader(const std::string& header)
{
    std::cout << header;

    size_t pos = header.find(':');

    // Skip status line like "HTTP/1.1 200 OK"
    if (pos == std::string::npos)
        return;

    std::string key = header.substr(0, pos);
    std::string value = header.substr(pos + 1);

    // Remove leading whitespace
    value.erase(0, value.find_first_not_of(" \t"));

    // Remove trailing CR/LF
    value.erase(value.find_last_not_of("\r\n") + 1);

    // Convert key to lowercase
    std::transform(key.begin(), key.end(), key.begin(),
                   [](unsigned char c)
                   {
                       return std::tolower(c);
                   });

    if (key == "content-type")
    {
        contentType = value;
    }
    else if (key == "content-length")
    {
        try
        {
            contentLength = std::stoll(value);
        }
        catch (...)
        {
            contentLength = -1;
        }
    }
    else if (key == "accept-ranges")
    {
        if (value == "bytes")
        {
            supportsRange = true;
        }
    }
}
bool HTTPClient::fetchHeaders(const std::string& url)
{
    contentType = "Unknown";
    supportsRange = false;
    contentLength = -1;
    statusCode = 0;
    CURL* curl = curl_easy_init();

    if (!curl)
    {
        std::cerr << "Failed to initialize CURL\n";
        return false;
    }
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_NOBODY, 1L);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(
        curl,
        CURLOPT_HEADERFUNCTION,
        headerCallback);

    curl_easy_setopt(
        curl,
        CURLOPT_HEADERDATA,
        this);
    CURLcode result = curl_easy_perform(curl);

    if(result != CURLE_OK)
    {
        std::cerr << curl_easy_strerror(result) << std::endl;
        curl_easy_cleanup(curl);
        return false;
    }
    curl_easy_getinfo(curl,
                      CURLINFO_RESPONSE_CODE,
                      &statusCode);
    curl_easy_getinfo(curl,
                      CURLINFO_CONTENT_LENGTH_DOWNLOAD_T,
                      &contentLength);
    curl_easy_cleanup(curl);

    return true;

}
long HTTPClient::getStatusCode() const
{
    return statusCode;
}

curl_off_t HTTPClient::getContentLength() const
{
    return contentLength;
}

std::string HTTPClient::getContentType() const
{
    return contentType;
}

bool HTTPClient::supportsRangeRequests() const
{
    return supportsRange;
}