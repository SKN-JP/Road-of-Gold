#include"Node.h"

void	initNodes()
{
	//Node�̓ǂݍ���
	BinaryReader reader(U"assets/nodeMap/nodeMap.bin");
	if (!reader)
	{
		Logger << U"assets/nodeMap/nodeMap.bin�̓ǂݍ��݂Ɏ��s";
		System::Exit();
		return;
	}

	int	nodesSize, pathsSize;

	//Node�̈ʒu�̓ǂݍ���
	reader.read(nodesSize);
	nodes.reserve(nodesSize);
	for (int i = 0; i < nodesSize; ++i)
	{
		Vec3 ePos;
		reader.read(ePos);
		nodes.emplace_back(ePos);
	}

	//Path�̊֌W�̓ǂݍ���
	reader.read(pathsSize);
	for (int i = 0; i < pathsSize; ++i)
	{
		int parentNodeID;
		int childNodeID;
		reader.read(parentNodeID);
		reader.read(childNodeID);

		if (parentNodeID < 0 || parentNodeID >= nodesSize || childNodeID < 0 || childNodeID >= nodesSize)
		{
			Logger << U"NodeMap.bin����ُ�Ȑ��l�����o";
			System::Exit();
			return;
		}

		nodes[parentNodeID].paths.emplace_back(childNodeID);
	}

	//Length�̓K�p
	for (auto& n : nodes)
	{
		for (auto& p : n.paths)
		{
			p.length = nodes[p.toID].pos.distanceFrom(n.pos);
		}
	}
	Logger << U"nodes�����paths�̓ǂݍ��݊���";
	Logger << U"��Node��:" << nodes.size();
}