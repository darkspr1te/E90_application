#ifndef UI_SEARCH_2D_USER_H
#define UI_SEARCH_2D_USER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>

class Ui_UserSearch
{
public:
    QLabel *lblBackground;
    QLabel *lblIcon;
    QLabel *lblID;
    QLineEdit *txtID;
    QLabel *lblStatus;
    QPushButton *btnOK;
    QPushButton *btnESC;
    QLabel *lblName;
    QLineEdit *txtName;
    QLabel *lblStatusbar;
    QLabel *label;
    QLabel *lblStatusText;
    QLabel *lblStatusIcon;
    QLabel *lblBackgroundFrame;
    QLabel *lblTitleBackground;
    QLabel *lblTitleIcon;
    QLabel *lblTitleText;
    QLabel *lblEsc;
    QLabel *lblButtonBackgroud;
    QLabel *lblButtonTitle;

    void setupUi(QDialog *UserSearch)
    {
    UserSearch->setObjectName(QString::fromUtf8("UserSearch"));
    UserSearch->resize(QSize(480, 272).expandedTo(UserSearch->minimumSizeHint()));
    lblBackground = new QLabel(UserSearch);
    lblBackground->setObjectName(QString::fromUtf8("lblBackground"));
    lblBackground->setGeometry(QRect(0, 0, 480, 272));
    lblBackground->setPixmap(QPixmap(QString::fromUtf8(":/images/res/bg-main.png")));
    lblBackground->setScaledContents(false);
    lblIcon = new QLabel(UserSearch);
    lblIcon->setObjectName(QString::fromUtf8("lblIcon"));
    lblIcon->setGeometry(QRect(30, 84, 40, 40));
    lblIcon->setPixmap(QPixmap(QString::fromUtf8(":/images/res/DATAVIEW.png")));
    lblIcon->setScaledContents(true);
    lblID = new QLabel(UserSearch);
    lblID->setObjectName(QString::fromUtf8("lblID"));
    lblID->setGeometry(QRect(80, 83, 61, 21));
    txtID = new QLineEdit(UserSearch);
    txtID->setObjectName(QString::fromUtf8("txtID"));
    txtID->setGeometry(QRect(150, 83, 113, 20));
    txtID->setMaxLength(9);
    lblStatus = new QLabel(UserSearch);
    lblStatus->setObjectName(QString::fromUtf8("lblStatus"));
    lblStatus->setGeometry(QRect(40, 50, 221, 21));
    lblStatus->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
    btnOK = new QPushButton(UserSearch);
    btnOK->setObjectName(QString::fromUtf8("btnOK"));
    btnOK->setGeometry(QRect(40, 140, 75, 24));
    btnESC = new QPushButton(UserSearch);
    btnESC->setObjectName(QString::fromUtf8("btnESC"));
    btnESC->setGeometry(QRect(180, 140, 75, 24));
    lblName = new QLabel(UserSearch);
    lblName->setObjectName(QString::fromUtf8("lblName"));
    lblName->setGeometry(QRect(80, 110, 61, 21));
    txtName = new QLineEdit(UserSearch);
    txtName->setObjectName(QString::fromUtf8("txtName"));
    txtName->setGeometry(QRect(150, 110, 113, 20));
    txtName->setMaxLength(8);
    lblStatusbar = new QLabel(UserSearch);
    lblStatusbar->setObjectName(QString::fromUtf8("lblStatusbar"));
    lblStatusbar->setGeometry(QRect(0, 200, 320, 40));
    label = new QLabel(UserSearch);
    label->setObjectName(QString::fromUtf8("label"));
    label->setGeometry(QRect(0, 200, 320, 40));
    label->setPixmap(QPixmap(QString::fromUtf8(":/images/res/bottom.png")));
    label->setScaledContents(true);
    lblStatusText = new QLabel(UserSearch);
    lblStatusText->setObjectName(QString::fromUtf8("lblStatusText"));
    lblStatusText->setGeometry(QRect(40, 200, 270, 25));
    lblStatusIcon = new QLabel(UserSearch);
    lblStatusIcon->setObjectName(QString::fromUtf8("lblStatusIcon"));
    lblStatusIcon->setGeometry(QRect(20, 205, 16, 16));
    lblStatusIcon->setPixmap(QPixmap(QString::fromUtf8(":/images/res/icon-help.png")));
    lblBackgroundFrame = new QLabel(UserSearch);
    lblBackgroundFrame->setObjectName(QString::fromUtf8("lblBackgroundFrame"));
    lblBackgroundFrame->setGeometry(QRect(12, 34, 456, 238));
    lblBackgroundFrame->setPixmap(QPixmap(QString::fromUtf8(":/images/res/bg-menu.png")));
    lblTitleBackground = new QLabel(UserSearch);
    lblTitleBackground->setObjectName(QString::fromUtf8("lblTitleBackground"));
    lblTitleBackground->setGeometry(QRect(0, 0, 400, 34));
    lblTitleBackground->setPixmap(QPixmap(QString::fromUtf8(":/images/res/title-1.png")));
    lblTitleIcon = new QLabel(UserSearch);
    lblTitleIcon->setObjectName(QString::fromUtf8("lblTitleIcon"));
    lblTitleIcon->setGeometry(QRect(9, 5, 26, 26));
    lblTitleIcon->setPixmap(QPixmap(QString::fromUtf8(":/images/res/SEARCH_USER.png")));
    lblTitleIcon->setScaledContents(true);
    lblTitleText = new QLabel(UserSearch);
    lblTitleText->setObjectName(QString::fromUtf8("lblTitleText"));
    lblTitleText->setGeometry(QRect(40, 3, 273, 28));
    lblEsc = new QLabel(UserSearch);
    lblEsc->setObjectName(QString::fromUtf8("lblEsc"));
    lblEsc->setGeometry(QRect(400, 0, 80, 34));
    lblEsc->setPixmap(QPixmap(QString::fromUtf8(":/images/res/esc.png")));
    lblButtonBackgroud = new QLabel(UserSearch);
    lblButtonBackgroud->setObjectName(QString::fromUtf8("lblButtonBackgroud"));
    lblButtonBackgroud->setGeometry(QRect(330, 150, 80, 40));
    lblButtonBackgroud->setPixmap(QPixmap(QString::fromUtf8(":/images/res/bg-button.png")));
    lblButtonTitle = new QLabel(UserSearch);
    lblButtonTitle->setObjectName(QString::fromUtf8("lblButtonTitle"));
    lblButtonTitle->setGeometry(QRect(345, 156, 50, 28));
    lblButtonTitle->setAlignment(Qt::AlignCenter);
    QWidget::setTabOrder(txtID, txtName);
    QWidget::setTabOrder(txtName, btnOK);
    QWidget::setTabOrder(btnOK, btnESC);
    retranslateUi(UserSearch);

    QMetaObject::connectSlotsByName(UserSearch);
    } // setupUi

    void retranslateUi(QDialog *UserSearch)
    {
    UserSearch->setWindowTitle(QApplication::translate("UserSearch", "Dialog", 0, QApplication::UnicodeUTF8));
    lblBackground->setText(QApplication::translate("UserSearch", "", 0, QApplication::UnicodeUTF8));
    lblIcon->setText(QApplication::translate("UserSearch", "", 0, QApplication::UnicodeUTF8));
    lblID->setText(QApplication::translate("UserSearch", "User ID", 0, QApplication::UnicodeUTF8));
    lblStatus->setText(QApplication::translate("UserSearch", "Press finger or input card", 0, QApplication::UnicodeUTF8));
    btnOK->setText(QApplication::translate("UserSearch", "OK", 0, QApplication::UnicodeUTF8));
    btnESC->setText(QApplication::translate("UserSearch", "ESC", 0, QApplication::UnicodeUTF8));
    lblName->setText(QApplication::translate("UserSearch", "Name", 0, QApplication::UnicodeUTF8));
    lblStatusbar->setText(QApplication::translate("UserSearch", "", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("UserSearch", "", 0, QApplication::UnicodeUTF8));
    lblStatusText->setText(QApplication::translate("UserSearch", "OK: Search Or T9Input, ESC: Return ", 0, QApplication::UnicodeUTF8));
    lblStatusIcon->setText(QApplication::translate("UserSearch", "", 0, QApplication::UnicodeUTF8));
    lblBackgroundFrame->setText(QApplication::translate("UserSearch", "", 0, QApplication::UnicodeUTF8));
    lblTitleBackground->setText(QApplication::translate("UserSearch", "", 0, QApplication::UnicodeUTF8));
    lblTitleIcon->setText(QApplication::translate("UserSearch", "", 0, QApplication::UnicodeUTF8));
    lblTitleText->setText(QApplication::translate("UserSearch", "User Search", 0, QApplication::UnicodeUTF8));
    lblEsc->setText(QApplication::translate("UserSearch", "", 0, QApplication::UnicodeUTF8));
    lblButtonBackgroud->setText(QApplication::translate("UserSearch", "", 0, QApplication::UnicodeUTF8));
    lblButtonTitle->setText(QApplication::translate("UserSearch", "OK", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(UserSearch);
    } // retranslateUi

};

namespace Ui {
    class UserSearch: public Ui_UserSearch {};
} // namespace Ui

#endif // UI_SEARCH_2D_USER_H
