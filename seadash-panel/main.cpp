#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QWindow>
#include <QFontDatabase>

#include "QtAwesome/QtAwesome.h"

#ifdef Q_OS_WIN
#include <windows.h>
#include <shellapi.h>

static void registerAppBarWindows(QWindow* w, int barHeight)
{
    APPBARDATA abd;
    ZeroMemory(&abd, sizeof(abd));
    abd.cbSize = sizeof(abd);
    abd.hWnd = reinterpret_cast<HWND>(w->winId());
    abd.uEdge = ABE_TOP;
    abd.rc.left = 0;
    abd.rc.top = 0;
    abd.rc.right = GetSystemMetrics(SM_CXSCREEN);
    abd.rc.bottom = barHeight;
    SHAppBarMessage(ABM_NEW, &abd);
    SHAppBarMessage(ABM_SETPOS, &abd);
}

static void shapeWindowWindows(QWindow* w,
    int barHeight,
    int mobX, int mobWidth,
    int winWidth, int winHeight,
    int mobRadius)
{
    HWND hwnd = reinterpret_cast<HWND>(w->winId());

    HRGN rBar = CreateRectRgn(0, 0, winWidth, barHeight);

    // Match QML's: topMargin: -10, height: 90
    int mobY = barHeight - 10;
    int mobHeight = 90;

    // ADD padding on left/right
    int padding = 2;

    HRGN rMob = CreateRoundRectRgn(
        mobX - padding,
        mobY,
        mobX + mobWidth + padding,
        mobY + mobHeight,
        mobRadius,
        mobRadius
    );

    HRGN rTotal = CreateRectRgn(0, 0, 0, 0);
    CombineRgn(rTotal, rBar, rMob, RGN_OR);

    SetWindowRgn(hwnd, rTotal, TRUE);

    DeleteObject(rBar);
    DeleteObject(rMob);
}
#endif

#ifdef Q_OS_UNIX
#ifndef Q_OS_MAC

static void registerDockWayland(QWindow* w, int barHeight)
{
    // On Wayland, most window metadata is handled by Qt automatically.
    // You can use special protocols like wlr-layer-shell in the future,
    // but for now Qt::Tool | FramelessWindowHint | StayOnTop should suffice.

    w->setFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint);
    w->setTitle("SeaDash Panel");
    w->setProperty("panelWindow", true);  // Optional property for QML/compositor
}

static void shapeWindowWayland(QWindow* w,
    int barHeight,
    int mobX, int mobWidth,
    int winWidth, int winHeight)
{
    // No server-side shaping in Wayland — use QML shapes and transparency instead
    Q_UNUSED(w)
        Q_UNUSED(barHeight)
        Q_UNUSED(mobX)
        Q_UNUSED(mobWidth)
        Q_UNUSED(winWidth)
        Q_UNUSED(winHeight)

        // On Wayland, use Qt Quick Rectangle + radius + opacity mask
        // Nothing to do here on the C++ side
}

#endif
#endif

int main(int argc, char* argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6,0,0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    // Register font files from qrc
    QFontDatabase::addApplicationFont(":/fonts/Font Awesome 6 Brands-Regular-400.otf");
    QFontDatabase::addApplicationFont(":/fonts/Font Awesome 6 Free-Regular-400.otf");
    QFontDatabase::addApplicationFont(":/fonts/Font Awesome 6 Free-Solid-900.otf");

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

    // Set up dimensions
    constexpr int barHeight = 50;
    constexpr int windowHeight = 90;
    constexpr int pillWidth = 80;
    constexpr int pillRadius = 10;
    constexpr int pillX = 500;

    for (QObject* obj : engine.rootObjects()) {
        if (auto w = qobject_cast<QWindow*>(obj)) {
            if (w->objectName() == QLatin1String("TitleBarWindow")) {

#ifdef Q_OS_WIN
                registerAppBarWindows(w, barHeight);
                shapeWindowWindows(w, barHeight, pillX, pillWidth, w->width(), windowHeight, pillRadius);

#elif defined(Q_OS_UNIX) && !defined(Q_OS_MAC)
                registerDockWayland(w, barHeight);
                shapeWindowWayland(w, barHeight, pillX, pillWidth, w->width(), windowHeight);
#endif

                break;
            }
        }
    }

    return app.exec();
}
