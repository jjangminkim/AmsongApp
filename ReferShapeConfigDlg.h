#pragma once

#include <map>

// CReferShapeConfigDlg ��ȭ �����Դϴ�.

namespace Amsong {
    class ShapeManager;
}

class CReferShapeConfigDlg : public CDialog
{
	DECLARE_DYNAMIC(CReferShapeConfigDlg)

public:
	CReferShapeConfigDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CReferShapeConfigDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_REFER_CONFIG_DIALOG };

protected:
    virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()

private:
    enum {
        SHAPE_TYPE_ALL = 0,
        SHAPE_TYPE_RECTANGLE,
        SHAPE_TYPE_TRIANGLE,
        SHAPE_TYPE_PIE,
    };

    int _radioShape;
    int _shapeId;
    int _shapeType;

    typedef std::map<int, int> IdShapeMap;
    IdShapeMap _rectangleIdMap;
    IdShapeMap _triangleIdMap;
    IdShapeMap _pieIdMap;

    Amsong::ShapeManager* _shapeManager;

public:
    void setShapeManager(Amsong::ShapeManager* manager) { _shapeManager = manager; }

private:
    void enableControls(int type);
    int shapeType(UINT id);

public:
    afx_msg void setRadioValeu(UINT id);

    afx_msg void OnBnClickedBtnCtrlLeft();
    afx_msg void OnBnClickedBtnCtrlUp();
    afx_msg void OnBnClickedBtnCtrlDown();
    afx_msg void OnBnClickedBtnCtrlRight();
    afx_msg void OnBnClickedBtnCtrlHeightPlus();
    afx_msg void OnBnClickedBtnCtrlHeightMinus();
    afx_msg void OnBnClickedBtnCtrlWidthPlus();
    afx_msg void OnBnClickedBtnCtrlWidthMinus();
    afx_msg void OnBnClickedBtnCtrlAnglePlus();
    afx_msg void OnBnClickedBtnCtrlAngleMinus();
};
