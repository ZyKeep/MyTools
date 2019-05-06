#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "JQFile/JQFile.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

#include   <QDebug>
void MainWindow::on_pushButton_clicked()
{
    QString className = ui->lineEdit_for_creat_class->text();
    QString path ="E:file";
    QString spath = "E:creat";
    QDir dir(path);
    dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    dir.setSorting(QDir::Size | QDir::Reversed);

    QFileInfoList list = dir.entryInfoList();

    for (int i = 0; i < list.size(); ++i) {
        QFileInfo fileInfo = list.at(i);
        QString filePath = fileInfo.filePath();
        QString sousepath = filePath.replace(path,spath);
        sousepath = filePath.replace("%classname%", className.toUtf8().toLower());

        qDebug()<<"sousepath = "<<sousepath;



        JQFile::writeFile( sousepath, QByteArray::fromHex( "efbbbf" )
                           + this->getTemplateData( fileInfo.filePath(), "macroProtectsPrefix", className ).toUtf8() );

    }
}

/*******************************
 * @input:
 *
 * @result: 对文本内容进行替换
 *******************************/
QString MainWindow::getTemplateData(
        const QString &templateFilePath,
        const QString &macroProtectsPrefix,
        const QString &className
        )
{
    auto readFileReply = JQFile::readFile( templateFilePath );
    if ( !readFileReply.first ) { return { }; }

    readFileReply.second = readFileReply.second.replace( "%classname%", className.toUtf8().toLower() );
    readFileReply.second = readFileReply.second.replace( "%ClassName%", className.toUtf8() );
    readFileReply.second = readFileReply.second.replace( "%CLASSNAME%", className.toUtf8().toUpper() );

    return readFileReply.second;
}
