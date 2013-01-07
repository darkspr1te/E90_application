#ifndef UI_T9_2D_INPUT_H
#define UI_T9_2D_INPUT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>

class Ui_T9InputDlg
{
public:
    QLabel *lblStatusbar;
    QLabel *label;
    QLabel *lblStatusText;
    QLabel *lblIcon;
    QLabel *lblBackground;
    QLabel *lblInputText;
    QLabel *lbl0;
    QLabel *lbl1;
    QLabel *lbl2;
    QLabel *lbl3;
    QLabel *lbl4;
    QLabel *lbl5;
    QLabel *lbl6;
    QLabel *lbl7;
    QLabel *lbl8;
    QLabel *lbl9;
    QLabel *lbl10;
    QLabel *lbl11;
    QLabel *lbl12;
    QLabel *lbl13;
    QLabel *lbl14;
    QLabel *lbl15;
    QLabel *lbl16;
    QLabel *lbl17;
    QLabel *lbl18;
    QLabel *lbl19;
    QLabel *lbl20;
    QLabel *lbl21;
    QLabel *lbl22;
    QLabel *lbl23;
    QLabel *lbl24;
    QLabel *lbl25;
    QLabel *lbl26;
    QLabel *lbl27;
    QLabel *lbl28;
    QLabel *lbl29;
    QLabel *lbl30;
    QLineEdit *txtName;
    QLabel *lblUp;
    QLabel *lblDown;

    void setupUi(QDialog *T9InputDlg)
    {
    T9InputDlg->setObjectName(QString::fromUtf8("T9InputDlg"));
    T9InputDlg->resize(QSize(480, 272).expandedTo(T9InputDlg->minimumSizeHint()));
    QFont font;
    font.setFamily(QString::fromUtf8("Tahoma"));
    font.setBold(false);
    font.setItalic(false);
    font.setUnderline(false);
    font.setStrikeOut(false);
    T9InputDlg->setFont(font);
    lblStatusbar = new QLabel(T9InputDlg);
    lblStatusbar->setObjectName(QString::fromUtf8("lblStatusbar"));
    lblStatusbar->setGeometry(QRect(-1, 229, 320, 40));
    label = new QLabel(T9InputDlg);
    label->setObjectName(QString::fromUtf8("label"));
    label->setGeometry(QRect(10, 220, 320, 40));
    label->setPixmap(QPixmap(QString::fromUtf8(":/images/res/bottom.png")));
    label->setScaledContents(true);
    lblStatusText = new QLabel(T9InputDlg);
    lblStatusText->setObjectName(QString::fromUtf8("lblStatusText"));
    lblStatusText->setGeometry(QRect(38, 220, 261, 41));
    lblIcon = new QLabel(T9InputDlg);
    lblIcon->setObjectName(QString::fromUtf8("lblIcon"));
    lblIcon->setEnabled(true);
    lblIcon->setGeometry(QRect(10, 230, 24, 24));
    lblIcon->setPixmap(QPixmap(QString::fromUtf8(":/images/res/t9-input.png")));
    lblBackground = new QLabel(T9InputDlg);
    lblBackground->setObjectName(QString::fromUtf8("lblBackground"));
    lblBackground->setGeometry(QRect(0, 0, 480, 272));
    lblBackground->setPixmap(QPixmap(QString::fromUtf8(":/images/res/bg-inputbox.png")));
    lblBackground->setScaledContents(true);
    lblInputText = new QLabel(T9InputDlg);
    lblInputText->setObjectName(QString::fromUtf8("lblInputText"));
    lblInputText->setGeometry(QRect(40, 40, 381, 30));
    lbl0 = new QLabel(T9InputDlg);
    lbl0->setObjectName(QString::fromUtf8("lbl0"));
    lbl0->setGeometry(QRect(15, 87, 36, 37));
    lbl0->setPixmap(QPixmap(QString::fromUtf8(":/images/res/inputABC-0.png")));
    lbl1 = new QLabel(T9InputDlg);
    lbl1->setObjectName(QString::fromUtf8("lbl1"));
    lbl1->setGeometry(QRect(61, 87, 36, 37));
    lbl1->setPixmap(QPixmap(QString::fromUtf8(":/images/res/inputABC-1.png")));
    lbl2 = new QLabel(T9InputDlg);
    lbl2->setObjectName(QString::fromUtf8("lbl2"));
    lbl2->setGeometry(QRect(107, 87, 36, 37));
    lbl2->setPixmap(QPixmap(QString::fromUtf8(":/images/res/inputABC-2.png")));
    lbl3 = new QLabel(T9InputDlg);
    lbl3->setObjectName(QString::fromUtf8("lbl3"));
    lbl3->setGeometry(QRect(153, 87, 36, 37));
    lbl3->setPixmap(QPixmap(QString::fromUtf8(":/images/res/inputABC-3.png")));
    lbl4 = new QLabel(T9InputDlg);
    lbl4->setObjectName(QString::fromUtf8("lbl4"));
    lbl4->setGeometry(QRect(199, 87, 36, 37));
    lbl4->setPixmap(QPixmap(QString::fromUtf8(":/images/res/inputABC-4.png")));
    lbl5 = new QLabel(T9InputDlg);
    lbl5->setObjectName(QString::fromUtf8("lbl5"));
    lbl5->setGeometry(QRect(245, 87, 36, 37));
    lbl5->setPixmap(QPixmap(QString::fromUtf8(":/images/res/inputABC-5.png")));
    lbl6 = new QLabel(T9InputDlg);
    lbl6->setObjectName(QString::fromUtf8("lbl6"));
    lbl6->setGeometry(QRect(291, 87, 36, 37));
    lbl6->setPixmap(QPixmap(QString::fromUtf8(":/images/res/inputABC-6.png")));
    lbl7 = new QLabel(T9InputDlg);
    lbl7->setObjectName(QString::fromUtf8("lbl7"));
    lbl7->setGeometry(QRect(337, 87, 36, 37));
    lbl7->setPixmap(QPixmap(QString::fromUtf8(":/images/res/inputABC-7.png")));
    lbl8 = new QLabel(T9InputDlg);
    lbl8->setObjectName(QString::fromUtf8("lbl8"));
    lbl8->setGeometry(QRect(383, 87, 36, 37));
    lbl8->setPixmap(QPixmap(QString::fromUtf8(":/images/res/inputABC-8.png")));
    lbl9 = new QLabel(T9InputDlg);
    lbl9->setObjectName(QString::fromUtf8("lbl9"));
    lbl9->setGeometry(QRect(429, 87, 36, 37));
    lbl9->setPixmap(QPixmap(QString::fromUtf8(":/images/res/inputABC-9.png")));
    lbl10 = new QLabel(T9InputDlg);
    lbl10->setObjectName(QString::fromUtf8("lbl10"));
    lbl10->setGeometry(QRect(37, 134, 36, 37));
    lbl10->setPixmap(QPixmap(QString::fromUtf8(":/images/res/inputABC-10.png")));
    lbl11 = new QLabel(T9InputDlg);
    lbl11->setObjectName(QString::fromUtf8("lbl11"));
    lbl11->setGeometry(QRect(83, 134, 36, 37));
    lbl11->setPixmap(QPixmap(QString::fromUtf8(":/images/res/inputABC-11.png")));
    lbl12 = new QLabel(T9InputDlg);
    lbl12->setObjectName(QString::fromUtf8("lbl12"));
    lbl12->setGeometry(QRect(129, 134, 36, 37));
    lbl12->setPixmap(QPixmap(QString::fromUtf8(":/images/res/inputABC-12.png")));
    lbl13 = new QLabel(T9InputDlg);
    lbl13->setObjectName(QString::fromUtf8("lbl13"));
    lbl13->setGeometry(QRect(175, 134, 36, 37));
    lbl13->setPixmap(QPixmap(QString::fromUtf8(":/images/res/inputABC-13.png")));
    lbl14 = new QLabel(T9InputDlg);
    lbl14->setObjectName(QString::fromUtf8("lbl14"));
    lbl14->setGeometry(QRect(221, 134, 36, 37));
    lbl14->setPixmap(QPixmap(QString::fromUtf8(":/images/res/inputABC-14.png")));
    lbl15 = new QLabel(T9InputDlg);
    lbl15->setObjectName(QString::fromUtf8("lbl15"));
    lbl15->setGeometry(QRect(267, 134, 36, 37));
    lbl15->setPixmap(QPixmap(QString::fromUtf8(":/images/res/inputABC-15.png")));
    lbl16 = new QLabel(T9InputDlg);
    lbl16->setObjectName(QString::fromUtf8("lbl16"));
    lbl16->setGeometry(QRect(313, 134, 36, 37));
    lbl16->setPixmap(QPixmap(QString::fromUtf8(":/images/res/inputABC-16.png")));
    lbl17 = new QLabel(T9InputDlg);
    lbl17->setObjectName(QString::fromUtf8("lbl17"));
    lbl17->setGeometry(QRect(359, 134, 36, 37));
    lbl17->setPixmap(QPixmap(QString::fromUtf8(":/images/res/inputABC-17.png")));
    lbl18 = new QLabel(T9InputDlg);
    lbl18->setObjectName(QString::fromUtf8("lbl18"));
    lbl18->setGeometry(QRect(405, 134, 36, 37));
    lbl18->setPixmap(QPixmap(QString::fromUtf8(":/images/res/inputABC-18.png")));
    lbl19 = new QLabel(T9InputDlg);
    lbl19->setObjectName(QString::fromUtf8("lbl19"));
    lbl19->setGeometry(QRect(84, 181, 36, 37));
    lbl19->setPixmap(QPixmap(QString::fromUtf8(":/images/res/inputABC-19.png")));
    lbl20 = new QLabel(T9InputDlg);
    lbl20->setObjectName(QString::fromUtf8("lbl20"));
    lbl20->setGeometry(QRect(130, 181, 36, 37));
    lbl20->setPixmap(QPixmap(QString::fromUtf8(":/images/res/inputABC-20.png")));
    lbl21 = new QLabel(T9InputDlg);
    lbl21->setObjectName(QString::fromUtf8("lbl21"));
    lbl21->setGeometry(QRect(176, 181, 36, 37));
    lbl21->setPixmap(QPixmap(QString::fromUtf8(":/images/res/inputABC-21.png")));
    lbl22 = new QLabel(T9InputDlg);
    lbl22->setObjectName(QString::fromUtf8("lbl22"));
    lbl22->setGeometry(QRect(222, 181, 36, 37));
    lbl22->setPixmap(QPixmap(QString::fromUtf8(":/images/res/inputABC-22.png")));
    lbl23 = new QLabel(T9InputDlg);
    lbl23->setObjectName(QString::fromUtf8("lbl23"));
    lbl23->setGeometry(QRect(268, 181, 36, 37));
    lbl23->setPixmap(QPixmap(QString::fromUtf8(":/images/res/inputABC-23.png")));
    lbl24 = new QLabel(T9InputDlg);
    lbl24->setObjectName(QString::fromUtf8("lbl24"));
    lbl24->setGeometry(QRect(314, 181, 36, 37));
    lbl24->setPixmap(QPixmap(QString::fromUtf8(":/images/res/inputABC-24.png")));
    lbl25 = new QLabel(T9InputDlg);
    lbl25->setObjectName(QString::fromUtf8("lbl25"));
    lbl25->setGeometry(QRect(360, 181, 36, 37));
    lbl25->setPixmap(QPixmap(QString::fromUtf8(":/images/res/inputABC-25.png")));
    lbl26 = new QLabel(T9InputDlg);
    lbl26->setObjectName(QString::fromUtf8("lbl26"));
    lbl26->setGeometry(QRect(130, 228, 36, 37));
    lbl26->setPixmap(QPixmap(QString::fromUtf8(":/images/res/inputABC-26.png")));
    lbl27 = new QLabel(T9InputDlg);
    lbl27->setObjectName(QString::fromUtf8("lbl27"));
    lbl27->setGeometry(QRect(176, 228, 36, 37));
    lbl27->setPixmap(QPixmap(QString::fromUtf8(":/images/res/inputABC-27.png")));
    lbl28 = new QLabel(T9InputDlg);
    lbl28->setObjectName(QString::fromUtf8("lbl28"));
    lbl28->setGeometry(QRect(222, 228, 36, 37));
    lbl28->setPixmap(QPixmap(QString::fromUtf8(":/images/res/inputABC-28.png")));
    lbl29 = new QLabel(T9InputDlg);
    lbl29->setObjectName(QString::fromUtf8("lbl29"));
    lbl29->setGeometry(QRect(268, 228, 36, 37));
    lbl29->setPixmap(QPixmap(QString::fromUtf8(":/images/res/inputABC-29.png")));
    lbl30 = new QLabel(T9InputDlg);
    lbl30->setObjectName(QString::fromUtf8("lbl30"));
    lbl30->setGeometry(QRect(314, 228, 36, 37));
    lbl30->setPixmap(QPixmap(QString::fromUtf8(":/images/res/inputABC-30.png")));
    txtName = new QLineEdit(T9InputDlg);
    txtName->setObjectName(QString::fromUtf8("txtName"));
    txtName->setGeometry(QRect(90, 10, 290, 30));
    txtName->setMaxLength(8);
    lblUp = new QLabel(T9InputDlg);
    lblUp->setObjectName(QString::fromUtf8("lblUp"));
    lblUp->setGeometry(QRect(380, 50, 29, 29));
    lblUp->setPixmap(QPixmap(QString::fromUtf8(":/images/res/inputABC-up.png")));
    lblDown = new QLabel(T9InputDlg);
    lblDown->setObjectName(QString::fromUtf8("lblDown"));
    lblDown->setGeometry(QRect(430, 50, 29, 29));
    lblDown->setPixmap(QPixmap(QString::fromUtf8(":/images/res/inputABC-down.png")));
    retranslateUi(T9InputDlg);

    QMetaObject::connectSlotsByName(T9InputDlg);
    } // setupUi

    void retranslateUi(QDialog *T9InputDlg)
    {
    T9InputDlg->setWindowTitle(QApplication::translate("T9InputDlg", "Title", 0, QApplication::UnicodeUTF8));
    lblStatusbar->setText(QApplication::translate("T9InputDlg", "", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("T9InputDlg", "", 0, QApplication::UnicodeUTF8));
    lblIcon->setText(QApplication::translate("T9InputDlg", "", 0, QApplication::UnicodeUTF8));
    lblBackground->setText(QApplication::translate("T9InputDlg", "", 0, QApplication::UnicodeUTF8));
    lblInputText->setText(QApplication::translate("T9InputDlg", "", 0, QApplication::UnicodeUTF8));
    lbl0->setText(QApplication::translate("T9InputDlg", "", 0, QApplication::UnicodeUTF8));
    lbl1->setText(QApplication::translate("T9InputDlg", "", 0, QApplication::UnicodeUTF8));
    lbl2->setText(QApplication::translate("T9InputDlg", "", 0, QApplication::UnicodeUTF8));
    lbl3->setText(QApplication::translate("T9InputDlg", "", 0, QApplication::UnicodeUTF8));
    lbl4->setText(QApplication::translate("T9InputDlg", "", 0, QApplication::UnicodeUTF8));
    lbl5->setText(QApplication::translate("T9InputDlg", "", 0, QApplication::UnicodeUTF8));
    lbl6->setText(QApplication::translate("T9InputDlg", "", 0, QApplication::UnicodeUTF8));
    lbl7->setText(QApplication::translate("T9InputDlg", "", 0, QApplication::UnicodeUTF8));
    lbl8->setText(QApplication::translate("T9InputDlg", "", 0, QApplication::UnicodeUTF8));
    lbl9->setText(QApplication::translate("T9InputDlg", "", 0, QApplication::UnicodeUTF8));
    lbl10->setText(QApplication::translate("T9InputDlg", "", 0, QApplication::UnicodeUTF8));
    lbl11->setText(QApplication::translate("T9InputDlg", "", 0, QApplication::UnicodeUTF8));
    lbl12->setText(QApplication::translate("T9InputDlg", "", 0, QApplication::UnicodeUTF8));
    lbl13->setText(QApplication::translate("T9InputDlg", "", 0, QApplication::UnicodeUTF8));
    lbl14->setText(QApplication::translate("T9InputDlg", "", 0, QApplication::UnicodeUTF8));
    lbl15->setText(QApplication::translate("T9InputDlg", "", 0, QApplication::UnicodeUTF8));
    lbl16->setText(QApplication::translate("T9InputDlg", "", 0, QApplication::UnicodeUTF8));
    lbl17->setText(QApplication::translate("T9InputDlg", "", 0, QApplication::UnicodeUTF8));
    lbl18->setText(QApplication::translate("T9InputDlg", "", 0, QApplication::UnicodeUTF8));
    lbl19->setText(QApplication::translate("T9InputDlg", "", 0, QApplication::UnicodeUTF8));
    lbl20->setText(QApplication::translate("T9InputDlg", "", 0, QApplication::UnicodeUTF8));
    lbl21->setText(QApplication::translate("T9InputDlg", "", 0, QApplication::UnicodeUTF8));
    lbl22->setText(QApplication::translate("T9InputDlg", "", 0, QApplication::UnicodeUTF8));
    lbl23->setText(QApplication::translate("T9InputDlg", "", 0, QApplication::UnicodeUTF8));
    lbl24->setText(QApplication::translate("T9InputDlg", "", 0, QApplication::UnicodeUTF8));
    lbl25->setText(QApplication::translate("T9InputDlg", "", 0, QApplication::UnicodeUTF8));
    lbl26->setText(QApplication::translate("T9InputDlg", "", 0, QApplication::UnicodeUTF8));
    lbl27->setText(QApplication::translate("T9InputDlg", "", 0, QApplication::UnicodeUTF8));
    lbl28->setText(QApplication::translate("T9InputDlg", "", 0, QApplication::UnicodeUTF8));
    lbl29->setText(QApplication::translate("T9InputDlg", "", 0, QApplication::UnicodeUTF8));
    lbl30->setText(QApplication::translate("T9InputDlg", "", 0, QApplication::UnicodeUTF8));
    lblUp->setText(QApplication::translate("T9InputDlg", "", 0, QApplication::UnicodeUTF8));
    lblDown->setText(QApplication::translate("T9InputDlg", "", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(T9InputDlg);
    } // retranslateUi

};

namespace Ui {
    class T9InputDlg: public Ui_T9InputDlg {};
} // namespace Ui

#endif // UI_T9_2D_INPUT_H
