#include"Planet.h"
#include"Node.h"
#include"Urban.h"
#include"BiomeData.h"
#include"Incident.h"
#include"Scuttle.h"
#include"Group.h"
#include"Nation.h"
#include"UI.h"
#include"Route.h"
#include<thread>
#include"Data.h"

bool	selectMap()
{
	std::thread thread(initNodes);
	loadData();

	auto items = FileSystem::DirectoryContents(L"assets/map/").filter([](const FilePath& _path) {
		return FileSystem::IsDirectory(_path) && FileSystem::Exists(_path + L"BiomeData.bin");
	});

	for (;;)
	{
		(*ui.fonts[32])(L"�g�p����}�b�v��I�����Ă�������").draw();
		for (int i = 0; i < int(items.size()); i++)
		{
			Rect rect(0, 48 + i * 48, Window::Size().x, 48);
			rect.draw(rect.mouseOver() ? ColorF(Palette::White, 0.5) : Color(0, 0)).drawFrame(2, 0, Palette::White);
			(*ui.fonts[32])(FileSystem::BaseName(items[i])).draw(0, 48 + i * 48);
			if (rect.leftClicked())
			{
				thread.join();
				loadMap(items[i]);
				return true;
			}
		}
		if (!System::Update()) break;
	}
	thread.join();
	return false;
}
void	loadMap(const FilePath& _path)
{
	//MapImage�̍쐬or�ǂݍ���
	auto mapImageFunc = [&_path]() {
		{
			if (FileSystem::Exists(_path + L"MapImage.png"))
			{
				planet.mapTexture = Texture(_path + L"MapImage.png");
			}
			else
			{
				//VoronoiMap�̓ǂݍ���
				Image image(L"assets/nodeMap/voronoiMap.png");
				auto size = image.size();

				for (auto p : step(size))
				{
					auto& n = nodes.at(image[p.y][p.x].r + (image[p.y][p.x].g << 8) + (image[p.y][p.x].b << 16));

					image[p.y][p.x] = n.color;
				}

				//mapTexture�ɓK�p
				planet.mapTexture = Texture(image);
			}
		}
	};
	std::thread thread(mapImageFunc);

	//Planet�f�[�^�̃��[�h
	{
		JSONReader reader(_path + L"Planet.json");
		auto j = reader[L"StartTime"];

		//���Ԑݒ�
		planet.sandglass.set(j[L"Year"].getOr<int>(0), j[L"Month"].getOr<int>(1), j[L"Day"].getOr<int>(1));
	}

	//�o�C�I�[���f�[�^�̃��[�h
	{
		BinaryReader reader(_path + L"BiomeData.bin");

		for (auto& n : nodes)
		{
			reader.read(n.biomeType);

			//Node�ɐF�̓K�p
			n.color = n.data().color.lerp(RandomColor(), 0.05);
		}
	}

	//Urbans�f�[�^�̃��[�h
	if (FileSystem::Exists(_path + L"Urbans.json"))
	{
		JSONReader reader(_path + L"Urbans.json");

		for (auto json : reader.arrayView())
			urbans.emplace_back(json);

		for (auto& u : urbans)
			for (auto& b : u.shelves)
				b.joinedUrban = &u;
	}
	initRoutes();


	//Incidents�f�[�^�̃��[�h
	if (FileSystem::Exists(_path + L"Incidents.json"))
	{
		incidentsJson = JSONReader(_path + L"Incidents.json");
		for (auto json : incidentsJson.arrayView())
			incidents.emplace_back(json);
	}

	//Groups�f�[�^�̃��[�h
	if (FileSystem::Exists(_path + L"Groups.json"))
	{
		auto json = JSONReader(_path + L"Groups.json");

		for (auto j : json.arrayView())
			groups.emplace_back(j);
	}

	//Nations�f�[�^�̃��[�h
	if (FileSystem::Exists(_path + L"Nations.json"))
	{
		auto json = JSONReader(_path + L"Nations.json");

		for (auto j : json.arrayView())
			nations.emplace_back(j);
		for (auto& n : nations)
		{
			for (auto& u : n.ownUrbans) u->joinedNation = &n;
		}
	}

	thread.join();	//mapImage�p
}