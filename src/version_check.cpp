#include "version_check.h"
#include "messagebox.cpp"

QString Version::getVersion() {
    QString versionString;

    QResource versionResource(":/version.txt");
    if (versionResource.isValid()) {
        if (QFileInfo(versionResource.absoluteFilePath()).suffix() == QLatin1String("rcc")) {
            QByteArray compressedData(reinterpret_cast<const char*>(versionResource.data()), versionResource.size());
            QByteArray uncompressedData = qUncompress(compressedData);
            versionString = QString::fromUtf8(uncompressedData).trimmed();
        } else {
            QByteArray data(reinterpret_cast<const char*>(versionResource.data()), versionResource.size());
            versionString = QString::fromUtf8(data).trimmed();
        }
    } else {
        qDebug() << "Version resource not found!";
    }

    return versionString;
}

QString Version_Remote::getVersion_remote() {
    QNetworkAccessManager manager;
    QNetworkReply *reply = manager.get(QNetworkRequest(QUrl("https://raw.githubusercontent.com/athrvvvv/Minimal-Notepad/master/version.txt")));

    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    QString versionString;
    if (reply->error() == QNetworkReply::NoError) {
        versionString = QString::fromUtf8(reply->readAll()).trimmed();
    } else {
        qDebug() << "Failed to retrieve version:" << reply->errorString();
    }
    reply->deleteLater();

    return versionString;
}

bool InternetCheck::isConnected()
{
    bool internetConnected = false;

    foreach(QNetworkInterface interface, QNetworkInterface::allInterfaces())
    {
        if(interface.flags().testFlag(QNetworkInterface::IsUp) &&
           !interface.flags().testFlag(QNetworkInterface::IsLoopBack))
        {
            foreach(QNetworkAddressEntry address, interface.addressEntries())
            {
                if(address.ip().protocol() == QAbstractSocket::IPv4Protocol &&
                   address.netmask().toString() != "0.0.0.0")
                {
                    internetConnected = true;
                    break;
                }
            }
        }
    }

    return internetConnected;
}


namespace prompt_version_update {
    void version_update() {

        bool internetConnected = InternetCheck::isConnected();

        if(internetConnected)
        {
            qDebug() << "Internet is connected!";
            QString localVersion = Version::getVersion();
            QString remoteVersion = Version_Remote::getVersion_remote();
            qDebug() << localVersion << remoteVersion;
            if (localVersion == remoteVersion) {
                qDebug() << "Version is up to date.";
            } else {
                qDebug() << "A new version is available!";
                showNewVersionMessageBox();
            }
        }
        else
        {
            qDebug() << "Internet is not connected!";
            return;
        }
    }
}




