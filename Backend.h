#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>

#include <cstdio>
#include <QList>
#include <filesystem>
#include <QDebug>

#include "FoundFile.h"

typedef QList<FoundFile *> FoundFiles;

class Backend : public QObject
{
    Q_OBJECT
    Q_PROPERTY(FoundFiles foundFiles READ getFoundFiles CONSTANT FINAL)

public:
    explicit Backend(int argc, char **argv);
    ~Backend();

    bool getFailedAndShouldExit() const;
    bool getNoFilesFound() const;
    Q_INVOKABLE FoundFiles getFoundFiles() const; // getter mismarked as a slot XDD (but only when using "public slots:")

private:
    static void printInfo() noexcept;
    void addFileToList(std::filesystem::path filePath);
    void lookForFiles(QString phrase, bool detail, bool caseSensitive) noexcept;

signals:

private:
    bool m_failedAndShouldExit;
    bool m_noFilesFound;
    FoundFiles m_foundFiles;
};

#endif // BACKEND_H
