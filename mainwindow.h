#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<setting.h>
#include<QGraphicsPixmapItem>
#include<QGraphicsScene>
#include<QMessageBox>
#include <QKeyEvent>
#include <QMouseEvent>
#include<QDebug>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setCbview_dir(const QString &newCbview_dir);

    void setCbsave_dir(const QString &newCbsave_dir);

    void setCtview_dir(const QString &newCtview_dir);

    void setCtsave_dir(const QString &newCtsave_dir);

    void setCbindex(int newCbindex);

    int getCbindex() const;

    int getCtindex() const;
    void setCtindex(int newCtindex);

    void img_show(QGraphicsScene * scene,const QString type,int index);
    void init();
    bool eventFilter(QObject *obj, QEvent *event) override;

private slots:
    void on_btnCbUp_clicked();

    void on_btnCbDown_clicked();

    void on_btnCtUp_clicked();

    void on_btnCtDown_clicked();
    void viewinit();


    void on_btn_pair_clicked();

private:
    QList<QFileInfo> cbfiles;
    QList<QFileInfo> ctfiles;
    Ui::MainWindow *ui;
    Setting set;
    QString cbview_dir;
    QString cbsave_dir;
    QString ctview_dir;
    QString ctsave_dir;
    int cbindex=0;
    int ctindex=0;
    QList<QGraphicsPixmapItem*> ctpixmaps;
    QList<QGraphicsPixmapItem*> cbpixmaps;
    QList<QString> cbfilename;
    QList<QString> ctfilename;
    QGraphicsScene *ctscene=new QGraphicsScene;
    QGraphicsScene *cbscene=new QGraphicsScene;
};
#endif // MAINWINDOW_H
