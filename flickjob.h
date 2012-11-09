/******************************************************************************
 *  Copyright (C) 2012 by Shaun Reich <sreich@kde.org>                        *
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

#ifndef FLICKJOB_H
#define FLICKJOB_H

#include <QObject>
#include <KIO/Job>

#include <KUrl>

class QNetworkReply;
class QNetworkAccessManager;

class FlickJob : public QObject
{
    Q_OBJECT

public:
    FlickJob(const QString& term,  bool singleRunnerMode);

    void start();
    QByteArray data();

private Q_SLOTS:
    void jobCompleted(QNetworkReply *reply);

Q_SIGNALS:
    void finished();

private:
    QNetworkAccessManager *m_manager;
    QByteArray m_data;
};

#endif
