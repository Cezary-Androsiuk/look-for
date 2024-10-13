#include "FoundFile.h"

FoundFile::FoundFile(std::filesystem::path sourcePath, QObject *parent)
    : QObject{parent}
    , m_sourcePath(sourcePath)
{}

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

void FoundFile::open() const noexcept
{
    std::wstring argument = L"/select," + m_sourcePath.wstring();
    ShellExecute(0, L"open", L"explorer", argument.c_str(), 0, SW_SHOWNORMAL);
}
