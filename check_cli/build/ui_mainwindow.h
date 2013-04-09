/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Tue Apr 9 08:50:50 2013
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
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSplitter>
#include <QtGui/QStatusBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionAddNewEmp;
    QAction *actionManageEmp;
    QAction *action_3;
    QWidget *centralwidget;
    QFrame *frame;
    QLabel *labelShow;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButtonCommitCheck;
    QPushButton *pushButtonCheckAgain;
    QPushButton *pushButtonSignIn;
    QPushButton *pushButtonCancel;
    QPushButton *pushButtonSubmit;
    QPushButton *pushButtonUpdateModel;
    QPushButton *pushButtonCamara;
    QPushButton *pushButtonSearch;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout;
    QSplitter *splitter;
    QLabel *labelName;
    QLineEdit *lineEditName;
    QSplitter *splitter_2;
    QLabel *labelDep;
    QLineEdit *lineEditDep;
    QLabel *labelCheckInfo;
    QMenuBar *menubar;
    QMenu *menu_2;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(812, 452);
        actionAddNewEmp = new QAction(MainWindow);
        actionAddNewEmp->setObjectName(QString::fromUtf8("actionAddNewEmp"));
        actionManageEmp = new QAction(MainWindow);
        actionManageEmp->setObjectName(QString::fromUtf8("actionManageEmp"));
        action_3 = new QAction(MainWindow);
        action_3->setObjectName(QString::fromUtf8("action_3"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        frame = new QFrame(centralwidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(10, 10, 791, 381));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        labelShow = new QLabel(frame);
        labelShow->setObjectName(QString::fromUtf8("labelShow"));
        labelShow->setGeometry(QRect(400, 10, 351, 291));
        labelShow->setScaledContents(false);
        layoutWidget = new QWidget(frame);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 340, 747, 30));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetMinimumSize);
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        pushButtonCommitCheck = new QPushButton(layoutWidget);
        pushButtonCommitCheck->setObjectName(QString::fromUtf8("pushButtonCommitCheck"));

        horizontalLayout->addWidget(pushButtonCommitCheck);

        pushButtonCheckAgain = new QPushButton(layoutWidget);
        pushButtonCheckAgain->setObjectName(QString::fromUtf8("pushButtonCheckAgain"));

        horizontalLayout->addWidget(pushButtonCheckAgain);

        pushButtonSignIn = new QPushButton(layoutWidget);
        pushButtonSignIn->setObjectName(QString::fromUtf8("pushButtonSignIn"));

        horizontalLayout->addWidget(pushButtonSignIn);

        pushButtonCancel = new QPushButton(layoutWidget);
        pushButtonCancel->setObjectName(QString::fromUtf8("pushButtonCancel"));

        horizontalLayout->addWidget(pushButtonCancel);

        pushButtonSubmit = new QPushButton(layoutWidget);
        pushButtonSubmit->setObjectName(QString::fromUtf8("pushButtonSubmit"));

        horizontalLayout->addWidget(pushButtonSubmit);

        pushButtonUpdateModel = new QPushButton(layoutWidget);
        pushButtonUpdateModel->setObjectName(QString::fromUtf8("pushButtonUpdateModel"));

        horizontalLayout->addWidget(pushButtonUpdateModel);

        pushButtonCamara = new QPushButton(layoutWidget);
        pushButtonCamara->setObjectName(QString::fromUtf8("pushButtonCamara"));

        horizontalLayout->addWidget(pushButtonCamara);

        pushButtonSearch = new QPushButton(layoutWidget);
        pushButtonSearch->setObjectName(QString::fromUtf8("pushButtonSearch"));

        horizontalLayout->addWidget(pushButtonSearch);

        layoutWidget1 = new QWidget(frame);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(100, 90, 176, 60));
        verticalLayout = new QVBoxLayout(layoutWidget1);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        splitter = new QSplitter(layoutWidget1);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        labelName = new QLabel(splitter);
        labelName->setObjectName(QString::fromUtf8("labelName"));
        splitter->addWidget(labelName);
        lineEditName = new QLineEdit(splitter);
        lineEditName->setObjectName(QString::fromUtf8("lineEditName"));
        splitter->addWidget(lineEditName);

        verticalLayout->addWidget(splitter);

        splitter_2 = new QSplitter(layoutWidget1);
        splitter_2->setObjectName(QString::fromUtf8("splitter_2"));
        splitter_2->setOrientation(Qt::Horizontal);
        labelDep = new QLabel(splitter_2);
        labelDep->setObjectName(QString::fromUtf8("labelDep"));
        splitter_2->addWidget(labelDep);
        lineEditDep = new QLineEdit(splitter_2);
        lineEditDep->setObjectName(QString::fromUtf8("lineEditDep"));
        splitter_2->addWidget(lineEditDep);

        verticalLayout->addWidget(splitter_2);

        labelCheckInfo = new QLabel(frame);
        labelCheckInfo->setObjectName(QString::fromUtf8("labelCheckInfo"));
        labelCheckInfo->setGeometry(QRect(100, 160, 141, 71));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 812, 26));
        menu_2 = new QMenu(menubar);
        menu_2->setObjectName(QString::fromUtf8("menu_2"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menu_2->menuAction());
        menu_2->addAction(actionAddNewEmp);
        menu_2->addSeparator();
        menu_2->addAction(actionManageEmp);
        menu_2->addSeparator();
        menu_2->addAction(action_3);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "\350\200\203\345\213\244\347\263\273\347\273\237", 0, QApplication::UnicodeUTF8));
        actionAddNewEmp->setText(QApplication::translate("MainWindow", "\346\226\260\345\242\236\345\221\230\345\267\245", 0, QApplication::UnicodeUTF8));
        actionManageEmp->setText(QApplication::translate("MainWindow", "\347\256\241\347\220\206\345\221\230\345\267\245", 0, QApplication::UnicodeUTF8));
        action_3->setText(QApplication::translate("MainWindow", "\347\211\271\346\256\212\346\211\223\345\215\241", 0, QApplication::UnicodeUTF8));
        labelShow->setText(QApplication::translate("MainWindow", "\346\221\204\345\203\217\345\244\264\346\230\276\347\244\272\n"
"\347\202\271\345\207\273\346\263\250\345\206\214\345\220\216\345\257\271\347\235\200\346\221\204\345\203\217\345\244\2643s", 0, QApplication::UnicodeUTF8));
        pushButtonCommitCheck->setText(QApplication::translate("MainWindow", "\347\241\256\345\256\232\346\211\223\345\215\241", 0, QApplication::UnicodeUTF8));
        pushButtonCheckAgain->setText(QApplication::translate("MainWindow", "\351\207\215\346\226\260\346\211\223\345\215\241", 0, QApplication::UnicodeUTF8));
        pushButtonSignIn->setText(QApplication::translate("MainWindow", "\346\263\250\345\206\214", 0, QApplication::UnicodeUTF8));
        pushButtonCancel->setText(QApplication::translate("MainWindow", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
        pushButtonSubmit->setText(QApplication::translate("MainWindow", "\346\217\220\344\272\244", 0, QApplication::UnicodeUTF8));
        pushButtonUpdateModel->setText(QApplication::translate("MainWindow", "\346\233\264\346\226\260\346\250\241\346\235\277\346\225\260\346\215\256", 0, QApplication::UnicodeUTF8));
        pushButtonCamara->setText(QApplication::translate("MainWindow", "\346\213\215\347\205\247", 0, QApplication::UnicodeUTF8));
        pushButtonSearch->setText(QApplication::translate("MainWindow", "\346\237\245\350\257\242", 0, QApplication::UnicodeUTF8));
        labelName->setText(QApplication::translate("MainWindow", "\345\247\223\345\220\215\357\274\232", 0, QApplication::UnicodeUTF8));
        labelDep->setText(QApplication::translate("MainWindow", "\351\203\250\351\227\250\357\274\232", 0, QApplication::UnicodeUTF8));
        labelCheckInfo->setText(QApplication::translate("MainWindow", "\347\255\276\345\210\260\344\277\241\346\201\257\346\230\276\347\244\272", 0, QApplication::UnicodeUTF8));
        menu_2->setTitle(QApplication::translate("MainWindow", "\350\217\234\345\215\225", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
