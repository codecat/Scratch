#ifdef _MSC_VER

#include "Common.h"
#include "CString.h"
#include <Windows.h>

SCRATCH_NAMESPACE_BEGIN;

inline BOOL SCRATCH_EXPORT _scratch_assert(const char* expr, const char* filename, unsigned lineno)
{
  CString strText;

  char szProgname[MAX_PATH + 1];
  szProgname[MAX_PATH] = '\0';
  GetModuleFileName(NULL, szProgname, MAX_PATH);

  strText.SetF(
    "Assertion Failed!\n\n"
    "Program: %s\n"
    "File: %s\n"
    "Line: %d\n\n"
    "Expression: %s\n\n"
    "(Press Retry to break)",
      szProgname, filename, lineno, expr);

  int nCode = MessageBox(NULL, strText, "Scratch Assertion",
    MB_ABORTRETRYIGNORE|MB_ICONHAND|MB_SETFOREGROUND|MB_TASKMODAL);

  if(nCode == IDABORT) {
    exit(3);
    return FALSE;
  }

  if(nCode == IDRETRY) {
    return TRUE;
  }

  if(nCode == IDIGNORE) {
    return FALSE;
  }

  return FALSE;
}

SCRATCH_NAMESPACE_END;

#endif
