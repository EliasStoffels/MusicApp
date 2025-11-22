#ifndef YTDLPINTERFACE_H
#define YTDLPINTERFACE_H
#include "QString"

struct YTDLPConfigs
{
    QString downloadDir; // -p "downloadDir"
    QString fileName; // -o "fileName"
    QString audioFormat; // --audio-format "audioFormat"
};

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
    void Search(const QString& queary);
};

#endif // YTDLPINTERFACE_H
