/****************************************************************************
 Copyright (c) 2021 Final-Knight- Group.

 Code version 21w20a (2021-5-26)

 Annotation:BGMº∞“Ù–ß£®SE£©
 ****************************************************************************/
#pragma once

#ifndef __BGM_H__
#define __BGM_H__
#include "cocos2d.h"
#include "audio/include/AudioEngine.h"

static class BGM :public cocos2d::AudioEngine
{
private:
	static bool _ifonBGM;
public:
	int _audioID;

	BGM();
	int GetIfon();

	virtual int play2d(const std::string& filePath, bool loop = true);

	void Change();
}bgm;

static class SE :public BGM
{
private:
	static bool _ifonSE;
public:
	int _audioID;

	int GetIfon();

	virtual int play2d(const std::string& filePath, bool loop = false);

	void Change();
}se;

#endif  __BGM_H_H__