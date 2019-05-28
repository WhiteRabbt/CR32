/********************************************************************************
** Form generated from reading UI file 'LinkGame.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LINKGAME_H
#define UI_LINKGAME_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LinkGameClass
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *speed;
    QLineEdit *lineEdit;
    QPushButton *start;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *LinkGameClass)
    {
        if (LinkGameClass->objectName().isEmpty())
            LinkGameClass->setObjectName(QString::fromUtf8("LinkGameClass"));
        LinkGameClass->resize(490, 336);
        centralWidget = new QWidget(LinkGameClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        speed = new QLabel(centralWidget);
        speed->setObjectName(QString::fromUtf8("speed"));

        horizontalLayout->addWidget(speed);

        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        horizontalLayout->addWidget(lineEdit);

        start = new QPushButton(centralWidget);
        start->setObjectName(QString::fromUtf8("start"));

        horizontalLayout->addWidget(start);

        LinkGameClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(LinkGameClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 490, 23));
        LinkGameClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(LinkGameClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        LinkGameClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(LinkGameClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        LinkGameClass->setStatusBar(statusBar);

        retranslateUi(LinkGameClass);

        QMetaObject::connectSlotsByName(LinkGameClass);
    } // setupUi

    void retranslateUi(QMainWindow *LinkGameClass)
    {
        LinkGameClass->setWindowTitle(QApplication::translate("LinkGameClass", "LinkGame", nullptr));
        speed->setText(QApplication::translate("LinkGameClass", "\346\270\270\346\210\217\351\200\237\345\272\246", nullptr));
        start->setText(QApplication::translate("LinkGameClass", "\346\270\270\346\210\217\345\274\200\345\247\213", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LinkGameClass: public Ui_LinkGameClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LINKGAME_H
