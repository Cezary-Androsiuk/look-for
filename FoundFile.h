#ifndef FOUNDFILE_H
#define FOUNDFILE_H

#include <QObject>

class FoundFile : public QObject
{
    Q_OBJECT
public:
    explicit FoundFile(QObject *parent = nullptr);

signals:
};

#endif // FOUNDFILE_H
