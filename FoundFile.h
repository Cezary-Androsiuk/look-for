#ifndef FOUNDFILE_H
#define FOUNDFILE_H

#include <QObject>

#include <filesystem>
#include <string>
#include <windows.h>

class FoundFile : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString path READ getPath CONSTANT FINAL)
    Q_PROPERTY(QString fileName READ getFileName CONSTANT FINAL)
    Q_PROPERTY(QString extension READ getExtension CONSTANT FINAL)

public:
    explicit FoundFile(std::filesystem::path sourcePath, QObject *parent = nullptr);

    QString getPath() const;
    QString getFileName() const;
    QString getExtension() const;

    void setPath(const QString &path);
    void setFileName(const QString &fileName);
    void setExtension(const QString &extension);

    Q_INVOKABLE void open() const noexcept;

signals:

private:
    std::filesystem::path m_sourcePath;
    QString m_path;
    QString m_fileName;
    QString m_extension;
};

#endif // FOUNDFILE_H
