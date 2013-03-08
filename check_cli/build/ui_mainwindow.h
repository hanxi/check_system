/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Wed Mar 6 08:41:46 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QFrame *frame;
    QLabel *labelShow;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButtonCheckIn;
    QPushButton *pushButtonSearch;
    QPushButton *pushButtonCamara;
    QPushButton *pushButtonAgain;
    QPushButton *pushButtonSubmit;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuManage;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(567, 442);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        frame = new QFrame(centralwidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(10, 10, 541, 371));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        labelShow = new QLabel(frame);
        labelShow->setObjectName(QString::fromUtf8("labelShow"));
        labelShow->setGeometry(QRect(10, 10, 371, 341));
        labelShow->setScaledContents(false);
        layoutWidget = new QWidget(frame);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(450, 10, 87, 166));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetMinimumSize);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        pushButtonCheckIn = new QPushButton(layoutWidget);
        pushButtonCheckIn->setObjectName(QString::fromUtf8("pushButtonCheckIn"));

        verticalLayout->addWidget(pushButtonCheckIn);

        pushButtonSearch = new QPushButton(layoutWidget);
        pushButtonSearch->setObjectName(QString::fromUtf8("pushButtonSearch"));

        verticalLayout->addWidget(pushButtonSearch);

        pushButtonCamara = new QPushButton(layoutWidget);
        pushButtonCamara->setObjectName(QString::fromUtf8("pushButtonCamara"));

        verticalLayout->addWidget(pushButtonCamara);

        pushButtonAgain = new QPushButton(layoutWidget);
        pushButtonAgain->setObjectName(QString::fromUtf8("pushButtonAgain"));

        verticalLayout->addWidget(pushButtonAgain);

        pushButtonSubmit = new QPushButton(layoutWidget);
        pushButtonSubmit->setObjectName(QString::fromUtf8("pushButtonSubmit"));

        verticalLayout->addWidget(pushButtonSubmit);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 567, 26));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuManage = new QMenu(menubar);
        menuManage->setObjectName(QString::fromUtf8("menuManage"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuManage->menuAction());

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "\350\200\203\345\213\244\347\263\273\347\273\237", 0, QApplication::UnicodeUTF8));
        labelShow->setText(QApplication::translate("MainWindow", "\346\221\204\345\203\217\345\244\264\346\230\276\347\244\272", 0, QApplication::UnicodeUTF8));
        pushButtonCheckIn->setText(QApplication::translate("MainWindow", "\347\255\276\345\210\260", 0, QApplication::UnicodeUTF8));
        pushButtonSearch->setText(QApplication::translate("MainWindow", "\346\237\245\350\257\242", 0, QApplication::UnicodeUTF8));
        pushButtonCamara->setText(QApplication::translate("MainWindow", "\346\213\215\347\205\247", 0, QApplication::UnicodeUTF8));
        pushButtonAgain->setText(QApplication::translate("MainWindow", "\351\207\215\346\213\215", 0, QApplication::UnicodeUTF8));
        pushButtonSubmit->setText(QApplication::translate("MainWindow", "\346\217\220\344\272\244", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("MainWindow", "\346\226\207\344\273\266", 0, QApplication::UnicodeUTF8));
        menuManage->setTitle(QApplication::translate("MainWindow", "\347\256\241\347\220\206", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
