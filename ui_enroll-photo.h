#ifndef UI_ENROLL_2D_PHOTO_H
#define UI_ENROLL_2D_PHOTO_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>

class Ui_EnrollPhoto
{
public:
    QLabel *lblBackground;
    QLabel *lblBackgroundFrame;
    QLabel *lblTitleBackground;
    QLabel *label;
    QLabel *lblTitleText;
    QLabel *lblTitleIcon;
    QLabel *lblStatusIcon;
    QLabel *lblStatusText;
    QLabel *lblEnrollStatus;
    QPushButton *btnESC;
    QPushButton *btnOK;
    QLabel *lblCameraArea;

    void setupUi(QDialog *EnrollPhoto)
    {
    EnrollPhoto->setObjectName(QString::fromUtf8("EnrollPhoto"));
    EnrollPhoto->resize(QSize(320, 240).expandedTo(EnrollPhoto->minimumSizeHint()));
    lblBackground = new QLabel(EnrollPhoto);
    lblBackground->setObjectName(QString::fromUtf8("lblBackground"));
    lblBackground->setGeometry(QRect(0, 0, 320, 240));
    lblBackground->setPixmap(QPixmap(QString::fromUtf8(":/images/res/bg-main.png")));
    lblBackgroundFrame = new QLabel(EnrollPhoto);
    lblBackgroundFrame->setObjectName(QString::fromUtf8("lblBackgroundFrame"));
    lblBackgroundFrame->setGeometry(QRect(12, 10, 297, 217));
    lblBackgroundFrame->setPixmap(QPixmap(QString::fromUtf8(":/images/res/bg-mask2.png")));
    lblBackgroundFrame->setScaledContents(true);
    lblTitleBackground = new QLabel(EnrollPhoto);
    lblTitleBackground->setObjectName(QString::fromUtf8("lblTitleBackground"));
    lblTitleBackground->setGeometry(QRect(0, 4, 320, 30));
    lblTitleBackground->setPixmap(QPixmap(QString::fromUtf8(":/images/res/title-1.png")));
    label = new QLabel(EnrollPhoto);
    label->setObjectName(QString::fromUtf8("label"));
    label->setGeometry(QRect(0, 176, 320, 63));
    label->setPixmap(QPixmap(QString::fromUtf8(":/images/res/bottom.png")));
    lblTitleText = new QLabel(EnrollPhoto);
    lblTitleText->setObjectName(QString::fromUtf8("lblTitleText"));
    lblTitleText->setGeometry(QRect(40, 10, 273, 28));
    lblTitleIcon = new QLabel(EnrollPhoto);
    lblTitleIcon->setObjectName(QString::fromUtf8("lblTitleIcon"));
    lblTitleIcon->setGeometry(QRect(9, 10, 26, 26));
    lblTitleIcon->setPixmap(QPixmap(QString::fromUtf8(":/images/res/icon-camera.png")));
    lblTitleIcon->setScaledContents(true);
    lblStatusIcon = new QLabel(EnrollPhoto);
    lblStatusIcon->setObjectName(QString::fromUtf8("lblStatusIcon"));
    lblStatusIcon->setGeometry(QRect(20, 205, 16, 16));
    lblStatusIcon->setPixmap(QPixmap(QString::fromUtf8(":/images/res/icon-help.png")));
    lblStatusText = new QLabel(EnrollPhoto);
    lblStatusText->setObjectName(QString::fromUtf8("lblStatusText"));
    lblStatusText->setGeometry(QRect(40, 200, 270, 25));
    lblEnrollStatus = new QLabel(EnrollPhoto);
    lblEnrollStatus->setObjectName(QString::fromUtf8("lblEnrollStatus"));
    lblEnrollStatus->setGeometry(QRect(30, 40, 260, 21));
    lblEnrollStatus->setFocusPolicy(Qt::StrongFocus);
    btnESC = new QPushButton(EnrollPhoto);
    btnESC->setObjectName(QString::fromUtf8("btnESC"));
    btnESC->setGeometry(QRect(220, 160, 75, 24));
    btnOK = new QPushButton(EnrollPhoto);
    btnOK->setObjectName(QString::fromUtf8("btnOK"));
    btnOK->setGeometry(QRect(220, 120, 75, 24));
    lblCameraArea = new QLabel(EnrollPhoto);
    lblCameraArea->setObjectName(QString::fromUtf8("lblCameraArea"));
    lblCameraArea->setGeometry(QRect(60, 60, 141, 141));
    lblCameraArea->setFrameShape(QFrame::NoFrame);
    lblCameraArea->setPixmap(QPixmap(QString::fromUtf8(":/images/res/default-character.png")));
    lblCameraArea->setScaledContents(true);
    QWidget::setTabOrder(lblEnrollStatus, btnOK);
    QWidget::setTabOrder(btnOK, btnESC);
    retranslateUi(EnrollPhoto);

    QMetaObject::connectSlotsByName(EnrollPhoto);
    } // setupUi

    void retranslateUi(QDialog *EnrollPhoto)
    {
    EnrollPhoto->setWindowTitle(QApplication::translate("EnrollPhoto", "Dialog", 0, QApplication::UnicodeUTF8));
    lblBackground->setText(QApplication::translate("EnrollPhoto", "", 0, QApplication::UnicodeUTF8));
    lblBackgroundFrame->setText(QApplication::translate("EnrollPhoto", "", 0, QApplication::UnicodeUTF8));
    lblTitleBackground->setText(QApplication::translate("EnrollPhoto", "", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("EnrollPhoto", "", 0, QApplication::UnicodeUTF8));
    lblTitleText->setText(QApplication::translate("EnrollPhoto", "Title", 0, QApplication::UnicodeUTF8));
    lblTitleIcon->setText(QApplication::translate("EnrollPhoto", "", 0, QApplication::UnicodeUTF8));
    lblStatusIcon->setText(QApplication::translate("EnrollPhoto", "", 0, QApplication::UnicodeUTF8));
    lblStatusText->setText(QApplication::translate("EnrollPhoto", "OK: Select  ESC: Return \342\226\262Retry  \342\226\272 Capture", 0, QApplication::UnicodeUTF8));
    lblEnrollStatus->setText(QApplication::translate("EnrollPhoto", "Please prepare...", 0, QApplication::UnicodeUTF8));
    btnESC->setText(QApplication::translate("EnrollPhoto", "ESC", 0, QApplication::UnicodeUTF8));
    btnOK->setText(QApplication::translate("EnrollPhoto", "OK", 0, QApplication::UnicodeUTF8));
    lblCameraArea->setText(QApplication::translate("EnrollPhoto", "", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(EnrollPhoto);
    } // retranslateUi

};

namespace Ui {
    class EnrollPhoto: public Ui_EnrollPhoto {};
} // namespace Ui

#endif // UI_ENROLL_2D_PHOTO_H
