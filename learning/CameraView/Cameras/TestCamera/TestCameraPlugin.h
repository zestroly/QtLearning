#ifndef GENERICPLUGIN_H
#define GENERICPLUGIN_H

#include <QGenericPlugin>
#include "../../View/CameraBasePlugin.h"
#include <QDir>



class TestCamera :  public QObject, public CameraBasePlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QGenericPluginFactoryInterface" CameraBase_IID FILE "TestCamera.json")
    Q_INTERFACES(CameraBasePlugin)

public:
    class CameraTest: public CameraDevice
    {
        public:
            CameraTest();
            bool Start();
            bool Stop();
            bool Open();
            bool Close();
            bool GetOneImage(QImage &img, int timeout = 1000);
            bool SetParameter(const QString Key, const QString Value);
            bool GetParameter(const QString Key, QString &Value);

            bool GetParameterList(QStringList & keys);

        private:
            QString _DirPath;
            QDir *_Dir;
            QStringList _files;
            QStringList::iterator _it;
    };


    CameraDevice *operator[](int index);
    int CameraNumber();
    bool Discover();

private:
    QList<CameraDevice*> _Cameras;

};
#endif // GENERICPLUGIN_H
