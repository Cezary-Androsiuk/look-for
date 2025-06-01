#ifndef FOUNDFILE_H
#define FOUNDFILE_H

#include <QObject>
#include <windows.h>
#include <QImage>

class FoundFile : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString path READ getPath CONSTANT FINAL)
    Q_PROPERTY(QString fileName READ getFileName CONSTANT FINAL)
    Q_PROPERTY(QString extension READ getExtension CONSTANT FINAL)
    Q_PROPERTY(bool isImage READ getIsImage CONSTANT FINAL)

public:
    explicit FoundFile(QObject *parent = nullptr);

    QString getPath() const;
    QString getFileName() const;
    QString getExtension() const;
    bool getIsImage() const;

    void setPath(const QString &path);
    void setFileName(const QString &fileName);
    void setExtension(const QString &extension);

    void testFileType();

    Q_INVOKABLE void open() const noexcept;

signals:
    void clickedChanged();

public:
    static QByteArrayList supportedImageFormats;

private:

    QString m_path;
    QString m_fileName;
    QString m_extension;

    bool m_clicked;

    bool m_isImage;
};

#endif // FOUNDFILE_H
