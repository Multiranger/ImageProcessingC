#define _CRT_SECURE_NO_WARNINGS // VS 보안 오류 해제
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <conio.h>
#include <Windows.h>

#define UC unsigned char
#define MAX_WORK 10

// 전역 변수부
UC **m_Image[MAX_WORK];
int m_H[MAX_WORK], m_W[MAX_WORK], m_cur, m_last;
char m_dir[100];
HWND hwnd; // 윈도 화면(물리적)
HDC hdc;   // 윈도 화면(논리적)

// 함수 선언부(공통)
void changeDir();
void openImage();
void saveImage();
void drawImage();
UC **malloc2D(int, int);
void free2D(UC **, int);
// 함수 선언부(영상 처리)
void equalImage();
void negativeImage();
void addImage();
void mulImage();
void bwImage();
void avgImage();
void gammaImage();
void capParaImage();
void cupParaImage();
void rotate90();
void zoomOutImage();
void zoomInImage();
void moveImage();
void rotateImage();
void udMirrorImage();
void lrMirrorImage();
void emboss();
void blur();
void gauss();
void sharpen();
void lpfSharpen();
void homogen();
void differ();
void LoG();
void DoG();
void contrast();
void histoSmooth();
void histoStretch();
void mergeImage();
void circleAndImage();
void posterImage();
void partImage();
void hpfSharpen();
void pixelation();

void printMenu1()
{ // 화소 점 처리
	puts("\n ## 영상 처리 KSY 1.01 ##\n");
	puts("0.파일경로  1.열기  2.원본  3.저장  4.Undo  5.Redo  6.종료\n");
	puts("A.더하기  B.곱하기  C.대비  D.감마\n");
	puts("E.명암반전  F.파라(캡)  G.파라(컵)\n");
	puts("H.포스터라이징  I.부분 강조\n");
	puts("J.흑백(128)  K.흑백(평균)\n");
	puts("L.히스토그램(평활)  M.히스토그램(엔드-인)\n");
	puts("N.다음 메뉴\n");
}
void printMenu2()
{ // 기하학 처리
	puts("\n ## 영상 처리 KSY 1.01 ##\n");
	puts("0.파일경로  1.열기  2.원본  3.저장  4.Undo  5.Redo  6.종료\n");
	puts("A.이동  B.축소  C.확대  D.회전\n");
	puts("E.회전(90)  F.상하반전  G.좌우반전\n");
	puts("N.다음 메뉴\n");
}
void printMenu3()
{ // 화소 영역 처리
	puts("\n ## 영상 처리 KSY 1.01 ##\n");
	puts("0.파일경로  1.열기  2.원본  3.저장  4.Undo  5.Redo  6.종료\n");
	puts("A.엠보싱  B.블러  C.가우시안\n");
	puts("D.기본 샤프닝  E.HPF  F.LPF\n");
	puts("G.유사 연산자  H.차 연산자\n");
	puts("I.LoG  J.DoG\n");
	puts("N.다음 메뉴\n");
}
void printMenu4()
{ // 기타
	puts("\n ## 영상 처리 KSY 1.01 ##\n");
	puts("0.파일경로  1.열기  2.원본  3.저장  4.Undo  5.Redo  6.종료\n");
	puts("A.머지  B.원형 마스크  C.픽셀화\n");
	puts("N.처음으로\n");
}
void undo()
{
	if (m_cur > 1)
		m_cur--;

	drawImage();
}
void redo()
{
	if (m_cur < m_last)
		m_cur++;

	drawImage();
}

// 메인 코드
int main()
{
	hwnd = GetForegroundWindow();
	hdc = GetWindowDC(hwnd);

	char select = 0;
	char menu = 0;
	while (select != '6')
	{
		if (menu == 0)
		{
			printMenu1();
			rewind(stdin);
			select = _getch();

			switch (select)
			{
			case '0':
				changeDir();
				break;
			case '1':
				openImage();
				equalImage();
				break;
			case '2':
				equalImage();
				break;
			case '3':
				saveImage();
				break;
			case '4':
				undo();
				break;
			case '5':
				redo();
				break;
			case '6':
				for (int i = 0; i < MAX_WORK; i++)
					free2D(m_Image[i], m_H[i]);
				return 0;
			case 'a':
			case 'A':
				addImage();
				break;
			case 'b':
			case 'B':
				mulImage();
				break;
			case 'c':
			case 'C':
				contrast();
				break;
			case 'd':
			case 'D':
				gammaImage();
				break;
			case 'e':
			case 'E':
				negativeImage();
				break;
			case 'f':
			case 'F':
				capParaImage();
				break;
			case 'g':
			case 'G':
				cupParaImage();
				break;
			case 'h':
			case 'H':
				posterImage();
				break;
			case 'i':
			case 'I':
				partImage();
				break;
			case 'j':
			case 'J':
				bwImage();
				break;
			case 'k':
			case 'K':
				avgImage();
				break;
			case 'l':
			case 'L':
				histoSmooth();
				break;
			case 'm':
			case 'M':
				histoStretch();
				break;
			case 'n':
			case 'N':
				drawImage();
				menu = 1;
				break;
			default:
				drawImage();
				break;
			}
		}
		if (menu == 1)
		{
			printMenu2();
			rewind(stdin);
			select = _getch();

			switch (select)
			{
			case '0':
				changeDir();
				break;
			case '1':
				openImage();
				equalImage();
				break;
			case '2':
				equalImage();
				break;
			case '3':
				saveImage();
				break;
			case '4':
				undo();
				break;
			case '5':
				redo();
				break;
			case '6':
				for (int i = 0; i < MAX_WORK; i++)
					free2D(m_Image[i], m_H[i]);
				return 0;
			case 'a':
			case 'A':
				moveImage();
				break;
			case 'b':
			case 'B':
				zoomOutImage();
				break;
			case 'c':
			case 'C':
				zoomInImage();
				break;
			case 'd':
			case 'D':
				rotateImage();
				break;
			case 'e':
			case 'E':
				rotate90();
				break;
			case 'f':
			case 'F':
				udMirrorImage();
				break;
			case 'g':
			case 'G':
				lrMirrorImage();
				break;
			case 'n':
			case 'N':
				drawImage();
				menu = 2;
				break;
			default:
				drawImage();
				break;
			}
		}
		if (menu == 2)
		{
			printMenu3();
			rewind(stdin);
			select = _getch();

			switch (select)
			{
			case '0':
				changeDir();
				break;
			case '1':
				openImage();
				equalImage();
				break;
			case '2':
				equalImage();
				break;
			case '3':
				saveImage();
				break;
			case '4':
				undo();
				break;
			case '5':
				redo();
				break;
			case '6':
				for (int i = 0; i < MAX_WORK; i++)
					free2D(m_Image[i], m_H[i]);
				return 0;
			case 'a':
			case 'A':
				emboss();
				break;
			case 'b':
			case 'B':
				blur();
				break;
			case 'c':
			case 'C':
				gauss();
				break;
			case 'd':
			case 'D':
				sharpen();
				break;
			case 'e':
			case 'E':
				hpfSharpen();
				break;
			case 'f':
			case 'F':
				lpfSharpen();
				break;
			case 'g':
			case 'G':
				homogen();
				break;
			case 'h':
			case 'H':
				differ();
				break;
			case 'i':
			case 'I':
				LoG();
				break;
			case 'j':
			case 'J':
				DoG();
				break;
			case 'n':
			case 'N':
				drawImage();
				menu = 3;
				break;
			default:
				drawImage();
				break;
			}
		}
		if (menu == 3)
		{
			printMenu4();
			rewind(stdin);
			select = _getch();

			switch (select)
			{
			case '0':
				changeDir();
				break;
			case '1':
				openImage();
				equalImage();
				break;
			case '2':
				equalImage();
				break;
			case '3':
				saveImage();
				break;
			case '4':
				undo();
				break;
			case '5':
				redo();
				break;
			case '6':
				for (int i = 0; i < MAX_WORK; i++)
					free2D(m_Image[i], m_H[i]);
				return 0;
			case 'a':
			case 'A':
				mergeImage();
				break;
			case 'b':
			case 'B':
				circleAndImage();
				break;
			case 'c':
			case 'C':
				pixelation();
				break;
			case 'n':
			case 'N':
				drawImage();
				menu = 0;
				break;
			default:
				drawImage();
				break;
			}
		}
	}
}

// 함수 정의부
// 공통 함수 정의부

/// <summary>
/// 2차원 메모리 할당 (h x w)
/// </summary>
/// <param name="h">높이 (포인터 배열)</param>
/// <param name="w">폭 (배열)</param>
/// <returns></returns>
UC **malloc2D(int h, int w)
{
	UC **memory;

	memory = (UC **)malloc(h * sizeof(UC *)); // 포인터 배열 할당

	if (memory == NULL)
		return NULL;

	for (int i = 0; i < h; i++) // 각 포인터에 배열 할당
	{
		memory[i] = (UC *)malloc(w * sizeof(UC));

		if (memory[i] == NULL) // 할당에 실패한 배열이 있으면
		{
			for (int k = 0; k < i; k++) // 지금까지 할당한 메모리를 모두 반환하고
				free(memory[k]);
			free(memory);
			return NULL; // NULL 반환
		}

		for (int k = 0; k < w; k++) // 초기화
			memory[i][k] = 0;
	}
	return memory; // 모두 할당에 성공한 경우
}

/// <summary>
/// 2차원 메모리 할당 해제
/// </summary>
/// <param name="memory">해제하려는 메모리</param>
/// <param name="h">해제하려는 메모리의 높이</param>
void free2D(UC **memory, int h)
{
	if (memory == NULL) // 할당된 적이 없으면 아무것도 안함
	{
		return;
	}

	for (int i = 0; i < h; i++)
		free(memory[i]);
	free(memory);
}

/// <summary>
/// 새로운 작업에 대해 커서 이동
/// </summary>
void newCur()
{
	if (m_cur < MAX_WORK - 1) // 작업공간이 남아있다면
	{
		m_cur++;
		m_last = m_cur;
	}
	else // 작업공간이 가득 차면 첫 번째 작업을 지우고 앞으로 한 칸씩 이동
	{
		free2D(m_Image[1], m_H[1]);
		for (int i = 1; i < MAX_WORK - 1; i++)
		{
			m_Image[i] = m_Image[i + 1];
			m_H[i] = m_H[i + 1];
			m_W[i] = m_W[i + 1];
		}
		m_Image[MAX_WORK - 1] = malloc2D(m_H[MAX_WORK - 1], m_W[MAX_WORK - 1]);
	}
}

/// <summary>
/// 경로 이름 변경
/// </summary>
void changeDir()
{
	char tmpDir[100] = "";
	printf("경로명: ");
	rewind(stdin);
	scanf("%s", tmpDir);

	if (tmpDir[99] != 0)
	{
		MessageBox(hwnd, "파일 경로가 최대 길이(99자)를 초과했습니다.", "경로 창", 0);
		drawImage();
		return;
	}

	if (!strcmp(tmpDir, "default")) // 기본값은 실행파일 위치
		strcpy(m_dir, "");
	else
		strcpy(m_dir, tmpDir);

	drawImage();
}

/// <summary>
/// raw 이미지를 열어서 m_Images[0]에 저장
/// </summary>
void openImage()
{
	char fullName[160] = "";
	char tmpName[50] = "";
	printf("파일명: ");
	rewind(stdin);
	scanf("%s", tmpName);

	if (tmpName[49] != 0)
	{
		MessageBox(hwnd, "파일 이름이 최대 길이(49자)를 초과했습니다.", "열기 창", 0);
		return;
	}

	strcpy(fullName, m_dir);
	strcat(fullName, tmpName);
	strcat(fullName, ".raw");

	FILE *rfp;
	rfp = fopen(fullName, "rb");
	if (rfp == NULL)
	{
		MessageBox(hwnd, "파일 읽기 실패.", "열기 창", 0);
		return;
	}

	// 파일 크기 알아내기
	fseek(rfp, 0L, SEEK_END);
	unsigned long fsize = ftell(rfp);
	fseek(rfp, 0L, SEEK_SET);

	// 메모리 누수 방지
	for (int i = 0; i < MAX_WORK; i++)
		free2D(m_Image[i], m_H[i]);
	m_cur = m_last = 0;

	// (중요!) 영상의 높이와 폭 계산
	m_H[0] = m_W[0] = (int)sqrt(fsize);

	// 메모리 할당.	uc image[height][width];
	m_Image[0] = malloc2D(m_H[0], m_W[0]);
	if (m_Image[0] == NULL)
	{
		MessageBox(hwnd, "메모리 부족.", "열기 창", 0);
		fclose(rfp);
		return;
	}

	// 파일 --> 메모리로 로딩
	for (int i = 0; i < m_H[0]; i++)
		fread(m_Image[0][i], sizeof(UC), m_W[0], rfp);

	fclose(rfp);
}

/// <summary>
/// m_Images[m_cur] 출력
/// </summary>
void drawImage()
{
	int px;

	system("cls");
	for (int i = 0; i < m_H[m_cur]; i++)
	{
		for (int k = 0; k < m_W[m_cur]; k++)
		{
			px = m_Image[m_cur][i][k];
			SetPixel(hdc, k + 600, i + 100, RGB(px, px, px));
		}
	}
}

/// <summary>
/// m_Images[m_cur]를 사용자가 입력한 이름.raw 로 저장
/// </summary>
void saveImage()
{
	// 저장할 파일명 입력 받기.
	char fullName[160] = "";
	char tmpName[50] = "";
	printf("저장 파일명: ");
	rewind(stdin);
	scanf("%s", tmpName);

	if (tmpName[49] != 0)
	{
		MessageBox(hwnd, "파일 이름이 최대 길이(49자)를 초과했습니다.", "저장 창", 0);
		drawImage();
		return;
	}

	if (!strcmp(tmpName, "cancel"))
	{
		MessageBox(hwnd, "저장 취소.", "저장 창", 0);
		drawImage();
		return;
	}

	strcpy(fullName, m_dir);
	strcat(fullName, tmpName);
	strcat(fullName, ".raw");

	FILE *wfp = fopen(fullName, "wb");
	if (wfp == NULL)
	{
		MessageBox(hwnd, "저장 실패", "저장 창", 0);
		drawImage();
		return;
	}

	for (int i = 0; i < m_H[m_cur]; i++)
		fwrite(m_Image[m_cur][i], sizeof(UC), m_W[m_cur], wfp);

	fclose(wfp);
	MessageBox(hwnd, "저장 OK", "저장 창", 0);

	drawImage();
}

// 영상 처리 함수 정의부

/// <summary>
/// 동일 영상 알고리즘
/// </summary>
void equalImage()
{
	newCur(); // 새 작업공간 이동

	free2D(m_Image[m_cur], m_H[m_cur]); // 메모리 누수 방지
	m_H[m_cur] = m_H[0];
	m_W[m_cur] = m_W[0];
	m_Image[m_cur] = malloc2D(m_H[m_cur], m_W[m_cur]);

	if (m_Image[m_cur] == NULL)
	{
		m_cur--;
		m_last = m_cur;
		MessageBox(hwnd, "메모리 부족.", "작업 창", 0);
		drawImage();
		return;
	}

	for (int i = 0; i < m_H[m_cur]; i++)
		for (int k = 0; k < m_W[m_cur]; k++)
			m_Image[m_cur][i][k] = m_Image[0][i][k]; // 그대로 복사

	drawImage();
}

/// <summary>
/// 영상 반전 알고리즘
/// </summary>
void negativeImage()
{
	newCur();

	free2D(m_Image[m_cur], m_H[m_cur]);
	m_H[m_cur] = m_H[m_cur - 1];
	m_W[m_cur] = m_W[m_cur - 1];
	m_Image[m_cur] = malloc2D(m_H[m_cur], m_W[m_cur]);

	if (m_Image[m_cur] == NULL)
	{
		m_cur--;
		m_last = m_cur;
		MessageBox(hwnd, "메모리 부족.", "작업 창", 0);
		drawImage();
		return;
	}

	for (int i = 0; i < m_H[m_cur]; i++)
		for (int k = 0; k < m_W[m_cur]; k++)
			m_Image[m_cur][i][k] = 255 - m_Image[m_cur - 1][i][k]; // 반전, 오버플로우 없음

	drawImage();
}

/// <summary>
/// 영상 더하기 알고리즘
/// </summary>
void addImage()
{
	newCur();

	free2D(m_Image[m_cur], m_H[m_cur]);
	m_H[m_cur] = m_H[m_cur - 1];
	m_W[m_cur] = m_W[m_cur - 1];
	m_Image[m_cur] = malloc2D(m_H[m_cur], m_W[m_cur]);

	if (m_Image[m_cur] == NULL)
	{
		m_cur--;
		m_last = m_cur;
		MessageBox(hwnd, "메모리 부족.", "작업 창", 0);
		drawImage();
		return;
	}

	int value = 0;

	printf("더할 값: ");
	rewind(stdin);
	scanf("%d", &value);

	for (int i = 0; i < m_H[m_cur]; i++)
	{
		for (int k = 0; k < m_W[m_cur]; k++)
		{
			int pixel = m_Image[m_cur - 1][i][k] + value;

			if (pixel > 255) // 오버플로우 방지
				pixel = 255;
			else if (pixel < 0)
				pixel = 0;

			m_Image[m_cur][i][k] = pixel;
		}
	}

	drawImage();
}

/// <summary>
/// 영상 곱하기 알고리즘
/// </summary>
void mulImage()
{
	newCur();

	free2D(m_Image[m_cur], m_H[m_cur]);
	m_H[m_cur] = m_H[m_cur - 1];
	m_W[m_cur] = m_W[m_cur - 1];
	m_Image[m_cur] = malloc2D(m_H[m_cur], m_W[m_cur]);

	if (m_Image[m_cur] == NULL)
	{
		m_cur--;
		m_last = m_cur;
		MessageBox(hwnd, "메모리 부족.", "작업 창", 0);
		drawImage();
		return;
	}

	double value = 1.0;

	printf("곱할 값: ");
	rewind(stdin);
	scanf("%lf", &value);

	if (value < 0) // 음수로 곱하면 반전됨
		value = -value;

	for (int i = 0; i < m_H[m_cur]; i++)
	{
		for (int k = 0; k < m_W[m_cur]; k++)
		{
			int pixel = (int)(m_Image[m_cur - 1][i][k] * value);

			if (pixel > 255) // 음수로 곱해지는 경우 없음
				pixel = 255;

			m_Image[m_cur][i][k] = pixel;
		}
	}

	drawImage();
}

/// <summary>
/// 영상 흑백 알고리즘(128)
/// </summary>
void bwImage()
{
	newCur();

	free2D(m_Image[m_cur], m_H[m_cur]);
	m_H[m_cur] = m_H[m_cur - 1];
	m_W[m_cur] = m_W[m_cur - 1];
	m_Image[m_cur] = malloc2D(m_H[m_cur], m_W[m_cur]);

	if (m_Image[m_cur] == NULL)
	{
		m_cur--;
		m_last = m_cur;
		MessageBox(hwnd, "메모리 부족.", "작업 창", 0);
		drawImage();
		return;
	}

	for (int i = 0; i < m_H[m_cur]; i++)
	{
		for (int k = 0; k < m_W[m_cur]; k++)
		{
			if (m_Image[m_cur - 1][i][k] < 128) // 128을 기준으로
				m_Image[m_cur][i][k] = 0;
			else
				m_Image[m_cur][i][k] = 255;
		}
	}

	drawImage();
}

/// <summary>
/// 영상 평균 기준 흑백 알고리즘
/// </summary>
void avgImage()
{
	newCur();

	free2D(m_Image[m_cur], m_H[m_cur]);
	m_H[m_cur] = m_H[m_cur - 1];
	m_W[m_cur] = m_W[m_cur - 1];
	m_Image[m_cur] = malloc2D(m_H[m_cur], m_W[m_cur]);

	if (m_Image[m_cur] == NULL)
	{
		m_cur--;
		m_last = m_cur;
		MessageBox(hwnd, "메모리 부족.", "작업 창", 0);
		drawImage();
		return;
	}

	unsigned long total = 0;
	double avg;

	for (int i = 0; i < m_H[m_cur]; i++) // 전체 합을 구해서
		for (int k = 0; k < m_W[m_cur]; k++)
			total += m_Image[m_cur - 1][i][k];

	if (m_H[m_cur] != 0 && m_W[m_cur] != 0)
		avg = total / (double)(m_H[m_cur] * m_W[m_cur]); // 원소 수로 나눠서 평균 구함

	for (int i = 0; i < m_H[m_cur]; i++)
	{
		for (int k = 0; k < m_W[m_cur]; k++)
		{
			if (m_Image[m_cur - 1][i][k] < avg) // 평균을 기준으로 흑백
				m_Image[m_cur][i][k] = 0;
			else
				m_Image[m_cur][i][k] = 255;
		}
	}

	drawImage();
}

/// <summary>
/// 영상 감마 알고리즘
/// </summary>
void gammaImage()
{
	newCur();

	free2D(m_Image[m_cur], m_H[m_cur]);
	m_H[m_cur] = m_H[m_cur - 1];
	m_W[m_cur] = m_W[m_cur - 1];
	m_Image[m_cur] = malloc2D(m_H[m_cur], m_W[m_cur]);

	if (m_Image[m_cur] == NULL)
	{
		m_cur--;
		m_last = m_cur;
		MessageBox(hwnd, "메모리 부족.", "작업 창", 0);
		drawImage();
		return;
	}

	double gamma = 0.0;

	printf("감마 입력: ");
	rewind(stdin);
	scanf("%lf", &gamma);

	for (int i = 0; i < m_H[m_cur]; i++)
	{
		for (int k = 0; k < m_W[m_cur]; k++)
		{
			double temp = m_Image[m_cur - 1][i][k] / 255.0;
			m_Image[m_cur][i][k] = (UC)(255.0 * pow(temp, 1.0 / gamma)); // 255(x/255)^(1/r)
		}
	}

	drawImage();
}

/// <summary>
/// 영상 cap 파라볼라 알고리즘
/// </summary>
void capParaImage()
{
	newCur();

	free2D(m_Image[m_cur], m_H[m_cur]);
	m_H[m_cur] = m_H[m_cur - 1];
	m_W[m_cur] = m_W[m_cur - 1];
	m_Image[m_cur] = malloc2D(m_H[m_cur], m_W[m_cur]);

	if (m_Image[m_cur] == NULL)
	{
		m_cur--;
		m_last = m_cur;
		MessageBox(hwnd, "메모리 부족.", "작업 창", 0);
		drawImage();
		return;
	}

	for (int i = 0; i < m_H[m_cur]; i++)
	{
		for (int k = 0; k < m_W[m_cur]; k++)
		{
			double value = 255.0 - 255.0 * pow(m_Image[m_cur - 1][i][k] / 128.0 - 1.0, 2.0);
			m_Image[m_cur][i][k] = (UC)value;
		}
	}

	drawImage();
}

/// <summary>
/// 영상 cup 파라볼라 알고리즘
/// </summary>
void cupParaImage()
{
	newCur();

	free2D(m_Image[m_cur], m_H[m_cur]);
	m_H[m_cur] = m_H[m_cur - 1];
	m_W[m_cur] = m_W[m_cur - 1];
	m_Image[m_cur] = malloc2D(m_H[m_cur], m_W[m_cur]);

	if (m_Image[m_cur] == NULL)
	{
		m_cur--;
		m_last = m_cur;
		MessageBox(hwnd, "메모리 부족.", "작업 창", 0);
		drawImage();
		return;
	}

	for (int i = 0; i < m_H[m_cur]; i++)
	{
		for (int k = 0; k < m_W[m_cur]; k++)
		{
			double value = 255.0 * pow(m_Image[m_cur - 1][i][k] / 128.0 - 1.0, 2.0);
			m_Image[m_cur][i][k] = (UC)value;
		}
	}

	drawImage();
}

/// <summary>
/// 영상 90도 회전
/// </summary>
void rotate90()
{
	newCur();

	free2D(m_Image[m_cur], m_H[m_cur]);
	m_H[m_cur] = m_W[m_cur - 1];
	m_W[m_cur] = m_H[m_cur - 1];
	m_Image[m_cur] = malloc2D(m_H[m_cur], m_W[m_cur]);

	if (m_Image[m_cur] == NULL)
	{
		m_cur--;
		m_last = m_cur;
		MessageBox(hwnd, "메모리 부족.", "작업 창", 0);
		drawImage();
		return;
	}

	for (int i = 0; i < m_H[m_cur]; i++)
		for (int k = 0; k < m_W[m_cur]; k++)
			m_Image[m_cur][i][k] = m_Image[m_cur - 1][m_H[m_cur - 1] - 1 - k][i]; // 90도 회전

	drawImage();
}

/// <summary>
/// 입력 비율 만큼 축소(평균값 서브샘플링)
/// </summary>
void zoomOutImage()
{
	newCur();

	int value = 1;

	printf("축소 비율: ");
	rewind(stdin);
	scanf("%d", &value);

	if (value < 0)
		value = -value;
	else if (value == 0)
		value = 1;

	free2D(m_Image[m_cur], m_H[m_cur]);
	m_H[m_cur] = m_H[m_cur - 1] / value;
	m_W[m_cur] = m_W[m_cur - 1] / value;
	m_Image[m_cur] = malloc2D(m_H[m_cur], m_W[m_cur]);

	if (m_Image[m_cur] == NULL)
	{
		m_cur--;
		m_last = m_cur;
		MessageBox(hwnd, "메모리 부족.", "작업 창", 0);
		drawImage();
		return;
	}

	for (int i = 0; i < m_H[m_cur]; i++)
	{
		for (int k = 0; k < m_W[m_cur]; k++)
		{
			int avg = 0;

			for (int m = 0; m < value; m++) // 평균값 서브샘플링
				for (int n = 0; n < value; n++)
					avg += m_Image[m_cur - 1][i * value + m][k * value + n];

			avg /= value * value;

			m_Image[m_cur][i][k] = (UC)avg;
		}
	}

	drawImage();
}

/// <summary>
/// 입력 비율 만큼 확대(양선형 보간)
/// </summary>
void zoomInImage()
{
	newCur();

	int value = 1;

	printf("확대 비율: ");
	rewind(stdin);
	scanf("%d", &value);

	if (value < 0)
		value = -value;
	else if (value == 0)
		value = 1;

	free2D(m_Image[m_cur], m_H[m_cur]);
	m_H[m_cur] = m_H[m_cur - 1] * value;
	m_W[m_cur] = m_W[m_cur - 1] * value;
	m_Image[m_cur] = malloc2D(m_H[m_cur], m_W[m_cur]);

	if (m_Image[m_cur] == NULL)
	{
		m_cur--;
		m_last = m_cur;
		MessageBox(hwnd, "메모리 부족.", "작업 창", 0);
		drawImage();
		return;
	}

	for (int i = 0; i < m_H[m_cur]; i++)
	{
		for (int k = 0; k < m_W[m_cur]; k++)
		{
			double rx = (double)k / value; // 원본 좌표
			double ry = (double)i / value;
			int x1 = (int)rx; // 원본 좌표 근처의 점
			int y1 = (int)ry;
			int x2 = x1 + 1;
			int y2 = y1 + 1;

			if (x2 == m_W[m_cur - 1])
				x2 = m_W[m_cur - 1] - 1;
			if (y2 == m_H[m_cur - 1])
				y2 = m_H[m_cur - 1] - 1;

			double p = rx - x1; // 보간할 거리
			double q = ry - y1;

			double value = (1. - p) * (1. - q) * m_Image[m_cur - 1][y1][x1] + p * (1. - q) * m_Image[m_cur - 1][y1][x2] + (1. - p) * q * m_Image[m_cur - 1][y2][x1] + p * q * m_Image[m_cur - 1][y2][x2];

			m_Image[m_cur][i][k] = (UC)value;
		}
	}

	drawImage();
}

/// <summary>
/// 입력 x, y 만큼 위치 이동
/// </summary>
void moveImage()
{
	newCur();

	free2D(m_Image[m_cur], m_H[m_cur]);
	m_H[m_cur] = m_H[m_cur - 1];
	m_W[m_cur] = m_W[m_cur - 1];
	m_Image[m_cur] = malloc2D(m_H[m_cur], m_W[m_cur]);

	if (m_Image[m_cur] == NULL)
	{
		m_cur--;
		m_last = m_cur;
		MessageBox(hwnd, "메모리 부족.", "작업 창", 0);
		drawImage();
		return;
	}

	int x = 0, y = 0;

	printf("x 값: ");
	rewind(stdin);
	scanf("%d", &x);
	printf("y 값: ");
	rewind(stdin);
	scanf("%d", &y);

	for (int i = 0; i < m_H[m_cur]; i++)
		for (int k = 0; k < m_W[m_cur]; k++)
			if (i - y >= 0 && i - y < m_H[m_cur - 1] && k - x >= 0 && k - x < m_W[m_cur - 1])
				m_Image[m_cur][i][k] = m_Image[m_cur - 1][i - y][k - x];

	drawImage();
}

/// <summary>
/// 입력 각도 만큼 회전
/// </summary>
void rotateImage()
{
	newCur();

	int degree = 0;
	double radian = 0., radian90 = 0.;
	UC **temp;

	printf("각도 입력: ");
	rewind(stdin);
	scanf("%d", &degree);

	radian = degree * 3.1415926535 / 180;
	radian90 = (90 - degree) * 3.1415926535 / 180;

	free2D(m_Image[m_cur], m_H[m_cur]);
	// 확대할 크기 계산
	m_H[m_cur] = (int)(m_H[m_cur - 1] * fabs(cos(radian90)) + m_W[m_cur - 1] * fabs(cos(radian)));
	m_W[m_cur] = (int)(m_H[m_cur - 1] * fabs(cos(radian)) + m_W[m_cur - 1] * fabs(cos(radian90)));
	m_Image[m_cur] = malloc2D(m_H[m_cur], m_W[m_cur]);
	temp = malloc2D(m_H[m_cur], m_W[m_cur]);

	if (m_Image[m_cur] == NULL || temp == NULL)
	{
		m_cur--;
		m_last = m_cur;
		free2D(temp, m_H[m_cur]);
		MessageBox(hwnd, "메모리 부족.", "작업 창", 0);
		drawImage();
		return;
	}

	int x0, y0, dx, dy;

	dx = (m_W[m_cur] - m_W[m_cur - 1]) / 2; // 중심 이동
	dy = (m_H[m_cur] - m_H[m_cur - 1]) / 2;

	for (int i = 0; i < m_H[m_cur - 1]; i++) // 이동한 위치로 복사
		for (int k = 0; k < m_W[m_cur - 1]; k++)
			temp[i + dy][k + dx] = m_Image[m_cur - 1][i][k];

	x0 = m_W[m_cur] / 2; // 새로운 중심
	y0 = m_H[m_cur] / 2;

	for (int i = 0; i < m_H[m_cur]; i++)
	{
		for (int k = 0; k < m_W[m_cur]; k++) // 새로운 중심을 기준으로 회전
		{
			double nk = (k - x0) * cos(radian) + (i - y0) * sin(radian) + x0;
			double ni = (x0 - k) * sin(radian) + (i - y0) * cos(radian) + y0;
			if (nk >= 0 && ni >= 0 && nk < m_W[m_cur] && ni < m_H[m_cur])
			{
				int x1 = (int)nk; // 양선형 보간을 할 기준점
				int y1 = (int)ni;
				int x2 = x1 + 1;
				int y2 = y1 + 1;

				if (x2 == m_W[m_cur])
					x2 = m_W[m_cur] - 1;
				if (y2 == m_H[m_cur])
					y2 = m_H[m_cur] - 1;

				double p = nk - x1; // 기준점으로 부터 떨어진 거리
				double q = ni - y1;
				// 보간 값 계산
				double value = (1. - p) * (1. - q) * temp[y1][x1] + p * (1. - q) * temp[y1][x2] + (1. - p) * q * temp[y2][x1] + p * q * temp[y2][x2];

				m_Image[m_cur][i][k] = (UC)value;
			}
		}
	}

	free2D(temp, m_H[m_cur]);

	drawImage();
}

/// <summary>
/// 상하 미러링
/// </summary>
void udMirrorImage()
{
	newCur();

	free2D(m_Image[m_cur], m_H[m_cur]);
	m_H[m_cur] = m_W[m_cur - 1];
	m_W[m_cur] = m_H[m_cur - 1];
	m_Image[m_cur] = malloc2D(m_H[m_cur], m_W[m_cur]);

	if (m_Image[m_cur] == NULL)
	{
		m_cur--;
		m_last = m_cur;
		MessageBox(hwnd, "메모리 부족.", "작업 창", 0);
		drawImage();
		return;
	}

	for (int i = 0; i < m_H[m_cur]; i++)
		for (int k = 0; k < m_W[m_cur]; k++)
			m_Image[m_cur][i][k] = m_Image[m_cur - 1][m_H[m_cur - 1] - 1 - i][k];

	drawImage();
}

/// <summary>
/// 좌우 미러링
/// </summary>
void lrMirrorImage()
{
	newCur();

	free2D(m_Image[m_cur], m_H[m_cur]);
	m_H[m_cur] = m_W[m_cur - 1];
	m_W[m_cur] = m_H[m_cur - 1];
	m_Image[m_cur] = malloc2D(m_H[m_cur], m_W[m_cur]);

	if (m_Image[m_cur] == NULL)
	{
		m_cur--;
		m_last = m_cur;
		MessageBox(hwnd, "메모리 부족.", "작업 창", 0);
		drawImage();
		return;
	}

	for (int i = 0; i < m_H[m_cur]; i++)
		for (int k = 0; k < m_W[m_cur]; k++)
			m_Image[m_cur][i][k] = m_Image[m_cur - 1][i][m_W[m_cur - 1] - 1 - k];

	drawImage();
}

/// <summary>
/// 더블형 2차원 메모리 할당 (h x w)
/// </summary>
/// <param name="h">높이 (포인터 배열)</param>
/// <param name="w">폭 (배열)</param>
/// <returns></returns>
double **malloc2Ddouble(int h, int w)
{
	double **memory = (double **)malloc(h * sizeof(double *)); // 포인터 배열 할당

	if (memory == NULL)
		return NULL;

	for (int i = 0; i < h; i++)
	{ // 각 포인터에 배열 할당
		memory[i] = (double *)malloc(w * sizeof(double));

		if (memory[i] == NULL)
		{								// 할당에 실패한 배열이 있으면
			for (int k = 0; k < i; k++) // 지금까지 할당한 메모리를 모두 반환하고
				free(memory[k]);

			free(memory);
			return NULL; // NULL 반환
		}

		for (int k = 0; k < w; k++) // 초기화
			memory[i][k] = 128;
	}
	return memory; // 모두 할당에 성공한 경우
}

/// <summary>
/// 더블형 2차원 메모리 할당 해제
/// </summary>
/// <param name="memory">해제하려는 메모리</param>
/// <param name="h">해제하려는 메모리의 높이</param>
void free2Ddouble(double **memory, int h)
{
	if (memory == NULL) // 할당된 적이 없으면 아무것도 안함
		return;

	for (int i = 0; i < h; i++)
		free(memory[i]);
	free(memory);
}

/// <summary>
/// 엠보싱 알고리즘
/// </summary>
void emboss()
{
	newCur();

	free2D(m_Image[m_cur], m_H[m_cur]);
	m_H[m_cur] = m_W[m_cur - 1];
	m_W[m_cur] = m_H[m_cur - 1];
	m_Image[m_cur] = malloc2D(m_H[m_cur], m_W[m_cur]);

	// 알고리즘에 해당하는 마스크
	double mask[3][3] = {{-1, 0, 0},
						 {0, 0, 0},
						 {0, 0, 1}};

	double **tmpInput = malloc2Ddouble(m_H[m_cur - 1] + 2, m_W[m_cur - 1] + 2);
	double **tmpOutput = malloc2Ddouble(m_H[m_cur], m_W[m_cur]);

	if (m_Image[m_cur] == NULL || tmpInput == NULL || tmpOutput == NULL)
	{
		m_cur--;
		m_last = m_cur;
		free2Ddouble(tmpInput, m_H[m_cur - 1] + 2);
		free2Ddouble(tmpOutput, m_H[m_cur]);
		MessageBox(hwnd, "메모리 부족.", "작업 창", 0);
		drawImage();
		return;
	}

	double S = 0; // 마스크 9개 X 입력영상 9개의 합

	for (int i = 0; i < m_H[m_cur - 1]; i++)
		for (int k = 0; k < m_W[m_cur - 1]; k++)
			tmpInput[i + 1][k + 1] = m_Image[m_cur - 1][i][k];

	for (int i = 0; i < m_H[m_cur]; i++)
	{
		for (int k = 0; k < m_W[m_cur]; k++)
		{
			S = 0;

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInput[i + m][k + n] * mask[m][n];

			tmpOutput[i][k] = S;
		}
	}

	// 마스크의 합이 0이면 127 더하기
	for (int i = 0; i < m_H[m_cur]; i++)
		for (int k = 0; k < m_W[m_cur]; k++)
			tmpOutput[i][k] += 127.0;

	// tmpOutput -> Output
	for (int i = 0; i < m_H[m_cur]; i++)
	{
		for (int k = 0; k < m_W[m_cur]; k++)
		{
			double v = tmpOutput[i][k];

			if (v > 255.0)
				v = 255.0;
			else if (v < 0)
				v = 0;

			m_Image[m_cur][i][k] = (UC)v;
		}
	}

	free2Ddouble(tmpInput, m_H[m_cur - 1] + 2);
	free2Ddouble(tmpOutput, m_H[m_cur]);

	drawImage();
}

/// <summary>
/// 블러 알고리즘
/// </summary>
void blur()
{
	newCur();

	free2D(m_Image[m_cur], m_H[m_cur]);
	m_H[m_cur] = m_W[m_cur - 1];
	m_W[m_cur] = m_H[m_cur - 1];
	m_Image[m_cur] = malloc2D(m_H[m_cur], m_W[m_cur]);

	int value = 1;
	int append;
	int offset;

	printf("블러 세기(1 ~ 20): ");
	rewind(stdin);
	scanf("%d", &value);

	if (value < 1 || value > 20)
		value = 1;

	value = value * 2 + 1; // 입력강도를 마스크 크기로
	append = value - 1;	   // 마스크가 넘치는 만큼 늘려줘야 함
	offset = value / 2;	   // 인풋을 확장한 배열에 그리기 위한 오프셋

	// 메모리 할당
	double **mask = malloc2Ddouble(value, value);
	double **tmpInput = malloc2Ddouble(m_H[m_cur - 1] + append, m_W[m_cur - 1] + append);
	double **tmpOutput = malloc2Ddouble(m_H[m_cur], m_W[m_cur]);

	if (m_Image[m_cur] == NULL || tmpInput == NULL || tmpOutput == NULL || mask == NULL)
	{
		m_cur--;
		m_last = m_cur;
		free2Ddouble(mask, value);
		free2Ddouble(tmpInput, m_H[m_cur - 1] + 2);
		free2Ddouble(tmpOutput, m_H[m_cur]);
		MessageBox(hwnd, "메모리 부족.", "작업 창", 0);
		drawImage();
		return;
	}

	double S = 0; // 마스크 9개 X 입력영상 9개의 합

	// 마스크 생성
	for (int i = 0; i < value; i++)
		for (int k = 0; k < value; k++)
			mask[i][k] = 1.0 / (value * value);

	for (int i = 0; i < m_H[m_cur - 1]; i++)
		for (int k = 0; k < m_W[m_cur - 1]; k++)
			tmpInput[i + offset][k + offset] = m_Image[m_cur - 1][i][k];

	for (int i = 0; i < m_H[m_cur]; i++)
	{
		for (int k = 0; k < m_W[m_cur]; k++)
		{
			S = 0;

			for (int m = 0; m < value; m++)
				for (int n = 0; n < value; n++)
					S += tmpInput[i + m][k + n] * mask[m][n];

			tmpOutput[i][k] = S;
		}
	}

	// 마스크의 합이 0이면 127 더하기
	//for (int i = 0; i < m_H[m_cur]; i++)
	//	for (int k = 0; k < m_W[m_cur]; k++)
	//		tmpOutput[i][k] += 127.0;

	// tmpOutput -> Output
	for (int i = 0; i < m_H[m_cur]; i++)
	{
		for (int k = 0; k < m_W[m_cur]; k++)
		{
			double v = tmpOutput[i][k];

			if (v > 255.0)
				v = 255.0;
			else if (v < 0)
				v = 0;

			m_Image[m_cur][i][k] = (UC)v;
		}
	}

	free2Ddouble(mask, value);
	free2Ddouble(tmpInput, m_H[m_cur - 1] + append);
	free2Ddouble(tmpOutput, m_H[m_cur]);

	drawImage();
}

/// <summary>
/// 가우시안 알고리즘
/// </summary>
void gauss()
{
	newCur();

	free2D(m_Image[m_cur], m_H[m_cur]);
	m_H[m_cur] = m_H[m_cur - 1];
	m_W[m_cur] = m_W[m_cur - 1];
	m_Image[m_cur] = malloc2D(m_H[m_cur], m_W[m_cur]);

	// 알고리즘에 해당하는 마스크
	double mask[3][3] = {{1 / 16.0, 1 / 8.0, 1 / 16.0},
						 {1 / 8.0, 1 / 4.0, 1 / 8.0},
						 {1 / 16.0, 1 / 8.0, 1 / 16.0}};

	double **tmpInput = malloc2Ddouble(m_H[m_cur - 1] + 2, m_W[m_cur - 1] + 2);
	double **tmpOutput = malloc2Ddouble(m_H[m_cur], m_W[m_cur]);

	if (m_Image[m_cur] == NULL || tmpInput == NULL || tmpOutput == NULL)
	{
		m_cur--;
		m_last = m_cur;
		free2Ddouble(tmpInput, m_H[m_cur - 1] + 2);
		free2Ddouble(tmpOutput, m_H[m_cur]);
		MessageBox(hwnd, "메모리 부족.", "작업 창", 0);
		drawImage();
		return;
	}

	double S = 0; // 마스크 9개 X 입력영상 9개의 합

	for (int i = 0; i < m_H[m_cur - 1]; i++)
		for (int k = 0; k < m_W[m_cur - 1]; k++)
			tmpInput[i + 1][k + 1] = m_Image[m_cur - 1][i][k];

	for (int i = 0; i < m_H[m_cur]; i++)
	{
		for (int k = 0; k < m_W[m_cur]; k++)
		{
			S = 0;

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInput[i + m][k + n] * mask[m][n];

			tmpOutput[i][k] = S;
		}
	}

	// 마스크의 합이 0이면 127 더하기
	//for (int i = 0; i < m_H[m_cur]; i++)
	//	for (int k = 0; k < m_W[m_cur]; k++)
	//		tmpOutput[i][k] += 127.0;

	// tmpOutput -> Output
	for (int i = 0; i < m_H[m_cur]; i++)
	{
		for (int k = 0; k < m_W[m_cur]; k++)
		{
			double v = tmpOutput[i][k];

			if (v > 255.0)
				v = 255.0;
			else if (v < 0)
				v = 0;

			m_Image[m_cur][i][k] = (UC)v;
		}
	}

	free2Ddouble(tmpInput, m_H[m_cur - 1] + 2);
	free2Ddouble(tmpOutput, m_H[m_cur]);

	drawImage();
}

/// <summary>
/// 샤프닝 알고리즘
/// </summary>
void sharpen()
{
	newCur();

	free2D(m_Image[m_cur], m_H[m_cur]);
	m_H[m_cur] = m_H[m_cur - 1];
	m_W[m_cur] = m_W[m_cur - 1];
	m_Image[m_cur] = malloc2D(m_H[m_cur], m_W[m_cur]);

	// 알고리즘에 해당하는 마스크
	double mask[3][3] = {{0, -1, 0},
						 {-1, 5, -1},
						 {0, -1, 0}};

	double **tmpInput = malloc2Ddouble(m_H[m_cur - 1] + 2, m_W[m_cur - 1] + 2);
	double **tmpOutput = malloc2Ddouble(m_H[m_cur], m_W[m_cur]);

	if (m_Image[m_cur] == NULL || tmpInput == NULL || tmpOutput == NULL)
	{
		m_cur--;
		m_last = m_cur;
		free2Ddouble(tmpInput, m_H[m_cur - 1] + 2);
		free2Ddouble(tmpOutput, m_H[m_cur]);
		MessageBox(hwnd, "메모리 부족.", "작업 창", 0);
		drawImage();
		return;
	}

	double S = 0; // 마스크 9개 X 입력영상 9개의 합

	for (int i = 0; i < m_H[m_cur - 1]; i++)
		for (int k = 0; k < m_W[m_cur - 1]; k++)
			tmpInput[i + 1][k + 1] = m_Image[m_cur - 1][i][k];

	for (int i = 0; i < m_H[m_cur]; i++)
	{
		for (int k = 0; k < m_W[m_cur]; k++)
		{
			S = 0;

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInput[i + m][k + n] * mask[m][n];

			tmpOutput[i][k] = S;
		}
	}

	// 마스크의 합이 0이면 127 더하기
	//for (int i = 0; i < m_H[m_cur]; i++)
	//	for (int k = 0; k < m_W[m_cur]; k++)
	//		tmpOutput[i][k] += 127.0;

	// tmpOutput -> Output
	for (int i = 0; i < m_H[m_cur]; i++)
	{
		for (int k = 0; k < m_W[m_cur]; k++)
		{
			double v = tmpOutput[i][k];

			if (v > 255.0)
				v = 255.0;
			else if (v < 0)
				v = 0;

			m_Image[m_cur][i][k] = (UC)v;
		}
	}

	free2Ddouble(tmpInput, m_H[m_cur - 1] + 2);
	free2Ddouble(tmpOutput, m_H[m_cur]);

	drawImage();
}

/// <summary>
/// 저주파 필터 샤프닝 알고리즘
/// </summary>
void lpfSharpen()
{
	newCur();

	free2D(m_Image[m_cur], m_H[m_cur]);
	m_H[m_cur] = m_H[m_cur - 1];
	m_W[m_cur] = m_W[m_cur - 1];
	m_Image[m_cur] = malloc2D(m_H[m_cur], m_W[m_cur]);

	// 알고리즘에 해당하는 마스크
	double mask[3][3] = {{1 / 9.0, 1 / 9.0, 1 / 9.0},
						 {1 / 9.0, 1 / 9.0, 1 / 9.0},
						 {1 / 9.0, 1 / 9.0, 1 / 9.0}};

	double **tmpInput = malloc2Ddouble(m_H[m_cur - 1] + 2, m_W[m_cur - 1] + 2);
	double **tmpOutput = malloc2Ddouble(m_H[m_cur], m_W[m_cur]);

	if (m_Image[m_cur] == NULL || tmpInput == NULL || tmpOutput == NULL)
	{
		m_cur--;
		m_last = m_cur;
		free2Ddouble(tmpInput, m_H[m_cur - 1] + 2);
		free2Ddouble(tmpOutput, m_H[m_cur]);
		MessageBox(hwnd, "메모리 부족.", "작업 창", 0);
		drawImage();
		return;
	}

	double a = 1.0; // 게인
	double S = 0;	// 마스크 9개 X 입력영상 9개의 합

	for (int i = 0; i < m_H[m_cur - 1]; i++)
		for (int k = 0; k < m_W[m_cur - 1]; k++)
			tmpInput[i + 1][k + 1] = m_Image[m_cur - 1][i][k];

	for (int i = 0; i < m_H[m_cur]; i++) // 저주파 필터 적용
	{
		for (int k = 0; k < m_W[m_cur]; k++)
		{
			S = 0;

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInput[i + m][k + n] * mask[m][n];

			tmpOutput[i][k] = S;
		}
	}

	printf("게인 값(1.0 ~ 3.0): ");
	rewind(stdin);
	scanf("%lf", &a);

	if (a < 1.0 || a > 3.0)
		a = 2.0;

	for (int i = 0; i < m_H[m_cur - 1]; i++) // 고주파 지원
		for (int k = 0; k < m_W[m_cur - 1]; k++)
			tmpOutput[i][k] = a * m_Image[m_cur - 1][i][k] - tmpOutput[i][k];

	// tmpOutput -> Output
	for (int i = 0; i < m_H[m_cur]; i++)
	{
		for (int k = 0; k < m_W[m_cur]; k++)
		{
			double v = tmpOutput[i][k];

			if (v > 255.0)
				v = 255.0;
			else if (v < 0)
				v = 0;

			m_Image[m_cur][i][k] = (UC)v;
		}
	}

	free2Ddouble(tmpInput, m_H[m_cur - 1] + 2);
	free2Ddouble(tmpOutput, m_H[m_cur]);

	drawImage();
}

/// <summary>
/// 유사 연산자 알고리즘
/// </summary>
void homogen()
{
	newCur();

	free2D(m_Image[m_cur], m_H[m_cur]);
	m_H[m_cur] = m_H[m_cur - 1];
	m_W[m_cur] = m_W[m_cur - 1];
	m_Image[m_cur] = malloc2D(m_H[m_cur], m_W[m_cur]);

	double **tmpInput = malloc2Ddouble(m_H[m_cur - 1] + 2, m_W[m_cur - 1] + 2);
	double **tmpOutput = malloc2Ddouble(m_H[m_cur], m_W[m_cur]);

	if (m_Image[m_cur] == NULL || tmpInput == NULL || tmpOutput == NULL)
	{
		m_cur--;
		m_last = m_cur;
		free2Ddouble(tmpInput, m_H[m_cur - 1] + 2);
		free2Ddouble(tmpOutput, m_H[m_cur]);
		MessageBox(hwnd, "메모리 부족.", "작업 창", 0);
		drawImage();
		return;
	}

	for (int i = 0; i < m_H[m_cur - 1]; i++)
		for (int k = 0; k < m_W[m_cur - 1]; k++)
			tmpInput[i + 1][k + 1] = m_Image[m_cur - 1][i][k];

	for (int i = 0; i < m_H[m_cur]; i++) // 모든 화소에 대해
	{
		for (int k = 0; k < m_W[m_cur]; k++)
		{
			double S = 0.; // |center - m|
			double max = 0.;

			for (int m = 0; m < 3; m++) // 3 X 3 범위로 가운데 화소의 값과 주변 화소의 차를 구함
			{
				for (int n = 0; n < 3; n++)
				{
					if (m != 1 || n != 1) // 가운데는 계산하지 않음
					{
						S = fabs(tmpInput[i + 1][k + 1] - tmpInput[i + m][k + n]);
						if (S > max)
							max = S;
					}
				}
			}

			tmpOutput[i][k] = max;
		}
	}

	// tmpOutput -> Output
	for (int i = 0; i < m_H[m_cur]; i++)
		for (int k = 0; k < m_W[m_cur]; k++)
			m_Image[m_cur][i][k] = (UC)tmpOutput[i][k];

	free2Ddouble(tmpInput, m_H[m_cur - 1] + 2);
	free2Ddouble(tmpOutput, m_H[m_cur]);

	drawImage();
}

/// <summary>
/// 차 연산자 알고리즘
/// </summary>
void differ()
{
	newCur();

	free2D(m_Image[m_cur], m_H[m_cur]);
	m_H[m_cur] = m_H[m_cur - 1];
	m_W[m_cur] = m_W[m_cur - 1];
	m_Image[m_cur] = malloc2D(m_H[m_cur], m_W[m_cur]);

	double **tmpInput = malloc2Ddouble(m_H[m_cur - 1] + 2, m_W[m_cur - 1] + 2);
	double **tmpOutput = malloc2Ddouble(m_H[m_cur], m_W[m_cur]);

	if (m_Image[m_cur] == NULL || tmpInput == NULL || tmpOutput == NULL)
	{
		m_cur--;
		m_last = m_cur;
		free2Ddouble(tmpInput, m_H[m_cur - 1] + 2);
		free2Ddouble(tmpOutput, m_H[m_cur]);
		MessageBox(hwnd, "메모리 부족.", "작업 창", 0);
		drawImage();
		return;
	}

	for (int i = 0; i < m_H[m_cur - 1]; i++)
		for (int k = 0; k < m_W[m_cur - 1]; k++)
			tmpInput[i + 1][k + 1] = m_Image[m_cur - 1][i][k];

	for (int i = 0; i < m_H[m_cur]; i++) // 모든 화소에 대해
	{
		for (int k = 0; k < m_W[m_cur]; k++)
		{
			double S[4] = {0.}; // |대각선 끼리의 차|
			double max = 0.;

			for (int m = 0; m < 3; m++) // 3 X 3 범위로 대각선 성분들의 차를 구함
				S[m] = fabs(tmpInput[i][k + m] - tmpInput[i + 2][k + 2 - m]);
			S[3] = fabs(tmpInput[i + 1][k] - tmpInput[i + 1][k + 2]);

			for (int m = 0; m < 4; m++)
				if (S[m] > max)
					max = S[m];

			tmpOutput[i][k] = max;
		}
	}

	// tmpOutput -> Output
	for (int i = 0; i < m_H[m_cur]; i++)
		for (int k = 0; k < m_W[m_cur]; k++)
			m_Image[m_cur][i][k] = (UC)tmpOutput[i][k];

	free2Ddouble(tmpInput, m_H[m_cur - 1] + 2);
	free2Ddouble(tmpOutput, m_H[m_cur]);

	drawImage();
}

/// <summary>
/// 2차 라플라시안 알고리즘
/// </summary>
void LoG()
{
	newCur();

	free2D(m_Image[m_cur], m_H[m_cur]);
	m_H[m_cur] = m_H[m_cur - 1];
	m_W[m_cur] = m_W[m_cur - 1];
	m_Image[m_cur] = malloc2D(m_H[m_cur], m_W[m_cur]);

	// 알고리즘에 해당하는 마스크
	double mask[5][5] = {{0, 0, -1, 0, 0},
						 {0, -1, -2, -1, 0},
						 {-1, -2, 16, -2, -1},
						 {0, -1, -2, -1, 0},
						 {0, 0, -1, 0, 0}};

	double **tmpInput = malloc2Ddouble(m_H[m_cur - 1] + 4, m_W[m_cur - 1] + 4);
	double **tmpOutput = malloc2Ddouble(m_H[m_cur], m_W[m_cur]);

	if (m_Image[m_cur] == NULL || tmpInput == NULL || tmpOutput == NULL)
	{
		m_cur--;
		m_last = m_cur;
		free2Ddouble(tmpInput, m_H[m_cur - 1] + 2);
		free2Ddouble(tmpOutput, m_H[m_cur]);
		MessageBox(hwnd, "메모리 부족.", "작업 창", 0);
		drawImage();
		return;
	}

	double S = 0; // 마스크 25개 X 입력영상 25개의 합

	for (int i = 0; i < m_H[m_cur - 1]; i++)
		for (int k = 0; k < m_W[m_cur - 1]; k++)
			tmpInput[i + 2][k + 2] = m_Image[m_cur - 1][i][k];

	for (int i = 0; i < m_H[m_cur]; i++)
	{
		for (int k = 0; k < m_W[m_cur]; k++)
		{
			S = 0;

			for (int m = 0; m < 5; m++)
				for (int n = 0; n < 5; n++)
					S += tmpInput[i + m][k + n] * mask[m][n];

			tmpOutput[i][k] = S;
		}
	}

	// 마스크의 합이 0이면 127 더하기
	// 경계선 검출에서는 더하기 하지 않는 것이 보기에 더 좋다.
	//for (int i = 0; i < m_H[m_cur]; i++)
	//	for (int k = 0; k < m_W[m_cur]; k++)
	//		tmpOutput[i][k] += 127.0;

	// tmpOutput -> Output
	for (int i = 0; i < m_H[m_cur]; i++)
	{
		for (int k = 0; k < m_W[m_cur]; k++)
		{
			double v = tmpOutput[i][k];

			if (v > 255.0)
				v = 255.0;
			else if (v < 0)
				v = 0;

			m_Image[m_cur][i][k] = (UC)v;
		}
	}

	free2Ddouble(tmpInput, m_H[m_cur - 1] + 4);
	free2Ddouble(tmpOutput, m_H[m_cur]);

	drawImage();
}

/// <summary>
/// DoG 알고리즘
/// </summary>
void DoG()
{
	newCur();

	free2D(m_Image[m_cur], m_H[m_cur]);
	m_H[m_cur] = m_H[m_cur - 1];
	m_W[m_cur] = m_W[m_cur - 1];
	m_Image[m_cur] = malloc2D(m_H[m_cur], m_W[m_cur]);

	// 알고리즘에 해당하는 마스크
	double mask[9][9] = {{0, 0, 0, -1, -1, -1, 0, 0, 0},
						 {0, -2, -3, -3, -3, -3, -3, -2, 0},
						 {0, -3, -2, -1, -1, -1, -2, -3, 0},
						 {-1, -3, -1, 9, 9, 9, -1, -3, -1},
						 {-1, -3, -1, 9, 19, 9, -1, -3, -1},
						 {-1, -3, -1, 9, 9, 9, -1, -3, -1},
						 {0, -3, -2, -1, -1, -1, -2, -3, 0},
						 {0, -2, -3, -3, -3, -3, -3, -2, 0},
						 {0, 0, 0, -1, -1, -1, 0, 0, 0}};

	double **tmpInput = malloc2Ddouble(m_H[m_cur - 1] + 8, m_W[m_cur - 1] + 8);
	double **tmpOutput = malloc2Ddouble(m_H[m_cur], m_W[m_cur]);

	if (m_Image[m_cur] == NULL || tmpInput == NULL || tmpOutput == NULL)
	{
		m_cur--;
		m_last = m_cur;
		free2Ddouble(tmpInput, m_H[m_cur - 1] + 2);
		free2Ddouble(tmpOutput, m_H[m_cur]);
		MessageBox(hwnd, "메모리 부족.", "작업 창", 0);
		drawImage();
		return;
	}

	double S = 0; // 마스크 81개 X 입력영상 81개의 합

	for (int i = 0; i < m_H[m_cur - 1]; i++)
		for (int k = 0; k < m_W[m_cur - 1]; k++)
			tmpInput[i + 4][k + 4] = m_Image[m_cur - 1][i][k];

	for (int i = 0; i < m_H[m_cur]; i++)
	{
		for (int k = 0; k < m_W[m_cur]; k++)
		{
			S = 0;

			for (int m = 0; m < 9; m++)
				for (int n = 0; n < 9; n++)
					S += tmpInput[i + m][k + n] * mask[m][n];

			tmpOutput[i][k] = S;
		}
	}

	// tmpOutput -> Output
	for (int i = 0; i < m_H[m_cur]; i++)
	{
		for (int k = 0; k < m_W[m_cur]; k++)
		{
			double v = tmpOutput[i][k];

			if (v > 255.0)
				v = 255.0;
			else if (v < 0)
				v = 0;

			m_Image[m_cur][i][k] = (UC)v;
		}
	}

	free2Ddouble(tmpInput, m_H[m_cur - 1] + 8);
	free2Ddouble(tmpOutput, m_H[m_cur]);

	drawImage();
}

/// <summary>
/// 대비 조절 알고리즘
/// </summary>
void contrast()
{
	newCur();

	free2D(m_Image[m_cur], m_H[m_cur]);
	m_H[m_cur] = m_H[m_cur - 1];
	m_W[m_cur] = m_W[m_cur - 1];
	m_Image[m_cur] = malloc2D(m_H[m_cur], m_W[m_cur]);

	if (m_Image[m_cur] == NULL)
	{
		m_cur--;
		m_last = m_cur;
		MessageBox(hwnd, "메모리 부족.", "작업 창", 0);
		drawImage();
		return;
	}

	double val = 1.0;

	printf("대비 값(0.0 ~ 2.0): ");
	rewind(stdin);
	scanf("%lf", &val);

	if (val < 0.0 || val > 2)
		val = 1;

	for (int i = 0; i < m_H[m_cur - 1]; i++)
	{
		for (int k = 0; k < m_W[m_cur - 1]; k++)
		{
			double pixel = m_Image[m_cur - 1][i][k] + (val - 1) * (m_Image[0][i][k] - 127);

			if (pixel > 255)
				pixel = 255;
			else if (pixel < 0)
				pixel = 0;

			m_Image[m_cur][i][k] = (UC)pixel;
		}
	}

	drawImage();
}

/// <summary>
/// 히스토그램 평활
/// </summary>
void histoSmooth()
{
	newCur();

	int histogram[256] = {
		0,
	};
	int cumulative_histogram[256] = {
		0,
	};
	float normalized_cumulative_histogram[256] = {
		0.,
	};
	int image_size = m_H[m_cur - 1] * m_W[m_cur - 1];
	int sum = 0;

	free2D(m_Image[m_cur], m_H[m_cur]);
	m_H[m_cur] = m_H[m_cur - 1];
	m_W[m_cur] = m_W[m_cur - 1];
	m_Image[m_cur] = malloc2D(m_H[m_cur], m_W[m_cur]);

	if (m_Image[m_cur] == NULL)
	{
		m_cur--;
		m_last = m_cur;
		MessageBox(hwnd, "메모리 부족.", "작업 창", 0);
		drawImage();
		return;
	}

	for (int i = 0; i < m_H[m_cur - 1]; i++)
		for (int k = 0; k < m_W[m_cur - 1]; k++)
			histogram[m_Image[m_cur - 1][i][k]]++;

	for (int i = 1; i < 256; i++)
	{
		sum += histogram[i];
		cumulative_histogram[i] = sum;
	}

	for (int i = 0; i < 256; i++)
		normalized_cumulative_histogram[i] = cumulative_histogram[i] / (float)image_size;

	for (int i = 0; i < m_H[m_cur - 1]; i++)
		for (int k = 0; k < m_W[m_cur - 1]; k++)
			m_Image[m_cur][i][k] = (UC)(normalized_cumulative_histogram[m_Image[m_cur - 1][i][k]] * 255);

	drawImage();
}

/// <summary>
/// 히스토그램 스트레칭 엔드-인
/// </summary>
void histoStretch()
{
	newCur();

	int max = m_Image[m_cur - 1][0][0], min = m_Image[m_cur - 1][0][0];

	free2D(m_Image[m_cur], m_H[m_cur]);
	m_H[m_cur] = m_H[m_cur - 1];
	m_W[m_cur] = m_W[m_cur - 1];
	m_Image[m_cur] = malloc2D(m_H[m_cur], m_W[m_cur]);

	if (m_Image[m_cur] == NULL)
	{
		m_cur--;
		m_last = m_cur;
		MessageBox(hwnd, "메모리 부족.", "작업 창", 0);
		drawImage();
		return;
	}

	for (int i = 0; i < m_H[m_cur - 1]; i++)
	{
		for (int k = 0; k < m_W[m_cur - 1]; k++)
		{
			if (min > m_Image[m_cur - 1][i][k])
				min = m_Image[m_cur - 1][i][k];
			if (max < m_Image[m_cur - 1][i][k])
				max = m_Image[m_cur - 1][i][k];
		}
	}

	for (int i = 0; i < m_H[m_cur]; i++)
	{
		for (int k = 0; k < m_W[m_cur]; k++)
		{
			if (m_Image[m_cur - 1][i][k] < min)
				m_Image[m_cur][i][k] = 0;
			else if (m_Image[m_cur - 1][i][k] > max)
				m_Image[m_cur][i][k] = 255;
			else
				m_Image[m_cur][i][k] = 255 * (m_Image[m_cur - 1][i][k] - min) / (max - min);
		}
	}

	drawImage();
}

/// <summary>
/// 마스크용 이미지 로드
/// </summary>
void openMaskImage(UC **mask)
{
	char fullName[160] = "";
	char tmpName[50] = "";
	printf("마스크 파일명: ");
	rewind(stdin);
	scanf("%s", tmpName);

	if (tmpName[49] != 0)
	{
		printf("파일 이름이 최대 길이(49자)를 초과했습니다.\n");
		return;
	}

	strcpy(fullName, m_dir);
	strcat(fullName, tmpName);
	strcat(fullName, ".raw");

	FILE *rfp;
	rfp = fopen(fullName, "rb");
	if (rfp == NULL)
	{
		printf("파일 읽기 실패.\n");
		return;
	}
	// 파일 크기 알아내기
	fseek(rfp, 0L, SEEK_END);
	unsigned long fsize = ftell(rfp);
	fseek(rfp, 0L, SEEK_SET);
	// 마스크 크기 검사
	if (fsize != m_H[m_cur] * m_W[m_cur])
	{
		fclose(rfp);
		printf("마스크의 크기가 원본과 다릅니다.\n");
		return;
	}
	// 파일 --> 메모리로 로딩
	for (int i = 0; i < m_H[m_cur]; i++)
		fread(mask[i], sizeof(UC), m_W[m_cur], rfp);

	fclose(rfp);
}

/// <summary>
/// 머지 알고리즘
/// </summary>
void mergeImage()
{
	newCur();

	UC **tmp;

	free2D(m_Image[m_cur], m_H[m_cur]);
	m_H[m_cur] = m_H[m_cur - 1];
	m_W[m_cur] = m_W[m_cur - 1];
	m_Image[m_cur] = malloc2D(m_H[m_cur], m_W[m_cur]);
	tmp = malloc2D(m_H[m_cur], m_W[m_cur]);

	if (m_Image[m_cur] == NULL || tmp == NULL)
	{
		m_cur--;
		m_last = m_cur;
		free2D(tmp, m_H[m_cur]);
		MessageBox(hwnd, "메모리 부족.", "작업 창", 0);
		drawImage();
		return;
	}

	double val = 1.0;

	openMaskImage(tmp);

	printf("비율 값(0.0 ~ 1.0): ");
	rewind(stdin);
	scanf("%lf", &val);

	if (val < 0. || val > 1.)
		val = 1.0;

	for (int i = 0; i < m_H[m_cur - 1]; i++)
		for (int k = 0; k < m_W[m_cur - 1]; k++)
			m_Image[m_cur][i][k] = (UC)(val * m_Image[m_cur - 1][i][k] + (1 - val) * tmp[i][k]);

	free2D(tmp, m_H[m_cur]);

	drawImage();
}

/// <summary>
/// 원을 생성
/// </summary>
/// <param name="Result">원을 생성해서 저장할 배열</param>
/// <param name="diameter">만들 원의 반경</param>
void Circle(UC **Result, int diameter)
{
	int i, j;
	double tmp, xSqure, ySqure;

	for (i = 0; i < m_H[m_cur]; i++)
	{
		for (j = 0; j < m_W[m_cur]; j++)
		{
			ySqure = (abs(m_H[m_cur] / 2 - i)) * (abs(m_H[m_cur] / 2 - i));
			xSqure = (abs(m_W[m_cur] / 2 - j)) * (abs(m_W[m_cur] / 2 - j));
			tmp = sqrt(ySqure + xSqure);

			if (tmp < diameter)
				Result[i][j] = 255;
			else
				Result[i][j] = 0;
		}
	}
}

/// <summary>
/// 원을 생성하여 and 연산
/// </summary>
void circleAndImage()
{
	newCur();

	UC **tmp;

	free2D(m_Image[m_cur], m_H[m_cur]);
	m_H[m_cur] = m_H[m_cur - 1];
	m_W[m_cur] = m_W[m_cur - 1];
	m_Image[m_cur] = malloc2D(m_H[m_cur], m_W[m_cur]);
	tmp = malloc2D(m_H[m_cur], m_W[m_cur]);

	if (m_Image[m_cur] == NULL || tmp == NULL)
	{
		m_cur--;
		m_last = m_cur;
		free2D(tmp, m_H[m_cur]);
		MessageBox(hwnd, "메모리 부족.", "작업 창", 0);
		drawImage();
		return;
	}

	int val = 1;

	printf("원의 반지름: ");
	rewind(stdin);
	scanf("%d", &val);

	if (val < 1)
		val = 1;

	Circle(tmp, val);

	for (int i = 0; i < m_H[m_cur - 1]; i++)
		for (int k = 0; k < m_W[m_cur - 1]; k++)
			m_Image[m_cur][i][k] = m_Image[m_cur - 1][i][k] & tmp[i][k];

	free2D(tmp, m_H[m_cur]);

	drawImage();
}

/// <summary>
/// 영상 포스터라이징 (레벨8)
/// </summary>
void posterImage()
{
	newCur();

	free2D(m_Image[m_cur], m_H[m_cur]);
	m_H[m_cur] = m_H[m_cur - 1];
	m_W[m_cur] = m_W[m_cur - 1];
	m_Image[m_cur] = malloc2D(m_H[m_cur], m_W[m_cur]);

	if (m_Image[m_cur] == NULL)
	{
		m_cur--;
		m_last = m_cur;
		MessageBox(hwnd, "메모리 부족.", "작업 창", 0);
		drawImage();
		return;
	}

	for (int i = 0; i < m_H[m_cur - 1]; i++)
	{
		for (int k = 0; k < m_W[m_cur - 1]; k++)
		{
			if (m_Image[m_cur - 1][i][k] < 32)
				m_Image[m_cur][i][k] = 0;
			else if (m_Image[m_cur - 1][i][k] < 64)
				m_Image[m_cur][i][k] = 36;
			else if (m_Image[m_cur - 1][i][k] < 96)
				m_Image[m_cur][i][k] = 72;
			else if (m_Image[m_cur - 1][i][k] < 128)
				m_Image[m_cur][i][k] = 108;
			else if (m_Image[m_cur - 1][i][k] < 160)
				m_Image[m_cur][i][k] = 144;
			else if (m_Image[m_cur - 1][i][k] < 192)
				m_Image[m_cur][i][k] = 181;
			else if (m_Image[m_cur - 1][i][k] < 224)
				m_Image[m_cur][i][k] = 218;
			else
				m_Image[m_cur][i][k] = 255;
		}
	}

	drawImage();
}

/// <summary>
/// 부분 강조
/// </summary>
void partImage()
{
	newCur();

	free2D(m_Image[m_cur], m_H[m_cur]);
	m_H[m_cur] = m_H[m_cur - 1];
	m_W[m_cur] = m_W[m_cur - 1];
	m_Image[m_cur] = malloc2D(m_H[m_cur], m_W[m_cur]);

	if (m_Image[m_cur] == NULL)
	{
		m_cur--;
		m_last = m_cur;
		MessageBox(hwnd, "메모리 부족.", "작업 창", 0);
		drawImage();
		return;
	}

	int h = 255, l = 0;

	printf("강조 시작 밝기: ");
	rewind(stdin);
	scanf("%d", &l);
	printf("강조할 범위: ");
	rewind(stdin);
	scanf("%d", &h);

	if (l < 0 || l > 255)
		l = 0;

	h += l;
	if (h < 0 || h > 255)
		h = 255;

	for (int i = 0; i < m_H[m_cur - 1]; i++)
	{
		for (int k = 0; k < m_W[m_cur - 1]; k++)
		{
			if (m_Image[m_cur - 1][i][k] >= l && m_Image[m_cur - 1][i][k] <= h)
				m_Image[m_cur][i][k] = 255;
			else
				m_Image[m_cur][i][k] = m_Image[m_cur - 1][i][k];
		}
	}

	drawImage();
}

/// <summary>
/// hpf 샤프닝 알고리즘
/// </summary>
void hpfSharpen()
{
	newCur();

	free2D(m_Image[m_cur], m_H[m_cur]);
	m_H[m_cur] = m_H[m_cur - 1];
	m_W[m_cur] = m_W[m_cur - 1];
	m_Image[m_cur] = malloc2D(m_H[m_cur], m_W[m_cur]);

	// 알고리즘에 해당하는 마스크
	double mask[3][3] = {{-1 / 9.0, -1 / 9.0, -1 / 9.0},
						 {-1 / 9.0, 8 / 9.0, -1 / 9.0},
						 {-1 / 9.0, -1 / 9.0, -1 / 9.0}};

	double **tmpInput = malloc2Ddouble(m_H[m_cur - 1] + 2, m_W[m_cur - 1] + 2);
	double **tmpOutput = malloc2Ddouble(m_H[m_cur], m_W[m_cur]);

	if (m_Image[m_cur] == NULL || tmpInput == NULL || tmpOutput == NULL)
	{
		m_cur--;
		m_last = m_cur;
		free2Ddouble(tmpInput, m_H[m_cur - 1] + 2);
		free2Ddouble(tmpOutput, m_H[m_cur]);
		MessageBox(hwnd, "메모리 부족.", "작업 창", 0);
		drawImage();
		return;
	}

	double S = 0; // 마스크 9개 X 입력영상 9개의 합

	for (int i = 0; i < m_H[m_cur - 1]; i++)
		for (int k = 0; k < m_W[m_cur - 1]; k++)
			tmpInput[i + 1][k + 1] = m_Image[m_cur - 1][i][k];

	for (int i = 0; i < m_H[m_cur]; i++)
	{
		for (int k = 0; k < m_W[m_cur]; k++)
		{
			S = 0;

			for (int m = 0; m < 3; m++)
				for (int n = 0; n < 3; n++)
					S += tmpInput[i + m][k + n] * mask[m][n];

			tmpOutput[i][k] = S;
		}
	}

	// tmpOutput -> Output
	for (int i = 0; i < m_H[m_cur]; i++)
	{
		for (int k = 0; k < m_W[m_cur]; k++)
		{
			double v = tmpOutput[i][k];

			if (v > 255.0)
				v = 255.0;
			else if (v < 0)
				v = 0;

			m_Image[m_cur][i][k] = (UC)v;
		}
	}

	free2Ddouble(tmpInput, m_H[m_cur - 1] + 2);
	free2Ddouble(tmpOutput, m_H[m_cur]);

	drawImage();
}

/// <summary>
/// 픽셀화
/// </summary>
void pixelation()
{
	newCur();

	free2D(m_Image[m_cur], m_H[m_cur]);
	m_H[m_cur] = m_H[m_cur - 1];
	m_W[m_cur] = m_W[m_cur - 1];
	m_Image[m_cur] = malloc2D(m_H[m_cur], m_W[m_cur]);

	if (m_Image[m_cur] == NULL)
	{
		m_cur--;
		m_last = m_cur;
		MessageBox(hwnd, "메모리 부족.", "작업 창", 0);
		drawImage();
		return;
	}

	int block = 1;

	printf("모자이크 크기: ");
	rewind(stdin);
	scanf("%d", &block);

	if (block < 1)
		block = 1;

	for (int i = 0; i < m_H[m_cur - 1]; i += block) // 블록 단위로
	{
		for (int k = 0; k < m_W[m_cur - 1]; k += block)
		{
			int temp = 0;

			for (int m = 0; m < block; m++) // 블록 내 화소의 평균값을 구하고
			{
				for (int n = 0; n < block; n++)
				{
					int ni = i + m;
					int nk = k + n;

					if (ni >= m_H[m_cur - 1]) // 인덱스 오버플로우 방지
						ni = m_H[m_cur - 1] - 1;
					if (nk >= m_W[m_cur - 1])
						nk = m_W[m_cur - 1] - 1;

					temp += m_Image[m_cur - 1][ni][nk];
				}
			}

			temp /= block * block;

			for (int m = 0; m < block; m++) // 블록 내의 화소를 전부 평균값으로 채움
			{
				for (int n = 0; n < block; n++)
				{
					int ni = i + m;
					int nk = k + n;

					if (ni >= m_H[m_cur - 1])
						ni = m_H[m_cur - 1] - 1;
					if (nk >= m_W[m_cur - 1])
						nk = m_W[m_cur - 1] - 1;

					m_Image[m_cur][ni][nk] = temp;
				}
			}
		}
	}

	drawImage();
}