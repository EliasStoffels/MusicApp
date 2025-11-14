#ifndef PLAYLISTPLAYER_H
#define PLAYLISTPLAYER_H


class QMediaPlayer;
class QAudioOutput;
class QListView;
class PlaylistPlayer
{
    QMediaPlayer* m_Player;
    QAudioOutput* m_Output;
    QListView* m_Playlist;

    bool m_IsPaused = false;
public:
    PlaylistPlayer(QListView* playlist);
    ~PlaylistPlayer();

    void Play();
    void Pause();
    void Previous();
    void Next();
    void SetVolume(int volume);

    void OnTimelineReleased(int volume);
};

#endif // PLAYLISTPLAYER_H
