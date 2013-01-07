#ifndef UI_SELFTEST_2D_SOUND_H
#define UI_SELFTEST_2D_SOUND_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>

class Ui_SelftestSound
{
public:
    QLabel *lblBackground;
    QPushButton *btnPlay;
    QPushButton *btnESC;
    QComboBox *comboBox;
    QLabel *lblStatusbar;
    QLabel *label;
    QLabel *lblStatusIcon;
    QLabel *lblStatusText;

    void setupUi(QDialog *SelftestSound)
    {
    SelftestSound->setObjectName(QString::fromUtf8("SelftestSound"));
    SelftestSound->resize(QSize(320, 240).expandedTo(SelftestSound->minimumSizeHint()));
    lblBackground = new QLabel(SelftestSound);
    lblBackground->setObjectName(QString::fromUtf8("lblBackground"));
    lblBackground->setGeometry(QRect(20, 50, 270, 120));
    lblBackground->setPixmap(QPixmap(QString::fromUtf8(":/images/res/bg-inputbox.png")));
    lblBackground->setScaledContents(true);
    btnPlay = new QPushButton(SelftestSound);
    btnPlay->setObjectName(QString::fromUtf8("btnPlay"));
    btnPlay->setGeometry(QRect(50, 120, 80, 34));
    btnPlay->setFocusPolicy(Qt::NoFocus);
    btnESC = new QPushButton(SelftestSound);
    btnESC->setObjectName(QString::fromUtf8("btnESC"));
    btnESC->setGeometry(QRect(190, 120, 80, 34));
    btnESC->setFocusPolicy(Qt::NoFocus);
    comboBox = new QComboBox(SelftestSound);
    comboBox->setObjectName(QString::fromUtf8("comboBox"));
    comboBox->setGeometry(QRect(70, 70, 180, 22));
    lblStatusbar = new QLabel(SelftestSound);
    lblStatusbar->setObjectName(QString::fromUtf8("lblStatusbar"));
    lblStatusbar->setGeometry(QRect(0, 200, 320, 40));
    label = new QLabel(SelftestSound);
    label->setObjectName(QString::fromUtf8("label"));
    label->setGeometry(QRect(0, 200, 320, 40));
    label->setPixmap(QPixmap(QString::fromUtf8(":/images/res/bottom.png")));
    label->setScaledContents(true);
    lblStatusIcon = new QLabel(SelftestSound);
    lblStatusIcon->setObjectName(QString::fromUtf8("lblStatusIcon"));
    lblStatusIcon->setGeometry(QRect(20, 205, 16, 16));
    lblStatusIcon->setPixmap(QPixmap(QString::fromUtf8(":/images/res/icon-help.png")));
    lblStatusText = new QLabel(SelftestSound);
    lblStatusText->setObjectName(QString::fromUtf8("lblStatusText"));
    lblStatusText->setGeometry(QRect(40, 200, 270, 25));
    QWidget::setTabOrder(btnPlay, btnESC);
    retranslateUi(SelftestSound);

    QMetaObject::connectSlotsByName(SelftestSound);
    } // setupUi

    void retranslateUi(QDialog *SelftestSound)
    {
    SelftestSound->setWindowTitle(QApplication::translate("SelftestSound", "Dialog", 0, QApplication::UnicodeUTF8));
    lblBackground->setText(QApplication::translate("SelftestSound", "", 0, QApplication::UnicodeUTF8));
    btnPlay->setText(QApplication::translate("SelftestSound", "Play", 0, QApplication::UnicodeUTF8));
    btnESC->setText(QApplication::translate("SelftestSound", "ESC", 0, QApplication::UnicodeUTF8));
    comboBox->clear();
    comboBox->addItem(QApplication::translate("SelftestSound", "Channel 1", 0, QApplication::UnicodeUTF8));
    comboBox->addItem(QApplication::translate("SelftestSound", "Channel 2", 0, QApplication::UnicodeUTF8));
    comboBox->addItem(QApplication::translate("SelftestSound", "Channel 3", 0, QApplication::UnicodeUTF8));
    comboBox->addItem(QApplication::translate("SelftestSound", "Channel 4", 0, QApplication::UnicodeUTF8));
    lblStatusbar->setText(QApplication::translate("SelftestSound", "", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("SelftestSound", "", 0, QApplication::UnicodeUTF8));
    lblStatusIcon->setText(QApplication::translate("SelftestSound", "", 0, QApplication::UnicodeUTF8));
    lblStatusText->setText(QApplication::translate("SelftestSound", "OK: Play  ESC: Return", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(SelftestSound);
    } // retranslateUi

};

namespace Ui {
    class SelftestSound: public Ui_SelftestSound {};
} // namespace Ui

#endif // UI_SELFTEST_2D_SOUND_H
