#include "qtinterface.hpp"
#include "QString"
#include "QFileDialog"
#include "QDesktopWidget"
#include <QVBoxLayout>
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
    buttonEncode->setGeometry(400,200,100,40);


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

    groupBox = new QGroupBox(tr("Choose mode"), this);
    groupBox->setGeometry(0,160,150,150);
    radio1 = new QRadioButton(tr("Encode"));
    radio1->setFont(minFont);
    radio2 = new QRadioButton(tr("Decode"));
    radio2->setFont(minFont);
    radio3 = new QRadioButton(tr("Clear"));
    radio3->setFont(minFont);
    radio1->setChecked(true);

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(radio1);
    vbox->addWidget(radio2);
    vbox->addWidget(radio3);
    vbox->addStretch(1);
    groupBox->setLayout(vbox);

    connect(buttonCarrierPath, SIGNAL(released()), this, SLOT(OnButtonCarrierPathSlot()));
    connect(buttonDataPath, SIGNAL(released()), this, SLOT(OnButtonDataPathSlot()));
    connect(buttonOutputPath, SIGNAL(released()), this, SLOT(OnButtonOutputPathSlot()));
    connect(buttonEncode, SIGNAL(released()), this, SLOT(OnButtonEncodeSlot()));
    connect(radio1, SIGNAL(toggled(bool)), this, SLOT(OncheckboxModeSlot()));
    connect(radio2, SIGNAL(toggled(bool)), this, SLOT(OncheckboxModeSlot()));
    connect(radio3, SIGNAL(toggled(bool)), this, SLOT(OncheckboxModeSlot()));
}

bool QtInterface::CheckIfEcodeButtonShouldBeEnabled()
{
    if(carrierPath.isEmpty() || outputPath.isEmpty())
    {
        return false;
    }
    if(dataPath.isEmpty() && radio1->isChecked())
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

    if(radio1->isChecked())
        temp = Arguments::Mode::write;
    if(radio2->isChecked())
        temp = Arguments::Mode::read;
    if(radio3->isChecked())
        temp = Arguments::Mode::clear;

    *arg = new Arguments(temp,carrierPath.toStdString(),outputPath.toStdString(),dataPath.toStdString());
    this->close();
}

void QtInterface::OncheckboxModeSlot()
{
    if(radio1->isChecked())
    {
        buttonEncode->setText("Encode");
        buttonDataPath->show();
        labelDataPath->show();
    }
    if(radio2->isChecked())
    {
        buttonEncode->setText("Decode");
        buttonDataPath->hide();
        labelDataPath->hide();
    }
    if(radio3->isChecked())
    {
        buttonEncode->setText("Clear");
        buttonDataPath->hide();
        labelDataPath->hide();
    }

    buttonEncode->setEnabled(CheckIfEcodeButtonShouldBeEnabled());
}
