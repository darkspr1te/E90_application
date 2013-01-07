#ifndef UI_ENROLL_2D_FP_H
#define UI_ENROLL_2D_FP_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>

class Ui_EnrollFP
{
public:
    QLabel *lblBackground;
    QLabel *lblTitleBackground;
    QLabel *lblTitleText;
    QLabel *lblTitleIcon;
    QLabel *lblStatusIcon;
    QLabel *lblStatusText;
    QLineEdit *txtFpNumber;
    QLabel *lblEnrollStatus3;
    QLabel *lblEnrollStatus1;
    QLabel *lblFpNumber;
    QLabel *lblEnrollStatus2;
    QLabel *lblEnrollStatus;
    QLabel *lblFpArea;
    QLabel *lblEsc;
    QLabel *lblOKButtonBackgroud;
    QLabel *lblNextButtonBackgroud;
    QLabel *lblRetryButtonBackgroud;
    QLabel *lblOKButtonTitle;
    QLabel *lblNextButtonTitle;
    QLabel *lblRetryButtonTitle;

    void setupUi(QDialog *EnrollFP)
    {
    EnrollFP->setObjectName(QString::fromUtf8("EnrollFP"));
    EnrollFP->resize(QSize(480, 272).expandedTo(EnrollFP->minimumSizeHint()));
    lblBackground = new QLabel(EnrollFP);
    lblBackground->setObjectName(QString::fromUtf8("lblBackground"));
    lblBackground->setGeometry(QRect(0, 0, 480, 272));
    lblBackground->setPixmap(QPixmap(QString::fromUtf8(":/images/res/bg-main.png")));
    lblTitleBackground = new QLabel(EnrollFP);
    lblTitleBackground->setObjectName(QString::fromUtf8("lblTitleBackground"));
    lblTitleBackground->setGeometry(QRect(0, 0, 400, 34));
    lblTitleBackground->setPixmap(QPixmap(QString::fromUtf8(":/images/res/title-1.png")));
    lblTitleText = new QLabel(EnrollFP);
    lblTitleText->setObjectName(QString::fromUtf8("lblTitleText"));
    lblTitleText->setGeometry(QRect(40, 3, 273, 28));
    lblTitleIcon = new QLabel(EnrollFP);
    lblTitleIcon->setObjectName(QString::fromUtf8("lblTitleIcon"));
    lblTitleIcon->setGeometry(QRect(9, 5, 26, 26));
    lblTitleIcon->setPixmap(QPixmap(QString::fromUtf8(":/images/res/icon-finger.png")));
    lblTitleIcon->setScaledContents(true);
    lblStatusIcon = new QLabel(EnrollFP);
    lblStatusIcon->setObjectName(QString::fromUtf8("lblStatusIcon"));
    lblStatusIcon->setGeometry(QRect(40, 240, 16, 16));
    lblStatusIcon->setPixmap(QPixmap(QString::fromUtf8(":/images/res/icon-help.png")));
    lblStatusText = new QLabel(EnrollFP);
    lblStatusText->setObjectName(QString::fromUtf8("lblStatusText"));
    lblStatusText->setGeometry(QRect(70, 240, 301, 25));
    txtFpNumber = new QLineEdit(EnrollFP);
    txtFpNumber->setObjectName(QString::fromUtf8("txtFpNumber"));
    txtFpNumber->setGeometry(QRect(220, 30, 71, 20));
    txtFpNumber->setReadOnly(true);
    lblEnrollStatus3 = new QLabel(EnrollFP);
    lblEnrollStatus3->setObjectName(QString::fromUtf8("lblEnrollStatus3"));
    lblEnrollStatus3->setEnabled(false);
    lblEnrollStatus3->setGeometry(QRect(50, 190, 32, 32));
    lblEnrollStatus3->setPixmap(QPixmap(QString::fromUtf8(":/images/res/icon-finger.png")));
    lblEnrollStatus3->setScaledContents(true);
    lblEnrollStatus1 = new QLabel(EnrollFP);
    lblEnrollStatus1->setObjectName(QString::fromUtf8("lblEnrollStatus1"));
    lblEnrollStatus1->setEnabled(false);
    lblEnrollStatus1->setGeometry(QRect(50, 70, 32, 32));
    lblEnrollStatus1->setPixmap(QPixmap(QString::fromUtf8(":/images/res/icon-finger.png")));
    lblEnrollStatus1->setScaledContents(true);
    lblFpNumber = new QLabel(EnrollFP);
    lblFpNumber->setObjectName(QString::fromUtf8("lblFpNumber"));
    lblFpNumber->setGeometry(QRect(160, 30, 61, 21));
    lblEnrollStatus2 = new QLabel(EnrollFP);
    lblEnrollStatus2->setObjectName(QString::fromUtf8("lblEnrollStatus2"));
    lblEnrollStatus2->setEnabled(false);
    lblEnrollStatus2->setGeometry(QRect(50, 130, 32, 32));
    lblEnrollStatus2->setPixmap(QPixmap(QString::fromUtf8(":/images/res/icon-finger.png")));
    lblEnrollStatus2->setScaledContents(true);
    lblEnrollStatus = new QLabel(EnrollFP);
    lblEnrollStatus->setObjectName(QString::fromUtf8("lblEnrollStatus"));
    lblEnrollStatus->setGeometry(QRect(140, 60, 161, 30));
    lblEnrollStatus->setAlignment(Qt::AlignCenter);
    lblFpArea = new QLabel(EnrollFP);
    lblFpArea->setObjectName(QString::fromUtf8("lblFpArea"));
    lblFpArea->setGeometry(QRect(170, 100, 105, 130));
    lblFpArea->setPixmap(QPixmap(QString::fromUtf8(":/images/res/area-fingerprint.png")));
    lblFpArea->setScaledContents(false);
    lblEsc = new QLabel(EnrollFP);
    lblEsc->setObjectName(QString::fromUtf8("lblEsc"));
    lblEsc->setGeometry(QRect(400, 0, 80, 34));
    lblEsc->setPixmap(QPixmap(QString::fromUtf8(":/images/res/esc.png")));
    lblOKButtonBackgroud = new QLabel(EnrollFP);
    lblOKButtonBackgroud->setObjectName(QString::fromUtf8("lblOKButtonBackgroud"));
    lblOKButtonBackgroud->setGeometry(QRect(340, 60, 100, 40));
    lblOKButtonBackgroud->setPixmap(QPixmap(QString::fromUtf8(":/images/res/bg-button.png")));
    lblOKButtonBackgroud->setScaledContents(true);
    lblNextButtonBackgroud = new QLabel(EnrollFP);
    lblNextButtonBackgroud->setObjectName(QString::fromUtf8("lblNextButtonBackgroud"));
    lblNextButtonBackgroud->setGeometry(QRect(340, 130, 100, 40));
    lblNextButtonBackgroud->setPixmap(QPixmap(QString::fromUtf8(":/images/res/bg-button.png")));
    lblNextButtonBackgroud->setScaledContents(true);
    lblRetryButtonBackgroud = new QLabel(EnrollFP);
    lblRetryButtonBackgroud->setObjectName(QString::fromUtf8("lblRetryButtonBackgroud"));
    lblRetryButtonBackgroud->setGeometry(QRect(340, 200, 100, 40));
    lblRetryButtonBackgroud->setPixmap(QPixmap(QString::fromUtf8(":/images/res/bg-button.png")));
    lblRetryButtonBackgroud->setScaledContents(true);
    lblOKButtonTitle = new QLabel(EnrollFP);
    lblOKButtonTitle->setObjectName(QString::fromUtf8("lblOKButtonTitle"));
    lblOKButtonTitle->setGeometry(QRect(350, 66, 80, 28));
    lblOKButtonTitle->setAlignment(Qt::AlignCenter);
    lblNextButtonTitle = new QLabel(EnrollFP);
    lblNextButtonTitle->setObjectName(QString::fromUtf8("lblNextButtonTitle"));
    lblNextButtonTitle->setGeometry(QRect(350, 136, 80, 28));
    lblNextButtonTitle->setAlignment(Qt::AlignCenter);
    lblRetryButtonTitle = new QLabel(EnrollFP);
    lblRetryButtonTitle->setObjectName(QString::fromUtf8("lblRetryButtonTitle"));
    lblRetryButtonTitle->setGeometry(QRect(350, 206, 80, 28));
    lblRetryButtonTitle->setScaledContents(false);
    lblRetryButtonTitle->setAlignment(Qt::AlignCenter);
    retranslateUi(EnrollFP);

    QMetaObject::connectSlotsByName(EnrollFP);
    } // setupUi

    void retranslateUi(QDialog *EnrollFP)
    {
    EnrollFP->setWindowTitle(QApplication::translate("EnrollFP", "Dialog", 0, QApplication::UnicodeUTF8));
    lblBackground->setText(QApplication::translate("EnrollFP", "", 0, QApplication::UnicodeUTF8));
    lblTitleBackground->setText(QApplication::translate("EnrollFP", "", 0, QApplication::UnicodeUTF8));
    lblTitleText->setText(QApplication::translate("EnrollFP", "Title", 0, QApplication::UnicodeUTF8));
    lblTitleIcon->setText(QApplication::translate("EnrollFP", "", 0, QApplication::UnicodeUTF8));
    lblStatusIcon->setText(QApplication::translate("EnrollFP", "", 0, QApplication::UnicodeUTF8));
    lblStatusText->setText(QApplication::translate("EnrollFP", "EnrollFP Status", 0, QApplication::UnicodeUTF8));
    lblEnrollStatus3->setText(QApplication::translate("EnrollFP", "", 0, QApplication::UnicodeUTF8));
    lblEnrollStatus1->setText(QApplication::translate("EnrollFP", "", 0, QApplication::UnicodeUTF8));
    lblFpNumber->setText(QApplication::translate("EnrollFP", "FP Number :", 0, QApplication::UnicodeUTF8));
    lblEnrollStatus2->setText(QApplication::translate("EnrollFP", "", 0, QApplication::UnicodeUTF8));
    lblEnrollStatus->setText(QApplication::translate("EnrollFP", "Enroll Status", 0, QApplication::UnicodeUTF8));
    lblFpArea->setText(QApplication::translate("EnrollFP", "", 0, QApplication::UnicodeUTF8));
    lblEsc->setText(QApplication::translate("EnrollFP", "", 0, QApplication::UnicodeUTF8));
    lblOKButtonBackgroud->setText(QApplication::translate("EnrollFP", "", 0, QApplication::UnicodeUTF8));
    lblNextButtonBackgroud->setText(QApplication::translate("EnrollFP", "", 0, QApplication::UnicodeUTF8));
    lblRetryButtonBackgroud->setText(QApplication::translate("EnrollFP", "", 0, QApplication::UnicodeUTF8));
    lblOKButtonTitle->setText(QApplication::translate("EnrollFP", "OK", 0, QApplication::UnicodeUTF8));
    lblNextButtonTitle->setText(QApplication::translate("EnrollFP", "Next", 0, QApplication::UnicodeUTF8));
    lblRetryButtonTitle->setText(QApplication::translate("EnrollFP", "Retry", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(EnrollFP);
    } // retranslateUi

};

namespace Ui {
    class EnrollFP: public Ui_EnrollFP {};
} // namespace Ui

#endif // UI_ENROLL_2D_FP_H
