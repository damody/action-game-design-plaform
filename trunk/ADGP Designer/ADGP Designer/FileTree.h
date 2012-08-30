#pragma once


// CFileTree

class CFileTree : public CTreeCtrl
{
	DECLARE_DYNAMIC(CFileTree)

public:
	CFileTree();
	virtual ~CFileTree();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
};


