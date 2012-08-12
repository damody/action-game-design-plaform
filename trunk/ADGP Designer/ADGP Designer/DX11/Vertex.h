#ifndef VERTEX_H
#define VERTEX_H
#include <d3d9.h>
#include <d3dx9.h>

#include <d3d11.h>
#include <windows.h>
#include <d3dx11.h>
#include <vector>

//Picture Vertex format
struct PictureVertex
{
	D3DXVECTOR3 position;
	D3DXVECTOR2 size;
};
typedef std::vector<PictureVertex> PictureVertices;

extern D3D11_INPUT_ELEMENT_DESC VertexDesc_PICVertex[];

#endif // VERTEX_H
