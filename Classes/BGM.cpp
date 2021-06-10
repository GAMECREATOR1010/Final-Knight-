/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 Code version 21w20a (2021-5-26)

 Annotation:BGM����Ч
 ****************************************************************************/
#include "BGM.h"

BGM bgm;
SE se;

BGM::BGM()
{
	_audioID = AudioEngine::INVALID_AUDIO_ID;
}
bool BGM::_ifonBGM = true;
bool SE::_ifonSE = true;



int BGM::play2d(const std::string& filePath, bool loop)
{
	if (true == _ifonBGM)
		return AudioEngine::play2d(filePath, loop);
	else
		return AudioEngine::INVALID_AUDIO_ID;
}


int BGM::getIfon()
{
	return _ifonBGM;
}


void BGM::change()
{
	if (false == _ifonBGM)
	{
		_ifonBGM = true;
	}
	else
	{
		_ifonBGM = false;
	}

}


int SE::play2d(const std::string& filePath, bool loop)
{
	if (true == _ifonSE)
		return AudioEngine::play2d(filePath, loop);
	else
		return AudioEngine::INVALID_AUDIO_ID;
}

int SE::getIfon()
{
	return _ifonSE;
}


void SE::change()
{
	if (false == _ifonSE)
	{
		_ifonSE = true;
	}
	else
	{
		_ifonSE = false;
	}
}