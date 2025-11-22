#include "searchresult.h"
#include "./ui_SearchResult.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QPixmap>
#include <QLabel>
#include <QUrl>


SearchResult::SearchResult(QWidget *parent, YTSearchResult* resultData) :
    QWidget(parent),
    ui(new Ui::SearchResult)
{
    ui->setupUi(this);
    m_NetworkAccesManager = new QNetworkAccessManager;

    if(resultData)
    {
        ui->TitleText->setText(resultData->title);
        ui->UploaderText->setText(resultData->uploader);
        ui->DurationText->setText(QString::number(resultData->duration));
        m_Url = resultData->url;
        SetLabel(resultData->thumbnail);
    }
}

SearchResult::~SearchResult()
{
    delete m_NetworkAccesManager;
    delete ui;
}

QString SearchResult::GetUrl()
{
    return m_Url;
}

void SearchResult::SetLabel(const QString& imageUrl)
{
    if(!m_NetworkAccesManager)
        return;

    QNetworkReply* reply = m_NetworkAccesManager->get(QNetworkRequest(imageUrl));

    connect(reply, &QNetworkReply::finished, this, [=]() {
        if(reply->error() == QNetworkReply::NoError) {
            QByteArray data = reply->readAll();
            QPixmap pixmap;
            pixmap.loadFromData(data);
            ui->ThumbnailLabel->setPixmap(pixmap);
        } else {
            qDebug() << "Error downloading image:" << reply->errorString();
        }
        reply->deleteLater();
    });
}
