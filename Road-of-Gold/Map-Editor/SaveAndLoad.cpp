#include"Node.h"
#include"Planet.h"
#include"BiomeData.h"
#include"EnergyData.h"
#include"Urban.h"
#include"GlobalVariables.h"
#include"River.h"


bool loadMapData(const FilePath& _path)
{
	if (!FileSystem::IsDirectory(_path)) return false;

	urbans.clear();
	rivers.clear();

	//�o�C�I�[���f�[�^�̃��[�h
	if (FileSystem::Exists(_path + U"BiomeData.bin"))
	{
		Array<Node*> list;
		BinaryReader reader(_path + U"BiomeData.bin");
		for (auto& n : nodes)
		{
			reader.read(n.biomeType);
			if (n.biomeType >= int(biomeData.size())) return false;
			list.emplace_back(&n);
		}
		planet.updateImage(list);
	}
	else return false;

	//Urbans�f�[�^�̃��[�h
	if (FileSystem::Exists(_path + U"Urbans.json"))
	{
		JSONReader reader(_path + U"Urbans.json");
		for (auto json : reader.arrayView())
			urbans.emplace_back(json);
	}

	//Rivers�f�[�^�̃��[�h
	if (FileSystem::Exists(_path + U"Rivers.json"))
	{
		JSONReader reader(_path + U"Rivers.json");
		for (auto json : reader.arrayView())
			rivers.emplace_back(json);
	}
	

	textBox.setText(FileSystem::BaseName(_path));

	return true;
}
bool saveMapData(const FilePath& _path)
{
	//�o�C�I�[���f�[�^�̃Z�[�u
	{
		BinaryWriter writer(_path + U"BiomeData.bin");
		for (auto& n : nodes) writer.write(n.biomeType);
	}

	//�}�b�v��png�ɂ��ĕۑ�
	{
		planet.image.save(_path + U"MapImage.png");
	}

	//Urbans�f�[�^�̃Z�[�u
	if (!urbans.isEmpty())
	{
		String text(U"[");

		for (auto i : step(int(urbans.size())))
		{
			auto& u = urbans[i];

			if (i == 0) text += U"\r\t{";
			else text += U",\r\t{";

			//�s�s���W�̕ۑ�
			text += Format(U"\r\t\t\"JoinedNodeID\": ", u.joinedNodeID);

			//�s�s���̕ۑ�
			text += Format(U",\r\t\t\"Name\": \"", u.name, U"\"");

			//�l���̕ۑ�
			text += Format(U",\r\t\t\"NumCitizens\": ", u.numCitizens);

			//���Y���̕ۑ�
			//text += Format(U",\r\t\t\t\"Productivity\": ", u.productivity);

			//Resources�f�[�^�̕ۑ�
			text += U",\r\t\t\"Energies\": {";
			bool isFirst = true;
			for (auto j : step(energyData.size()))
			{
				if (u.energies[j] > 0)
				{
					if (isFirst) { text += U"\r\t\t\t\""; isFirst = false; }
					else text += U",\r\t\t\t\"";
					text += Format(energyData[j].name, U"\": ", u.energies[j]);
				}
			}
			text += U"\r\t\t}";

			text += U"\r\t}";
		}
		text += U"\r]";
		TextWriter writer(_path + U"Urbans.json");
		writer.write(text);
		writer.close();
	}

	//Rivers�f�[�^�̃Z�[�u
	{
		String text(U"[");
		for (auto i : step(int(rivers.size())))
		{
			auto& r = rivers[i];
			if (i == 0) text += U"\r\t{";
			else text += U",\r\t{";

			text += Format(U"\r\t\t\"Width\": ", r.width);

			text += U",\r\t\t\"Paths\": [";
			text += Format(r.riverPaths.front()->parentNodeID);
			for (auto* p : r.riverPaths)
			{
				text += U",";
				text += Format(p->childNodeID);
			}

			text += U"]";

			text += U"\r\t}";
		}
		text += U"\r]";
		TextWriter writer(_path + U"Rivers.json");
		writer.write(text);
		writer.close();
	}
	return true;
}