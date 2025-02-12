#pragma once
#include "Scene.h"
#include <string>
#include <vector>
#include <map>

class Input;

/// <summary>
/// キー婚画面
/// </summary>
class KeyConfigScene : public Scene
{
private:
	Input& input_;
	int frame_ = 0;
	unsigned int currentSelectorIndex_ = 0;

	using UpdateFunc_t = void (KeyConfigScene::*)(Input& input);
	using DrawFunc_t = void (KeyConfigScene::*)();

	UpdateFunc_t update_;
	DrawFunc_t draw_;

	std::map<int, std::string> keyNameTable_;
	std::map<int, std::string> padNameTable_;

	// 出現状態
	void AppearUpdate(Input& input);
	// ノーマル状態
	void NomalUpdate(Input& input);
	// 編集中状態
	void EdittintUpdate(Input& input);
	// 消滅中状態
	void DisappearUpdate(Input& input);

	// 通常描画
	void NomalDraw();
	// 途中描画
	void ShiftingDraw();
	/// <summary>
	/// Inputの情報を表示
	/// </summary>
	void DrawInputInfo();

	void DrawStringWithShadow(int x, int y, const char* str, uint32_t color);

	void Close();
	using MenuFunc_t = void (KeyConfigScene::*) (Input&);
	void CloseKeyConfig(Input& input);
	void CommitAndClose(Input& input);
	void CancelEdit(Input& input);
	void SetDefault(Input& input);

	std::map<std::string, MenuFunc_t> menuFuncTable_;	// メニューに対応した関数テーブル
	std::vector<std::string> menuString_;
public:
	KeyConfigScene(SceneController& cont, Input& input);

	virtual void Update(Input& input) override;
	virtual void Draw() override;
};

