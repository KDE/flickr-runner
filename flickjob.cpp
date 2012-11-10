/******************************************************************************
 *  Copyright (C) 2012 by Shaun Reich <shaun.reich@blue-systems.com           *
 *                                                                            *
 *  This library is free software; you can redistribute it and/or modify      *
 *  it under the terms of the GNU Lesser General Public License as published  *
 *  by the Free Software Foundation; either version 2 of the License or (at   *
 *  your option) any later version.                                           *
 *                                                                            *
 *  This library is distributed in the hope that it will be useful,           *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU         *
 *  Library General Public License for more details.                          *
 *                                                                            *
 *  You should have received a copy of the GNU Lesser General Public License  *
 *  along with this library; see the file COPYING.LIB.                        *
 *  If not, see <http://www.gnu.org/licenses/>.                               *
 *****************************************************************************/

#include "flickjob.h"
#include <QtCore/qurl.h>

#include <KDebug>
#include <KToolInvocation>

#include <QNetworkAccessManager>
#include <QNetworkReply>

FlickJob::FlickJob(const QString& term, bool singleRunnerMode)
  : QObject()
  , m_manager(0)
{
    m_manager = new QNetworkAccessManager(this);

    int resultCount = singleRunnerMode ? 30 : 10;
    QUrl url("http://api.flickr.com/services/rest/");
    url.addQueryItem("method", "flickr.photos.search");
    url.addQueryItem("api_key", "37e8cfe947339a756f5045b9b0d445cd");
    url.addQueryItem("tags", term);
    url.addQueryItem("format", "json");
    url.addQueryItem("nojsoncallback","1");
    url.addQueryItem("per_page", QString::number(resultCount));
    url.addQueryItem("page", QString::number(1));
    url.addQueryItem("sort","relevance");

    QNetworkRequest request = QNetworkRequest(url);
    m_manager->get(request);
}

void FlickJob::jobCompleted(QNetworkReply* reply)
{
    m_data = reply->readAll();

    emit finished();
}

QByteArray FlickJob::data()
{
    return m_data;
}


#include "flickjob.moc"
