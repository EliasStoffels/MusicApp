#ifndef MEDIALIBRARYMANAGER_H
#define MEDIALIBRARYMANAGER_H
#include "QString"

class QStringListModel;
class MediaLibraryManager
{
    inline static const QString PLAYLIST_DIR = "";
    inline static const QString SONG_DIR = "AUDIO";
    QStringListModel* m_Model = nullptr;
public:
    MediaLibraryManager();
    ~MediaLibraryManager();

    QStringListModel* GetSongModel(const QString& playlistName = "");
};

#endif // MEDIALIBRARYMANAGER_H
