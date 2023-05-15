#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->action_setting,&QAction::triggered,this,[=](){
        set.setWindowModality(Qt::ApplicationModal); // 设置为应用程序级别的模态对话框
        set.show();
    });
    connect(&set,SIGNAL(mysignal()),this,SLOT(viewinit()));
    ui->ct_img->setScene(ctscene);
    ui->cbct_img->setScene(cbscene);
//    connect(ui->btnCtDown,SIGNAL(clicked()),this,SLOT(on_btnCtDown_clicked()));
//    connect(ui->btnCtUp,SIGNAL(clicked()),this,SLOT(on_btnCtUp_clicked()));
//    connect(ui->btnCbDown,SIGNAL(clicked()),this,SLOT(on_btnCbDown_clicked()));
//    connect(ui->btnCbUp,SIGNAL(clicked()),this,SLOT(on_btnCbUp_clicked()));
//    viewinit();

//    ui->ct_img->show();
//    ui->cbct_img->show();
    this->show();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setCbview_dir(const QString &newCbview_dir)
{
    cbview_dir = newCbview_dir;
}

void MainWindow::setCbsave_dir(const QString &newCbsave_dir)
{
    cbsave_dir = newCbsave_dir;
}

void MainWindow::setCtview_dir(const QString &newCtview_dir)
{
    ctview_dir = newCtview_dir;
}

void MainWindow::setCtsave_dir(const QString &newCtsave_dir)
{
    ctsave_dir = newCtsave_dir;
}

void MainWindow::setCbindex(int newCbindex)
{
    cbindex = newCbindex;
}

int MainWindow::getCbindex() const
{
    return cbindex;
}

int MainWindow::getCtindex() const
{
    return ctindex;
}

void MainWindow::setCtindex(int newCtindex)
{
    ctindex = newCtindex;
}

void MainWindow::viewinit()
{
    ctpixmaps.clear();
    cbpixmaps.clear();
    cbview_dir = set.getCb_path();
    ctview_dir = set.getCt_path();
    cbsave_dir = set.getCb_savepath();
    ctsave_dir = set.getCt_savepath();
    qDebug()<<cbview_dir;
    QDir ctdir(ctview_dir);
    ctdir.setFilter(QDir::Files | QDir::NoDotAndDotDot);
    ctdir.setNameFilters(QStringList() << "*.bmp");
    QList<QFileInfo> ctfiles = ctdir.entryInfoList();

    for (int i = 0; i < ctfiles.count(); i++) {
        QPixmap pixmap(ctfiles[i].absoluteFilePath());
        QGraphicsPixmapItem* pixmapItem = new QGraphicsPixmapItem(pixmap);
        ctpixmaps.append(pixmapItem);
    }

    QDir dir(cbview_dir);
    dir.setFilter(QDir::Files | QDir::NoDotAndDotDot);
    dir.setNameFilters(QStringList() << "*.bmp");
    files = dir.entryInfoList();

    for (int i = 0; i < files.count(); i++) {
        QPixmap pixmap(files[i].absoluteFilePath());
        QGraphicsPixmapItem* pixmapItem = new QGraphicsPixmapItem(pixmap);
        cbpixmaps.append(pixmapItem);
    }
    init();
    img_show(cbscene,"cb",cbindex);
    img_show(ctscene,"ct",ctindex);

}


void MainWindow::img_show(QGraphicsScene *  scene, const QString type,  int index)
{
//    scene->clear();
    if(type=="cb"){
        if(cbpixmaps[index]->scene()!=nullptr)
            scene->removeItem(cbpixmaps[index]);
        scene->addItem(cbpixmaps[index]);
//        ui->cbct_img->show();
    }
    else{
        if(ctpixmaps[index]->scene()!=nullptr)
            scene->removeItem(ctpixmaps[index]);
      scene->addItem(ctpixmaps[index]);
//         ui->ct_img->show();
    }
//    if(type =="cb"){
//        qDebug()<<"fuck";
//    }
//            scene->addItem(cbpixmaps[index]);
//             ui->cbct_img->show();
    qDebug()<<cbindex;
    qDebug()<<ctindex;
}

void MainWindow::init()
{
    cbindex=0;
    ctindex=0;
}




void MainWindow::on_btnCbUp_clicked()
{
    if(cbindex<1){
        QMessageBox::warning(this,"警告","到头啦" );
        cbindex=0;
    }

    else {

        img_show(cbscene,"cb",--cbindex);

    }




}


void MainWindow::on_btnCbDown_clicked()
{
    if(cbindex>=cbpixmaps.count()-1){
        QMessageBox::warning(this,"警告","到头啦" );
        cbindex=cbpixmaps.count()-1;

    }
    else {
        img_show(cbscene,"cb",++cbindex);
    }
}


void MainWindow::on_btnCtUp_clicked()
{
    if(ctindex<1){
        QMessageBox::warning(this,"警告","到头啦" );
        ctindex=0;
    }

    else {

        img_show(ctscene,"ct",--ctindex);
    }

}


void MainWindow::on_btnCtDown_clicked()
{
    if(ctindex>=ctpixmaps.count()-1){
        QMessageBox::warning(this,"警告","到头啦" );
        ctindex=ctpixmaps.count()-1;

    }
    else {
       img_show(ctscene,"ct",++ctindex);
    }
}


void MainWindow::on_btn_pair_clicked()
{
    QDir dir;
    if (dir.mkpath(cbsave_dir)) {
        qDebug() << "文件夹创建成功：" << cbsave_dir;
    } else {
        qDebug() << "文件夹创建失败：" << cbsave_dir;
    }
    if (dir.mkpath(ctsave_dir)) {
        qDebug() << "文件夹创建成功：" << cbsave_dir;
    } else {
        qDebug() << "文件夹创建失败：" << cbsave_dir;
    }
    QFile sourceFile1(files[cbindex].absoluteFilePath());
    QFileInfo fileInfo1(sourceFile1);
    QString fileName1 = fileInfo1.completeBaseName();  // 获取文件名

    bool success1 = sourceFile1.copy(cbsave_dir +  fileName1+".bmp");
    QFile sourceFile2(files[ctindex].absoluteFilePath());
    QFileInfo fileInfo2(sourceFile2);
    QString fileName2 = fileInfo2.completeBaseName();  // 获取文件名

    bool success2 = sourceFile1.copy(ctsave_dir + fileName1+'-'+fileName2+".bmp");

    if(success1&&success2){
        QMessageBox::information(this,"成功","配对成功");

    }
    else{
        QMessageBox::warning(this,"错误","配对失败");
    }
}

