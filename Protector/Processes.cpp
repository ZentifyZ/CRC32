#define WIN32_LEAN_AND_MEAN
#include "nt_.hpp"
#include "pch.h"
#include "Processes.h"


/*
    Return:
        FALSE if no bad windows and process is found aka "Good, let's keep going"
        TRUE if we found any bad things, if this return TRUE - do not run and just close out.
*/

__declspec(noinline) BOOL ARE_BAD_TOOLS_RUNNING()
{
    //if (!FindBadWindows() && !FindBadProcesses())
    if (!FindBadProcesses())
        return FALSE;

    return TRUE;
}