#ifndef UI_USER_2D_DEL_H
#define UI_USER_2D_DEL_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>

class Ui_UserDel
{
public:
    QLabel *lblBackground;
    QLabel *lblTitleBackground;
    QLabel *lblTitleText;
    QLabel *lblTitleIcon;
    QLabel *lblStatusIcon;
    QLabel *lblStatusText;
    QPushButton *btnESC;
    QLabel *lblName;
    QLineEdit *txtTo;
    QLabel *lblStatus;
    QPushButton *btnOK;
    QLabel *lblID;
    QLabel *lblTo;
    QComboBox *comboDate;
    QLabel *lblDate;
    QLineEdit *txtFrom;
    QLabel *lblFrom;
    QLineEdit *txtName;
    QLineEdit *txtID;
    QLabel *lblEsc;
    QLabel *lblBackgroundFrame;
    QLabel *lblButtonBackgroud;
    QLabel *lblButtonTitle;

    void setupUi(QDialog *UserDel)
    {
    UserDel->setObjectName(QString::fromUtf8("UserDel"));
    UserDel->resize(QSize(480, 272).expandedTo(UserDel->minimumSizeHint()));
    lblBackground = new QLabel(UserDel);
    lblBackground->setObjectName(QString::fromUtf8("lblBackground"));
    lblBackground->setGeometry(QRect(0, 0, 480, 272));
    lblBackground->setPixmap(QPixmap(QString::fromUtf8(":/images/res/bg-main.png")));
    lblTitleBackground = new QLabel(UserDel);
    lblTitleBackground->setObjectName(QString::fromUtf8("lblTitleBackground"));
    lblTitleBackground->setGeometry(QRect(0, 0, 400, 34));
    lblTitleBackground->setPixmap(QPixmap(QString::fromUtf8(":/images/res/title-1.png")));
    lblTitleText = new QLabel(UserDel);
    lblTitleText->setObjectName(QString::fromUtf8("lblTitleText"));
    lblTitleText->setGeometry(QRect(40, 3, 273, 28));
    lblTitleIcon = new QLabel(UserDel);
    lblTitleIcon->setObjectName(QString::fromUtf8("lblTitleIcon"));
    lblTitleIcon->setGeometry(QRect(9, 5, 26, 26));
    lblTitleIcon->setPixmap(QPixmap(QString::fromUtf8(":/images/res/SEARCH_GLOG.png")));
    lblTitleIcon->setScaledContents(true);
    lblStatusIcon = new QLabel(UserDel);
    lblStatusIcon->setObjectName(QString::fromUtf8("lblStatusIcon"));
    lblStatusIcon->setGeometry(QRect(20, 205, 16, 16));
    lblStatusIcon->setPixmap(QPixmap(QString::fromUtf8(":/images/res/icon-help.png")));
    lblStatusText = new QLabel(UserDel);
    lblStatusText->setObjectName(QString::fromUtf8("lblStatusText"));
    lblStatusText->setGeometry(QRect(40, 200, 270, 25));
    btnESC = new QPushButton(UserDel);
    btnESC->setObjectName(QString::fromUtf8("btnESC"));
    btnESC->setGeometry(QRect(200, 162, 75, 24));
    lblName = new QLabel(UserDel);
    lblName->setObjectName(QString::fromUtf8("lblName"));
    lblName->setGeometry(QRect(60, 120, 50, 21));
    txtTo = new QLineEdit(UserDel);
    txtTo->setObjectName(QString::fromUtf8("txtTo"));
    txtTo->setEnabled(false);
    txtTo->setGeometry(QRect(70, 129, 91, 20));
    lblStatus = new QLabel(UserDel);
    lblStatus->setObjectName(QString::fromUtf8("lblStatus"));
    lblStatus->setGeometry(QRect(40, 50, 279, 21));
    lblStatus->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
    btnOK = new QPushButton(UserDel);
    btnOK->setObjectName(QString::fromUtf8("btnOK"));
    btnOK->setGeometry(QRect(70, 162, 75, 24));
    lblID = new QLabel(UserDel);
    lblID->setObjectName(QString::fromUtf8("lblID"));
    lblID->setGeometry(QRect(60, 90, 40, 21));
    lblTo = new QLabel(UserDel);
    lblTo->setObjectName(QString::fromUtf8("lblTo"));
    lblTo->setGeometry(QRect(20, 129, 40, 21));
    comboDate = new QComboBox(UserDel);
    comboDate->setObjectName(QString::fromUtf8("comboDate"));
    comboDate->setGeometry(QRect(70, 72, 231, 21));
    lblDate = new QLabel(UserDel);
    lblDate->setObjectName(QString::fromUtf8("lblDate"));
    lblDate->setGeometry(QRect(20, 72, 40, 16));
    txtFrom = new QLineEdit(UserDel);
    txtFrom->setObjectName(QString::fromUtf8("txtFrom"));
    txtFrom->setEnabled(false);
    txtFrom->setGeometry(QRect(70, 101, 91, 20));
    lblFrom = new QLabel(UserDel);
    lblFrom->setObjectName(QString::fromUtf8("lblFrom"));
    lblFrom->setGeometry(QRect(20, 99, 40, 21));
    txtName = new QLineEdit(UserDel);
    txtName->setObjectName(QString::fromUtf8("txtName"));
    txtName->setGeometry(QRect(113, 120, 131, 20));
    txtName->setMaxLength(8);
    txtName->setAlignment(Qt::AlignCenter);
    txtID = new QLineEdit(UserDel);
    txtID->setObjectName(QString::fromUtf8("txtID"));
    txtID->setGeometry(QRect(113, 90, 131, 20));
    txtID->setMaxLength(9);
    txtID->setAlignment(Qt::AlignCenter);
    lblEsc = new QLabel(UserDel);
    lblEsc->setObjectName(QString::fromUtf8("lblEsc"));
    lblEsc->setGeometry(QRect(400, 0, 80, 34));
    lblEsc->setPixmap(QPixmap(QString::fromUtf8(":/images/res/esc.png")));
    lblBackgroundFrame = new QLabel(UserDel);
    lblBackgroundFrame->setObjectName(QString::fromUtf8("lblBackgroundFrame"));
    lblBackgroundFrame->setGeometry(QRect(12, 34, 456, 238));
    lblBackgroundFrame->setPixmap(QPixmap(QString::fromUtf8(":/images/res/bg-menu.png")));
    lblButtonBackgroud = new QLabel(UserDel);
    lblButtonBackgroud->setObjectName(QString::fromUtf8("lblButtonBackgroud"));
    lblButtonBackgroud->setGeometry(QRect(330, 150, 80, 40));
    lblButtonBackgroud->setPixmap(QPixmap(QString::fromUtf8(":/images/res/bg-button.png")));
    lblButtonTitle = new QLabel(UserDel);
    lblButtonTitle->setObjectName(QString::fromUtf8("lblButtonTitle"));
    lblButtonTitle->setGeometry(QRect(345, 156, 50, 28));
    lblButtonTitle->setAlignment(Qt::AlignCenter);
    QWidget::setTabOrder(comboDate, txtFrom);
    QWidget::setTabOrder(txtFrom, txtTo);
    QWidget::setTabOrder(txtTo, txtID);
    QWidget::setTabOrder(txtID, txtName);
    QWidget::setTabOrder(txtName, btnOK);
    QWidget::setTabOrder(btnOK, btnESC);
    retranslateUi(UserDel);

    QMetaObject::connectSlotsByName(UserDel);
    } // setupUi

    void retranslateUi(QDialog *UserDel)
    {
    UserDel->setWindowTitle(QApplication::translate("UserDel", "Dialog", 0, QApplication::UnicodeUTF8));
    lblBackground->setText(QApplication::translate("UserDel", "", 0, QApplication::UnicodeUTF8));
    lblTitleBackground->setText(QApplication::translate("UserDel", "", 0, QApplication::UnicodeUTF8));
    lblTitleText->setText(QApplication::translate("UserDel", "Log Search", 0, QApplication::UnicodeUTF8));
    lblTitleIcon->setText(QApplication::translate("UserDel", "", 0, QApplication::UnicodeUTF8));
    lblStatusIcon->setText(QApplication::translate("UserDel", "", 0, QApplication::UnicodeUTF8));
    lblStatusText->setText(QApplication::translate("UserDel", "Use Arrow & OK, ESC for return, OK for T9Input", 0, QApplication::UnicodeUTF8));
    btnESC->setText(QApplication::translate("UserDel", "ESC", 0, QApplication::UnicodeUTF8));
    lblName->setText(QApplication::translate("UserDel", "Name", 0, QApplication::UnicodeUTF8));
    lblStatus->setText(QApplication::translate("UserDel", "Press finger or input card", 0, QApplication::UnicodeUTF8));
    btnOK->setText(QApplication::translate("UserDel", "Search", 0, QApplication::UnicodeUTF8));
    lblID->setText(QApplication::translate("UserDel", "ID", 0, QApplication::UnicodeUTF8));
    lblTo->setText(QApplication::translate("UserDel", "to", 0, QApplication::UnicodeUTF8));
    comboDate->clear();
    comboDate->addItem(QApplication::translate("UserDel", "All", 0, QApplication::UnicodeUTF8));
    comboDate->addItem(QApplication::translate("UserDel", "Last Week", 0, QApplication::UnicodeUTF8));
    comboDate->addItem(QApplication::translate("UserDel", "Past Month", 0, QApplication::UnicodeUTF8));
    comboDate->addItem(QApplication::translate("UserDel", "Specify Date", 0, QApplication::UnicodeUTF8));
    lblDate->setText(QApplication::translate("UserDel", "Date", 0, QApplication::UnicodeUTF8));
    lblFrom->setText(QApplication::translate("UserDel", "from", 0, QApplication::UnicodeUTF8));
    lblEsc->setText(QApplication::translate("UserDel", "", 0, QApplication::UnicodeUTF8));
    lblBackgroundFrame->setText(QApplication::translate("UserDel", "", 0, QApplication::UnicodeUTF8));
    lblButtonBackgroud->setText(QApplication::translate("UserDel", "", 0, QApplication::UnicodeUTF8));
    lblButtonTitle->setText(QApplication::translate("UserDel", "Search", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(UserDel);
    } // retranslateUi

};

namespace Ui {
    class UserDel: public Ui_UserDel {};
} // namespace Ui

#endif // UI_USER_2D_DEL_H
