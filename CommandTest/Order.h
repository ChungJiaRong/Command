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
    //Arc And Circle And Start運作結構 (狀態、紀錄X、紀錄Y、紀錄Z)
    struct ACSData {
        BOOL Status;
        LONG X;
        LONG Y;
        LONG Z;
    };
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
    //程序控管結構(標籤計數、標籤名稱、回子程序地址)
    struct Program {
        int LabelCount;
        CString LabelName;
        UINT SubroutinCount;
        BOOL CallSubroutineStatus;
        std::vector<UINT> SubroutineStack;
        std::vector<ACSData> SubroutinePointStack;
    };
    //Z軸資訊結構(Z軸回升高度、Z軸回升型態(0絕對1相對))
    struct ZSet {
        LONG ZBackHeight;
        BOOL ZBackType;
    };
    //出膠結構 (出膠時間、斷膠停留時間)
    struct GlueData {
        LONG GlueTime;
        LONG GlueStayTime;
    };
    //運行參數結構(副程式名子、運行狀態、運行計數、控制主副程序、主副程序堆疊計數、動作狀態)  
    //運作狀態(0:未運作 1:運行中 2:暫停中)
    //運行計數(目前做到第幾個指令 0:主程序 1-X:副程序)
    //動作狀態(0:線段執行完畢 1:線段尚未執行完成 2:Goto過的線段)
    struct RunData {
        CString SubProgramName;
        UINT RunStatus;
        std::vector<UINT> RunCount;//計數程序命令
        std::vector<UINT> MSChange; //控管目前所讀的程序
        UINT StackingCount;
        std::vector<UINT> ActionStatus;
    };
    
private:    //變數
    HANDLE  wakeEvent;
    
private:    //函數
    static  UINT    Thread(LPVOID pParam);
    static  UINT    SubroutineThread(LPVOID pParam);
    static  void    LineGotoActionJudge(LPVOID pParam);
    static  CString CommandResolve(CString Command,UINT Choose);
    void            ParameterDefult();
    void            DecideClear();
    
public:     //變數
    LONG            Time;
    CAction         m_Action;
    CString         Commanding;
    std::vector<CString> CommandMemory;
    std::vector<CString> CommandSwap;
    std::vector<std::vector<CString>> Command;
    
    DispenseDotSet  DispenseDotSet;
    DispenseDotEnd  DispenseDotEnd;
    DispenseLineSet DispenseLineSet;
    DispenseLineEnd DispenseLineEnd;
    Speed           DotSpeedSet,LineSpeedSet;
    Program         Program;
    ZSet            ZSet;
    GlueData        GlueData;
    RunData         RunData;
    ACSData         InitData;
    std::vector<ACSData> ArcData, CircleData1, CircleData2, StartData;
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
    void            MainSubroutineSeparate();
protected:
	DECLARE_MESSAGE_MAP()
};


