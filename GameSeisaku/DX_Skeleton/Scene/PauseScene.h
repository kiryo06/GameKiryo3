#pragma once
#include "Scene.h"
#include <string>
#include <vector>
#include <map>

/// <summary>
/// �|�[�Y���V�[���N���X
/// </summary>
class PauseScene : public Scene
{
private:
	using UpdateFunc_t = void (PauseScene::*)(Input& input);
	using DrawFunc_t = void (PauseScene::*)();

	UpdateFunc_t update_;
	DrawFunc_t draw_;

	int frame_;
	int currentMenuIndex_;

	// �o�����
	void AppearUpdate(Input& input);
	// �m�[�}�����
	void NomalUpdate(Input& input);
	// ���Œ����
	void DisappearUpdate(Input& input);

	// �ʏ�`��
	void NomalDraw();
	// �r���`��
	void ShiftingDraw();

	/// <summary>
	/// �Q�[���ɖ߂�
	/// </summary>
	void BackGame(Input&);
	/// <summary>
	/// �L�[�R���t�B�O�𗧂��グ��
	/// </summary>
	void GoKeyConfig(Input&);
	/// <summary>
	/// ���̑��ݒ�
	/// </summary>
	void EtcConfig(Input&);
	/// <summary>
	/// �^�C�g���ɖ߂�
	/// </summary>
	void BackTitle(Input&);
	using MenuFunc_t = void (PauseScene::*)(Input&);
	// ���j���[����ׂ邽�߂�vector
	std::vector<std::string> menuTexts_;
	// ���j���[�ƑΉ�����֐����Z�b�g�ɂ����e�[�u��
	std::map<std::string, MenuFunc_t> functionTable_;
	void DrawMenu();

public:
	PauseScene(SceneController& cont);
	/// <summary>
	/// �h���N���X�Ŏ���������
	/// </summary>
	virtual void Update(Input& input) override;

	virtual void Draw() override;
};

