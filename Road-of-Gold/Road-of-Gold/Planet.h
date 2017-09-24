#pragma once

#include"TinyCamera.h"
#include"Sandglass.h"

struct lua_State;

struct Planet
{
	Sandglass	sandglass;
	Texture		mapTexture;
	double		timeSpeed;
	lua_State*	incidentsLua;	//�C�x���g�����plua
	Array<Audio>	audios;
	FilePath	mapPath;
	Audio		bgm;

	Planet();
};

extern Planet	planet;

void	loadMap(const FilePath& _path);
bool	selectMap();
void	updatePlanet();
void	drawPlanet();