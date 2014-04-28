#include <QCoreApplication>
#include <QTextStream>
#include <QEverCloud.h>

// This example demonstrates asynchronous API using.

using namespace qevercloud;

QTextStream cout(stdout);

int main(int argc, char *argv[])
{   
    QCoreApplication a(argc, argv);
    NoteStore* ns = new NoteStore(&a);

    // paste your developer token here
    // get it from https://www.evernote.com/api/DeveloperToken.action
    ns->setAuthenticationToken("S=s41:U=427a0c:E=14761d37b39:C=1400a224f39:P=1cd:A=en-devtoken:V=2:H=XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");

    // Take your NoteStore URL from the same place
    ns->setNoteStoreUrl("https://www.evernote.com/shard/XXX/notestore");

    Note note;
    note.title = QString("Test note");
    note.content = QString("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
             "<!DOCTYPE en-note SYSTEM \"http://xml.evernote.com/pub/enml2.dtd\">\n"
             "<en-note>"
             "<b>It's good to be king!</b><br /><br /><p>Well, it seems that <a href=\"https://github.com/mgsxx/QEverCloud\">QEverCloud</a> is indeed working...</p>"
             "</en-note>");

    QSharedPointer<EverCloudExceptionData> error;
    QVariant result;
    QObject::connect(ns->createNoteAsync(note), &AsyncResult::finished, [ns](QVariant result, QSharedPointer<EverCloudExceptionData> error) {
        if(!error.isNull()) {
            cout << QStringLiteral("Error: ") << error->errorMessage << endl;
            qApp->quit();
        } else {
            Note note = result.value<Note>();
            cout << QStringLiteral("The new note guid: ") << note.guid << endl;

            QObject::connect(ns->getNotebookAsync(note.notebookGuid), &AsyncResult::finished, [](QVariant result, QSharedPointer<EverCloudExceptionData> error) {
               if(error.isNull()) {
                   Notebook notebook = result.value<Notebook>();
                   cout << QStringLiteral("The note is created in the notebook '") << notebook.name << QStringLiteral("'") << endl;
               } else {
                   cout << QStringLiteral("Error 2: ") << error->errorMessage << endl;

                   // Example of handling an error by it's type
                   QSharedPointer<EDAMNotFoundExceptionData> errorNotFound = error.objectCast<EDAMNotFoundExceptionData>();
                   if(!errorNotFound.isNull()) {
                       cout << QStringLiteral("The notebook is not found!!!") << endl;
                   }
               }
               qApp->quit();
            });
        }
    });

    return a.exec();
}

