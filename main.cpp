#include "math.h"
#include <Novice.h>

const char kWindowTitle[] = "LE2C_03_イケダ_タクミ";

struct Matrix4x4 {
    float m[4][4];
};

static const int krowheight = 20;
static const int kcolumnwidth = 60;

void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* num)
{

    Novice::ScreenPrintf(x, y, "%s", num);
    for (int row = 0; row < 4; ++row) {
        for (int column = 0; column < 4; ++column) {
            Novice::ScreenPrintf(x + column * kcolumnwidth, (y + row * krowheight) + 20, "%6.02f", matrix.m[row][column]);
        }
    }
}

// 1.透明投影行列
Matrix4x4 MakePrespectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip)
{
    Matrix4x4 num;
    num = { (1 / aspectRatio) * (1 / tanf(fovY / 2)), 0, 0, 0, 0, (1 / tanf(fovY / 2)), 0, 0, 0, 0, farClip / (farClip - nearClip), 1, 0, 0, (-nearClip * farClip) / (farClip - nearClip) };
    return num;
}

// 2.正射影行列
Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip)
{
    Matrix4x4 num;
    num = { 2 / (right - left), 0, 0, 0, 0, 2 / (top - bottom), 0, 0, 0, 0, 1 / (farClip - nearClip), 0, (left + right) / (left - right),
        (top + bottom) / (bottom - top),
        nearClip / (nearClip - farClip), 1 };
    return num;
}

// 3.ビューポート変換行列
Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth)
{
    Matrix4x4 num;
    num = { width / 2, 0, 0, 0, 0, -(height / 2), 0, 0, 0, 0, maxDepth - minDepth, 0, left + (width / 2), top + (height / 2), minDepth, 1 };
    return num;
}

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{

    // ライブラリの初期化
    Novice::Initialize(kWindowTitle, 1280, 720);

    // キー入力結果を受け取る箱
    char keys[256] = { 0 };
    char preKeys[256] = { 0 };

    Matrix4x4 orthographocMatrix = MakeOrthographicMatrix(-160.0f, 160.0f, 200.f, 300.0f, 0.0f, 1000.0f);

    Matrix4x4 perspectiveFovMatrix = MakePrespectiveFovMatrix(0.63f, 1.33f, 0.1f, 1000.0f);

    Matrix4x4 viewPortMatrix = MakeViewportMatrix(100.0f, 200.0f, 600.0f, 300.0f, 0.0f, 1.0f);

    // ウィンドウの×ボタンが押されるまでループ
    while (Novice::ProcessMessage() == 0) {
        // フレームの開始
        Novice::BeginFrame();

        // キー入力を受け取る
        memcpy(preKeys, keys, 256);
        Novice::GetHitKeyStateAll(keys);

        ///
        /// ↓更新処理ここから
        ///

        ///
        /// ↑更新処理ここまで
        ///

        ///
        /// ↓描画処理ここから
        ///

        MatrixScreenPrintf(0, 0, orthographocMatrix, "orthographocMatrix");
        MatrixScreenPrintf(0, krowheight * 5, perspectiveFovMatrix, "perspectiveFovMatrix");
        MatrixScreenPrintf(0, krowheight * 10, viewPortMatrix, "viewPortMatrix");

        ///
        /// ↑描画処理ここまで
        ///

        // フレームの終了
        Novice::EndFrame();

        // ESCキーが押されたらループを抜ける
        if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
            break;
        }
    }

    // ライブラリの終了
    Novice::Finalize();
    return 0;
}
