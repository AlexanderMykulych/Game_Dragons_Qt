#include "form.h"
#include <QApplication>
#include <windows.h>
#include <QTextCodec>
#include <QtCore>
#include <QtGui>
#include <time.h>
#include <QInputDialog>
#include "propertis.h"

void Change_Display_Size(int New_Width, int New_Height);
int Old_Display_Width;
int Old_Display_Height;

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    Change_Display_Size(CLIENT_SCREEN_WIDTH, CLIENT_SCREEN_HEIGHT);

    Form w;

    w.Old_Display_Width = Old_Display_Width;
    w.Old_Display_Height = Old_Display_Height;

    srand(time(NULL));

    w.showFullScreen();

    return a.exec();
}

void Change_Display_Size(int New_Width, int New_Height)
{
    QDesktopWidget *descktop = QApplication::desktop();
    Old_Display_Width = descktop->width();
    Old_Display_Height = descktop->height();

    //change display size
    {
        DEVMODE dm;

        dm.dmSize = sizeof(DEVMODE);

        dm.dmPelsWidth = New_Width;
        dm.dmPelsHeight = New_Height;

        dm.dmFields = DM_PELSWIDTH|DM_PELSHEIGHT;

        ChangeDisplaySettings(&dm, CDS_UPDATEREGISTRY);
    }
}
