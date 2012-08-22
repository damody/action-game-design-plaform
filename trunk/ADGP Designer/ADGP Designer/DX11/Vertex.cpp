#include "Vertex.h"

D3D11_INPUT_ELEMENT_DESC VertexDesc_PointVertex[] =
{
	{"POSITION",	0, DXGI_FORMAT_R32G32_FLOAT,		0,  0, D3D11_INPUT_PER_VERTEX_DATA, 0},
	{"SIZE",	0, DXGI_FORMAT_R32G32_FLOAT,		0,  8, D3D11_INPUT_PER_VERTEX_DATA, 0},
	{"COLOR",	0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0, 16, D3D11_INPUT_PER_VERTEX_DATA, 0},
};

D3D11_INPUT_ELEMENT_DESC VertexDesc_LineVertex[] =
{
	{"POSITION",	0, DXGI_FORMAT_R32G32_FLOAT,		0,  0, D3D11_INPUT_PER_VERTEX_DATA, 0},
	{"COLOR",	0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0,  8, D3D11_INPUT_PER_VERTEX_DATA, 0},
};

D3D11_INPUT_ELEMENT_DESC VertexDesc_PICVertex[] =
{
	{"SIZE",	0, DXGI_FORMAT_R32G32_FLOAT,		0,  0, D3D11_INPUT_PER_VERTEX_DATA, 0},
	{"PICPOSITION",	0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0,  8, D3D11_INPUT_PER_VERTEX_DATA, 0},
};
