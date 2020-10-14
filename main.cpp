/*
 * main.cpp
 *
 *  Created on: 14 ���. 2020 �.
 *      Author: Alexers1501
 *      https://github.com/Alexers1501/Picture-with-House.git
 */

#include <iostream>

#include <memory>

/*
 * std::shared_ptr - ����������� ���������
 * std::unique_ptr - ���������� ���������
 * std::weak_ptr -"������" ���������
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_main.h>


#include <cmath>
constexpr double Pi = acos(-1.);

constexpr int WIDTH = 1280, HEIGHT = 720;


void DrawCircle (SDL_Renderer * ren, int cx, int cy, int r){

}

int main(int, char **){

	std::cout << "������ ������ ���������" <<std::endl;

	SDL_Init(SDL_INIT_EVERYTHING);
auto win = std::shared_ptr<SDL_Window>(
	SDL_CreateWindow("Apps shell", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN), SDL_DestroyWindow);

	if (win == nullptr){
		std::cerr <<"������ ��� �������� ����: " <<
				SDL_GetError() << std::endl;
		return 1;
	}

	auto ren = std::shared_ptr <SDL_Renderer>(
			SDL_CreateRenderer(win.get(), -1,
					SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC), SDL_DestroyRenderer);
	if (ren == nullptr){
		std::cerr << "������ ��� �������� �������: " <<
				SDL_GetError() << std::endl;
		return 1;
	}




	//�������� ���� ���������
	SDL_Event event;// � ��� ����������� ����� �������� ���������� � ������ ��������� �������
	bool finish = false;

	while (not finish){
		// ���� ��������� �������
		while (SDL_PollEvent(&event)){//��������� ���� �� �������, � �������� �� ��������� ������� � ���������� ��������� ��������
		if (event.type == SDL_QUIT)//���� ���� �������...
			finish = true;
		}

		SDL_SetRenderDrawColor(ren.get(), 0, 70, 0, 255);
		//��������� �������� - ��������������
		SDL_RenderClear(ren.get());//��������� �����������
		/*
		 * ������� �����������
		 * 1 ����� (��������) - ���������� ������������ � ����
		 * 2 ����� (������) - �����, � ������� �������������� ����������� �����������, �� ������� �� ������������
		 */

		SDL_SetRenderDrawColor(ren.get(), 255, 255, 63, 255);

		// !!!���������� ���������� � ������� ��������� ����������
		// ��� ���������� ���������� mingw-w64-x86_64-SDL2-gfx
		for (double angle = 0.; angle < 2.*Pi; angle += Pi/720.){
			double x = WIDTH/2.+300. * cos(angle);
			double y = HEIGHT/2. + 300. * sin(angle);
			SDL_RenderDrawPoint(ren.get(), int (x), int(y));
		}

		SDL_RenderDrawLine(ren.get(), 0, 0, WIDTH-1, HEIGHT-1);


		SDL_Rect r { 200, 200, 400, 150};
		SDL_SetRenderDrawColor(ren.get(), 127, 0, 0, 255);
		SDL_RenderFillRect(ren.get(), &r);

		SDL_SetRenderDrawColor(ren.get(),95, 95, 255, 255);
		for (int x = 0; x < 800; x++)
			SDL_RenderDrawLine(ren.get(), 200+x, 250, 200, 1000-x);

		//����������
		SDL_SetRenderDrawColor(ren.get(),0, 255, 255, 255);
		for (int i =0; i< 150; i++){
			SDL_RenderDrawLine(ren.get(), 150+i, 500-i*2, 150+i, 500+i);
		}



		SDL_RenderPresent(ren.get());// ����� �����������

	}





	//SDL_Delay(3000); //������ ���, ��������

	std::cout << "����� ������ ���������" << std::endl;

	return 0;
}


