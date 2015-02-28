#include "XUtil.h"

XUtil& XUtil::GetInstance()
{
	static XUtil instance;
	return instance;
}

void XUtil::Debug(String s)
{
#if defined(DEBUG) || defined(_DEBUG)
	cout << s << endl;
#endif
}
