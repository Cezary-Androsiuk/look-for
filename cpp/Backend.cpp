#include "Backend.h"

Backend::Backend(int argc, char **argv)
    : QObject{nullptr}
    , m_failedAndShouldExit(false)
    , m_noFilesFound(false)
{
    printf("current path: %s\n",QDir::currentPath().toStdString().c_str());

    auto &sif = FoundFile::supportedImageFormats;
    sif = QImageReader::supportedImageFormats();
    // if(!sif.contains("jpg"))
    //     sif.append("jpg");
    // if(!sif.contains("png"))
    //     sif.append("png");
    // if(!sif.contains("heic"))
    //     sif.append("heic");

    printf("supported image formats:\n");
    if(!sif.isEmpty())
        printf("%s", sif[0].toStdString().c_str());
    for(auto it = sif.begin()+1; it != sif.end(); ++it)
        printf(", %s", it->toStdString().c_str());

    QElapsedTimer timer;
    timer.start();
    // lookfor 20161110_23
    m_foundFiles.reserve(16'777'216); /// 16 MB

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

    printf("\n");
    printf("Directory: %s\n", QDir::currentPath().toStdString().c_str());
    printf("Phrase: \"%s\"\n", lookFor.toStdString().c_str());
    printf("Case Sensitive: %s\n", BOOL_TO_CSTR(caseSensitive));
    printf("Detail: %s\n", BOOL_TO_CSTR(detailSearching));

    m_searchPhrase = lookFor;

    // printf("elapsed: %lld \n", timer.elapsed());

    printf("\n" "Searching...\n");
    fflush(stdout);
    this->lookForFiles(lookFor, detailSearching, caseSensitive);

    // printf("\n""elapsed: %lld \n", timer.elapsed());
}

Backend::~Backend()
{
    for(auto it = m_foundFiles.begin(); it != m_foundFiles.end(); ++it)
        delete *it;
    // m_foundFiles.clear();
}

void Backend::printInfo() noexcept
{
    printf("arg1: text phrase to look for in current directory\n");
    printf("arg2: \n");
    printf("\t optional -d value, if set then phrase will be looked also in the conntent of files in directory, otherwise only in filenames\n");
    printf("\t optional -c value, if set then phrase will be compared as case sensitive, otherwise will be compared case insensitive\n");
    printf("\n");
    printf("example1: lookfor \"some text\"\n");
    printf("example2: lookfor \"some text\" -d\n");
    printf("example2: lookfor \"some text\" -dc\n");
}

std::string Backend::readableNumber(size_t number) noexcept
{
    // std::string strNumber;
    // do{
    //     // strNumber.push_back(number)
    // }while(!number);
    return "";
}

void Backend::addFileToList(QFileInfo fileInfo)
{
    FoundFile *foundFile = new FoundFile(this);
    foundFile->setPath(fileInfo.filePath());
    foundFile->setFileName(fileInfo.fileName());
    foundFile->setExtension(fileInfo.suffix());

    foundFile->testFileType();

    m_foundFiles.append(foundFile);
}

void Backend::lookForFiles(QString phrase, bool detail, bool caseSensitive) noexcept
{
    QDirIterator dirIt(QDir::currentPath(), QDir::AllEntries | QDir::Hidden | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);

    size_t foundFiles = 0;
    size_t foundDirs = 0;
    size_t matchFiles = 0;
    Qt::CaseSensitivity isSensitive = caseSensitive ? Qt::CaseSensitive : Qt::CaseInsensitive;

    size_t last_write = QDateTime::currentMSecsSinceEpoch();
    const size_t printDelayMS = 500;
    printf("Found: %u, Match: %u",0, 0);

    try{
        while(dirIt.hasNext())
        {
            dirIt.next();
            if(dirIt.fileName().contains(phrase, isSensitive))
            {
                this->addFileToList(dirIt.fileInfo());
                ++matchFiles;
            }
            if(dirIt.fileInfo().isFile())
                ++foundFiles;
            else if(dirIt.fileInfo().isDir())
                ++foundDirs;

            if(last_write + printDelayMS < QDateTime::currentMSecsSinceEpoch())
            {
                printf("\r" "Found: %u, Match: %u", foundFiles + foundDirs, matchFiles);
                last_write = QDateTime::currentMSecsSinceEpoch();
            }
        }
        printf("\r" "Found: %u, Match: %u", foundFiles + foundDirs, matchFiles);
    }
    catch (...) {
        printf("Exception occured while%s iterating through files in \"%s\"\n",
               detail ? " detail" : "", phrase.toStdString().c_str());
    }
    printf("\n" "Searching Finished!\n");

    if(!matchFiles)
    {
        printf("Found %llu files and %llu dirs, but none of them matching the phrase!\n", foundFiles, foundDirs);
        m_noFilesFound = true;
        return;
    }

    printf("Found %llu files and %llu dirs, and %llu match the phrase\n", foundFiles, foundDirs, matchFiles);
}

bool Backend::getNoFilesFound() const
{
    return m_noFilesFound;
}

const QString &Backend::getSearchPhrase() const
{
    return m_searchPhrase;
}

FoundFiles Backend::getFoundFiles() const
{
    return m_foundFiles;
}

bool Backend::getFailedAndShouldExit() const
{
    return m_failedAndShouldExit;
}
