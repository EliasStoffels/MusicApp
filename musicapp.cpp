#include "musicapp.h"
#include "./ui_musicapp.h"
#include "QMessageBox"
#include "ytdlpinterface.h"
#include "medialibrarymanager.h"
#include <QStringListModel>
#include "playlistplayer.h"

MusicApp::MusicApp(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MusicApp)
{
    //initialize variabals
    ui->setupUi(this);
    m_PlaylistPlayer = new PlaylistPlayer(ui->SongListView);
    m_MediaLibraryManager = new MediaLibraryManager;
    m_YTInterface = new YTDLPInterface;

    //connect functionality
    connect(this->ui->PlayButton,&QPushButton::clicked,this,&MusicApp::Play);
    connect(this->ui->DownloadButton, &QPushButton::clicked,this,&MusicApp::Download);
    connect(this->ui->PauseButton, &QPushButton::clicked,this,&MusicApp::Pause);
    connect(this->ui->PreviousButton,&QPushButton::clicked,this,&MusicApp::Previous);
    connect(this->ui->NextButton,&QPushButton::clicked,this,&MusicApp::Next);
    connect(this->ui->MainTabWidget,&QTabWidget::currentChanged,this,&MusicApp::OnTabChanged);
    connect(this->ui->VolumeSlider,&QSlider::valueChanged,this,&MusicApp::SetVolume);
    connect(this->ui->TimelineSlider,&QSlider::sliderReleased,this,&MusicApp::OnTimelineReleased);

    //initialize play tab
    ui->SongListView->setModel(m_MediaLibraryManager->GetSongModel());
}

MusicApp::~MusicApp()
{
    delete m_YTInterface;
    delete m_MediaLibraryManager;
    delete m_PlaylistPlayer;
    delete ui;
}

void MusicApp::Play()
{
    m_PlaylistPlayer->Play();
}

void MusicApp::Pause()
{
    m_PlaylistPlayer->Pause();
}

void MusicApp::Previous()
{
    m_PlaylistPlayer->Previous();
}

void MusicApp::Next()
{
    m_PlaylistPlayer->Next();
}

void MusicApp::SetVolume(int volume)
{
    m_PlaylistPlayer->SetVolume(volume);
}

void MusicApp::Download()
{
    QString url = ui->LinkInput->toPlainText();
    QString command = "YTDLP\\yt-dlp.exe \""+ url + "\"";

    system(command.toUtf8().constData());
}

void MusicApp::OnTimelineReleased()
{
    m_PlaylistPlayer->OnTimelineReleased(ui->TimelineSlider->value());
}

void MusicApp::OnTabChanged(int idx)
{
    if(idx == PLAY_TAB_IDX)
    {
        ui->SongListView->setModel(m_MediaLibraryManager->GetSongModel());
    }
}

