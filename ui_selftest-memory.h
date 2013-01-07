#ifndef UI_SELFTEST_2D_MEMORY_H
#define UI_SELFTEST_2D_MEMORY_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QLabel>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>

class Ui_SelftestMemory
{
public:
    QLabel *lblBackground;
    QPushButton *btnESC;
    QProgressBar *progressBar;
    QLabel *lblStatus;

    void setupUi(QDialog *SelftestMemory)
    {
    SelftestMemory->setObjectName(QString::fromUtf8("SelftestMemory"));
    SelftestMemory->resize(QSize(270, 120).expandedTo(SelftestMemory->minimumSizeHint()));
    lblBackground = new QLabel(SelftestMemory);
    lblBackground->setObjectName(QString::fromUtf8("lblBackground"));
    lblBackground->setGeometry(QRect(0, 0, 270, 120));
    lblBackground->setPixmap(QPixmap(QString::fromUtf8(":/images/res/bg-inputbox.png")));
    lblBackground->setScaledContents(true);
    btnESC = new QPushButton(SelftestMemory);
    btnESC->setObjectName(QString::fromUtf8("btnESC"));
    btnESC->setGeometry(QRect(95, 75, 80, 34));
    progressBar = new QProgressBar(SelftestMemory);
    progressBar->setObjectName(QString::fromUtf8("progressBar"));
    progressBar->setGeometry(QRect(21, 40, 234, 16));
    progressBar->setValue(0);
    progressBar->setTextVisible(false);
    lblStatus = new QLabel(SelftestMemory);
    lblStatus->setObjectName(QString::fromUtf8("lblStatus"));
    lblStatus->setGeometry(QRect(20, 10, 220, 21));
    retranslateUi(SelftestMemory);

    QMetaObject::connectSlotsByName(SelftestMemory);
    } // setupUi

    void retranslateUi(QDialog *SelftestMemory)
    {
    SelftestMemory->setWindowTitle(QApplication::translate("SelftestMemory", "Dialog", 0, QApplication::UnicodeUTF8));
    lblBackground->setText(QApplication::translate("SelftestMemory", "", 0, QApplication::UnicodeUTF8));
    btnESC->setText(QApplication::translate("SelftestMemory", "ESC", 0, QApplication::UnicodeUTF8));
    lblStatus->setText(QApplication::translate("SelftestMemory", "Memory testing...", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(SelftestMemory);
    } // retranslateUi

};

namespace Ui {
    class SelftestMemory: public Ui_SelftestMemory {};
} // namespace Ui

#endif // UI_SELFTEST_2D_MEMORY_H
