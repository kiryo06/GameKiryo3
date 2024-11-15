#pragma once
class Input;
class SceneManager;
/// <summary>
/// �V�[�����N���X
/// �F��ȃV�[���̂��ƂɂȂ�N���X
/// </summary>
class Scene
{
protected:
	SceneManager& manager_;
public:
	/// <summary>
	/// ��������SceneManager�̎Q�Ƃ��󂯎���Ă���
	/// </summary>
	/// <param name="manager">SceneManager�̎Q��</param>
	Scene(SceneManager& manager);

	/// <summary>
	/// �V�[���̍X�V
	/// </summary>
	/// <param name="input">���̓I�u�W�F�N�g</param>
	virtual void Update(Input& input) = 0;

	/// <summary>
	/// �V�[���̕`��
	/// </summary>
	virtual void Draw() = 0;
};

