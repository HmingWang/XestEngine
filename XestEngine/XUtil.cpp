#include "XUtil.h"


void XUtil::Trace(String s)
{
#if defined(DEBUG) || defined(_DEBUG)
	cout << s << endl;
#endif
}