#ifndef MUSICAPP_H
#define MUSICAPP_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MusicApp;
}
QT_END_NAMESPACE

class QMediaPlayer;
class QAudioOutput;
class MusicApp : public QMainWindow
{
    Q_OBJECT

public:
    MusicApp(QWidget *parent = nullptr);
    ~MusicApp();

private:
    void Play();
    void Download();

    Ui::MusicApp *ui;
    QMediaPlayer* m_Player;
    QAudioOutput* m_Output;
};
#endif // MUSICAPP_H
