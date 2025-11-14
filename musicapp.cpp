#include "musicapp.h"
#include "./ui_musicapp.h"
#include "QMessageBox"
#include "QtMultimedia"
#include "ytdlpinterface.h"
#include "medialibrarymanager.h"
//#include <QStringListModel>

MusicApp::MusicApp(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MusicApp)
{
    ui->setupUi(this);
    m_MediaLibraryManager = new MediaLibraryManager;
    m_YTInterface = new YTDLPInterface;
    m_Player = new QMediaPlayer;
    m_Output = new QAudioOutput;
    connect(this->ui->PlayButton,&QPushButton::clicked,this,&MusicApp::Play);
    connect(this->ui->DownloadButton, &QPushButton::clicked,this,&MusicApp::Download);
    connect(this->ui->MainTabWidget,&QTabWidget::currentChanged,this,&MusicApp::OnTabChanged);


    //QStringListModel* model = new QStringListModel(this);
    //QStringList list;
    //QString text = ui->textEdit->toPlainText();
    //list << text;
    //model->setStringList(list);
    ui->SongListView->setModel(m_MediaLibraryManager->GetSongModel());

}

MusicApp::~MusicApp()
{
    delete m_Output;
    delete m_Player;
    delete m_YTInterface;
    delete m_MediaLibraryManager;
    delete ui;
}

void MusicApp::Play()
{
    qDebug() << "hello" ;
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

void MusicApp::OnTabChanged(int idx)
{
    if(idx == PLAY_TAB_IDX)
    {
        ui->SongListView->setModel(m_MediaLibraryManager->GetSongModel());
    }
}
