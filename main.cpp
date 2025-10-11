#include "dvcs-ui/headers/mainwindow.h"
#include "VCS/headers/DVCSManager.h"
#include "VCS/headers/Message.h"
#include <QApplication>
#include <QFile>
#include <QDir>
#include <QDebug>
#include <QCoreApplication>
#include <QProcess>
#include <algorithm>
#include <vector>


int main(int argc, char *argv[])
{
    QString installationPath = QCoreApplication::applicationDirPath();
    DVCSManager Manager = DVCSManager(installationPath);

}
