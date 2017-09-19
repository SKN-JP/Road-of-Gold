#pragma once
#include"united.h"

struct EnergyData
{
	Font	textBoxFont = Font(16);
	TextBox	nameTextBox;
	TextBox iconTextBox;
	Image	iconImage;
	Texture	iconTexture;

	EnergyData(JSONValue _j)
		: nameTextBox(textBoxFont, 288, 24, 120, _j[L"Name"].getString())
		, iconTextBox(textBoxFont, 288, 24 * 7, 360, _j[L"Icon"].getString())
		, iconImage(_j[L"Icon"].getString())
		, iconTexture(iconImage)
	{}
	EnergyData()
		: nameTextBox(textBoxFont, 288, 24, 120, L"newItem")
		, iconTextBox(textBoxFont, 288, 24 * 7, 360)
	{}
	String	name() const { return nameTextBox.getText(); }
};

Array<EnergyData>	energyData;

bool	energyIsExist(const String& _energyName)
{
	return energyData.any([&_energyName](const EnergyData& i) { return i.name() == _energyName; });
}
struct SetEnergyData : MyApp::Scene
{
	Font	font16 = Font(16);


	SetEnergyData(const InitData& init)
		: IScene(init)
	{}

	void update() override
	{
		//�����j���[
		for (int i = 0; i < int(itemList.size()); i++)
		{
			Rect rect(0, i * 24, 24 * 6, 24);
			if (rect.mouseOver()) rect.draw(Palette::Orange);
			if (i == 2) rect.draw(Palette::Red);
			if (rect.leftClicked())
			{
				getData().selectedSceneID = i;
				changeScene(itemList[i], 0ms, false);
			}
			rect.drawFrame(2);
			font16(itemList[i]).draw(rect.movedBy(4, 0));
		}

		//�����j���[�L�[����
		if(false)
		{
			if (KeyW.down() && getData().selectedSceneID > 0)
			{
				getData().selectedSceneID--;
				changeScene(itemList[getData().selectedSceneID], 0ms, false);
			}
			if (KeyS.down() && getData().selectedSceneID < int(itemList.size() - 1))
			{
				getData().selectedSceneID++;
				changeScene(itemList[getData().selectedSceneID], 0ms, false);
			}
		}


		//�����̃A�C�e��
		for (int i = 0; i < int(energyData.size()); i++)
		{
			Rect rect(24 * 6, i * 24, 24 * 5, 24);

			if (rect.mouseOver()) rect.draw(Palette::Orange);
			if (rect.leftClicked()) getData().selectedEnergyType = i;
			if (i == getData().selectedEnergyType) rect.draw(Palette::Red);
			rect.drawFrame(2);

			if (i < int(energyData.size())) font16(energyData[i].name()).draw(rect.movedBy(4, 0));
		}

		//�V�A�C�e���ǉ�
		{
			Rect rect(144, int(energyData.size()) * 24, 24 * 5, 24);

			rect.draw(Palette::Gray);
			if (rect.mouseOver()) rect.draw(Palette::Orange);
			if (rect.leftClicked())
			{
				getData().selectedEnergyType = int(energyData.size());
				energyData.emplace_back();
			}
			rect.drawFrame(2);

			font16(L"�V�����ǉ�").draw(rect.movedBy(4, 0));
		}

		if (energyData.isEmpty()) return;

		//�㉺�L�[�Ή�
		{
			if (KeyUp.down() && getData().selectedEnergyType > 0) --getData().selectedEnergyType;
			if (KeyDown.down() && getData().selectedEnergyType < int(energyData.size() - 1)) ++getData().selectedEnergyType;
		}

		//Tab�L�[�Ή�
		if (KeyTab.down())
		{
			auto& e = energyData[getData().selectedEnergyType];
			if (e.nameTextBox.isActive())
			{
				e.nameTextBox.setActive(false);
				e.iconTextBox.setActive(true);
			}
			else if (e.iconTextBox.isActive())
			{
				e.iconTextBox.setActive(false);
				e.nameTextBox.setActive(true);
			}
			else e.nameTextBox.setActive(true);
		}

		//�A�C�e���̍X�V���`��
		{
			auto& e = energyData[getData().selectedEnergyType];

			font16(L"������").drawAt(348, 12);
			e.nameTextBox.update();
			e.nameTextBox.draw();

			font16(L"�A�C�R���t�@�C��").drawAt(348, 156);
			auto beforeFilePath = e.iconTextBox.getText();
			e.iconTextBox.update();
			e.iconTextBox.draw();
			if (DragDrop::HasNewFilePaths()) e.iconTextBox.setText(DragDrop::GetDroppedFilePaths().front().path);
			if (beforeFilePath != e.iconTextBox.getText())
			{
				e.iconImage = Image(e.iconTextBox.getText());
				e.iconTexture = Texture(e.iconImage);
			}
			Rect(432, 24, 128, 128).draw(DragDrop::DragOver() ? Palette::Gray : Color(0, 0)).drawFrame(4);
			if (e.iconTexture) e.iconTexture.resize(128, 128).draw(432, 24);
		}

		{
			Rect rect(720, 72, 120, 24);
			if (rect.mouseOver()) rect.draw(Palette::Orange);
			if (rect.leftClicked())
			{
				energyData.erase(energyData.begin() + getData().selectedEnergyType);
				if (getData().selectedEnergyType == int(energyData.size()) && getData().selectedEnergyType > 0) getData().selectedEnergyType--;
			}
			rect.drawFrame(2);
			font16(L"���ڂ̍폜").drawAt(rect.center());
		}
	}
};