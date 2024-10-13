#ifndef BACKEND_H
#define BACKEND_H

#include <cstdio>
#include <filesystem>
#include <QDebug>

#include <QObject>

class Backend : public QObject
{
    Q_OBJECT
public:
    explicit Backend(int argc, char **argv);
    ~Backend();

    bool getFailedAndShouldExit() const;
    bool getNoFilesFound() const;

private:
    static void printInfo() noexcept;
    void addFileToList(std::filesystem::path foundFile);
    void lookForFiles(QString phrase, bool detail, bool caseSensitive) noexcept;

signals:

private:
    bool m_failedAndShouldExit;
    bool m_noFilesFound;
};

#endif // BACKEND_H
