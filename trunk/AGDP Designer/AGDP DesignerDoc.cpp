// 這個 MFC 範例原始程式碼會示範如何使用 MFC Microsoft Office Fluent 使用者介面
// (「Fluent UI」)，並且僅提供為參考資料，做為
// MFC 參考及 MFC C++ 程式庫軟體
// 隨附相關電子文件的補充。
// 關於 Fluent UI 之複製、使用或散發的授權條款則分別提供。
// 如需 Fluent UI 授權計劃的詳細資訊，請造訪
// http://msdn.microsoft.com/officeui。
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// AGDP DesignerDoc.cpp : CAGDPDesignerDoc 類別的實作
//

#include "stdafx.h"
// SHARED_HANDLERS 可以定義在實作預覽、縮圖和搜尋篩選條件處理常式的
// ATL 專案中，並允許與該專案共用文件程式碼。
#ifndef SHARED_HANDLERS
#include "AGDP Designer.h"
#endif

#include "AGDP DesignerDoc.h"

#include <propkey.h>


#include "ClassView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CAGDPDesignerDoc

IMPLEMENT_DYNCREATE( CAGDPDesignerDoc, CDocument )

BEGIN_MESSAGE_MAP( CAGDPDesignerDoc, CDocument )
END_MESSAGE_MAP()


// CAGDPDesignerDoc 建構/解構

CAGDPDesignerDoc::CAGDPDesignerDoc()
{
	// TODO: 在此加入一次建構程式碼
}

CAGDPDesignerDoc::~CAGDPDesignerDoc()
{
}

BOOL CAGDPDesignerDoc::OnNewDocument()
{
	if ( !CDocument::OnNewDocument() )
	{
		return FALSE;
	}

	return TRUE;
}




// CAGDPDesignerDoc 序列化

void CAGDPDesignerDoc::Serialize( CArchive& ar )
{
	if ( ar.IsStoring() )
	{
		// TODO: 在此加入儲存程式碼
	}
	else
	{
		// TODO: 在此加入載入程式碼
	}
}

#ifdef SHARED_HANDLERS

// 縮圖的支援
void CAGDPDesignerDoc::OnDrawThumbnail( CDC& dc, LPRECT lprcBounds )
{
	// 修改這段程式碼以繪製文件的資料
	dc.FillSolidRect( lprcBounds, RGB( 255, 255, 255 ) );
	CString strText = _T( "TODO: implement thumbnail drawing here" );
	LOGFONT lf;
	CFont* pDefaultGUIFont = CFont::FromHandle( ( HFONT ) GetStockObject( DEFAULT_GUI_FONT ) );
	pDefaultGUIFont->GetLogFont( &lf );
	lf.lfHeight = 36;
	CFont fontDraw;
	fontDraw.CreateFontIndirect( &lf );
	CFont* pOldFont = dc.SelectObject( &fontDraw );
	dc.DrawText( strText, lprcBounds, DT_CENTER | DT_WORDBREAK );
	dc.SelectObject( pOldFont );
}

// 搜尋處理常式的支援
void CAGDPDesignerDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 設定來自文件資料的搜尋內容。
	// 內容部分應該以 ";" 隔開
	// 範例:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent( strSearchContent );
}

void CAGDPDesignerDoc::SetSearchContent( const CString& value )
{
	if ( value.IsEmpty() )
	{
		RemoveChunk( PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid );
	}
	else
	{
		CMFCFilterChunkValueImpl* pChunk = NULL;
		ATLTRY( pChunk = new CMFCFilterChunkValueImpl );

		if ( pChunk != NULL )
		{
			pChunk->SetTextValue( PKEY_Search_Contents, value, CHUNK_TEXT );
			SetChunkValue( pChunk );
		}
	}
}

#endif // SHARED_HANDLERS

// CAGDPDesignerDoc 診斷

#ifdef _DEBUG
void CAGDPDesignerDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CAGDPDesignerDoc::Dump( CDumpContext& dc ) const
{
	CDocument::Dump( dc );
}
#endif //_DEBUG


// CAGDPDesignerDoc 命令
