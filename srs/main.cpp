#include <QApplication>
#include <MainWindow.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow *window = new MainWindow;
    window->setWindowTitle("ServoSliders 1.0");
    window->show();


    QObject::connect(window->setPortButton, SIGNAL(clicked()), window, SLOT(SetCOMPort()));
    QObject::connect(window->closePortButton, SIGNAL(clicked()), window, SLOT(CloseCOMPort()));

    QObject::connect(window->spBox1,SIGNAL(valueChanged(int)), window, SLOT(SetDegree1(int)));
    QObject::connect(window->spBox2,SIGNAL(valueChanged(int)), window, SLOT(SetDegree2(int)));
    QObject::connect(window->spBox3,SIGNAL(valueChanged(int)), window, SLOT(SetDegree3(int)));
    QObject::connect(window->spBox4,SIGNAL(valueChanged(int)), window, SLOT(SetDegree4(int)));

    QObject::connect(window,SIGNAL(destroyed()), window, SLOT(CloseCOMPort()));

    return app.exec();
}
