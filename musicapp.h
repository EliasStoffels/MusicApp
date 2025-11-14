#ifndef MUSICAPP_H
#define MUSICAPP_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MusicApp;
}
QT_END_NAMESPACE

class MediaLibraryManager;
class YTDLPInterface;
class QMediaPlayer;
class QAudioOutput;
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
    void Download();
    void OnTabChanged(int idx);

    Ui::MusicApp *ui;
    MediaLibraryManager* m_MediaLibraryManager;
    YTDLPInterface* m_YTInterface;
    QMediaPlayer* m_Player;
    QAudioOutput* m_Output;
};
#endif // MUSICAPP_H
