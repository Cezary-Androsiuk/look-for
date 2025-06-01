#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>

#include <cstdio>
#include <string>
#include <QList>
#include <QDateTime>
#include <QDirIterator>
#include <QFileInfo>
#include <QDebug>
#include <QElapsedTimer>
#include <QImageReader>

#include "FoundFile.h"

#define BOOL_TO_CSTR(b) ( (b) ? "true" : "false" )

typedef QList<FoundFile *> FoundFiles;

class Backend : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString searchPhrase READ getSearchPhrase CONSTANT FINAL)
    Q_PROPERTY(FoundFiles foundFiles READ getFoundFiles CONSTANT FINAL)

public:
    explicit Backend(int argc, char **argv);
    ~Backend();

    bool getFailedAndShouldExit() const;
    bool getNoFilesFound() const;
    const QString &getSearchPhrase() const;
    Q_INVOKABLE FoundFiles getFoundFiles() const; // getter mismarked as a slot XDD (but only when using "public slots:")

private:
    static void printInfo() noexcept;
    static std::string readableNumber(size_t number) noexcept;
    void addFileToList(QFileInfo fileInfo);
    void lookForFiles(QString phrase, bool detail, bool caseSensitive) noexcept;

signals:

private:
    QString m_searchPhrase;
    bool m_failedAndShouldExit;
    bool m_noFilesFound;
    FoundFiles m_foundFiles;
};

#endif // BACKEND_H
