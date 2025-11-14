#include "playlistplayer.h"
#include <QtMultimedia>
#include <QListView>

PlaylistPlayer::PlaylistPlayer(QListView* playlist): m_Playlist(playlist)
{
    m_Player = new QMediaPlayer;
    m_Output = new QAudioOutput;
    m_Player->setAudioOutput(m_Output);
}

PlaylistPlayer::~PlaylistPlayer()
{
    delete m_Player;
    delete m_Output;
}

void PlaylistPlayer::Play()
{
    if(m_IsPaused)
    {
        m_Player->play();
        m_IsPaused = false;
        return;
    }

    QModelIndex index = m_Playlist->currentIndex();
    QString fileLoc = "Audio\\" + index.data(Qt::DisplayRole).toString();
    m_Player->setSource(QUrl::fromLocalFile(fileLoc));
    m_Player->play();
}

void PlaylistPlayer::Pause()
{
    if(m_Player->isPlaying())
    {
        m_Player->pause();
        m_IsPaused = true;
    }
}

void PlaylistPlayer::Previous()
{
    QModelIndex current = m_Playlist->currentIndex();
    int rowCount = m_Playlist->model()->rowCount();

    int prevRow = (current.row() - 1);
    if(prevRow < 0)
        prevRow = rowCount -1;

    QModelIndex prevIndex = m_Playlist->model()->index(prevRow, 0);
    m_Playlist->setCurrentIndex(prevIndex);
    m_Playlist->selectionModel()->select(prevIndex, QItemSelectionModel::ClearAndSelect);
    m_Playlist->scrollTo(prevIndex);

    m_IsPaused = false;
    Play();
}

void PlaylistPlayer::Next()
{
    QModelIndex current = m_Playlist->currentIndex();
    int rowCount = m_Playlist->model()->rowCount();

    int nextRow = (current.row() + 1) % rowCount;

    QModelIndex nextIndex = m_Playlist->model()->index(nextRow, 0);
    m_Playlist->setCurrentIndex(nextIndex);
    m_Playlist->selectionModel()->select(nextIndex, QItemSelectionModel::ClearAndSelect);
    m_Playlist->scrollTo(nextIndex);

    m_IsPaused = false;
    Play();
}

void PlaylistPlayer::SetVolume(int volume)
{
    //qDebug() << QString::number(volume);
    m_Output->setVolume(volume/100.f);
}

void PlaylistPlayer::OnTimelineReleased(int value)
{
    if(!m_Player->isPlaying())
        return;

    float percent = value/100.f;
    qint64 duration = m_Player->duration();

    m_Player->setPosition(duration * percent);
}
