#include "ytdlpinterface.h"

YTDLPInterface::YTDLPInterface() {}

void YTDLPInterface::Download(const QString& url, const QString& name)
{
    QString command = "YTDLP\\yt-dlp.exe  \""+ url + "\"";

    system(command.toUtf8().constData());
}

void YTDLPInterface::Play(const QString& name)
{

}
