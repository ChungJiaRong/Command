#pragma once
#include "MoveButton.h"

// CCamera ��ܤ��

class CCamera : public CDialogEx
{
	DECLARE_DYNAMIC(CCamera)

public:
	CCamera(CWnd* pParent = NULL);   // �зǫغc�禡
	virtual ~CCamera();

// ��ܤ�����
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif
public: //�ܼ�
    CMoveButton m_Yup, m_Ydown, m_Xup, m_Xdown, m_Zup, m_Zdown;
    UINT RaiChoose;
    
public:// ���
    void MoveXYZ(int MoveX, int MoveY, int MoveZ);
    virtual BOOL OnInitDialog();
    virtual void OnCancel();
    virtual BOOL PreTranslateMessage(MSG* pMsg);
    afx_msg void OnSpeedTypeChange(UINT uId);
    afx_msg void OnBnClickedBtnmove();
    afx_msg void OnBnClickedBtnmodel();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �䴩
    
	DECLARE_MESSAGE_MAP()
   
};