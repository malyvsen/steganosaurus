#include "qtinterface.hpp"
#include "QString"
#include "QFileDialog"
#include <iostream>

QtInterface::QtInterface(Arguments **args, QWidget *parent)
    : arg(args),
      QMainWindow(parent)
{
    buttonDataPath = new QPushButton("DataPath", this);
    buttonDataPath->setGeometry(0,0,100,40);

    buttonCarrierPath = new QPushButton("CarrierPath", this);
    buttonCarrierPath->setGeometry(0,40,100,40);

    buttonOutputPath = new QPushButton("OutputPath", this);
    buttonOutputPath->setGeometry(0,80,100,40);

    buttonEncode = new QPushButton("Encode", this);
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
}

void QtInterface::OnButtonDataPathSlot()
{
    dataPath = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    "/home",
                                                    tr("File (*.*)"));
    labelDataPath->setText(dataPath);
}

void QtInterface::OnButtonCarrierPathSlot()
{
    carrierPath = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    "/home",
                                                    tr("Images (*.jpg)"));
    labelCarrierPath->setText(carrierPath);
}

void QtInterface::OnButtonOutputPathSlot()
{
    outputPath =  QFileDialog::getSaveFileName(this, tr("Save File"),
                                                                 "",
                                                                 tr("File (*.*)"));
    labelOutputPath->setText(outputPath);
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
