#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QWindow>

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
#if defined(QT_WIDGETS_LIB) || defined(QT_GUI_LIB)
#include <QX11Info>
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/extensions/shape.h>

static void registerDockX11(QWindow* w, int barHeight)
{
    Display* dpy = QX11Info::display();
    ::Window win = w->winId();

    Atom atomWindowType = XInternAtom(dpy, "_NET_WM_WINDOW_TYPE", False);
    Atom atomDock = XInternAtom(dpy, "_NET_WM_WINDOW_TYPE_DOCK", False);
    XChangeProperty(dpy, win, atomWindowType, XA_ATOM, 32, PropModeReplace,
        reinterpret_cast<unsigned char*>(&atomDock), 1);

    long strut[12] = {
        0, 0,
        barHeight, 0,
        0, 0, 0, 0,
        0, QX11Info::appScreenGeometry().width(),
        0, 0
    };
    Atom strutAtom = XInternAtom(dpy, "_NET_WM_STRUT_PARTIAL", False);
    XChangeProperty(dpy, win, strutAtom, XA_CARDINAL, 32, PropModeReplace,
        reinterpret_cast<unsigned char*>(strut), 12);
}

static void shapeWindowX11(QWindow* w,
    int barHeight,
    int mobX, int mobWidth,
    int winWidth, int winHeight)
{
    Display* dpy = QX11Info::display();
    ::Window win = w->winId();

    XRectangle rects[2];
    rects[0].x = 0;
    rects[0].y = 0;
    rects[0].width = winWidth;
    rects[0].height = barHeight;

    rects[1].x = mobX;
    rects[1].y = 0;
    rects[1].width = mobWidth;
    rects[1].height = winHeight;

    XShapeCombineRectangles(dpy, win,
        ShapeBounding,
        0, 0,
        rects, 2,
        ShapeSet, Unsorted);
}
#endif
#endif

int main(int argc, char* argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6,0,0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

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
#if defined(QT_WIDGETS_LIB) || defined(QT_GUI_LIB)
                registerDockX11(w, barHeight);
                shapeWindowX11(w, barHeight, pillX, pillWidth, w->width(), windowHeight);
#endif
#endif

                break;
            }
        }
    }

    return app.exec();
}
