/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLineEdit *file;
    QPushButton *select_file;
    QLineEdit *pwd;
    QLabel *label;
    QLabel *label_2;
    QComboBox *model;
    QLabel *label_3;
    QPushButton *encrypt;
    QPushButton *decrypt;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(608, 244);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        file = new QLineEdit(centralwidget);
        file->setObjectName(QString::fromUtf8("file"));
        file->setGeometry(QRect(120, 40, 331, 31));
        QFont font;
        font.setFamily(QString::fromUtf8("Microsoft YaHei"));
        file->setFont(font);
        select_file = new QPushButton(centralwidget);
        select_file->setObjectName(QString::fromUtf8("select_file"));
        select_file->setGeometry(QRect(480, 40, 93, 31));
        select_file->setFont(font);
        pwd = new QLineEdit(centralwidget);
        pwd->setObjectName(QString::fromUtf8("pwd"));
        pwd->setGeometry(QRect(120, 100, 331, 31));
        pwd->setFont(font);
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(40, 50, 72, 15));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(40, 110, 72, 15));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        model = new QComboBox(centralwidget);
        model->addItem(QString());
        model->addItem(QString());
        model->addItem(QString());
        model->addItem(QString());
        model->addItem(QString());
        model->setObjectName(QString::fromUtf8("model"));
        model->setGeometry(QRect(120, 160, 61, 21));
        model->setFont(font);
        model->setInsertPolicy(QComboBox::InsertAtBottom);
        model->setSizeAdjustPolicy(QComboBox::AdjustToContents);
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(40, 150, 72, 41));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        encrypt = new QPushButton(centralwidget);
        encrypt->setObjectName(QString::fromUtf8("encrypt"));
        encrypt->setGeometry(QRect(360, 160, 93, 31));
        decrypt = new QPushButton(centralwidget);
        decrypt->setObjectName(QString::fromUtf8("decrypt"));
        decrypt->setGeometry(QRect(480, 160, 93, 31));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Arial"));
        decrypt->setFont(font1);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 608, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        select_file->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\346\226\207\344\273\266\357\274\232", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\345\257\206\347\240\201\357\274\232", nullptr));
        model->setItemText(0, QCoreApplication::translate("MainWindow", "ECB", nullptr));
        model->setItemText(1, QCoreApplication::translate("MainWindow", "CBC", nullptr));
        model->setItemText(2, QCoreApplication::translate("MainWindow", "OFB", nullptr));
        model->setItemText(3, QCoreApplication::translate("MainWindow", "CFB", nullptr));
        model->setItemText(4, QCoreApplication::translate("MainWindow", "CTR", nullptr));

        label_3->setText(QCoreApplication::translate("MainWindow", "\346\250\241\345\274\217\357\274\232", nullptr));
        encrypt->setText(QCoreApplication::translate("MainWindow", "\345\212\240\345\257\206", nullptr));
        decrypt->setText(QCoreApplication::translate("MainWindow", "\350\247\243\345\257\206", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
