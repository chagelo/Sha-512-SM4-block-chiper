#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>
#include <QTextCodec>
#include "ui_mainwindow.h"
#include "SM4.h"

using std::string;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_select_file_clicked();

    void on_save_clicked();

    void on_encrypt_clicked();

    void on_decrypt_clicked();
    QString str2qstr(const string str);

    string qstr2str(const QString qstr);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
