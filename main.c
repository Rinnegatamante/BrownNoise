#include <vitasdk.h>
#include <taihen.h>
#include "noise.h"

int noise_thread(SceSize args, void *argp){
	int ch = sceAudioOutOpenPort(SCE_AUDIO_OUT_PORT_TYPE_MAIN, 2048, 48000, SCE_AUDIO_OUT_MODE_STEREO);
	sceAudioOutSetConfig(ch, -1, -1, -1);
	int vol_stereo[] = {328, 328}; // 1% of retail volume
	sceAudioOutSetVolume(ch, SCE_AUDIO_VOLUME_FLAG_L_CH | SCE_AUDIO_VOLUME_FLAG_R_CH, vol_stereo);
	for (;;){
		sceAudioOutOutput(ch, noise);
	}
}

void _start() __attribute__ ((weak, alias ("module_start")));
int module_start(SceSize argc, const void *args) {
	
	// Starting a secondary thread
	SceUID thd_id = sceKernelCreateThread("noise_thread", noise_thread, 0x40, 0x400000, 0, 0, NULL);
	sceKernelStartThread(thd_id, 0, NULL);
	
	return SCE_KERNEL_START_SUCCESS;
}

int module_stop(SceSize argc, const void *args) {
	return SCE_KERNEL_STOP_SUCCESS;	
}