#include "medialibrarymanager.h"
#include <QStringListModel>
#include <QDir>

MediaLibraryManager::MediaLibraryManager()
{
    m_Model = new QStringListModel;
}

MediaLibraryManager::~MediaLibraryManager()
{
    delete m_Model;
}

QStringListModel* MediaLibraryManager::GetSongModel(const QString& playlistName)
{
    QDir directory(SONG_DIR);
    if(playlistName == "")
    {
        QStringList songs = directory.entryList(QStringList() << "*.mp3" << "*.WAV" << "*.webm",QDir::Files);

        m_Model->setStringList(songs);
        return m_Model;
    }

    return m_Model;
}
