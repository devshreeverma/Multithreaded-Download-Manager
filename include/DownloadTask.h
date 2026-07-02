#ifndef DOWNLOADTASK_H
#define DOWNLOADTASK_H

#include <string>

class DownloadTask
{
public:
    DownloadTask(
        const std::string& url,
        const std::string& outputFile,
        long long startByte,
        long long endByte);

    bool execute();

private:
    std::string url;
    std::string outputFile;

    long long startByte;
    long long endByte;
};

#endif