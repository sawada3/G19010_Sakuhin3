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
#define IMAGE_START_MENU1		TEXT(".\\IMAGE\\menu1.png")
#define IMAGE_START_MENU2		TEXT(".\\IMAGE\\menu2.png")
#define IMAGE_SETSUMEI			TEXT(".\\IMAGE\\HowToPlay.png")
#define IMAGE_START_TITLE2		TEXT(".\\IMAGE\\TitleRogoBlend2.png")
#define IMAGE_START_TITLE		TEXT(".\\IMAGE\\TitleRogoBlend.png")
#define IMAGE_START_TITLEROGO	TEXT(".\\IMAGE\\TitleRogo.png")
#define IMAGE_END_COMP_ROGO		TEXT(".\\IMAGE\\EndRogo.png")
#define IMAGE_BOY_PATH			TEXT(".\\IMAGE\\boy.PNG")
#define IMAGE_PLAY_BACK1		TEXT(".\\IMAGE\\ImagePlayBack1.png")
#define IMAGE_PLAY_BACK2		TEXT(".\\IMAGE\\ImagePlayBack2.png")
#define IMAGE_PLAY_FRONT1		TEXT(".\\IMAGE\\ImagePlayFront1.png")
#define IMAGE_PLAY_FRONT2		TEXT(".\\IMAGE\\ImagePlayFront2.png")
#define IMAGE_NUM				4
#define IMAGE_LOAD_BLACK		TEXT(".\\IMAGE\\Loading.png")
#define IMAGE_END_BACK			TEXT(".\\IMAGE\\ImageEndBack.png")
#define IMAGE_TEXTBOX			TEXT(".\\IMAGE\\text.png")
#define IMAGE_PLAYER_PATH		TEXT(".\\IMAGE\\playerAll.png")
#define PLAYER_DIV_WIDTH		100
#define PLAYER_DIV_HEIGHT		169
#define PLAYER_DIV_TATE			4
#define PLAYER_DIV_YOKO			1
#define PLAYER_DIV_NUM		PLAYER_DIV_TATE * PLAYER_DIV_YOKO
#define IMAGE_PLAYER_CNT		1
#define IMAGE_PLAYER_CNT_MAX	10

#define TEXT_POSITION_X			224	//文字表示位置X
#define TEXT_POSITION_Y			32	//文字表示位置Y

//BGM
#define MUSIC_START_PATH		TEXT(".\\MUSIC\\魔法使いと振り子時計.mp3")
#define MUSIC_PLAY_PATH			TEXT(".\\MUSIC\\誰もいない風景.mp3")
#define MUSIC_END_PATH			TEXT(".\\MUSIC\\アクアの旅路.mp3")
//SE
#define SE_CURSOR				TEXT(".\\MUSIC\\se_maoudamashii_system48.mp3")
#define SE_KETTEI				TEXT(".\\MUSIC\\se_maoudamashii_system47.mp3")
#define SE_PAPER				TEXT(".\\MUSIC\\se_maoudamashii_se_paper01.mp3")
#define SE_WALK					TEXT(".\\MUSIC\\se_maoudamashii_se_footstep02.mp3")
#define SE_DOOR					TEXT(".\\MUSIC\\ドア・開ける05.mp3")


//マップ
#define GAME_MAP_TATE_MAX	10
#define GAME_MAP_YOKO_MAX	13
#define GAME_MAP_KIND_MAX	5

#define GAME_MAP_PATH		TEXT(".\\IMAGE\\MAP\\マップ.png")

#define MAP_DIV_WIDTH		64
#define MAP_DIV_HEIGHT		64
#define MAP_DIV_TATE		10
#define MAP_DIV_YOKO		4
#define MAP_DIV_NUM MAP_DIV_TATE * MAP_DIV_YOKO

//エラーメッセージ
#define FONT_INSTALL_ERR_TITLE	TEXT("フォントインストールエラー")
#define FONT_CREATE_ERR_TITLE	TEXT("フォント作成エラー")

#define IMAGE_LOAD_ERR_TITLE	TEXT("画像読み込みエラー")

#define MUSIC_LOAD_ERR_TITLE	TEXT("音楽読み込みエラー")

#define START_ERR_TITLE			TEXT("スタート位置エラー")
#define START_ERR_CAPTION		TEXT("スタート位置が決まっていません")

#define GOAL_ERR_TITLE			TEXT("ゴール位置エラー")
#define GOAL_ERR_CAPTION		TEXT("ゴール位置が決まっていません")

#define ESC_TITLE				TEXT("ゲーム中断")
#define ESC_CAPTION				TEXT("ゲーム中断し、タイトル画面に戻りますか？")

enum GAME_MAP_KIND
{
	n = -1,
	s = 0,
	t = 10,
	k = 21,
	m = 11,
	a = 1,
	b = 4,
	o = 14,
	x = 3,
	z = 13,
	e = 5,
	d = 6,
	p = 12,
	c = 20,
	y = 2,
	r = 8,
	g = 7
};

enum GAME_SCENE {
	GAME_SCENE_START,
	GAME_SCENE_PLAY,
	GAME_SCENE_END,
};	//ゲームのシーン

enum GAME_END {
	GAME_END_COMP,
	GAME_END_FAIL
};

enum CHARA_SPEED {
	CHARA_SPEED_LOW = 1,
	CHARA_SPEED_MIDI = 2,
	CHARA_SPEED_HIGH = 3
};	//キャラスピード

typedef struct STRUCT_MAP_IMAGE
{
	char path[PATH_MAX];
	int handle[MAP_DIV_NUM];
	int kind[MAP_DIV_NUM];
	int width;
	int height;
}MAPCHIP;

typedef struct STRUCT_MAP
{
	GAME_MAP_KIND kind;
	int x;
	int y;
	int num;
	int width;
	int height;
}MAP;

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

typedef struct STRUCT_PLAYER
{
	char path[PATH_MAX];
	int handle[PLAYER_DIV_NUM];
	int speed;		//速さ
	int x;
	int y;
	int width;
	int height;

	iPOINT collBeforePt;

	int nowImageKind;					//現在の画像
	int changeImageCnt;					//画像を変えるためのカウント
}PLAYER;

typedef struct STRUCT_CHARA
{
	IMAGE image;
	int CenterX;	//中心X
	int CenterY;	//中心Y
	RECT coll;
	BOOL IsDraw;

	PLAYER player[PLAYER_DIV_NUM];

}CHARA;	//キャラクター構造体

typedef struct STRUCT_IMAGE_DES
{
	IMAGE image;		//IMAGE構造体
	BOOL IsDraw;		//表示できるか
}IMAGE_DES;	//画像の構造体

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
int menu;
int GameEndKind;

RECT GoalRect = { -1,-1,-1,-1 };
RECT ReturnRect = { -1,-1,-1,-1 };

CHARA chara;	//プレイヤー
CHARA boy;		//少年

//当たり判定
RECT PlayerRect;	//プレイヤー
RECT boyRect;		//少年

//画像
IMAGE_DES ImageBack[IMAGE_NUM];		//ゲームの背景
IMAGE_DES ImageFront[IMAGE_NUM];	//
IMAGE_DES TextBox;	//テキストボックス
IMAGE_DES Title2;	//タイトルロゴ１
IMAGE_DES Title;	//タイトルロゴ２
IMAGE_DES TitleROGO;	//タイトルロゴ３
IMAGE_DES menu1;	//メニュー(はじめる)
IMAGE_DES menu2;	//メニュー(操作説明)
IMAGE_DES Setsumei;	//操作説明
IMAGE_DES Loading;	//車両移動時の黒い画像
IMAGE_DES EndROGO;	//エンドロゴ
IMAGE StartBack;	//スタート背景
IMAGE EndBack;		//エンド背景

BOOL IsMove = FALSE;	//プレイヤーが動けるか
BOOL Walk = FALSE;		//プレイヤーが歩いているか
//会話フラグ
BOOL boyFlg = FALSE;	//少年

//BGM
MUSIC StartBGM;
MUSIC PlayBGM;
MUSIC EndBGM;
//SE
MUSIC cursorSE;
MUSIC ketteiSE;
MUSIC paperSE;
MUSIC walkSE;
MUSIC doorSE;

GAME_MAP_KIND mapData[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX]{
	//  0,1,2,3,4,5,6,7,8,9,0,1,2,
		y,a,a,a,a,a,a,a,a,a,a,a,y,	// 0
		y,m,m,m,m,m,m,m,m,m,m,m,y,	// 1
		y,k,x,b,k,x,b,k,x,b,k,x,y,	// 2
		y,t,z,o,t,z,o,t,z,o,t,z,y,	// 3
		y,c,t,t,t,t,t,t,t,t,t,p,y,	// 4
		g,t,t,t,t,t,t,t,t,t,t,t,r,	// 5
		y,t,e,d,t,e,d,t,e,d,s,e,y,	// 6
		y,t,z,o,t,z,o,t,z,o,t,z,y,	// 7
		y,y,y,y,y,y,y,y,y,y,y,y,y,	// 8
		y,y,y,y,y,y,y,y,y,y,y,y,y,	// 9
};

GAME_MAP_KIND mapDataInit[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];

MAPCHIP mapChip;

MAP map[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];

iPOINT startPt{ -1,-1 };
iPOINT ReStartPt{ -1,-1 };
iPOINT ReturnPt{ -1,-1 };

RECT mapColl[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];

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

BOOL MY_CHECK_MAP1_PLAYER_COLL(RECT);
BOOL MY_CHECK_CHARA_PLAYER_COLL(RECT);
BOOL MY_CHECK_RECT_COLL(RECT, RECT);

INT TEXTBOX(VOID);
VOID BOY_TEXT(BOOL);

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

	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			if (mapData[tate][yoko] == s)
			{
				startPt.x = mapChip.width * yoko + mapChip.width / 2;
				startPt.y = mapChip.height * tate + mapChip.height / 2;
			}

			if (mapData[tate][yoko] == p)
			{
				ReStartPt.x= mapChip.width * yoko + mapChip.width / 2;
				ReStartPt.y = mapChip.height * tate + mapChip.height / 2;
			}

			if (mapData[tate][yoko] == c)
			{
				ReturnPt.x = mapChip.width * yoko + mapChip.width / 2;
				ReturnPt.y = mapChip.height * tate + mapChip.height / 2;
			}

			if (mapData[tate][yoko] == r)
			{
				ReturnRect.left = mapChip.width * yoko;
				ReturnRect.top = mapChip.height * tate;
				ReturnRect.right = mapChip.width * (yoko + 1);
				ReturnRect.bottom = mapChip.height * (tate + 1);
			}

			if (mapData[tate][yoko] == g)
			{
				GoalRect.left = mapChip.width * yoko;
				GoalRect.top = mapChip.height * tate;
				GoalRect.right = mapChip.width * (yoko + 1);
				GoalRect.bottom = mapChip.height * (tate + 1);
			}
		}
	}

	if (startPt.x == -1 && startPt.y == -1)
	{
		MessageBox(GetMainWindowHandle(), START_ERR_CAPTION, START_ERR_TITLE, MB_OK); return -1;
	}

	if (GoalRect.left == -1)
	{
		MessageBox(GetMainWindowHandle(), GOAL_ERR_CAPTION, GOAL_ERR_TITLE, MB_OK); return -1;
	}

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
		SetMouseDispFlag(FALSE);			//マウスカーソルを非表示

		ChangeVolumeSoundMem(255 * 50 / 100, StartBGM.handle);

		//BGMを流す
		//DX_PLAYTYPE_NORMAL:　ノーマル再生
		//DX_PLAYTYPE_BACK  : バックグラウンド再生
		//DX_PLAYTYPE_LOOP  : ループ再生
		PlaySoundMem(StartBGM.handle, DX_PLAYTYPE_LOOP);
	}

	//タイトルロゴ
	if (Title2.image.y > Title.image.y)
	{
		Title2.IsDraw = TRUE;
		Title2.image.y--;
	}
	else if (Title.image.y > TitleROGO.image.y)
	{
		Title2.IsDraw = FALSE;
		Title.IsDraw = TRUE;
		Title.image.y--;
	}
	else
	{
		Title.IsDraw = FALSE;
		TitleROGO.IsDraw = TRUE;
	}

	if (MY_KEY_DOWN(KEY_INPUT_RETURN) == TRUE)
	{
		Title2.image.y = Title.image.y;
		Title2.IsDraw = FALSE;
		Title.image.y = TitleROGO.image.y + 1;
		Title.IsDraw = FALSE;
	}

	if (TitleROGO.IsDraw == TRUE)
	{
		//メニューの表示
		//0:はじめる
		//1:操作説明
		if (MY_KEY_DOWN(KEY_INPUT_RIGHT) == TRUE && Setsumei.IsDraw == FALSE)
		{
			if (CheckSoundMem(cursorSE.handle) == 0)
			{
				PlaySoundMem(cursorSE.handle, DX_PLAYTYPE_BACK);
			}

			menu = 1;
		}
		if (MY_KEY_DOWN(KEY_INPUT_LEFT) == TRUE && Setsumei.IsDraw == FALSE)
		{
			if (CheckSoundMem(cursorSE.handle) == 0)
			{
				PlaySoundMem(cursorSE.handle, DX_PLAYTYPE_BACK);
			}

			menu = 0;
		}

		switch (menu)
		{
		case 0:
			menu2.IsDraw = FALSE;
			menu1.IsDraw = TRUE;

			break;

		case 1:
			menu1.IsDraw = FALSE;
			menu2.IsDraw = TRUE;

			break;
		}
	}

	if (menu1.IsDraw == TRUE && Setsumei.IsDraw == FALSE)
	{
		//エンターキーを押したら、プレイシーンへ移動する
		if (MY_KEY_DOWN(KEY_INPUT_RETURN) == TRUE)
		{
			SetMouseDispFlag(FALSE);

			if (CheckSoundMem(ketteiSE.handle) == 0)
			{
				PlaySoundMem(ketteiSE.handle, DX_PLAYTYPE_BACK);
			}

			//BGMが流れているなら
			if (CheckSoundMem(StartBGM.handle) != 0)
			{
				StopSoundMem(StartBGM.handle);
			}

			chara.CenterX = startPt.x;
			chara.CenterY = startPt.y;

			for (int cnt = 0; cnt < PLAYER_DIV_NUM; cnt++)
			{
				chara.player[cnt].x = chara.CenterX;
				chara.player[cnt].y = chara.CenterY;

				chara.player[cnt].collBeforePt.x = chara.CenterX;
				chara.player[cnt].collBeforePt.y = chara.CenterY;
			}

			for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
			{
				for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
				{
					map[tate][yoko].num = 1;
				}
			}

			GameEndKind = GAME_END_FAIL;

			GameScene = GAME_SCENE_PLAY;

			return;
		}
	}
	//操作説明
	if (menu2.IsDraw == TRUE)
	{
		//エンターキーを押したら
		if (MY_KEY_DOWN(KEY_INPUT_RETURN) == TRUE)
		{
			//操作説明画像表示
			Setsumei.IsDraw = TRUE;
			//紙の音
			if (CheckSoundMem(paperSE.handle) == 0)
			{
				PlaySoundMem(paperSE.handle, DX_PLAYTYPE_BACK);
			}
		}
		if (Setsumei.IsDraw == TRUE)
		{
			//BACKSPACEキーを押したら
			if (MY_KEY_DOWN(KEY_INPUT_BACK) == TRUE)
			{
				//画像を非表示
				Setsumei.IsDraw = FALSE;
			}
		}
	}

	return;
}

//スタート画面の描画
VOID MY_START_DRAW(VOID)
{
	//背景を描画
	DrawGraph(StartBack.x, StartBack.y, StartBack.handle, TRUE);

	//タイトルロゴ
	if (Title2.IsDraw == TRUE)
	{
		DrawGraph(Title2.image.x, Title2.image.y, Title2.image.handle, TRUE);
	}
	if (Title.IsDraw == TRUE)
	{
		DrawGraph(Title.image.x, Title.image.y, Title.image.handle, TRUE);
	}
	if (TitleROGO.IsDraw == TRUE)
	{
		DrawGraph(TitleROGO.image.x, TitleROGO.image.y, TitleROGO.image.handle, TRUE);
	}

	//メニュー
	if (menu1.IsDraw == TRUE)
	{
		DrawGraph(menu1.image.x, menu1.image.y, menu1.image.handle, TRUE);
	}
	if (menu2.IsDraw == TRUE)
	{
		DrawGraph(menu2.image.x, menu2.image.y, menu2.image.handle, TRUE);
	}
	
	//操作説明
	if (Setsumei.IsDraw == TRUE)
	{
		DrawGraph(Setsumei.image.x, Setsumei.image.y, Setsumei.image.handle, TRUE);
	}

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
	if (CheckSoundMem(PlayBGM.handle) == 0)
	{
		ChangeVolumeSoundMem(255 * 50 / 100, PlayBGM.handle);

		//BGMを流す
		//DX_PLAYTYPE_NORMAL:　ノーマル再生
		//DX_PLAYTYPE_BACK  : バックグラウンド再生
		//DX_PLAYTYPE_LOOP  : ループ再生
		PlaySoundMem(PlayBGM.handle, DX_PLAYTYPE_LOOP);
	}

	//ESCAPEキーを押したら
	if (MY_KEY_DOWN(KEY_INPUT_ESCAPE) == TRUE)
	{
		SetMouseDispFlag(TRUE);		//マウスカーソル表示

		//タイトルに戻りますか　YESNO
		int Ret = MessageBox(GetMainWindowHandle(), ESC_CAPTION, ESC_TITLE, MB_YESNO);

		//YESを選んだとき
		if (Ret == IDYES)
		{
			//BGMを止める
			if (CheckSoundMem(PlayBGM.handle) != 0)
			{
				StopSoundMem(PlayBGM.handle);
			}

			GameScene = GAME_SCENE_START;	//スタート画面に戻る

			return;
		}
		//NOを選んだとき
		else if (Ret == IDNO)
		{
			SetMouseDispFlag(FALSE);	//マウスカーソル非表示
		}
	}

	for (int cnt = 0; cnt < PLAYER_DIV_NUM; cnt++)
	{
		//プレイヤー移動
		chara.player[cnt].speed = 1;
		if (MY_KEY_DOWN(KEY_INPUT_UP) == TRUE)
		{
			chara.CenterY -= chara.player[cnt].speed;
		}
		if (MY_KEY_DOWN(KEY_INPUT_DOWN) == TRUE)
		{
			chara.CenterY += chara.player[cnt].speed;
		}
		if (MY_KEY_DOWN(KEY_INPUT_LEFT) == TRUE)
		{
			chara.CenterX -= chara.player[cnt].speed;
		}
		if (MY_KEY_DOWN(KEY_INPUT_RIGHT) == TRUE)
		{
			chara.CenterX += chara.player[cnt].speed;
		}

		//キャラの当たり判定
		//プレイヤー
		chara.coll.left = chara.CenterX - mapChip.width / 2 + 9;
		chara.coll.top = chara.CenterY + mapChip.height / 2;
		chara.coll.right = chara.CenterX + mapChip.width / 2 - 7;
		chara.coll.bottom = chara.CenterY + mapChip.height + 17;
		//少年
		boy.coll.left = boy.CenterX - mapChip.width / 2 + 9;
		boy.coll.top = boy.CenterY + mapChip.height / 2;
		boy.coll.right = boy.CenterX + mapChip.width / 2 - 7;
		boy.coll.bottom = boy.CenterY + mapChip.height + 17;

		//会話用当たり判定
		//.collよりちょっとだけ広くなってる
		//プレイヤー
		PlayerRect.left = chara.coll.left - 5;
		PlayerRect.top = chara.coll.top - 5;
		PlayerRect.right = chara.coll.right + 5;
		PlayerRect.bottom = chara.coll.bottom + 5;
		//少年
		boyRect.left = boy.coll.left - 5;
		boyRect.top = boy.coll.top - 5;
		boyRect.right = boy.coll.right + 5;
		boyRect.bottom = boy.coll.bottom + 5;

		IsMove = TRUE;	//プレイヤー動ける

		//プレイヤーとマップが当たったとき
		if (MY_CHECK_MAP1_PLAYER_COLL(chara.coll) == TRUE)
		{
			chara.CenterX = chara.player[cnt].collBeforePt.x;
			chara.CenterY = chara.player[cnt].collBeforePt.y;

			IsMove = FALSE;	//プレイヤー動けない
		}
		//プレイヤーとその他キャラ
		if (MY_CHECK_CHARA_PLAYER_COLL(chara.coll) == TRUE)
		{
			chara.CenterX = chara.player[cnt].collBeforePt.x;
			chara.CenterY = chara.player[cnt].collBeforePt.y;

			IsMove = FALSE;
		}

		//会話
		if (MY_CHECK_RECT_COLL(PlayerRect, boyRect) == TRUE)
		{
			if (MY_KEY_DOWN(KEY_INPUT_RETURN) == TRUE)
			{
				boyFlg = TRUE;		//会話フラグ
			}
			if (boyFlg == TRUE)
			{
				chara.CenterX = chara.player[cnt].collBeforePt.x;
				chara.CenterY = chara.player[cnt].collBeforePt.y;

				IsMove = FALSE;

				if (MY_KEY_DOWN(KEY_INPUT_BACK) == TRUE)
				{
					boyFlg = FALSE;
				}
			}
			if (boyFlg == FALSE)
			{
				IsMove = TRUE;
			}
		}

		//プレイヤーが動けるとき
		if (IsMove == TRUE)
		{
			//プレイヤーの位置に置き換える
			chara.player[cnt].x = chara.CenterX - chara.player[cnt].width / 2;
			chara.player[cnt].y = chara.CenterY - chara.player[cnt].height / 2;
			//あたっていないときの座標を取得
			chara.player[cnt].collBeforePt.x = chara.CenterX;
			chara.player[cnt].collBeforePt.y = chara.CenterY;

			//押したキーに応じて画像を切り替え
			//０：左向き前
			//１：右向き前
			//２：左向き足
			//３：右向き足
			if (MY_KEY_DOWN(KEY_INPUT_LEFT) == TRUE)	//左
			{
				if (CheckSoundMem(walkSE.handle) == 0)
				{
					PlaySoundMem(walkSE.handle, DX_PLAYTYPE_BACK);
				}

				chara.player[cnt].nowImageKind = 0;
				Walk = TRUE;
			}
			if (MY_KEY_DOWN(KEY_INPUT_RIGHT) == TRUE)	//右
			{
				if (CheckSoundMem(walkSE.handle) == 0)
				{
					PlaySoundMem(walkSE.handle, DX_PLAYTYPE_BACK);
				}

				chara.player[cnt].nowImageKind = 1;
				Walk = TRUE;
			}
			if (Walk == TRUE)
			{
				if (chara.player[cnt].nowImageKind == 0)
				{
					chara.player[cnt].nowImageKind = 2;
				}
				if (chara.player[cnt].nowImageKind == 1)
				{
					chara.player[cnt].nowImageKind = 3;
				}
				if (MY_KEY_DOWN(KEY_INPUT_LEFT) == FALSE &&
					MY_KEY_DOWN(KEY_INPUT_RIGHT) == FALSE)
				{
					if (chara.player[cnt].nowImageKind == 0 ||
						chara.player[cnt].nowImageKind == 2)
					{
						chara.player[cnt].nowImageKind = 0;
					}
					if (chara.player[cnt].nowImageKind == 1 ||
						chara.player[cnt].nowImageKind == 3)
					{
						chara.player[cnt].nowImageKind = 1;
					}
				}
			}
			//下に移動するとき
			if (MY_KEY_DOWN(KEY_INPUT_DOWN) == TRUE)
			{
				if (CheckSoundMem(walkSE.handle) == 0)
				{
					PlaySoundMem(walkSE.handle, DX_PLAYTYPE_BACK);
				}

				//今の画像が0なら
				if (chara.player[cnt].nowImageKind == 0 ||
					chara.player[cnt].nowImageKind == 2)
				{
					chara.player[cnt].nowImageKind = 0;
				}
				//それ以外(１or３)なら
				else
				{
					chara.player[cnt].nowImageKind = 1;
				}
			}
			//上に移動するとき
			if (MY_KEY_DOWN(KEY_INPUT_UP) == TRUE)
			{
				if (CheckSoundMem(walkSE.handle) == 0)
				{
					PlaySoundMem(walkSE.handle, DX_PLAYTYPE_BACK);
				}

				//今の画像が0なら
				if (chara.player[cnt].nowImageKind == 0 ||
					chara.player[cnt].nowImageKind == 2)
				{
					chara.player[cnt].nowImageKind = 0;
				}
				//それ以外(１or３)なら
				else
				{
					chara.player[cnt].nowImageKind = 1;
				}
			}
		}
	}


	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			if (MY_CHECK_RECT_COLL(PlayerRect, ReturnRect) == TRUE)
			{
				if (MY_KEY_DOWN(KEY_INPUT_RETURN) == TRUE)
				{
					//2番目以降の車両なら
					if (map[tate][yoko].num > 1)
					{
						//前の車両にどもる
						map[tate][yoko].num--;

						if (CheckSoundMem(doorSE.handle) == 0)
						{
							PlaySoundMem(doorSE.handle, DX_PLAYTYPE_BACK);
						}

						chara.CenterX = ReturnPt.x;
						chara.CenterY = ReturnPt.y;
					}
				}
			}

			if (MY_CHECK_RECT_COLL(PlayerRect, GoalRect) == TRUE)
			{
				if (MY_KEY_DOWN(KEY_INPUT_RETURN) == TRUE)
				{
					//次の車両に進む
					map[tate][yoko].num++;

					if (CheckSoundMem(doorSE.handle) == 0)
					{
						PlaySoundMem(doorSE.handle, DX_PLAYTYPE_BACK);
					}

					//最後の車両にいるなら
					if (map[tate][yoko].num > GAME_MAP_KIND_MAX)
					{
						//音楽を止める
						if (CheckSoundMem(PlayBGM.handle) != 0)
						{
							StopSoundMem(PlayBGM.handle);
						}

						GameEndKind = GAME_END_COMP;
						//エンド画面へ
						GameScene = GAME_SCENE_END;

						return;
					}

					chara.CenterX = ReStartPt.x;
					chara.CenterY = ReStartPt.y;
				}
			}
		}
	}

	//背景画像を動かす
	for (int num = 0; num < IMAGE_NUM; num++)
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

	for (int num = 0; num < IMAGE_NUM; num++)
	{
		//画像を移動させる
		ImageFront[num].image.x--;

		if (ImageFront[num].IsDraw == FALSE)
		{
			//背景画像が画面内にいるとき
			if (ImageFront[num].image.x < GAME_WIDTH)
			{
				ImageFront[num].IsDraw = TRUE;	//画像を描画する
			}
		}
		//背景画像が画面を通り越したとき
		if (ImageFront[num].image.x + ImageFront[num].image.width < 0)
		{
			ImageFront[num].image.x = 0 + ImageFront[0].image.width * 3;	//画像の幅２つ分、横に移動させる
			ImageFront[num].IsDraw = FALSE;								//画像を描画しない
		}
	}

	return;
}

//プレイ画面の描画
VOID MY_PLAY_DRAW(VOID)
{
	//プレイ画面の背景を描画
	for (int num = 0; num < IMAGE_NUM; num++)
	{
		if (ImageBack[num].IsDraw == TRUE)
		{
			DrawGraph(ImageBack[num].image.x, ImageBack[num].image.y, ImageBack[num].image.handle, TRUE);
		}
	}
	//マップを描画
	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			DrawGraph(
				map[tate][yoko].x,
				map[tate][yoko].y,
				mapChip.handle[map[tate][yoko].kind],
				TRUE);
		}
	}

	//当たり判定の描画（デバッグ用）
	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			//壁ならば
			if (mapData[tate][yoko] == k || mapData[tate][yoko] == a ||
				mapData[tate][yoko] == m || mapData[tate][yoko] == b ||
				mapData[tate][yoko] == o || mapData[tate][yoko] == x ||
				mapData[tate][yoko] == e || mapData[tate][yoko] == d ||
				mapData[tate][yoko] == z || mapData[tate][yoko] == y)
			{
				DrawBox(mapColl[tate][yoko].left, mapColl[tate][yoko].top, mapColl[tate][yoko].right, mapColl[tate][yoko].bottom, GetColor(0, 0, 255), FALSE);
			}

			//通路ならば
			if (mapData[tate][yoko] == t)
			{
				DrawBox(mapColl[tate][yoko].left, mapColl[tate][yoko].top, mapColl[tate][yoko].right, mapColl[tate][yoko].bottom, GetColor(255, 255, 0), FALSE);
			}

			if (mapData[tate][yoko] == g || mapData[tate][yoko] == r)
			{
				DrawBox(mapColl[tate][yoko].left, mapColl[tate][yoko].top, mapColl[tate][yoko].right, mapColl[tate][yoko].bottom, GetColor(0, 255, 0), FALSE);
			}
		}
	}

	DrawGraph(boy.image.x, boy.image.y, boy.image.handle, TRUE);
	DrawBox(boy.coll.left, boy.coll.top, boy.coll.right, boy.coll.bottom, GetColor(255, 0, 0), FALSE);

	//プレイヤー描写
	for (int cnt = 0; cnt < PLAYER_DIV_NUM; cnt++)
	{
		if (chara.IsDraw == TRUE)
		{
			DrawGraph(
				chara.player[cnt].x,
				chara.player[cnt].y,
				chara.player[cnt].handle[chara.player[cnt].nowImageKind],
				TRUE);

			//プレイヤーの当たり判定描画(デバッグ用)
			DrawBox(chara.coll.left, chara.coll.top, chara.coll.right, chara.coll.bottom, GetColor(255, 0, 0), FALSE);
		}
	}

	DrawString(0, 0, "矢印キーで移動・ESCAPEキーでスタートに戻る", GetColor(255, 255, 255));

	for (int num = 0; num < IMAGE_NUM; num++)
	{
		if (ImageFront[num].IsDraw == TRUE)
		{
			DrawGraph(ImageFront[num].image.x, ImageFront[num].image.y, ImageFront[num].image.handle, TRUE);
		}
	}

	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			DrawFormatString(0, 20, GetColor(255, 255, 255), "現在のマップ：%d", map[tate][yoko].num);
		}
	}

	if (Loading.IsDraw == TRUE)
	{
		DrawGraph(Loading.image.x, Loading.image.y, Loading.image.handle, TRUE);
	}

	if (boyFlg == TRUE)
	{
		BOY_TEXT(IsMove);
	}

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
	if (CheckSoundMem(EndBGM.handle) == 0)
	{
		ChangeVolumeSoundMem(255 * 50 / 100, EndBGM.handle);

		//BGMを流す
		//DX_PLAYTYPE_NORMAL:　ノーマル再生
		//DX_PLAYTYPE_BACK  : バックグラウンド再生
		//DX_PLAYTYPE_LOOP  : ループ再生
		PlaySoundMem(EndBGM.handle, DX_PLAYTYPE_LOOP);
	}

	//エスケープキーを押したら、スタートシーンへ移動する
	if (MY_KEY_DOWN(KEY_INPUT_ESCAPE) == TRUE)
	{
		//BGMが流れているなら
		if (CheckSoundMem(EndBGM.handle) != 0)
		{
			StopSoundMem(EndBGM.handle);
		}

		GameScene = GAME_SCENE_START;
	}

	return;
}

//エンド画面の描画
VOID MY_END_DRAW(VOID)
{
	//背景を描画
	DrawGraph(EndBack.x, EndBack.y, EndBack.handle, TRUE);

	if (GameEndKind == GAME_END_COMP)
	{
		DrawGraph(EndROGO.image.x, EndROGO.image.y, EndROGO.image.handle, TRUE);
	}

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
	Title.image.y = GAME_HEIGHT / 2 - Title.image.width / 2 + 120;
	Title.IsDraw = FALSE;

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
	TitleROGO.image.y = GAME_HEIGHT / 2 - TitleROGO.image.height / 2 - 40;
	TitleROGO.IsDraw = FALSE;

	//メニュー
	strcpy_s(menu1.image.path, IMAGE_START_MENU1);
	menu1.image.handle = LoadGraph(menu1.image.path);	//読み込み
	if (menu1.image.handle == -1)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), IMAGE_START_MENU1, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(menu1.image.handle, &menu1.image.width, &menu1.image.height);
	menu1.image.x = GAME_WIDTH / 2 - menu1.image.width / 2;
	menu1.image.y = TitleROGO.image.y + TitleROGO.image.height + 20;
	menu1.IsDraw = FALSE;

	strcpy_s(menu2.image.path, IMAGE_START_MENU2);
	menu2.image.handle = LoadGraph(menu2.image.path);	//読み込み
	if (menu2.image.handle == -1)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), IMAGE_START_MENU2, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(menu2.image.handle, &menu2.image.width, &menu2.image.height);
	menu2.image.x = GAME_WIDTH / 2 - menu2.image.width / 2;
	menu2.image.y = TitleROGO.image.y + TitleROGO.image.height + 20;
	menu2.IsDraw = FALSE;

	//操作説明
	strcpy_s(Setsumei.image.path, IMAGE_SETSUMEI);
	Setsumei.image.handle = LoadGraph(Setsumei.image.path);	//読み込み
	if (Setsumei.image.handle == -1)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), IMAGE_SETSUMEI, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(Setsumei.image.handle, &Setsumei.image.width, &Setsumei.image.height);
	Setsumei.image.x = GAME_WIDTH / 2 - Setsumei.image.width / 2;
	Setsumei.image.y = GAME_HEIGHT / 2 - Setsumei.image.height / 2;
	Setsumei.IsDraw = FALSE;

	//黒画面
	strcpy_s(Loading.image.path, IMAGE_LOAD_BLACK);
	Loading.image.handle = LoadGraph(Loading.image.path);	//読み込み
	if (Loading.image.handle == -1)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), IMAGE_LOAD_BLACK, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(Loading.image.handle, &Loading.image.width, &Loading.image.height);
	Loading.image.x = GAME_WIDTH / 2 - Loading.image.width / 2;
	Loading.image.y = GAME_HEIGHT / 2 - Loading.image.height / 2;
	Loading.IsDraw = FALSE;

	//エンドロゴ
	strcpy_s(EndROGO.image.path, IMAGE_END_COMP_ROGO);
	EndROGO.image.handle = LoadGraph(EndROGO.image.path);
	if (EndROGO.image.handle == -1)
	{
		MessageBox(GetMainWindowHandle(), IMAGE_END_COMP_ROGO, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(EndROGO.image.handle, &EndROGO.image.width, &EndROGO.image.height);
	EndROGO.image.x = GAME_WIDTH / 2 - EndROGO.image.width / 2;
	EndROGO.image.y = GAME_HEIGHT / 2 - EndROGO.image.height / 2;
	EndROGO.IsDraw = FALSE;

	//背景画像
	strcpy_s(ImageBack[0].image.path, IMAGE_PLAY_BACK1);			//パスの設定
	strcpy_s(ImageBack[1].image.path, IMAGE_PLAY_BACK2);
	strcpy_s(ImageBack[2].image.path, IMAGE_PLAY_BACK1);
	strcpy_s(ImageBack[3].image.path, IMAGE_PLAY_BACK2);

	//画像を連続して読み込み
	for (int num = 0; num < IMAGE_NUM; num++)
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

	//背景画像
	strcpy_s(ImageFront[0].image.path, IMAGE_PLAY_FRONT1);			//パスの設定
	strcpy_s(ImageFront[1].image.path, IMAGE_PLAY_FRONT2);
	strcpy_s(ImageFront[2].image.path, IMAGE_PLAY_FRONT1);
	strcpy_s(ImageFront[3].image.path, IMAGE_PLAY_FRONT2);

	//画像を連続して読み込み
	for (int num = 0; num < IMAGE_NUM; num++)
	{
		ImageFront[num].image.handle = LoadGraph(ImageFront[num].image.path);
		if (ImageFront[num].image.handle == -1)
		{
			//エラーメッセージ表示
			MessageBox(GetMainWindowHandle(), IMAGE_PLAY_FRONT1, IMAGE_LOAD_ERR_TITLE, MB_OK);
			return FALSE;
		}
		//画像の幅と高さを取得
		GetGraphSize(ImageFront[num].image.handle, &ImageFront[num].image.width, &ImageFront[num].image.height);
	}
	//背景画像①の設定
	ImageFront[0].image.x = 0 + ImageFront[0].image.width * 0;				//xは原点から
	ImageFront[0].image.y = GAME_HEIGHT / 2 - ImageFront[0].image.height / 2;	//上下中央揃え
	ImageFront[0].IsDraw = FALSE;
	//背景画像②の設定
	ImageFront[1].image.x = 0 + ImageFront[0].image.width * 1;				//xは原点から
	ImageFront[1].image.y = GAME_HEIGHT / 2 - ImageFront[1].image.height / 2;	//上下中央揃え
	ImageFront[1].IsDraw = FALSE;
	//背景画像③の設定
	ImageFront[2].image.x = 0 + ImageFront[0].image.width * 2;				//xは原点から
	ImageFront[2].image.y = GAME_HEIGHT / 2 - ImageFront[2].image.height / 2;	//上下中央揃え
	ImageFront[2].IsDraw = FALSE;
	//背景画像④の設定
	ImageFront[3].image.x = 0 + ImageFront[0].image.width * 3;				//xは原点から
	ImageFront[3].image.y = GAME_HEIGHT / 2 - ImageFront[3].image.height / 2;	//上下中央揃え
	ImageFront[3].IsDraw = FALSE;

	
		//プレイヤーの画像
		//プレイヤー
		int PRes = LoadDivGraph(
			IMAGE_PLAYER_PATH,										//プレイヤーのパス
			PLAYER_DIV_NUM, PLAYER_DIV_TATE, PLAYER_DIV_YOKO,	//分割する数
			PLAYER_DIV_WIDTH, PLAYER_DIV_HEIGHT,				//分割する
			&chara.player[0].handle[0]);

		if (PRes == -1)
		{
			//エラー
			MessageBox(GetMainWindowHandle(), IMAGE_PLAYER_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
			return FALSE;
		}

		//幅と高さを取得
		GetGraphSize(chara.player[0].handle[0], &chara.player[0].width, &chara.player[0].height);

		//画像の情報を生成
	for (int cnt = 0; cnt < PLAYER_DIV_NUM; cnt++)
	{
		//パスをコピー
		strcpyDx(chara.player[cnt].path, TEXT(IMAGE_PLAYER_PATH));

		for (int i_num = 0; i_num < PLAYER_DIV_NUM; i_num++)
		{
			//ハンドルをコピー
			chara.player[cnt].handle[i_num] = chara.player[0].handle[i_num];
		}

		chara.player[cnt].width = chara.player[0].width;
		chara.player[cnt].height = chara.player[0].height;

		chara.player[cnt].x = GAME_WIDTH / 2 - chara.player[cnt].width / 2;		//左右中央揃え
		chara.player[cnt].y = GAME_HEIGHT / 2 - chara.player[cnt].height / 2;		//上下中央揃
		chara.CenterX = chara.player[cnt].x + chara.player[cnt].width / 2;	//画像の横の中心を探す
		chara.CenterY = chara.player[cnt].y + chara.player[cnt].height / 2;	//画像の縦の中心を探す
		chara.IsDraw = TRUE;
		chara.player[cnt].nowImageKind = 0;		//現在の画像の種類
		chara.player[cnt].speed = CHARA_SPEED_LOW;	//スピードを設定
	}

	//少年
	strcpy_s(boy.image.path, IMAGE_BOY_PATH);		//パスの設定
	boy.image.handle = LoadGraph(boy.image.path);	//読み込み
	if (boy.image.handle == -1)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), IMAGE_BOY_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(boy.image.handle, &boy.image.width, &boy.image.height);	//画像の幅と高さを取得
	boy.image.x = GAME_WIDTH - 115;		//左右中央揃え
	boy.image.y = 144;		//上下中央揃え
	boy.CenterX = boy.image.x + boy.image.width / 2;		//画像の横の中心を探す
	boy.CenterY = boy.image.y + boy.image.height / 2;		//画像の縦の中心を探す
	boy.IsDraw = FALSE;

	//テキストボックス
	strcpy_s(TextBox.image.path, IMAGE_TEXTBOX);
	TextBox.image.handle = LoadGraph(TextBox.image.path);	//読み込み
	if (TextBox.image.handle == -1)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), IMAGE_TEXTBOX, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(TextBox.image.handle, &TextBox.image.width, &TextBox.image.height);
	TextBox.image.x = GAME_WIDTH / 2 - TextBox.image.width / 2;
	TextBox.image.y = GAME_HEIGHT / 2 - TextBox.image.height / 2;

	//マップ
	int mapRes = LoadDivGraph(
		GAME_MAP_PATH,
		MAP_DIV_NUM, MAP_DIV_TATE, MAP_DIV_YOKO,
		MAP_DIV_WIDTH, MAP_DIV_HEIGHT,
		&mapChip.handle[0]);

	if (mapRes == -1)
	{
		MessageBox(GetMainWindowHandle(), GAME_MAP_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	GetGraphSize(mapChip.handle[0], &mapChip.width, &mapChip.height);

	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			mapDataInit[tate][yoko] = mapData[tate][yoko];

			map[tate][yoko].kind = mapData[tate][yoko];
			map[tate][yoko].num = 1;

			map[tate][yoko].width = mapChip.width;
			map[tate][yoko].height = mapChip.height;

			map[tate][yoko].x = yoko * map[tate][yoko].width;
			map[tate][yoko].y = tate * map[tate][yoko].height;
		}
	}

	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			//マップの当たり判定を設定
			mapColl[tate][yoko].left = (yoko + 0) * mapChip.width + 1;
			mapColl[tate][yoko].top = (tate + 0) * mapChip.height + 1;
			mapColl[tate][yoko].right = (yoko + 1) * mapChip.width - 1;
			mapColl[tate][yoko].bottom = (tate + 1) * mapChip.height - 1;
		}
	}

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
	for (int num = 0; num < IMAGE_NUM; num++)
	{
		DeleteGraph(ImageBack[num].image.handle);
	}

	for (int num = 0; num < IMAGE_NUM; num++)
	{
		DeleteGraph(ImageFront[num].image.handle);
	}

	for (int i_num = 0; i_num < PLAYER_DIV_NUM; i_num++) { DeleteGraph(chara.player[0].handle[i_num]); }

	for (int i_num = 0; i_num < MAP_DIV_NUM; i_num++) { DeleteGraph(mapChip.handle[i_num]); }

	DeleteGraph(boy.image.handle);
	DeleteGraph(TextBox.image.handle);
	DeleteGraph(Title2.image.handle);
	DeleteGraph(Title.image.handle);
	DeleteGraph(TitleROGO.image.handle);
	DeleteGraph(menu1.image.handle);
	DeleteGraph(menu2.image.handle);
	DeleteGraph(Setsumei.image.handle);
	DeleteGraph(Loading.image.handle);
	DeleteGraph(EndROGO.image.handle);
	DeleteGraph(StartBack.handle);
	DeleteGraph(EndBack.handle);

	return;
}

BOOL MY_LOAD_MUSIC(VOID)
{
	//BGM
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
	//SE
	strcpy_s(cursorSE.path, SE_CURSOR);
	cursorSE.handle = LoadSoundMem(cursorSE.path);
	if (cursorSE.handle == -1)
	{
		MessageBox(GetMainWindowHandle(), SE_CURSOR, MUSIC_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	strcpy_s(ketteiSE.path, SE_KETTEI);
	ketteiSE.handle = LoadSoundMem(ketteiSE.path);
	if (ketteiSE.handle == -1)
	{
		MessageBox(GetMainWindowHandle(), SE_KETTEI, MUSIC_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	strcpy_s(paperSE.path, SE_PAPER);
	paperSE.handle = LoadSoundMem(paperSE.path);
	if (paperSE.handle == -1)
	{
		MessageBox(GetMainWindowHandle(), SE_PAPER, MUSIC_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	strcpy_s(walkSE.path, SE_WALK);
	walkSE.handle = LoadSoundMem(walkSE.path);
	if (walkSE.handle == -1)
	{
		MessageBox(GetMainWindowHandle(), SE_WALK, MUSIC_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	strcpy_s(doorSE.path, SE_DOOR);
	doorSE.handle = LoadSoundMem(doorSE.path);
	if (doorSE.handle == -1)
	{
		MessageBox(GetMainWindowHandle(), SE_DOOR, MUSIC_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	return TRUE;
}

VOID MY_DELETE_MUSIC(VOID)
{
	DeleteSoundMem(StartBGM.handle);
	DeleteSoundMem(PlayBGM.handle);
	DeleteSoundMem(EndBGM.handle);
	DeleteSoundMem(cursorSE.handle);
	DeleteSoundMem(ketteiSE.handle);
	DeleteSoundMem(paperSE.handle);
	DeleteSoundMem(walkSE.handle);
	DeleteSoundMem(doorSE.handle);
}

BOOL MY_CHECK_MAP1_PLAYER_COLL(RECT player)
{
	//マップの当たり判定を設定する
	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			//プレイヤーとマップが当たっているとき
			if (MY_CHECK_RECT_COLL(player, mapColl[tate][yoko]) == TRUE)
			{
				//壁のときは、プレイヤーとマップが当たっている
				if (mapData[tate][yoko] == k || mapData[tate][yoko] == a ||
					mapData[tate][yoko] == m || mapData[tate][yoko] == b ||
					mapData[tate][yoko] == o || mapData[tate][yoko] == x ||
					mapData[tate][yoko] == e || mapData[tate][yoko] == d ||
					mapData[tate][yoko] == z || mapData[tate][yoko] == y ||
					mapData[tate][yoko] == g || mapData[tate][yoko] == r) { return TRUE; }
			}
		}
	}

	return FALSE;
}

BOOL MY_CHECK_CHARA_PLAYER_COLL(RECT player)
{
	if (MY_CHECK_RECT_COLL(player, boy.coll) == TRUE)
	{
		return TRUE;
	}

	return FALSE;
}

//領域の当たり判定をする関数
BOOL MY_CHECK_RECT_COLL(RECT a, RECT b)
{
	if (a.left < b.right &&
		a.top < b.bottom &&
		a.right > b.left &&
		a.bottom > b.top
		)
	{
		return TRUE;	//当たっている
	}

	return FALSE;		//当たっていない
}

INT TEXTBOX(VOID)
{
	int TextPtY = 0;
	if (chara.CenterY < GAME_HEIGHT / 2)
	{
		TextPtY = GAME_HEIGHT - TextBox.image.height;
		DrawGraph(0, TextPtY, TextBox.image.handle, TRUE);
	}
	else 
	{
		DrawGraph(0, TextPtY, TextBox.image.handle, TRUE);
	}

	return TextPtY;
}

VOID BOY_TEXT(BOOL IsMove)
{
	int TextPtX = TEXT_POSITION_X;
	int TextPtY = TEXT_POSITION_Y;
	if (IsMove == FALSE)
	{
		//TEXTBOX();
		if (TEXTBOX() != 0)
		{
			TextPtY = GAME_HEIGHT - TextBox.image.height + TEXT_POSITION_Y;
			DrawString(TextPtX, TextPtY, "BACKSPACEキーで閉じます", GetColor(255, 255, 255));
		}
		else
		{
			DrawString(TextPtX, TextPtY, "BACKSPACEキーで閉じます", GetColor(255, 255, 255));
		}
	}

	return;
}