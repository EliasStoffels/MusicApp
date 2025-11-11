#include "musicapp.h"
#include "./ui_musicapp.h"
#include "QMessageBox"
#include "QtMultimedia"

MusicApp::MusicApp(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MusicApp)
{
    ui->setupUi(this);
    m_Player = new QMediaPlayer;
    m_Output = new QAudioOutput;
    connect(this->ui->PlayButton,&QPushButton::clicked,this,&MusicApp::Play);
    connect(this->ui->DownloadButton, &QPushButton::clicked,this,&MusicApp::Download);
}

MusicApp::~MusicApp()
{
    delete ui;
}

void MusicApp::Play()
{
    m_Player->setAudioOutput(m_Output);
    m_Player->setSource(QUrl::fromLocalFile("Audio/Buzz2.mp3"));
    m_Output->setVolume(0.5);
    m_Player->play();
}

void MusicApp::Download()
{
    QString url = ui->LinkInput->toPlainText();
    QString command = "YTDLP\\yt-dlp.exe \""+ url + "\"";

    system(command.toUtf8().constData());
}
