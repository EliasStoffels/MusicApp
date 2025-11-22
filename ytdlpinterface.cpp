#include "ytdlpinterface.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QProcess>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QListWidget>

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
    QString command = "YTDLP\\yt-dlp.exe \""+ url + "\"";

    QProcess::startDetached("YTDLP/yt-dlp.exe", {url});
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

QVector<YTSearchResult> YTDLPInterface::Search(const QString& query)
{
    // make command
    QString ytDlpPath = "YTDLP/yt-dlp.exe";
    QStringList args;
    args << QString("ytsearch5:%1").arg(query)
         << "--skip-download"
         << "--flat-playlist"
         << "--dump-json";

    //execute command
    QProcess process;
    process.start(ytDlpPath, args);
    process.waitForFinished();

    QString output = process.readAllStandardOutput();
    QStringList lines = output.split('\n', Qt::SkipEmptyParts);

    QVector<YTSearchResult> results;
    for (const QString &line : lines) {
        QJsonDocument doc = QJsonDocument::fromJson(line.toUtf8());
        if (!doc.isNull() && doc.isObject()) {

            //get json data from result
            QJsonObject obj = doc.object();
            QString title = obj.value("title").toString();
            QString url = obj.value("webpage_url").toString();
            QJsonArray  thumbnailArr = obj.value("thumbnails").toArray();
            QString thumbnail;
            if (!thumbnailArr.isEmpty()) {
                thumbnail = thumbnailArr.first().toObject().value("url").toString();
            }
            QString uploader = obj.value("uploader").toString();
            double duration = obj.value("duration").toDouble();

            results.emplace_back(title,url,thumbnail,uploader,duration);
        }
    }

    return results;
}
