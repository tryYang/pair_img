#ifndef SETTING_H
#define SETTING_H

#include <QWidget>
#include<QDialog>
#include<QtDebug>
#include<QDir>
#include<QMessageBox>
namespace Ui {
class Setting;
}

class Setting : public QWidget
{
    Q_OBJECT

public:
    explicit Setting(QWidget *parent = nullptr);
    ~Setting();

    const QString &getCb_path() const;
    void setCb_path(const QString &newCb_path);

    const QString &getCb_savepath() const;
    void setCb_savepath(const QString &newCb_savepath);

    const QString &getCt_path() const;
    void setCt_path(const QString &newCt_path);

    const QString &getCt_savepath() const;
    void setCt_savepath(const QString &newCt_savepath);
    bool isInvalidPath(const QString& path);
    bool isLegalPath(const QString& path);
private slots:
    void on_btn_confirm_clicked();
signals:
    void mysignal();

private:
    Ui::Setting *ui;
    QString cb_path;
    QString cb_savepath;
    QString ct_path;
    QString ct_savepath;
    QString basesavepath= R"(D:\Datasets\cbct2ct\配对集\)";
};


#endif // SETTING_H
