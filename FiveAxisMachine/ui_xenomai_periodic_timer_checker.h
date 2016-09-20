/********************************************************************************
** Form generated from reading UI file 'xenomai_periodic_timer_checker.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XENOMAI_PERIODIC_TIMER_CHECKER_H
#define UI_XENOMAI_PERIODIC_TIMER_CHECKER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Xenomai_periodic_timer_checker
{
public:
    QWidget *centralwidget;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLabel *label_pic_xeno;
    QLabel *label_7;
    QComboBox *comboBox_checkermode;
    QProgressBar *progressBar;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QLineEdit *checking_sampling_time;
    QLabel *label;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_3;
    QLineEdit *checking_sampling_time_2;
    QLabel *label_5;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_4;
    QLineEdit *checking_sampling_time_3;
    QLabel *label_6;
    QPushButton *pushButton_stop2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Xenomai_periodic_timer_checker)
    {
        if (Xenomai_periodic_timer_checker->objectName().isEmpty())
            Xenomai_periodic_timer_checker->setObjectName(QStringLiteral("Xenomai_periodic_timer_checker"));
        Xenomai_periodic_timer_checker->resize(554, 321);
        Xenomai_periodic_timer_checker->setStyleSheet(QStringLiteral(""));
        centralwidget = new QWidget(Xenomai_periodic_timer_checker);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(440, 20, 99, 27));
        pushButton->setStyleSheet(QLatin1String("background-color: rgb(70, 70, 70);\n"
"color: rgb(180, 180, 180);"));
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(440, 60, 99, 27));
        pushButton_2->setStyleSheet(QLatin1String("background-color: rgb(70, 70, 70);\n"
"color: rgb(180, 180, 180);"));
        label_pic_xeno = new QLabel(centralwidget);
        label_pic_xeno->setObjectName(QStringLiteral("label_pic_xeno"));
        label_pic_xeno->setGeometry(QRect(10, 10, 420, 92));
        label_7 = new QLabel(centralwidget);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(400, 140, 41, 27));
        label_7->setStyleSheet(QStringLiteral("color: rgb(150, 150, 150);"));
        comboBox_checkermode = new QComboBox(centralwidget);
        comboBox_checkermode->setObjectName(QStringLiteral("comboBox_checkermode"));
        comboBox_checkermode->setGeometry(QRect(440, 140, 79, 23));
        comboBox_checkermode->setStyleSheet(QStringLiteral("color: rgb(170, 170, 255);"));
        progressBar = new QProgressBar(centralwidget);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setGeometry(QRect(10, 230, 118, 23));
        progressBar->setValue(0);
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(21, 141, 302, 25));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setStyleSheet(QStringLiteral("color: rgb(150, 150, 150);"));

        horizontalLayout->addWidget(label_2);

        checking_sampling_time = new QLineEdit(layoutWidget);
        checking_sampling_time->setObjectName(QStringLiteral("checking_sampling_time"));
        checking_sampling_time->setLayoutDirection(Qt::RightToLeft);
        checking_sampling_time->setStyleSheet(QLatin1String("color: rgb(150, 150, 150);\n"
"border-color: rgb(0, 0, 255);\n"
"gridline-color: rgb(85, 0, 255);"));

        horizontalLayout->addWidget(checking_sampling_time);

        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setStyleSheet(QStringLiteral("color: rgb(150, 150, 150);"));

        horizontalLayout->addWidget(label);

        layoutWidget1 = new QWidget(centralwidget);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(209, 201, 275, 25));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(layoutWidget1);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setStyleSheet(QStringLiteral("color: rgb(150, 150, 150);"));

        horizontalLayout_2->addWidget(label_3);

        checking_sampling_time_2 = new QLineEdit(layoutWidget1);
        checking_sampling_time_2->setObjectName(QStringLiteral("checking_sampling_time_2"));

        horizontalLayout_2->addWidget(checking_sampling_time_2);

        label_5 = new QLabel(layoutWidget1);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setStyleSheet(QStringLiteral("color: rgb(150, 150, 150);"));

        horizontalLayout_2->addWidget(label_5);

        layoutWidget2 = new QWidget(centralwidget);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(182, 238, 300, 25));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget2);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_4 = new QLabel(layoutWidget2);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setStyleSheet(QStringLiteral("color: rgb(150, 150, 150);"));

        horizontalLayout_3->addWidget(label_4);

        checking_sampling_time_3 = new QLineEdit(layoutWidget2);
        checking_sampling_time_3->setObjectName(QStringLiteral("checking_sampling_time_3"));

        horizontalLayout_3->addWidget(checking_sampling_time_3);

        label_6 = new QLabel(layoutWidget2);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setStyleSheet(QStringLiteral("color: rgb(150, 150, 150);"));

        horizontalLayout_3->addWidget(label_6);

        pushButton_stop2 = new QPushButton(centralwidget);
        pushButton_stop2->setObjectName(QStringLiteral("pushButton_stop2"));
        pushButton_stop2->setGeometry(QRect(440, 100, 99, 27));
        pushButton_stop2->setStyleSheet(QLatin1String("background-color: rgb(70, 70, 70);\n"
"color: rgb(180, 180, 180);"));
        Xenomai_periodic_timer_checker->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Xenomai_periodic_timer_checker);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 554, 20));
        Xenomai_periodic_timer_checker->setMenuBar(menubar);
        statusbar = new QStatusBar(Xenomai_periodic_timer_checker);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        Xenomai_periodic_timer_checker->setStatusBar(statusbar);

        retranslateUi(Xenomai_periodic_timer_checker);

        QMetaObject::connectSlotsByName(Xenomai_periodic_timer_checker);
    } // setupUi

    void retranslateUi(QMainWindow *Xenomai_periodic_timer_checker)
    {
        Xenomai_periodic_timer_checker->setWindowTitle(QApplication::translate("Xenomai_periodic_timer_checker", "Xenomai periodic timer checker", 0));
        pushButton->setText(QApplication::translate("Xenomai_periodic_timer_checker", "Run", 0));
        pushButton_2->setText(QApplication::translate("Xenomai_periodic_timer_checker", "Stop1", 0));
        label_pic_xeno->setText(QString());
        label_7->setText(QApplication::translate("Xenomai_periodic_timer_checker", "mode", 0));
        comboBox_checkermode->clear();
        comboBox_checkermode->insertItems(0, QStringList()
         << QApplication::translate("Xenomai_periodic_timer_checker", "1", 0)
         << QApplication::translate("Xenomai_periodic_timer_checker", "2", 0)
        );
        label_2->setText(QApplication::translate("Xenomai_periodic_timer_checker", "sampling time", 0));
        checking_sampling_time->setText(QApplication::translate("Xenomai_periodic_timer_checker", "100000", 0));
        label->setText(QApplication::translate("Xenomai_periodic_timer_checker", "nano second", 0));
        label_3->setText(QApplication::translate("Xenomai_periodic_timer_checker", "Max error", 0));
        checking_sampling_time_2->setText(QString());
        label_5->setText(QApplication::translate("Xenomai_periodic_timer_checker", "nano second", 0));
        label_4->setText(QApplication::translate("Xenomai_periodic_timer_checker", "Average error", 0));
        checking_sampling_time_3->setText(QString());
        label_6->setText(QApplication::translate("Xenomai_periodic_timer_checker", "nano second", 0));
        pushButton_stop2->setText(QApplication::translate("Xenomai_periodic_timer_checker", "Stop2", 0));
    } // retranslateUi

};

namespace Ui {
    class Xenomai_periodic_timer_checker: public Ui_Xenomai_periodic_timer_checker {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XENOMAI_PERIODIC_TIMER_CHECKER_H
