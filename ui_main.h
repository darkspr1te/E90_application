#ifndef UI_MAIN_H
#define UI_MAIN_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QLabel>
#include <QtGui/QWidget>

class Ui_MainWidget
{
public:
    QLabel *lblBackground;
    QLabel *lblClock;
    QLabel *lblstatUSB;
    QLabel *lblstatCard;
    QLabel *lblstatFingerprint;
    QLabel *lblstatUDisk;
    QLabel *lblstatWebserver;
    QLabel *lblStatbarFingerprint;
    QLabel *lblStatusbarText;
    QLabel *lblMonth;
    QLabel *lblWeekday;
    QLabel *lblTime;
    QLabel *lblMessageArea;
    QLabel *lblAMPM;
    QLabel *lblMenu;
    QLabel *lblNum;
    QLabel *lblNet;

    void setupUi(QWidget *MainWidget)
    {
    MainWidget->setObjectName(QString::fromUtf8("MainWidget"));
    MainWidget->resize(QSize(480, 272).expandedTo(MainWidget->minimumSizeHint()));
    QFont font;
    font.setFamily(QString::fromUtf8("Tahoma"));
    font.setPointSize(10);
    font.setBold(false);
    font.setItalic(false);
    font.setUnderline(false);
    font.setStrikeOut(false);
    MainWidget->setFont(font);
    lblBackground = new QLabel(MainWidget);
    lblBackground->setObjectName(QString::fromUtf8("lblBackground"));
    lblBackground->setGeometry(QRect(0, 0, 480, 272));
    lblClock = new QLabel(MainWidget);
    lblClock->setObjectName(QString::fromUtf8("lblClock"));
    lblClock->setGeometry(QRect(27, 36, 112, 112));
    lblClock->setPixmap(QPixmap(QString::fromUtf8(":/images/res/clock.png")));
    lblClock->setScaledContents(false);
    lblstatUSB = new QLabel(MainWidget);
    lblstatUSB->setObjectName(QString::fromUtf8("lblstatUSB"));
    lblstatUSB->setEnabled(false);
    lblstatUSB->setGeometry(QRect(21, 120, 40, 40));
    lblstatUSB->setPixmap(QPixmap(QString::fromUtf8(":/images/res/stat-usb.png")));
    lblstatCard = new QLabel(MainWidget);
    lblstatCard->setObjectName(QString::fromUtf8("lblstatCard"));
    lblstatCard->setEnabled(false);
    lblstatCard->setGeometry(QRect(80, 120, 40, 40));
    lblstatCard->setPixmap(QPixmap(QString::fromUtf8(":/images/res/stat-card.png")));
    lblstatFingerprint = new QLabel(MainWidget);
    lblstatFingerprint->setObjectName(QString::fromUtf8("lblstatFingerprint"));
    lblstatFingerprint->setEnabled(false);
    lblstatFingerprint->setGeometry(QRect(139, 120, 40, 40));
    lblstatFingerprint->setPixmap(QPixmap(QString::fromUtf8(":/images/res/stat-fingerprint.png")));
    lblstatUDisk = new QLabel(MainWidget);
    lblstatUDisk->setObjectName(QString::fromUtf8("lblstatUDisk"));
    lblstatUDisk->setEnabled(false);
    lblstatUDisk->setGeometry(QRect(198, 120, 40, 40));
    lblstatUDisk->setPixmap(QPixmap(QString::fromUtf8(":/images/res/stat-udisk.png")));
    lblstatWebserver = new QLabel(MainWidget);
    lblstatWebserver->setObjectName(QString::fromUtf8("lblstatWebserver"));
    lblstatWebserver->setEnabled(false);
    lblstatWebserver->setGeometry(QRect(257, 120, 40, 40));
    lblstatWebserver->setPixmap(QPixmap(QString::fromUtf8(":/images/res/stat-webserver.png")));
    lblStatbarFingerprint = new QLabel(MainWidget);
    lblStatbarFingerprint->setObjectName(QString::fromUtf8("lblStatbarFingerprint"));
    lblStatbarFingerprint->setGeometry(QRect(159, 130, 32, 32));
    lblStatbarFingerprint->setPixmap(QPixmap(QString::fromUtf8(":/images/res/check-in.png")));
    lblStatusbarText = new QLabel(MainWidget);
    lblStatusbarText->setObjectName(QString::fromUtf8("lblStatusbarText"));
    lblStatusbarText->setGeometry(QRect(200, 130, 120, 32));
    QPalette palette;
    lblStatusbarText->setPalette(palette);
    QFont font1;
    font1.setFamily(QString::fromUtf8("\345\215\216\346\226\207\346\226\260\351\255\217"));
    font1.setPointSize(14);
    font1.setBold(true);
    font1.setItalic(false);
    font1.setUnderline(false);
    font1.setWeight(75);
    font1.setStrikeOut(false);
    lblStatusbarText->setFont(font1);
    lblStatusbarText->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
    lblMonth = new QLabel(MainWidget);
    lblMonth->setObjectName(QString::fromUtf8("lblMonth"));
    lblMonth->setGeometry(QRect(110, 220, 131, 31));
    lblMonth->setAlignment(Qt::AlignCenter);
    lblWeekday = new QLabel(MainWidget);
    lblWeekday->setObjectName(QString::fromUtf8("lblWeekday"));
    lblWeekday->setGeometry(QRect(120, 240, 101, 23));
    lblWeekday->setAlignment(Qt::AlignCenter);
    lblTime = new QLabel(MainWidget);
    lblTime->setObjectName(QString::fromUtf8("lblTime"));
    lblTime->setGeometry(QRect(0, 230, 130, 40));
    QPalette palette1;
    lblTime->setPalette(palette1);
    QFont font2;
    font2.setFamily(QString::fromUtf8("Arial"));
    font2.setPointSize(32);
    font2.setBold(true);
    font2.setItalic(false);
    font2.setUnderline(false);
    font2.setWeight(75);
    font2.setStrikeOut(false);
    lblTime->setFont(font2);
    lblTime->setAlignment(Qt::AlignCenter);
    lblMessageArea = new QLabel(MainWidget);
    lblMessageArea->setObjectName(QString::fromUtf8("lblMessageArea"));
    lblMessageArea->setGeometry(QRect(10, 164, 300, 26));
    QFont font3;
    font3.setFamily(QString::fromUtf8("Times New Roman"));
    font3.setPointSize(12);
    font3.setBold(false);
    font3.setItalic(false);
    font3.setUnderline(false);
    font3.setStrikeOut(false);
    lblMessageArea->setFont(font3);
    lblAMPM = new QLabel(MainWidget);
    lblAMPM->setObjectName(QString::fromUtf8("lblAMPM"));
    lblAMPM->setGeometry(QRect(180, 190, 30, 31));
    QPalette palette2;
    lblAMPM->setPalette(palette2);
    lblAMPM->setAlignment(Qt::AlignCenter);
    lblMenu = new QLabel(MainWidget);
    lblMenu->setObjectName(QString::fromUtf8("lblMenu"));
    lblMenu->setGeometry(QRect(280, 222, 100, 50));
    lblMenu->setPixmap(QPixmap(QString::fromUtf8(":/images/res/menu.png")));
    lblNum = new QLabel(MainWidget);
    lblNum->setObjectName(QString::fromUtf8("lblNum"));
    lblNum->setGeometry(QRect(380, 222, 100, 50));
    lblNum->setPixmap(QPixmap(QString::fromUtf8(":/images/res/num.png")));
    lblNet = new QLabel(MainWidget);
    lblNet->setObjectName(QString::fromUtf8("lblNet"));
    lblNet->setGeometry(QRect(230, 240, 41, 31));
    lblNet->setPixmap(QPixmap(QString::fromUtf8(":/images/res/net-lost.png")));
    lblNet->setScaledContents(true);
    lblNet->setAlignment(Qt::AlignCenter);
    retranslateUi(MainWidget);

    QMetaObject::connectSlotsByName(MainWidget);
    } // setupUi

    void retranslateUi(QWidget *MainWidget)
    {
    MainWidget->setWindowTitle(QApplication::translate("MainWidget", "Main Window", 0, QApplication::UnicodeUTF8));
    lblBackground->setText(QApplication::translate("MainWidget", "", 0, QApplication::UnicodeUTF8));
    lblClock->setText(QApplication::translate("MainWidget", "", 0, QApplication::UnicodeUTF8));
    lblstatUSB->setText(QApplication::translate("MainWidget", "", 0, QApplication::UnicodeUTF8));
    lblstatCard->setText(QApplication::translate("MainWidget", "", 0, QApplication::UnicodeUTF8));
    lblstatFingerprint->setText(QApplication::translate("MainWidget", "", 0, QApplication::UnicodeUTF8));
    lblstatUDisk->setText(QApplication::translate("MainWidget", "", 0, QApplication::UnicodeUTF8));
    lblstatWebserver->setText(QApplication::translate("MainWidget", "", 0, QApplication::UnicodeUTF8));
    lblStatbarFingerprint->setText(QApplication::translate("MainWidget", "", 0, QApplication::UnicodeUTF8));
    lblMessageArea->setText(QApplication::translate("MainWidget", "", 0, QApplication::UnicodeUTF8));
    lblMenu->setText(QApplication::translate("MainWidget", "", 0, QApplication::UnicodeUTF8));
    lblNum->setText(QApplication::translate("MainWidget", "", 0, QApplication::UnicodeUTF8));
    lblNet->setText(QApplication::translate("MainWidget", "", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(MainWidget);
    } // retranslateUi

};

namespace Ui {
    class MainWidget: public Ui_MainWidget {};
} // namespace Ui

#endif // UI_MAIN_H
