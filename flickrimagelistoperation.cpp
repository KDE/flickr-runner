#include "flickrimagelistoperation.h"

#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QDebug>

#include <qjson/parser.h>

FlickrImageListOperation::FlickrImageListOperation(const QString &keyword, int count) :
    m_keyword(keyword),
    m_requestedImages(count),
    m_page(),
    m_networkManager(new QNetworkAccessManager(this))
{
    downloadNextPage();
}

void FlickrImageListOperation::onListDownloaded()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());
    QByteArray jsonResponse = reply->readAll();

    QJson::Parser parser;
    QVariantMap  result = parser.parse(jsonResponse).toMap();
    QList<QVariant> photos = result["photos"].toMap()["photo"].toList();

    QList<FlickrItem> flickrPhotos;

    foreach (QVariant photo, photos) {
        QVariantMap map = photo.toMap();
        FlickrItem item(map["farm"].toString(), map["server"].toString(),map["id"].toString(),map["secret"].toString());
        flickrPhotos.append(item);
    }

    emit imagesAvailable(flickrPhotos);

    m_images.append(flickrPhotos);

    downloadNextPage();
}

void FlickrImageListOperation::downloadNextPage()
{
    if (m_page*30 < m_requestedImages) {
        QUrl url("http://api.flickr.com/services/rest/");
        url.addQueryItem("method", "flickr.photos.search");
        url.addQueryItem("api_key", "f934bf56f80a0268e2330030862b3c1d");
        url.addQueryItem("tags", m_keyword);
        url.addQueryItem("format", "json");
        url.addQueryItem("nojsoncallback","1");
        url.addQueryItem("per_page","30");
        url.addQueryItem("page", QString::number(m_page+1));
        url.addQueryItem("sort","relevance");
        connect(m_networkManager->get(QNetworkRequest(url)), SIGNAL(finished()), SLOT(onListDownloaded()));
        m_page++;
    }
    else {
        emit finished(this);
        deleteLater();
    }
}

QList<FlickrItem> FlickrImageListOperation::images()
{
    return m_images;
}
