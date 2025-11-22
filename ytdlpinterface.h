#ifndef YTDLPINTERFACE_H
#define YTDLPINTERFACE_H
#include "QString"

struct YTDLPConfigs
{
    QString downloadDir; // -p "downloadDir"
    QString fileName; // -o "fileName"
    QString audioFormat; // --audio-format "audioFormat"
};

struct YTSearchResult {
    YTSearchResult(const QString& titleStr, const QString& urlStr, const QString& thumbnailStr, const QString& uploaderStr, const double& durationD)
        : title(titleStr),url(urlStr),thumbnail(thumbnailStr), uploader(uploaderStr), duration(durationD) {}
    QString title;
    QString url;
    QString thumbnail;
    QString uploader;
    double duration;
};

class QListWidget;
class YTDLPInterface
{
    // config keys
    inline const static QString DOWNLOAD_DIR_KEY = "-P ";
    inline const static QString FILENAME_KEY = "-O ";
    inline const static QString AUDIO_FORMAT_KEY = "-O ";

    YTDLPConfigs m_Configs;
    void ReadConfigs();
    void WriteConfigs();
public:
    YTDLPInterface();
    ~YTDLPInterface();
    void Download(const QString& url, const QString& name);
    void SetDownloadDir(const QString& dir);
    void SetFileName(const QString& name);
    void SetAudioFormat(const QString& format);
    QVector<YTSearchResult> Search(const QString& queary);
};

#endif // YTDLPINTERFACE_H
