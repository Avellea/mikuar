// our own plugin entry
// int module_start(SceSize argc, const void *args) {
//   taiHookFunctionExport(&app_start_ref,  // Output a reference
//                         TAI_MAIN_MODULE,       // Name of module being hooked
//                         TAI_ANY_LIBRARY, // If there's multiple libs exporting this
//                         0x935CD196,      // Special NID specifying module_start
//                         hook_app_start); // Name of the hook function
//   return SCE_KERNEL_START_SUCCESS;
// }

  // time_s.year   = 2013;
  // time_s.month  = 6;
  // time_s.day    = 16;
  // time_s.hour   = 19;
  // time_s.minute = 30;
  // time_s.second = 0;
  

// int hook_app_start(SceSize argc, const void *args) {
//   printf("[MikuAR] hook_app_start\n");
//   return TAI_CONTINUE(int, app_start_ref, argc, args);
// }  