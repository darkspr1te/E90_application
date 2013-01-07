#include "../precomp.h"
#include "MessageBox.h"
#include <QtCore/QTimer>
#include <QtGui/QKeyEvent>
#include <QtGui/QPixmap>
#include <QtGui/QPainter>
#include <QtGui/QFont>
#include <QtGui/QPen>
#include <QtGui/QColor>

#define MESSGAEBOX_BACK_X   (480 - 270) / 2   //105
#define MESSGAEBOX_BACK_Y   (272 - 120) / 2   //76

#define MESSAGEBOX_OK_X 	MESSGAEBOX_BACK_X + 30 
#define MESSAGEBOX_OK_Y 	MESSGAEBOX_BACK_Y + 70
#define MESSAGEBOX_OK_W 	80
#define MESSAGEBOX_OK_H 	40

#define MESSAGEBOX_ESC_X 	MESSGAEBOX_BACK_X + 160
#define MESSAGEBOX_ESC_Y 	MESSGAEBOX_BACK_Y + 70
#define MESSAGEBOX_ESC_W 	80
#define MESSAGEBOX_ESC_H 	40

extern unsigned int nTouchX, nTouchY, nTouchPress;      

//////////////////////////////////////////////////////////////////////////
CMessageBox::CMessageBox(QWidget *parent)
	: QDialog(parent)
{
	GUI_DLG_IMPL(FALSE);
	GUI_DLG_CENTER(this);
	GUI_DLG_SET_THEME_1();
	m_bTerminateFlag = FALSE;

    ui.btnOK->hide();
	ui.btnESC->hide();

	connect(ui.btnOK, SIGNAL(clicked()), this, SLOT(OnBtnOK()));
	connect(ui.btnESC, SIGNAL(clicked()), this, SLOT(OnBtnESC()));
}

//////////////////////////////////////////////////////////////////////////
void CMessageBox::SetIcon(QString szIconFile)
{
	QPixmap pmap(szIconFile);
	ui.lblIcon->setPixmap(pmap);
}

//////////////////////////////////////////////////////////////////////////
void CMessageBox::SetText(QString szText)
{
	int i;
	int w = ui.lblStatus->width();
	QFontMetrics fm = ui.lblStatus->fontMetrics();

	for (i=0; i<szText.length(); i++)
	{
		if (fm.width(szText, i + 1) > w)
			break;
	}

	QString szMessage = szText;
	if (i < szText.length())
		szMessage.insert(i, "\r\n");

	ui.lblStatus->setText(szMessage);
}

//////////////////////////////////////////////////////////////////////////
void CMessageBox::SetType(int nType)
{
	int w = width();
	QPoint pos = ui.lblOK->pos();
	QPoint pos1 = ui.lblOKTitle->pos();
	int w_lblOK = ui.lblOK->width();
	int w_lblOKTitle = ui.lblOKTitle->width();

	switch (nType)
	{
	case UI_MSG_OK:
	case UI_MSG_ERROR:
		ui.lblESC->hide();
        ui.lblESCTitle->hide();
		ui.lblOK->move(w / 2 - w_lblOK / 2, pos.y());   
		ui.lblOKTitle->move(w / 2 - w_lblOKTitle / 2, pos1.y());   
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
int CMessageBox::MsgBoxProc(unsigned int nTimeout /* = 0xFFFFFFFF */)
{
	int nKey;
    int x_btnOK = MESSGAEBOX_BACK_X + ui.lblOK->x(), y_btnOK = MESSGAEBOX_BACK_Y + ui.lblOK->y();
    int x_btnESC = MESSGAEBOX_BACK_X + ui.lblESC->x(), y_btnESC = MESSGAEBOX_BACK_Y + ui.lblESC->y();
	int w_btnOK = ui.lblOK->width(), h_btnOK = ui.lblOK->height();
    int w_btnESC = ui.lblESC->width(), h_btnESC = ui.lblESC->height();

	m_nRet = UI_MSGRET_ESC;

	if (LCD_BLANK_STATUS() == FBINFO_BLANK_PAUSE)
		LCD_BLANK(FBINFO_BLANK_RESUME);

	while (!m_bTerminateFlag && uiTimeIsTimeout(nTimeout) == FALSE)
	{
		POST_EVENTS();

		nKey = uiKeyGetKey(TRUE);

		if ((nTouchX >= x_btnOK) && (nTouchX <= (x_btnOK+w_btnOK)) && (nTouchY >= y_btnOK) && (nTouchY <= (y_btnOK+h_btnOK)))  
		    OnBtnOK();
		if ((nTouchX >= x_btnESC) && (nTouchX <= (x_btnESC+w_btnESC)) && (nTouchY >= y_btnESC) && (nTouchY <= (y_btnESC+h_btnESC)))  
		    OnBtnESC();
	}
	
//_lExit:
	return m_nRet;
}

//////////////////////////////////////////////////////////////////////////
void CMessageBox::OnBtnOK()
{
	m_nRet = UI_MSGRET_OK;
	m_bTerminateFlag = TRUE;
}

//////////////////////////////////////////////////////////////////////////
void CMessageBox::OnBtnESC()
{
	m_nRet = UI_MSGRET_ESC;
	m_bTerminateFlag = TRUE;
}
