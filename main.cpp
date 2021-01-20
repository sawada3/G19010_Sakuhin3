//########## �w�b�_�[�t�@�C���ǂݍ��� ##########
#include "DxLib.h"
#include "resource.h"

//########## �}�N����` ##########
#define GAME_WIDTH			800	//��ʂ̉��̑傫��
#define GAME_HEIGHT			600	//��ʂ̏c�̑傫��
#define GAME_COLOR			32	//��ʂ̃J���[�r�b�g

#define GAME_WINDOW_BAR		0	//�^�C�g���o�[�̓f�t�H���g�ɂ���
#define GAME_WINDOW_NAME	"GAME TITLE"	//�E�B���h�E�̃^�C�g��

#define GAME_FPS			60	//FPS�̐��l	

#define PATH_MAX			255
#define NAME_MAX			255

//�t�H���g
#define FONT_TANU_PATH			TEXT(".\\FONT\\TanukiMagic.ttf")	//�t�H���g�̏ꏊ
#define FONT_TANU_NAME			TEXT("���ʂ������}�W�b�N")			//�t�H���g�̖��O

//�摜�̃p�X
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

#define TEXT_POSITION_X			224	//�����\���ʒuX
#define TEXT_POSITION_Y			32	//�����\���ʒuY

//BGM
#define MUSIC_START_PATH		TEXT(".\\MUSIC\\���@�g���ƐU��q���v.mp3")
#define MUSIC_PLAY_PATH			TEXT(".\\MUSIC\\�N�����Ȃ����i.mp3")
#define MUSIC_END_PATH			TEXT(".\\MUSIC\\�A�N�A�̗��H.mp3")
//SE
#define SE_CURSOR				TEXT(".\\MUSIC\\se_maoudamashii_system48.mp3")
#define SE_KETTEI				TEXT(".\\MUSIC\\se_maoudamashii_system47.mp3")
#define SE_PAPER				TEXT(".\\MUSIC\\se_maoudamashii_se_paper01.mp3")
#define SE_WALK					TEXT(".\\MUSIC\\se_maoudamashii_se_footstep02.mp3")
#define SE_DOOR					TEXT(".\\MUSIC\\�h�A�E�J����05.mp3")


//�}�b�v
#define GAME_MAP_TATE_MAX	10
#define GAME_MAP_YOKO_MAX	13
#define GAME_MAP_KIND_MAX	5

#define GAME_MAP_PATH		TEXT(".\\IMAGE\\MAP\\�}�b�v.png")

#define MAP_DIV_WIDTH		64
#define MAP_DIV_HEIGHT		64
#define MAP_DIV_TATE		10
#define MAP_DIV_YOKO		4
#define MAP_DIV_NUM MAP_DIV_TATE * MAP_DIV_YOKO

//�G���[���b�Z�[�W
#define FONT_INSTALL_ERR_TITLE	TEXT("�t�H���g�C���X�g�[���G���[")
#define FONT_CREATE_ERR_TITLE	TEXT("�t�H���g�쐬�G���[")

#define IMAGE_LOAD_ERR_TITLE	TEXT("�摜�ǂݍ��݃G���[")

#define MUSIC_LOAD_ERR_TITLE	TEXT("���y�ǂݍ��݃G���[")

#define START_ERR_TITLE			TEXT("�X�^�[�g�ʒu�G���[")
#define START_ERR_CAPTION		TEXT("�X�^�[�g�ʒu�����܂��Ă��܂���")

#define GOAL_ERR_TITLE			TEXT("�S�[���ʒu�G���[")
#define GOAL_ERR_CAPTION		TEXT("�S�[���ʒu�����܂��Ă��܂���")

#define ESC_TITLE				TEXT("�Q�[�����f")
#define ESC_CAPTION				TEXT("�Q�[�����f���A�^�C�g����ʂɖ߂�܂����H")

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
};	//�Q�[���̃V�[��

enum GAME_END {
	GAME_END_COMP,
	GAME_END_FAIL
};

enum CHARA_SPEED {
	CHARA_SPEED_LOW = 1,
	CHARA_SPEED_MIDI = 2,
	CHARA_SPEED_HIGH = 3
};	//�L�����X�s�[�h

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

//int�^��POINT�\����
typedef struct STRUCT_I_POINT
{
	int x = -1;	//���W��������
	int y = -1;	//���W��������
}iPOINT;

//�t�H���g�\����
typedef struct STRUCT_FONT
{
	char path[PATH_MAX];	//�p�X
	char name[NAME_MAX];	//�t�H���g��
	int handle;					//�n���h��
	int size;					//�傫��
	int bold;					//����
	int type;					//�^�C�v
	//���^�C�v�́Ahttps://dxlib.xsrv.jp/function/dxfunc_graph2.html#R17N10�@���Q��

}FONT;

typedef struct STRUCT_IMAGE
{
	char path[PATH_MAX];		//�p�X
	int handle;					//�n���h��
	int x;						//X�ʒu
	int y;						//Y�ʒu
	int width;					//��
	int height;					//����
}IMAGE;	//�摜�\����

typedef struct STRUCT_MUSIC
{
	char path[PATH_MAX];
	int handle;
}MUSIC;	//���y�\����

typedef struct STRUCT_PLAYER
{
	char path[PATH_MAX];
	int handle[PLAYER_DIV_NUM];
	int speed;		//����
	int x;
	int y;
	int width;
	int height;

	iPOINT collBeforePt;

	int nowImageKind;					//���݂̉摜
	int changeImageCnt;					//�摜��ς��邽�߂̃J�E���g
}PLAYER;

typedef struct STRUCT_CHARA
{
	IMAGE image;
	int CenterX;	//���SX
	int CenterY;	//���SY
	RECT coll;
	BOOL IsDraw;

	PLAYER player[PLAYER_DIV_NUM];

}CHARA;	//�L�����N�^�[�\����

typedef struct STRUCT_IMAGE_DES
{
	IMAGE image;		//IMAGE�\����
	BOOL IsDraw;		//�\���ł��邩
}IMAGE_DES;	//�摜�̍\����

//########## �O���[�o���ϐ� ##########
//FPS�֘A
int StartTimeFps;				//����J�n����
int CountFps;					//�J�E���^
float CalcFps;					//�v�Z����
int SampleNumFps = GAME_FPS;	//���ς����T���v����

//�L�[�{�[�h�̓��͂��擾
char AllKeyState[256] = { '\0' };			//���ׂẴL�[�̏�Ԃ�����
char OldAllKeyState[256] = { '\0' };	//���ׂẴL�[�̏��(���O)������

FONT FontTanu32;	//���ʂ������}�W�b�N�F�傫��32�@�̃t�H���g�\����

int GameScene;		//�Q�[���V�[�����Ǘ�
int menu;
int GameEndKind;

RECT GoalRect = { -1,-1,-1,-1 };
RECT ReturnRect = { -1,-1,-1,-1 };

CHARA chara;	//�v���C���[
CHARA boy;		//���N

//�����蔻��
RECT PlayerRect;	//�v���C���[
RECT boyRect;		//���N

//�摜
IMAGE_DES ImageBack[IMAGE_NUM];		//�Q�[���̔w�i
IMAGE_DES ImageFront[IMAGE_NUM];	//
IMAGE_DES TextBox;	//�e�L�X�g�{�b�N�X
IMAGE_DES Title2;	//�^�C�g�����S�P
IMAGE_DES Title;	//�^�C�g�����S�Q
IMAGE_DES TitleROGO;	//�^�C�g�����S�R
IMAGE_DES menu1;	//���j���[(�͂��߂�)
IMAGE_DES menu2;	//���j���[(�������)
IMAGE_DES Setsumei;	//�������
IMAGE_DES Loading;	//�ԗ��ړ����̍����摜
IMAGE_DES EndROGO;	//�G���h���S
IMAGE StartBack;	//�X�^�[�g�w�i
IMAGE EndBack;		//�G���h�w�i

BOOL IsMove = FALSE;	//�v���C���[�������邩
BOOL Walk = FALSE;		//�v���C���[�������Ă��邩
//��b�t���O
BOOL boyFlg = FALSE;	//���N

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

//########## �v���g�^�C�v�錾 ##########
VOID MY_FPS_UPDATE(VOID);			//FPS�l���v���A�X�V����
VOID MY_FPS_DRAW(VOID);				//FPS�l��`�悷��
VOID MY_FPS_WAIT(VOID);				//FPS�l���v�����A�҂�

VOID MY_ALL_KEYDOWN_UPDATE(VOID);	//�L�[�̓��͏�Ԃ��X�V����
BOOL MY_KEY_DOWN(int);				//�L�[�������Ă��邩�A�L�[�R�[�h�Ŕ��f����
BOOL MY_KEY_UP(int);				//�L�[�������グ�����A�L�[�R�[�h�Ŕ��f����
BOOL MY_KEYDOWN_KEEP(int, int);		//�L�[�����������Ă��邩�A�L�[�R�[�h�Ŕ��f����

BOOL MY_FONT_INSTALL_ONCE(VOID);	//�t�H���g�����̃\�t�g�p�ɁA�ꎞ�I�ɃC���X�g�[��
VOID MY_FONT_UNINSTALL_ONCE(VOID);	//�t�H���g�����̃\�t�g�p�ɁA�ꎞ�I�ɃA���C���X�g�[��
BOOL MY_FONT_CREATE(VOID);			//�t�H���g���쐬����
VOID MY_FONT_DELETE(VOID);			//�t�H���g���폜����

VOID MY_START(VOID);		//�X�^�[�g���
VOID MY_START_PROC(VOID);	//�X�^�[�g��ʂ̏���
VOID MY_START_DRAW(VOID);	//�X�^�[�g��ʂ̕`��

VOID MY_PLAY(VOID);			//�v���C���
VOID MY_PLAY_PROC(VOID);	//�v���C��ʂ̏���
VOID MY_PLAY_DRAW(VOID);	//�v���C��ʂ̕`��

VOID MY_END(VOID);			//�G���h���
VOID MY_END_PROC(VOID);		//�G���h��ʂ̏���
VOID MY_END_DRAW(VOID);		//�G���h��ʂ̕`��

BOOL MY_LOAD_IMAGE(VOID);		//�摜���܂Ƃ߂ēǂݍ��ފ֐�
VOID MY_DELETE_IMAGE(VOID);		//�摜���܂Ƃ߂č폜����֐�

BOOL MY_LOAD_MUSIC(VOID);		//���y���܂Ƃ߂ēǂݍ��ފ֐�
VOID MY_DELETE_MUSIC(VOID);		//���y���܂Ƃ߂č폜����֐�

BOOL MY_CHECK_MAP1_PLAYER_COLL(RECT);
BOOL MY_CHECK_CHARA_PLAYER_COLL(RECT);
BOOL MY_CHECK_RECT_COLL(RECT, RECT);

INT TEXTBOX(VOID);
VOID BOY_TEXT(BOOL);

//########## �v���O�����ōŏ��Ɏ��s�����֐� ##########
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);								//�E�B���h�E���[�h�ɐݒ�
	SetGraphMode(GAME_WIDTH, GAME_HEIGHT, GAME_COLOR);	//�w��̐��l�ŃE�B���h�E��\������
	SetWindowStyleMode(GAME_WINDOW_BAR);				//�^�C�g���o�[�̓f�t�H���g�ɂ���
	SetMainWindowText(TEXT(GAME_WINDOW_NAME));			//�E�B���h�E�̃^�C�g���̕���
	SetAlwaysRunFlag(TRUE);								//��A�N�e�B�u�ł����s����
	SetWindowIconID(IDI_ICON1);							//�A�C�R���t�@�C����Ǎ�

	if (DxLib_Init() == -1) { return -1; }	//�c�w���C�u��������������

	//�摜��ǂݍ���
	if (MY_LOAD_IMAGE() == FALSE) { return -1; }
	//���y��ǂݍ���
	if (MY_LOAD_MUSIC() == FALSE) { return -1; }

	//�t�H���g���ꎞ�I�ɃC���X�g�[��
	if (MY_FONT_INSTALL_ONCE() == FALSE) { return -1; }
	//�t�H���g�n���h�����쐬
	if (MY_FONT_CREATE() == FALSE) { return -1; }

	SetMouseDispFlag(TRUE);			//�}�E�X�J�[�\����\��	

	GameScene = GAME_SCENE_START;	//�Q�[���V�[���̓X�^�[�g��ʂ���

	SetDrawScreen(DX_SCREEN_BACK);	//Draw�n�֐��͗���ʂɕ`��

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

	//�������[�v
	while (TRUE)
	{
		if (ProcessMessage() != 0) { break; }	//���b�Z�[�W�����̌��ʂ��G���[�̂Ƃ��A�����I��
		if (ClearDrawScreen() != 0) { break; }	//��ʂ������ł��Ȃ������Ƃ��A�����I��

		MY_ALL_KEYDOWN_UPDATE();				//�����Ă���L�[��Ԃ��擾

		MY_FPS_UPDATE();	//FPS�̏���[�X�V]
		
		//�V�[�����Ƃɏ������s��
		switch (GameScene)
		{
		case GAME_SCENE_START:
			MY_START();	//�X�^�[�g���
			break;
		case GAME_SCENE_PLAY:
			MY_PLAY();	//�v���C���
			break;
		case GAME_SCENE_END:
			MY_END();	//�G���h���
			break;
		}

		MY_FPS_DRAW();		//FPS�̏���[�`��]

		ScreenFlip();		//���j�^�̃��t���b�V�����[�g�̑����ŗ���ʂ��ĕ`��

		MY_FPS_WAIT();		//FPS�̏���[�҂�]
	}

	//�t�H���g�n���h����j��
	MY_FONT_DELETE();

	//�ꎞ�I�ɃC���X�g�[�������t�H���g���A���C���X�g�[��
	MY_FONT_UNINSTALL_ONCE();

	//�摜�n���h����j��
	MY_DELETE_IMAGE();

	//���y�n���h����j��
	MY_DELETE_MUSIC();

	DxLib_End();	//�c�w���C�u�����g�p�̏I������

	return 0;
}

//########## FPS�l���v���A�X�V����֐� ##########
VOID MY_FPS_UPDATE(VOID)
{
	if (CountFps == 0) //1�t���[���ڂȂ玞�����L��
	{
		StartTimeFps = GetNowCount();
	}

	if (CountFps == SampleNumFps) //60�t���[���ڂȂ畽�ς��v�Z
	{
		int now = GetNowCount();
		//���݂̎��Ԃ���A0�t���[���ڂ̎��Ԃ������AFPS�̐��l�Ŋ��遁1FPS�ӂ�̕��ώ��Ԃ��v�Z�����
		CalcFps = 1000.f / ((now - StartTimeFps) / (float)SampleNumFps);
		CountFps = 0;
		StartTimeFps = now;
	}
	CountFps++;
	return;
}

//########## FPS�l��`�悷��֐� ##########
VOID MY_FPS_DRAW(VOID)
{
	//�������`��
	DrawFormatString(0, GAME_HEIGHT - 20, GetColor(255, 255, 255), "FPS:%.1f", CalcFps);
	return;
}

//########## FPS�l���v�����A�҂֐� ##########
VOID MY_FPS_WAIT(VOID)
{
	int resultTime = GetNowCount() - StartTimeFps;					//������������
	int waitTime = CountFps * 1000 / GAME_FPS - resultTime;	//�҂ׂ�����

	if (waitTime > 0)		//�w���FPS�l���������ꍇ
	{
		WaitTimer(waitTime);	//�҂�
	}
	return;
}

//########## �L�[�̓��͏�Ԃ��X�V����֐� ##########
VOID MY_ALL_KEYDOWN_UPDATE(VOID)
{
	//�Q�l�Fhttps://dxlib.xsrv.jp/function/dxfunc_input.html

	char TempKey[256];	//�ꎞ�I�ɁA���݂̃L�[�̓��͏�Ԃ��i�[����

	//���O�̃L�[���͂��Ƃ��Ă���
	for (int i = 0; i < 256; i++)
	{
		OldAllKeyState[i] = AllKeyState[i];
	}

	GetHitKeyStateAll(TempKey); // �S�ẴL�[�̓��͏�Ԃ𓾂�

	for (int i = 0; i < 256; i++)
	{
		if (TempKey[i] != 0)	//������Ă���L�[�̃L�[�R�[�h�������Ă���Ƃ�
		{
			AllKeyState[i]++;	//������Ă���
		}
		else
		{
			AllKeyState[i] = 0;	//������Ă��Ȃ�
		}
	}
	return;
}

//�L�[�������Ă��邩�A�L�[�R�[�h�Ŕ��f����
//���@���Fint�F�L�[�R�[�h�FKEY_INPUT_???
BOOL MY_KEY_DOWN(int KEY_INPUT_)
{
	//�L�[�R�[�h�̃L�[�������Ă��鎞
	if (AllKeyState[KEY_INPUT_] != 0)
	{
		return TRUE;	//�L�[�������Ă���
	}
	else
	{
		return FALSE;	//�L�[�������Ă��Ȃ�
	}
}

//�L�[�������グ�����A�L�[�R�[�h�Ŕ��f����
//���@���Fint�F�L�[�R�[�h�FKEY_INPUT_???
BOOL MY_KEY_UP(int KEY_INPUT_)
{
	if (OldAllKeyState[KEY_INPUT_] >= 1	//���O�͉����Ă���
		&& AllKeyState[KEY_INPUT_] == 0)	//���͉����Ă��Ȃ��Ƃ�
	{
		return TRUE;	//�L�[�������グ�Ă���
	}
	else
	{
		return FALSE;	//�L�[�������グ�Ă��Ȃ�
	}
}

//�L�[�����������Ă��邩�A�L�[�R�[�h�Ŕ��f����
//���@���Fint�F�L�[�R�[�h�FKEY_INPUT_???
//���@���Fint�F�L�[�����������鎞��
BOOL MY_KEYDOWN_KEEP(int KEY_INPUT_, int DownTime)
{
	//���������鎞��=�b���~FPS�l
	//��j60FPS�̃Q�[���ŁA1�b�ԉ���������Ȃ�A1�b�~60FPS
	int UpdateTime = DownTime * GAME_FPS;

	if (AllKeyState[KEY_INPUT_] > UpdateTime)
	{
		return TRUE;	//���������Ă���
	}
	else
	{
		return FALSE;	//���������Ă��Ȃ�
	}
}

//�t�H���g�����̃\�t�g�p�ɁA�ꎞ�I�ɃC���X�g�[��
BOOL MY_FONT_INSTALL_ONCE(VOID)
{
	//�t�H���g���ꎞ�I�ɓǂݍ���(WinAPI)
	if (AddFontResourceEx(FONT_TANU_PATH, FR_PRIVATE, NULL) == 0)
	{
		//�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), FONT_TANU_NAME, FONT_INSTALL_ERR_TITLE, MB_OK);
		return FALSE;
	}

	return TRUE;
}

//�t�H���g�����̃\�t�g�p�ɁA�ꎞ�I�ɃA���C���X�g�[��
VOID MY_FONT_UNINSTALL_ONCE(VOID)
{
	//�ꎞ�I�ɓǂݍ��񂾃t�H���g���폜(WinAPI)
	RemoveFontResourceEx(FONT_TANU_PATH, FR_PRIVATE, NULL);

	return;
}

//�t�H���g��ǂݍ��ފ֐�
//���@���Fconst char *�F�ǂݍ��ރt�H���g�̖��O
//���@���Fint�@�F�t�H���g�̑傫��
//���@���Fint�@�F�t�H���g�̑���
//���@���Fint�@�F�t�H���g�̃^�C�v
//�߂�l�F�Ȃ����ύX���߂�l�FBOOL�F�G���[���FFALSE
BOOL MY_FONT_CREATE(VOID)
{
	//���������ʂ������}�W�b�N�̃t�H���g���쐬������

	//�t�H���g�f�[�^���쐬
	strcpy_s(FontTanu32.path, sizeof(FontTanu32.path), FONT_TANU_PATH);	//�p�X���R�s�[
	strcpy_s(FontTanu32.name, sizeof(FontTanu32.name), FONT_TANU_NAME);	//�t�H���g�����R�s�[
	FontTanu32.handle = -1;								//�n���h����������
	FontTanu32.size = 32;								//�T�C�Y��32
	FontTanu32.bold = 1;								//����1
	FontTanu32.type = DX_FONTTYPE_ANTIALIASING_EDGE;	//�A���`�G�C���A�V���O�t���̃t�H���g

	//�t�H���g�n���h���쐬
	FontTanu32.handle = CreateFontToHandle(FontTanu32.name, FontTanu32.size, FontTanu32.bold, FontTanu32.type);
	//�t�H���g�n���h���쐬�ł��Ȃ��Ƃ��A�G���[
	if (FontTanu32.handle == -1) { MessageBox(GetMainWindowHandle(), FONT_TANU_NAME, FONT_CREATE_ERR_TITLE, MB_OK); return FALSE; }

	//���������ʂ������}�W�b�N�̃t�H���g���쐬������

	return TRUE;
}

//�t�H���g���폜����֐�
VOID MY_FONT_DELETE(VOID)
{
	//�t�H���g�f�[�^���폜
	DeleteFontToHandle(FontTanu32.handle);	//�t�H���g�̃n���h�����폜

	return;
}

//�X�^�[�g���
VOID MY_START(VOID)
{
	MY_START_PROC();	//�X�^�[�g��ʂ̏���
	MY_START_DRAW();	//�X�^�[�g��ʂ̕`��

	return;
}

//�X�^�[�g��ʂ̏���
VOID MY_START_PROC(VOID)
{
	if (CheckSoundMem(StartBGM.handle) == 0)
	{
		SetMouseDispFlag(FALSE);			//�}�E�X�J�[�\�����\��

		ChangeVolumeSoundMem(255 * 50 / 100, StartBGM.handle);

		//BGM�𗬂�
		//DX_PLAYTYPE_NORMAL:�@�m�[�}���Đ�
		//DX_PLAYTYPE_BACK  : �o�b�N�O���E���h�Đ�
		//DX_PLAYTYPE_LOOP  : ���[�v�Đ�
		PlaySoundMem(StartBGM.handle, DX_PLAYTYPE_LOOP);
	}

	//�^�C�g�����S
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
		//���j���[�̕\��
		//0:�͂��߂�
		//1:�������
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
		//�G���^�[�L�[����������A�v���C�V�[���ֈړ�����
		if (MY_KEY_DOWN(KEY_INPUT_RETURN) == TRUE)
		{
			SetMouseDispFlag(FALSE);

			if (CheckSoundMem(ketteiSE.handle) == 0)
			{
				PlaySoundMem(ketteiSE.handle, DX_PLAYTYPE_BACK);
			}

			//BGM������Ă���Ȃ�
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
	//�������
	if (menu2.IsDraw == TRUE)
	{
		//�G���^�[�L�[����������
		if (MY_KEY_DOWN(KEY_INPUT_RETURN) == TRUE)
		{
			//��������摜�\��
			Setsumei.IsDraw = TRUE;
			//���̉�
			if (CheckSoundMem(paperSE.handle) == 0)
			{
				PlaySoundMem(paperSE.handle, DX_PLAYTYPE_BACK);
			}
		}
		if (Setsumei.IsDraw == TRUE)
		{
			//BACKSPACE�L�[����������
			if (MY_KEY_DOWN(KEY_INPUT_BACK) == TRUE)
			{
				//�摜���\��
				Setsumei.IsDraw = FALSE;
			}
		}
	}

	return;
}

//�X�^�[�g��ʂ̕`��
VOID MY_START_DRAW(VOID)
{
	//�w�i��`��
	DrawGraph(StartBack.x, StartBack.y, StartBack.handle, TRUE);

	//�^�C�g�����S
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

	//���j���[
	if (menu1.IsDraw == TRUE)
	{
		DrawGraph(menu1.image.x, menu1.image.y, menu1.image.handle, TRUE);
	}
	if (menu2.IsDraw == TRUE)
	{
		DrawGraph(menu2.image.x, menu2.image.y, menu2.image.handle, TRUE);
	}
	
	//�������
	if (Setsumei.IsDraw == TRUE)
	{
		DrawGraph(Setsumei.image.x, Setsumei.image.y, Setsumei.image.handle, TRUE);
	}

	return;
}

//�v���C���
VOID MY_PLAY(VOID)
{
	MY_PLAY_PROC();	//�v���C��ʂ̏���
	MY_PLAY_DRAW();	//�v���C��ʂ̕`��

	return;
}

//�v���C��ʂ̏���
VOID MY_PLAY_PROC(VOID)
{
	if (CheckSoundMem(PlayBGM.handle) == 0)
	{
		ChangeVolumeSoundMem(255 * 50 / 100, PlayBGM.handle);

		//BGM�𗬂�
		//DX_PLAYTYPE_NORMAL:�@�m�[�}���Đ�
		//DX_PLAYTYPE_BACK  : �o�b�N�O���E���h�Đ�
		//DX_PLAYTYPE_LOOP  : ���[�v�Đ�
		PlaySoundMem(PlayBGM.handle, DX_PLAYTYPE_LOOP);
	}

	//ESCAPE�L�[����������
	if (MY_KEY_DOWN(KEY_INPUT_ESCAPE) == TRUE)
	{
		SetMouseDispFlag(TRUE);		//�}�E�X�J�[�\���\��

		//�^�C�g���ɖ߂�܂����@YESNO
		int Ret = MessageBox(GetMainWindowHandle(), ESC_CAPTION, ESC_TITLE, MB_YESNO);

		//YES��I�񂾂Ƃ�
		if (Ret == IDYES)
		{
			//BGM���~�߂�
			if (CheckSoundMem(PlayBGM.handle) != 0)
			{
				StopSoundMem(PlayBGM.handle);
			}

			GameScene = GAME_SCENE_START;	//�X�^�[�g��ʂɖ߂�

			return;
		}
		//NO��I�񂾂Ƃ�
		else if (Ret == IDNO)
		{
			SetMouseDispFlag(FALSE);	//�}�E�X�J�[�\����\��
		}
	}

	for (int cnt = 0; cnt < PLAYER_DIV_NUM; cnt++)
	{
		//�v���C���[�ړ�
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

		//�L�����̓����蔻��
		//�v���C���[
		chara.coll.left = chara.CenterX - mapChip.width / 2 + 9;
		chara.coll.top = chara.CenterY + mapChip.height / 2;
		chara.coll.right = chara.CenterX + mapChip.width / 2 - 7;
		chara.coll.bottom = chara.CenterY + mapChip.height + 17;
		//���N
		boy.coll.left = boy.CenterX - mapChip.width / 2 + 9;
		boy.coll.top = boy.CenterY + mapChip.height / 2;
		boy.coll.right = boy.CenterX + mapChip.width / 2 - 7;
		boy.coll.bottom = boy.CenterY + mapChip.height + 17;

		//��b�p�����蔻��
		//.coll��肿����Ƃ����L���Ȃ��Ă�
		//�v���C���[
		PlayerRect.left = chara.coll.left - 5;
		PlayerRect.top = chara.coll.top - 5;
		PlayerRect.right = chara.coll.right + 5;
		PlayerRect.bottom = chara.coll.bottom + 5;
		//���N
		boyRect.left = boy.coll.left - 5;
		boyRect.top = boy.coll.top - 5;
		boyRect.right = boy.coll.right + 5;
		boyRect.bottom = boy.coll.bottom + 5;

		IsMove = TRUE;	//�v���C���[������

		//�v���C���[�ƃ}�b�v�����������Ƃ�
		if (MY_CHECK_MAP1_PLAYER_COLL(chara.coll) == TRUE)
		{
			chara.CenterX = chara.player[cnt].collBeforePt.x;
			chara.CenterY = chara.player[cnt].collBeforePt.y;

			IsMove = FALSE;	//�v���C���[�����Ȃ�
		}
		//�v���C���[�Ƃ��̑��L����
		if (MY_CHECK_CHARA_PLAYER_COLL(chara.coll) == TRUE)
		{
			chara.CenterX = chara.player[cnt].collBeforePt.x;
			chara.CenterY = chara.player[cnt].collBeforePt.y;

			IsMove = FALSE;
		}

		//��b
		if (MY_CHECK_RECT_COLL(PlayerRect, boyRect) == TRUE)
		{
			if (MY_KEY_DOWN(KEY_INPUT_RETURN) == TRUE)
			{
				boyFlg = TRUE;		//��b�t���O
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

		//�v���C���[��������Ƃ�
		if (IsMove == TRUE)
		{
			//�v���C���[�̈ʒu�ɒu��������
			chara.player[cnt].x = chara.CenterX - chara.player[cnt].width / 2;
			chara.player[cnt].y = chara.CenterY - chara.player[cnt].height / 2;
			//�������Ă��Ȃ��Ƃ��̍��W���擾
			chara.player[cnt].collBeforePt.x = chara.CenterX;
			chara.player[cnt].collBeforePt.y = chara.CenterY;

			//�������L�[�ɉ����ĉ摜��؂�ւ�
			//�O�F�������O
			//�P�F�E�����O
			//�Q�F��������
			//�R�F�E������
			if (MY_KEY_DOWN(KEY_INPUT_LEFT) == TRUE)	//��
			{
				if (CheckSoundMem(walkSE.handle) == 0)
				{
					PlaySoundMem(walkSE.handle, DX_PLAYTYPE_BACK);
				}

				chara.player[cnt].nowImageKind = 0;
				Walk = TRUE;
			}
			if (MY_KEY_DOWN(KEY_INPUT_RIGHT) == TRUE)	//�E
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
			//���Ɉړ�����Ƃ�
			if (MY_KEY_DOWN(KEY_INPUT_DOWN) == TRUE)
			{
				if (CheckSoundMem(walkSE.handle) == 0)
				{
					PlaySoundMem(walkSE.handle, DX_PLAYTYPE_BACK);
				}

				//���̉摜��0�Ȃ�
				if (chara.player[cnt].nowImageKind == 0 ||
					chara.player[cnt].nowImageKind == 2)
				{
					chara.player[cnt].nowImageKind = 0;
				}
				//����ȊO(�Por�R)�Ȃ�
				else
				{
					chara.player[cnt].nowImageKind = 1;
				}
			}
			//��Ɉړ�����Ƃ�
			if (MY_KEY_DOWN(KEY_INPUT_UP) == TRUE)
			{
				if (CheckSoundMem(walkSE.handle) == 0)
				{
					PlaySoundMem(walkSE.handle, DX_PLAYTYPE_BACK);
				}

				//���̉摜��0�Ȃ�
				if (chara.player[cnt].nowImageKind == 0 ||
					chara.player[cnt].nowImageKind == 2)
				{
					chara.player[cnt].nowImageKind = 0;
				}
				//����ȊO(�Por�R)�Ȃ�
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
					//2�Ԗڈȍ~�̎ԗ��Ȃ�
					if (map[tate][yoko].num > 1)
					{
						//�O�̎ԗ��ɂǂ���
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
					//���̎ԗ��ɐi��
					map[tate][yoko].num++;

					if (CheckSoundMem(doorSE.handle) == 0)
					{
						PlaySoundMem(doorSE.handle, DX_PLAYTYPE_BACK);
					}

					//�Ō�̎ԗ��ɂ���Ȃ�
					if (map[tate][yoko].num > GAME_MAP_KIND_MAX)
					{
						//���y���~�߂�
						if (CheckSoundMem(PlayBGM.handle) != 0)
						{
							StopSoundMem(PlayBGM.handle);
						}

						GameEndKind = GAME_END_COMP;
						//�G���h��ʂ�
						GameScene = GAME_SCENE_END;

						return;
					}

					chara.CenterX = ReStartPt.x;
					chara.CenterY = ReStartPt.y;
				}
			}
		}
	}

	//�w�i�摜�𓮂���
	for (int num = 0; num < IMAGE_NUM; num++)
	{
		//�摜���ړ�������
		ImageBack[num].image.x++;

		if (ImageBack[num].IsDraw == FALSE)
		{
			//�w�i�摜����ʓ��ɂ���Ƃ�
			if (ImageBack[num].image.x + ImageBack[num].image.width > 0)
			{
				ImageBack[num].IsDraw = TRUE;	//�摜��`�悷��
			}
		}
		//�w�i�摜����ʂ�ʂ�z�����Ƃ�
		if (ImageBack[num].image.x > GAME_WIDTH)
		{
			ImageBack[num].image.x = 0 - ImageBack[0].image.width * 3;	//�摜�̍����Q���A���Ɉړ�������
			ImageBack[num].IsDraw = FALSE;								//�摜��`�悵�Ȃ�
		}
	}

	for (int num = 0; num < IMAGE_NUM; num++)
	{
		//�摜���ړ�������
		ImageFront[num].image.x--;

		if (ImageFront[num].IsDraw == FALSE)
		{
			//�w�i�摜����ʓ��ɂ���Ƃ�
			if (ImageFront[num].image.x < GAME_WIDTH)
			{
				ImageFront[num].IsDraw = TRUE;	//�摜��`�悷��
			}
		}
		//�w�i�摜����ʂ�ʂ�z�����Ƃ�
		if (ImageFront[num].image.x + ImageFront[num].image.width < 0)
		{
			ImageFront[num].image.x = 0 + ImageFront[0].image.width * 3;	//�摜�̕��Q���A���Ɉړ�������
			ImageFront[num].IsDraw = FALSE;								//�摜��`�悵�Ȃ�
		}
	}

	return;
}

//�v���C��ʂ̕`��
VOID MY_PLAY_DRAW(VOID)
{
	//�v���C��ʂ̔w�i��`��
	for (int num = 0; num < IMAGE_NUM; num++)
	{
		if (ImageBack[num].IsDraw == TRUE)
		{
			DrawGraph(ImageBack[num].image.x, ImageBack[num].image.y, ImageBack[num].image.handle, TRUE);
		}
	}
	//�}�b�v��`��
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

	//�����蔻��̕`��i�f�o�b�O�p�j
	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			//�ǂȂ��
			if (mapData[tate][yoko] == k || mapData[tate][yoko] == a ||
				mapData[tate][yoko] == m || mapData[tate][yoko] == b ||
				mapData[tate][yoko] == o || mapData[tate][yoko] == x ||
				mapData[tate][yoko] == e || mapData[tate][yoko] == d ||
				mapData[tate][yoko] == z || mapData[tate][yoko] == y)
			{
				DrawBox(mapColl[tate][yoko].left, mapColl[tate][yoko].top, mapColl[tate][yoko].right, mapColl[tate][yoko].bottom, GetColor(0, 0, 255), FALSE);
			}

			//�ʘH�Ȃ��
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

	//�v���C���[�`��
	for (int cnt = 0; cnt < PLAYER_DIV_NUM; cnt++)
	{
		if (chara.IsDraw == TRUE)
		{
			DrawGraph(
				chara.player[cnt].x,
				chara.player[cnt].y,
				chara.player[cnt].handle[chara.player[cnt].nowImageKind],
				TRUE);

			//�v���C���[�̓����蔻��`��(�f�o�b�O�p)
			DrawBox(chara.coll.left, chara.coll.top, chara.coll.right, chara.coll.bottom, GetColor(255, 0, 0), FALSE);
		}
	}

	DrawString(0, 0, "���L�[�ňړ��EESCAPE�L�[�ŃX�^�[�g�ɖ߂�", GetColor(255, 255, 255));

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
			DrawFormatString(0, 20, GetColor(255, 255, 255), "���݂̃}�b�v�F%d", map[tate][yoko].num);
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

//�G���h���
VOID MY_END(VOID)
{
	MY_END_PROC();	//�G���h��ʂ̏���
	MY_END_DRAW();	//�G���h��ʂ̕`��
	return;
}

//�G���h��ʂ̏���
VOID MY_END_PROC(VOID)
{
	if (CheckSoundMem(EndBGM.handle) == 0)
	{
		ChangeVolumeSoundMem(255 * 50 / 100, EndBGM.handle);

		//BGM�𗬂�
		//DX_PLAYTYPE_NORMAL:�@�m�[�}���Đ�
		//DX_PLAYTYPE_BACK  : �o�b�N�O���E���h�Đ�
		//DX_PLAYTYPE_LOOP  : ���[�v�Đ�
		PlaySoundMem(EndBGM.handle, DX_PLAYTYPE_LOOP);
	}

	//�G�X�P�[�v�L�[����������A�X�^�[�g�V�[���ֈړ�����
	if (MY_KEY_DOWN(KEY_INPUT_ESCAPE) == TRUE)
	{
		//BGM������Ă���Ȃ�
		if (CheckSoundMem(EndBGM.handle) != 0)
		{
			StopSoundMem(EndBGM.handle);
		}

		GameScene = GAME_SCENE_START;
	}

	return;
}

//�G���h��ʂ̕`��
VOID MY_END_DRAW(VOID)
{
	//�w�i��`��
	DrawGraph(EndBack.x, EndBack.y, EndBack.handle, TRUE);

	if (GameEndKind == GAME_END_COMP)
	{
		DrawGraph(EndROGO.image.x, EndROGO.image.y, EndROGO.image.handle, TRUE);
	}

	DrawString(0, 0, "�G���h���(�G�X�P�[�v�L�[�������ĉ�����)", GetColor(255, 255, 255));
	return;
}

BOOL MY_LOAD_IMAGE(VOID)
{
	//�^�C�g���w�i
	strcpy_s(StartBack.path, IMAGE_START_BACK);
	StartBack.handle = LoadGraph(StartBack.path);	//�ǂݍ���
	if (StartBack.handle == -1)
	{
		//�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), IMAGE_START_BACK, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(StartBack.handle, &StartBack.width, &StartBack.height);
	StartBack.x = GAME_WIDTH / 2 - StartBack.width / 2;
	StartBack.y = GAME_HEIGHT / 2 - StartBack.height / 2;

	//�^�C�g�����S
	strcpy_s(Title2.image.path, IMAGE_START_TITLE2);
	Title2.image.handle = LoadGraph(Title2.image.path);	//�ǂݍ���
	if (Title2.image.handle == -1)
	{
		//�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), IMAGE_START_TITLE2, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(Title2.image.handle, &Title2.image.width, &Title2.image.height);
	Title2.image.x = GAME_WIDTH / 2 - Title2.image.width / 2;
	Title2.image.y = GAME_HEIGHT / 2 - Title2.image.width / 2 + 180;
	Title2.IsDraw = FALSE;

	strcpy_s(Title.image.path, IMAGE_START_TITLE);
	Title.image.handle = LoadGraph(Title.image.path);	//�ǂݍ���
	if (Title.image.handle == -1)
	{
		//�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), IMAGE_START_TITLE, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(Title.image.handle, &Title.image.width, &Title.image.height);
	Title.image.x = GAME_WIDTH / 2 - Title.image.width / 2;
	Title.image.y = GAME_HEIGHT / 2 - Title.image.width / 2 + 120;
	Title.IsDraw = FALSE;

	strcpy_s(TitleROGO.image.path, IMAGE_START_TITLEROGO);
	TitleROGO.image.handle = LoadGraph(TitleROGO.image.path);	//�ǂݍ���
	if (TitleROGO.image.handle == -1)
	{
		//�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), IMAGE_START_TITLEROGO, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(TitleROGO.image.handle, &TitleROGO.image.width, &TitleROGO.image.height);
	TitleROGO.image.x = GAME_WIDTH / 2 - TitleROGO.image.width / 2;
	TitleROGO.image.y = GAME_HEIGHT / 2 - TitleROGO.image.height / 2 - 40;
	TitleROGO.IsDraw = FALSE;

	//���j���[
	strcpy_s(menu1.image.path, IMAGE_START_MENU1);
	menu1.image.handle = LoadGraph(menu1.image.path);	//�ǂݍ���
	if (menu1.image.handle == -1)
	{
		//�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), IMAGE_START_MENU1, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(menu1.image.handle, &menu1.image.width, &menu1.image.height);
	menu1.image.x = GAME_WIDTH / 2 - menu1.image.width / 2;
	menu1.image.y = TitleROGO.image.y + TitleROGO.image.height + 20;
	menu1.IsDraw = FALSE;

	strcpy_s(menu2.image.path, IMAGE_START_MENU2);
	menu2.image.handle = LoadGraph(menu2.image.path);	//�ǂݍ���
	if (menu2.image.handle == -1)
	{
		//�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), IMAGE_START_MENU2, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(menu2.image.handle, &menu2.image.width, &menu2.image.height);
	menu2.image.x = GAME_WIDTH / 2 - menu2.image.width / 2;
	menu2.image.y = TitleROGO.image.y + TitleROGO.image.height + 20;
	menu2.IsDraw = FALSE;

	//�������
	strcpy_s(Setsumei.image.path, IMAGE_SETSUMEI);
	Setsumei.image.handle = LoadGraph(Setsumei.image.path);	//�ǂݍ���
	if (Setsumei.image.handle == -1)
	{
		//�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), IMAGE_SETSUMEI, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(Setsumei.image.handle, &Setsumei.image.width, &Setsumei.image.height);
	Setsumei.image.x = GAME_WIDTH / 2 - Setsumei.image.width / 2;
	Setsumei.image.y = GAME_HEIGHT / 2 - Setsumei.image.height / 2;
	Setsumei.IsDraw = FALSE;

	//�����
	strcpy_s(Loading.image.path, IMAGE_LOAD_BLACK);
	Loading.image.handle = LoadGraph(Loading.image.path);	//�ǂݍ���
	if (Loading.image.handle == -1)
	{
		//�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), IMAGE_LOAD_BLACK, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(Loading.image.handle, &Loading.image.width, &Loading.image.height);
	Loading.image.x = GAME_WIDTH / 2 - Loading.image.width / 2;
	Loading.image.y = GAME_HEIGHT / 2 - Loading.image.height / 2;
	Loading.IsDraw = FALSE;

	//�G���h���S
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

	//�w�i�摜
	strcpy_s(ImageBack[0].image.path, IMAGE_PLAY_BACK1);			//�p�X�̐ݒ�
	strcpy_s(ImageBack[1].image.path, IMAGE_PLAY_BACK2);
	strcpy_s(ImageBack[2].image.path, IMAGE_PLAY_BACK1);
	strcpy_s(ImageBack[3].image.path, IMAGE_PLAY_BACK2);

	//�摜��A�����ēǂݍ���
	for (int num = 0; num < IMAGE_NUM; num++)
	{
		ImageBack[num].image.handle = LoadGraph(ImageBack[num].image.path);
		if (ImageBack[num].image.handle == -1)
		{
			//�G���[���b�Z�[�W�\��
			MessageBox(GetMainWindowHandle(), IMAGE_PLAY_BACK1, IMAGE_LOAD_ERR_TITLE, MB_OK);
			return FALSE;
		}
		//�摜�̕��ƍ������擾
		GetGraphSize(ImageBack[num].image.handle, &ImageBack[num].image.width, &ImageBack[num].image.height);
	}
	//�w�i�摜�@�̐ݒ�
	ImageBack[0].image.x = 0 - ImageBack[0].image.width * 0;				//x�͌��_����
	ImageBack[0].image.y = GAME_HEIGHT / 2 - ImageBack[0].image.height / 2;	//�㉺��������
	ImageBack[0].IsDraw = FALSE;
	//�w�i�摜�A�̐ݒ�
	ImageBack[1].image.x = 0 - ImageBack[0].image.width * 1;				//x�͌��_����
	ImageBack[1].image.y = GAME_HEIGHT / 2 - ImageBack[1].image.height / 2;	//�㉺��������
	ImageBack[1].IsDraw = FALSE;
	//�w�i�摜�B�̐ݒ�
	ImageBack[2].image.x = 0 - ImageBack[0].image.width * 2;				//x�͌��_����
	ImageBack[2].image.y = GAME_HEIGHT / 2 - ImageBack[2].image.height / 2;	//�㉺��������
	ImageBack[2].IsDraw = FALSE;
	//�w�i�摜�C�̐ݒ�
	ImageBack[3].image.x = 0 - ImageBack[0].image.width * 3;				//x�͌��_����
	ImageBack[3].image.y = GAME_HEIGHT / 2 - ImageBack[3].image.height / 2;	//�㉺��������
	ImageBack[3].IsDraw = FALSE;

	//�w�i�摜
	strcpy_s(ImageFront[0].image.path, IMAGE_PLAY_FRONT1);			//�p�X�̐ݒ�
	strcpy_s(ImageFront[1].image.path, IMAGE_PLAY_FRONT2);
	strcpy_s(ImageFront[2].image.path, IMAGE_PLAY_FRONT1);
	strcpy_s(ImageFront[3].image.path, IMAGE_PLAY_FRONT2);

	//�摜��A�����ēǂݍ���
	for (int num = 0; num < IMAGE_NUM; num++)
	{
		ImageFront[num].image.handle = LoadGraph(ImageFront[num].image.path);
		if (ImageFront[num].image.handle == -1)
		{
			//�G���[���b�Z�[�W�\��
			MessageBox(GetMainWindowHandle(), IMAGE_PLAY_FRONT1, IMAGE_LOAD_ERR_TITLE, MB_OK);
			return FALSE;
		}
		//�摜�̕��ƍ������擾
		GetGraphSize(ImageFront[num].image.handle, &ImageFront[num].image.width, &ImageFront[num].image.height);
	}
	//�w�i�摜�@�̐ݒ�
	ImageFront[0].image.x = 0 + ImageFront[0].image.width * 0;				//x�͌��_����
	ImageFront[0].image.y = GAME_HEIGHT / 2 - ImageFront[0].image.height / 2;	//�㉺��������
	ImageFront[0].IsDraw = FALSE;
	//�w�i�摜�A�̐ݒ�
	ImageFront[1].image.x = 0 + ImageFront[0].image.width * 1;				//x�͌��_����
	ImageFront[1].image.y = GAME_HEIGHT / 2 - ImageFront[1].image.height / 2;	//�㉺��������
	ImageFront[1].IsDraw = FALSE;
	//�w�i�摜�B�̐ݒ�
	ImageFront[2].image.x = 0 + ImageFront[0].image.width * 2;				//x�͌��_����
	ImageFront[2].image.y = GAME_HEIGHT / 2 - ImageFront[2].image.height / 2;	//�㉺��������
	ImageFront[2].IsDraw = FALSE;
	//�w�i�摜�C�̐ݒ�
	ImageFront[3].image.x = 0 + ImageFront[0].image.width * 3;				//x�͌��_����
	ImageFront[3].image.y = GAME_HEIGHT / 2 - ImageFront[3].image.height / 2;	//�㉺��������
	ImageFront[3].IsDraw = FALSE;

	
		//�v���C���[�̉摜
		//�v���C���[
		int PRes = LoadDivGraph(
			IMAGE_PLAYER_PATH,										//�v���C���[�̃p�X
			PLAYER_DIV_NUM, PLAYER_DIV_TATE, PLAYER_DIV_YOKO,	//�������鐔
			PLAYER_DIV_WIDTH, PLAYER_DIV_HEIGHT,				//��������
			&chara.player[0].handle[0]);

		if (PRes == -1)
		{
			//�G���[
			MessageBox(GetMainWindowHandle(), IMAGE_PLAYER_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
			return FALSE;
		}

		//���ƍ������擾
		GetGraphSize(chara.player[0].handle[0], &chara.player[0].width, &chara.player[0].height);

		//�摜�̏��𐶐�
	for (int cnt = 0; cnt < PLAYER_DIV_NUM; cnt++)
	{
		//�p�X���R�s�[
		strcpyDx(chara.player[cnt].path, TEXT(IMAGE_PLAYER_PATH));

		for (int i_num = 0; i_num < PLAYER_DIV_NUM; i_num++)
		{
			//�n���h�����R�s�[
			chara.player[cnt].handle[i_num] = chara.player[0].handle[i_num];
		}

		chara.player[cnt].width = chara.player[0].width;
		chara.player[cnt].height = chara.player[0].height;

		chara.player[cnt].x = GAME_WIDTH / 2 - chara.player[cnt].width / 2;		//���E��������
		chara.player[cnt].y = GAME_HEIGHT / 2 - chara.player[cnt].height / 2;		//�㉺������
		chara.CenterX = chara.player[cnt].x + chara.player[cnt].width / 2;	//�摜�̉��̒��S��T��
		chara.CenterY = chara.player[cnt].y + chara.player[cnt].height / 2;	//�摜�̏c�̒��S��T��
		chara.IsDraw = TRUE;
		chara.player[cnt].nowImageKind = 0;		//���݂̉摜�̎��
		chara.player[cnt].speed = CHARA_SPEED_LOW;	//�X�s�[�h��ݒ�
	}

	//���N
	strcpy_s(boy.image.path, IMAGE_BOY_PATH);		//�p�X�̐ݒ�
	boy.image.handle = LoadGraph(boy.image.path);	//�ǂݍ���
	if (boy.image.handle == -1)
	{
		//�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), IMAGE_BOY_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(boy.image.handle, &boy.image.width, &boy.image.height);	//�摜�̕��ƍ������擾
	boy.image.x = GAME_WIDTH - 115;		//���E��������
	boy.image.y = 144;		//�㉺��������
	boy.CenterX = boy.image.x + boy.image.width / 2;		//�摜�̉��̒��S��T��
	boy.CenterY = boy.image.y + boy.image.height / 2;		//�摜�̏c�̒��S��T��
	boy.IsDraw = FALSE;

	//�e�L�X�g�{�b�N�X
	strcpy_s(TextBox.image.path, IMAGE_TEXTBOX);
	TextBox.image.handle = LoadGraph(TextBox.image.path);	//�ǂݍ���
	if (TextBox.image.handle == -1)
	{
		//�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), IMAGE_TEXTBOX, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(TextBox.image.handle, &TextBox.image.width, &TextBox.image.height);
	TextBox.image.x = GAME_WIDTH / 2 - TextBox.image.width / 2;
	TextBox.image.y = GAME_HEIGHT / 2 - TextBox.image.height / 2;

	//�}�b�v
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
			//�}�b�v�̓����蔻���ݒ�
			mapColl[tate][yoko].left = (yoko + 0) * mapChip.width + 1;
			mapColl[tate][yoko].top = (tate + 0) * mapChip.height + 1;
			mapColl[tate][yoko].right = (yoko + 1) * mapChip.width - 1;
			mapColl[tate][yoko].bottom = (tate + 1) * mapChip.height - 1;
		}
	}

	//�G���h�w�i
	strcpy_s(EndBack.path, IMAGE_END_BACK);
	EndBack.handle = LoadGraph(EndBack.path);	//�ǂݍ���
	if (EndBack.handle == -1)
	{
		//�G���[���b�Z�[�W�\��
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
	//�}�b�v�̓����蔻���ݒ肷��
	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			//�v���C���[�ƃ}�b�v���������Ă���Ƃ�
			if (MY_CHECK_RECT_COLL(player, mapColl[tate][yoko]) == TRUE)
			{
				//�ǂ̂Ƃ��́A�v���C���[�ƃ}�b�v���������Ă���
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

//�̈�̓����蔻�������֐�
BOOL MY_CHECK_RECT_COLL(RECT a, RECT b)
{
	if (a.left < b.right &&
		a.top < b.bottom &&
		a.right > b.left &&
		a.bottom > b.top
		)
	{
		return TRUE;	//�������Ă���
	}

	return FALSE;		//�������Ă��Ȃ�
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
			DrawString(TextPtX, TextPtY, "BACKSPACE�L�[�ŕ��܂�", GetColor(255, 255, 255));
		}
		else
		{
			DrawString(TextPtX, TextPtY, "BACKSPACE�L�[�ŕ��܂�", GetColor(255, 255, 255));
		}
	}

	return;
}