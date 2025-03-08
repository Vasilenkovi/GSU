#include "dvcs-ui/headers/mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QDir>
#include <QDebug>
#include <QCoreApplication>
#include <QProcess>

bool copySelfToLocation(const QString& targetPath) {
    QString selfPath = QCoreApplication::applicationFilePath();
    QFileInfo fi(selfPath);
    QString newPath = QDir(targetPath).filePath(fi.fileName());

    if(QFile::exists(newPath) && !QFile::remove(newPath)) {
        qCritical() << "Failed to remove existing file:" << newPath;
        return false;
    }

    if(!QFile::copy(selfPath, newPath)) {
        qCritical() << "Failed to copy to:" << newPath;
        return false;
    }

    // This bullshit is stolen, should work for linux to made file executable
    QFile::setPermissions(newPath,
                          QFile::ExeOwner | QFile::ExeUser | QFile::ExeGroup | QFile::ExeOther |
                              QFile::WriteOwner | QFile::ReadOwner |
                              QFile::WriteUser | QFile::ReadUser);
    QDir targetDir(targetPath);
    if(!targetDir.mkpath("repositorykeeper")) {
        qCritical() << "Failed to create repositorykeeper directory in:" << targetPath;
        return false;
    }

    return true;
}

int main(int argc, char *argv[])
{
\
    bool guiMode = false;
    bool installationMode = false;
    QString targetDir = "C:/DVCS";

    for(int i = 1; i < argc; ++i) {
        if(strcmp(argv[i], "--move") == 0 || strcmp(argv[i], "-m") == 0) {
            installationMode = true;
            if(i+1 < argc && QDir(argv[i+1]).exists()) {
                targetDir = argv[++i];
            }
            break;
        }
        if(strcmp(argv[i], "--gui") == 0 || strcmp(argv[i], "-g") == 0) {
            guiMode = true;
            if(i+1 < argc && QDir(argv[i+1]).exists()) {
                targetDir = argv[++i];
            }
            break;
        }
    }

    if(installationMode) {
        // installation process
        QCoreApplication a(argc, argv);

        qDebug() << "Trying to copy to:" << targetDir;

        if(copySelfToLocation(targetDir)) {
            qDebug() << "Successfully copied to:" << targetDir;
            return 0;
        } else {
            qCritical() << "Failed to copy executable!";
            return 1;
        }
    }
    else {
        // GUI mode... maybe once
        QApplication a(argc, argv);
        MainWindow w;
        w.show();
        return a.exec();
    }
}
