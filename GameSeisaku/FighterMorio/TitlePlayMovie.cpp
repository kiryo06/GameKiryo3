#include "TitlePlayMovie.h"
#include "DxLib.h"

TitlePlayMovie::TitlePlayMovie():
	MovieGraphHandle(0)
{
}

TitlePlayMovie::~TitlePlayMovie()
{
	DeleteGraph(MovieGraphHandle);
}

void TitlePlayMovie::Init()
{
	MovieGraphHandle = LoadGraph("data/image/download.mp4");
}

void TitlePlayMovie::Update()
{
    // ���[�r�[���Đ���Ԃɂ��܂�
    PlayMovieToGraph(MovieGraphHandle);

    // ���[�v�AGetMovieStateToGraph �֐��̓��[�r�[�̍Đ���Ԃ𓾂�֐��ł�
    // �߂�l���P�̊Ԃ͍Đ���Ԃł��̂Ń��[�v�𑱂��܂�
    while (ProcessMessage() == 0 && GetMovieStateToGraph(MovieGraphHandle) == 1)
    {
        // ���[�r�[�f������ʂ����ς��ɕ`�悵�܂�
        DrawExtendGraph(0, 0, 640, 480, MovieGraphHandle, FALSE);

        // �E�G�C�g�������܂��A���܂葬���`�悷��Ɖ�ʂ����������ł�
        WaitTimer(17);
    }
}

void TitlePlayMovie::Draw()
{
}
