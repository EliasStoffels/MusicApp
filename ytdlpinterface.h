#ifndef YTDLPINTERFACE_H
#define YTDLPINTERFACE_H
#include "QString"

struct YTDLPConfigs
{
    QString downloadDir; // -p "downloadDir"
    QString fileName; // -o "fileName"
};

class YTDLPInterface
{
    YTDLPConfigs m_Configs;
    void ReadConfigs();
    void WriteConfigs();
public:
    YTDLPInterface();
    ~YTDLPInterface();
    void Download(const QString& url, const QString& name);
    void Play(const QString& name);
};

#endif // YTDLPINTERFACE_H
