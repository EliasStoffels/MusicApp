#ifndef SEARCHRESULT_H
#define SEARCHRESULT_H

#include <QWidget>
#include "ytdlpinterface.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class SearchResult;
}
QT_END_NAMESPACE

class QNetworkAccessManager;
class SearchResult : public QWidget
{
    Q_OBJECT
public:
    explicit SearchResult(QWidget *parent = nullptr, YTSearchResult* resultData = nullptr);
    ~SearchResult();

    QString GetUrl();

private:
    QNetworkAccessManager* m_NetworkAccesManager = nullptr;
    Ui::SearchResult *ui = nullptr;
    QString m_Url;

    void SetLabel(const QString& imageUrl);

signals:
};

#endif // SEARCHRESULT_H
