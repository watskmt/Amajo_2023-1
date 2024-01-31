// Project3.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "framework.h"
#include "Project3.h"

#include <cmath>
#include <ctime>

#define MAX_LOADSTRING 100

// グローバル変数:
HINSTANCE hInst;                                // 現在のインターフェイス
WCHAR szTitle[MAX_LOADSTRING];                  // タイトル バーのテキスト
WCHAR szWindowClass[MAX_LOADSTRING];            // メイン ウィンドウ クラス名

// このコード モジュールに含まれる関数の宣言を転送します:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: ここにコードを挿入してください。

    // グローバル文字列を初期化する
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_PROJECT3, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // アプリケーション初期化の実行:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PROJECT3));

    MSG msg;

    // メイン メッセージ ループ:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  関数: MyRegisterClass()
//
//  目的: ウィンドウ クラスを登録します。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PROJECT3));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_PROJECT3);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   関数: InitInstance(HINSTANCE, int)
//
//   目的: インスタンス ハンドルを保存して、メイン ウィンドウを作成します
//
//   コメント:
//
//        この関数で、グローバル変数でインスタンス ハンドルを保存し、
//        メイン プログラム ウィンドウを作成および表示します。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // グローバル変数にインスタンス ハンドルを格納する

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  関数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的: メイン ウィンドウのメッセージを処理します。
//
//  WM_COMMAND  - アプリケーション メニューの処理
//  WM_PAINT    - メイン ウィンドウを描画する
//  WM_DESTROY  - 中止メッセージを表示して戻る
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 選択されたメニューの解析:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: HDC を使用する描画コードをここに追加してください...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// バージョン情報ボックスのメッセージ ハンドラーです。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

#include <windows.h>
#include "DxLib.h"
#define WINDOW_SIZE_X 400 // x方向のウィンドウサイズ 
#define WINDOW_SIZE_Y 400 // y方向のウィンドウサイズ

#define COUNT_X 10 // x方向に🔲を並べる数
#define COUNT_Y 10 // y方向に🔲を並べる数

#define WALL 2 //　壁
#define CLEAR 0 //　通路（通行可能）
#define ME 1 // 通路（自分がいる場所）
#define COMING 3 //　通路（今通ってきた）
#define AVOID 4 // 通路（その先が行き止まり）

int pattern[COUNT_Y][COUNT_X] = {
<<<<<<< HEAD
    {0, 0, 0, 2, 2, 0, 0, 0, 0, 0 },
    {0, 2, 2, 0, 2, 0, 0, 2, 2, 0 },
    {0, 2, 0, 0, 2, 0, 0, 0, 0, 0 },
    {0, 0, 0, 2, 2, 2, 2, 2, 2, 0 },
    {2, 2, 0, 0, 0, 0, 0, 2, 0, 0 },
    {0, 2, 2, 0, 2, 2, 2, 0, 0, 0 },
    {0, 2, 0, 0, 0, 2, 0, 0, 2, 2 },
    {0, 0, 0, 2, 0, 2, 2, 0, 2, 0 },
    {0, 2, 0, 0, 0, 0, 2, 0, 0, 0 },
    {0, 0, 0, 2, 2, 0, 0, 0, 2, 0 }
=======
    {0, 2, 0, 0, 0, 0, 0, 0, 2, 0 },
    {0, 2, 0, 2, 0, 2, 2, 2, 2, 0 },
    {0, 2, 0, 2, 0, 2, 2, 2, 2, 0 },
    {0, 2, 0, 2, 0, 2, 0, 0, 0, 0 },
    {0, 0, 0, 2, 0, 0, 0, 2, 2, 0 },
    {0, 2, 0, 2, 0, 2, 0, 2, 2, 0 },
    {0, 2, 0, 2, 0, 2, 0, 2, 2, 0 },
    {0, 2, 0, 2, 0, 2, 0, 2, 2, 0 },
    {0, 2, 0, 2, 2, 2, 0, 0, 2, 0 },
    {0, 2, 0, 0, 0, 2, 2, 0, 2, 0 }
>>>>>>> origin/test
};
int meX, meY, oldX, oldY;
typedef struct POS
{
    int x;
    int y;
}POS;


// 四方の情報を持つ構造体
typedef struct DIR
{
    int left, up, right, down;
}DIR;

// ウィンドウ範囲をチェックする（範囲内：１、範囲外：０）
int checkBound(int x, int y)
{
    return x >= 0 && x < COUNT_X && y >= 0 && y < COUNT_Y ? 1 : 0;
}

int count_deadend = 0;

// 四方の進行可能な方向を返す
DIR checkDirection(int pat[][10], POS p)
{
    DIR d;
    if ((checkBound(p.x - 1, p.y) && pat[p.y][p.x - 1] == 0) || count_deadend >= 3) {
        d.left = 1;      
    }   
    else {
        d.left = 0;
        count_deadend++;
    }
    if ((checkBound(p.x + 1, p.y) && pat[p.y][p.x + 1] == 0) || count_deadend >= 3) {
        d.right = 1;       
    }       
    else {
        d.right = 0;
        count_deadend++;
    }
    if ((checkBound(p.x, p.y - 1) && pat[p.y - 1][p.x] == 0) || count_deadend >= 3) {
        d.up = 1;       
    }        
    else {
        d.up = 0;
        count_deadend++;
    }
    if ((checkBound(p.x, p.y + 1) && pat[p.y + 1][p.x] == 0) || count_deadend >= 3) {
        d.down = 1;       
    }        
    else{
        d.down = 0;
        count_deadend++;
    }
    return d;
}

// 自分の位置を更新する
void updatePosition(int pat[][10], POS *me)
{
    POS oldPos = *me;

    DIR d = checkDirection(pat, *me);
    pat[me->y][me->x] = 3;

	if (d.down)
        me->y++;
    else if (d.right)
        me->x++;
    else if (d.up)
        me->y--;
    else if (d.left)
        me->x--;

	pat[me->y][me->x] = 1;
	return;
}

<<<<<<< HEAD

=======
//マップをランダムに生成
void generateRandomMap(int pat[][COUNT_X])
{
    time_t t;
    time(&t);
    SRand((int)t);
    for(int i=0; i<COUNT_X; i++)
        for(int j=0; j<COUNT_Y; j++)
        {
            // 10000までの乱数を発生し、10で割った余りが3以下の時は壁、
            // それより大きいときは通路に設定する
            if (GetRand(10000) % 10 <= 3)
                pat[i][j] = WALL;
            else
                pat[i][j] = CLEAR;
        }

    //スタート地点とゴール地点は必ず通路に設定する。
	pat[0][0] = 0;
    pat[COUNT_Y - 1][COUNT_X - 1] = 0;
}
>>>>>>> origin/test
/**
 * \brief 
 * \param hInstance 
 * \param hPrevInstance 
 * \param lpCmdLine 
 * \param nCmdShow 
 * \return 
 */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    unsigned int Cb, Cb2, Cy, Ck;
    int spaceKeywasPushed = 0;

    if (DxLib_Init() == -1)        // ＤＸライブラリ初期化処理
    {
        return -1;        // エラーが起きたら直ちに終了
    }

    ChangeWindowMode(1);
    SetGraphMode(WINDOW_SIZE_X, WINDOW_SIZE_Y, 32);
    SetMouseDispFlag(TRUE);

    Cb = GetColor(0, 0, 255);
    Cb2 = GetColor(0, 0, 55);
    Cy = GetColor(255, 255, 0);
    Ck = GetColor(0, 0, 0);

    double sizeX = (double)WINDOW_SIZE_X / COUNT_X;
    double sizeY = (double)WINDOW_SIZE_Y / COUNT_Y;

    POS me = { 0,0 };
    POS old = { me.x, me.y };
    generateRandomMap(pattern);
    pattern[me.y][me.x] = 1;

	while(1)
    {
        if (CheckHitKey(KEY_INPUT_ESCAPE)) // ESCキーで抜ける
            break;

        old = me;

		int isSpacekeyPushed = CheckHitKey(KEY_INPUT_SPACE);

		if (isSpacekeyPushed && !spaceKeywasPushed) // スペースキーを押した瞬間
		{
            updatePosition(pattern, &me);

		}
        spaceKeywasPushed = isSpacekeyPushed;

        // 円を描画
        for (int j = 0; j < COUNT_Y; j++)
        {
            int y1 = (int)sizeY * j;
            int y2 = (int)y1 + sizeY;

            for (int i = 0; i < COUNT_X; i++)
            {
                int x1 = (int)sizeX * i;
                int x2 = x1 + (int)sizeX;
                if(pattern[j][i] ==0)
	            	DrawBox(x1, y1, x2, y2, Cb, FALSE); // 通路
                else if (pattern[j][i] == 2)
                    DrawBox(x1, y1, x2, y2, Cb, TRUE); // 壁
                else if (pattern[j][i] == COMING)
                    DrawBox(x1, y1, x2, y2, Cb2, TRUE); // 通ってきた道

                if (pattern[j][i]==1) // 自分がいる場所
                    DrawCircle((x1 + x2) / 2, (y1 + y2) / 2, sizeX / 2 - 2, Cy, TRUE);
                else if(pattern[j][i] == 0) // 自分がいない場所
	                DrawCircle((x1 + x2) / 2, (y1 + y2) / 2, sizeX / 2 - 2, Ck, TRUE);
            }
        }
        //Sleep(10);
        ProcessMessage();
    }

    DxLib_End();            // ＤＸライブラリ使用の終了処理

    return 0;            // ソフトの終了
}