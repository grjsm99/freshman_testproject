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
	printf("시작 전 도스창을 전체화면으로 해주세요. (아무키나 누르세요..)");
	_getch();
	clearScreen();

	movetoxy(x, y);
	printf("발사 속도를 입력하시오. (단위 : m/s) : ");
	scanf("%d", &vlc);

	clearScreen();
	movetoxy(x, y);
	printf("발사 각도를 입력하시오. (단위 : Θ) :");

	scanf("%d", &theta);
	while (theta>89)
	{
		clearScreen();
		movetoxy(x, y);
		printf("발사 각도를 입력하시오. (단위 : Θ) :");
		scanf("%d", &theta);
		
	}
	clearScreen();

	movetoxy(x, y);
	xt = pow(vlc, 2)*(double)radsin(2 * theta) / GRAVITY_ACL; // 수평 이동거리
	yt = pow(vlc, 2)*pow((double)radsin(theta), 2) / 2 / GRAVITY_ACL; // 최고점
	time = vlc*(double)radsin(theta) / GRAVITY_ACL * 2; // 걸리는 시간

	double amdx = XSize / xt; // 칸1개당 x길이
	double amdy = YSize / yt; // 칸1개당 y길이

	movetoxy(1, YSize);
	xt *= amdx; // 칸수=XSize
	for (i = 0; i < (int)xt; i++) 	printf("■");


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
		if(YSize-xycoord[i].yc>1) 	printf("●");

		movetoxy(XSize, YSize - 5);
		printf("소요 시간  = %.4f초\n", time/XSize*(i-1));

		movetoxy(XSize, YSize - 4);
		printf("수평이동거리 = %.4fm\n", xycoord[i].xc / amdx);

		movetoxy(XSize, YSize - 3);
		printf("현재 고도 = %.04fm\n",   pow(xycoord[i].yc,2) / yt );

		movetoxy(XSize, YSize - 2);
		printf("최고점 = %.4fm\n", yt);

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
