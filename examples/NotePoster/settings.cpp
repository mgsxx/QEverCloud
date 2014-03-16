
#include "settings.h"

#include <QApplication>
#include <QDir>
#include <QSettings>
#include <QtDebug>

Settings *settings()
{
    static Settings* settings_ = 0;
    if(!settings_) {
        settings_ = new Settings;
    }
    return settings_;

}


Settings::Settings()
{
    QString iniPath = QDir(qApp->applicationDirPath()).absoluteFilePath("NotePoster.ini");
    st_ = new QSettings(iniPath, QSettings::IniFormat, this);
}

QString Settings::host()
{
    return st_->value("Evernote/host", QString()).toString().trimmed();
}

void Settings::setHost(QString value)
{
    st_->setValue("Evernote/host", value);
    st_->sync();
}

QString Settings::consumerKey()
{
    return st_->value("Evernote/consumerKey", QString()).toString().trimmed();
}

void Settings::setConsumerKey(QString value)
{
    st_->setValue("Evernote/consumerKey", value);
    st_->sync();
}

QString Settings::consumerSecret()
{
    return st_->value("Evernote/consumerSecret", QString()).toString().trimmed();
}

void Settings::setConsumerSecret(QString value)
{
    st_->setValue("Evernote/consumerSecret", value);
    st_->sync();
}

QString Settings::noteStoreUrl()
{
    return st_->value("Evernote/noteStoreUrl", QString()).toString().trimmed();
}

void Settings::setNoteStoreUrl(QString value)
{
    st_->setValue("Evernote/noteStoreUrl", value);
    st_->sync();
}

QString Settings::authenticationToken()
{
    return st_->value("Evernote/authenticationToken", QString()).toString().trimmed();
}

void Settings::setAuthenticationToken(QString value)
{
    st_->setValue("Evernote/authenticationToken", value);
    st_->sync();
}

