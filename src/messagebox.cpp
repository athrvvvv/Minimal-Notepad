#include <QMessageBox>
#include <QDesktopServices>
#include <QUrl>

void showNewVersionMessageBox() {
    QMessageBox msgBox;
    msgBox.setWindowTitle("New Version Available");
    msgBox.setText("A new version is available! Get it now?");
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Ok);

    int ret = msgBox.exec();

    if (ret == QMessageBox::Ok) {
        QDesktopServices::openUrl(QUrl("https://github.com/athrvvvv/Minimal-Notepad/releases/"));
    }
}
