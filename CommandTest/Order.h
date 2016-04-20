#pragma once
#include <vector>
#include "Action.h"
// COrder
static CWinThread* g_pThread = NULL;
static CWinThread* g_pSubroutineThread = NULL;
class COrder : public CWnd
{
	DECLARE_DYNAMIC(COrder)
private:    //參數
    //速度結構(加速度、驅動速度)
    struct Speed {
        LONG AccSpeed;
        LONG EndSpeed;
    };
    //點膠設置結構(點膠開啟時間、點膠關閉停留時間)
    struct DispenseDotSet {
        LONG GlueOpenTime;
        LONG GlueCloseTime;
    };
    //點膠結束結構(第一階段抬升距離、低回程速度、高回程速度)
    struct DispenseDotEnd {
        LONG RiseDistance;
        LONG RiseLowSpeed;
        LONG RiseHightSpeed;
    }; 
    //線段設置結構(移動前延遲、移動前距離、節點時間、停留時間、關機距離、關機延遲)
    struct DispenseLineSet {
        LONG BeforeMoveDelay;
        LONG BeforeMoveDistance;
        LONG NodeTime;
        LONG StayTime;
        LONG ShutdownDistance;
        LONG ShutdownDelay;
    };
    //線段結束結構(返回類型、低速度、高度、長度、高速度)
    struct DispenseLineEnd {
        LONG Type;
        LONG LowSpeed;
        LONG Height;
        LONG Width;
        LONG HighSpeed;
    };
    //程序控管結構(標籤名稱、子程序名稱、回子程序地址)
    struct Program {
        int LabelCount;
        CString LabelName;
        CString SubroutineName;
        int BackSubroutineAddress;
    };
    //Z軸資訊結構(Z軸回升高度)
    struct ZSet {
        LONG ZBackHeight;
    };
    //Arc And Circle運作結構 (狀態、紀錄X、紀錄Y)
    struct AACData {
        BOOL Status;
        LONG X;
        LONG Y;
    };
    //出膠結構 (出膠時間、斷膠停留時間)
    struct GlueData {
        LONG GlueTime;
        LONG GlueStayTime;
    };
    //運行參數結構(運行狀態、運行計數、運行迴圈)  
    //運作狀態(0:未運作 1:運行中 2:暫停中)
    //運行計數(目前做到第幾個指令)
    //運行迴圈(從1-End算一個迴圈)
    struct RunData {
        UINT RunStatus;
        int RunCount; 
    };
    
private:    //變數
    HANDLE  wakeEvent;
    
private:    //函數
    static  UINT    Thread(LPVOID pParam);
    static  UINT    SubroutineThread(LPVOID pParam);
    static  CString CommandResolve(CString Command,UINT Choose);
    void            ParameterDefult();
    void            DecideClear();
public:     //變數
    LONG            Time;
    CAction         m_Action;
    CString         Commanding;
    std::vector<CString> Command;

    DispenseDotSet  DispenseDotSet;
    DispenseDotEnd  DispenseDotEnd;
    DispenseLineSet DispenseLineSet;
    DispenseLineEnd DispenseLineEnd;
    Speed           DotSpeedSet,LineSpeedSet;
    Program         Program;
    ZSet            ZSet;
    AACData         ArcData,CircleData;
    GlueData        GlueData;
    RunData         RunData;
public:     //函數
	COrder();
	virtual ~COrder();
    //開始命令解譯(成功return 1失敗return 0)
	BOOL    Run();
    //立即停止命令解譯(成功return 1失敗return 0)
	BOOL    Stop();
    //暫停命令解譯(成功return 1失敗return 0)
	BOOL    Pause();
    //繼續命令解譯(成功return 1失敗return 0)
    BOOL    Continue();
protected:
	DECLARE_MESSAGE_MAP()
};


