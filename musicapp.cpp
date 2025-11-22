#include "musicapp.h"
#include "./ui_musicapp.h"
#include "QMessageBox"
#include "ytdlpinterface.h"
#include "medialibrarymanager.h"
#include <QStringListModel>
#include "playlistplayer.h"
#include <QProcess>

MusicApp::MusicApp(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MusicApp)
{
    //initialize UI
    ui->setupUi(this);

    //initialize variabals
    m_MediaLibraryManager = new MediaLibraryManager;
    ui->SongListView->setModel(m_MediaLibraryManager->GetSongModel());

    m_PlaylistPlayer = new PlaylistPlayer(ui->SongListView->model(),ui->SongListView->selectionModel());

    m_YTInterface = new YTDLPInterface;

    //connect functionality
    connect(this->ui->PlayButton,&QPushButton::clicked,this,&MusicApp::Play);
    connect(this->ui->DownloadButton, &QPushButton::clicked,this,&MusicApp::Download);
    connect(this->ui->PauseButton, &QPushButton::clicked,this,&MusicApp::Pause);
    connect(this->ui->PreviousButton,&QPushButton::clicked,this,&MusicApp::Previous);
    connect(this->ui->NextButton,&QPushButton::clicked,this,&MusicApp::Next);
    connect(this->ui->SearchButton,&QPushButton::clicked,this,&MusicApp::Search);
    connect(this->ui->MainTabWidget,&QTabWidget::currentChanged,this,&MusicApp::OnTabChanged);
    connect(this->ui->VolumeSlider,&QSlider::valueChanged,this,&MusicApp::SetVolume);
    connect(this->ui->TimelineSlider,&QSlider::sliderReleased,this,&MusicApp::OnTimelineReleased);
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
    m_YTInterface->Download(ui->LinkInput->toPlainText(),"");
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

void MusicApp::Search()
{
    m_YTInterface->Search(ui->SearchInput->text());
}

