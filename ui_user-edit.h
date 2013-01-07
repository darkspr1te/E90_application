#ifndef UI_USER_2D_EDIT_H
#define UI_USER_2D_EDIT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>

class Ui_UserEdit
{
public:
    QLabel *label;
    QLabel *lblStatusbar;
    QLabel *lblStatusText;
    QLabel *lblStatusIcon;
    QLabel *lblBackground;
    QComboBox *comboPart;
    QLineEdit *txtName;
    QComboBox *comboLevel;
    QPushButton *btnESC;
    QLabel *lblPart;
    QLabel *lblName;
    QPushButton *btnOK;
    QLabel *lblLevel;
    QLineEdit *txtID;
    QLabel *lblID;

    void setupUi(QDialog *UserEdit)
    {
    UserEdit->setObjectName(QString::fromUtf8("UserEdit"));
    UserEdit->resize(QSize(320, 240).expandedTo(UserEdit->minimumSizeHint()));
    label = new QLabel(UserEdit);
    label->setObjectName(QString::fromUtf8("label"));
    label->setGeometry(QRect(0, 200, 320, 40));
    label->setPixmap(QPixmap(QString::fromUtf8(":/images/res/bottom.png")));
    label->setScaledContents(true);
    lblStatusbar = new QLabel(UserEdit);
    lblStatusbar->setObjectName(QString::fromUtf8("lblStatusbar"));
    lblStatusbar->setGeometry(QRect(0, 0, 320, 40));
    lblStatusText = new QLabel(UserEdit);
    lblStatusText->setObjectName(QString::fromUtf8("lblStatusText"));
    lblStatusText->setGeometry(QRect(40, 200, 270, 25));
    lblStatusIcon = new QLabel(UserEdit);
    lblStatusIcon->setObjectName(QString::fromUtf8("lblStatusIcon"));
    lblStatusIcon->setGeometry(QRect(20, 205, 16, 16));
    lblStatusIcon->setPixmap(QPixmap(QString::fromUtf8(":/images/res/icon-help.png")));
    lblBackground = new QLabel(UserEdit);
    lblBackground->setObjectName(QString::fromUtf8("lblBackground"));
    lblBackground->setGeometry(QRect(20, 50, 270, 141));
    lblBackground->setPixmap(QPixmap(QString::fromUtf8(":/images/res/bg-inputbox.png")));
    lblBackground->setScaledContents(true);
    comboPart = new QComboBox(UserEdit);
    comboPart->setObjectName(QString::fromUtf8("comboPart"));
    comboPart->setGeometry(QRect(103, 137, 181, 22));
    txtName = new QLineEdit(UserEdit);
    txtName->setObjectName(QString::fromUtf8("txtName"));
    txtName->setGeometry(QRect(103, 82, 131, 22));
    txtName->setMaxLength(8);
    txtName->setAlignment(Qt::AlignCenter);
    comboLevel = new QComboBox(UserEdit);
    comboLevel->setObjectName(QString::fromUtf8("comboLevel"));
    comboLevel->setGeometry(QRect(103, 109, 181, 22));
    btnESC = new QPushButton(UserEdit);
    btnESC->setObjectName(QString::fromUtf8("btnESC"));
    btnESC->setGeometry(QRect(203, 163, 81, 25));
    lblPart = new QLabel(UserEdit);
    lblPart->setObjectName(QString::fromUtf8("lblPart"));
    lblPart->setGeometry(QRect(38, 137, 62, 20));
    lblName = new QLabel(UserEdit);
    lblName->setObjectName(QString::fromUtf8("lblName"));
    lblName->setGeometry(QRect(40, 82, 62, 20));
    btnOK = new QPushButton(UserEdit);
    btnOK->setObjectName(QString::fromUtf8("btnOK"));
    btnOK->setGeometry(QRect(103, 163, 81, 25));
    lblLevel = new QLabel(UserEdit);
    lblLevel->setObjectName(QString::fromUtf8("lblLevel"));
    lblLevel->setGeometry(QRect(40, 109, 62, 20));
    txtID = new QLineEdit(UserEdit);
    txtID->setObjectName(QString::fromUtf8("txtID"));
    txtID->setGeometry(QRect(103, 55, 131, 22));
    txtID->setMaxLength(9);
    txtID->setAlignment(Qt::AlignCenter);
    lblID = new QLabel(UserEdit);
    lblID->setObjectName(QString::fromUtf8("lblID"));
    lblID->setGeometry(QRect(40, 55, 62, 20));
    QWidget::setTabOrder(txtID, txtName);
    QWidget::setTabOrder(txtName, comboLevel);
    QWidget::setTabOrder(comboLevel, comboPart);
    QWidget::setTabOrder(comboPart, btnOK);
    QWidget::setTabOrder(btnOK, btnESC);
    retranslateUi(UserEdit);

    comboLevel->setCurrentIndex(0);


    QMetaObject::connectSlotsByName(UserEdit);
    } // setupUi

    void retranslateUi(QDialog *UserEdit)
    {
    UserEdit->setWindowTitle(QApplication::translate("UserEdit", "Dialog", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("UserEdit", "", 0, QApplication::UnicodeUTF8));
    lblStatusbar->setText(QApplication::translate("UserEdit", "", 0, QApplication::UnicodeUTF8));
    lblStatusText->setText(QApplication::translate("UserEdit", "OK: Select Or T9Input,   ESC: Return ", 0, QApplication::UnicodeUTF8));
    lblStatusIcon->setText(QApplication::translate("UserEdit", "", 0, QApplication::UnicodeUTF8));
    lblBackground->setText(QApplication::translate("UserEdit", "", 0, QApplication::UnicodeUTF8));
    comboLevel->clear();
    comboLevel->addItem(QApplication::translate("UserEdit", "User", 0, QApplication::UnicodeUTF8));
    comboLevel->addItem(QApplication::translate("UserEdit", "Manager", 0, QApplication::UnicodeUTF8));
    comboLevel->addItem(QApplication::translate("UserEdit", "SManager", 0, QApplication::UnicodeUTF8));
    btnESC->setText(QApplication::translate("UserEdit", "ESC", 0, QApplication::UnicodeUTF8));
    lblPart->setText(QApplication::translate("UserEdit", "Part      ", 0, QApplication::UnicodeUTF8));
    lblName->setText(QApplication::translate("UserEdit", "Name      ", 0, QApplication::UnicodeUTF8));
    btnOK->setText(QApplication::translate("UserEdit", "OK", 0, QApplication::UnicodeUTF8));
    lblLevel->setText(QApplication::translate("UserEdit", "Level     ", 0, QApplication::UnicodeUTF8));
    lblID->setText(QApplication::translate("UserEdit", "ID        ", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(UserEdit);
    } // retranslateUi

};

namespace Ui {
    class UserEdit: public Ui_UserEdit {};
} // namespace Ui

#endif // UI_USER_2D_EDIT_H
