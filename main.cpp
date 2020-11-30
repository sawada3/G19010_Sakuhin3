//########## ヘッダーファイル読み込み ##########
#include "DxLib.h"
#include "resource.h"

//########## マクロ定義 ##########
#define GAME_WIDTH			800	//画面の横の大きさ
#define GAME_HEIGHT			600	//画面の縦の大きさ
#define GAME_COLOR			32	//画面のカラービット

#define GAME_WINDOW_BAR		0	//タイトルバーはデフォルトにする
#define GAME_WINDOW_NAME	"GAME TITLE"	//ウィンドウのタイトル

#define GAME_FPS			60	//FPSの数値	

#define PATH_MAX			255
#define NAME_MAX			255

//フォント
#define FONT_TANU_PATH			TEXT(".\\FONT\\TanukiMagic.ttf")	//フォントの場所
#define FONT_TANU_NAME			TEXT("たぬき油性マジック")			//フォントの名前

//画像のパス
#define IMAGE_START_BACK		TEXT(".\\IMAGE\\ImageStartBack.png")
#define IMAGE_START_TITLE2		TEXT(".\\IMAGE\\TitleRogoBlend2.png")
#define IMAGE_START_TITLE		TEXT(".\\IMAGE\\TitleRogoBlend.png")
#define IMAGE_START_ROGO		TEXT(".\\IMAGE\\TitleRogoBlight.png")
#define IMAGE_START_TITLEROGO	TEXT(".\\IMAGE\\TitleRogo.png")
#define IMAGE_PLAYER_PATH		TEXT(".\\IMAGE\\player.PNG")
#define IMAGE_PLAY_BACK1		TEXT(".\\IMAGE\\ImagePlayBack1.png")
#define IMAGE_PLAY_BACK2		TEXT(".\\IMAGE\\ImagePlayBack2.png")
#define IMAGE_BACK_NUM			4
#define IMAGE_END_BACK		TEXT(".\\IMAGE\\ImageEndBack.png")

//音楽
#define MUSIC_START_PATH		TEXT(".\\MUSIC\\魔法使いと振り子時計.mp3")
#define MUSIC_PLAY_PATH			TEXT(".\\MUSIC\\誰もいない風景.mp3")
#define MUSIC_END_PATH			TEXT(".\\MUSIC\\アクアの旅路.mp3")

//エラーメッセージ
#define FONT_INSTALL_ERR_TITLE	TEXT("フォントインストールエラー")
#define FONT_CREATE_ERR_TITLE	TEXT("フォント作成エラー")

#define IMAGE_LOAD_ERR_TITLE	TEXT("画像読み込みエラー")

#define MUSIC_LOAD_ERR_TITLE	TEXT("音楽読み込みエラー")


enum GAME_SCENE {
	GAME_SCENE_START,
	GAME_SCENE_PLAY,
	GAME_SCENE_END,
};	//ゲームのシーン

enum CHARA_SPEED {
	CHARA_SPEED_LOW = 1,
	CHARA_SPEED_MIDI = 2,
	CHARA_SPEED_HIGH = 3
};	//キャラスピード

//int型のPOINT構造体
typedef struct STRUCT_I_POINT
{
	int x = -1;	//座標を初期化
	int y = -1;	//座標を初期化
}iPOINT;

//フォント構造体
typedef struct STRUCT_FONT
{
	char path[PATH_MAX];	//パス
	char name[NAME_MAX];	//フォント名
	int handle;					//ハンドル
	int size;					//大きさ
	int bold;					//太さ
	int type;					//タイプ
	//※タイプは、https://dxlib.xsrv.jp/function/dxfunc_graph2.html#R17N10　を参照

}FONT;

typedef struct STRUCT_IMAGE
{
	char path[PATH_MAX];		//パス
	int handle;					//ハンドル
	int x;						//X位置
	int y;						//Y位置
	int width;					//幅
	int height;					//高さ
}IMAGE;	//画像構造体

typedef struct STRUCT_MUSIC
{
	char path[PATH_MAX];
	int handle;
}MUSIC;	//音楽構造体

typedef struct STRUCT_CHARA
{
	IMAGE image;	//IMAGE構造体
	int speed;		//速さ
	int CenterX;	//中心X
	int CenterY;	//中心Y
}CHARA;	//キャラクター構造体

typedef struct STRUCT_IMAGE_DES
{
	IMAGE image;		//IMAGE構造体
	BOOL IsDraw;		//弾を表示できるか
}IMAGE_DES;	//背景画像の構造体

//########## グローバル変数 ##########
//FPS関連
int StartTimeFps;				//測定開始時刻
int CountFps;					//カウンタ
float CalcFps;					//計算結果
int SampleNumFps = GAME_FPS;	//平均を取るサンプル数

//キーボードの入力を取得
char AllKeyState[256] = { '\0' };			//すべてのキーの状態が入る
char OldAllKeyState[256] = { '\0' };	//すべてのキーの状態(直前)が入る

FONT FontTanu32;	//たぬき油性マジック：大きさ32　のフォント構造体

int GameScene;		//ゲームシーンを管理

CHARA player;		//プレイヤー

IMAGE_DES ImageBack[IMAGE_BACK_NUM];	//ゲームの背景
IMAGE_DES Title2;
IMAGE_DES Title;
IMAGE_DES ROGO;
IMAGE_DES TitleROGO;
IMAGE StartBack;
IMAGE EndBack;

//音楽関連
MUSIC StartBGM;
MUSIC PlayBGM;
MUSIC EndBGM;

//########## プロトタイプ宣言 ##########
VOID MY_FPS_UPDATE(VOID);			//FPS値を計測、更新する
VOID MY_FPS_DRAW(VOID);				//FPS値を描画する
VOID MY_FPS_WAIT(VOID);				//FPS値を計測し、待つ

VOID MY_ALL_KEYDOWN_UPDATE(VOID);	//キーの入力状態を更新する
BOOL MY_KEY_DOWN(int);				//キーを押しているか、キーコードで判断する
BOOL MY_KEY_UP(int);				//キーを押し上げたか、キーコードで判断する
BOOL MY_KEYDOWN_KEEP(int, int);		//キーを押し続けているか、キーコードで判断する

BOOL MY_FONT_INSTALL_ONCE(VOID);	//フォントをこのソフト用に、一時的にインストール
VOID MY_FONT_UNINSTALL_ONCE(VOID);	//フォントをこのソフト用に、一時的にアンインストール
BOOL MY_FONT_CREATE(VOID);			//フォントを作成する
VOID MY_FONT_DELETE(VOID);			//フォントを削除する

VOID MY_START(VOID);		//スタート画面
VOID MY_START_PROC(VOID);	//スタート画面の処理
VOID MY_START_DRAW(VOID);	//スタート画面の描画

VOID MY_PLAY(VOID);			//プレイ画面
VOID MY_PLAY_PROC(VOID);	//プレイ画面の処理
VOID MY_PLAY_DRAW(VOID);	//プレイ画面の描画

VOID MY_END(VOID);			//エンド画面
VOID MY_END_PROC(VOID);		//エンド画面の処理
VOID MY_END_DRAW(VOID);		//エンド画面の描画

BOOL MY_LOAD_IMAGE(VOID);		//画像をまとめて読み込む関数
VOID MY_DELETE_IMAGE(VOID);		//画像をまとめて削除する関数

BOOL MY_LOAD_MUSIC(VOID);		//音楽をまとめて読み込む関数
VOID MY_DELETE_MUSIC(VOID);		//音楽をまとめて削除する関数

//########## プログラムで最初に実行される関数 ##########
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);								//ウィンドウモードに設定
	SetGraphMode(GAME_WIDTH, GAME_HEIGHT, GAME_COLOR);	//指定の数値でウィンドウを表示する
	SetWindowStyleMode(GAME_WINDOW_BAR);				//タイトルバーはデフォルトにする
	SetMainWindowText(TEXT(GAME_WINDOW_NAME));			//ウィンドウのタイトルの文字
	SetAlwaysRunFlag(TRUE);								//非アクティブでも実行する
	SetWindowIconID(IDI_ICON1);							//アイコンファイルを読込

	if (DxLib_Init() == -1) { return -1; }	//ＤＸライブラリ初期化処理

	//画像を読み込む
	if (MY_LOAD_IMAGE() == FALSE) { return -1; }
	//音楽を読み込む
	if (MY_LOAD_MUSIC() == FALSE) { return -1; }

	//フォントを一時的にインストール
	if (MY_FONT_INSTALL_ONCE() == FALSE) { return -1; }
	//フォントハンドルを作成
	if (MY_FONT_CREATE() == FALSE) { return -1; }

	SetMouseDispFlag(TRUE);			//マウスカーソルを表示	

	GameScene = GAME_SCENE_START;	//ゲームシーンはスタート画面から

	SetDrawScreen(DX_SCREEN_BACK);	//Draw系関数は裏画面に描画

	//無限ループ
	while (TRUE)
	{
		if (ProcessMessage() != 0) { break; }	//メッセージ処理の結果がエラーのとき、強制終了
		if (ClearDrawScreen() != 0) { break; }	//画面を消去できなかったとき、強制終了

		MY_ALL_KEYDOWN_UPDATE();				//押しているキー状態を取得

		MY_FPS_UPDATE();	//FPSの処理[更新]
		
		//シーンごとに処理を行う
		switch (GameScene)
		{
		case GAME_SCENE_START:
			MY_START();	//スタート画面
			break;
		case GAME_SCENE_PLAY:
			MY_PLAY();	//プレイ画面
			break;
		case GAME_SCENE_END:
			MY_END();	//エンド画面
			break;
		}

		MY_FPS_DRAW();		//FPSの処理[描画]

		ScreenFlip();		//モニタのリフレッシュレートの速さで裏画面を再描画

		MY_FPS_WAIT();		//FPSの処理[待つ]
	}

	//フォントハンドルを破棄
	MY_FONT_DELETE();

	//一時的にインストールしたフォントをアンインストール
	MY_FONT_UNINSTALL_ONCE();

	//画像ハンドルを破棄
	MY_DELETE_IMAGE();

	//音楽ハンドルを破棄
	MY_DELETE_MUSIC();

	DxLib_End();	//ＤＸライブラリ使用の終了処理

	return 0;
}

//########## FPS値を計測、更新する関数 ##########
VOID MY_FPS_UPDATE(VOID)
{
	if (CountFps == 0) //1フレーム目なら時刻を記憶
	{
		StartTimeFps = GetNowCount();
	}

	if (CountFps == SampleNumFps) //60フレーム目なら平均を計算
	{
		int now = GetNowCount();
		//現在の時間から、0フレーム目の時間を引き、FPSの数値で割る＝1FPS辺りの平均時間が計算される
		CalcFps = 1000.f / ((now - StartTimeFps) / (float)SampleNumFps);
		CountFps = 0;
		StartTimeFps = now;
	}
	CountFps++;
	return;
}

//########## FPS値を描画する関数 ##########
VOID MY_FPS_DRAW(VOID)
{
	//文字列を描画
	DrawFormatString(0, GAME_HEIGHT - 20, GetColor(255, 255, 255), "FPS:%.1f", CalcFps);
	return;
}

//########## FPS値を計測し、待つ関数 ##########
VOID MY_FPS_WAIT(VOID)
{
	int resultTime = GetNowCount() - StartTimeFps;					//かかった時間
	int waitTime = CountFps * 1000 / GAME_FPS - resultTime;	//待つべき時間

	if (waitTime > 0)		//指定のFPS値よりも早い場合
	{
		WaitTimer(waitTime);	//待つ
	}
	return;
}

//########## キーの入力状態を更新する関数 ##########
VOID MY_ALL_KEYDOWN_UPDATE(VOID)
{
	//参考：https://dxlib.xsrv.jp/function/dxfunc_input.html

	char TempKey[256];	//一時的に、現在のキーの入力状態を格納する

	//直前のキー入力をとっておく
	for (int i = 0; i < 256; i++)
	{
		OldAllKeyState[i] = AllKeyState[i];
	}

	GetHitKeyStateAll(TempKey); // 全てのキーの入力状態を得る

	for (int i = 0; i < 256; i++)
	{
		if (TempKey[i] != 0)	//押されているキーのキーコードを押しているとき
		{
			AllKeyState[i]++;	//押されている
		}
		else
		{
			AllKeyState[i] = 0;	//押されていない
		}
	}
	return;
}

//キーを押しているか、キーコードで判断する
//引　数：int：キーコード：KEY_INPUT_???
BOOL MY_KEY_DOWN(int KEY_INPUT_)
{
	//キーコードのキーを押している時
	if (AllKeyState[KEY_INPUT_] != 0)
	{
		return TRUE;	//キーを押している
	}
	else
	{
		return FALSE;	//キーを押していない
	}
}

//キーを押し上げたか、キーコードで判断する
//引　数：int：キーコード：KEY_INPUT_???
BOOL MY_KEY_UP(int KEY_INPUT_)
{
	if (OldAllKeyState[KEY_INPUT_] >= 1	//直前は押していて
		&& AllKeyState[KEY_INPUT_] == 0)	//今は押していないとき
	{
		return TRUE;	//キーを押し上げている
	}
	else
	{
		return FALSE;	//キーを押し上げていない
	}
}

//キーを押し続けているか、キーコードで判断する
//引　数：int：キーコード：KEY_INPUT_???
//引　数：int：キーを押し続ける時間
BOOL MY_KEYDOWN_KEEP(int KEY_INPUT_, int DownTime)
{
	//押し続ける時間=秒数×FPS値
	//例）60FPSのゲームで、1秒間押し続けるなら、1秒×60FPS
	int UpdateTime = DownTime * GAME_FPS;

	if (AllKeyState[KEY_INPUT_] > UpdateTime)
	{
		return TRUE;	//押し続けている
	}
	else
	{
		return FALSE;	//押し続けていない
	}
}

//フォントをこのソフト用に、一時的にインストール
BOOL MY_FONT_INSTALL_ONCE(VOID)
{
	//フォントを一時的に読み込み(WinAPI)
	if (AddFontResourceEx(FONT_TANU_PATH, FR_PRIVATE, NULL) == 0)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), FONT_TANU_NAME, FONT_INSTALL_ERR_TITLE, MB_OK);
		return FALSE;
	}

	return TRUE;
}

//フォントをこのソフト用に、一時的にアンインストール
VOID MY_FONT_UNINSTALL_ONCE(VOID)
{
	//一時的に読み込んだフォントを削除(WinAPI)
	RemoveFontResourceEx(FONT_TANU_PATH, FR_PRIVATE, NULL);

	return;
}

//フォントを読み込む関数
//引　数：const char *：読み込むフォントの名前
//引　数：int　：フォントの大きさ
//引　数：int　：フォントの太さ
//引　数：int　：フォントのタイプ
//戻り値：なし→変更→戻り値：BOOL：エラー時：FALSE
BOOL MY_FONT_CREATE(VOID)
{
	//↓↓↓たぬき油性マジックのフォントを作成↓↓↓

	//フォントデータを作成
	strcpy_s(FontTanu32.path, sizeof(FontTanu32.path), FONT_TANU_PATH);	//パスをコピー
	strcpy_s(FontTanu32.name, sizeof(FontTanu32.name), FONT_TANU_NAME);	//フォント名をコピー
	FontTanu32.handle = -1;								//ハンドルを初期化
	FontTanu32.size = 32;								//サイズは32
	FontTanu32.bold = 1;								//太さ1
	FontTanu32.type = DX_FONTTYPE_ANTIALIASING_EDGE;	//アンチエイリアシング付きのフォント

	//フォントハンドル作成
	FontTanu32.handle = CreateFontToHandle(FontTanu32.name, FontTanu32.size, FontTanu32.bold, FontTanu32.type);
	//フォントハンドル作成できないとき、エラー
	if (FontTanu32.handle == -1) { MessageBox(GetMainWindowHandle(), FONT_TANU_NAME, FONT_CREATE_ERR_TITLE, MB_OK); return FALSE; }

	//↑↑↑たぬき油性マジックのフォントを作成↑↑↑

	return TRUE;
}

//フォントを削除する関数
VOID MY_FONT_DELETE(VOID)
{
	//フォントデータを削除
	DeleteFontToHandle(FontTanu32.handle);	//フォントのハンドルを削除

	return;
}

//スタート画面
VOID MY_START(VOID)
{
	MY_START_PROC();	//スタート画面の処理
	MY_START_DRAW();	//スタート画面の描画

	return;
}

//スタート画面の処理
VOID MY_START_PROC(VOID)
{
	if (CheckSoundMem(StartBGM.handle) == 0)
	{
		ChangeVolumeSoundMem(255 * 50 / 100, StartBGM.handle);

		//BGMを流す
		//DX_PLAYTYPE_NORMAL:　ノーマル再生
		//DX_PLAYTYPE_BACK  : バックグラウンド再生
		//DX_PLAYTYPE_LOOP  : ループ再生
		PlaySoundMem(StartBGM.handle, DX_PLAYTYPE_LOOP);
	}


	//エンターキーを押したら、プレイシーンへ移動する
	if (MY_KEY_DOWN(KEY_INPUT_RETURN) == TRUE)
	{
		//BGMが流れているなら
		if (CheckSoundMem(StartBGM.handle) != 0)
		{
			StopSoundMem(StartBGM.handle);
		}

		GameScene = GAME_SCENE_PLAY;

		return;
	}
	
	if (Title2.image.y > Title.image.y)
	{
		Title2.IsDraw = TRUE;
		Title2.image.y--;
	}
	else if (Title.image.y > ROGO.image.y)
	{
		Title2.IsDraw = FALSE;
		Title.IsDraw = TRUE;
		Title.image.y--;
	}
	else if (ROGO.image.y > GAME_HEIGHT / 2 - ROGO.image.height / 2)
	{
		Title.IsDraw = FALSE;
		ROGO.IsDraw = TRUE;
		ROGO.image.y--;
	}
	else
	{
		ROGO.IsDraw = FALSE;
		TitleROGO.IsDraw = TRUE;
	}

	return;
}

//スタート画面の描画
VOID MY_START_DRAW(VOID)
{
	//背景を描画
	DrawGraph(StartBack.x, StartBack.y, StartBack.handle, TRUE);

	if (Title2.IsDraw == TRUE)
	{
		DrawGraph(Title2.image.x, Title2.image.y, Title2.image.handle, TRUE);
	}
	if (Title.IsDraw == TRUE)
	{
		DrawGraph(Title.image.x, Title.image.y, Title.image.handle, TRUE);
	}
	if (ROGO.IsDraw == TRUE)
	{
		DrawGraph(ROGO.image.x, ROGO.image.y, ROGO.image.handle, TRUE);
	}
	if (TitleROGO.IsDraw == TRUE)
	{
		DrawGraph(TitleROGO.image.x, TitleROGO.image.y, TitleROGO.image.handle, TRUE);
	}

	DrawString(0, 0, "スタート画面(エンターキーを押して下さい)", GetColor(255, 255, 255));
	
	return;
}

//プレイ画面
VOID MY_PLAY(VOID)
{
	MY_PLAY_PROC();	//プレイ画面の処理
	MY_PLAY_DRAW();	//プレイ画面の描画

	return;
}

//プレイ画面の処理
VOID MY_PLAY_PROC(VOID)
{
	//スペースキーを押したら、エンドシーンへ移動する
	if (MY_KEY_DOWN(KEY_INPUT_SPACE) == TRUE)
	{
		//BGMが流れているなら
		if (CheckSoundMem(PlayBGM.handle) != 0)
		{
			StopSoundMem(PlayBGM.handle);
		}

		GameScene = GAME_SCENE_END;

		return;
	}

	if (CheckSoundMem(PlayBGM.handle) == 0)
	{
		ChangeVolumeSoundMem(255 * 50 / 100, PlayBGM.handle);

		//BGMを流す
		//DX_PLAYTYPE_NORMAL:　ノーマル再生
		//DX_PLAYTYPE_BACK  : バックグラウンド再生
		//DX_PLAYTYPE_LOOP  : ループ再生
		PlaySoundMem(PlayBGM.handle, DX_PLAYTYPE_LOOP);
	}

	

	player.image.x = player.CenterX - player.image.width / 2;
	player.image.y = player.CenterY - player.image.height / 2;

	player.speed = 2;
	if (MY_KEY_DOWN(KEY_INPUT_UP) == TRUE)
	{
		player.CenterY -= player.speed;
	}
	if (MY_KEY_DOWN(KEY_INPUT_DOWN) == TRUE)
	{
		player.CenterY += player.speed;
	}
	if (MY_KEY_DOWN(KEY_INPUT_LEFT) == TRUE)
	{
		player.CenterX -= player.speed;
	}
	if (MY_KEY_DOWN(KEY_INPUT_RIGHT) == TRUE)
	{
		player.CenterX += player.speed;
	}

	//画面外にプレイヤーが行かないようにする
	if (player.image.x < 0) { player.image.x = 0; }
	if (player.image.x + player.image.width > GAME_WIDTH) { player.image.x = GAME_WIDTH - player.image.width; }
	if (player.image.y < 0) { player.image.y = 0; }
	if (player.image.y + player.image.height > GAME_HEIGHT) { player.image.y = GAME_HEIGHT - player.image.height; }

	//背景画像を動かす
	for (int num = 0; num < IMAGE_BACK_NUM; num++)
	{
		//画像を移動させる
		ImageBack[num].image.x++;

		if (ImageBack[num].IsDraw == FALSE)
		{
			//背景画像が画面内にいるとき
			if (ImageBack[num].image.x + ImageBack[num].image.width > 0)
			{
				ImageBack[num].IsDraw = TRUE;	//画像を描画する
			}
		}
		//背景画像が画面を通り越したとき
		if (ImageBack[num].image.x > GAME_WIDTH)
		{
			ImageBack[num].image.x = 0 - ImageBack[0].image.width * 3;	//画像の高さ２つ分、横に移動させる
			ImageBack[num].IsDraw = FALSE;								//画像を描画しない
		}
	}

	return;
}

//プレイ画面の描画
VOID MY_PLAY_DRAW(VOID)
{
	for (int num = 0; num < IMAGE_BACK_NUM; num++)
	{
		if (ImageBack[num].IsDraw == TRUE)
		{
			DrawGraph(ImageBack[num].image.x, ImageBack[num].image.y, ImageBack[num].image.handle, TRUE);
		}
	}

	//プレイヤーを描画する
	DrawGraph(player.image.x, player.image.y, player.image.handle, TRUE);

	DrawString(0, 0, "プレイ画面(スペースキーを押して下さい)", GetColor(255, 255, 255));
	return;
}

//エンド画面
VOID MY_END(VOID)
{
	MY_END_PROC();	//エンド画面の処理
	MY_END_DRAW();	//エンド画面の描画
	return;
}

//エンド画面の処理
VOID MY_END_PROC(VOID)
{
	//エスケープキーを押したら、スタートシーンへ移動する
	if (MY_KEY_DOWN(KEY_INPUT_ESCAPE) == TRUE)
	{
		//BGMが流れているなら
		if (CheckSoundMem(EndBGM.handle) != 0)
		{
			StopSoundMem(EndBGM.handle);
		}

		GameScene = GAME_SCENE_START;

		return;
	}

	if (CheckSoundMem(EndBGM.handle) == 0)
	{
		ChangeVolumeSoundMem(255 * 50 / 100, EndBGM.handle);

		//BGMを流す
		//DX_PLAYTYPE_NORMAL:　ノーマル再生
		//DX_PLAYTYPE_BACK  : バックグラウンド再生
		//DX_PLAYTYPE_LOOP  : ループ再生
		PlaySoundMem(EndBGM.handle, DX_PLAYTYPE_LOOP);
	}

	return;
}

//エンド画面の描画
VOID MY_END_DRAW(VOID)
{
	//背景を描画
	DrawGraph(EndBack.x, EndBack.y, EndBack.handle, TRUE);

	DrawString(0, 0, "エンド画面(エスケープキーを押して下さい)", GetColor(255, 255, 255));
	return;
}

BOOL MY_LOAD_IMAGE(VOID)
{
	//タイトル背景
	strcpy_s(StartBack.path, IMAGE_START_BACK);
	StartBack.handle = LoadGraph(StartBack.path);	//読み込み
	if (StartBack.handle == -1)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), IMAGE_START_BACK, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(StartBack.handle, &StartBack.width, &StartBack.height);
	StartBack.x = GAME_WIDTH / 2 - StartBack.width / 2;
	StartBack.y = GAME_HEIGHT / 2 - StartBack.height / 2;

	//タイトルロゴ
	strcpy_s(Title2.image.path, IMAGE_START_TITLE2);
	Title2.image.handle = LoadGraph(Title2.image.path);	//読み込み
	if (Title2.image.handle == -1)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), IMAGE_START_TITLE2, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(Title2.image.handle, &Title2.image.width, &Title2.image.height);
	Title2.image.x = GAME_WIDTH / 2 - Title2.image.width / 2;
	Title2.image.y = GAME_HEIGHT / 2 - Title2.image.width / 2 + 180;
	Title2.IsDraw = FALSE;

	strcpy_s(Title.image.path, IMAGE_START_TITLE);
	Title.image.handle = LoadGraph(Title.image.path);	//読み込み
	if (Title.image.handle == -1)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), IMAGE_START_TITLE, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(Title.image.handle, &Title.image.width, &Title.image.height);
	Title.image.x = GAME_WIDTH / 2 - Title.image.width / 2;
	Title.image.y = GAME_HEIGHT / 2 - Title.image.width / 2 + 130;
	Title.IsDraw = FALSE;

	strcpy_s(ROGO.image.path, IMAGE_START_ROGO);
	ROGO.image.handle = LoadGraph(ROGO.image.path);	//読み込み
	if (ROGO.image.handle == -1)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), IMAGE_START_ROGO, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ROGO.image.handle, &ROGO.image.width, &ROGO.image.height);
	ROGO.image.x = GAME_WIDTH / 2 - ROGO.image.width / 2;
	ROGO.image.y = GAME_HEIGHT / 2 - ROGO.image.width / 2 + 100;
	ROGO.IsDraw = FALSE;

	strcpy_s(TitleROGO.image.path, IMAGE_START_TITLEROGO);
	TitleROGO.image.handle = LoadGraph(TitleROGO.image.path);	//読み込み
	if (TitleROGO.image.handle == -1)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), IMAGE_START_TITLEROGO, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(TitleROGO.image.handle, &TitleROGO.image.width, &TitleROGO.image.height);
	TitleROGO.image.x = GAME_WIDTH / 2 - TitleROGO.image.width / 2;
	TitleROGO.image.y = GAME_HEIGHT / 2 - TitleROGO.image.height / 2;
	TitleROGO.IsDraw = FALSE;

	//背景画像
	strcpy_s(ImageBack[0].image.path, IMAGE_PLAY_BACK1);			//パスの設定
	strcpy_s(ImageBack[1].image.path, IMAGE_PLAY_BACK2);
	strcpy_s(ImageBack[2].image.path, IMAGE_PLAY_BACK1);
	strcpy_s(ImageBack[3].image.path, IMAGE_PLAY_BACK2);

	//画像を連続して読み込み
	for (int num = 0; num < IMAGE_BACK_NUM; num++)
	{
		ImageBack[num].image.handle = LoadGraph(ImageBack[num].image.path);
		if (ImageBack[num].image.handle == -1)
		{
			//エラーメッセージ表示
			MessageBox(GetMainWindowHandle(), IMAGE_PLAY_BACK1, IMAGE_LOAD_ERR_TITLE, MB_OK);
			return FALSE;
		}
		//画像の幅と高さを取得
		GetGraphSize(ImageBack[num].image.handle, &ImageBack[num].image.width, &ImageBack[num].image.height);
	}
	//背景画像①の設定
	ImageBack[0].image.x = 0 - ImageBack[0].image.width * 0;				//xは原点から
	ImageBack[0].image.y = GAME_HEIGHT / 2 - ImageBack[0].image.height / 2;	//上下中央揃え
	ImageBack[0].IsDraw = FALSE;
	//背景画像②の設定
	ImageBack[1].image.x = 0 - ImageBack[0].image.width * 1;				//xは原点から
	ImageBack[1].image.y = GAME_HEIGHT / 2 - ImageBack[1].image.height / 2;	//上下中央揃え
	ImageBack[1].IsDraw = FALSE;
	//背景画像③の設定
	ImageBack[2].image.x = 0 - ImageBack[0].image.width * 2;				//xは原点から
	ImageBack[2].image.y = GAME_HEIGHT / 2 - ImageBack[2].image.height / 2;	//上下中央揃え
	ImageBack[2].IsDraw = FALSE;
	//背景画像④の設定
	ImageBack[3].image.x = 0 - ImageBack[0].image.width * 3;				//xは原点から
	ImageBack[3].image.y = GAME_HEIGHT / 2 - ImageBack[3].image.height / 2;	//上下中央揃え
	ImageBack[3].IsDraw = FALSE;

	//プレイヤーの画像
	strcpy_s(player.image.path, IMAGE_PLAYER_PATH);		//パスの設定
	player.image.handle = LoadGraph(player.image.path);	//読み込み
	if (player.image.handle == -1)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), IMAGE_PLAYER_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(player.image.handle, &player.image.width, &player.image.height);	//画像の幅と高さを取得
	player.image.x = GAME_WIDTH / 2 - player.image.width / 2;		//左右中央揃え
	player.image.y = GAME_HEIGHT / 2 - player.image.height / 2;		//上下中央揃え
	player.CenterX = player.image.x + player.image.width / 2;		//画像の横の中心を探す
	player.CenterY = player.image.y + player.image.height / 2;		//画像の縦の中心を探す
	player.speed = CHARA_SPEED_LOW;									//スピードを設定

	//エンド背景
	strcpy_s(EndBack.path, IMAGE_END_BACK);
	EndBack.handle = LoadGraph(EndBack.path);	//読み込み
	if (EndBack.handle == -1)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), IMAGE_END_BACK, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(EndBack.handle, &EndBack.width, &EndBack.height);
	EndBack.x = GAME_WIDTH / 2 - EndBack.width / 2;
	EndBack.y = GAME_HEIGHT / 2 - EndBack.height / 2;

	return TRUE;
}

VOID MY_DELETE_IMAGE(VOID)
{
	for (int num = 0; num < IMAGE_BACK_NUM; num++)
	{
		DeleteGraph(ImageBack[num].image.handle);
	}

	DeleteGraph(player.image.handle);
	DeleteGraph(Title2.image.handle);
	DeleteGraph(Title.image.handle);
	DeleteGraph(ROGO.image.handle);
	DeleteGraph(TitleROGO.image.handle);
	DeleteGraph(StartBack.handle);
	DeleteGraph(EndBack.handle);

	return;
}

BOOL MY_LOAD_MUSIC(VOID)
{
	strcpy_s(StartBGM.path, MUSIC_START_PATH);
	StartBGM.handle = LoadSoundMem(StartBGM.path);
	if (StartBGM.handle == -1)
	{
		MessageBox(GetMainWindowHandle(), MUSIC_START_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	strcpy_s(PlayBGM.path, MUSIC_PLAY_PATH);
	PlayBGM.handle = LoadSoundMem(PlayBGM.path);
	if (PlayBGM.handle == -1)
	{
		MessageBox(GetMainWindowHandle(), MUSIC_PLAY_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	strcpy_s(EndBGM.path, MUSIC_END_PATH);
	EndBGM.handle = LoadSoundMem(EndBGM.path);
	if (EndBGM.handle == -1)
	{
		MessageBox(GetMainWindowHandle(), MUSIC_END_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	return TRUE;
}

VOID MY_DELETE_MUSIC(VOID)
{
	DeleteSoundMem(StartBGM.handle);
	DeleteSoundMem(PlayBGM.handle);
	DeleteSoundMem(EndBGM.handle);
}