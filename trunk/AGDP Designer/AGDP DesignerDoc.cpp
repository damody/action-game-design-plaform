// �o�� MFC �d�ҭ�l�{���X�|�ܽd�p��ϥ� MFC Microsoft Office Fluent �ϥΪ̤���
// (�uFluent UI�v)�A�åB�ȴ��Ѭ��ѦҸ�ơA����
// MFC �ѦҤ� MFC C++ �{���w�n��
// �H�������q�l��󪺸ɥR�C
// ���� Fluent UI ���ƻs�B�ϥΩδ��o�����v���ګh���O���ѡC
// �p�� Fluent UI ���v�p�����ԲӸ�T�A�гy�X
// http://msdn.microsoft.com/officeui�C
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// AGDP DesignerDoc.cpp : CAGDPDesignerDoc ���O����@
//

#include "stdafx.h"
// SHARED_HANDLERS �i�H�w�q�b��@�w���B�Y�ϩM�j�M�z�����B�z�`����
// ATL �M�פ��A�ä��\�P�ӱM�צ@�Τ��{���X�C
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


// CAGDPDesignerDoc �غc/�Ѻc

CAGDPDesignerDoc::CAGDPDesignerDoc()
{
	// TODO: �b���[�J�@���غc�{���X
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




// CAGDPDesignerDoc �ǦC��

void CAGDPDesignerDoc::Serialize( CArchive& ar )
{
	if ( ar.IsStoring() )
	{
		// TODO: �b���[�J�x�s�{���X
	}
	else
	{
		// TODO: �b���[�J���J�{���X
	}
}

#ifdef SHARED_HANDLERS

// �Y�Ϫ��䴩
void CAGDPDesignerDoc::OnDrawThumbnail( CDC& dc, LPRECT lprcBounds )
{
	// �ק�o�q�{���X�Hø�s��󪺸��
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

// �j�M�B�z�`�����䴩
void CAGDPDesignerDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// �]�w�Ӧۤ���ƪ��j�M���e�C
	// ���e�������ӥH ";" �j�}
	// �d��:  strSearchContent = _T("point;rectangle;circle;ole object;");
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

// CAGDPDesignerDoc �E�_

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


// CAGDPDesignerDoc �R�O
