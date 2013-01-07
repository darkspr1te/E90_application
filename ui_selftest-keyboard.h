#ifndef UI_SELFTEST_2D_KEYBOARD_H
#define UI_SELFTEST_2D_KEYBOARD_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>

class Ui_SelftestKeyboard
{
public:
    QLabel *lblBackground;
    QPushButton *btnF2;
    QPushButton *btnF6;
    QPushButton *btnF8;
    QPushButton *btnF1;
    QPushButton *btnF4;
    QPushButton *btnF5;
    QPushButton *btnF3;
    QPushButton *btnF7;
    QLabel *lblStatusbar;
    QLabel *lblStatusIcon;
    QLabel *lblStatusText;
    QPushButton *btnESC;

    void setupUi(QDialog *SelftestKeyboard)
    {
    SelftestKeyboard->setObjectName(QString::fromUtf8("SelftestKeyboard"));
    SelftestKeyboard->resize(QSize(320, 240).expandedTo(SelftestKeyboard->minimumSizeHint()));
    lblBackground = new QLabel(SelftestKeyboard);
    lblBackground->setObjectName(QString::fromUtf8("lblBackground"));
    lblBackground->setGeometry(QRect(30, 38, 261, 181));
    lblBackground->setPixmap(QPixmap(QString::fromUtf8(":/images/res/bg-inputbox.png")));
    lblBackground->setScaledContents(true);
    btnF2 = new QPushButton(SelftestKeyboard);
    btnF2->setObjectName(QString::fromUtf8("btnF2"));
    btnF2->setGeometry(QRect(102, 70, 49, 26));
    btnF6 = new QPushButton(SelftestKeyboard);
    btnF6->setObjectName(QString::fromUtf8("btnF6"));
    btnF6->setGeometry(QRect(102, 120, 49, 26));
    btnF8 = new QPushButton(SelftestKeyboard);
    btnF8->setObjectName(QString::fromUtf8("btnF8"));
    btnF8->setGeometry(QRect(226, 120, 49, 26));
    btnF1 = new QPushButton(SelftestKeyboard);
    btnF1->setObjectName(QString::fromUtf8("btnF1"));
    btnF1->setGeometry(QRect(40, 70, 50, 26));
    btnF4 = new QPushButton(SelftestKeyboard);
    btnF4->setObjectName(QString::fromUtf8("btnF4"));
    btnF4->setGeometry(QRect(226, 70, 49, 26));
    btnF5 = new QPushButton(SelftestKeyboard);
    btnF5->setObjectName(QString::fromUtf8("btnF5"));
    btnF5->setGeometry(QRect(40, 120, 50, 26));
    btnF3 = new QPushButton(SelftestKeyboard);
    btnF3->setObjectName(QString::fromUtf8("btnF3"));
    btnF3->setGeometry(QRect(162, 70, 49, 26));
    btnF7 = new QPushButton(SelftestKeyboard);
    btnF7->setObjectName(QString::fromUtf8("btnF7"));
    btnF7->setGeometry(QRect(164, 120, 49, 26));
    lblStatusbar = new QLabel(SelftestKeyboard);
    lblStatusbar->setObjectName(QString::fromUtf8("lblStatusbar"));
    lblStatusbar->setGeometry(QRect(0, 200, 320, 40));
    lblStatusIcon = new QLabel(SelftestKeyboard);
    lblStatusIcon->setObjectName(QString::fromUtf8("lblStatusIcon"));
    lblStatusIcon->setGeometry(QRect(10, 210, 16, 16));
    lblStatusIcon->setPixmap(QPixmap(QString::fromUtf8(":/images/res/icon-help.png")));
    lblStatusText = new QLabel(SelftestKeyboard);
    lblStatusText->setObjectName(QString::fromUtf8("lblStatusText"));
    lblStatusText->setGeometry(QRect(30, 200, 261, 40));
    btnESC = new QPushButton(SelftestKeyboard);
    btnESC->setObjectName(QString::fromUtf8("btnESC"));
    btnESC->setGeometry(QRect(120, 175, 80, 34));
    retranslateUi(SelftestKeyboard);

    QMetaObject::connectSlotsByName(SelftestKeyboard);
    } // setupUi

    void retranslateUi(QDialog *SelftestKeyboard)
    {
    SelftestKeyboard->setWindowTitle(QApplication::translate("SelftestKeyboard", "Dialog", 0, QApplication::UnicodeUTF8));
    lblBackground->setText(QApplication::translate("SelftestKeyboard", "", 0, QApplication::UnicodeUTF8));
    btnF2->setText(QApplication::translate("SelftestKeyboard", "F2", 0, QApplication::UnicodeUTF8));
    btnF6->setText(QApplication::translate("SelftestKeyboard", "F6", 0, QApplication::UnicodeUTF8));
    btnF8->setText(QApplication::translate("SelftestKeyboard", "F8", 0, QApplication::UnicodeUTF8));
    btnF1->setText(QApplication::translate("SelftestKeyboard", "F1", 0, QApplication::UnicodeUTF8));
    btnF4->setText(QApplication::translate("SelftestKeyboard", "F4", 0, QApplication::UnicodeUTF8));
    btnF5->setText(QApplication::translate("SelftestKeyboard", "F5", 0, QApplication::UnicodeUTF8));
    btnF3->setText(QApplication::translate("SelftestKeyboard", "F3", 0, QApplication::UnicodeUTF8));
    btnF7->setText(QApplication::translate("SelftestKeyboard", "F7", 0, QApplication::UnicodeUTF8));
    lblStatusbar->setText(QApplication::translate("SelftestKeyboard", "", 0, QApplication::UnicodeUTF8));
    lblStatusIcon->setText(QApplication::translate("SelftestKeyboard", "", 0, QApplication::UnicodeUTF8));
    lblStatusText->setText(QApplication::translate("SelftestKeyboard", "Press any key to check", 0, QApplication::UnicodeUTF8));
    btnESC->setText(QApplication::translate("SelftestKeyboard", "ESC", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(SelftestKeyboard);
    } // retranslateUi

};

namespace Ui {
    class SelftestKeyboard: public Ui_SelftestKeyboard {};
} // namespace Ui

#endif // UI_SELFTEST_2D_KEYBOARD_H
