#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <Serial.h>

#include <QDialog>
#include <QApplication>
#include <QSlider>
#include <QSpinBox>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QWindow>

class MainWindow : public QDialog
{
     Q_OBJECT
public:
    MainWindow(QWidget *parent=0);

    QLabel *statusLbl;
    QPushButton *setPortButton;
    QPushButton *closePortButton;
    QLineEdit *setPortLine;

    QSpinBox *spBox1;
    QSpinBox *spBox2;
    QSpinBox *spBox3;
    QSpinBox *spBox4;

private:

    QSlider *slide1;
    QSlider *slide2;
    QSlider *slide3;
    QSlider *slide4;

    QLabel *lbl1;
    QLabel *lbl2;
    QLabel *lbl3;
    QLabel *lbl4;

    QGridLayout *layout;

public slots:

    void SetCOMPort();
    void CloseCOMPort();

    void SetDegree1(int value);
    void SetDegree2(int value);
    void SetDegree3(int value);
    void SetDegree4(int value);


};

#endif // MAINWINDOW_H
