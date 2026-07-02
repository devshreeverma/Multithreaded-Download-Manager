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
    std::string filename;

    std::cout << "\nOutput file: ";
    std::cin >> filename;

    if(client.downloadFile(url, filename))
    {
        std::cout << "Download completed successfully!\n";
    }
    else
    {
        std::cout << "Download failed!\n";
    }



    return 0;
}