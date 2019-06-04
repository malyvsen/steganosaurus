#ifndef QTINTERFACE_H
#define QTINTERFACE_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QGroupBox>
#include <QRadioButton>
#include <interface/arguments.hpp>

class QtInterface: public QMainWindow
{
     Q_OBJECT
public:
    QtInterface(Arguments **args, QWidget *parent = 0);
private:
    Arguments **arg;

    QLabel *labelDataPath;
    QLabel *labelCarrierPath;
    QLabel *labelOutputPath;
    QPushButton *buttonDataPath;
    QPushButton *buttonCarrierPath;
    QPushButton *buttonOutputPath;
    QPushButton *buttonEncode;

    QGroupBox *groupBox;

    QRadioButton *radio1;
    QRadioButton *radio2;
    QRadioButton *radio3;



    QString dataPath;
    QString carrierPath;
    QString outputPath;

    bool CheckIfEcodeButtonShouldBeEnabled();


private slots:
    void OnButtonDataPathSlot();
    void OnButtonCarrierPathSlot();
    void OnButtonOutputPathSlot();
    void OnButtonEncodeSlot();
    void OncheckboxModeSlot();

};

#endif // QTINTERFACE_H
