#include <psp2/kernel/clib.h>
#include <psp2/kernel/modulemgr.h>
#include <psp2/rtc.h>
#include <psp2/apputil.h>

#include <taihen.h>

#define printf sceClibPrintf
#define SCE_SYSTEM_PARAM_ID_TIME_ZONE 6


static tai_hook_ref_t app_start_ref;

SceUID gHook = -1;

static int saved_now = 0;
static int tzoffset = 0;
//static int desiredTime = 1374091200; // Wed Jul 17 2013 20:00:00 GMT+0000
static int desiredTime = 1374003000; // Wed Jul 17 2013 20:00:00 GMT+0000

int fakeSystemDateTime(int *t) {
  int ret = TAI_CONTINUE(int, app_start_ref, t);
  if (saved_now == 0) {
    saved_now = ret;
    printf("now: %d\n", ret);
    printf("set saved_now\n");
    printf("returning: %d\n", desiredTime + (ret - saved_now));
  }
  if (t != NULL)
    *t = desiredTime + (ret - saved_now) - tzoffset;
  return desiredTime + (ret - saved_now) - tzoffset;
}

void _start() __attribute__ ((weak, alias ("module_start")));
int module_start(SceSize argc, const void *args) {

  SceAppUtilInitParam init;
  SceAppUtilBootParam boot;
  sceClibMemset(&init, 0, sizeof(SceAppUtilInitParam));
  sceClibMemset(&boot, 0, sizeof(SceAppUtilBootParam));

  SceInt ret = 0;
  ret = sceAppUtilInit(&init, &boot);
  printf("ret: 0x%08x\n", ret);

  SceInt tzoffset_minutes = 0;

  sceAppUtilSystemParamGetInt(SCE_SYSTEM_PARAM_ID_TIME_ZONE, &tzoffset_minutes);
  printf("tzoffset_minutes: %d\n", tzoffset_minutes);

  tzoffset = tzoffset_minutes * 60;

  ret = sceAppUtilShutdown();
  printf("ret: 0x%08x\n", ret);

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