#include "DownloadTask.h"

DownloadTask::DownloadTask(
    const std::string& url,
    const std::string& outputFile,
    long long startByte,
    long long endByte)
    : url(url),
      outputFile(outputFile),
      startByte(startByte),
      endByte(endByte)
{
}

bool DownloadTask::execute()
{
    return true;
}