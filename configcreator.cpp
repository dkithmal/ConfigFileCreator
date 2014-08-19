#include "configcreator.h"
#include "ui_configcreator.h"

ConfigCreator::ConfigCreator(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigCreator)
{
   ui->setupUi(this);
   fieldNamePosition=0;
   dataTypePosition=0;
}

ConfigCreator::~ConfigCreator()
{
    delete ui;
}


void ConfigCreator::csvFileSelectClicked()
{

   csvFilePath = QFileDialog::getOpenFileName(this, tr("Select CSV file"),"D:/dk work/Motarola");
   ui->lECSVFile->setText(csvFilePath);


}

void ConfigCreator::configFileSavePathClicked()
{
    configFileSavePath=QFileDialog::getExistingDirectory(this, tr("Select Save Directry"),"D:/dk work/Motarola");
    ui->lESaveTo->setText(configFileSavePath);

}


void ConfigCreator::genarateButtonClicked()
{

    configFileName=ui->lEConfigFileName->text();
    templateName=ui->lETemplateName->text();
    templateClass=ui->lETemplateClass->text();
    templatetag=ui->lETemplateTag->text();




    QFile newConfigFile(configFileSavePath+"/"+configFileName);
    if(!newConfigFile.open(QFile::ReadWrite| QIODevice::Text))
    {
        qDebug()<<"error";

    }
    else
    {
        QDomDocument document;
        document.setContent(&newConfigFile);

        QDomElement root= document.createElement("Template");
        root.setAttribute("name",templateName);
        root.setAttribute("class",templateClass);
        root.setAttribute("format","1");


        QDomElement tag= document.createElement("Tag");
        tag.appendChild(document.createTextNode(templatetag));

        QDomElement templateGroup= document.createElement("TemplateGroup");
        templateGroup.appendChild(document.createTextNode(templateClass));

        QDomElement connection= document.createElement("Connection");

        QDomElement expression= document.createElement("Expression");

        QDomElement transportOnlyUsedCols= document.createElement("TransportOnlyUsedCols");
        transportOnlyUsedCols.appendChild(document.createTextNode("false"));

        QDomElement priorityObj= document.createElement("PriorityObj");
        priorityObj.appendChild(document.createTextNode("false"));

        QDomElement defaultSortOrder= document.createElement("DefaultSortOrder");

        QDomElement columns= document.createElement("Columns");







        QFile file(csvFilePath);
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        QTextStream in(&file);
        in.setCodec("UTF-8"); // change the file codec to UTF-8.
        int x=0;
        while(!in.atEnd())
        {
            QString line = in.readLine();

            if(x==3)
            {
                QStringList splitedList=line.split(",");
                for(int y=0;y<splitedList.size();y++)
                {
                    if(splitedList.at(y)=="Field Name")
                        fieldNamePosition=y;

                     if(splitedList.at(y)=="Data Type")
                         dataTypePosition=y;
                }
            }


            if(x>4)
            {
                QDomElement column= document.createElement("Column");
                if(line.length()>0)
                {
                    QStringList splitedColumnData=line.split(",");


                        column.setAttribute("name",splitedColumnData.at(fieldNamePosition));
                        column.setAttribute("dataType",splitedColumnData.at(dataTypePosition));
                        column.setAttribute("description","");
                        column.setAttribute("alwaysTx","false");
                        column.setAttribute("unicode","false");
                        column.setAttribute("translate","false");
                        column.setAttribute("enum","");

                        columns.appendChild(column);

                }



            }

             x++;
        }


        root.appendChild(tag);
        root.appendChild(templateGroup);
        root.appendChild(connection);
        root.appendChild(expression);
        root.appendChild(transportOnlyUsedCols);
        root.appendChild(priorityObj);
        root.appendChild(columns);
        root.appendChild(defaultSortOrder);


        document.appendChild(root);
        QTextStream stream(&newConfigFile);
        stream <<document.toString();
        newConfigFile.close();
    }





}


