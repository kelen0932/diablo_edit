// CDlgFoundry.cpp: 实现文件
//

#include "stdafx.h"
#include "Diablo Edit2.h"
#include "DlgFoundry.h"
#include "afxdialogex.h"

using namespace std;

// CDlgFoundry 对话框

IMPLEMENT_DYNAMIC(CDlgFoundry, CDialogEx)

CDlgFoundry::CDlgFoundry(CD2Item & item, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_Foundry, pParent)
	, m_stItem(item)
	, m_bUnidentified(FALSE), m_bEthereal(FALSE), m_sExtSockets(_T("")) {}

CDlgFoundry::~CDlgFoundry() {}

void CDlgFoundry::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_STATIC_LEVEL, m_sText[0]);
	DDX_Text(pDX, IDC_STATIC_OWNER, m_sText[1]);
	DDX_Text(pDX, IDC_STATIC_CLASS, m_sText[2]);
	DDX_Text(pDX, IDC_CHECK_UNIDENTIFIED, m_sText[3]);
	DDX_Text(pDX, IDC_CHECK_ETHEREAL, m_sText[4]);
	DDX_Text(pDX, IDC_STATIC_DURABILITY, m_sText[5]);
	DDX_Text(pDX, IDC_CHECK_INDESTRUCTIBLE, m_sText[6]);
	DDX_Text(pDX, IDC_STATIC_QUANTITY, m_sText[7]);
	DDX_Text(pDX, IDC_STATIC_QUALITY, m_sText[8]);
	DDX_Text(pDX, IDC_STATIC_Sockets, m_sText[9]);
	DDX_Text(pDX, IDC_STATIC_DEFENCE, m_sText[10]);
	DDX_Text(pDX, IDC_STATIC_MONSTER, m_sText[11]);
	DDX_Text(pDX, IDC_STATIC_FIRST_NAME, m_sText[12]);
	DDX_Text(pDX, IDC_STATIC_SECOND_NAME, m_sText[13]);
	DDX_Text(pDX, IDC_STATIC_SUBTYPE, m_sText[14]);
	DDX_Text(pDX, IDC_STATIC_PREFIX1, m_sText[15]);
	DDX_Text(pDX, IDC_STATIC_SUFFIX1, m_sText[16]);
	DDX_Text(pDX, IDC_STATIC_SET_NAME, m_sText[17]);
	DDX_Text(pDX, IDC_STATIC_UNIQUE_NAME, m_sText[18]);
	DDX_Control(pDX, IDC_COMBO_CLASS, m_cbClass);
	DDX_Control(pDX, IDC_COMBO_QUALITY, m_cbQuality);
	DDX_Control(pDX, IDC_COMBO_MONSTER, m_cbMonster);
	DDX_Control(pDX, IDC_COMBO_FIRST_NAME, m_cbRareCraftedName[0]);
	DDX_Control(pDX, IDC_COMBO_SECOND_NAME, m_cbRareCraftedName[1]);
	DDX_Control(pDX, IDC_COMBO_SUBTYPE, m_cbSubType);
	DDX_Control(pDX, IDC_COMBO_PREFX1, m_cbPrefix[0]);
	DDX_Control(pDX, IDC_COMBO_PREFIX2, m_cbPrefix[1]);
	DDX_Control(pDX, IDC_COMBO_PREFIX3, m_cbPrefix[2]);
	DDX_Control(pDX, IDC_COMBO_SUFFIX1, m_cbSuffix[0]);
	DDX_Control(pDX, IDC_COMBO_SUFFIX2, m_cbSuffix[1]);
	DDX_Control(pDX, IDC_COMBO_SUFFIX3, m_cbSuffix[2]);
	DDX_Control(pDX, IDC_COMBO_SET_NAME, m_cbSetName);
	DDX_Control(pDX, IDC_COMBO_UNIQUE_NAME, m_cbUniqueName);
	DDX_Control(pDX, IDC_EDIT_LEVEL, m_edLevel);
	DDX_Check(pDX, IDC_CHECK_UNIDENTIFIED, m_bUnidentified);
	DDX_Check(pDX, IDC_CHECK_ETHEREAL, m_bEthereal);
	DDX_Control(pDX, IDC_CHECK_INDESTRUCTIBLE, m_chIndestructible);
	DDX_Control(pDX, IDC_EDIT_DURABILITY_MAX, m_edMaxDurability);
	DDX_Control(pDX, IDC_EDIT_DURABILITY, m_edDurability);
	DDX_Control(pDX, IDC_EDIT_QUANTITY, m_edQuantity);
	DDX_Control(pDX, IDC_EDIT_OWNER, m_edOwner);
	DDX_Control(pDX, IDC_EDIT_BASE_SOCKETS, m_edSockets);
	DDX_Text(pDX, IDC_STATIC_SOCKETS_EXT, m_sExtSockets);
	DDX_Control(pDX, IDC_EDIT_DEFENCE, m_edDefence);
}


BEGIN_MESSAGE_MAP(CDlgFoundry, CDialogEx)
	ON_BN_CLICKED(IDC_CHECK_INDESTRUCTIBLE, &CDlgFoundry::OnBnClickedCheckIndestructible)
END_MESSAGE_MAP()


// CDlgFoundry 消息处理程序

void CDlgFoundry::InitUI() {
	//UI text
	for (int i = 0; i < int(size(m_sText)); ++i)
		m_sText[i] = ::theApp.FoundryUI(i);
	//UI combox
	for (UINT i = 0; i < ::theApp.CLASS_NAME_SIZE; ++i)
		m_cbClass.AddString(::theApp.ClassName(i));
	for (UINT i = 0; i < ::theApp.ItemQualityNameSize(); ++i)
		m_cbQuality.AddString(::theApp.ItemQualityName(i));
	for (UINT i = 0; i < ::theApp.MonsterNameSize(); ++i)
		m_cbMonster.AddString(::theApp.MonsterName(i));
	for (UINT i = 0; i < ::theApp.RareCraftedNameSize(); ++i) {
		const auto name = ::theApp.RareCraftedName(i);
		m_cbRareCraftedName[0].InsertString(-1, name);
		m_cbRareCraftedName[1].InsertString(-1, name);
	}
	WCHAR tmp[] = _T("0");
	for (; tmp[0] < _T('8'); ++tmp[0])
		m_cbSubType.InsertString(-1, tmp);
	for (UINT i = 0; i < ::theApp.MagicPrefixSize(); ++i) {
		const auto str = ::theApp.MagicPrefix(i);
		for (auto & cb : m_cbPrefix)
			cb.InsertString(-1, str);
	}
	for (UINT i = 0; i < ::theApp.MagicSuffixSize(); ++i) {
		const auto str = ::theApp.MagicSuffix(i);
		for (auto & cb : m_cbSuffix)
			cb.InsertString(-1, str);
	}
	for (UINT i = 0; i < ::theApp.SetItemNameSize(); ++i)
		m_cbSetName.InsertString(-1, ::theApp.SetItemName(i));
	for (UINT i = 0; i < ::theApp.UniqueNameSize(); ++i)
		m_cbUniqueName.InsertString(-1, ::theApp.UniqueName(i));
}

void CDlgFoundry::ReadItem() {
	SetWindowText(m_stItem.ItemName());
	m_edLevel.EnableWindow(m_stItem.bEar);
	m_cbClass.EnableWindow(m_stItem.bEar);
	m_bUnidentified = !m_stItem.bIdentified;
	m_bEthereal = m_stItem.bEthereal;
	const auto & meta = m_stItem.MetaData();
	m_chIndestructible.EnableWindow(meta.HasDur);
	m_edMaxDurability.EnableWindow(meta.HasDur);
	m_edDurability.EnableWindow(meta.HasDur);
	m_edQuantity.EnableWindow(meta.IsStacked);
	m_edSockets.EnableWindow(FALSE);
	m_sExtSockets = _T("0");
	m_edDefence.EnableWindow(meta.HasDef);
	m_cbMonster.EnableWindow(meta.HasMonsterID);

	if (m_stItem.pEar.exist()) {	//耳朵
		const auto & ear = *m_stItem.pEar;
		m_edLevel.SetWindowText(CSFormat(_T("%d"), ear.iEarLevel));
		m_edOwner.SetWindowText(CString(ear.sEarName));
		m_cbClass.SetCurSel(ear.iEarClass);
	} else {	//普通物品
		m_edOwner.EnableWindow(FALSE);

		if (m_stItem.pItemInfo.exist()) {
			const auto & info = *m_stItem.pItemInfo;

			if (info.pGold.exist()) {
				m_edQuantity.EnableWindow(TRUE);
				m_edQuantity.SetWindowText(CSFormat(_T("%d"), info.pGold->wQuantity));
			} else {
				if (info.pExtItemInfo.exist()) {
					const auto & extInfo = *info.pExtItemInfo;
					m_edLevel.SetWindowText(CSFormat(_T("%d"), extInfo.iDropLevel));
					m_edOwner.EnableWindow(TRUE);
					if (extInfo.sPersonName.exist())
						m_edOwner.SetWindowText(CString(extInfo.sPersonName));
					if (extInfo.wMonsterID.exist())
						m_cbMonster.SetCurSel(extInfo.wMonsterID);
				}
				if (info.pTpSpInfo.exist()) {
					const auto & spec = *info.pTpSpInfo;
					if (spec.iMaxDurability.exist()) {
						m_edMaxDurability.SetWindowText(CSFormat(_T("%d"), int(spec.iMaxDurability)));
						m_edDurability.SetWindowText(CSFormat(_T("%d"), spec.iCurDur.exist() ? int(spec.iCurDur) : 0));
						m_chIndestructible.SetCheck(spec.iMaxDurability == 0);
						OnBnClickedCheckIndestructible();
					}
					if(spec.iQuantity.exist())
						m_edQuantity.SetWindowText(CSFormat(_T("%d"), int(spec.iQuantity)));
					m_edSockets.EnableWindow(TRUE);
					auto s = spec.Sockets();
					m_edSockets.SetWindowText(CSFormat(_T("%d"), s.first));
					m_sExtSockets = CSFormat(_T("%d"), s.second);
					if(spec.iDefence.exist())
						m_edDefence.SetWindowText(CSFormat(_T("%d"), spec.GetDefence()));
				}
			}

		}

	}


}


BOOL CDlgFoundry::OnInitDialog() {
	CDialogEx::OnInitDialog();
	InitUI();
	ReadItem();
	UpdateData(FALSE);
	return TRUE;
}

void CDlgFoundry::OnBnClickedCheckIndestructible() {
	const BOOL ch = m_chIndestructible.GetCheck();
	m_edDurability.EnableWindow(!ch);
	m_edMaxDurability.EnableWindow(!ch);
}
