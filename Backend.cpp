#include "Backend.h"

Backend::Backend(int argc, char **argv)
    : QObject{nullptr}
    , m_failedAndShouldExit(false)
    , m_noFilesFound(false)
{
    QString lookFor;
    bool detailSearching = false;
    bool caseSensitive = false;

    if(argc <= 1) // no args was given
    {
        Backend::printInfo();
        m_failedAndShouldExit = true;
        return;
    }
    else // (2 or more) at least value to look for was given
    {
        lookFor = argv[1];
    }

    if(argc != 2) // more than two arguments was given
    {
        if(argc == 3) // three arguments
        {
            QString arg2(argv[2]);
            if(arg2 == "-d")
            {
                detailSearching = true;
            }
            else if(arg2 == "-c")
            {
                caseSensitive = true;
            }
            else if(arg2 == "-cd" || arg2 == "-dc")
            {
                caseSensitive = true;
                detailSearching = true;
            }
            else // second argument was not correct
            {
                printf("second argument failed! Looking for \"-d\", \"-c\" or \"-dc\" but got \"%s\"\n", argv[2]);
                Backend::printInfo();
                m_failedAndShouldExit = true;
                return;
            }
        }
        else // 4 or more arguments
        {
            QString arg2(argv[2]);
            QString arg3(argv[3]);
            bool combination1 = arg2 == "-d" && arg3 == "-c";
            bool combination2 = arg2 == "-c" && arg3 == "-d";
            if(combination1 || combination2)
            {
                caseSensitive = true;
                detailSearching = true;
            }
            else // third argument was not correct
            {
                printf("second or third argument failed! Looking for \"-c\" or \"-d\" but got \"%s\" and \"%s\"\n", argv[2], argv[3]);
                Backend::printInfo();
                m_failedAndShouldExit = true;
                return;
            }
        }

    }

    this->lookForFiles(lookFor, detailSearching, caseSensitive);

}

Backend::~Backend()
{
    for(FoundFile *foundFile : m_foundFiles)
        delete foundFile;
    m_foundFiles.clear();
}

void Backend::printInfo() noexcept
{
    printf("value to look for was specyfied!\n");
    printf("arg1: text phrase to look for in current directory\n");
    printf("arg2: \n");
    printf("\t optional -d value, if set then phrase will be looked also in the conntent of files in directory, otherwise only in filenames\n");
    printf("\t optional -c value, if set then phrase will be compared as case sensitive, otherwise will be compared case insensitive\n");
    printf("\n");
    printf("example1: lookfor \"some text\"\n");
    printf("example2: lookfor \"some text\" -d\n");
    printf("example2: lookfor \"some text\" -dc\n");
}

void Backend::addFileToList(std::filesystem::__cxx11::path filePath)
{
    FoundFile *foundFile = new FoundFile(filePath, this);
    foundFile->setPath(filePath.string().c_str());
    foundFile->setFileName(filePath.filename().string().c_str());
    foundFile->setExtension(filePath.extension().string().c_str());

    m_foundFiles.append(foundFile);
}

void Backend::lookForFiles(QString phrase, bool detail, bool caseSensitive) noexcept
{
    try{
        for(const auto &file : std::filesystem::recursive_directory_iterator(std::filesystem::current_path()))
        {
            QString fileName(file.path().filename().string().c_str());
            Qt::CaseSensitivity isSensitive = caseSensitive ? Qt::CaseSensitive : Qt::CaseInsensitive;
            if(fileName.contains(phrase, isSensitive))
                this->addFileToList(file);
        }
    }
    catch (...) {
        printf("exception occured while%s iterating through files in \"%s\"\n", detail ? " detail" : "", phrase.toStdString().c_str());
    }
}

bool Backend::getNoFilesFound() const
{
    return m_noFilesFound;
}

FoundFiles Backend::getFoundFiles() const
{
    return m_foundFiles;
}

bool Backend::getFailedAndShouldExit() const
{
    return m_failedAndShouldExit;
}
