#include "setting.h"
#include "ui_setting.h"

Setting::Setting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Setting)
{
    ui->setupUi(this);
//    connect(ui->btn_confirm,SIGNAL(clicked()),this,SLOT(on_btn_confirm_clicked()));
    ui->cbsave_dir->setText(basesavepath);
    ui->ctsave_dir->setText(basesavepath);
    connect(ui->btn_quit,&QPushButton::clicked,this,[=](){
        this->hide();
    });
}

Setting::~Setting()
{
    delete ui;
}

const QString &Setting::getCb_path() const
{
    return cb_path;
}

void Setting::setCb_path(const QString &newCb_path)
{
    cb_path = newCb_path;
}

const QString &Setting::getCb_savepath() const
{
    return cb_savepath;
}

void Setting::setCb_savepath(const QString &newCb_savepath)
{
    cb_savepath = newCb_savepath;
}

const QString &Setting::getCt_path() const
{
    return ct_path;
}

void Setting::setCt_path(const QString &newCt_path)
{
    ct_path = newCt_path;
}

const QString &Setting::getCt_savepath() const
{
    return ct_savepath;
}

void Setting::setCt_savepath(const QString &newCt_savepath)
{
    ct_savepath = newCt_savepath;
}

bool Setting::isInvalidPath(const QString &path)
{
    QDir dir(path);
    return dir.exists();
}

bool Setting::isLegalPath(const QString &path)
{
    QDir dir(path);
    return dir.isAbsolutePath(path);
}

void Setting::on_btn_confirm_clicked()
{
    if(isInvalidPath(ui->cb_dir->text())&&isInvalidPath(ui->ct_dir->text())&&!ui->ct_dir->text().isEmpty()&&!ui->cb_dir->text().isEmpty()){
        setCb_path(ui->cb_dir->text());
        setCt_path(ui->ct_dir->text());
        QFileInfo fileInfo(ui->cb_dir->text());
        QString fileName = fileInfo.fileName();
        qDebug()<<ui->cbsave_dir->text();
        qDebug()<<fileName;
        setCb_savepath(basesavepath+fileName+'\\'+"trianA\\");
        setCt_savepath(basesavepath+fileName+'\\'+"trianB\\");
        ui->cbsave_dir->setText(basesavepath+fileName+'\\'+"trianA\\");
        ui->ctsave_dir->setText(basesavepath+fileName+'\\'+"trianB\\");
         QMessageBox::information(this,"提示","设置成功");
         this->hide();
        emit mysignal();
    }
    else{
        QMessageBox::warning(this,"警告","输入非法路径,重新输入");
    }



}

