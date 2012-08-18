#include "Vertex.h"

D3D11_INPUT_ELEMENT_DESC VertexDesc_ClipVertex[] =
{
	{"POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0,  0, D3D11_INPUT_PER_VERTEX_DATA, 0},
	{"SIZE",	0, DXGI_FORMAT_R32G32_FLOAT,		0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
	{"PI",		0, DXGI_FORMAT_R32_FLOAT,		0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0},
	{"PICPOS",	0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0},
	{"FACE",	0, DXGI_FORMAT_R32_FLOAT,		0, 40, D3D11_INPUT_PER_VERTEX_DATA, 0},
	{"CENTER",	0, DXGI_FORMAT_R32G32_FLOAT,		0, 44, D3D11_INPUT_PER_VERTEX_DATA, 0},
};

D3D11_INPUT_ELEMENT_DESC VertexDesc_BGVertex[] =
{
	{"POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0,  0, D3D11_INPUT_PER_VERTEX_DATA, 0},
	{"SIZE",	0, DXGI_FORMAT_R32G32_FLOAT,		0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
	{"PI",		0, DXGI_FORMAT_R32_FLOAT,       	0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0},
};

D3D11_INPUT_ELEMENT_DESC VertexDesc_CRVertex[] =
{
	{"POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0,  0, D3D11_INPUT_PER_VERTEX_DATA, 0},
	{"SIZE",	0, DXGI_FORMAT_R32G32_FLOAT,		0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
	{"PI",		0, DXGI_FORMAT_R32_FLOAT,		0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0},
	{"COLOR",	0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0},
};

D3D11_INPUT_ELEMENT_DESC VertexDesc_BodyVertex[] =
{
	{"POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0,  0, D3D11_INPUT_PER_VERTEX_DATA, 0},
	{"BODY",	0, DXGI_FORMAT_R32G32_FLOAT,		0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
	{"PI",		0, DXGI_FORMAT_R32_FLOAT,		0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0},
	{"FACE",	0, DXGI_FORMAT_R32_FLOAT,		0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0},
	{"CENTER",	0, DXGI_FORMAT_R32G32_FLOAT,		0, 28, D3D11_INPUT_PER_VERTEX_DATA, 0},
};

D3D11_INPUT_ELEMENT_DESC VertexDesc_TextVertex[] =
{
	{"POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0,  0, D3D11_INPUT_PER_VERTEX_DATA, 0},
	{"SIZE",	0, DXGI_FORMAT_R32G32_FLOAT,		0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
	{"PI",		0, DXGI_FORMAT_R32_FLOAT,		0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0},
	{"FORECOLOR",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0},
};