#ifndef UI_MAINFRAME_H
#define UI_MAINFRAME_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QLabel>

class Ui_MainFrame
{
public:
    QLabel *lblBackground;
    QLabel *lblBackgroundFrame;
    QLabel *lblTitleBackground;
    QLabel *lblTitleText;
    QLabel *lblTitleIcon;
    QLabel *lblStatusIcon;
    QLabel *lblStatusText;
    QLabel *lblTitleText1;
    QLabel *lblEsc;

    void setupUi(QDialog *MainFrame)
    {
    MainFrame->setObjectName(QString::fromUtf8("MainFrame"));
    MainFrame->resize(QSize(480, 272).expandedTo(MainFrame->minimumSizeHint()));
    lblBackground = new QLabel(MainFrame);
    lblBackground->setObjectName(QString::fromUtf8("lblBackground"));
    lblBackground->setGeometry(QRect(0, 0, 480, 272));
    lblBackground->setPixmap(QPixmap(QString::fromUtf8(":/images/res/bg-main.png")));
    lblBackgroundFrame = new QLabel(MainFrame);
    lblBackgroundFrame->setObjectName(QString::fromUtf8("lblBackgroundFrame"));
    lblBackgroundFrame->setGeometry(QRect(12, 10, 456, 260));
    lblBackgroundFrame->setPixmap(QPixmap(QString::fromUtf8(":/images/res/bg-menu.png")));
    lblBackgroundFrame->setScaledContents(false);
    lblTitleBackground = new QLabel(MainFrame);
    lblTitleBackground->setObjectName(QString::fromUtf8("lblTitleBackground"));
    lblTitleBackground->setGeometry(QRect(0, 0, 400, 34));
    lblTitleBackground->setPixmap(QPixmap(QString::fromUtf8(":/images/res/title-1.png")));
    lblTitleText = new QLabel(MainFrame);
    lblTitleText->setObjectName(QString::fromUtf8("lblTitleText"));
    lblTitleText->setGeometry(QRect(40, 3, 273, 28));
    lblTitleIcon = new QLabel(MainFrame);
    lblTitleIcon->setObjectName(QString::fromUtf8("lblTitleIcon"));
    lblTitleIcon->setGeometry(QRect(9, 5, 26, 26));
    lblTitleIcon->setScaledContents(true);
    lblStatusIcon = new QLabel(MainFrame);
    lblStatusIcon->setObjectName(QString::fromUtf8("lblStatusIcon"));
    lblStatusIcon->setGeometry(QRect(20, 215, 16, 16));
    lblStatusIcon->setPixmap(QPixmap(QString::fromUtf8(":/images/res/icon-help.png")));
    lblStatusText = new QLabel(MainFrame);
    lblStatusText->setObjectName(QString::fromUtf8("lblStatusText"));
    lblStatusText->setGeometry(QRect(40, 210, 275, 25));
    lblTitleText1 = new QLabel(MainFrame);
    lblTitleText1->setObjectName(QString::fromUtf8("lblTitleText1"));
    lblTitleText1->setGeometry(QRect(201, 10, 110, 28));
    lblEsc = new QLabel(MainFrame);
    lblEsc->setObjectName(QString::fromUtf8("lblEsc"));
    lblEsc->setGeometry(QRect(400, 0, 80, 34));
    lblEsc->setPixmap(QPixmap(QString::fromUtf8(":/images/res/esc.png")));
    retranslateUi(MainFrame);

    QMetaObject::connectSlotsByName(MainFrame);
    } // setupUi

    void retranslateUi(QDialog *MainFrame)
    {
    MainFrame->setWindowTitle(QApplication::translate("MainFrame", "Dialog", 0, QApplication::UnicodeUTF8));
    lblBackground->setText(QApplication::translate("MainFrame", "", 0, QApplication::UnicodeUTF8));
    lblBackgroundFrame->setText(QApplication::translate("MainFrame", "", 0, QApplication::UnicodeUTF8));
    lblTitleBackground->setText(QApplication::translate("MainFrame", "", 0, QApplication::UnicodeUTF8));
    lblTitleText->setText(QApplication::translate("MainFrame", "Title", 0, QApplication::UnicodeUTF8));
    lblTitleIcon->setText(QApplication::translate("MainFrame", "", 0, QApplication::UnicodeUTF8));
    lblStatusIcon->setText(QApplication::translate("MainFrame", "", 0, QApplication::UnicodeUTF8));
    lblStatusText->setText(QApplication::translate("MainFrame", "Use Arrow & OK, ESC for return", 0, QApplication::UnicodeUTF8));
    lblTitleText1->setText(QApplication::translate("MainFrame", "", 0, QApplication::UnicodeUTF8));
    lblEsc->setText(QApplication::translate("MainFrame", "", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(MainFrame);
    } // retranslateUi

};

namespace Ui {
    class MainFrame: public Ui_MainFrame {};
} // namespace Ui

#endif // UI_MAINFRAME_H
