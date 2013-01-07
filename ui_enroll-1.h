#ifndef UI_ENROLL_2D_1_H
#define UI_ENROLL_2D_1_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>

class Ui_EnrollStep1
{
public:
    QLabel *lblBackground;
    QLabel *lblTitleBackground;
    QLabel *lblTitleText;
    QLabel *lblTitleIcon;
    QLabel *lblStatusIcon;
    QLabel *lblStatusText;
    QComboBox *comboPart;
    QLabel *lblID;
    QComboBox *comboLevel;
    QLineEdit *txtID;
    QLineEdit *txtName;
    QPushButton *btnOK;
    QLabel *lblPart;
    QLabel *lblLevel;
    QLabel *lblName;
    QPushButton *btnESC;
    QLabel *lblID1;
    QLabel *lblName1;
    QLabel *lblLevel1;
    QLabel *lblFinger;
    QLabel *lblCard;
    QLabel *lblPwd;
    QLabel *lblBackgroundFrame;
    QLabel *lblEsc;

    void setupUi(QDialog *EnrollStep1)
    {
    EnrollStep1->setObjectName(QString::fromUtf8("EnrollStep1"));
    EnrollStep1->resize(QSize(480, 272).expandedTo(EnrollStep1->minimumSizeHint()));
    lblBackground = new QLabel(EnrollStep1);
    lblBackground->setObjectName(QString::fromUtf8("lblBackground"));
    lblBackground->setGeometry(QRect(0, 0, 480, 272));
    lblBackground->setPixmap(QPixmap(QString::fromUtf8(":/images/res/bg-main.png")));
    lblTitleBackground = new QLabel(EnrollStep1);
    lblTitleBackground->setObjectName(QString::fromUtf8("lblTitleBackground"));
    lblTitleBackground->setGeometry(QRect(0, 0, 400, 34));
    lblTitleBackground->setPixmap(QPixmap(QString::fromUtf8(":/images/res/title-1.png")));
    lblTitleText = new QLabel(EnrollStep1);
    lblTitleText->setObjectName(QString::fromUtf8("lblTitleText"));
    lblTitleText->setGeometry(QRect(58, 3, 240, 28));
    lblTitleIcon = new QLabel(EnrollStep1);
    lblTitleIcon->setObjectName(QString::fromUtf8("lblTitleIcon"));
    lblTitleIcon->setGeometry(QRect(20, 5, 26, 26));
    lblTitleIcon->setPixmap(QPixmap(QString::fromUtf8(":/images/res/icon-normal.png")));
    lblTitleIcon->setScaledContents(true);
    lblStatusIcon = new QLabel(EnrollStep1);
    lblStatusIcon->setObjectName(QString::fromUtf8("lblStatusIcon"));
    lblStatusIcon->setGeometry(QRect(10, 230, 16, 16));
    lblStatusIcon->setPixmap(QPixmap(QString::fromUtf8(":/images/res/icon-help.png")));
    lblStatusText = new QLabel(EnrollStep1);
    lblStatusText->setObjectName(QString::fromUtf8("lblStatusText"));
    lblStatusText->setGeometry(QRect(50, 230, 270, 25));
    comboPart = new QComboBox(EnrollStep1);
    comboPart->setObjectName(QString::fromUtf8("comboPart"));
    comboPart->setGeometry(QRect(180, 120, 181, 22));
    lblID = new QLabel(EnrollStep1);
    lblID->setObjectName(QString::fromUtf8("lblID"));
    lblID->setGeometry(QRect(140, 50, 62, 20));
    comboLevel = new QComboBox(EnrollStep1);
    comboLevel->setObjectName(QString::fromUtf8("comboLevel"));
    comboLevel->setGeometry(QRect(180, 160, 181, 22));
    txtID = new QLineEdit(EnrollStep1);
    txtID->setObjectName(QString::fromUtf8("txtID"));
    txtID->setGeometry(QRect(210, 50, 131, 22));
    txtID->setMaxLength(9);
    txtID->setAlignment(Qt::AlignCenter);
    txtName = new QLineEdit(EnrollStep1);
    txtName->setObjectName(QString::fromUtf8("txtName"));
    txtName->setGeometry(QRect(210, 0, 131, 22));
    txtName->setMaxLength(8);
    txtName->setAlignment(Qt::AlignCenter);
    btnOK = new QPushButton(EnrollStep1);
    btnOK->setObjectName(QString::fromUtf8("btnOK"));
    btnOK->setGeometry(QRect(160, 190, 71, 25));
    lblPart = new QLabel(EnrollStep1);
    lblPart->setObjectName(QString::fromUtf8("lblPart"));
    lblPart->setGeometry(QRect(110, 120, 62, 20));
    lblLevel = new QLabel(EnrollStep1);
    lblLevel->setObjectName(QString::fromUtf8("lblLevel"));
    lblLevel->setGeometry(QRect(110, 160, 62, 20));
    lblName = new QLabel(EnrollStep1);
    lblName->setObjectName(QString::fromUtf8("lblName"));
    lblName->setGeometry(QRect(140, 80, 62, 20));
    btnESC = new QPushButton(EnrollStep1);
    btnESC->setObjectName(QString::fromUtf8("btnESC"));
    btnESC->setGeometry(QRect(280, 190, 71, 25));
    lblID1 = new QLabel(EnrollStep1);
    lblID1->setObjectName(QString::fromUtf8("lblID1"));
    lblID1->setGeometry(QRect(45, 60, 200, 50));
    lblName1 = new QLabel(EnrollStep1);
    lblName1->setObjectName(QString::fromUtf8("lblName1"));
    lblName1->setGeometry(QRect(45, 130, 200, 50));
    lblLevel1 = new QLabel(EnrollStep1);
    lblLevel1->setObjectName(QString::fromUtf8("lblLevel1"));
    lblLevel1->setGeometry(QRect(45, 200, 200, 50));
    lblFinger = new QLabel(EnrollStep1);
    lblFinger->setObjectName(QString::fromUtf8("lblFinger"));
    lblFinger->setGeometry(QRect(290, 60, 136, 50));
    lblCard = new QLabel(EnrollStep1);
    lblCard->setObjectName(QString::fromUtf8("lblCard"));
    lblCard->setGeometry(QRect(290, 130, 136, 50));
    lblPwd = new QLabel(EnrollStep1);
    lblPwd->setObjectName(QString::fromUtf8("lblPwd"));
    lblPwd->setGeometry(QRect(290, 200, 136, 50));
    lblBackgroundFrame = new QLabel(EnrollStep1);
    lblBackgroundFrame->setObjectName(QString::fromUtf8("lblBackgroundFrame"));
    lblBackgroundFrame->setGeometry(QRect(12, 34, 456, 238));
    lblBackgroundFrame->setPixmap(QPixmap(QString::fromUtf8(":/images/res/bg-menu.png")));
    lblEsc = new QLabel(EnrollStep1);
    lblEsc->setObjectName(QString::fromUtf8("lblEsc"));
    lblEsc->setGeometry(QRect(400, 0, 80, 34));
    lblEsc->setPixmap(QPixmap(QString::fromUtf8(":/images/res/esc.png")));
    QWidget::setTabOrder(txtID, txtName);
    QWidget::setTabOrder(txtName, comboLevel);
    QWidget::setTabOrder(comboLevel, comboPart);
    QWidget::setTabOrder(comboPart, btnOK);
    QWidget::setTabOrder(btnOK, btnESC);
    retranslateUi(EnrollStep1);

    comboLevel->setCurrentIndex(0);


    QMetaObject::connectSlotsByName(EnrollStep1);
    } // setupUi

    void retranslateUi(QDialog *EnrollStep1)
    {
    EnrollStep1->setWindowTitle(QApplication::translate("EnrollStep1", "Dialog", 0, QApplication::UnicodeUTF8));
    lblBackground->setText(QApplication::translate("EnrollStep1", "", 0, QApplication::UnicodeUTF8));
    lblTitleBackground->setText(QApplication::translate("EnrollStep1", "", 0, QApplication::UnicodeUTF8));
    lblTitleText->setText(QApplication::translate("EnrollStep1", "Title", 0, QApplication::UnicodeUTF8));
    lblTitleIcon->setText(QApplication::translate("EnrollStep1", "", 0, QApplication::UnicodeUTF8));
    lblStatusIcon->setText(QApplication::translate("EnrollStep1", "", 0, QApplication::UnicodeUTF8));
    lblStatusText->setText(QApplication::translate("EnrollStep1", "OK:Select Or T9Input,  ESC:Back ", 0, QApplication::UnicodeUTF8));
    lblID->setText(QApplication::translate("EnrollStep1", "ID        ", 0, QApplication::UnicodeUTF8));
    comboLevel->clear();
    comboLevel->addItem(QApplication::translate("EnrollStep1", "User", 0, QApplication::UnicodeUTF8));
    comboLevel->addItem(QApplication::translate("EnrollStep1", "Manager", 0, QApplication::UnicodeUTF8));
    comboLevel->addItem(QApplication::translate("EnrollStep1", "SManager", 0, QApplication::UnicodeUTF8));
    btnOK->setText(QApplication::translate("EnrollStep1", "OK", 0, QApplication::UnicodeUTF8));
    lblPart->setText(QApplication::translate("EnrollStep1", "Part      ", 0, QApplication::UnicodeUTF8));
    lblLevel->setText(QApplication::translate("EnrollStep1", "Level     ", 0, QApplication::UnicodeUTF8));
    lblName->setText(QApplication::translate("EnrollStep1", "Name      ", 0, QApplication::UnicodeUTF8));
    btnESC->setText(QApplication::translate("EnrollStep1", "ESC", 0, QApplication::UnicodeUTF8));
    lblID1->setText(QApplication::translate("EnrollStep1", "", 0, QApplication::UnicodeUTF8));
    lblName1->setText(QApplication::translate("EnrollStep1", "", 0, QApplication::UnicodeUTF8));
    lblLevel1->setText(QApplication::translate("EnrollStep1", "", 0, QApplication::UnicodeUTF8));
    lblFinger->setText(QApplication::translate("EnrollStep1", "", 0, QApplication::UnicodeUTF8));
    lblCard->setText(QApplication::translate("EnrollStep1", "", 0, QApplication::UnicodeUTF8));
    lblPwd->setText(QApplication::translate("EnrollStep1", "", 0, QApplication::UnicodeUTF8));
    lblBackgroundFrame->setText(QApplication::translate("EnrollStep1", "", 0, QApplication::UnicodeUTF8));
    lblEsc->setText(QApplication::translate("EnrollStep1", "", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(EnrollStep1);
    } // retranslateUi

};

namespace Ui {
    class EnrollStep1: public Ui_EnrollStep1 {};
} // namespace Ui

#endif // UI_ENROLL_2D_1_H
