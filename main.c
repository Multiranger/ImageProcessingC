#define _CRT_SECURE_NO_WARNINGS // VS ���� ���� ����
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <conio.h>
#include <Windows.h>

#define UC unsigned char
#define MAX_WORK 10

// ���� ������
UC **m_Image[MAX_WORK];
int m_H[MAX_WORK], m_W[MAX_WORK], m_cur, m_last;
char m_dir[100];
HWND hwnd; // ���� ȭ��(������)
HDC hdc;   // ���� ȭ��(����)

// �Լ� �����(����)
void changeDir();
void openImage();
void saveImage();
void drawImage();
UC **malloc2D(int, int);
void free2D(UC **, int);
// �Լ� �����(���� ó��)
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
{ // ȭ�� �� ó��
	puts("\n ## ���� ó�� KSY 1.01 ##\n");
	puts("0.���ϰ��  1.����  2.����  3.����  4.Undo  5.Redo  6.����\n");
	puts("A.���ϱ�  B.���ϱ�  C.���  D.����\n");
	puts("E.��Ϲ���  F.�Ķ�(ĸ)  G.�Ķ�(��)\n");
	puts("H.�����Ͷ���¡  I.�κ� ����\n");
	puts("J.���(128)  K.���(���)\n");
	puts("L.������׷�(��Ȱ)  M.������׷�(����-��)\n");
	puts("N.���� �޴�\n");
}
void printMenu2()
{ // ������ ó��
	puts("\n ## ���� ó�� KSY 1.01 ##\n");
	puts("0.���ϰ��  1.����  2.����  3.����  4.Undo  5.Redo  6.����\n");
	puts("A.�̵�  B.���  C.Ȯ��  D.ȸ��\n");
	puts("E.ȸ��(90)  F.���Ϲ���  G.�¿����\n");
	puts("N.���� �޴�\n");
}
void printMenu3()
{ // ȭ�� ���� ó��
	puts("\n ## ���� ó�� KSY 1.01 ##\n");
	puts("0.���ϰ��  1.����  2.����  3.����  4.Undo  5.Redo  6.����\n");
	puts("A.������  B.��  C.����þ�\n");
	puts("D.�⺻ ������  E.HPF  F.LPF\n");
	puts("G.���� ������  H.�� ������\n");
	puts("I.LoG  J.DoG\n");
	puts("N.���� �޴�\n");
}
void printMenu4()
{ // ��Ÿ
	puts("\n ## ���� ó�� KSY 1.01 ##\n");
	puts("0.���ϰ��  1.����  2.����  3.����  4.Undo  5.Redo  6.����\n");
	puts("A.����  B.���� ����ũ  C.�ȼ�ȭ\n");
	puts("N.ó������\n");
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

// ���� �ڵ�
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

// �Լ� ���Ǻ�
// ���� �Լ� ���Ǻ�

/// <summary>
/// 2���� �޸� �Ҵ� (h x w)
/// </summary>
/// <param name="h">���� (������ �迭)</param>
/// <param name="w">�� (�迭)</param>
/// <returns></returns>
UC **malloc2D(int h, int w)
{
	UC **memory;

	memory = (UC **)malloc(h * sizeof(UC *)); // ������ �迭 �Ҵ�

	if (memory == NULL)
		return NULL;

	for (int i = 0; i < h; i++) // �� �����Ϳ� �迭 �Ҵ�
	{
		memory[i] = (UC *)malloc(w * sizeof(UC));

		if (memory[i] == NULL) // �Ҵ翡 ������ �迭�� ������
		{
			for (int k = 0; k < i; k++) // ���ݱ��� �Ҵ��� �޸𸮸� ��� ��ȯ�ϰ�
				free(memory[k]);
			free(memory);
			return NULL; // NULL ��ȯ
		}

		for (int k = 0; k < w; k++) // �ʱ�ȭ
			memory[i][k] = 0;
	}
	return memory; // ��� �Ҵ翡 ������ ���
}

/// <summary>
/// 2���� �޸� �Ҵ� ����
/// </summary>
/// <param name="memory">�����Ϸ��� �޸�</param>
/// <param name="h">�����Ϸ��� �޸��� ����</param>
void free2D(UC **memory, int h)
{
	if (memory == NULL) // �Ҵ�� ���� ������ �ƹ��͵� ����
	{
		return;
	}

	for (int i = 0; i < h; i++)
		free(memory[i]);
	free(memory);
}

/// <summary>
/// ���ο� �۾��� ���� Ŀ�� �̵�
/// </summary>
void newCur()
{
	if (m_cur < MAX_WORK - 1) // �۾������� �����ִٸ�
	{
		m_cur++;
		m_last = m_cur;
	}
	else // �۾������� ���� ���� ù ��° �۾��� ����� ������ �� ĭ�� �̵�
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
/// ��� �̸� ����
/// </summary>
void changeDir()
{
	char tmpDir[100] = "";
	printf("��θ�: ");
	rewind(stdin);
	scanf("%s", tmpDir);

	if (tmpDir[99] != 0)
	{
		MessageBox(hwnd, "���� ��ΰ� �ִ� ����(99��)�� �ʰ��߽��ϴ�.", "��� â", 0);
		drawImage();
		return;
	}

	if (!strcmp(tmpDir, "default")) // �⺻���� �������� ��ġ
		strcpy(m_dir, "");
	else
		strcpy(m_dir, tmpDir);

	drawImage();
}

/// <summary>
/// raw �̹����� ��� m_Images[0]�� ����
/// </summary>
void openImage()
{
	char fullName[160] = "";
	char tmpName[50] = "";
	printf("���ϸ�: ");
	rewind(stdin);
	scanf("%s", tmpName);

	if (tmpName[49] != 0)
	{
		MessageBox(hwnd, "���� �̸��� �ִ� ����(49��)�� �ʰ��߽��ϴ�.", "���� â", 0);
		return;
	}

	strcpy(fullName, m_dir);
	strcat(fullName, tmpName);
	strcat(fullName, ".raw");

	FILE *rfp;
	rfp = fopen(fullName, "rb");
	if (rfp == NULL)
	{
		MessageBox(hwnd, "���� �б� ����.", "���� â", 0);
		return;
	}

	// ���� ũ�� �˾Ƴ���
	fseek(rfp, 0L, SEEK_END);
	unsigned long fsize = ftell(rfp);
	fseek(rfp, 0L, SEEK_SET);

	// �޸� ���� ����
	for (int i = 0; i < MAX_WORK; i++)
		free2D(m_Image[i], m_H[i]);
	m_cur = m_last = 0;

	// (�߿�!) ������ ���̿� �� ���
	m_H[0] = m_W[0] = (int)sqrt(fsize);

	// �޸� �Ҵ�.	uc image[height][width];
	m_Image[0] = malloc2D(m_H[0], m_W[0]);
	if (m_Image[0] == NULL)
	{
		MessageBox(hwnd, "�޸� ����.", "���� â", 0);
		fclose(rfp);
		return;
	}

	// ���� --> �޸𸮷� �ε�
	for (int i = 0; i < m_H[0]; i++)
		fread(m_Image[0][i], sizeof(UC), m_W[0], rfp);

	fclose(rfp);
}

/// <summary>
/// m_Images[m_cur] ���
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
/// m_Images[m_cur]�� ����ڰ� �Է��� �̸�.raw �� ����
/// </summary>
void saveImage()
{
	// ������ ���ϸ� �Է� �ޱ�.
	char fullName[160] = "";
	char tmpName[50] = "";
	printf("���� ���ϸ�: ");
	rewind(stdin);
	scanf("%s", tmpName);

	if (tmpName[49] != 0)
	{
		MessageBox(hwnd, "���� �̸��� �ִ� ����(49��)�� �ʰ��߽��ϴ�.", "���� â", 0);
		drawImage();
		return;
	}

	if (!strcmp(tmpName, "cancel"))
	{
		MessageBox(hwnd, "���� ���.", "���� â", 0);
		drawImage();
		return;
	}

	strcpy(fullName, m_dir);
	strcat(fullName, tmpName);
	strcat(fullName, ".raw");

	FILE *wfp = fopen(fullName, "wb");
	if (wfp == NULL)
	{
		MessageBox(hwnd, "���� ����", "���� â", 0);
		drawImage();
		return;
	}

	for (int i = 0; i < m_H[m_cur]; i++)
		fwrite(m_Image[m_cur][i], sizeof(UC), m_W[m_cur], wfp);

	fclose(wfp);
	MessageBox(hwnd, "���� OK", "���� â", 0);

	drawImage();
}

// ���� ó�� �Լ� ���Ǻ�

/// <summary>
/// ���� ���� �˰���
/// </summary>
void equalImage()
{
	newCur(); // �� �۾����� �̵�

	free2D(m_Image[m_cur], m_H[m_cur]); // �޸� ���� ����
	m_H[m_cur] = m_H[0];
	m_W[m_cur] = m_W[0];
	m_Image[m_cur] = malloc2D(m_H[m_cur], m_W[m_cur]);

	if (m_Image[m_cur] == NULL)
	{
		m_cur--;
		m_last = m_cur;
		MessageBox(hwnd, "�޸� ����.", "�۾� â", 0);
		drawImage();
		return;
	}

	for (int i = 0; i < m_H[m_cur]; i++)
		for (int k = 0; k < m_W[m_cur]; k++)
			m_Image[m_cur][i][k] = m_Image[0][i][k]; // �״�� ����

	drawImage();
}

/// <summary>
/// ���� ���� �˰���
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
		MessageBox(hwnd, "�޸� ����.", "�۾� â", 0);
		drawImage();
		return;
	}

	for (int i = 0; i < m_H[m_cur]; i++)
		for (int k = 0; k < m_W[m_cur]; k++)
			m_Image[m_cur][i][k] = 255 - m_Image[m_cur - 1][i][k]; // ����, �����÷ο� ����

	drawImage();
}

/// <summary>
/// ���� ���ϱ� �˰���
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
		MessageBox(hwnd, "�޸� ����.", "�۾� â", 0);
		drawImage();
		return;
	}

	int value = 0;

	printf("���� ��: ");
	rewind(stdin);
	scanf("%d", &value);

	for (int i = 0; i < m_H[m_cur]; i++)
	{
		for (int k = 0; k < m_W[m_cur]; k++)
		{
			int pixel = m_Image[m_cur - 1][i][k] + value;

			if (pixel > 255) // �����÷ο� ����
				pixel = 255;
			else if (pixel < 0)
				pixel = 0;

			m_Image[m_cur][i][k] = pixel;
		}
	}

	drawImage();
}

/// <summary>
/// ���� ���ϱ� �˰���
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
		MessageBox(hwnd, "�޸� ����.", "�۾� â", 0);
		drawImage();
		return;
	}

	double value = 1.0;

	printf("���� ��: ");
	rewind(stdin);
	scanf("%lf", &value);

	if (value < 0) // ������ ���ϸ� ������
		value = -value;

	for (int i = 0; i < m_H[m_cur]; i++)
	{
		for (int k = 0; k < m_W[m_cur]; k++)
		{
			int pixel = (int)(m_Image[m_cur - 1][i][k] * value);

			if (pixel > 255) // ������ �������� ��� ����
				pixel = 255;

			m_Image[m_cur][i][k] = pixel;
		}
	}

	drawImage();
}

/// <summary>
/// ���� ��� �˰���(128)
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
		MessageBox(hwnd, "�޸� ����.", "�۾� â", 0);
		drawImage();
		return;
	}

	for (int i = 0; i < m_H[m_cur]; i++)
	{
		for (int k = 0; k < m_W[m_cur]; k++)
		{
			if (m_Image[m_cur - 1][i][k] < 128) // 128�� ��������
				m_Image[m_cur][i][k] = 0;
			else
				m_Image[m_cur][i][k] = 255;
		}
	}

	drawImage();
}

/// <summary>
/// ���� ��� ���� ��� �˰���
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
		MessageBox(hwnd, "�޸� ����.", "�۾� â", 0);
		drawImage();
		return;
	}

	unsigned long total = 0;
	double avg;

	for (int i = 0; i < m_H[m_cur]; i++) // ��ü ���� ���ؼ�
		for (int k = 0; k < m_W[m_cur]; k++)
			total += m_Image[m_cur - 1][i][k];

	if (m_H[m_cur] != 0 && m_W[m_cur] != 0)
		avg = total / (double)(m_H[m_cur] * m_W[m_cur]); // ���� ���� ������ ��� ����

	for (int i = 0; i < m_H[m_cur]; i++)
	{
		for (int k = 0; k < m_W[m_cur]; k++)
		{
			if (m_Image[m_cur - 1][i][k] < avg) // ����� �������� ���
				m_Image[m_cur][i][k] = 0;
			else
				m_Image[m_cur][i][k] = 255;
		}
	}

	drawImage();
}

/// <summary>
/// ���� ���� �˰���
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
		MessageBox(hwnd, "�޸� ����.", "�۾� â", 0);
		drawImage();
		return;
	}

	double gamma = 0.0;

	printf("���� �Է�: ");
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
/// ���� cap �Ķ󺼶� �˰���
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
		MessageBox(hwnd, "�޸� ����.", "�۾� â", 0);
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
/// ���� cup �Ķ󺼶� �˰���
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
		MessageBox(hwnd, "�޸� ����.", "�۾� â", 0);
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
/// ���� 90�� ȸ��
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
		MessageBox(hwnd, "�޸� ����.", "�۾� â", 0);
		drawImage();
		return;
	}

	for (int i = 0; i < m_H[m_cur]; i++)
		for (int k = 0; k < m_W[m_cur]; k++)
			m_Image[m_cur][i][k] = m_Image[m_cur - 1][m_H[m_cur - 1] - 1 - k][i]; // 90�� ȸ��

	drawImage();
}

/// <summary>
/// �Է� ���� ��ŭ ���(��հ� ������ø�)
/// </summary>
void zoomOutImage()
{
	newCur();

	int value = 1;

	printf("��� ����: ");
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
		MessageBox(hwnd, "�޸� ����.", "�۾� â", 0);
		drawImage();
		return;
	}

	for (int i = 0; i < m_H[m_cur]; i++)
	{
		for (int k = 0; k < m_W[m_cur]; k++)
		{
			int avg = 0;

			for (int m = 0; m < value; m++) // ��հ� ������ø�
				for (int n = 0; n < value; n++)
					avg += m_Image[m_cur - 1][i * value + m][k * value + n];

			avg /= value * value;

			m_Image[m_cur][i][k] = (UC)avg;
		}
	}

	drawImage();
}

/// <summary>
/// �Է� ���� ��ŭ Ȯ��(�缱�� ����)
/// </summary>
void zoomInImage()
{
	newCur();

	int value = 1;

	printf("Ȯ�� ����: ");
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
		MessageBox(hwnd, "�޸� ����.", "�۾� â", 0);
		drawImage();
		return;
	}

	for (int i = 0; i < m_H[m_cur]; i++)
	{
		for (int k = 0; k < m_W[m_cur]; k++)
		{
			double rx = (double)k / value; // ���� ��ǥ
			double ry = (double)i / value;
			int x1 = (int)rx; // ���� ��ǥ ��ó�� ��
			int y1 = (int)ry;
			int x2 = x1 + 1;
			int y2 = y1 + 1;

			if (x2 == m_W[m_cur - 1])
				x2 = m_W[m_cur - 1] - 1;
			if (y2 == m_H[m_cur - 1])
				y2 = m_H[m_cur - 1] - 1;

			double p = rx - x1; // ������ �Ÿ�
			double q = ry - y1;

			double value = (1. - p) * (1. - q) * m_Image[m_cur - 1][y1][x1] + p * (1. - q) * m_Image[m_cur - 1][y1][x2] + (1. - p) * q * m_Image[m_cur - 1][y2][x1] + p * q * m_Image[m_cur - 1][y2][x2];

			m_Image[m_cur][i][k] = (UC)value;
		}
	}

	drawImage();
}

/// <summary>
/// �Է� x, y ��ŭ ��ġ �̵�
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
		MessageBox(hwnd, "�޸� ����.", "�۾� â", 0);
		drawImage();
		return;
	}

	int x = 0, y = 0;

	printf("x ��: ");
	rewind(stdin);
	scanf("%d", &x);
	printf("y ��: ");
	rewind(stdin);
	scanf("%d", &y);

	for (int i = 0; i < m_H[m_cur]; i++)
		for (int k = 0; k < m_W[m_cur]; k++)
			if (i - y >= 0 && i - y < m_H[m_cur - 1] && k - x >= 0 && k - x < m_W[m_cur - 1])
				m_Image[m_cur][i][k] = m_Image[m_cur - 1][i - y][k - x];

	drawImage();
}

/// <summary>
/// �Է� ���� ��ŭ ȸ��
/// </summary>
void rotateImage()
{
	newCur();

	int degree = 0;
	double radian = 0., radian90 = 0.;
	UC **temp;

	printf("���� �Է�: ");
	rewind(stdin);
	scanf("%d", &degree);

	radian = degree * 3.1415926535 / 180;
	radian90 = (90 - degree) * 3.1415926535 / 180;

	free2D(m_Image[m_cur], m_H[m_cur]);
	// Ȯ���� ũ�� ���
	m_H[m_cur] = (int)(m_H[m_cur - 1] * fabs(cos(radian90)) + m_W[m_cur - 1] * fabs(cos(radian)));
	m_W[m_cur] = (int)(m_H[m_cur - 1] * fabs(cos(radian)) + m_W[m_cur - 1] * fabs(cos(radian90)));
	m_Image[m_cur] = malloc2D(m_H[m_cur], m_W[m_cur]);
	temp = malloc2D(m_H[m_cur], m_W[m_cur]);

	if (m_Image[m_cur] == NULL || temp == NULL)
	{
		m_cur--;
		m_last = m_cur;
		free2D(temp, m_H[m_cur]);
		MessageBox(hwnd, "�޸� ����.", "�۾� â", 0);
		drawImage();
		return;
	}

	int x0, y0, dx, dy;

	dx = (m_W[m_cur] - m_W[m_cur - 1]) / 2; // �߽� �̵�
	dy = (m_H[m_cur] - m_H[m_cur - 1]) / 2;

	for (int i = 0; i < m_H[m_cur - 1]; i++) // �̵��� ��ġ�� ����
		for (int k = 0; k < m_W[m_cur - 1]; k++)
			temp[i + dy][k + dx] = m_Image[m_cur - 1][i][k];

	x0 = m_W[m_cur] / 2; // ���ο� �߽�
	y0 = m_H[m_cur] / 2;

	for (int i = 0; i < m_H[m_cur]; i++)
	{
		for (int k = 0; k < m_W[m_cur]; k++) // ���ο� �߽��� �������� ȸ��
		{
			double nk = (k - x0) * cos(radian) + (i - y0) * sin(radian) + x0;
			double ni = (x0 - k) * sin(radian) + (i - y0) * cos(radian) + y0;
			if (nk >= 0 && ni >= 0 && nk < m_W[m_cur] && ni < m_H[m_cur])
			{
				int x1 = (int)nk; // �缱�� ������ �� ������
				int y1 = (int)ni;
				int x2 = x1 + 1;
				int y2 = y1 + 1;

				if (x2 == m_W[m_cur])
					x2 = m_W[m_cur] - 1;
				if (y2 == m_H[m_cur])
					y2 = m_H[m_cur] - 1;

				double p = nk - x1; // ���������� ���� ������ �Ÿ�
				double q = ni - y1;
				// ���� �� ���
				double value = (1. - p) * (1. - q) * temp[y1][x1] + p * (1. - q) * temp[y1][x2] + (1. - p) * q * temp[y2][x1] + p * q * temp[y2][x2];

				m_Image[m_cur][i][k] = (UC)value;
			}
		}
	}

	free2D(temp, m_H[m_cur]);

	drawImage();
}

/// <summary>
/// ���� �̷���
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
		MessageBox(hwnd, "�޸� ����.", "�۾� â", 0);
		drawImage();
		return;
	}

	for (int i = 0; i < m_H[m_cur]; i++)
		for (int k = 0; k < m_W[m_cur]; k++)
			m_Image[m_cur][i][k] = m_Image[m_cur - 1][m_H[m_cur - 1] - 1 - i][k];

	drawImage();
}

/// <summary>
/// �¿� �̷���
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
		MessageBox(hwnd, "�޸� ����.", "�۾� â", 0);
		drawImage();
		return;
	}

	for (int i = 0; i < m_H[m_cur]; i++)
		for (int k = 0; k < m_W[m_cur]; k++)
			m_Image[m_cur][i][k] = m_Image[m_cur - 1][i][m_W[m_cur - 1] - 1 - k];

	drawImage();
}

/// <summary>
/// ������ 2���� �޸� �Ҵ� (h x w)
/// </summary>
/// <param name="h">���� (������ �迭)</param>
/// <param name="w">�� (�迭)</param>
/// <returns></returns>
double **malloc2Ddouble(int h, int w)
{
	double **memory = (double **)malloc(h * sizeof(double *)); // ������ �迭 �Ҵ�

	if (memory == NULL)
		return NULL;

	for (int i = 0; i < h; i++)
	{ // �� �����Ϳ� �迭 �Ҵ�
		memory[i] = (double *)malloc(w * sizeof(double));

		if (memory[i] == NULL)
		{								// �Ҵ翡 ������ �迭�� ������
			for (int k = 0; k < i; k++) // ���ݱ��� �Ҵ��� �޸𸮸� ��� ��ȯ�ϰ�
				free(memory[k]);

			free(memory);
			return NULL; // NULL ��ȯ
		}

		for (int k = 0; k < w; k++) // �ʱ�ȭ
			memory[i][k] = 128;
	}
	return memory; // ��� �Ҵ翡 ������ ���
}

/// <summary>
/// ������ 2���� �޸� �Ҵ� ����
/// </summary>
/// <param name="memory">�����Ϸ��� �޸�</param>
/// <param name="h">�����Ϸ��� �޸��� ����</param>
void free2Ddouble(double **memory, int h)
{
	if (memory == NULL) // �Ҵ�� ���� ������ �ƹ��͵� ����
		return;

	for (int i = 0; i < h; i++)
		free(memory[i]);
	free(memory);
}

/// <summary>
/// ������ �˰���
/// </summary>
void emboss()
{
	newCur();

	free2D(m_Image[m_cur], m_H[m_cur]);
	m_H[m_cur] = m_W[m_cur - 1];
	m_W[m_cur] = m_H[m_cur - 1];
	m_Image[m_cur] = malloc2D(m_H[m_cur], m_W[m_cur]);

	// �˰��� �ش��ϴ� ����ũ
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
		MessageBox(hwnd, "�޸� ����.", "�۾� â", 0);
		drawImage();
		return;
	}

	double S = 0; // ����ũ 9�� X �Է¿��� 9���� ��

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

	// ����ũ�� ���� 0�̸� 127 ���ϱ�
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
/// �� �˰���
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

	printf("�� ����(1 ~ 20): ");
	rewind(stdin);
	scanf("%d", &value);

	if (value < 1 || value > 20)
		value = 1;

	value = value * 2 + 1; // �Է°����� ����ũ ũ���
	append = value - 1;	   // ����ũ�� ��ġ�� ��ŭ �÷���� ��
	offset = value / 2;	   // ��ǲ�� Ȯ���� �迭�� �׸��� ���� ������

	// �޸� �Ҵ�
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
		MessageBox(hwnd, "�޸� ����.", "�۾� â", 0);
		drawImage();
		return;
	}

	double S = 0; // ����ũ 9�� X �Է¿��� 9���� ��

	// ����ũ ����
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

	// ����ũ�� ���� 0�̸� 127 ���ϱ�
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
/// ����þ� �˰���
/// </summary>
void gauss()
{
	newCur();

	free2D(m_Image[m_cur], m_H[m_cur]);
	m_H[m_cur] = m_H[m_cur - 1];
	m_W[m_cur] = m_W[m_cur - 1];
	m_Image[m_cur] = malloc2D(m_H[m_cur], m_W[m_cur]);

	// �˰��� �ش��ϴ� ����ũ
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
		MessageBox(hwnd, "�޸� ����.", "�۾� â", 0);
		drawImage();
		return;
	}

	double S = 0; // ����ũ 9�� X �Է¿��� 9���� ��

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

	// ����ũ�� ���� 0�̸� 127 ���ϱ�
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
/// ������ �˰���
/// </summary>
void sharpen()
{
	newCur();

	free2D(m_Image[m_cur], m_H[m_cur]);
	m_H[m_cur] = m_H[m_cur - 1];
	m_W[m_cur] = m_W[m_cur - 1];
	m_Image[m_cur] = malloc2D(m_H[m_cur], m_W[m_cur]);

	// �˰��� �ش��ϴ� ����ũ
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
		MessageBox(hwnd, "�޸� ����.", "�۾� â", 0);
		drawImage();
		return;
	}

	double S = 0; // ����ũ 9�� X �Է¿��� 9���� ��

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

	// ����ũ�� ���� 0�̸� 127 ���ϱ�
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
/// ������ ���� ������ �˰���
/// </summary>
void lpfSharpen()
{
	newCur();

	free2D(m_Image[m_cur], m_H[m_cur]);
	m_H[m_cur] = m_H[m_cur - 1];
	m_W[m_cur] = m_W[m_cur - 1];
	m_Image[m_cur] = malloc2D(m_H[m_cur], m_W[m_cur]);

	// �˰��� �ش��ϴ� ����ũ
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
		MessageBox(hwnd, "�޸� ����.", "�۾� â", 0);
		drawImage();
		return;
	}

	double a = 1.0; // ����
	double S = 0;	// ����ũ 9�� X �Է¿��� 9���� ��

	for (int i = 0; i < m_H[m_cur - 1]; i++)
		for (int k = 0; k < m_W[m_cur - 1]; k++)
			tmpInput[i + 1][k + 1] = m_Image[m_cur - 1][i][k];

	for (int i = 0; i < m_H[m_cur]; i++) // ������ ���� ����
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

	printf("���� ��(1.0 ~ 3.0): ");
	rewind(stdin);
	scanf("%lf", &a);

	if (a < 1.0 || a > 3.0)
		a = 2.0;

	for (int i = 0; i < m_H[m_cur - 1]; i++) // ������ ����
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
/// ���� ������ �˰���
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
		MessageBox(hwnd, "�޸� ����.", "�۾� â", 0);
		drawImage();
		return;
	}

	for (int i = 0; i < m_H[m_cur - 1]; i++)
		for (int k = 0; k < m_W[m_cur - 1]; k++)
			tmpInput[i + 1][k + 1] = m_Image[m_cur - 1][i][k];

	for (int i = 0; i < m_H[m_cur]; i++) // ��� ȭ�ҿ� ����
	{
		for (int k = 0; k < m_W[m_cur]; k++)
		{
			double S = 0.; // |center - m|
			double max = 0.;

			for (int m = 0; m < 3; m++) // 3 X 3 ������ ��� ȭ���� ���� �ֺ� ȭ���� ���� ����
			{
				for (int n = 0; n < 3; n++)
				{
					if (m != 1 || n != 1) // ����� ������� ����
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
/// �� ������ �˰���
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
		MessageBox(hwnd, "�޸� ����.", "�۾� â", 0);
		drawImage();
		return;
	}

	for (int i = 0; i < m_H[m_cur - 1]; i++)
		for (int k = 0; k < m_W[m_cur - 1]; k++)
			tmpInput[i + 1][k + 1] = m_Image[m_cur - 1][i][k];

	for (int i = 0; i < m_H[m_cur]; i++) // ��� ȭ�ҿ� ����
	{
		for (int k = 0; k < m_W[m_cur]; k++)
		{
			double S[4] = {0.}; // |�밢�� ������ ��|
			double max = 0.;

			for (int m = 0; m < 3; m++) // 3 X 3 ������ �밢�� ���е��� ���� ����
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
/// 2�� ���ö�þ� �˰���
/// </summary>
void LoG()
{
	newCur();

	free2D(m_Image[m_cur], m_H[m_cur]);
	m_H[m_cur] = m_H[m_cur - 1];
	m_W[m_cur] = m_W[m_cur - 1];
	m_Image[m_cur] = malloc2D(m_H[m_cur], m_W[m_cur]);

	// �˰��� �ش��ϴ� ����ũ
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
		MessageBox(hwnd, "�޸� ����.", "�۾� â", 0);
		drawImage();
		return;
	}

	double S = 0; // ����ũ 25�� X �Է¿��� 25���� ��

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

	// ����ũ�� ���� 0�̸� 127 ���ϱ�
	// ��輱 ���⿡���� ���ϱ� ���� �ʴ� ���� ���⿡ �� ����.
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
/// DoG �˰���
/// </summary>
void DoG()
{
	newCur();

	free2D(m_Image[m_cur], m_H[m_cur]);
	m_H[m_cur] = m_H[m_cur - 1];
	m_W[m_cur] = m_W[m_cur - 1];
	m_Image[m_cur] = malloc2D(m_H[m_cur], m_W[m_cur]);

	// �˰��� �ش��ϴ� ����ũ
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
		MessageBox(hwnd, "�޸� ����.", "�۾� â", 0);
		drawImage();
		return;
	}

	double S = 0; // ����ũ 81�� X �Է¿��� 81���� ��

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
/// ��� ���� �˰���
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
		MessageBox(hwnd, "�޸� ����.", "�۾� â", 0);
		drawImage();
		return;
	}

	double val = 1.0;

	printf("��� ��(0.0 ~ 2.0): ");
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
/// ������׷� ��Ȱ
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
		MessageBox(hwnd, "�޸� ����.", "�۾� â", 0);
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
/// ������׷� ��Ʈ��Ī ����-��
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
		MessageBox(hwnd, "�޸� ����.", "�۾� â", 0);
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
/// ����ũ�� �̹��� �ε�
/// </summary>
void openMaskImage(UC **mask)
{
	char fullName[160] = "";
	char tmpName[50] = "";
	printf("����ũ ���ϸ�: ");
	rewind(stdin);
	scanf("%s", tmpName);

	if (tmpName[49] != 0)
	{
		printf("���� �̸��� �ִ� ����(49��)�� �ʰ��߽��ϴ�.\n");
		return;
	}

	strcpy(fullName, m_dir);
	strcat(fullName, tmpName);
	strcat(fullName, ".raw");

	FILE *rfp;
	rfp = fopen(fullName, "rb");
	if (rfp == NULL)
	{
		printf("���� �б� ����.\n");
		return;
	}
	// ���� ũ�� �˾Ƴ���
	fseek(rfp, 0L, SEEK_END);
	unsigned long fsize = ftell(rfp);
	fseek(rfp, 0L, SEEK_SET);
	// ����ũ ũ�� �˻�
	if (fsize != m_H[m_cur] * m_W[m_cur])
	{
		fclose(rfp);
		printf("����ũ�� ũ�Ⱑ ������ �ٸ��ϴ�.\n");
		return;
	}
	// ���� --> �޸𸮷� �ε�
	for (int i = 0; i < m_H[m_cur]; i++)
		fread(mask[i], sizeof(UC), m_W[m_cur], rfp);

	fclose(rfp);
}

/// <summary>
/// ���� �˰���
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
		MessageBox(hwnd, "�޸� ����.", "�۾� â", 0);
		drawImage();
		return;
	}

	double val = 1.0;

	openMaskImage(tmp);

	printf("���� ��(0.0 ~ 1.0): ");
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
/// ���� ����
/// </summary>
/// <param name="Result">���� �����ؼ� ������ �迭</param>
/// <param name="diameter">���� ���� �ݰ�</param>
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
/// ���� �����Ͽ� and ����
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
		MessageBox(hwnd, "�޸� ����.", "�۾� â", 0);
		drawImage();
		return;
	}

	int val = 1;

	printf("���� ������: ");
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
/// ���� �����Ͷ���¡ (����8)
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
		MessageBox(hwnd, "�޸� ����.", "�۾� â", 0);
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
/// �κ� ����
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
		MessageBox(hwnd, "�޸� ����.", "�۾� â", 0);
		drawImage();
		return;
	}

	int h = 255, l = 0;

	printf("���� ���� ���: ");
	rewind(stdin);
	scanf("%d", &l);
	printf("������ ����: ");
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
/// hpf ������ �˰���
/// </summary>
void hpfSharpen()
{
	newCur();

	free2D(m_Image[m_cur], m_H[m_cur]);
	m_H[m_cur] = m_H[m_cur - 1];
	m_W[m_cur] = m_W[m_cur - 1];
	m_Image[m_cur] = malloc2D(m_H[m_cur], m_W[m_cur]);

	// �˰��� �ش��ϴ� ����ũ
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
		MessageBox(hwnd, "�޸� ����.", "�۾� â", 0);
		drawImage();
		return;
	}

	double S = 0; // ����ũ 9�� X �Է¿��� 9���� ��

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
/// �ȼ�ȭ
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
		MessageBox(hwnd, "�޸� ����.", "�۾� â", 0);
		drawImage();
		return;
	}

	int block = 1;

	printf("������ũ ũ��: ");
	rewind(stdin);
	scanf("%d", &block);

	if (block < 1)
		block = 1;

	for (int i = 0; i < m_H[m_cur - 1]; i += block) // ��� ������
	{
		for (int k = 0; k < m_W[m_cur - 1]; k += block)
		{
			int temp = 0;

			for (int m = 0; m < block; m++) // ��� �� ȭ���� ��հ��� ���ϰ�
			{
				for (int n = 0; n < block; n++)
				{
					int ni = i + m;
					int nk = k + n;

					if (ni >= m_H[m_cur - 1]) // �ε��� �����÷ο� ����
						ni = m_H[m_cur - 1] - 1;
					if (nk >= m_W[m_cur - 1])
						nk = m_W[m_cur - 1] - 1;

					temp += m_Image[m_cur - 1][ni][nk];
				}
			}

			temp /= block * block;

			for (int m = 0; m < block; m++) // ��� ���� ȭ�Ҹ� ���� ��հ����� ä��
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