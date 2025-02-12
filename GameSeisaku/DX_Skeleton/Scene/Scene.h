#pragma once

class Input;
class SceneController;

/// <summary>
///  �e�V�[���̊��N���X
/// </summary>
class Scene
{
protected:
	// �e��Ԃ��؂�ւ��邽�߂�
	SceneController& controller_;

public:
	Scene(SceneController& cont);

	/// <summary>
	/// �����ϐ��̍X�V
	/// </summary>
	/// <param name="input">���͏��</param>
	virtual void Update(Input& input) = 0;

	/// <summary>
	///  �`��
	/// </summary>
	virtual void Draw() = 0;
};

