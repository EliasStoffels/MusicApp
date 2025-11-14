#include "ytdlpinterface.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

YTDLPInterface::YTDLPInterface()
{
    ReadConfigs();
}

YTDLPInterface::~YTDLPInterface()
{
    WriteConfigs();
}

void YTDLPInterface::ReadConfigs()
{
   QFile configFile("YTDLP/yt-dlp.conf");
    if (!configFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&configFile);
    while (!in.atEnd()) {
        QString line = in.readLine();
        if(line.contains(DOWNLOAD_DIR_KEY))
        {
            m_Configs.downloadDir = line.mid(DOWNLOAD_DIR_KEY.length());
        }
        else if(line.contains(FILENAME_KEY))
        {
            m_Configs.fileName = line.mid(FILENAME_KEY.length());
        }
        else if(line.contains(AUDIO_FORMAT_KEY))
        {
            m_Configs.fileName = line.mid(AUDIO_FORMAT_KEY.length());
        }
    }
}

void YTDLPInterface::WriteConfigs()
{
    QFile configFile("YTDLP/yt-dlp.conf");
    if (!configFile.open(QIODevice::WriteOnly  | QIODevice::Text))
        return;

    QTextStream out(&configFile);
    if(!m_Configs.downloadDir.isEmpty())
        out << DOWNLOAD_DIR_KEY << m_Configs.downloadDir << "\n";

    if(!m_Configs.fileName.isEmpty())
        out << FILENAME_KEY << m_Configs.fileName << "\n";

    if(!m_Configs.audioFormat.isEmpty())
        out << AUDIO_FORMAT_KEY << m_Configs.audioFormat << "\n";
}

void YTDLPInterface::Download(const QString& url, const QString& name)
{
    QString command = "YTDLP\\yt-dlp.exe  \""+ url + "\"";

    system(command.toUtf8().constData());
}

void YTDLPInterface::SetDownloadDir(const QString& dir)
{
    m_Configs.downloadDir = dir;
}

void YTDLPInterface::SetFileName(const QString& name)
{
    m_Configs.fileName = name;
}

void YTDLPInterface::SetAudioFormat(const QString& format)
{
    m_Configs.audioFormat = format;
}
