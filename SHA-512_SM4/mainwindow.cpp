#include "mainwindow.h"


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
    }


    QString q_pwd = ui->pwd->text();
    if (q_pwd.isEmpty()){
        QMessageBox::information(this, tr("WARNING"), tr("Password is empty!"));
    }


    string lspath = "D:/";
    string savefile = QFileDialog::getOpenFileName(this, tr("Save"), QString::fromStdString(lspath)).toStdString();
    if(!savefile.empty()){
        string encry_file = q_encry_file.toStdString();
        string pwd = q_pwd.toStdString();
        string mode = ui->model->currentText().toStdString();

        auto startTime_all = std::chrono::high_resolution_clock::now();
        SM4::encrypt(pwd, encry_file, savefile, mode);
        auto endTime_all = std::chrono::high_resolution_clock::now();
        auto x_all = std::chrono::duration_cast<std::chrono::milliseconds>(startTime_all - endTime_all).count();
        cout << " time of encryption: " << x_all << endl;

        cout << "encrypt successfully" << endl;
    }

    ui->pwd->setText("");
}

void MainWindow::on_decrypt_clicked()
{
    QString q_decry_file = ui->file->text();
    if (q_decry_file.isEmpty()) {
        QMessageBox::information(this, tr("WARNING"), tr("Decrypted file is empty!"));
    }

    QString q_pwd = ui->pwd->text();
    if (q_pwd.isEmpty()){
        QMessageBox::information(this, tr("WARNING"), tr("Password is empty!"));
    }

    string lspath = "D:/";
    string savefile = QFileDialog::getOpenFileName(this, tr("Save"), QString::fromStdString(lspath)).toStdString();

    if (!savefile.empty()){
        string decry_file = q_decry_file.toStdString();
        string pwd = q_pwd.toStdString();
        string mode = ui->model->currentText().toStdString();

        auto startTime_all = std::chrono::high_resolution_clock::now();
        SM4::decrypt(pwd, decry_file, savefile, mode);
        auto endTime_all = std::chrono::high_resolution_clock::now();
        auto x_all = std::chrono::duration_cast<std::chrono::milliseconds>(startTime_all - endTime_all).count();
        cout << " time of encryption: " << x_all << endl;


        cout << "decrypt successfully" << endl;
    }

}