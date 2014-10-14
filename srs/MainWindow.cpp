#include <MainWindow.h>
#include <windows.h>

#define DEGREE_MAX 180
#define DEGREE_MIN 0
#define DEGREE_MID 90

Serial *serial = new Serial;

MainWindow::MainWindow(QWidget *parent) : QDialog(parent)
{
    slide1 = new QSlider(Qt::Horizontal);
    slide2 = new QSlider(Qt::Horizontal);
    slide3 = new QSlider(Qt::Horizontal);
    slide4 = new QSlider(Qt::Horizontal);

    slide1->setMaximum(DEGREE_MAX);
    slide1->setValue(DEGREE_MID);
    slide1->setMinimum(DEGREE_MIN);

    slide2->setMaximum(DEGREE_MAX);
    slide2->setValue(DEGREE_MID);
    slide2->setMinimum(DEGREE_MIN);

    slide3->setMaximum(DEGREE_MAX);
    slide3->setValue(DEGREE_MID);
    slide3->setMinimum(DEGREE_MIN);

    slide4->setMaximum(DEGREE_MAX);
    slide4->setValue(DEGREE_MID);
    slide4->setMinimum(DEGREE_MIN);

    spBox1 = new QSpinBox;
    spBox2 = new QSpinBox;
    spBox3 = new QSpinBox;
    spBox4 = new QSpinBox;

    spBox1->setMaximum(DEGREE_MAX);
    spBox1->setValue(DEGREE_MID);
    spBox1->setMinimum(DEGREE_MIN);

    spBox2->setMaximum(DEGREE_MAX);
    spBox2->setValue(DEGREE_MID);
    spBox2->setMinimum(DEGREE_MIN);

    spBox3->setMaximum(DEGREE_MAX);
    spBox3->setValue(DEGREE_MID);
    spBox3->setMinimum(DEGREE_MIN);

    spBox4->setMaximum(DEGREE_MAX);
    spBox4->setValue(DEGREE_MID);
    spBox4->setMinimum(DEGREE_MIN);

    lbl1 = new QLabel("Base");
    lbl2 = new QLabel("Shoulder");
    lbl3 = new QLabel("Elbow");
    lbl4 = new QLabel("Wrist");
    statusLbl = new QLabel("Connection status...");

    setPortLine = new QLineEdit;
    setPortLine->setPlaceholderText("Set COM-port number...");

    setPortButton = new QPushButton;
    setPortButton->setDefault(true);
    setPortButton->setText("Connect");

    closePortButton = new QPushButton;
    closePortButton->setText("Disconnect");

    layout = new QGridLayout;

    layout->addWidget(statusLbl, 5, 10, 5, 20);
    layout->addWidget(setPortLine, 5, 30, 5, 5);
    layout->addWidget(setPortButton, 5, 40, 5, 5 );
    layout->addWidget(closePortButton, 5, 50, 5, 5 );

    layout->addWidget(lbl1, 20, 10, 10, 5);
    layout->addWidget(spBox1, 20, 20, 10, 5);
    layout->addWidget(slide1, 20, 30, 10, 30);

    layout->addWidget(lbl2, 30, 10, 10, 5);
    layout->addWidget(spBox2, 30, 20, 10, 5);
    layout->addWidget(slide2, 30, 30, 10, 30);

    layout->addWidget(lbl3, 40, 10, 10, 5);
    layout->addWidget(spBox3, 40, 20, 10, 5);
    layout->addWidget(slide3, 40, 30, 10, 30);

    layout->addWidget(lbl4, 50, 10, 10, 5);
    layout->addWidget(spBox4, 50, 20, 10, 5);
    layout->addWidget(slide4, 50, 30, 10, 30);

    setLayout(layout);

    connect(spBox1,SIGNAL(valueChanged(int)), slide1, SLOT(setValue(int)));
    connect(spBox2,SIGNAL(valueChanged(int)), slide2, SLOT(setValue(int)));
    connect(spBox3,SIGNAL(valueChanged(int)), slide3, SLOT(setValue(int)));
    connect(spBox4,SIGNAL(valueChanged(int)), slide4, SLOT(setValue(int)));

    connect(slide1,SIGNAL(valueChanged(int)), spBox1, SLOT(setValue(int)));
    connect(slide2,SIGNAL(valueChanged(int)), spBox2, SLOT(setValue(int)));
    connect(slide3,SIGNAL(valueChanged(int)), spBox3, SLOT(setValue(int)));
    connect(slide4,SIGNAL(valueChanged(int)), spBox4, SLOT(setValue(int)));
}

void MainWindow::SetCOMPort()
{
        QString strng = setPortLine->text();
        int numPort = strng.toInt();

        statusLbl->setText("Trying to open COM-port "+numPort);

        bool b = serial->Open(numPort, 9600);
        if(!b)
        {
            statusLbl->setText("Error open COM-port");
            statusLbl->setStyleSheet("color: red;"
                                     "selection-color: black;"
                                     "selection-background-color: red;");
        }
        else
        {
            statusLbl->setText("Success!");
            statusLbl->setStyleSheet("color: green;"
                                     "selection-color: white;"
                                     "selection-background-color: grey;");
        }
}

void MainWindow::CloseCOMPort()
{
    serial->Close();
    serial->Clean();
    delete serial;

    statusLbl->setStyleSheet("color: default;"
                             "selection-color: default;"
                             "selection-background-color: default;");
    statusLbl->setText("Port has been closed");
}

void MainWindow::SetDegree1(int value)
{
            char buf[3];
            buf[0] = 0xE0 | 8;
            buf[1] = value & 0x7F;
            buf[2] = (value >> 8) & 0x7F;
            serial->Send(buf, 3);

            Sleep(200);
}

void MainWindow::SetDegree2(int value)
{
            char buf[3];
            buf[0] = 0xE0 | 9;
            buf[1] = value & 0x7F;
            buf[2] = (value >> 9) & 0x7F;
            serial->Send(buf, 3);

            Sleep(200);
}

void MainWindow::SetDegree3(int value)
{
            char buf[3];
            buf[0] = 0xE0 | 10;
            buf[1] = value & 0x7F;
            buf[2] = (value >> 10) & 0x7F;
            serial->Send(buf, 3);

            Sleep(200);
}

void MainWindow::SetDegree4(int value)
{
            char buf[3];
            buf[0] = 0xE0 | 11;
            buf[1] = value & 0x7F;
            buf[2] = (value >> 11) & 0x7F;
            serial->Send(buf, 3);

            Sleep(200);
}
