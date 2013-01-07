#ifndef UI_BELL_2D_DLG_H
#define UI_BELL_2D_DLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>

class Ui_BellDlg
{
public:
    QLabel *lblBackground;
    QPushButton *btnESC;
    QLabel *lblBellTime;
    QLabel *lblBellLength;
    QLineEdit *txtBellTime;
    QLineEdit *txtBellLength;
    QLabel *label;
    QLabel *lblESC;
    QLabel *lblESCTitle;

    void setupUi(QDialog *BellDlg)
    {
    BellDlg->setObjectName(QString::fromUtf8("BellDlg"));
    BellDlg->resize(QSize(270, 120).expandedTo(BellDlg->minimumSizeHint()));
    lblBackground = new QLabel(BellDlg);
    lblBackground->setObjectName(QString::fromUtf8("lblBackground"));
    lblBackground->setGeometry(QRect(0, 0, 270, 120));
    lblBackground->setPixmap(QPixmap(QString::fromUtf8(":/images/res/bg-inputbox.png")));
    lblBackground->setScaledContents(true);
    btnESC = new QPushButton(BellDlg);
    btnESC->setObjectName(QString::fromUtf8("btnESC"));
    btnESC->setGeometry(QRect(180, 47, 75, 24));
    lblBellTime = new QLabel(BellDlg);
    lblBellTime->setObjectName(QString::fromUtf8("lblBellTime"));
    lblBellTime->setGeometry(QRect(14, 30, 70, 14));
    lblBellLength = new QLabel(BellDlg);
    lblBellLength->setObjectName(QString::fromUtf8("lblBellLength"));
    lblBellLength->setGeometry(QRect(14, 53, 70, 16));
    txtBellTime = new QLineEdit(BellDlg);
    txtBellTime->setObjectName(QString::fromUtf8("txtBellTime"));
    txtBellTime->setGeometry(QRect(84, 24, 91, 20));
    txtBellTime->setFocusPolicy(Qt::NoFocus);
    txtBellTime->setReadOnly(true);
    txtBellLength = new QLineEdit(BellDlg);
    txtBellLength->setObjectName(QString::fromUtf8("txtBellLength"));
    txtBellLength->setGeometry(QRect(84, 50, 91, 20));
    txtBellLength->setFocusPolicy(Qt::NoFocus);
    txtBellLength->setMaxLength(3);
    txtBellLength->setReadOnly(true);
    label = new QLabel(BellDlg);
    label->setObjectName(QString::fromUtf8("label"));
    label->setGeometry(QRect(21, 80, 231, 20));
    label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
    lblESC = new QLabel(BellDlg);
    lblESC->setObjectName(QString::fromUtf8("lblESC"));
    lblESC->setGeometry(QRect(180, 70, 80, 40));
    lblESC->setPixmap(QPixmap(QString::fromUtf8(":/images/res/bg-button1.png")));
    lblESCTitle = new QLabel(BellDlg);
    lblESCTitle->setObjectName(QString::fromUtf8("lblESCTitle"));
    lblESCTitle->setGeometry(QRect(195, 76, 50, 28));
    lblESCTitle->setAlignment(Qt::AlignCenter);
    QWidget::setTabOrder(txtBellTime, txtBellLength);
    QWidget::setTabOrder(txtBellLength, btnESC);
    retranslateUi(BellDlg);

    QMetaObject::connectSlotsByName(BellDlg);
    } // setupUi

    void retranslateUi(QDialog *BellDlg)
    {
    BellDlg->setWindowTitle(QApplication::translate("BellDlg", "Dialog", 0, QApplication::UnicodeUTF8));
    lblBackground->setText(QApplication::translate("BellDlg", "", 0, QApplication::UnicodeUTF8));
    btnESC->setText(QApplication::translate("BellDlg", "Stop", 0, QApplication::UnicodeUTF8));
    lblBellTime->setText(QApplication::translate("BellDlg", "BellTime", 0, QApplication::UnicodeUTF8));
    lblBellLength->setText(QApplication::translate("BellDlg", "Length(s)", 0, QApplication::UnicodeUTF8));
    txtBellTime->setInputMask(QApplication::translate("BellDlg", "", 0, QApplication::UnicodeUTF8));
    txtBellLength->setText(QApplication::translate("BellDlg", "0", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("BellDlg", "Press OK or ESC key for stop", 0, QApplication::UnicodeUTF8));
    lblESC->setText(QApplication::translate("BellDlg", "", 0, QApplication::UnicodeUTF8));
    lblESCTitle->setText(QApplication::translate("BellDlg", "ESC", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(BellDlg);
    } // retranslateUi

};

namespace Ui {
    class BellDlg: public Ui_BellDlg {};
} // namespace Ui

#endif // UI_BELL_2D_DLG_H
