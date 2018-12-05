#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>

#define _USE_MATH_DEFINES
#include <math.h>
#define GRAVITY_ACL 9.8
#define radsin(theta) sin(M_PI * theta / 180)
#define radcos(theta) cos(M_PI * theta / 180)

#define XSize 94
#define YSize 60
int vlc, theta,  cm, *px, *py;
double xt, yt, time;
struct XY {
	double xc;
	double yc;
};
XY xycoord[XSize];


void movetoxy(int col, int row);
void clearScreen();
char anyKey();
void projectile(XY* xycoord);
int main(void)
{
	projectile(xycoord);

}

void movetoxy(int col, int row)

{

	COORD position = { col - 1,row - 1 };

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);

}
void clearScreen()
{
	system("cls");
}
void projectile(XY* xycoord)
{
	int x = 10, y = 5, i;
	movetoxy(x, y);
	printf("���� �� ����â�� ��üȭ������ ���ּ���. (�ƹ�Ű�� ��������..)");
	_getch();
	clearScreen();

	movetoxy(x, y);
	printf("�߻� �ӵ��� �Է��Ͻÿ�. (���� : m/s) : ");
	scanf("%d", &vlc);

	clearScreen();
	movetoxy(x, y);
	printf("�߻� ������ �Է��Ͻÿ�. (���� : ��) :");

	scanf("%d", &theta);
	while (theta>89)
	{
		clearScreen();
		movetoxy(x, y);
		printf("�߻� ������ �Է��Ͻÿ�. (���� : ��) :");
		scanf("%d", &theta);
		
	}
	clearScreen();

	movetoxy(x, y);
	xt = pow(vlc, 2)*(double)radsin(2 * theta) / GRAVITY_ACL; // ���� �̵��Ÿ�
	yt = pow(vlc, 2)*pow((double)radsin(theta), 2) / 2 / GRAVITY_ACL; // �ְ���
	time = vlc*(double)radsin(theta) / GRAVITY_ACL * 2; // �ɸ��� �ð�

	double amdx = XSize / xt; // ĭ1���� x����
	double amdy = YSize / yt; // ĭ1���� y����

	movetoxy(1, YSize);
	xt *= amdx; // ĭ��=XSize
	for (i = 0; i < (int)xt; i++) 	printf("��");


	for (i = 0; i < XSize+1; i++) {
		xycoord[i].xc = (int)(vlc*(double)radcos(theta) / XSize * i * time*amdx); // =i 
		// xycoord[i].xc = (int)(vlc*(double)radcos(theta) * i * time/xt); 
	}
	for (i = 0; i < XSize+1; i++) {
		xycoord[i].yc = (((vlc*(double)radsin(theta))*time/XSize*i - GRAVITY_ACL*pow(time/XSize*i, 2) / 2)); // vt(i/XSize)sin(theta)(1-i/XSize)

	}
	for(i=1;i<XSize+1;i++)
	{
		printf(" ");
		movetoxy(xycoord[i].xc*2, (int)YSize-xycoord[i].yc);
		if(YSize-xycoord[i].yc>1) 	printf("��");

		movetoxy(XSize, YSize - 5);
		printf("�ҿ� �ð�  = %.4f��\n", time/XSize*(i-1));

		movetoxy(XSize, YSize - 4);
		printf("�����̵��Ÿ� = %.4fm\n", xycoord[i].xc / amdx);

		movetoxy(XSize, YSize - 3);
		printf("���� �� = %.04fm\n",   pow(xycoord[i].yc,2) / yt );

		movetoxy(XSize, YSize - 2);
		printf("�ְ��� = %.4fm\n", yt);

		movetoxy(xycoord[i].xc * 2, YSize - xycoord[i].yc);
		Sleep(time/XSize*1000);
	}
	movetoxy(XSize, YSize - 1);
}


char anyKey()
{
	char pressed;
	pressed = _getch();
	return pressed;
}
