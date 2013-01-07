#include "../precomp.h"

#include <QtGui/QApplication>
#include <QtGui/QWidget>
#include <QtGui/QLineEdit>
#include <QtGui/QLabel>
#include <QtGui/QKeyEvent>

#include "t9_main.h"
#include "../gui/SBLabel.h"

//////////////////////////////////////////////////////////////////////////
SBLabel* g_T9Window = NULL;
SBLabel* g_T9Staute =NULL;
int g_nEditStatus;

#define INPUT_ABC_COUNT     31
#define INPUT_ABC_SIZE_X    36
#define INPUT_ABC_SIZE_Y    37
#define INPUT_ABC_START_Y   87 
#define INPUT_ABC_SPACE_X   10
#define INPUT_ABC_SPACE_Y   10

#define INPUT_ABC1_START_X   15
#define INPUT_ABC2_START_X   37
#define INPUT_ABC3_START_X   84
#define INPUT_ABC4_START_X   130

#define INPUT_ABC1_COLS     10  //10
#define INPUT_ABC2_COLS     19  //9
#define INPUT_ABC3_COLS     26  //7

#define INPUT_PY_COUNT      9
#define INPUT_PY_START_X    40
#define INPUT_PY_START_Y    55  //51
#define INPUT_PY_WIDTH		400
#define INPUT_PY_HEIGHT		30
#define INPUT_PY_SPACE_X    30  //28
#define INPUT_PY_SPACE_Y    20

#define INPUT_PY_UP_MIN_X     380
#define INPUT_PY_UP_MIN_Y     50  
#define INPUT_PY_UP_MAX_X	  35 + 380  //29
#define INPUT_PY_UP_MAX_Y	  29 + 50

#define INPUT_PY_DOWN_MIN_X     430
#define INPUT_PY_DOWN_MIN_Y     50  
#define INPUT_PY_DOWN_MAX_X	  	35 + 430  //29
#define INPUT_PY_DOWN_MAX_Y	    29 + 50

extern unsigned int nTouchX, nTouchY, nTouchPress;      

extern char TS_SYmb[];

void chn_Init(void);
void eng_Init(void);
void sym_Init(void);
QChar chn_keyPress(int nKey);
QChar eng_keyPress(int nKey);
QChar sym_keyPress(int nKey);
QChar chn_TsPress(int nKey);   
QChar eng_TsPress(int nKey);  

void uiProcDrawStatusbar(QLabel *pLbl, int nOK, int nESC);
/************************************************************************/
/*                                                                      */
/************************************************************************/
CT9Window::CT9Window(QWidget */*parent = NULL */)
{
	GUI_DLG_IMPL(FALSE);
	GUI_DLG_CENTER(this);
//	GUI_DLG_SET_THEME_1();

	m_InputWindow = new SBLabel(this, qRgba(59, 129, 212, 0));
	if (!m_InputWindow)
		return;
//	ui.lblBackground->hide();  
	m_InputWindow->setGeometry(ui.lblStatusText->x(), ui.lblStatusText->y(),ui.lblStatusText->width(),ui.lblStatusText->height());  
	m_InputWindow->show();  
	m_InputWindow->setFont(SB_FONT_4());

	GUI_DLG_STATUSBAR();
}

enum {IME_CHINA, IME_ENGLISH, IME_COUNT};    

QString CT9Window::DoProcess()
{
    USER_INFO* pUserInfo;
	int nKey;
	int i, j, m, x, y, w, h, w_spacer, h_spacer;  
	QString szIconFile;
	QString str;
	
	QChar ch;
	QString strResult;

	int nIME = IME_CHINA;
	const int __IME_STR[] = {UISTR_T9_CHN, UISTR_T9_ENG}; 

	chn_Init();
	eng_Init();
	
	g_nEditStatus = T9_Start;
	
	g_T9Staute = new SBLabel(this,qRgba(59, 129, 212, 0));
	g_T9Staute->setGeometry(410,17,T9_IME_CHAR_WIDTH*5,T9_IME_CHAR_HEIGHT+3);   
	g_T9Staute->show();
	g_T9Staute->setFont(SB_FONT_4());
	g_T9Staute->SetText(T9_IME_INDEX, UISTR(__IME_STR[nIME]), T9_IME_FORECOLOR, T9_IME_BGCOLOR, T9_IME_POS_X, T9_IME_POS_Y, T9_IME_CHAR_WIDTH, T9_IME_CHAR_HEIGHT);

	g_T9Window = new SBLabel(this, qRgba(59, 129, 212, 0)); 
	g_T9Window->setGeometry(INPUT_PY_START_X, INPUT_PY_START_Y, INPUT_PY_WIDTH, INPUT_PY_HEIGHT);  
	g_T9Window ->show();  
	g_T9Window->setFont(SB_FONT_4());

	if ( gUserInfoTemp.ID != 0 )
	{
		pUserInfo = (USER_INFO*)DbUserInfoGetPointer(gUserInfoTemp.ID);
		if (pUserInfo)
		{
			ui.txtName->setText(UNICODE2STRING(pUserInfo->NAME, USERNAME_LENGTH));
			strResult = UNICODE2STRING(pUserInfo->NAME, USERNAME_LENGTH);
		}
	}

	while (uiTimeIsTimeout() == FALSE)
	{
		POST_EVENTS();

		nKey = uiKeyGetKey(TRUE); 

		w = INPUT_ABC_SIZE_X; h = INPUT_ABC_SIZE_Y;   
		x = INPUT_ABC1_START_X; y = INPUT_ABC_START_Y; 
		w_spacer = INPUT_ABC_SPACE_X; 
		h_spacer = INPUT_ABC_SPACE_Y;

		for (i=0; i<INPUT_ABC_COUNT; i++)
		{
			switch(i)
			{
				case INPUT_ABC1_COLS:
					 x = INPUT_ABC2_START_X;
					 y = y + h + h_spacer;
					 break;
				case INPUT_ABC2_COLS:
					 x = INPUT_ABC3_START_X;
					 y = y + h + h_spacer;
					 break;
				case INPUT_ABC3_COLS:
					 x = INPUT_ABC4_START_X;
					 y = y + h + h_spacer;
					 break;
			}

			if ((nTouchX >= x) && (nTouchX <= (x+w)) && (nTouchY >= y) && (nTouchY <= (y+h)))  
			{

				if ((i + UIABC_Q) >= UIABC_Q && (i + UIABC_Q) <= UIABC_M)
				{
					 if (nIME == IME_CHINA)
						chn_TsPress(T_UI_TS_ABC(i));
					 else if (nIME == IME_ENGLISH)
						eng_TsPress(T_UI_TS_ABC(i));
				}
				else if ((i + UIABC_Q) == UIABC_OK )
				{
					 memset(&gUserInfoTemp.NAME, 0, sizeof(gUserInfoTemp.NAME));
					 STRING2UNICODE(ui.txtName->text(), gUserInfoTemp.NAME, USERNAME_LENGTH);
					 return ui.txtName->text();
				}
				else if ((i + UIABC_Q) == UIABC_DEL )
				{					 
					 if (nIME == IME_CHINA)
						ch = chn_TsPress(UIABC_DEL);
					 else if (nIME == IME_ENGLISH)
                        ch = eng_TsPress(UIABC_DEL);

					 if (ch == UIABC_DEL)
					 {
						  if (strResult.length() > 0)
						  {
							   strResult.remove(strResult.length() - 1, 1);
							   ui.txtName->setText(strResult);
						  }
					 }
				}
				else if ((i + UIABC_Q) == UIABC_CH || (i + UIABC_Q) == UIABC_EN )
				{
                    if(g_nEditStatus == T9_Start || g_nEditStatus == T9_Select)
					{
                        if ((i + UIABC_Q) == UIABC_CH)
							 nIME = IME_CHINA;
						else nIME = IME_ENGLISH;

						chn_Init();
						eng_Init();

						g_T9Window->ClearText(0, MAX_TEXTITEM_CNT);
						g_T9Staute->SetText(T9_IME_INDEX, UISTR(__IME_STR[nIME]), T9_IME_FORECOLOR, T9_IME_BGCOLOR,
							T9_IME_POS_X, T9_IME_POS_Y, T9_IME_CHAR_WIDTH, T9_IME_CHAR_HEIGHT);
					}
				}
				else if ((i + UIABC_Q) == UIABC_ESC)
				{
					 ui.txtName->clear();
					 return ui.txtName->text();
				}

				break;
			}
			x = x + w + w_spacer;  
		}
		
		if ((nTouchX >= INPUT_PY_UP_MIN_X) && (nTouchX <= INPUT_PY_UP_MAX_X) && (nTouchY >= INPUT_PY_UP_MIN_Y) && (nTouchY <= INPUT_PY_UP_MAX_Y))  
		{
			chn_TsPress(UIABC_UP);
		}
		if ((nTouchX >= INPUT_PY_DOWN_MIN_X) && (nTouchX <= INPUT_PY_DOWN_MAX_X) && (nTouchY >= INPUT_PY_DOWN_MIN_Y) && (nTouchY <= INPUT_PY_DOWN_MAX_Y))  
		{
			chn_TsPress(UIABC_DOWN);
        }

        w = INPUT_PY_SPACE_X; h = INPUT_PY_SPACE_Y;   
		x = INPUT_PY_START_X+T9_NUM_POS_X; y = INPUT_PY_START_Y; 

		for (i=0; i<INPUT_PY_COUNT; i++)
		{
			if ((nTouchX >= x) && (nTouchX <= (x+w)) && (nTouchY >= y) && (nTouchY <= (y+h)))  
			{
				if(g_nEditStatus != T9_Select)
				   g_nEditStatus = T9_Select;

				if (nIME == IME_CHINA)
					ch = chn_TsPress(T_UI_TS_ABC(i) + UIABC_PY1);
				else if (nIME == IME_ENGLISH)
					ch = eng_TsPress(T_UI_TS_ABC(i) + UIABC_PY1);

				if (ch != 0)
				{
					strResult += ch;
					ui.txtName->setText(strResult);
					g_T9Window->ClearText(0, MAX_TEXTITEM_CNT);
				}
				break;
			}

			x = x + w;  
		}  

		if (nKey == UIKEY_ESC)
			break;
		
	}    

	return strResult;

}

CT9Window::~CT9Window()
{
	if (m_InputWindow)
		delete m_InputWindow;
}

SBLabel* CT9Window::GetInputWindow()
{
	return m_InputWindow;
}

//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
void T9_INPUT_PROC(QWidget* mainWidget, QLineEdit* ctrlTextEdit)
{
	int nKey;
	QLabel* pIcon,*pStatusBar;

	
	pIcon = mainWidget->findChild<QLabel*>("lblStatusIcon");
	pIcon->setGeometry(20,201,24,24);
	pStatusBar = mainWidget->findChild<QLabel*>("lblStatusText");
	pStatusBar->hide();

	QPixmap pixmap(QString(GUI_RESOURCE_PATH) + QString("t9-input.png")) ;
	QPixmap oldpixmap;
	oldpixmap =*pIcon->pixmap();
	pIcon->setPixmap(pixmap);
	
	QChar ch;
	int nIME = IME_CHINA;
    const int __IME_STR[] = {UISTR_T9_CHN, UISTR_T9_ENG};  
	QString strResult = ctrlTextEdit->text();

	chn_Init();
	eng_Init();
	//sym_Init();
	
	g_nEditStatus = T9_Start;	

	g_T9Staute = new SBLabel(mainWidget,qRgba(59, 129, 212, 0));
	g_T9Staute->setGeometry(258,17,T9_IME_CHAR_WIDTH*5,T9_IME_CHAR_HEIGHT+3);
	g_T9Staute->show();
	g_T9Staute->setFont(SB_FONT_4());
	g_T9Staute->SetText(T9_IME_INDEX, UISTR(__IME_STR[nIME]), T9_IME_FORECOLOR, T9_IME_BGCOLOR, T9_IME_POS_X, T9_IME_POS_Y, T9_IME_CHAR_WIDTH, T9_IME_CHAR_HEIGHT);
	g_T9Window = new SBLabel(mainWidget, qRgba(59, 129, 212, 0));
    g_T9Window->setGeometry(45,195 ,275,40);  
	g_T9Window ->show();  
	g_T9Window->setFont(SB_FONT_4());
	
	while (uiTimeIsTimeout() == FALSE)
	{
		POST_EVENTS();

		nKey = uiKeyGetKey();
		if (nKey == UIKEY_NONE)
			continue;
		if (uiKeyIsDigit((T_UI_KEY)nKey) && strResult.length() >= ctrlTextEdit->maxLength())
			continue;

		switch(nKey)
		{
        case UIKEY_POWER:       
			if(g_nEditStatus == T9_Start || g_nEditStatus == T9_Select)
			{
				nIME = (nIME + 1) % IME_COUNT;

				chn_Init();
				eng_Init();

				g_T9Window->ClearText(0, MAX_TEXTITEM_CNT);
				g_T9Staute->SetText(T9_IME_INDEX, UISTR(__IME_STR[nIME]), T9_IME_FORECOLOR, T9_IME_BGCOLOR,
					T9_IME_POS_X, T9_IME_POS_Y, T9_IME_CHAR_WIDTH, T9_IME_CHAR_HEIGHT);
				 ctrlTextEdit->setText(strResult);
				break;
			}
			break;
        case UIKEY_OK:
            if(g_nEditStatus == T9_Edit)
			{
				g_nEditStatus = T9_Select;
				goto _lDefaultProcess;
				break;
			} 
			else goto _lExit;
			break;
		case UIKEY_ESC:
			goto _lExit;
		default:
_lDefaultProcess:
			if (nIME == IME_CHINA)
				ch = chn_keyPress(nKey);
			else if (nIME == IME_ENGLISH)
				ch = eng_keyPress(nKey);
			//else if (nIME == IME_SYMBOL)
			//	ch = sym_keyPress(nKey);
			if (ch == UIKEY_MENU)
			{
				if (strResult.length() > 0)
				{
					strResult.remove(strResult.length() - 1, 1);
 					//g_T9Window->SetText(T9_VIEW_INDEX, strResult, T9_VIEW_FORECOLOR, T9_VIEW_BGCOLOR,
 					//	T9_VIEW_POS_X, T9_VIEW_POS_Y, T9_VIEW_CHAR_WIDTH, T9_VIEW_CHAR_HEIGHT);
				//	t9_window->ui.txtResult->setText(strResult);
						ctrlTextEdit->setText(strResult);
				}
			}
			else if (ch != 0)
			{
				strResult += ch;
			//g_T9Window->SetText(T9_VIEW_INDEX, strResult, T9_VIEW_FORECOLOR, T9_VIEW_BGCOLOR,
			//	T9_VIEW_POS_X, T9_VIEW_POS_Y, T9_VIEW_CHAR_WIDTH, T9_VIEW_CHAR_HEIGHT);
	//			t9_window->ui.txtResult->setText(strResult);
					ctrlTextEdit->setText(strResult);
					g_T9Window->ClearText(0, MAX_TEXTITEM_CNT);
				WAIT_EVENT(GETKEY(TRUE) == nKey);
			}
			break;
		}
	}

_lExit:
	//DELETE(t9_window);
	pIcon->setPixmap(oldpixmap);
	pStatusBar->show();
	
	//DELETE(pIcon);
	//DELETE(pStatusBar);
	DELETE(g_T9Staute);
	DELETE(g_T9Window);

	return;
}

//////////////////////////////////////////////////////////////////////////
BOOL T9_DRAW_CHARS(int nPageSize, int & nPageIndex, BOOL /*bNumber*/, QString str)
{
	int i;
	int from, to;
	int nPageCount;
	QString strNumber = "";
	QString strOutput = "";

	if (str.length() == 0)
	{
		g_T9Window->ClearText(T9_NUM_INDEX, T9_STR_INDEX);
		return FALSE;
	}

	nPageSize = MIN(nPageSize, 9);   
	nPageCount = (str.length() + nPageSize - 1) / nPageSize;
	nPageIndex += nPageCount;
	nPageIndex %= nPageCount;

	if (nPageIndex * nPageSize >= str.length())
		return FALSE;
	
	from = nPageIndex * nPageSize;
	to   = from + nPageSize;

	for (i = from; i < to; i++)
	{
		if (i >= str.length())
			break;

		strNumber += QString("%1").arg(i - from + 1);
		strOutput += str[i];
	}

	if (from > 0)
		strOutput += UISTR(UISTR_SYMBOL_UP);
	if (to < str.length())
		strNumber += UISTR(UISTR_SYMBOL_DOWN);

//_lExit:
	if(g_nEditStatus == T9_Edit)
	{	
		g_T9Window->ClearText(T9_NUM_INDEX, MAX_TEXTITEM_CNT);
		g_T9Window->SetText(T9_STR_INDEX, strOutput, T9_STR_FORECOLOR, T9_STR_BGCOLOR, 
			T9_NUM_POS_X, T9_NUM_POS_Y, T9_STR_CHAR_WIDTH, T9_STR_CHAR_HEIGHT, TRUE);
	}
	else
	{
		g_T9Window->ClearText(T9_NUM_INDEX, MAX_TEXTITEM_CNT);
		g_T9Window->SetText(T9_STR_INDEX, strOutput, T9_STR_FORECOLOR, T9_STR_BGCOLOR, 
			T9_NUM_POS_X, T9_NUM_POS_Y, T9_STR_CHAR_WIDTH, T9_STR_CHAR_HEIGHT, TRUE);

	}
		return TRUE;
}
