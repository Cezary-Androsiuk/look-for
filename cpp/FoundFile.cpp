#include "FoundFile.h"

#include <filesystem>

QByteArrayList FoundFile::supportedImageFormats;

FoundFile::FoundFile(QObject *parent)
    : QObject{parent}
{

}

QString FoundFile::getPath() const
{
    return m_path;
}

QString FoundFile::getFileName() const
{
    return m_fileName;
}

QString FoundFile::getExtension() const
{
    return m_extension;
}

bool FoundFile::getIsImage() const
{
    return m_isImage;
}

void FoundFile::setPath(const QString &path)
{
    m_path = path;
}

void FoundFile::setFileName(const QString &fileName)
{
    m_fileName = fileName;
}

void FoundFile::setExtension(const QString &extension)
{
    m_extension = extension;
}

void FoundFile::testFileType()
{
    // printf("file format: %s\n", m_extension.toStdString().c_str());

    if(FoundFile::supportedImageFormats.contains(m_extension))
    {
        m_isImage = true;
    }
    else
    {
        m_isImage = false;
    }
}

void FoundFile::open() const noexcept
{
    std::filesystem::path file = m_path.toStdWString();
    file.make_preferred();
    std::wstring argument = L"/select,\"" + file.wstring() + L'\"';
    ShellExecute(0, L"open", L"explorer", argument.c_str(), 0, SW_SHOWNORMAL);
}
