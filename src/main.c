#include <psp2/kernel/clib.h>
#include <psp2/kernel/modulemgr.h>
#include <psp2/rtc.h> 

// #include <time.h>

#include <taihen.h>

#define printf sceClibPrintf

// handle to our hook
static tai_hook_ref_t app_start_ref;
// our hook for app entry

SceUID gHook = -1;


int fakeSystemDateTime() {
  printf("[MikuAR] Hooked! Faking date...\n");
  return TAI_CONTINUE(int, app_start_ref);
}



void _start() __attribute__ ((weak, alias ("module_start")));
int module_start(SceSize argc, const void *args) {
  printf("[MikuAR] module_start - gHook = %d\n", gHook);
  gHook = taiHookFunctionImport(
    &app_start_ref,
    "SegaMiku",
    // TAI_ANY_LIBRARY,
    0x3503487E, // SceRtc
    0x41A6C861, // _sceRtcGetCurrentClockLocalTime
    &fakeSystemDateTime
  );
  printf("[MikuAR] gHook post = %d\n", gHook);
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