#include "SceneController.h"
#include <memory>
// �p�����̊֐����F�����Ă����̂�
// �܂��w�b�_�̓��e�����̂܂ܕt�������Ă��邾������
// �p������������
#include "TitleScene.h"
#include <cassert>

SceneController::SceneController()
{
	// ��ԍŏ��̃V�[�������͊��蓖�Ă�
	// �������g�̃C���X�^���X��n���Ă�����
	ChangeScene(std::make_shared<TitleScene>(*this));
}

void SceneController::Update(Input& input)
{
	// ��ԏ�ɂ�������Update
	scenes_.back()->Update(input);
}

void SceneController::Draw()
{
	for (auto& scene : scenes_)
	{
		scene->Draw();
	}
}

void SceneController::ChangeScene(std::shared_ptr<Scene> scene)
{
	// �X�}�|�Ȃ̂ł���ŃI�b�P�[
	// ��ԏ��Ȃ�
	if (scenes_.empty())
	{
		scenes_.push_back(scene);
	}
	// ��q�������ꍇ�A�ǂ��Ă��炤
	else
	{
		// �����̗v�f�̎Q�Ƃ��̂��̂�
		scenes_.back() = scene;
	}
	// ���O�̃I�u�W�F�N�g�͎Q�Ƃ������̂ŏ��������
}

void SceneController::ChangeBaseScene(std::shared_ptr<Scene> scene)
{
	assert(!scenes_.empty());
	scenes_.front() = scene;
}

void SceneController::PushScene(std::shared_ptr<Scene> scene)
{
	scenes_.push_back(scene);
}

void SceneController::PopScene()
{
	// ���s���ׂ��V�[�����Ȃ��Ȃ�̂ŋ����Ȃ�
	if (scenes_.size() == 1) return;

	// ��������菜��
	scenes_.pop_back();
}
