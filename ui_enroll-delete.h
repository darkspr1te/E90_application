#ifndef UI_ENROLL_2D_DELETE_H
#define UI_ENROLL_2D_DELETE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>

class Ui_EnrollDelete
{
public:
    QLabel *lblBackground;
    QLabel *lblTitleBackground;
    QLabel *lblTitleText;
    QLabel *lblTitleIcon;
    QLabel *lblStatusIcon;
    QLabel *lblStatusText;
    QLabel *lblPwdIcon;
    QLabel *lblFinger2;
    QLabel *lblFinger1;
    QLabel *lblFinger9;
    QLabel *lblFinger4;
    QLabel *lblFinger8;
    QLabel *lblFinger6;
    QLabel *lblFinger7;
    QPushButton *btnDeleteCard;
    QPushButton *btnDeleteAll;
    QLabel *lblFingerIcon;
    QLabel *lblFinger5;
    QLabel *lblFinger10;
    QPushButton *btnDeleteFP;
    QLabel *lblCardIcon;
    QLabel *lblFinger3;
    QPushButton *btnDeletePwd;
    QLabel *lblEsc;
    QLabel *lblDelFPButton;
    QLabel *lblDelFPButtonTitle;
    QLabel *lblDelCardButton;
    QLabel *lblDelCardButtonTitle;
    QLabel *lblDelPwdButton;
    QLabel *lblDelPwdButtonTitle;
    QLabel *lblDelAllButton;
    QLabel *lblDelAllButtonTitle;

    void setupUi(QDialog *EnrollDelete)
    {
    EnrollDelete->setObjectName(QString::fromUtf8("EnrollDelete"));
    EnrollDelete->resize(QSize(480, 272).expandedTo(EnrollDelete->minimumSizeHint()));
    lblBackground = new QLabel(EnrollDelete);
    lblBackground->setObjectName(QString::fromUtf8("lblBackground"));
    lblBackground->setGeometry(QRect(0, 0, 480, 272));
    lblBackground->setPixmap(QPixmap(QString::fromUtf8(":/images/res/bg-main.png")));
    lblTitleBackground = new QLabel(EnrollDelete);
    lblTitleBackground->setObjectName(QString::fromUtf8("lblTitleBackground"));
    lblTitleBackground->setGeometry(QRect(0, 0, 400, 34));
    lblTitleBackground->setPixmap(QPixmap(QString::fromUtf8(":/images/res/title-1.png")));
    lblTitleText = new QLabel(EnrollDelete);
    lblTitleText->setObjectName(QString::fromUtf8("lblTitleText"));
    lblTitleText->setGeometry(QRect(40, 3, 273, 28));
    lblTitleIcon = new QLabel(EnrollDelete);
    lblTitleIcon->setObjectName(QString::fromUtf8("lblTitleIcon"));
    lblTitleIcon->setGeometry(QRect(9, 5, 26, 26));
    lblTitleIcon->setPixmap(QPixmap(QString::fromUtf8(":/images/res/icon-normal.png")));
    lblTitleIcon->setScaledContents(true);
    lblStatusIcon = new QLabel(EnrollDelete);
    lblStatusIcon->setObjectName(QString::fromUtf8("lblStatusIcon"));
    lblStatusIcon->setGeometry(QRect(160, 260, 16, 16));
    lblStatusIcon->setPixmap(QPixmap(QString::fromUtf8(":/images/res/icon-help.png")));
    lblStatusText = new QLabel(EnrollDelete);
    lblStatusText->setObjectName(QString::fromUtf8("lblStatusText"));
    lblStatusText->setGeometry(QRect(200, 250, 270, 25));
    lblPwdIcon = new QLabel(EnrollDelete);
    lblPwdIcon->setObjectName(QString::fromUtf8("lblPwdIcon"));
    lblPwdIcon->setEnabled(false);
    lblPwdIcon->setGeometry(QRect(140, 170, 26, 26));
    lblPwdIcon->setPixmap(QPixmap(QString::fromUtf8(":/images/res/icon-pwd.png")));
    lblPwdIcon->setScaledContents(true);
    lblFinger2 = new QLabel(EnrollDelete);
    lblFinger2->setObjectName(QString::fromUtf8("lblFinger2"));
    lblFinger2->setEnabled(false);
    lblFinger2->setGeometry(QRect(220, 60, 21, 21));
    lblFinger2->setPixmap(QPixmap(QString::fromUtf8(":/images/res/icon-fingerenrolled.png")));
    lblFinger2->setScaledContents(true);
    lblFinger1 = new QLabel(EnrollDelete);
    lblFinger1->setObjectName(QString::fromUtf8("lblFinger1"));
    lblFinger1->setEnabled(false);
    lblFinger1->setGeometry(QRect(195, 60, 21, 21));
    lblFinger1->setPixmap(QPixmap(QString::fromUtf8(":/images/res/icon-fingerenrolled.png")));
    lblFinger1->setScaledContents(true);
    lblFinger9 = new QLabel(EnrollDelete);
    lblFinger9->setObjectName(QString::fromUtf8("lblFinger9"));
    lblFinger9->setEnabled(false);
    lblFinger9->setGeometry(QRect(395, 60, 21, 21));
    lblFinger9->setPixmap(QPixmap(QString::fromUtf8(":/images/res/icon-fingerenrolled.png")));
    lblFinger9->setScaledContents(true);
    lblFinger4 = new QLabel(EnrollDelete);
    lblFinger4->setObjectName(QString::fromUtf8("lblFinger4"));
    lblFinger4->setEnabled(false);
    lblFinger4->setGeometry(QRect(270, 60, 21, 21));
    lblFinger4->setPixmap(QPixmap(QString::fromUtf8(":/images/res/icon-fingerenrolled.png")));
    lblFinger4->setScaledContents(true);
    lblFinger8 = new QLabel(EnrollDelete);
    lblFinger8->setObjectName(QString::fromUtf8("lblFinger8"));
    lblFinger8->setEnabled(false);
    lblFinger8->setGeometry(QRect(370, 60, 21, 21));
    lblFinger8->setPixmap(QPixmap(QString::fromUtf8(":/images/res/icon-fingerenrolled.png")));
    lblFinger8->setScaledContents(true);
    lblFinger6 = new QLabel(EnrollDelete);
    lblFinger6->setObjectName(QString::fromUtf8("lblFinger6"));
    lblFinger6->setEnabled(false);
    lblFinger6->setGeometry(QRect(320, 60, 21, 21));
    lblFinger6->setPixmap(QPixmap(QString::fromUtf8(":/images/res/icon-fingerenrolled.png")));
    lblFinger6->setScaledContents(true);
    lblFinger7 = new QLabel(EnrollDelete);
    lblFinger7->setObjectName(QString::fromUtf8("lblFinger7"));
    lblFinger7->setEnabled(false);
    lblFinger7->setGeometry(QRect(345, 60, 21, 21));
    lblFinger7->setPixmap(QPixmap(QString::fromUtf8(":/images/res/icon-fingerenrolled.png")));
    lblFinger7->setScaledContents(true);
    btnDeleteCard = new QPushButton(EnrollDelete);
    btnDeleteCard->setObjectName(QString::fromUtf8("btnDeleteCard"));
    btnDeleteCard->setGeometry(QRect(360, 150, 85, 22));
    btnDeleteAll = new QPushButton(EnrollDelete);
    btnDeleteAll->setObjectName(QString::fromUtf8("btnDeleteAll"));
    btnDeleteAll->setGeometry(QRect(320, 240, 85, 22));
    lblFingerIcon = new QLabel(EnrollDelete);
    lblFingerIcon->setObjectName(QString::fromUtf8("lblFingerIcon"));
    lblFingerIcon->setEnabled(false);
    lblFingerIcon->setGeometry(QRect(140, 60, 26, 26));
    lblFingerIcon->setPixmap(QPixmap(QString::fromUtf8(":/images/res/icon-finger.png")));
    lblFingerIcon->setScaledContents(true);
    lblFinger5 = new QLabel(EnrollDelete);
    lblFinger5->setObjectName(QString::fromUtf8("lblFinger5"));
    lblFinger5->setEnabled(false);
    lblFinger5->setGeometry(QRect(295, 60, 21, 21));
    lblFinger5->setPixmap(QPixmap(QString::fromUtf8(":/images/res/icon-fingerenrolled.png")));
    lblFinger5->setScaledContents(true);
    lblFinger10 = new QLabel(EnrollDelete);
    lblFinger10->setObjectName(QString::fromUtf8("lblFinger10"));
    lblFinger10->setEnabled(false);
    lblFinger10->setGeometry(QRect(420, 60, 21, 21));
    lblFinger10->setPixmap(QPixmap(QString::fromUtf8(":/images/res/icon-fingerenrolled.png")));
    lblFinger10->setScaledContents(true);
    btnDeleteFP = new QPushButton(EnrollDelete);
    btnDeleteFP->setObjectName(QString::fromUtf8("btnDeleteFP"));
    btnDeleteFP->setGeometry(QRect(360, 110, 85, 22));
    lblCardIcon = new QLabel(EnrollDelete);
    lblCardIcon->setObjectName(QString::fromUtf8("lblCardIcon"));
    lblCardIcon->setEnabled(false);
    lblCardIcon->setGeometry(QRect(140, 110, 26, 26));
    lblCardIcon->setPixmap(QPixmap(QString::fromUtf8(":/images/res/icon-card.png")));
    lblCardIcon->setScaledContents(true);
    lblFinger3 = new QLabel(EnrollDelete);
    lblFinger3->setObjectName(QString::fromUtf8("lblFinger3"));
    lblFinger3->setEnabled(false);
    lblFinger3->setGeometry(QRect(245, 60, 21, 21));
    lblFinger3->setPixmap(QPixmap(QString::fromUtf8(":/images/res/icon-fingerenrolled.png")));
    lblFinger3->setScaledContents(true);
    btnDeletePwd = new QPushButton(EnrollDelete);
    btnDeletePwd->setObjectName(QString::fromUtf8("btnDeletePwd"));
    btnDeletePwd->setGeometry(QRect(360, 190, 85, 22));
    lblEsc = new QLabel(EnrollDelete);
    lblEsc->setObjectName(QString::fromUtf8("lblEsc"));
    lblEsc->setGeometry(QRect(400, 0, 80, 34));
    lblEsc->setPixmap(QPixmap(QString::fromUtf8(":/images/res/esc.png")));
    lblDelFPButton = new QLabel(EnrollDelete);
    lblDelFPButton->setObjectName(QString::fromUtf8("lblDelFPButton"));
    lblDelFPButton->setGeometry(QRect(40, 50, 85, 40));
    lblDelFPButton->setPixmap(QPixmap(QString::fromUtf8(":/images/res/bg-button.png")));
    lblDelFPButton->setScaledContents(true);
    lblDelFPButtonTitle = new QLabel(EnrollDelete);
    lblDelFPButtonTitle->setObjectName(QString::fromUtf8("lblDelFPButtonTitle"));
    lblDelFPButtonTitle->setGeometry(QRect(40, 56, 85, 28));
    lblDelFPButtonTitle->setAlignment(Qt::AlignCenter);
    lblDelCardButton = new QLabel(EnrollDelete);
    lblDelCardButton->setObjectName(QString::fromUtf8("lblDelCardButton"));
    lblDelCardButton->setGeometry(QRect(40, 105, 85, 40));
    lblDelCardButton->setPixmap(QPixmap(QString::fromUtf8(":/images/res/bg-button.png")));
    lblDelCardButton->setScaledContents(true);
    lblDelCardButtonTitle = new QLabel(EnrollDelete);
    lblDelCardButtonTitle->setObjectName(QString::fromUtf8("lblDelCardButtonTitle"));
    lblDelCardButtonTitle->setGeometry(QRect(40, 111, 85, 28));
    lblDelCardButtonTitle->setAlignment(Qt::AlignCenter);
    lblDelPwdButton = new QLabel(EnrollDelete);
    lblDelPwdButton->setObjectName(QString::fromUtf8("lblDelPwdButton"));
    lblDelPwdButton->setGeometry(QRect(40, 160, 85, 40));
    lblDelPwdButton->setPixmap(QPixmap(QString::fromUtf8(":/images/res/bg-button.png")));
    lblDelPwdButton->setScaledContents(true);
    lblDelPwdButtonTitle = new QLabel(EnrollDelete);
    lblDelPwdButtonTitle->setObjectName(QString::fromUtf8("lblDelPwdButtonTitle"));
    lblDelPwdButtonTitle->setGeometry(QRect(40, 166, 85, 28));
    lblDelPwdButtonTitle->setAlignment(Qt::AlignCenter);
    lblDelAllButton = new QLabel(EnrollDelete);
    lblDelAllButton->setObjectName(QString::fromUtf8("lblDelAllButton"));
    lblDelAllButton->setGeometry(QRect(40, 215, 85, 40));
    lblDelAllButton->setPixmap(QPixmap(QString::fromUtf8(":/images/res/bg-button.png")));
    lblDelAllButton->setScaledContents(true);
    lblDelAllButtonTitle = new QLabel(EnrollDelete);
    lblDelAllButtonTitle->setObjectName(QString::fromUtf8("lblDelAllButtonTitle"));
    lblDelAllButtonTitle->setGeometry(QRect(40, 221, 85, 28));
    lblDelAllButtonTitle->setAlignment(Qt::AlignCenter);
    QWidget::setTabOrder(btnDeleteFP, btnDeleteCard);
    QWidget::setTabOrder(btnDeleteCard, btnDeletePwd);
    QWidget::setTabOrder(btnDeletePwd, btnDeleteAll);
    retranslateUi(EnrollDelete);

    QMetaObject::connectSlotsByName(EnrollDelete);
    } // setupUi

    void retranslateUi(QDialog *EnrollDelete)
    {
    EnrollDelete->setWindowTitle(QApplication::translate("EnrollDelete", "Dialog", 0, QApplication::UnicodeUTF8));
    lblBackground->setText(QApplication::translate("EnrollDelete", "", 0, QApplication::UnicodeUTF8));
    lblTitleBackground->setText(QApplication::translate("EnrollDelete", "", 0, QApplication::UnicodeUTF8));
    lblTitleText->setText(QApplication::translate("EnrollDelete", "Title", 0, QApplication::UnicodeUTF8));
    lblTitleIcon->setText(QApplication::translate("EnrollDelete", "", 0, QApplication::UnicodeUTF8));
    lblStatusIcon->setText(QApplication::translate("EnrollDelete", "", 0, QApplication::UnicodeUTF8));
    lblStatusText->setText(QApplication::translate("EnrollDelete", "Use Arrow & OK, ESC for return", 0, QApplication::UnicodeUTF8));
    lblPwdIcon->setText(QApplication::translate("EnrollDelete", "", 0, QApplication::UnicodeUTF8));
    lblFinger2->setText(QApplication::translate("EnrollDelete", "", 0, QApplication::UnicodeUTF8));
    lblFinger1->setText(QApplication::translate("EnrollDelete", "", 0, QApplication::UnicodeUTF8));
    lblFinger9->setText(QApplication::translate("EnrollDelete", "", 0, QApplication::UnicodeUTF8));
    lblFinger4->setText(QApplication::translate("EnrollDelete", "", 0, QApplication::UnicodeUTF8));
    lblFinger8->setText(QApplication::translate("EnrollDelete", "", 0, QApplication::UnicodeUTF8));
    lblFinger6->setText(QApplication::translate("EnrollDelete", "", 0, QApplication::UnicodeUTF8));
    lblFinger7->setText(QApplication::translate("EnrollDelete", "", 0, QApplication::UnicodeUTF8));
    btnDeleteCard->setText(QApplication::translate("EnrollDelete", "2. Delete Card", 0, QApplication::UnicodeUTF8));
    btnDeleteAll->setText(QApplication::translate("EnrollDelete", "4. Delete All   ", 0, QApplication::UnicodeUTF8));
    lblFingerIcon->setText(QApplication::translate("EnrollDelete", "", 0, QApplication::UnicodeUTF8));
    lblFinger5->setText(QApplication::translate("EnrollDelete", "", 0, QApplication::UnicodeUTF8));
    lblFinger10->setText(QApplication::translate("EnrollDelete", "", 0, QApplication::UnicodeUTF8));
    btnDeleteFP->setText(QApplication::translate("EnrollDelete", "1. Delete FP    ", 0, QApplication::UnicodeUTF8));
    lblCardIcon->setText(QApplication::translate("EnrollDelete", "", 0, QApplication::UnicodeUTF8));
    lblFinger3->setText(QApplication::translate("EnrollDelete", "", 0, QApplication::UnicodeUTF8));
    btnDeletePwd->setText(QApplication::translate("EnrollDelete", "3. Delete Pwd", 0, QApplication::UnicodeUTF8));
    lblEsc->setText(QApplication::translate("EnrollDelete", "", 0, QApplication::UnicodeUTF8));
    lblDelFPButton->setText(QApplication::translate("EnrollDelete", "", 0, QApplication::UnicodeUTF8));
    lblDelFPButtonTitle->setText(QApplication::translate("EnrollDelete", "1. Delete FP    ", 0, QApplication::UnicodeUTF8));
    lblDelCardButton->setText(QApplication::translate("EnrollDelete", "", 0, QApplication::UnicodeUTF8));
    lblDelCardButtonTitle->setText(QApplication::translate("EnrollDelete", "2. Delete Card", 0, QApplication::UnicodeUTF8));
    lblDelPwdButton->setText(QApplication::translate("EnrollDelete", "", 0, QApplication::UnicodeUTF8));
    lblDelPwdButtonTitle->setText(QApplication::translate("EnrollDelete", "3. Delete Pwd", 0, QApplication::UnicodeUTF8));
    lblDelAllButton->setText(QApplication::translate("EnrollDelete", "", 0, QApplication::UnicodeUTF8));
    lblDelAllButtonTitle->setText(QApplication::translate("EnrollDelete", "4. Delete All   ", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(EnrollDelete);
    } // retranslateUi

};

namespace Ui {
    class EnrollDelete: public Ui_EnrollDelete {};
} // namespace Ui

#endif // UI_ENROLL_2D_DELETE_H
