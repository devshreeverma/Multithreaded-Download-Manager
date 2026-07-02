#include <iostream>
#include "HTTPClient.h"

int main()
{
    HTTPClient client;

    std::string url;

    std::cout << "Enter URL: ";
    std::cin >> url;

    if(client.fetchHeaders(url))
    {
        std::cout << "Status Code: "
                  << client.getStatusCode()
                  << std::endl;

        std::cout << "Content Length: "
                  << client.getContentLength()
                  << std::endl;
        std::cout << "Content Type: "
            << client.getContentType() << '\n';

        std::cout << "Supports Range Requests: "
                << (client.supportsRangeRequests() ? "YES" : "NO")
                << '\n';
    }



    return 0;
}