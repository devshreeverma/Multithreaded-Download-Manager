#include <iostream>
#include "HTTPClient.h"
#include "DownloadTask.h" 
int main()
{
    HTTPClient client;

    std::string url;

    std::cout << "Enter URL: ";
    std::cin >> url;

    if(!client.fetchHeaders(url))
    {
        std::cout << "Failed to fetch headers.\n";
        return 1;
    }

    std::cout << "Status Code: "
            << client.getStatusCode()
            << '\n';

    std::cout << "Content Length: "
            << client.getContentLength()
            << '\n';

    std::cout << "Content Type: "
            << client.getContentType()
            << '\n';

    std::cout << "Supports Range Requests: "
            << (client.supportsRangeRequests() ? "YES" : "NO")
            << '\n';
    std::string filename;

    std::cout << "\nOutput file: ";
    std::cin >> filename;
    if(!client.supportsRangeRequests())
    {
        std::cout << "Server does not support range requests.\n";
        return 1;
    }
    DownloadTask task(
        url,
        filename,
        0,  
        999999);

    if(task.execute())
    {
        std::cout << "Task completed!\n";
    }
    else
    {
        std::cout << "Task failed!\n";
    }

    return 0;
}