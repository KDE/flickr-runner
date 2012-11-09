#ifndef FILTEREDIMAGEOPERATION_H
#define FILTEREDIMAGEOPERATION_H

#include <QObject>
#include "flickritem.h"

class QNetworkAccessManager;

/** Fetches a list of images from flickr */
class FlickrImageListOperation : public QObject
{
    Q_OBJECT
public:
    explicit FlickrImageListOperation(const QString &keyword, int requestedImages = 30);
    QList<FlickrItem> images();

signals:
    void finished(FlickrImageListOperation*);
    void imagesAvailable(const QList<FlickrItem> &items);

public slots:

private slots:
    void onListDownloaded();



private:
    void downloadNextPage();
    QString m_keyword;
    int m_requestedImages;
    int m_page;
    QNetworkAccessManager* m_networkManager;
    QList<FlickrItem> m_images;
};

#endif // FILTEREDIMAGEOPERATION_H
