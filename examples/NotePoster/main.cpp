
#include "MainWindow.h"
#include <QApplication>
#include <QMessageBox>
#include "SettingsDialog.h"
#include <QtDebug>

using namespace qevercloud;

class NotePosterApplication: public QApplication {
public:
    bool notify(QObject* o, QEvent * e);
};

bool NotePosterApplication::notify(QObject *o, QEvent *e)
{
    try {
        return QApplication::notify(o, e);
    } catch(const std::exception& e)  {
        qDebug() << e.what();
        quit();
    } catch(...) {
        qDebug() << "Unknown exception";
        quit();
    }
    return false;
}

int main(int argc, char *argv[])
try
{
    // qrand is used for nonce generation by default
    // so qsrand must be called in the default case
    qsrand(QDateTime::currentMSecsSinceEpoch() % static_cast<quint64>(256)*256*256*256);

    QApplication a(argc, argv);

    SettingsDialog d;
    if(d.exec() != QDialog::Accepted) return 0;

    MainWindow w;
    w.show();

    return a.exec();
} catch(const std::exception& e) {
    qDebug() << e.what();
    return 1;
} catch(...) {
    qDebug() << "Unknown exception";
    return 1;
}





