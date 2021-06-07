/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 Code version 21w20a (2021-5-26)

 Annotation:BGMº∞“Ù–ß
 ****************************************************************************/
#pragma once

#ifndef __BGM_H__
#define __BGM_H__
#include "cocos2d.h"
#include "audio/include/AudioEngine.h"

class BGM :public cocos2d::AudioEngine
{
private:
	bool _ifonBGM;
	bool _ifonSE;
public:
	int _audioIDBGM;
	int _audioIDSE;

	BGM();

	int play2dBGM(const std::string& filePath, bool loop = true);

	int play2dSE(const std::string& filePath, bool loop = false);

	void stopBGM();

	void stopSE();
};

#endif  __BGM_H_H__