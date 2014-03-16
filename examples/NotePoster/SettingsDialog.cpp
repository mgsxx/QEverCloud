#include "SettingsDialog.h"
#include "ui_SettingsDialog.h"
#include <QEverCloudOAuth.h>
#include <QMessageBox>
#include "settings.h"

using namespace qevercloud;

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
    ui->hostLineEdit->setText(settings()->host());
    ui->consumerKeyLineEdit->setText(settings()->consumerKey());
    ui->consumerSecretLineEdit->setText(settings()->consumerSecret());
    ui->noteStoreUrlLineEdit->setText(settings()->noteStoreUrl());
    ui->authenticationTokenLineEdit->setText(settings()->authenticationToken());
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::login()
{
    EvernoteOAuthDialog d(ui->consumerKeyLineEdit->text().trimmed(), ui->consumerSecretLineEdit->text().trimmed(), ui->hostLineEdit->text().trimmed());
    d.setWindowTitle("Log in to Evernote");
    if(d.exec() != QDialog::Accepted) {
        QMessageBox::critical(0, "NotePoster", "Login failed.\n" + d.oauthError());
        return;
    }
    ui->authenticationTokenLineEdit->setText(d.oauthResult().authenticationToken);
    ui->noteStoreUrlLineEdit->setText(d.oauthResult().noteStoreUrl);
}

void SettingsDialog::onFinished()
{
    settings()->setHost(ui->hostLineEdit->text());
    settings()->setConsumerKey(ui->consumerKeyLineEdit->text());
    settings()->setConsumerSecret(ui->consumerSecretLineEdit->text());
    settings()->setNoteStoreUrl(ui->noteStoreUrlLineEdit->text());
    settings()->setAuthenticationToken(ui->authenticationTokenLineEdit->text());
}
