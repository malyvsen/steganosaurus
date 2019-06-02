#include "qtinterface.hpp"
#include "QString"
#include "QFileDialog"
#include "QDesktopWidget"
#include <iostream>

QtInterface::QtInterface(Arguments **args, QWidget *parent)
    : arg(args),
      QMainWindow(parent)
{
    QDesktopWidget dw;
    int x=dw.width()*0.7;
    int y=dw.height()*0.7;
    this->setFixedSize(x,y);

    buttonDataPath = new QPushButton("DataPath", this);
    buttonDataPath->setGeometry(0,0,100,40);

    buttonCarrierPath = new QPushButton("CarrierPath", this);
    buttonCarrierPath->setGeometry(0,40,100,40);

    buttonOutputPath = new QPushButton("OutputPath", this);
    buttonOutputPath->setGeometry(0,80,100,40);

    buttonEncode = new QPushButton("Encode", this);
    buttonEncode->setEnabled(false);
    buttonEncode->setGeometry(400,120,100,40);


    QFont minFont("Arial", 16, QFont::Bold);
    labelDataPath = new QLabel(this);
    labelDataPath->setGeometry(QRect(100,0,1500,40));
    labelDataPath->setFont(minFont);
    labelDataPath->setText("labelDataPath");

    labelCarrierPath = new QLabel(this);
    labelCarrierPath->setGeometry(QRect(100,40,1500,40));
    labelCarrierPath->setFont(minFont);
    labelCarrierPath->setText("labelCarrierPath");

    labelOutputPath = new QLabel(this);
    labelOutputPath->setGeometry(QRect(100,80,1500,40));
    labelOutputPath->setFont(minFont);
    labelOutputPath->setText("labelOutputPath");

    checkboxMode = new QCheckBox("Hide", this);
    checkboxMode->setGeometry(200,120,100,40);
    checkboxMode->setFont(minFont);


    connect(buttonCarrierPath, SIGNAL(released()), this, SLOT(OnButtonCarrierPathSlot()));
    connect(buttonDataPath, SIGNAL(released()), this, SLOT(OnButtonDataPathSlot()));
    connect(buttonOutputPath, SIGNAL(released()), this, SLOT(OnButtonOutputPathSlot()));
    connect(buttonEncode, SIGNAL(released()), this, SLOT(OnButtonEncodeSlot()));
    connect(checkboxMode, SIGNAL(toggled(bool)), this, SLOT(OncheckboxModeSlot()));
}

bool QtInterface::CheckIfEcodeButtonShouldBeEnabled()
{
    if(carrierPath.isEmpty() || outputPath.isEmpty())
    {
        return false;
    }
    if(dataPath.isEmpty() && checkboxMode->isChecked())
    {
        return false;
    }
    return true;
}

void QtInterface::OnButtonDataPathSlot()
{
    dataPath = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    "/home",
                                                    tr("File (*.*)"));
    labelDataPath->setText(dataPath);
    buttonEncode->setEnabled(CheckIfEcodeButtonShouldBeEnabled());
}

void QtInterface::OnButtonCarrierPathSlot()
{
    carrierPath = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    "/home",
                                                    tr("Images (*.jpg)"));
    labelCarrierPath->setText(carrierPath);
    buttonEncode->setEnabled(CheckIfEcodeButtonShouldBeEnabled());
}

void QtInterface::OnButtonOutputPathSlot()
{
    outputPath =  QFileDialog::getSaveFileName(this, tr("Save File"),
                                                                 "",
                                                                 tr("File (*.*)"));
    labelOutputPath->setText(outputPath);
    buttonEncode->setEnabled(CheckIfEcodeButtonShouldBeEnabled());
}

void QtInterface::OnButtonEncodeSlot()
{
    Arguments::Mode temp;
    if(checkboxMode->isChecked())
        temp = Arguments::Mode::write;
    else
        temp = Arguments::Mode::read;
    *arg = new Arguments(temp,carrierPath.toStdString(),outputPath.toStdString(),dataPath.toStdString());
    this->close();
}

void QtInterface::OncheckboxModeSlot()
{
    buttonEncode->setEnabled(CheckIfEcodeButtonShouldBeEnabled());
}
