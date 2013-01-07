#ifndef UI_PROGRESS_2D_DLG_H
#define UI_PROGRESS_2D_DLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QLabel>
#include <QtGui/QProgressBar>

class Ui_ProgressDlg
{
public:
    QLabel *lblBackground;
    QLabel *lblMessage;
    QProgressBar *progressBar;

    void setupUi(QDialog *ProgressDlg)
    {
    ProgressDlg->setObjectName(QString::fromUtf8("ProgressDlg"));
    ProgressDlg->setWindowModality(Qt::NonModal);
    ProgressDlg->resize(QSize(270, 90).expandedTo(ProgressDlg->minimumSizeHint()));
    QFont font;
    font.setFamily(QString::fromUtf8("Tahoma"));
    font.setBold(false);
    font.setItalic(false);
    font.setUnderline(false);
    font.setStrikeOut(false);
    ProgressDlg->setFont(font);
    lblBackground = new QLabel(ProgressDlg);
    lblBackground->setObjectName(QString::fromUtf8("lblBackground"));
    lblBackground->setGeometry(QRect(0, 0, 270, 90));
    lblBackground->setPixmap(QPixmap(QString::fromUtf8(":/images/res/bg-inputbox.png")));
    lblBackground->setScaledContents(true);
    lblMessage = new QLabel(ProgressDlg);
    lblMessage->setObjectName(QString::fromUtf8("lblMessage"));
    lblMessage->setGeometry(QRect(18, 10, 241, 32));
    lblMessage->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
    progressBar = new QProgressBar(ProgressDlg);
    progressBar->setObjectName(QString::fromUtf8("progressBar"));
    progressBar->setGeometry(QRect(17, 50, 240, 21));
    progressBar->setValue(24);
    progressBar->setTextVisible(false);
    retranslateUi(ProgressDlg);

    QMetaObject::connectSlotsByName(ProgressDlg);
    } // setupUi

    void retranslateUi(QDialog *ProgressDlg)
    {
    ProgressDlg->setWindowTitle(QApplication::translate("ProgressDlg", "Title", 0, QApplication::UnicodeUTF8));
    lblBackground->setText(QApplication::translate("ProgressDlg", "", 0, QApplication::UnicodeUTF8));
    lblMessage->setText(QApplication::translate("ProgressDlg", "", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(ProgressDlg);
    } // retranslateUi

};

namespace Ui {
    class ProgressDlg: public Ui_ProgressDlg {};
} // namespace Ui

#endif // UI_PROGRESS_2D_DLG_H
