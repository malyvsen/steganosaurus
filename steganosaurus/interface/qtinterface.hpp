#ifndef QTINTERFACE_H
#define QTINTERFACE_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QCheckBox>
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

    QCheckBox *checkboxMode;

    QString dataPath;
    QString carrierPath;
    QString outputPath;

private slots:
    void OnButtonDataPathSlot();
    void OnButtonCarrierPathSlot();
    void OnButtonOutputPathSlot();
    void OnButtonEncodeSlot();

};

#endif // QTINTERFACE_H
