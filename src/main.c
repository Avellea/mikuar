#include <psp2/kernel/clib.h>
#include <psp2/kernel/modulemgr.h>
#include <psp2/rtc.h> 

#include <taihen.h>

#define printf sceClibPrintf


static tai_hook_ref_t app_start_ref;

SceUID gHook = -1;


int fakeSystemDateTime(int *t) {
  static int offset = 0;
  int desiredTime = 1374021000; // 13 July 2013, 19:30
  int ret = TAI_CONTINUE(int, app_start_ref, t);
  if (!offset) {
    offset = ret - desiredTime;
  }
  if (t != NULL)
    *t = ret - offset;
  return ret - offset;
}

void _start() __attribute__ ((weak, alias ("module_start")));
int module_start(SceSize argc, const void *args) {
  gHook = taiHookFunctionExport(
    &app_start_ref,
    "SceLibc",
    0xBE43BB07, // SceLibc
    0xDAE8D60F, // time
    &fakeSystemDateTime
  );

  printf("[MikuAR] gHook post = %08x\n", gHook);

  return SCE_KERNEL_START_SUCCESS;
}

int module_stop(SceSize argc, const void *args){
  printf("[MikuAR] module_stop\n");
  if(gHook >= 0) {
    printf("[MikuAR] taiHookRelease(gHook, app_start_ref)\n");
    taiHookRelease(gHook, app_start_ref);
  }
  return SCE_KERNEL_STOP_SUCCESS;
}