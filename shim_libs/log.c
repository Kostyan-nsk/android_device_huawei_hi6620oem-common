#include <sys/types.h>

int __android_log_exception_write(void)
{
	return 0;
}

int __android_log_exception_msg_write(void)
{
	return 0;
}

int __android_logPower_print(void)
{
	return 0;
}

int __android_janklog_print(void) {
	return 0;
}


/*
int _ZN7android17MediaLogException11writeLogMsgEiiPKcz(void) {
	return 0;
}

// size_t ICameraRecordingProxy::getCommonBaseAddress()
size_t _ZN7android21ICameraRecordingProxy20getCommonBaseAddressEv() {
    return 0;
}
*/
//void _ZN7android15MediaLogService21CreateMediaLogProcessEv(void) {}