/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 Code version 21w20a (2021-5-26)

 Annotation:BGMº∞“Ù–ß
 ****************************************************************************/
#include "BGM.h"


BGM::BGM()
{
	_audioIDBGM = AudioEngine::INVALID_AUDIO_ID;
	_audioIDSE = AudioEngine::INVALID_AUDIO_ID;
	_ifonBGM = true;
	_ifonSE = true;
}

int BGM::play2dBGM(const std::string& filePath, bool loop )
{
	if (true == _ifonBGM)
		return AudioEngine::play2d(filePath, loop);
	else
		return AudioEngine::INVALID_AUDIO_ID;
}

int BGM::play2dSE(const std::string& filePath, bool loop )
{
	if (true == _ifonSE)
		return AudioEngine::play2d(filePath, loop);
	else
		return AudioEngine::INVALID_AUDIO_ID;
}

void BGM::stopBGM()
{
	if (true == _ifonBGM)
		AudioEngine::stop(_audioIDBGM);
}

void  BGM::stopSE()
{
	if (true == _ifonSE)
		AudioEngine::stop(_audioIDSE);
}