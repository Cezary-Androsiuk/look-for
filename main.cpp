#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QQmlContext>

#include "Backend.h"

int main(int argc, char *argv[])
{
    Backend backend(argc, argv); // test given path and exist if empty (no gui in that case)
    if(backend.getFailedAndShouldExit())
        return 1;
    if(backend.getNoFilesFound())
        return 0;

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("Backend", &backend);

    const QUrl url(QStringLiteral("qrc:/LookFor/Main.qml"));
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
