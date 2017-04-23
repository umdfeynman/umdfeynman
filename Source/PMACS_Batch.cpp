#include "PMACS_Batch.h"
#include "PMACS_Logger.h"
#include "PMACS_Globals.h"
#include "PMACS_AddDeleteTemp.h"

bool runOfflineBatchProcess()
{
	bool lastResult = addDeleteStore();
	if (!lastResult)
	{
		Plog.logError("runOfflineBatchProcess", "addDeleteStore failed.  Bailing.");
		return false;
	}

	return true;
}