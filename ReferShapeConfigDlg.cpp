// ReferShapeConfigDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "AmsongTester.h"
#include "ReferShapeConfigDlg.h"
#include "afxdialogex.h"
#include "ShapeManager.h"


// CReferShapeConfigDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CReferShapeConfigDlg, CDialog)

CReferShapeConfigDlg::CReferShapeConfigDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CReferShapeConfigDlg::IDD, pParent)
    , _shapeId(0)
    , _shapeType(SHAPE_TYPE_ALL)
{
}

CReferShapeConfigDlg::~CReferShapeConfigDlg()
{
}

BOOL CReferShapeConfigDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    unsigned int i;
    unsigned int shapeId;
    for (i = IDC_RD_RECT_OUT_LEFT, shapeId = 0; i <= IDC_RD_RECT_BOTTOM; ++i) {
        _rectangleIdMap[i] = shapeId++;
    }
    for (i = IDC_RD_TRI_BIG, shapeId = 0; i <= IDC_RD_TRI_MICRO; ++i) {
        _triangleIdMap[i] = shapeId++;
    }
    for (i = IDC_RD_PIE_BIG_CENTER, shapeId = 0; i <= IDC_RD_PIE_SMALL; ++i) {
        _pieIdMap[i] = shapeId++;
    }

    _shapeId = IDC_RD_ALL;
    _shapeType = SHAPE_TYPE_ALL;
    enableControls(_shapeType);
    ((CButton*)GetDlgItem(IDC_RD_ALL))->SetCheck(true);

    return TRUE;
}

void CReferShapeConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
    DDX_Radio(pDX, IDC_RD_ALL, _radioShape);
}


BEGIN_MESSAGE_MAP(CReferShapeConfigDlg, CDialog)
    ON_CONTROL_RANGE(BN_CLICKED, IDC_RD_ALL, IDC_RD_PIE_SMALL, &CReferShapeConfigDlg::setRadioValeu)
    ON_BN_CLICKED(IDC_BTN_CTRL_LEFT, &CReferShapeConfigDlg::OnBnClickedBtnCtrlLeft)
    ON_BN_CLICKED(IDC_BTN_CTRL_UP, &CReferShapeConfigDlg::OnBnClickedBtnCtrlUp)
    ON_BN_CLICKED(IDC_BTN_CTRL_DOWN, &CReferShapeConfigDlg::OnBnClickedBtnCtrlDown)
    ON_BN_CLICKED(IDC_BTN_CTRL_RIGHT, &CReferShapeConfigDlg::OnBnClickedBtnCtrlRight)
    ON_BN_CLICKED(IDC_BTN_CTRL_HEIGHT_PLUS, &CReferShapeConfigDlg::OnBnClickedBtnCtrlHeightPlus)
    ON_BN_CLICKED(IDC_BTN_CTRL_HEIGHT_MINUS, &CReferShapeConfigDlg::OnBnClickedBtnCtrlHeightMinus)
    ON_BN_CLICKED(IDC_BTN_CTRL_WIDTH_PLUS, &CReferShapeConfigDlg::OnBnClickedBtnCtrlWidthPlus)
    ON_BN_CLICKED(IDC_BTN_CTRL_WIDTH_MINUS, &CReferShapeConfigDlg::OnBnClickedBtnCtrlWidthMinus)
    ON_BN_CLICKED(IDC_BTN_CTRL_ANGLE_PLUS, &CReferShapeConfigDlg::OnBnClickedBtnCtrlAnglePlus)
    ON_BN_CLICKED(IDC_BTN_CTRL_ANGLE_MINUS, &CReferShapeConfigDlg::OnBnClickedBtnCtrlAngleMinus)
END_MESSAGE_MAP()

void CReferShapeConfigDlg::enableControls(int type)
{
    BOOL enableMove = FALSE;
    BOOL enableSize = FALSE;
    BOOL enableAngle = FALSE;

    switch (type) {
        case SHAPE_TYPE_ALL:
            enableMove = TRUE;
            break;
        case SHAPE_TYPE_RECTANGLE:
            enableMove = TRUE;
            enableSize = TRUE;
            break;
        case SHAPE_TYPE_TRIANGLE:
            enableMove = TRUE;
            enableSize = TRUE;
            break;
        case SHAPE_TYPE_PIE: {
            enableMove = TRUE;
            enableSize = TRUE;
            if (Amsong::ShapeManager::BIG_LEFT_PIE == _pieIdMap[_shapeId] ||
                Amsong::ShapeManager::BIG_RIGHT_PIE == _pieIdMap[_shapeId]) {
                enableAngle = TRUE;
            }
            break;
        }
    }

    GetDlgItem(IDC_BTN_CTRL_LEFT)->EnableWindow(enableMove);
    GetDlgItem(IDC_BTN_CTRL_RIGHT)->EnableWindow(enableMove);
    GetDlgItem(IDC_BTN_CTRL_UP)->EnableWindow(enableMove);
    GetDlgItem(IDC_BTN_CTRL_DOWN)->EnableWindow(enableMove);

    GetDlgItem(IDC_BTN_CTRL_HEIGHT_PLUS)->EnableWindow(enableSize);
    GetDlgItem(IDC_BTN_CTRL_HEIGHT_MINUS)->EnableWindow(enableSize);
    GetDlgItem(IDC_BTN_CTRL_WIDTH_PLUS)->EnableWindow(enableSize);
    GetDlgItem(IDC_BTN_CTRL_WIDTH_MINUS)->EnableWindow(enableSize);

    GetDlgItem(IDC_BTN_CTRL_ANGLE_PLUS)->EnableWindow(enableAngle);
    GetDlgItem(IDC_BTN_CTRL_ANGLE_MINUS)->EnableWindow(enableAngle);
}

int CReferShapeConfigDlg::shapeType(UINT id)
{
    int shapeType = SHAPE_TYPE_ALL;
    if ((IDC_RD_RECT_OUT_LEFT <= id) &&
        (id <= IDC_RD_RECT_BOTTOM)) {
        shapeType = SHAPE_TYPE_RECTANGLE;
    }
    else if ((IDC_RD_TRI_BIG <= id) &&
             (id <= IDC_RD_TRI_MICRO)) {
        shapeType = SHAPE_TYPE_TRIANGLE;
    }
    else if ((IDC_RD_PIE_BIG_CENTER <= id) &&
             (id <= IDC_RD_PIE_SMALL)) {
        shapeType = SHAPE_TYPE_PIE;
    }

    _shapeId = id;
    _shapeType = shapeType;

    return shapeType;
}

void CReferShapeConfigDlg::setRadioValeu(UINT id)
{
    enableControls(shapeType(id));
}


void CReferShapeConfigDlg::OnBnClickedBtnCtrlLeft()
{
    if (SHAPE_TYPE_ALL == _shapeType) {
        _shapeManager->moveAllHorizontally(-1);
    }
    else if (SHAPE_TYPE_RECTANGLE == _shapeType) {
        _shapeManager->moveRectangle(_rectangleIdMap[_shapeId], -1, 0);
    }
    else if (SHAPE_TYPE_TRIANGLE == _shapeType) {
        _shapeManager->moveTriangle(_triangleIdMap[_shapeId], -1, 0);
    }
    else if (SHAPE_TYPE_PIE == _shapeType) {
        _shapeManager->movePie(_pieIdMap[_shapeId], -1, 0);
    }
}


void CReferShapeConfigDlg::OnBnClickedBtnCtrlUp()
{
    if (SHAPE_TYPE_ALL == _shapeType) {
        _shapeManager->moveAllVerically(-1);
    }
    else if (SHAPE_TYPE_RECTANGLE == _shapeType) {
        _shapeManager->moveRectangle(_rectangleIdMap[_shapeId], 0, -1);
    }
    else if (SHAPE_TYPE_TRIANGLE == _shapeType) {
        _shapeManager->moveTriangle(_triangleIdMap[_shapeId], 0, -1);
    }
    else if (SHAPE_TYPE_PIE == _shapeType) {
        _shapeManager->movePie(_pieIdMap[_shapeId], 0, -1);
    }
}


void CReferShapeConfigDlg::OnBnClickedBtnCtrlDown()
{
    if (SHAPE_TYPE_ALL == _shapeType) {
        _shapeManager->moveAllVerically(1);
    }
    else if (SHAPE_TYPE_RECTANGLE == _shapeType) {
        _shapeManager->moveRectangle(_rectangleIdMap[_shapeId], 0, 1);
    }
    else if (SHAPE_TYPE_TRIANGLE == _shapeType) {
        _shapeManager->moveTriangle(_triangleIdMap[_shapeId], 0, 1);
    }
    else if (SHAPE_TYPE_PIE == _shapeType) {
        _shapeManager->movePie(_pieIdMap[_shapeId], 0, 1);
    }
}


void CReferShapeConfigDlg::OnBnClickedBtnCtrlRight()
{
    if (SHAPE_TYPE_ALL == _shapeType) {
        _shapeManager->moveAllHorizontally(1);
    }
    else if (SHAPE_TYPE_RECTANGLE == _shapeType) {
        _shapeManager->moveRectangle(_rectangleIdMap[_shapeId], 1, 0);
    }
    else if (SHAPE_TYPE_TRIANGLE == _shapeType) {
        _shapeManager->moveTriangle(_triangleIdMap[_shapeId], 1, 0);
    }
    else if (SHAPE_TYPE_PIE == _shapeType) {
        _shapeManager->movePie(_pieIdMap[_shapeId], 1, 0);
    }
}


void CReferShapeConfigDlg::OnBnClickedBtnCtrlHeightPlus()
{
    if (SHAPE_TYPE_RECTANGLE == _shapeType) {
        _shapeManager->resizeRectangle(_rectangleIdMap[_shapeId], 0, 1);
    }
    else if (SHAPE_TYPE_TRIANGLE == _shapeType) {
        _shapeManager->resizeTriangle(_triangleIdMap[_shapeId], 0, 1);
    }
    else if (SHAPE_TYPE_PIE == _shapeType) {
        _shapeManager->resizePie(_pieIdMap[_shapeId], 0, 1, 0);
    }
}


void CReferShapeConfigDlg::OnBnClickedBtnCtrlHeightMinus()
{
    if (SHAPE_TYPE_RECTANGLE == _shapeType) {
        _shapeManager->resizeRectangle(_rectangleIdMap[_shapeId], 0, -1);
    }
    else if (SHAPE_TYPE_TRIANGLE == _shapeType) {
        _shapeManager->resizeTriangle(_triangleIdMap[_shapeId], 0, -1);
    }
    else if (SHAPE_TYPE_PIE == _shapeType) {
        _shapeManager->resizePie(_pieIdMap[_shapeId], 0, -1, 0);
    }
}


void CReferShapeConfigDlg::OnBnClickedBtnCtrlWidthPlus()
{
    if (SHAPE_TYPE_RECTANGLE == _shapeType) {
        _shapeManager->resizeRectangle(_rectangleIdMap[_shapeId], 1, 0);
    }
    else if (SHAPE_TYPE_TRIANGLE == _shapeType) {
        _shapeManager->resizeTriangle(_triangleIdMap[_shapeId], 1, 0);
    }
    else if (SHAPE_TYPE_PIE == _shapeType) {
        _shapeManager->resizePie(_pieIdMap[_shapeId], 1, 0, 0);
    }
}


void CReferShapeConfigDlg::OnBnClickedBtnCtrlWidthMinus()
{
    if (SHAPE_TYPE_RECTANGLE == _shapeType) {
        _shapeManager->resizeRectangle(_rectangleIdMap[_shapeId], -1, 0);
    }
    else if (SHAPE_TYPE_TRIANGLE == _shapeType) {
        _shapeManager->resizeTriangle(_triangleIdMap[_shapeId], -1, 0);
    }
    else if (SHAPE_TYPE_PIE == _shapeType) {
        _shapeManager->resizePie(_pieIdMap[_shapeId], -1, 0, 0);
    }
}


void CReferShapeConfigDlg::OnBnClickedBtnCtrlAnglePlus()
{
    if (SHAPE_TYPE_PIE == _shapeType) {
        _shapeManager->resizePie(_pieIdMap[_shapeId], 0, 0, 1);
    }
}


void CReferShapeConfigDlg::OnBnClickedBtnCtrlAngleMinus()
{
    if (SHAPE_TYPE_PIE == _shapeType) {
        _shapeManager->resizePie(_pieIdMap[_shapeId], 0, 0, -1);
    }
}
