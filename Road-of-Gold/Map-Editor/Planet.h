#pragma once
#include "Pos.h"

struct Node;

//���R���̐����ƃ}�b�v��̎��_�ړ����s��
struct Planet
{
	Grid<int>	voronoiMap;
	DynamicTexture mapTexture;
	Texture outlineTexture;
	Texture coverTexture;	//�ォ��ڂ���e�N�X�`��
	Image	image;
	double	coverRate;

	Planet();
	bool	loadVoronoiMap();
	void	updateImage(Array<Node*> _nodeList);
	void	generateBiome();
	void	setCoverImage();
};

extern Planet planet;

extern int		selectedBiome;
extern int		selectedBrush;