#ifndef VERTEX_H
#define VERTEX_H
#include <d3d9.h>
#include <d3dx9.h>

#include <d3d11.h>
#include <windows.h>
#include <d3dx11.h>
#include <vector>

struct Screen_Vertex
{
	D3DXVECTOR4 pos;
	D3DXVECTOR2 tex;
};

// Vertex format
struct DXVertex
{
	D3DXVECTOR3 position;
	D3DXVECTOR2 size;
	float angle;
};
typedef std::vector<DXVertex> DXVertexs;
// Vertex format
struct ClipVertex
{
	D3DXVECTOR3 position;
	D3DXVECTOR2 size;
	float angle;
	D3DXVECTOR4 picpos; // x, y, w, h
};
typedef std::vector<ClipVertex> ClipVertexs;
// 
extern D3D11_INPUT_ELEMENT_DESC VertexDesc_DXVertex[];
extern D3D11_INPUT_ELEMENT_DESC VertexDesc_BulletVertex[];
extern D3D11_INPUT_ELEMENT_DESC VertexDesc_SVertex[];

#endif // VERTEX_H