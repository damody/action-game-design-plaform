#pragma once
#include <cstdio>
#define DXTRACE_MSG(str)              wprintf(str)
#define DXTRACE_ERR(str,hr)           (hr)
#define DXTRACE_ERR_MSGBOX(str,hr)    (hr)