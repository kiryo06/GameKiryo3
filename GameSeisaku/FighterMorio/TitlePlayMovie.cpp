#include "TitlePlayMovie.h"
#include "DxLib.h"

TitlePlayMovie::TitlePlayMovie():
    MovieGraphHandle(-1),
    IsPlay(false)
{
}

TitlePlayMovie::~TitlePlayMovie()
{
    DeleteGraph(MovieGraphHandle);
}

void TitlePlayMovie::Init()
{
    // ����t�@�C�����J��
    MovieGraphHandle = LoadGraph("data/image/Title_2.mp4");
    PlayMovieToGraph(MovieGraphHandle);
}

void TitlePlayMovie::Update()
{
    //// ����̍Đ���Ԃ��X�V
    //if (!IsPlay)
    //{
    //    if (MovieGraphHandle != -1 && GetMovieStateToGraph(MovieGraphHandle) == DX_MOVIEPLAYTYPE_BCANCEL)
    //    {
    //        // �Đ����I��������Đ������Z�b�g
    //        SeekMovieToGraph(MovieGraphHandle, 0);
    //        PlayMovieToGraph(MovieGraphHandle);
    //    }
    //}
}

void TitlePlayMovie::Draw()
{
    // �����`��
    DrawGraph(0, 0, MovieGraphHandle, TRUE);
   // DrawRectExtendGraph(0, 0, Game::kScreenWidth, Game::kScreenHeight, );
   // DrawExtendGraph(0, 0, Game::kScreenWidth, Game::kScreenHeight, MovieGraphHandle, TRUE);
}
