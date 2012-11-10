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

#include "flickr.h"
#include "flickjob.h"
#include "imageiconengine.h"

#include <KDebug>
#include <KToolInvocation>
#include <KRun>

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QtCore/QTimer>
#include <QtCore/QWaitCondition>
#include <QtCore/QEventLoop>
#include <qfile.h>
#include <QtGui/QIcon>
#include <qpushbutton.h>
#include <qjson/parser.h>

Flickr::Flickr(QObject *parent, const QVariantList& args)
    : Plasma::AbstractRunner(parent, args)
    , m_thumbnailDownloader(0)
{
    Q_UNUSED(args);
    setObjectName(QLatin1String("Flickr"));
    setIgnoredTypes(Plasma::RunnerContext::FileSystem | Plasma::RunnerContext::Directory | Plasma::RunnerContext::NetworkLocation);

    addSyntax(Plasma::RunnerSyntax("images :q:", i18n("Lists the images matching the query, using Flickr search")));
    setSpeed(SlowSpeed);
    setPriority(LowPriority);
}

Flickr::~Flickr()
{
}

void Flickr::match(Plasma::RunnerContext &context)
{
    QString term = context.query();

    if (!term.startsWith("images ")) {
        return;
    } else {
        term = term.remove("images ");
    }

    if (term.length() < 3) {
        return;
    }

    if (!context.isValid()) {
        return;
    }

    QEventLoop loop;
    FlickJob flickJob(term, context.singleRunnerQueryMode());
    connect(&flickJob, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    parseJson(flickJob.data(), context);
}

void Flickr::run(const Plasma::RunnerContext &context, const Plasma::QueryMatch &match)
{
    KRun *opener = new KRun(match.data().toString(), 0);
    opener->setRunExecutables(false);
}

void Flickr::parseJson(const QByteArray& data, Plasma::RunnerContext &context)
{
    kDebug() << "FLICKR DATA: " << data;
    QJson::Parser parser;
    QVariantMap  result = parser.parse(data).toMap();
    QList<QVariant> photos = result["photos"].toMap()["photo"].toList();

    const QString term = context.query();

    foreach (QVariant photo, photos) {
        QVariantMap map = photo.toMap();

       Plasma::QueryMatch match(this);
       match.setType(Plasma::QueryMatch::PossibleMatch);
       QString fullUrl;
       fullUrl = QString("http://farm%1.staticflickr.com/%2/%3_%4.jpg").arg(map["farm"].toString(), map["server"].toString(), map["id"].toString(), map["secret"].toString());
//       if (reply->error() != 0) {
  //         kDebug() << "KRunner::Flickr runner, Json parser error. please report. error code: " << reply->error();
 //      }

//       QByteArray data = reply->readAll();

       QImage image;
 //      image.loadFromData(data);

       QIcon icon(new ImageIconEngine(image));
//      match.setIcon(icon);

        match.setData(fullUrl);
        match.setText(i18n("%1 on Flickr", map["title"].toString()));

       context.addMatch(term, match);
    }
}

#include "flickr.moc"
