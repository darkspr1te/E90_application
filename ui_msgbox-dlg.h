#ifndef UI_MSGBOX_2D_DLG_H
#define UI_MSGBOX_2D_DLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>

class Ui_MsgboxDlg
{
public:
    QLabel *lblBackground;
    QLabel *lblIcon;
    QLabel *lblStatus;
    QPushButton *btnESC;
    QPushButton *btnOK;
    QLabel *lblOK;
    QLabel *lblESC;
    QLabel *lblOKTitle;
    QLabel *lblESCTitle;

    void setupUi(QDialog *MsgboxDlg)
    {
    MsgboxDlg->setObjectName(QString::fromUtf8("MsgboxDlg"));
    MsgboxDlg->setWindowModality(Qt::NonModal);
    MsgboxDlg->resize(QSize(270, 120).expandedTo(MsgboxDlg->minimumSizeHint()));
    QFont font;
    font.setFamily(QString::fromUtf8("Tahoma"));
    font.setBold(false);
    font.setItalic(false);
    font.setUnderline(false);
    font.setStrikeOut(false);
    MsgboxDlg->setFont(font);
    lblBackground = new QLabel(MsgboxDlg);
    lblBackground->setObjectName(QString::fromUtf8("lblBackground"));
    lblBackground->setGeometry(QRect(0, 0, 270, 120));
    lblBackground->setPixmap(QPixmap(QString::fromUtf8(":/images/res/bg-inputbox.png")));
    lblBackground->setScaledContents(true);
    lblIcon = new QLabel(MsgboxDlg);
    lblIcon->setObjectName(QString::fromUtf8("lblIcon"));
    lblIcon->setGeometry(QRect(10, 20, 40, 40));
    lblIcon->setPixmap(QPixmap(QString::fromUtf8(":/images/res/icon-ok.png")));
    lblStatus = new QLabel(MsgboxDlg);
    lblStatus->setObjectName(QString::fromUtf8("lblStatus"));
    lblStatus->setGeometry(QRect(60, 30, 200, 41));
    lblStatus->setTextFormat(Qt::LogText);
    lblStatus->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
    btnESC = new QPushButton(MsgboxDlg);
    btnESC->setObjectName(QString::fromUtf8("btnESC"));
    btnESC->setGeometry(QRect(160, 30, 80, 40));
    btnOK = new QPushButton(MsgboxDlg);
    btnOK->setObjectName(QString::fromUtf8("btnOK"));
    btnOK->setGeometry(QRect(20, 40, 80, 40));
    lblOK = new QLabel(MsgboxDlg);
    lblOK->setObjectName(QString::fromUtf8("lblOK"));
    lblOK->setGeometry(QRect(30, 70, 80, 40));
    lblOK->setPixmap(QPixmap(QString::fromUtf8(":/images/res/bg-button.png")));
    lblESC = new QLabel(MsgboxDlg);
    lblESC->setObjectName(QString::fromUtf8("lblESC"));
    lblESC->setGeometry(QRect(160, 70, 80, 40));
    lblESC->setPixmap(QPixmap(QString::fromUtf8(":/images/res/bg-button1.png")));
    lblOKTitle = new QLabel(MsgboxDlg);
    lblOKTitle->setObjectName(QString::fromUtf8("lblOKTitle"));
    lblOKTitle->setGeometry(QRect(45, 76, 50, 28));
    lblOKTitle->setAlignment(Qt::AlignCenter);
    lblESCTitle = new QLabel(MsgboxDlg);
    lblESCTitle->setObjectName(QString::fromUtf8("lblESCTitle"));
    lblESCTitle->setGeometry(QRect(175, 76, 50, 28));
    lblESCTitle->setAlignment(Qt::AlignCenter);
    QWidget::setTabOrder(btnOK, btnESC);
    retranslateUi(MsgboxDlg);

    QMetaObject::connectSlotsByName(MsgboxDlg);
    } // setupUi

    void retranslateUi(QDialog *MsgboxDlg)
    {
    MsgboxDlg->setWindowTitle(QApplication::translate("MsgboxDlg", "Title", 0, QApplication::UnicodeUTF8));
    lblBackground->setText(QApplication::translate("MsgboxDlg", "", 0, QApplication::UnicodeUTF8));
    lblIcon->setText(QApplication::translate("MsgboxDlg", "", 0, QApplication::UnicodeUTF8));
    lblStatus->setText(QApplication::translate("MsgboxDlg", "Status", 0, QApplication::UnicodeUTF8));
    btnESC->setText(QApplication::translate("MsgboxDlg", "ESC", 0, QApplication::UnicodeUTF8));
    btnOK->setText(QApplication::translate("MsgboxDlg", "OK", 0, QApplication::UnicodeUTF8));
    lblOK->setText(QApplication::translate("MsgboxDlg", "", 0, QApplication::UnicodeUTF8));
    lblESC->setText(QApplication::translate("MsgboxDlg", "", 0, QApplication::UnicodeUTF8));
    lblOKTitle->setText(QApplication::translate("MsgboxDlg", "OK", 0, QApplication::UnicodeUTF8));
    lblESCTitle->setText(QApplication::translate("MsgboxDlg", "ESC", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(MsgboxDlg);
    } // retranslateUi

};

namespace Ui {
    class MsgboxDlg: public Ui_MsgboxDlg {};
} // namespace Ui

#endif // UI_MSGBOX_2D_DLG_H
