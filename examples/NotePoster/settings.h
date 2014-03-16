#ifndef NOTEPOSTER_SETTINGS_H
#define NOTEPOSTER_SETTINGS_H

#include <QObject>
#include <QString>

class QSettings;

class Settings: public QObject {
public:
    Settings();

    QString host();
    void setHost(QString value);

    QString consumerKey();
    void setConsumerKey(QString value);

    QString consumerSecret();
    void setConsumerSecret(QString value);

    QString noteStoreUrl();
    void setNoteStoreUrl(QString value);

    QString authenticationToken();
    void setAuthenticationToken(QString value);

private:
  QSettings* st_;
};

Settings* settings();

#endif // NOTEPOSTER_SETTINGS_H
