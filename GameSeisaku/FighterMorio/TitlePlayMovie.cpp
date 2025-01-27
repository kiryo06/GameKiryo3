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
    // ムービーを再生状態にします
    PlayMovieToGraph(MovieGraphHandle);

    // ループ、GetMovieStateToGraph 関数はムービーの再生状態を得る関数です
    // 戻り値が１の間は再生状態ですのでループを続けます
    while (ProcessMessage() == 0 && GetMovieStateToGraph(MovieGraphHandle) == 1)
    {
        // ムービー映像を画面いっぱいに描画します
        DrawExtendGraph(0, 0, 640, 480, MovieGraphHandle, FALSE);

        // ウエイトをかけます、あまり速く描画すると画面がちらつくからです
        WaitTimer(17);
    }
}

void TitlePlayMovie::Draw()
{
}
