#ifndef PLAYLISTPLAYER_H
#define PLAYLISTPLAYER_H


class QMediaPlayer;
class QAudioOutput;
class QAbstractItemModel;
class QItemSelectionModel;
class PlaylistPlayer
{
    QMediaPlayer* m_Player;
    QAudioOutput* m_Output;
    QAbstractItemModel* m_Model;
    QItemSelectionModel* m_Selection;

    bool m_IsPaused = false;
public:
    PlaylistPlayer(QAbstractItemModel* model, QItemSelectionModel* selection);
    ~PlaylistPlayer();

    void SetPlaylist(QAbstractItemModel* model, QItemSelectionModel* selection);
    void Play();
    void Pause();
    void Previous();
    void Next();
    void SetVolume(int volume);

    void OnTimelineReleased(int volume);
};

#endif // PLAYLISTPLAYER_H
