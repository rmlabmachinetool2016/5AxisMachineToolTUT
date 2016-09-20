/********************************************************************************
** Form generated from reading UI file 'openglwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPENGLWINDOW_H
#define UI_OPENGLWINDOW_H

#include <GUI/OPENGL/glwidget.h>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_openglwindow
{
public:
    QWidget *centralwidget;
    GLWidget *widget;
    QLabel *label;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QSlider *horizontalSlider;
    QProgressBar *progressBar;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_Close_openglwindow;
    QSlider *horizontalSlider_InitZaxis_2;
    QGroupBox *groupBox;
    QLabel *label_2;
    QLabel *label_15;
    QLabel *label_7;
    QSlider *horizontalSlider_InitXaxis;
    QLabel *label_5;
    QLineEdit *lineEdit_3;
    QLabel *label_9;
    QLabel *label_14;
    QLabel *label_4;
    QLabel *label_6;
    QSlider *horizontalSlider_InitXaxis_2;
    QSlider *horizontalSlider_InitZaxis;
    QLabel *label_8;
    QSlider *horizontalSlider_MainShaft;
    QLabel *label_3;
    QSlider *horizontalSlider_InitYaxis;
    QLineEdit *lineEdit_2;
    QLabel *label_11;
    QLineEdit *lineEdit_5;
    QSlider *horizontalSlider_InitYaxis_2;
    QLineEdit *lineEdit;
    QLabel *label_10;
    QLineEdit *lineEdit_4;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *openglwindow)
    {
        if (openglwindow->objectName().isEmpty())
            openglwindow->setObjectName(QStringLiteral("openglwindow"));
        openglwindow->resize(1168, 686);
        centralwidget = new QWidget(openglwindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        widget = new GLWidget(centralwidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(20, 10, 871, 561));
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(23, 584, 51, 21));
        QFont font;
        font.setFamily(QStringLiteral("Times New Roman"));
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(90, 580, 801, 63));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalSlider = new QSlider(layoutWidget);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setFocusPolicy(Qt::StrongFocus);
        horizontalSlider->setContextMenuPolicy(Qt::DefaultContextMenu);
        horizontalSlider->setOrientation(Qt::Horizontal);
        horizontalSlider->setTickPosition(QSlider::TicksBothSides);

        verticalLayout->addWidget(horizontalSlider);

        progressBar = new QProgressBar(layoutWidget);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        QFont font1;
        font1.setFamily(QStringLiteral("Times New Roman"));
        progressBar->setFont(font1);
        progressBar->setValue(0);

        verticalLayout->addWidget(progressBar);

        layoutWidget1 = new QWidget(centralwidget);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(910, 10, 97, 241));
        verticalLayout_2 = new QVBoxLayout(layoutWidget1);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        pushButton_3 = new QPushButton(layoutWidget1);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        QFont font2;
        font2.setFamily(QStringLiteral("Times New Roman"));
        font2.setPointSize(14);
        font2.setBold(true);
        font2.setWeight(75);
        pushButton_3->setFont(font2);

        verticalLayout_2->addWidget(pushButton_3);

        pushButton_4 = new QPushButton(layoutWidget1);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setFont(font2);

        verticalLayout_2->addWidget(pushButton_4);

        pushButton = new QPushButton(layoutWidget1);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setFont(font2);

        verticalLayout_2->addWidget(pushButton);

        pushButton_2 = new QPushButton(layoutWidget1);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setFont(font2);

        verticalLayout_2->addWidget(pushButton_2);

        pushButton_Close_openglwindow = new QPushButton(layoutWidget1);
        pushButton_Close_openglwindow->setObjectName(QStringLiteral("pushButton_Close_openglwindow"));
        pushButton_Close_openglwindow->setFont(font2);

        verticalLayout_2->addWidget(pushButton_Close_openglwindow);

        horizontalSlider_InitZaxis_2 = new QSlider(centralwidget);
        horizontalSlider_InitZaxis_2->setObjectName(QStringLiteral("horizontalSlider_InitZaxis_2"));
        horizontalSlider_InitZaxis_2->setGeometry(QRect(920, 650, 181, 22));
        horizontalSlider_InitZaxis_2->setMinimum(-5);
        horizontalSlider_InitZaxis_2->setMaximum(5);
        horizontalSlider_InitZaxis_2->setOrientation(Qt::Horizontal);
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(900, 260, 211, 371));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(17, 18, 94, 16));
        label_15 = new QLabel(groupBox);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setGeometry(QRect(16, 256, 38, 16));
        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(197, 82, 16, 16));
        horizontalSlider_InitXaxis = new QSlider(groupBox);
        horizontalSlider_InitXaxis->setObjectName(QStringLiteral("horizontalSlider_InitXaxis"));
        horizontalSlider_InitXaxis->setGeometry(QRect(17, 108, 181, 22));
        horizontalSlider_InitXaxis->setMinimum(-5);
        horizontalSlider_InitXaxis->setMaximum(5);
        horizontalSlider_InitXaxis->setOrientation(Qt::Horizontal);
        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(17, 136, 38, 16));
        lineEdit_3 = new QLineEdit(groupBox);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(61, 190, 130, 20));
        label_9 = new QLabel(groupBox);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(197, 190, 16, 16));
        label_14 = new QLabel(groupBox);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setGeometry(QRect(196, 310, 16, 16));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(17, 190, 38, 16));
        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(17, 82, 38, 16));
        horizontalSlider_InitXaxis_2 = new QSlider(groupBox);
        horizontalSlider_InitXaxis_2->setObjectName(QStringLiteral("horizontalSlider_InitXaxis_2"));
        horizontalSlider_InitXaxis_2->setGeometry(QRect(16, 282, 181, 22));
        horizontalSlider_InitXaxis_2->setMinimum(-5);
        horizontalSlider_InitXaxis_2->setMaximum(5);
        horizontalSlider_InitXaxis_2->setOrientation(Qt::Horizontal);
        horizontalSlider_InitZaxis = new QSlider(groupBox);
        horizontalSlider_InitZaxis->setObjectName(QStringLiteral("horizontalSlider_InitZaxis"));
        horizontalSlider_InitZaxis->setGeometry(QRect(17, 216, 181, 22));
        horizontalSlider_InitZaxis->setMinimum(-5);
        horizontalSlider_InitZaxis->setMaximum(5);
        horizontalSlider_InitZaxis->setOrientation(Qt::Horizontal);
        label_8 = new QLabel(groupBox);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(197, 136, 16, 16));
        horizontalSlider_MainShaft = new QSlider(groupBox);
        horizontalSlider_MainShaft->setObjectName(QStringLiteral("horizontalSlider_MainShaft"));
        horizontalSlider_MainShaft->setGeometry(QRect(17, 36, 191, 22));
        horizontalSlider_MainShaft->setOrientation(Qt::Horizontal);
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(17, 64, 60, 16));
        horizontalSlider_InitYaxis = new QSlider(groupBox);
        horizontalSlider_InitYaxis->setObjectName(QStringLiteral("horizontalSlider_InitYaxis"));
        horizontalSlider_InitYaxis->setGeometry(QRect(17, 162, 181, 22));
        horizontalSlider_InitYaxis->setMinimum(-5);
        horizontalSlider_InitYaxis->setMaximum(5);
        horizontalSlider_InitYaxis->setOrientation(Qt::Horizontal);
        lineEdit_2 = new QLineEdit(groupBox);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(61, 136, 130, 20));
        label_11 = new QLabel(groupBox);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(196, 256, 16, 16));
        lineEdit_5 = new QLineEdit(groupBox);
        lineEdit_5->setObjectName(QStringLiteral("lineEdit_5"));
        lineEdit_5->setGeometry(QRect(60, 256, 130, 20));
        horizontalSlider_InitYaxis_2 = new QSlider(groupBox);
        horizontalSlider_InitYaxis_2->setObjectName(QStringLiteral("horizontalSlider_InitYaxis_2"));
        horizontalSlider_InitYaxis_2->setGeometry(QRect(16, 336, 181, 22));
        horizontalSlider_InitYaxis_2->setMinimum(-5);
        horizontalSlider_InitYaxis_2->setMaximum(5);
        horizontalSlider_InitYaxis_2->setOrientation(Qt::Horizontal);
        lineEdit = new QLineEdit(groupBox);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(61, 82, 130, 20));
        label_10 = new QLabel(groupBox);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(16, 310, 38, 16));
        lineEdit_4 = new QLineEdit(groupBox);
        lineEdit_4->setObjectName(QStringLiteral("lineEdit_4"));
        lineEdit_4->setGeometry(QRect(60, 310, 130, 20));
        openglwindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(openglwindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 1168, 20));
        openglwindow->setMenuBar(menubar);
        statusbar = new QStatusBar(openglwindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        openglwindow->setStatusBar(statusbar);

        retranslateUi(openglwindow);
        QObject::connect(horizontalSlider, SIGNAL(valueChanged(int)), progressBar, SLOT(setValue(int)));
        QObject::connect(horizontalSlider_MainShaft, SIGNAL(valueChanged(int)), widget, SLOT(MainShaftRot(int)));
        QObject::connect(pushButton_Close_openglwindow, SIGNAL(clicked()), widget, SLOT(deleteLater()));

        QMetaObject::connectSlotsByName(openglwindow);
    } // setupUi

    void retranslateUi(QMainWindow *openglwindow)
    {
        openglwindow->setWindowTitle(QApplication::translate("openglwindow", "MainWindow", 0));
        label->setText(QApplication::translate("openglwindow", "Progress", 0));
        pushButton_3->setText(QApplication::translate("openglwindow", "Offset Set", 0));
        pushButton_4->setText(QApplication::translate("openglwindow", "Start", 0));
        pushButton->setText(QApplication::translate("openglwindow", "Stop", 0));
        pushButton_2->setText(QApplication::translate("openglwindow", "Clear", 0));
        pushButton_Close_openglwindow->setText(QApplication::translate("openglwindow", "Exit", 0));
        groupBox->setTitle(QApplication::translate("openglwindow", "Offset Parameter", 0));
        label_2->setText(QApplication::translate("openglwindow", "Main Shaft rotaion", 0));
        label_15->setText(QApplication::translate("openglwindow", "A-axis ", 0));
        label_7->setText(QApplication::translate("openglwindow", "m", 0));
        label_5->setText(QApplication::translate("openglwindow", "Y-axis ", 0));
        label_9->setText(QApplication::translate("openglwindow", "m", 0));
        label_14->setText(QApplication::translate("openglwindow", "m", 0));
        label_4->setText(QApplication::translate("openglwindow", "Z-axis ", 0));
        label_6->setText(QApplication::translate("openglwindow", "X-axis ", 0));
        label_8->setText(QApplication::translate("openglwindow", "m", 0));
        label_3->setText(QApplication::translate("openglwindow", "Init position", 0));
        label_11->setText(QApplication::translate("openglwindow", "m", 0));
        label_10->setText(QApplication::translate("openglwindow", "C-axis ", 0));
    } // retranslateUi

};

namespace Ui {
    class openglwindow: public Ui_openglwindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPENGLWINDOW_H
