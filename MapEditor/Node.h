#pragma once
#include "Pos.h"

struct Node;
struct Region;

struct Path
{
	int		id;
	int		parentNodeID;
	int		childNodeID;

	Path(int _parentNodeID, int _childNodeID);
	Node&	getChild() const;
	Node&	getParent() const;
	Line	getLine() const;

};
extern Array<Path*> paths;

struct Node
{
	int		id;
	Pos		pos;
	int		biomeType;
	Array<Path> paths;

	Node(const Pos& _pos);
	Color	getColor() const;
	int		ownUrbanID() const;
};

extern Array<Node> nodes;

bool saveMapData(const FilePath& _path);
bool loadMapData(const FilePath& _path);