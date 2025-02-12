#include "../Application.h"
#include "../Input.h"
#include "DxLib.h"
#include "GameScene.h"
#include "SceneController.h"
#include "TitleScene.h"
#include <cassert>

namespace
{
	// �X�l�[�N�P�[�X�Ƃ́c
	constexpr int fade_interval = 60;
}

void TitleScene::FadeInUpdate(Input&)
{
	--frame_;
	// ���ꂪ�g���K�[��
	if (frame_ <= 0)
	{
		update_ = &TitleScene::NormalUpdate;
		draw_ = &TitleScene::NormalDraw;
	}
}

void TitleScene::FadeOutUpdate(Input&)
{
	++frame_;

	// �܂肱�̌�ɃV�[���J�ڂ����������Ă��Ƃ�
	if (frame_ >= 60)
	{
		controller_.ChangeScene(std::make_shared<GameScene>(controller_));
		// �������E���̂Ȃ񂩂��ꂾ�ȁA�G������()
		// ���͎������Ȃ����A���̌�̏����𖳌��ɂ���(�������ʂ̂�)
		return;
	}
	// �����������ꍇ�Areturn���Ȃ���Ύ����傪����ł���̂�
	// �����]���r���������邱�ƂɂȂ適���낢��܂������ƂɂȂ�
}

void TitleScene::NormalUpdate(Input& input)
{
	// �G���^�[�L�[���������܂ŉ������Ȃ���
	if (input.IsTrigger("next"))
	{
		update_ = &TitleScene::FadeOutUpdate;
		draw_ = &TitleScene::FadeDraw;
	}
}

void TitleScene::FadeDraw()
{
	// ��ʂ̒��S�o���Ă邾��
	const Size& wsize = Application::GetInstance().GetWindowSize();

	// ���Ȃ��ݓ��ߕ`��𒴑��Ŏ���
	// �܂��t�F�[�h�����̌v�Z
	float rate = static_cast<float>(frame_) / static_cast<float>(fade_interval);
	// ���̏������Ȃ�����̃p�����[�^��0~1�ɂł���炵��
	SetDrawBlendMode(DX_BLENDMODE_MULA, static_cast<int>(255 * rate));
	DrawBox(0, 0, wsize.w, wsize.h, 0x000000, true);
	// BlendMode���g�p�������Noblend��Y��Ȃ�
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void TitleScene::NormalDraw()
{
	DrawString(10, 10, "Title Scene", 0xffffff);
}

// 
TitleScene::TitleScene(SceneController& cont) :
	Scene(cont),
	update_(&TitleScene::FadeInUpdate),
	draw_(&TitleScene::FadeDraw),
	frame_(fade_interval)
{
	// ���[�h
	 backH_ = LoadGraph("image/halloween_mark_pumpkin.png");
	 assert(backH_ != -1);
}

void TitleScene::Update(Input& input)
{
	(this->*update_) (input);
}

void TitleScene::Draw()
{
	// ��ʂ̒��S�o���Ă邾��
	const Size& wsize = Application::GetInstance().GetWindowSize();
	Position2 center = { static_cast<float>(wsize.w) * 0.5f, static_cast<float>(wsize.h) * 0.5f };
	// �w�i�̕\��
	DrawRotaGraph(static_cast<int>(center.x), static_cast<int>(center.y), 1.0, 0.0f, backH_, true);
	// ���s
	// ����͉�ʌ��ʂƂ��̕`��Ɏg�����炢������
	(this->*draw_) ();
}
