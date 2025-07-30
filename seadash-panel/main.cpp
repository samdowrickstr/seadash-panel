#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "QtAwesome/QtAwesome.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6,0,0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    // Initialize FontAwesome
    fa::QtAwesome awesome;
    awesome.initFontAwesome();

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("qtawesome", &awesome);
    engine.rootContext()->setContextProperty("faSolidFontFamily", awesome.fontName(fa::fa_solid));
    engine.rootContext()->setContextProperty("faRegularFontFamily", awesome.fontName(fa::fa_regular));
    engine.rootContext()->setContextProperty("faBrandsFontFamily", awesome.fontName(fa::fa_brands));

    engine.load(QUrl(QStringLiteral("qrc:/qml/TitleBarWindow.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
