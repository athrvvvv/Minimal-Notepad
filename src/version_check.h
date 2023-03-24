#ifndef VERSION_H
#define VERSION_H

#include <QString>
#include <QObject>
#include <QResource>
#include <QByteArray>
#include <QFileInfo>
#include <QDebug>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QEventLoop>
#include <QNetworkInformation>
#include <QNetworkInterface>

namespace Version {
    QString getVersion();
};

namespace Version_Remote {
    QString getVersion_remote();
}

namespace prompt_version_update {
    void version_update();
}

class InternetCheck
{
public:
    static bool isConnected();
};
#endif // VERSION_H
