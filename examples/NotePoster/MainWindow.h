#ifndef MGS_MAINWINDOW_H
#define MGS_MAINWINDOW_H

#include <QDialog>
#include <QEverCloud.h>
#include <QTextCharFormat>

namespace Ui {
class MainWindow;
}

class MainWindow : public QDialog
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void setBold(bool yes);
    void setItalic(bool yes);
    void currentCharFormatChanged(QTextCharFormat f);
    void createNote();
private:
    Ui::MainWindow *ui;
    qevercloud::NoteStore* noteStore;
    QMap<QString, QString> notebooks;
    bool inCycle_;
};

#endif // MGS_MAINWINDOW_H
