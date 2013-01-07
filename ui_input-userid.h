#ifndef UI_INPUT_2D_USERID_H
#define UI_INPUT_2D_USERID_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>

class Ui_UserIDInput
{
public:
    QLabel *lblBackground;
    QLabel *lblIcon;
    QLabel *lblID;
    QLineEdit *txtID;
    QLabel *lblStatus;
    QPushButton *btnOK;
    QPushButton *btnESC;
    QLabel *lblIconPWD;
    QLabel *lblPWD;
    QLineEdit *txtPWD;
    QLabel *lbl0;
    QLabel *lbl1;
    QLabel *lbl2;
    QLabel *lbl3;
    QLabel *lbl4;
    QLabel *lbl5;
    QLabel *lblOK;
    QLabel *lblESC;
    QLabel *lbl6;
    QLabel *lbl7;
    QLabel *lbl8;
    QLabel *lbl9;
    QLabel *lblPoint;
    QLabel *lblBack;
    QLineEdit *txtNUM;
    QLabel *lblPoint1;
    QLabel *lblPoint2;
    QLabel *lblBackSpace;

    void setupUi(QDialog *UserIDInput)
    {
    UserIDInput->setObjectName(QString::fromUtf8("UserIDInput"));
    UserIDInput->resize(QSize(480, 272).expandedTo(UserIDInput->minimumSizeHint()));
    UserIDInput->setMouseTracking(false);
    UserIDInput->setAcceptDrops(false);
    lblBackground = new QLabel(UserIDInput);
    lblBackground->setObjectName(QString::fromUtf8("lblBackground"));
    lblBackground->setGeometry(QRect(0, 0, 480, 272));
    lblBackground->setPixmap(QPixmap(QString::fromUtf8(":/images/res/bg-main.png")));
    lblBackground->setScaledContents(true);
    lblIcon = new QLabel(UserIDInput);
    lblIcon->setObjectName(QString::fromUtf8("lblIcon"));
    lblIcon->setGeometry(QRect(10, 10, 40, 40));
    lblIcon->setPixmap(QPixmap(QString::fromUtf8(":/images/res/input-userid.png")));
    lblIcon->setScaledContents(true);
    lblID = new QLabel(UserIDInput);
    lblID->setObjectName(QString::fromUtf8("lblID"));
    lblID->setGeometry(QRect(60, 30, 65, 21));
    txtID = new QLineEdit(UserIDInput);
    txtID->setObjectName(QString::fromUtf8("txtID"));
    txtID->setGeometry(QRect(130, 20, 231, 40));
    txtID->setMinimumSize(QSize(0, 0));
    txtID->setSizeIncrement(QSize(0, 0));
    txtID->setBaseSize(QSize(0, 0));
    QFont font;
    font.setPointSize(20);
    font.setBold(false);
    font.setItalic(false);
    font.setUnderline(false);
    font.setStrikeOut(false);
    txtID->setFont(font);
    txtID->setAutoFillBackground(false);
    txtID->setMaxLength(9);
    txtID->setDragEnabled(false);
    lblStatus = new QLabel(UserIDInput);
    lblStatus->setObjectName(QString::fromUtf8("lblStatus"));
    lblStatus->setGeometry(QRect(280, 20, 181, 21));
    lblStatus->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
    btnOK = new QPushButton(UserIDInput);
    btnOK->setObjectName(QString::fromUtf8("btnOK"));
    btnOK->setGeometry(QRect(360, 20, 52, 53));
    QFont font1;
    font1.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
    font1.setPointSize(16);
    font1.setBold(true);
    font1.setItalic(false);
    font1.setUnderline(false);
    font1.setWeight(75);
    font1.setStrikeOut(false);
    btnOK->setFont(font1);
    btnOK->setFocusPolicy(Qt::StrongFocus);
    btnESC = new QPushButton(UserIDInput);
    btnESC->setObjectName(QString::fromUtf8("btnESC"));
    btnESC->setGeometry(QRect(420, 20, 52, 53));
    QFont font2;
    font2.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
    font2.setPointSize(16);
    font2.setBold(true);
    font2.setItalic(false);
    font2.setUnderline(false);
    font2.setWeight(75);
    font2.setStrikeOut(false);
    btnESC->setFont(font2);
    btnESC->setFocusPolicy(Qt::StrongFocus);
    lblIconPWD = new QLabel(UserIDInput);
    lblIconPWD->setObjectName(QString::fromUtf8("lblIconPWD"));
    lblIconPWD->setGeometry(QRect(10, 10, 40, 40));
    lblIconPWD->setPixmap(QPixmap(QString::fromUtf8(":/images/res/input-pwd.png")));
    lblPWD = new QLabel(UserIDInput);
    lblPWD->setObjectName(QString::fromUtf8("lblPWD"));
    lblPWD->setGeometry(QRect(60, 20, 65, 21));
    txtPWD = new QLineEdit(UserIDInput);
    txtPWD->setObjectName(QString::fromUtf8("txtPWD"));
    txtPWD->setGeometry(QRect(130, 16, 231, 40));
    txtPWD->setMaxLength(4);
    txtPWD->setEchoMode(QLineEdit::Password);
    lbl0 = new QLabel(UserIDInput);
    lbl0->setObjectName(QString::fromUtf8("lbl0"));
    lbl0->setGeometry(QRect(252, 210, 52, 53));
    lbl0->setPixmap(QPixmap(QString::fromUtf8(":/images/res/input-0.png")));
    lbl1 = new QLabel(UserIDInput);
    lbl1->setObjectName(QString::fromUtf8("lbl1"));
    lbl1->setGeometry(QRect(24, 80, 52, 53));
    lbl1->setPixmap(QPixmap(QString::fromUtf8(":/images/res/input-1.png")));
    lbl2 = new QLabel(UserIDInput);
    lbl2->setObjectName(QString::fromUtf8("lbl2"));
    lbl2->setGeometry(QRect(100, 80, 52, 53));
    lbl2->setPixmap(QPixmap(QString::fromUtf8(":/images/res/input-2.png")));
    lbl3 = new QLabel(UserIDInput);
    lbl3->setObjectName(QString::fromUtf8("lbl3"));
    lbl3->setGeometry(QRect(176, 80, 52, 53));
    lbl3->setPixmap(QPixmap(QString::fromUtf8(":/images/res/input-3.png")));
    lbl4 = new QLabel(UserIDInput);
    lbl4->setObjectName(QString::fromUtf8("lbl4"));
    lbl4->setGeometry(QRect(24, 145, 52, 53));
    lbl4->setPixmap(QPixmap(QString::fromUtf8(":/images/res/input-4.png")));
    lbl5 = new QLabel(UserIDInput);
    lbl5->setObjectName(QString::fromUtf8("lbl5"));
    lbl5->setGeometry(QRect(100, 145, 52, 53));
    lbl5->setPixmap(QPixmap(QString::fromUtf8(":/images/res/input-5.png")));
    lblOK = new QLabel(UserIDInput);
    lblOK->setObjectName(QString::fromUtf8("lblOK"));
    lblOK->setGeometry(QRect(328, 80, 52, 53));
    lblOK->setPixmap(QPixmap(QString::fromUtf8(":/images/res/input-OK.png")));
    lblESC = new QLabel(UserIDInput);
    lblESC->setObjectName(QString::fromUtf8("lblESC"));
    lblESC->setGeometry(QRect(252, 80, 52, 53));
    lblESC->setPixmap(QPixmap(QString::fromUtf8(":/images/res/input-ESC.png")));
    lbl6 = new QLabel(UserIDInput);
    lbl6->setObjectName(QString::fromUtf8("lbl6"));
    lbl6->setGeometry(QRect(176, 145, 52, 53));
    lbl6->setPixmap(QPixmap(QString::fromUtf8(":/images/res/input-6.png")));
    lbl7 = new QLabel(UserIDInput);
    lbl7->setObjectName(QString::fromUtf8("lbl7"));
    lbl7->setGeometry(QRect(24, 210, 52, 53));
    lbl7->setPixmap(QPixmap(QString::fromUtf8(":/images/res/input-7.png")));
    lbl8 = new QLabel(UserIDInput);
    lbl8->setObjectName(QString::fromUtf8("lbl8"));
    lbl8->setGeometry(QRect(100, 210, 52, 53));
    lbl8->setPixmap(QPixmap(QString::fromUtf8(":/images/res/input-8.png")));
    lbl9 = new QLabel(UserIDInput);
    lbl9->setObjectName(QString::fromUtf8("lbl9"));
    lbl9->setGeometry(QRect(176, 210, 52, 53));
    lbl9->setPixmap(QPixmap(QString::fromUtf8(":/images/res/input-9.png")));
    lblPoint = new QLabel(UserIDInput);
    lblPoint->setObjectName(QString::fromUtf8("lblPoint"));
    lblPoint->setGeometry(QRect(252, 145, 52, 53));
    lblPoint->setPixmap(QPixmap(QString::fromUtf8(":/images/res/input-Point.png")));
    lblBack = new QLabel(UserIDInput);
    lblBack->setObjectName(QString::fromUtf8("lblBack"));
    lblBack->setGeometry(QRect(404, 80, 52, 53));
    lblBack->setPixmap(QPixmap(QString::fromUtf8(":/images/res/input-Back.png")));
    txtNUM = new QLineEdit(UserIDInput);
    txtNUM->setObjectName(QString::fromUtf8("txtNUM"));
    txtNUM->setGeometry(QRect(130, 12, 230, 40));
    QFont font3;
    font3.setPointSize(20);
    font3.setBold(false);
    font3.setItalic(false);
    font3.setUnderline(false);
    font3.setStrikeOut(false);
    txtNUM->setFont(font3);
    txtNUM->setMaxLength(99999999);
    txtNUM->setEchoMode(QLineEdit::Normal);
    lblPoint1 = new QLabel(UserIDInput);
    lblPoint1->setObjectName(QString::fromUtf8("lblPoint1"));
    lblPoint1->setGeometry(QRect(328, 145, 52, 53));
    lblPoint1->setPixmap(QPixmap(QString::fromUtf8(":/images/res/input-Point1.png")));
    lblPoint2 = new QLabel(UserIDInput);
    lblPoint2->setObjectName(QString::fromUtf8("lblPoint2"));
    lblPoint2->setGeometry(QRect(404, 145, 52, 53));
    lblPoint2->setPixmap(QPixmap(QString::fromUtf8(":/images/res/input-Point2.png")));
    lblBackSpace = new QLabel(UserIDInput);
    lblBackSpace->setObjectName(QString::fromUtf8("lblBackSpace"));
    lblBackSpace->setGeometry(QRect(328, 210, 128, 53));
    lblBackSpace->setPixmap(QPixmap(QString::fromUtf8(":/images/res/input-BackSpace.png")));
    lblBackSpace->setScaledContents(true);
    QWidget::setTabOrder(txtID, txtPWD);
    QWidget::setTabOrder(txtPWD, btnOK);
    QWidget::setTabOrder(btnOK, btnESC);
    retranslateUi(UserIDInput);

    QMetaObject::connectSlotsByName(UserIDInput);
    } // setupUi

    void retranslateUi(QDialog *UserIDInput)
    {
    UserIDInput->setWindowTitle(QApplication::translate("UserIDInput", "Dialog", 0, QApplication::UnicodeUTF8));
    lblBackground->setText(QApplication::translate("UserIDInput", "", 0, QApplication::UnicodeUTF8));
    lblIcon->setText(QApplication::translate("UserIDInput", "", 0, QApplication::UnicodeUTF8));
    lblID->setText(QApplication::translate("UserIDInput", "User ID", 0, QApplication::UnicodeUTF8));
    lblStatus->setText(QApplication::translate("UserIDInput", "Status", 0, QApplication::UnicodeUTF8));
    btnOK->setText(QApplication::translate("UserIDInput", "OK", 0, QApplication::UnicodeUTF8));
    btnESC->setText(QApplication::translate("UserIDInput", "ESC", 0, QApplication::UnicodeUTF8));
    lblIconPWD->setText(QApplication::translate("UserIDInput", "", 0, QApplication::UnicodeUTF8));
    lblPWD->setText(QApplication::translate("UserIDInput", "User PWD", 0, QApplication::UnicodeUTF8));
    lbl0->setText(QApplication::translate("UserIDInput", "", 0, QApplication::UnicodeUTF8));
    lbl1->setText(QApplication::translate("UserIDInput", "", 0, QApplication::UnicodeUTF8));
    lbl2->setText(QApplication::translate("UserIDInput", "", 0, QApplication::UnicodeUTF8));
    lbl3->setText(QApplication::translate("UserIDInput", "", 0, QApplication::UnicodeUTF8));
    lbl4->setText(QApplication::translate("UserIDInput", "", 0, QApplication::UnicodeUTF8));
    lbl5->setText(QApplication::translate("UserIDInput", "", 0, QApplication::UnicodeUTF8));
    lblOK->setText(QApplication::translate("UserIDInput", "", 0, QApplication::UnicodeUTF8));
    lblESC->setText(QApplication::translate("UserIDInput", "", 0, QApplication::UnicodeUTF8));
    lbl6->setText(QApplication::translate("UserIDInput", "", 0, QApplication::UnicodeUTF8));
    lbl7->setText(QApplication::translate("UserIDInput", "", 0, QApplication::UnicodeUTF8));
    lbl8->setText(QApplication::translate("UserIDInput", "", 0, QApplication::UnicodeUTF8));
    lbl9->setText(QApplication::translate("UserIDInput", "", 0, QApplication::UnicodeUTF8));
    lblPoint->setText(QApplication::translate("UserIDInput", "", 0, QApplication::UnicodeUTF8));
    lblBack->setText(QApplication::translate("UserIDInput", "", 0, QApplication::UnicodeUTF8));
    lblPoint1->setText(QApplication::translate("UserIDInput", "", 0, QApplication::UnicodeUTF8));
    lblPoint2->setText(QApplication::translate("UserIDInput", "", 0, QApplication::UnicodeUTF8));
    lblBackSpace->setText(QApplication::translate("UserIDInput", "", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(UserIDInput);
    } // retranslateUi

};

namespace Ui {
    class UserIDInput: public Ui_UserIDInput {};
} // namespace Ui

#endif // UI_INPUT_2D_USERID_H
