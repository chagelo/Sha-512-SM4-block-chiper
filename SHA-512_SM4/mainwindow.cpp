#include "mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_save_clicked()
{

}

void MainWindow::on_select_file_clicked()
{
    string lspath = "D:/";
    string filename = QFileDialog::getOpenFileName(this, tr("Open"), QString::fromStdString(lspath)).toStdString();
    ui->file->setText(QString::fromStdString(filename));
}

void MainWindow::on_encrypt_clicked()
{

    QString q_encry_file = ui->file->text();
    if (q_encry_file.isEmpty()) {
        QMessageBox::information(this, tr("WARNING"), tr("Encrypted file is empty!"));
        return;
    }


    QString q_pwd = ui->pwd->text();
    if (q_pwd.isEmpty()){
        QMessageBox::information(this, tr("WARNING"), tr("Password is empty!"));
        return;
    }


    string lspath = "D:/";
    QString qsavefile = QFileDialog::getOpenFileName(this, tr("Save"), QString(str2qstr(lspath)));
    string savefile = qstr2str(qsavefile);


    if(!savefile.empty()){
        string encry_file = qstr2str(q_encry_file);
        string pwd = qstr2str(q_pwd);
        string mode = qstr2str(ui->model->currentText());

        auto startTime_all = std::chrono::high_resolution_clock::now();
        SM4::encrypt(pwd, encry_file, savefile, mode);
        auto endTime_all = std::chrono::high_resolution_clock::now();
        auto x_all = std::chrono::duration_cast<std::chrono::milliseconds>(endTime_all - startTime_all).count();

        ui->statusbar->showMessage("加密成功, 加密时间: " + QString::number(x_all) + "ms");

//        cout << " time of encryption: " << x_all << "ms" << endl;

//        cout << "encrypt successfully" << endl;
    }

    ui->pwd->setText("");
}

void MainWindow::on_decrypt_clicked()
{
    QString q_decry_file = ui->file->text();
    if (q_decry_file.isEmpty()) {
        QMessageBox::information(this, tr("WARNING"), tr("Decrypted file is empty!"));
        return;
    }

    QString q_pwd = ui->pwd->text();
    if (q_pwd.isEmpty()){
        QMessageBox::information(this, tr("WARNING"), tr("Password is empty!"));
        return;
    }

    string lspath = "D:/";
    QString qsavefile = QFileDialog::getOpenFileName(this, tr("Save"), str2qstr(lspath));
    string savefile = qstr2str(qsavefile);


    qDebug() << q_decry_file <<"  ";
    cout << savefile << endl;
    if (!savefile.empty()){
        string decry_file = qstr2str(q_decry_file);
        string pwd = qstr2str(q_pwd);
        string mode = qstr2str(ui->model->currentText());

        auto startTime_all = std::chrono::high_resolution_clock::now();
        SM4::decrypt(pwd, decry_file, savefile, mode);
        auto endTime_all = std::chrono::high_resolution_clock::now();
        auto x_all = std::chrono::duration_cast<std::chrono::milliseconds>(endTime_all - startTime_all).count();
        ui->statusbar->showMessage("解密成功, 解密时间: " + QString::number(x_all) + "ms");
//        cout << " time of decryption: " << x_all << "ms" << endl;


//        cout << "decrypt successfully" << endl;
    }

}

QString MainWindow::str2qstr(const std::string str)
{
    return QString::fromLocal8Bit(str.data());
}

std::string MainWindow::qstr2str(const QString qstr)
{
    QByteArray cdata = qstr.toLocal8Bit();
    return string (cdata);
}
