

#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "settings.h"

#include <QMessageBox>

using namespace qevercloud;

MainWindow::MainWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainWindow),
    inCycle_(false)
{
    ui->setupUi(this);

    noteStore = new NoteStore(settings()->noteStoreUrl(), settings()->authenticationToken(), this);

    // reading notebook names and guids
    QStringList names;
    QString defualtNotebook;
    QList<Notebook> nl = noteStore->listNotebooks();
    for(int i = 0; i < nl.length(); i++) {
        const Notebook& n = nl.at(i);
        notebooks[n.name] = n.guid;
        names << n.name;
        if(n.defaultNotebook) defualtNotebook = n.name;
    }
    qSort(names);
    ui->notebooksComboBox->addItems(names);
    ui->notebooksComboBox->setCurrentIndex(names.indexOf(defualtNotebook));

    connect(ui->noteTextEdit, SIGNAL(currentCharFormatChanged(QTextCharFormat)), SLOT(currentCharFormatChanged(QTextCharFormat)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setBold(bool yes)
{
    if(!inCycle_) {
       ui->noteTextEdit->setFontWeight(yes ? QFont::Bold : QFont::Normal);
    }
}

void MainWindow::setItalic(bool yes)
{
    if(!inCycle_) {
       ui->noteTextEdit->setFontItalic(yes);
    }
}

void MainWindow::currentCharFormatChanged(QTextCharFormat f)
{
    inCycle_ = true;
    ui->boldButton->setChecked(ui->noteTextEdit->fontWeight() >= QFont::Bold);
    ui->italicButton->setChecked(ui->noteTextEdit->fontItalic());
    inCycle_ = false;
}

void MainWindow::createNote()
{
    // For the sake of simplicity I do not handle images
    // and ENML extensions
    QString enml = ui->noteTextEdit->toHtml();
    enml = enml.mid(enml.indexOf("<body "));
    enml.replace("<body ", "<en-note ");
    enml = enml.left(enml.indexOf("</body>"));
    enml += "</en-note>";

    // the xml header must always be peresent
    enml = QString("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n")
            + "<!DOCTYPE en-note SYSTEM \"http://xml.evernote.com/pub/enml2.dtd\">\n"
            + enml;

    try {
        Note note;
        note.title = ui->titleLineEdit->text().trimmed().left(EDAM_NOTE_TITLE_LEN_MAX);
        note.notebookGuid = notebooks[ui->notebooksComboBox->currentText()];
        note.content = enml;
        note = noteStore->createNote(note);
        QMessageBox::information(this, "Success", QString("Note GUID: %1").arg(note.guid));
    } catch(const std::exception& e) {
        QMessageBox::critical(this, "Failure", e.what());
    }
}

