#include "FoundFile.h"

FoundFile::FoundFile(QObject *parent)
    : QObject{parent}
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
    std::filesystem::path file = m_path.toStdWString();
    file.make_preferred();
    std::wstring argument = L"/select,\"" + file.wstring() + L'\"';
    ShellExecute(0, L"open", L"explorer", argument.c_str(), 0, SW_SHOWNORMAL);
}
