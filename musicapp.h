#ifndef MUSICAPP_H
#define MUSICAPP_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MusicApp;
}
QT_END_NAMESPACE

class PlaylistPlayer;
class MediaLibraryManager;
class YTDLPInterface;
class MusicApp : public QMainWindow
{
    Q_OBJECT

public:
    MusicApp(QWidget *parent = nullptr);
    ~MusicApp();

private:
    static constexpr int PLAY_TAB_IDX = 0;
    static constexpr int DOWNLOAD_TAB_IDX = 1;
    static constexpr int BROWSA_TAB_IDX = 2;

    void Play();
    void Pause();
    void Previous();
    void Next();
    void Download();
    void SetVolume(int volume);
    void Search();

    void OnTimelineReleased();
    void OnTabChanged(int idx);

    Ui::MusicApp *ui;
    PlaylistPlayer* m_PlaylistPlayer;
    MediaLibraryManager* m_MediaLibraryManager;
    YTDLPInterface* m_YTInterface;
};
#endif // MUSICAPP_H
