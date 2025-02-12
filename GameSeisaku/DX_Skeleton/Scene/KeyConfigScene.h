#pragma once
#include "Scene.h"
#include <string>
#include <vector>
#include <map>

class Input;

/// <summary>
/// �L�[�����
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

	// �o�����
	void AppearUpdate(Input& input);
	// �m�[�}�����
	void NomalUpdate(Input& input);
	// �ҏW�����
	void EdittintUpdate(Input& input);
	// ���Œ����
	void DisappearUpdate(Input& input);

	// �ʏ�`��
	void NomalDraw();
	// �r���`��
	void ShiftingDraw();
	/// <summary>
	/// Input�̏���\��
	/// </summary>
	void DrawInputInfo();

	void DrawStringWithShadow(int x, int y, const char* str, uint32_t color);

	void Close();
	using MenuFunc_t = void (KeyConfigScene::*) (Input&);
	void CloseKeyConfig(Input& input);
	void CommitAndClose(Input& input);
	void CancelEdit(Input& input);
	void SetDefault(Input& input);

	std::map<std::string, MenuFunc_t> menuFuncTable_;	// ���j���[�ɑΉ������֐��e�[�u��
	std::vector<std::string> menuString_;
public:
	KeyConfigScene(SceneController& cont, Input& input);

	virtual void Update(Input& input) override;
	virtual void Draw() override;
};

