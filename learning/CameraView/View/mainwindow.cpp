#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>
#include <QString>
#include <QPluginLoader>
#include <QDebug>
#include <QTextCodec>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QList>
#include <QListIterator>
#include <CameraInfoForm.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(tr("CameraView"));
    setWindowIcon(QIcon("://res/factory_128px.ico"));
    setMinimumSize(QSize(800, 600)); //窗口最小尺寸
    setCentralWidget(ui->tabWidgetMain); //设置为主窗口的中心窗口，会填充MainWindow的窗口

  //  QFile qssfile(":/qss/themeSun/mainTabWidget.qss");
   // qssfile.open(QFile::ReadOnly);
   // ui->tabWidgetMain->setStyleSheet(qssfile.readAll());

    discoverCamera();

    InitHomeWidget();
    showMaximized();

    for(int i = 0; i < _cameraDeviceForm.size(); i++)
    {
        _cameraDeviceForm[i]->InitCamera(_busManager[i]);
    }

    InitCameraWidget();

}


void MainWindow::InitHomeWidget()
{

    QWidget* homeWidget = new QWidget(this);
    ui->tabWidgetMain->addTab(homeWidget,tr("Home"));

    QGridLayout *gridlayout = new QGridLayout(homeWidget);

    CameraDeviceForm* cameraDeviceForm;
    int cameraDeviceNumber = 4;
    int cameraDeviceCols =  (cameraDeviceNumber + 1)/2;
    if(cameraDeviceNumber >=3)
    {
        for(int i = 0, j = 0, k = 0 ; i < cameraDeviceNumber ; i++, j++)
        {
            if(i == cameraDeviceCols)
            {
                j = 0;
                k++;
            }
            gridlayout->setColumnStretch(k, 1);
            gridlayout->setRowStretch(j,1);
            cameraDeviceForm = new  CameraDeviceForm(this);
            gridlayout->addWidget(cameraDeviceForm, k, j);
            _cameraDeviceForm.append(cameraDeviceForm);
        }
    }else{
        if( cameraDeviceNumber >= 1){
            cameraDeviceForm = new  CameraDeviceForm(this);
            gridlayout->addWidget(cameraDeviceForm, 0, 0);
            gridlayout->setColumnStretch(0,1);
            _cameraDeviceForm.append(cameraDeviceForm);
        }
        if( cameraDeviceNumber == 2){
            cameraDeviceForm = new  CameraDeviceForm(this);
            gridlayout->addWidget(cameraDeviceForm, 0, 1);
            gridlayout->setColumnStretch(1,1);
            _cameraDeviceForm.append(cameraDeviceForm);
        }
    }
}


void MainWindow::InitCameraWidget()
{
    QWidget* cameraWidget = nullptr;
    cameraWidget = new QWidget(this);
    ui->tabWidgetMain->addTab(cameraWidget,tr("Camera"));

    QGridLayout *gridlayout = new QGridLayout(cameraWidget);
    gridlayout->addWidget(new CameraInfoForm(_cameraDeviceForm, _busManager, this));

}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::discoverCamera()
{
    _busManager.loadCameraPlugin();
}


