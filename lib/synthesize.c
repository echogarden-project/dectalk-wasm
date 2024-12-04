#include "ttsapi.h"

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

#define PROGRAM_NAME "DECTalk"

LPTTS_HANDLE_T ttsHandle;
DWORD devEncoding[3] = {
	WAVE_FORMAT_1M16,
	WAVE_FORMAT_1M08,
	WAVE_FORMAT_08M08
};

int synthesize(char* text, char* outFilePath, int voice, int rate)
{
	ttsHandle = NULL;
	unsigned int devNo = WAVE_MAPPER;
	int status;
	DWORD devOptions = DO_NOT_USE_AUDIO_DEVICE;
	DWORD encoding = 0;

	status = TextToSpeechStartup(&ttsHandle, devNo, devOptions, NULL, (long)NULL);

	switch (status)
	{
		case MMSYSERR_NODRIVER:
			fprintf(stderr, PROGRAM_NAME ": Could not find any wave devices\n");
			fprintf(stderr, PROGRAM_NAME ": Is the MM server ready? \n");
			fprintf(stderr, PROGRAM_NAME ": Exiting\n");
			return 1;

		case MMSYSERR_NOTENABLED:
			fprintf(stderr, PROGRAM_NAME ": DECtalk licence not found.\n");
			fprintf(stderr, PROGRAM_NAME ": Exiting\n");
			return 1;

		case MMSYSERR_ALLOCATED:
			fprintf(stderr, PROGRAM_NAME ": DECtalk has exceeded licence quota.\n");
			fprintf(stderr, PROGRAM_NAME ": Exiting\n");
			return 1;

		case MMSYSERR_NOMEM:
			fprintf(stderr, PROGRAM_NAME ": DECtalk has ran out of memory.\n");
			return 1;

		case MMSYSERR_NOERROR:
			break;

		default:
			fprintf(stderr, PROGRAM_NAME ": TextToSpeechStartup failed with code %d, exiting.\n", status);
			return -1;
	}

	//fprintf(stderr, PROGRAM_NAME ": Opening up '%s' for writing...\n", outFilePath);
	TextToSpeechOpenWaveOutFile(ttsHandle, outFilePath, devEncoding[encoding]);

	TextToSpeechSetSpeaker(ttsHandle, voice);

	TextToSpeechSetRate(ttsHandle, rate);

	//fprintf(stderr, PROGRAM_NAME ": About to speak...\n");
	TextToSpeechSpeak(ttsHandle, text, TTS_FORCE);

	//fprintf(stderr, PROGRAM_NAME ": Waiting for synchronisation...\n");
	TextToSpeechSync(ttsHandle);

	//fprintf(stderr, PROGRAM_NAME ": Closing file.\n");
	TextToSpeechCloseWaveOutFile(ttsHandle);

	if (TextToSpeechShutdown(ttsHandle) != MMSYSERR_NOERROR) {
		fprintf(stderr, PROGRAM_NAME ": TextToSpeechShutdown failed.\n");
		return -1;
	}

	//fprintf(stderr, PROGRAM_NAME ": Thanks for using DECtalk!\n");

	return 0;
}