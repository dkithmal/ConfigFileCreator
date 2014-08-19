#ifndef CONFIGCREATOR_H
#define CONFIGCREATOR_H

#include <QWidget>
#include <QDialog>
#include <QString>
#include <QFile>
#include <QtXml>
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>

namespace Ui {
class ConfigCreator;
}

class ConfigCreator : public QDialog
{
    Q_OBJECT
    
public:
    explicit ConfigCreator(QWidget *parent = 0);
    ~ConfigCreator();
    
private:
    Ui::ConfigCreator *ui;
    QString configFileName;
    QString templateName;
    QString templateClass;
    QString templatetag;
    QString csvFilePath;
    QString configFileSavePath;
    int fieldNamePosition;
    int dataTypePosition;

private slots:
    void csvFileSelectClicked();
    void configFileSavePathClicked();
    void genarateButtonClicked();
};

#endif // CONFIGCREATOR_H
