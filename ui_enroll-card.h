#ifndef UI_ENROLL_2D_CARD_H
#define UI_ENROLL_2D_CARD_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>

class Ui_EnrollCard
{
public:
    QLabel *lblBackground;
    QLabel *lblTitleBackground;
    QLabel *lblTitleText;
    QLabel *lblTitleIcon;
    QLabel *lblStatusIcon;
    QLabel *lblStatusText;
    QLineEdit *txtCardNumber;
    QPushButton *btnESC;
    QPushButton *btnOK;
    QLabel *lblCardNumber;
    QLabel *lblEnrollStatus;
    QLabel *lblEsc;
    QLabel *lblButtonBackgroud;
    QLabel *lblButtonTitle;

    void setupUi(QDialog *EnrollCard)
    {
    EnrollCard->setObjectName(QString::fromUtf8("EnrollCard"));
    EnrollCard->resize(QSize(480, 272).expandedTo(EnrollCard->minimumSizeHint()));
    lblBackground = new QLabel(EnrollCard);
    lblBackground->setObjectName(QString::fromUtf8("lblBackground"));
    lblBackground->setGeometry(QRect(0, 0, 480, 272));
    lblBackground->setPixmap(QPixmap(QString::fromUtf8(":/images/res/bg-main.png")));
    lblTitleBackground = new QLabel(EnrollCard);
    lblTitleBackground->setObjectName(QString::fromUtf8("lblTitleBackground"));
    lblTitleBackground->setGeometry(QRect(0, 0, 400, 34));
    lblTitleBackground->setPixmap(QPixmap(QString::fromUtf8(":/images/res/title-1.png")));
    lblTitleText = new QLabel(EnrollCard);
    lblTitleText->setObjectName(QString::fromUtf8("lblTitleText"));
    lblTitleText->setGeometry(QRect(40, 3, 273, 28));
    lblTitleIcon = new QLabel(EnrollCard);
    lblTitleIcon->setObjectName(QString::fromUtf8("lblTitleIcon"));
    lblTitleIcon->setGeometry(QRect(9, 5, 26, 26));
    lblTitleIcon->setPixmap(QPixmap(QString::fromUtf8(":/images/res/icon-card.png")));
    lblTitleIcon->setScaledContents(true);
    lblStatusIcon = new QLabel(EnrollCard);
    lblStatusIcon->setObjectName(QString::fromUtf8("lblStatusIcon"));
    lblStatusIcon->setGeometry(QRect(20, 205, 16, 16));
    lblStatusIcon->setPixmap(QPixmap(QString::fromUtf8(":/images/res/icon-help.png")));
    lblStatusText = new QLabel(EnrollCard);
    lblStatusText->setObjectName(QString::fromUtf8("lblStatusText"));
    lblStatusText->setGeometry(QRect(40, 200, 270, 25));
    txtCardNumber = new QLineEdit(EnrollCard);
    txtCardNumber->setObjectName(QString::fromUtf8("txtCardNumber"));
    txtCardNumber->setGeometry(QRect(170, 120, 161, 20));
    btnESC = new QPushButton(EnrollCard);
    btnESC->setObjectName(QString::fromUtf8("btnESC"));
    btnESC->setGeometry(QRect(120, 230, 75, 24));
    btnOK = new QPushButton(EnrollCard);
    btnOK->setObjectName(QString::fromUtf8("btnOK"));
    btnOK->setGeometry(QRect(300, 220, 80, 40));
    lblCardNumber = new QLabel(EnrollCard);
    lblCardNumber->setObjectName(QString::fromUtf8("lblCardNumber"));
    lblCardNumber->setGeometry(QRect(100, 120, 61, 21));
    lblEnrollStatus = new QLabel(EnrollCard);
    lblEnrollStatus->setObjectName(QString::fromUtf8("lblEnrollStatus"));
    lblEnrollStatus->setGeometry(QRect(37, 60, 191, 21));
    lblEsc = new QLabel(EnrollCard);
    lblEsc->setObjectName(QString::fromUtf8("lblEsc"));
    lblEsc->setGeometry(QRect(400, 0, 80, 34));
    lblEsc->setPixmap(QPixmap(QString::fromUtf8(":/images/res/esc.png")));
    lblButtonBackgroud = new QLabel(EnrollCard);
    lblButtonBackgroud->setObjectName(QString::fromUtf8("lblButtonBackgroud"));
    lblButtonBackgroud->setGeometry(QRect(200, 190, 80, 40));
    lblButtonBackgroud->setPixmap(QPixmap(QString::fromUtf8(":/images/res/bg-button.png")));
    lblButtonTitle = new QLabel(EnrollCard);
    lblButtonTitle->setObjectName(QString::fromUtf8("lblButtonTitle"));
    lblButtonTitle->setGeometry(QRect(215, 196, 50, 28));
    lblButtonTitle->setAlignment(Qt::AlignCenter);
    retranslateUi(EnrollCard);

    QMetaObject::connectSlotsByName(EnrollCard);
    } // setupUi

    void retranslateUi(QDialog *EnrollCard)
    {
    EnrollCard->setWindowTitle(QApplication::translate("EnrollCard", "Dialog", 0, QApplication::UnicodeUTF8));
    lblBackground->setText(QApplication::translate("EnrollCard", "", 0, QApplication::UnicodeUTF8));
    lblTitleBackground->setText(QApplication::translate("EnrollCard", "", 0, QApplication::UnicodeUTF8));
    lblTitleText->setText(QApplication::translate("EnrollCard", "Title", 0, QApplication::UnicodeUTF8));
    lblTitleIcon->setText(QApplication::translate("EnrollCard", "", 0, QApplication::UnicodeUTF8));
    lblStatusIcon->setText(QApplication::translate("EnrollCard", "", 0, QApplication::UnicodeUTF8));
    lblStatusText->setText(QApplication::translate("EnrollCard", "OK: Select  ESC: Return \342\226\262Retry", 0, QApplication::UnicodeUTF8));
    btnESC->setText(QApplication::translate("EnrollCard", "ESC", 0, QApplication::UnicodeUTF8));
    btnOK->setText(QApplication::translate("EnrollCard", "OK", 0, QApplication::UnicodeUTF8));
    lblCardNumber->setText(QApplication::translate("EnrollCard", "CardNo: ", 0, QApplication::UnicodeUTF8));
    lblEnrollStatus->setText(QApplication::translate("EnrollCard", "Input your card", 0, QApplication::UnicodeUTF8));
    lblEsc->setText(QApplication::translate("EnrollCard", "", 0, QApplication::UnicodeUTF8));
    lblButtonBackgroud->setText(QApplication::translate("EnrollCard", "", 0, QApplication::UnicodeUTF8));
    lblButtonTitle->setText(QApplication::translate("EnrollCard", "OK", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(EnrollCard);
    } // retranslateUi

};

namespace Ui {
    class EnrollCard: public Ui_EnrollCard {};
} // namespace Ui

#endif // UI_ENROLL_2D_CARD_H
