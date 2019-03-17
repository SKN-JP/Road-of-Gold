#pragma once
#include"united.h"

struct VehicleData
{
	Font	textBoxFont = Font(16);
	TextBox	nameTextBox;
	TextBox	speedTextBox;
	TextBox	volumeTextBox;
	TextBox iconTextBox;
	TextBox rangeTextBox;
	TextBox isShipTextBox;
	Image	iconImage;
	Texture	iconTexture;

	VehicleData(JSONValue _j)
		: nameTextBox(textBoxFont, Vec2(288, 24), 120, unspecified, _j[U"Name"].getString())
		, speedTextBox(textBoxFont, Vec2(288, 24 * 3), 120, unspecified, Format(_j[U"Speed"].get<double>()))
		, volumeTextBox(textBoxFont, Vec2(288, 24 * 5), 120, unspecified, Format(_j[U"Volume"].get<int>()))
		, iconTextBox(textBoxFont, Vec2(288, 24 * 7), 360, unspecified, _j[U"Icon"].getString())
		, rangeTextBox(textBoxFont, Vec2(288, 24 * 9), 120, unspecified, Format(_j[U"Range"].get<double>()))
		, isShipTextBox(textBoxFont, Vec2(432, 24 * 9), 120, unspecified, Format(_j[U"IsShip"].get<bool>()))
		, iconImage(_j[U"Icon"].getString())
		, iconTexture(iconImage)
	{}
	VehicleData()
		: nameTextBox(textBoxFont, Vec2(288, 24), 120, unspecified, U"newVehicle")
		, speedTextBox(textBoxFont, Vec2(288, 24 * 3), 120, unspecified, U"1.0")
		, volumeTextBox(textBoxFont, Vec2(288, 24 * 5), 120, unspecified, U"100")
		, iconTextBox(textBoxFont, Vec2(288, 24 * 7), 360, unspecified)
		, rangeTextBox(textBoxFont, Vec2(288, 24 * 9), 120, unspecified, U"10.0")
		, isShipTextBox(textBoxFont, Vec2(432, 24 * 9), 120, unspecified, U"true")
	{}
	String	name() const { return nameTextBox.getText(); }
};

Array<VehicleData>	vehicleData;

struct SetVehicleData : MyApp::Scene
{
	Font	font16 = Font(16);

	SetVehicleData(const InitData& init)
		: IScene(init)
	{}

	void update() override
	{
		//�����j���[
		for (int i = 0; i < int(itemList.size()); i++)
		{
			Rect rect(0, i * 24, 24 * 6, 24);
			if (rect.mouseOver()) rect.draw(Palette::Orange);
			if (i == 3) rect.draw(Palette::Red);
			if (rect.leftClicked())
			{
				getData().selectedSceneID = i;
				changeScene(itemList[i], 0ms, false);
			}
			rect.drawFrame(2);
			font16(itemList[i]).draw(rect.movedBy(4, 0));
		}

		//�����j���[�L�[����
		if (false)
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
		for (int i = 0; i < int(vehicleData.size()); i++)
		{
			Rect rect(24 * 6, i * 24, 24 * 5, 24);

			if (rect.mouseOver()) rect.draw(Palette::Orange);
			if (rect.leftClicked()) getData().selectedVehicleType = i;
			if (i == getData().selectedVehicleType) rect.draw(Palette::Red);
			rect.drawFrame(2);

			if (i < int(vehicleData.size())) font16(vehicleData[i].name()).draw(rect.movedBy(4, 0));
		}

		//�V�A�C�e���ǉ�
		{
			Rect rect(144, int(vehicleData.size()) * 24, 24 * 5, 24);

			rect.draw(Palette::Gray);
			if (rect.mouseOver()) rect.draw(Palette::Orange);
			if (rect.leftClicked())
			{
				getData().selectedVehicleType = int(vehicleData.size());
				vehicleData.emplace_back();
			}
			rect.drawFrame(2);

			font16(U"�V�A�C�e���ǉ�").draw(rect.movedBy(4, 0));
		}

		if (vehicleData.isEmpty()) return;

		//�㉺�L�[�Ή�
		{
			if (KeyUp.down() && getData().selectedVehicleType > 0) --getData().selectedVehicleType;
			if (KeyDown.down() && getData().selectedVehicleType < int(vehicleData.size() - 1)) ++getData().selectedVehicleType;
		}

		//Tab�L�[�Ή�
		if (KeyTab.down())
		{
			auto& v = vehicleData[getData().selectedVehicleType];
			if (v.nameTextBox.isActive())
			{
				v.nameTextBox.setActive(false);
				v.speedTextBox.setActive(true);
			}
			else if (v.speedTextBox.isActive())
			{
				v.speedTextBox.setActive(false);
				v.volumeTextBox.setActive(true);
			}
			else if (v.volumeTextBox.isActive())
			{
				v.volumeTextBox.setActive(false);
				v.iconTextBox.setActive(true);
			}
			else if (v.iconTextBox.isActive())
			{
				v.iconTextBox.setActive(false);
				v.rangeTextBox.setActive(true);
			}
			else if (v.rangeTextBox.isActive())
			{
				v.rangeTextBox.setActive(false);
				v.isShipTextBox.setActive(true);
			}
			else if (v.isShipTextBox.isActive())
			{
				v.isShipTextBox.setActive(false);
				v.nameTextBox.setActive(true);
			}
			else v.nameTextBox.setActive(true);
		}

		//�N���b�v�{�[�h
		if (KeyControl.pressed() && KeyV.down())
		{
			auto& v = vehicleData[getData().selectedVehicleType];
			String string;

			Clipboard::GetText(string);
			if (string)
			{
				if (v.nameTextBox.isActive()) v.nameTextBox.setText(string);
				if (v.speedTextBox.isActive()) v.speedTextBox.setText(string);
				if (v.volumeTextBox.isActive()) v.volumeTextBox.setText(string);
				if (v.iconTextBox.isActive()) v.iconTextBox.setText(string);
				if (v.rangeTextBox.isActive()) v.rangeTextBox.setText(string);
				if (v.isShipTextBox.isActive()) v.isShipTextBox.setText(string);
			}
		}

		//�A�C�e���̍X�V���`��
		{
			auto& v = vehicleData[getData().selectedVehicleType];

			font16(U"���j�b�g��").drawAt(348, 12);
			v.nameTextBox.update();
			v.nameTextBox.draw();

			font16(U"�q�s���x(����)").drawAt(348, 60);
			v.speedTextBox.update();
			v.speedTextBox.draw();

			font16(U"�ύڗe��").drawAt(348, 108);
			v.volumeTextBox.update();
			v.volumeTextBox.draw();
			v.volumeTextBox.setText(Format(ParseInt<int32>(v.volumeTextBox.getText(), Arg::radix = 10)));

			font16(U"�A�C�R���t�@�C��").drawAt(348, 156);
			auto beforeFilePath = v.iconTextBox.getText();
			v.iconTextBox.update();
			v.iconTextBox.draw();
			if (DragDrop::HasNewFilePaths()) v.iconTextBox.setText(DragDrop::GetDroppedFilePaths().front().path);
			if (beforeFilePath != v.iconTextBox.getText())
			{
				v.iconImage = Image(v.iconTextBox.getText());
				v.iconTexture = Texture(v.iconImage);
			}
			Rect(432, 24, 128, 128).draw(DragDrop::DragOver() ? Palette::Gray : Color(0, 0)).drawFrame(4);
			if (v.iconTexture) v.iconTexture.resized(128, 128).draw(432, 24);

			font16(U"�q������(����)").drawAt(348, 204);
			v.rangeTextBox.update();
			v.rangeTextBox.draw();

			font16(U"�D���ǂ���(bool)").drawAt(492, 204);
			v.isShipTextBox.update();
			v.isShipTextBox.draw();

		}

		{
			Rect rect(720, 72, 120, 24);
			if (rect.mouseOver()) rect.draw(Palette::Orange);
			if (rect.leftClicked())
			{
				vehicleData.erase(vehicleData.begin() + getData().selectedVehicleType);
				if (getData().selectedVehicleType == int(vehicleData.size()) && getData().selectedVehicleType > 0) getData().selectedVehicleType--;
			}
			rect.drawFrame(2);
			font16(U"���ڂ̍폜").drawAt(rect.center());
		}
	}
};