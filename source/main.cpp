#include "precomp.h"
#include "gui/MainWindow.h"
#include <QtCore/QTextCodec>
#include "style/customstyle.h"
#include <QtPlugin>
#include "dbug.c"

void uiProcMain(BOOL bFirst);
void* DAEMON_THREAD(void* arg);
BOOL SB3500A_LOAD();

Q_IMPORT_PLUGIN(qjpeg)
//////////////////////////////////////////////////////////////////////////
int main(int argc, char ** argv)
{
	BOOL bFirst = TRUE;

	Q_INIT_RESOURCE(sb3000);

	QApplication app(argc, argv);

	app.setFont(SB_FONT_3());
	app.setFont(SB_FONT_4(), "QLineEdit");

	app.setStyle(new CustomStyle);
	QTextCodec::setCodecForTr(QTextCodec::codecForName(TEXTCODEC));

	if (!SB3500A_LOAD())
	{
		printf("Database Load fail\n");
		return 0;
	}

	while (1)
	{
		CMainWindow *w = new CMainWindow();
		if (w)
		{
			uiProcMain(bFirst);
			delete w;
		}
		bFirst = FALSE;
	}

	return 0;
}

BOOL InitFpLibrary(void);
//
//
//////////////////////////////////////////////////////////////////////////
BOOL SB3500A_LOAD()
{
	BOOL bFpLibraryLoad = InitFpLibrary();
	   
	if (SB3000DEV_INIT1() != DEVERR_SUCCESS)
	{
//		uiLcdMessageBox(UI_MSG_ERROR, UISTR_DEVICE_ERROR, UITIME_OUT);
		while (1)
		{
			BUZZER_START(); LED_G_ON(); LED_R_ON(); DelayMiliSecond(500);
			BUZZER_STOP();  LED_G_OFF();LED_R_OFF();DelayMiliSecond(500);
		}
	}   

	LCD_CTL_ON();

	if (!bFpLibraryLoad)
	{
		BUZZER_START(); LED_G_ON(); LED_R_ON();
		while (1) {};
	}  

	BOOL bRet = DbSetupTotalRead();
	
	if (SB3000DEV_INIT2() != DEVERR_SUCCESS)
	{
//		uiLcdMessageBox(UI_MSG_ERROR, UISTR_DEVICE_ERROR, UITIME_OUT);
		while (1)
		{
			BUZZER_START(); LED_G_ON(); LED_R_ON(); DelayMiliSecond(500);
			BUZZER_STOP();  LED_G_OFF();LED_R_OFF();DelayMiliSecond(500);
		}
	}  
	//nfsµ÷ÊÔÔÝÊ±É¾³ý
	//comm_tcpserver_init();
	
	LCD_BLANK(FBINFO_BLANK_PAUSE);

	gbIsCMOS = TRUE;
	gCMOSType = dbLicense.nCMOS;
//	gCMOSType = CMOSTYPE_HV7131R;
	
	if (SB_FP_OPEN(gCMOSType, NULL, NULL) != FP_ERR_SUCCESS)
	{
		uiLcdMessageBox(UI_MSG_ERROR, UISTR_DEVICE_ERROR, UITIME_OUT);
//		printf("FP Engine Open Error !\n");
		gbIsCMOS = FALSE;
	}

	uiCMOSCheck();

	LCD_BLANK(FBINFO_BLANK_RESUME);
	if (!Db_LoadAllData(bRet))
	{
		LCD_BLANK(FBINFO_BLANK_PAUSE);
		return FALSE;
	}
	LCD_BLANK(FBINFO_BLANK_PAUSE);

	fp_setlivecheck(TRUE);

	return TRUE;
}
