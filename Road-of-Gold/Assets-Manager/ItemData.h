#pragma once
#include"united.h"
#include"ColorPalette.h"

struct ItemData
{
	Font	textBoxFont = Font(16);
	TextBox	nameTextBox;
	TextBox	volumeTextBox;
	TextBox	valueTextBox;
	TextBox iconTextBox;
	TextBox colorTextBox;
	ColorPalette	colorPalette;
	Image	iconImage;
	Texture	iconTexture;

	ItemData(JSONValue _j)
		: nameTextBox(textBoxFont, Vec2(288, 24), 120, unspecified, _j[U"Name"].getString())
		, volumeTextBox(textBoxFont, Vec2(288, 24 * 3), 120, unspecified, Format(_j[U"Volume"].get<int>()))
		, valueTextBox(textBoxFont, Vec2(288, 24 * 5), 120, unspecified, Format(_j[U"Value"].get<int>()))
		, iconTextBox(textBoxFont, Vec2(288, 24 * 7), 360, unspecified, _j[U"Icon"].getString())
		, colorTextBox(textBoxFont, Vec2(288, 24 * 9), 120, unspecified, _j[U"Color"].getString())
		, iconImage(_j[U"Icon"].getString())
		, iconTexture(iconImage)
		, colorPalette(720, 120)
	{}
	ItemData()
		: nameTextBox(textBoxFont, Vec2(288, 24), 120, unspecified, U"newItem")
		, volumeTextBox(textBoxFont, Vec2(288, 24 * 3), 120, unspecified, U"1")
		, valueTextBox(textBoxFont, Vec2(288, 24 * 5), 120, unspecified, U"0")
		, iconTextBox(textBoxFont, Vec2(288, 24 * 7), 360, unspecified)
		, colorTextBox(textBoxFont, Vec2(288, 24 * 9), 120, unspecified, U"#FF0000")
		, colorPalette(720, 120)
	{}
	String	name() const { return nameTextBox.getText(); }
};

Array<ItemData>	itemData;

bool	itemIsExist(const String& _itemName)
{
	return itemData.any([&_itemName](const ItemData& i) { return i.name() == _itemName; });
}
struct SetItemData : MyApp::Scene
{
	Font	font16 = Font(16);


	SetItemData(const InitData& init)
		: IScene(init)
	{}

	void update() override
	{
		//左メニュー
		for (int i = 0; i < int(itemList.size()); i++)
		{
			Rect rect(0, i * 24, 24 * 6, 24);
			if (rect.mouseOver()) rect.draw(Palette::Orange);
			if (i == 0) rect.draw(Palette::Red);
			if (rect.leftClicked())
			{
				getData().selectedSceneID = i;
				changeScene(itemList[i], 0ms, false);
			}
			rect.drawFrame(2);
			font16(itemList[i]).draw(rect.movedBy(4, 0));
		}

		//左メニューキー操作
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

		//既存のアイテム
		for (int i = 0; i < int(itemData.size()); i++)
		{
			Rect rect(24 * 6, i * 24, 24 * 5, 24);

			if (rect.mouseOver()) rect.draw(Palette::Orange);
			if (rect.leftClicked()) getData().selectedItemType = i;
			if (i == getData().selectedItemType) rect.draw(Palette::Red);
			rect.drawFrame(2);

			if (i < int(itemData.size())) font16(itemData[i].name()).draw(rect.movedBy(4, 0));
		}

		//新アイテム追加
		{
			Rect rect(144, int(itemData.size()) * 24, 24 * 5, 24);

			rect.draw(Palette::Gray);
			if (rect.mouseOver()) rect.draw(Palette::Orange);
			if (rect.leftClicked())
			{
				getData().selectedItemType = int(itemData.size());
				itemData.emplace_back();
			}
			rect.drawFrame(2);

			font16(U"新アイテム追加").draw(rect.movedBy(4, 0));
		}

		if (itemData.isEmpty()) return;

		//上下キー対応
		{
			if (KeyUp.down() && getData().selectedItemType > 0) --getData().selectedItemType;
			if (KeyDown.down() && getData().selectedItemType < int(itemData.size() - 1)) ++getData().selectedItemType;
		}

		//Tabキー対応
		if (KeyTab.down())
		{
			auto& i = itemData[getData().selectedItemType];
			if (i.nameTextBox.isActive())
			{
				i.nameTextBox.setActive(false);
				i.volumeTextBox.setActive(true);
			}
			else if (i.volumeTextBox.isActive())
			{
				i.volumeTextBox.setActive(false);
				i.valueTextBox.setActive(true);
			}
			else if (i.valueTextBox.isActive())
			{
				i.valueTextBox.setActive(false);
				i.iconTextBox.setActive(true);
			}
			else if (i.iconTextBox.isActive())
			{
				i.iconTextBox.setActive(false);
				i.colorTextBox.setActive(true);
			}
			else if (i.colorTextBox.isActive())
			{
				i.colorTextBox.setActive(false);
				i.nameTextBox.setActive(true);
			}
			else i.nameTextBox.setActive(true);
		}

		//クリップボード
		if (KeyControl.pressed() && KeyV.down())
		{
			auto& i = itemData[getData().selectedItemType];
			String string;

			Clipboard::GetText(string);
			if (string)
			{
				if (i.nameTextBox.isActive()) i.nameTextBox.setText(string);
				if (i.volumeTextBox.isActive()) i.volumeTextBox.setText(string);
				if (i.valueTextBox.isActive()) i.valueTextBox.setText(string);
				if (i.iconTextBox.isActive()) i.iconTextBox.setText(string);
				if (i.colorTextBox.isActive()) i.colorTextBox.setText(string);
			}
		}

		//アイテムの更新＆描画
		{
			auto& i = itemData[getData().selectedItemType];

			font16(U"アイテム名").drawAt(348, 12);
			i.nameTextBox.update();
			i.nameTextBox.draw();

			font16(U"アイテム容量").drawAt(348, 60);
			i.volumeTextBox.update();
			i.volumeTextBox.draw();
			i.volumeTextBox.setText(Format(ParseInt<int32>(i.volumeTextBox.getText(), Arg::radix = 10)));

			font16(U"アイテム価値").drawAt(348, 108);
			i.valueTextBox.update();
			i.valueTextBox.draw();
			i.valueTextBox.setText(Format(ParseInt<int32>(i.valueTextBox.getText(), Arg::radix = 10)));

			font16(U"アイコンファイル").drawAt(348, 156);
			auto beforeFilePath = i.iconTextBox.getText();
			i.iconTextBox.update();
			i.iconTextBox.draw();
			if (DragDrop::HasNewFilePaths()) i.iconTextBox.setText(DragDrop::GetDroppedFilePaths().front().path);
			if (beforeFilePath != i.iconTextBox.getText())
			{
				i.iconImage = Image(i.iconTextBox.getText());
				i.iconTexture = Texture(i.iconImage);
			}
			Rect(432, 24, 128, 128).draw(DragDrop::DragOver() ? Palette::Gray : Color(0, 0)).drawFrame(4, Color(i.colorTextBox.getText()));
			if (i.iconTexture) i.iconTexture.resized(128, 128).draw(432, 24);

			font16(U"アイテムカラー").drawAt(348, 204);
			i.colorTextBox.update();
			i.colorTextBox.draw();

		}

		//ColorPalette
		{
			auto& i = itemData[getData().selectedItemType];
			if (i.colorPalette.update()) i.colorTextBox.setText(U"#" + i.colorPalette.color().toHex());
			i.colorPalette.draw();
		}

		{
			Rect rect(720, 72, 120, 24);
			if (rect.mouseOver()) rect.draw(Palette::Orange);
			if (rect.leftClicked())
			{
				itemData.erase(itemData.begin() + getData().selectedItemType);
				if (getData().selectedItemType == int(itemData.size()) && getData().selectedItemType > 0) getData().selectedItemType--;
			}
			rect.drawFrame(2);
			font16(U"項目の削除").drawAt(rect.center());
		}


	}
};