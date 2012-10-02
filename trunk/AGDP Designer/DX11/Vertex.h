#ifndef VERTEX_H
#define VERTEX_H
#include <d3d9.h>
#include <d3dx9.h>

#include <d3d11.h>
#include <windows.h>
#include <d3dx11.h>
#include <vector>

//Picture Vertex format
struct PointVertex
{
	D3DXVECTOR2 position;
	D3DXVECTOR2 size;
	D3DXVECTOR4 color;
};
typedef std::vector<PointVertex> PointVertices;

//Picture Vertex format
struct LineVertex
{
	D3DXVECTOR2 position;
	D3DXVECTOR4 color;
};
typedef std::vector<LineVertex> LineVertices;

//Picture Vertex format
struct PictureVertex
{
	D3DXVECTOR2 position;
	D3DXVECTOR2 size;
	D3DXVECTOR4 picpos;
};
typedef std::vector<PictureVertex> PictureVertices;

struct GamePictureVertex
{
	D3DXVECTOR2 position;
	D3DXVECTOR2 size;
	D3DXVECTOR4 picpos;
	float	    faceside;
	D3DXVECTOR2 center;
};
typedef std::vector<GamePictureVertex> GamePictureVertices;

extern D3D11_INPUT_ELEMENT_DESC VertexDesc_PointVertex[];
extern D3D11_INPUT_ELEMENT_DESC VertexDesc_LineVertex[];
extern D3D11_INPUT_ELEMENT_DESC VertexDesc_PICVertex[];
extern D3D11_INPUT_ELEMENT_DESC VertexDesc_GPICVertex[];
#endif // VERTEX_H
