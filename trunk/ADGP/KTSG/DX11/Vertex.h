#ifndef VERTEX_H
#define VERTEX_H
#include <d3d9.h>
#include <d3dx9.h>

#include <d3d11.h>
#include <windows.h>
#include <d3dx11.h>
#include <vector>

//Hero Weapon Chee Vertex format
struct ClipVertex
{
	D3DXVECTOR3 position;
	D3DXVECTOR2 size;
	float angle;
	D3DXVECTOR4 picpos; // x, y, w, h
	float faceside;
	D3DXVECTOR2 center;
};
typedef std::vector<ClipVertex> ClipVertexs;
//Background Vertex format
struct BGVertex
{
	D3DXVECTOR3 position;
	D3DXVECTOR2 size;
	float angle;
};
typedef std::vector<BGVertex> BGVerteices;
//Color Rect Vertex format
struct CRVertex
{
	D3DXVECTOR3 position;
	D3DXVECTOR2 size;
	float angle;
	D3DXVECTOR4 color;
};
typedef std::vector<CRVertex> CRVerteices;

//Text Vertex format
struct TextVertex
{
	D3DXVECTOR3 position;
	D3DXVECTOR2 size;
	float angle;
	D3DXVECTOR3 color;
};
typedef std::vector<TextVertex> TextVerteices;

//Body Vertex format
struct BodyVertex
{
	D3DXVECTOR3 position;
	D3DXVECTOR2 body;
	float angle;
	float faceside;
	D3DXVECTOR2 center;
};
typedef std::vector<BodyVertex> BodyVerteices;

extern D3D11_INPUT_ELEMENT_DESC VertexDesc_ClipVertex[];
extern D3D11_INPUT_ELEMENT_DESC VertexDesc_BGVertex[];
extern D3D11_INPUT_ELEMENT_DESC VertexDesc_CRVertex[];
extern D3D11_INPUT_ELEMENT_DESC VertexDesc_BodyVertex[];
extern D3D11_INPUT_ELEMENT_DESC VertexDesc_TextVertex[];

#endif // VERTEX_H
