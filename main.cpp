/*
 * main.cpp
 *
 *  Created on: 14 окт. 2020 г.
 *      Author: Alexers1501
 *      https://github.com/Alexers1501/Picture-with-House.git
 */

#include <iostream>

#include <memory>
#include <random>

/*
 * std::shared_ptr - разделяемый указатель
 * std::unique_ptr - уникальный указатель
 * std::weak_ptr -"слабый" указатель
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_main.h>


#include <cmath>
constexpr double Pi = acos(-1.);

constexpr int WIDTH = 1280, HEIGHT = 720;


// данные замка
constexpr int rx = 200;
constexpr int ry = 200;
constexpr int downX = 110;
constexpr int downY = 130;
constexpr int upX = 100;
constexpr int upY = 340;
constexpr int centerX = 130;
constexpr int centerY = 420;

//данне забора
constexpr int fenceX = 50;
constexpr int fenceY = 200;
//данне для трав
constexpr int k = 7;
constexpr int sizeArr = 4;
int lenght[] = {4, 8, 20, 5};
int xy[] = {10, 400,
		50, 567,
		25, 712,
		200, 654,
		128, 390,
		189, 478,
		76, 523};



void DrawCircle (SDL_Renderer * ren, int cx, int cy, int r){
	//алгоритм Брезенхэма
	int x = 0;
	int y = r;
	int delta = 1-2*r;
	int error = 0;
	while (y >= 0){
		SDL_RenderDrawPoint(ren, cx + x, cy + y);
		SDL_RenderDrawPoint(ren, cx + x, cy - y);
		SDL_RenderDrawPoint(ren, cx - x, cy + y);
		SDL_RenderDrawPoint(ren, cx - x, cy - y);
		error = 2 * (delta + y) - 1;
		if ((delta < 0) && (error <= 0))
			delta += 2* ++x +1;
		else if ((delta > 0) && (error > 0))
			delta -= 2* --y + 1;
		else
			delta += 2 * (++x - --y);
	}
}

int main(int, char **){

	std::cout << "Начало работы программы" <<std::endl;

	SDL_Init(SDL_INIT_EVERYTHING);
auto win = std::shared_ptr<SDL_Window>(
	SDL_CreateWindow("Apps shell", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN), SDL_DestroyWindow);

	if (win == nullptr){
		std::cerr <<"Ошибка при сохдании окна: " <<
				SDL_GetError() << std::endl;
		return 1;
	}

	auto ren = std::shared_ptr <SDL_Renderer>(
			SDL_CreateRenderer(win.get(), -1,
					SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC), SDL_DestroyRenderer);
	if (ren == nullptr){
		std::cerr << "Ошибка при сохдании рендера: " <<
				SDL_GetError() << std::endl;
		return 1;
	}




	//Основной цикд программы
	SDL_Event event;// в эту переменнную будем помещвть информацию о каждом следующем событии
	bool finish = false;

	while (not finish){
		// цикл обработки событий
		while (SDL_PollEvent(&event)){//проверяет есть ли событие, и помещает по указателю событие и возвращает ненулевое значение
		if (event.type == SDL_QUIT)//если окно закрыли...
			finish = true;
		}

		SDL_SetRenderDrawColor(ren.get(), 83, 196, 252, 255);    //фон - небо
		//последний параметр - непрозрачность
		SDL_RenderClear(ren.get());//отрисовка изображения

		//фон травы

		SDL_Rect grass { 0, 330, WIDTH, HEIGHT-330};
		SDL_SetRenderDrawColor(ren.get(), 31, 240, 87, 255);
		SDL_RenderFillRect(ren.get(), &grass);



		//забор

		SDL_SetRenderDrawColor(ren.get(), 143, 120, 86, 255);
		SDL_RenderDrawLine (ren.get(), 0, HEIGHT/2-40, WIDTH, HEIGHT/2-40);
		SDL_RenderDrawLine (ren.get(), 0, HEIGHT/2+fenceY/2, WIDTH, HEIGHT/2+fenceY/2);
		for (int i = 0; i < WIDTH; i += fenceX+10){
			SDL_Rect fence { i, HEIGHT/2-70, fenceX, fenceY};
			SDL_SetRenderDrawColor(ren.get(), 230, 193, 138, 255);
			SDL_RenderFillRect(ren.get(), &fence);
		}

		//солнце
		constexpr int rad = 100;
		SDL_SetRenderDrawColor(ren.get(), 252, 239, 116, 255);
		for (int i = rad; i > 0; i--)
			DrawCircle (ren.get(), WIDTH - 150, 150, i);

		////////////////////////////////ОТРИСОВКА ЗАМКА//////////////////////
		constexpr int moveP = 50; //сдвиг замка


		//пристрой ввурху в центре
		SDL_Rect center { WIDTH/2-centerX/2, HEIGHT/2+moveP-centerY+ry, centerX, centerY};
		SDL_SetRenderDrawColor(ren.get(), 210, 170, 255, 255);
		SDL_RenderFillRect(ren.get(), &center);

		//крыша в центре свурху
		constexpr int hRoof3 = 80;
		SDL_SetRenderDrawColor(ren.get(),149, 123, 175, 255);
			for (int i = 0; i< hRoof3; i++){
				SDL_RenderDrawLine(ren.get(), WIDTH/2-i, HEIGHT/2+moveP-centerY+ry-hRoof3+i,
						WIDTH/2+i, HEIGHT/2+moveP-centerY+ry-hRoof3+i);
			}

		//пристрой ввурху слева
		SDL_Rect upLeft { WIDTH/2-rx/2-upX/2, HEIGHT/2+moveP-upY+ry, upX, upY};
		SDL_SetRenderDrawColor(ren.get(), 210, 170, 190, 255);
		SDL_RenderFillRect(ren.get(), &upLeft);
		//пристрой ввурху справа
		SDL_Rect upRight { WIDTH/2+rx/2-upX/2, HEIGHT/2+moveP-upY+ry, upX, upY};
		SDL_RenderFillRect(ren.get(), &upRight);

		//крыша сверху сдева
		constexpr int hRoof2 = 60;
		SDL_SetRenderDrawColor(ren.get(),149, 123, 175, 255);
				for (int i = 0; i< hRoof2; i++){
						SDL_RenderDrawLine(ren.get(), (WIDTH/2-rx/2)-i,
								HEIGHT/2+moveP-upY+ry-hRoof2+i,
								(WIDTH/2-rx/2)+i,
								HEIGHT/2+moveP-upY+ry-hRoof2+i);
				}

		//крыша сверху справа
			for (int i = 0; i< hRoof2; i++){
				SDL_RenderDrawLine(ren.get(), (WIDTH/2+rx/2)-i,
						HEIGHT/2+moveP-upY+ry-hRoof2+i,
						(WIDTH/2+rx/2)+i,
						HEIGHT/2+moveP-upY+ry-hRoof2+i);
			}

		//спереди
		SDL_Rect r { WIDTH/2-rx/2, HEIGHT/2+moveP, rx, ry};
		SDL_SetRenderDrawColor(ren.get(), 210, 200, 255, 255);
		SDL_RenderFillRect(ren.get(), &r);

		//ворота
		SDL_SetRenderDrawColor(ren.get(), 168, 129, 110, 255);
		constexpr int gateRad = 50;
		for (int i = gateRad; i>0; i--)
			DrawCircle(ren.get(), WIDTH/2, HEIGHT/2+moveP+ry/2, i);
		SDL_Rect gate { WIDTH/2 - gateRad, HEIGHT/2+moveP+ry/2, gateRad*2, ry/2};
		SDL_RenderFillRect(ren.get(), &gate);

		//пристрой внизу слева

		SDL_Rect downLeft { WIDTH/2-rx/2-downX, HEIGHT/2+moveP+(ry-downY), downX, downY};
		SDL_SetRenderDrawColor(ren.get(), 210, 170, 255, 255);
		SDL_RenderFillRect(ren.get(), &downLeft);
		//пристрой внизу справа
		SDL_Rect downRight { WIDTH/2+rx/2, HEIGHT/2+moveP+(ry-downY), downX, downY};
		SDL_RenderFillRect(ren.get(), &downRight);

		//крыша боьшая
		constexpr int bigRoof = 150;
		SDL_SetRenderDrawColor(ren.get(),149, 123, 175, 255);
				for (int i = 0; i< bigRoof; i++){
					SDL_RenderDrawLine(ren.get(), WIDTH/2-i, moveP+HEIGHT/2-bigRoof+i, WIDTH/2+i, moveP+HEIGHT/2-bigRoof+i);
				}
		//часы на крыше
		SDL_SetRenderDrawColor(ren.get(), 210, 200, 255, 255);
		constexpr int clockRad = 30;
		for (int i = clockRad; i>0; i--)
			DrawCircle(ren.get(), WIDTH/2, HEIGHT/2+moveP-bigRoof/2, i);
		SDL_SetRenderDrawColor(ren.get(), 0, 0, 0, 255);
		SDL_RenderDrawLine(ren.get(),WIDTH/2, HEIGHT/2+moveP-bigRoof/2-clockRad, WIDTH/2, HEIGHT/2+moveP-bigRoof/2);
		SDL_RenderDrawLine(ren.get(),WIDTH/2, HEIGHT/2+moveP-bigRoof/2, WIDTH/2+clockRad*0.66, HEIGHT/2+moveP-bigRoof/2);

				//крыша внизу сдева
		constexpr int hRoof1 = 70;
		SDL_SetRenderDrawColor(ren.get(),149, 123, 175, 255);
				for (int i = 0; i< hRoof1; i++){
						SDL_RenderDrawLine(ren.get(), (WIDTH/2-rx/2-downX)+(downX/2)-i,
								HEIGHT/2+moveP+(ry-downY)-hRoof1+i,
								(WIDTH/2-rx/2-downX)+(downX/2)+i,
								HEIGHT/2+moveP+(ry-downY)-hRoof1+i);
				}
				//крыша внизу сдева
		SDL_SetRenderDrawColor(ren.get(),149, 123, 175, 255);
			for (int i = 0; i< hRoof1; i++){
				SDL_RenderDrawLine(ren.get(), (WIDTH/2+rx/2)+(downX/2)-i,
								HEIGHT/2+moveP+(ry-downY)-hRoof1+i,
								(WIDTH/2+rx/2)+(downX/2)+i,
								HEIGHT/2+moveP+(ry-downY)-hRoof1+i);
			}

			//Трава
			SDL_SetRenderDrawColor(ren.get(), 64, 92, 52, 255);

			constexpr int space = 10;
			int x;

			for (int i = 0; i < k*2;i += 2){
				x = xy[i];
				for (int j = 0; j <= sizeArr; j++){
					SDL_RenderDrawLine(ren.get(), x, xy[i+1], x+space/2, xy[i+1]-lenght[j]);
					SDL_RenderDrawLine(ren.get(), x+space/2, xy[i+1]-lenght[j], x+space, xy[i+1]);
					x += space;

				}
			}


//		SDL_SetRenderDrawColor(ren.get(), 255, 255, 63, 255);
//
//		for (double angle = 0.; angle < 2.*Pi; angle += Pi/720.){
//			double x = WIDTH/2.+300. * cos(angle);
//			double y = HEIGHT/2. + 300. * sin(angle);
//			SDL_RenderDrawPoint(ren.get(), int (x), int(y));
//		}
//
//		SDL_RenderDrawLine(ren.get(), 0, 0, WIDTH-1, HEIGHT-1);
//
//
//		SDL_Rect r { 200, 200, 400, 150};
//		SDL_SetRenderDrawColor(ren.get(), 127, 0, 0, 255);
//		SDL_RenderFillRect(ren.get(), &r);
//
//		SDL_SetRenderDrawColor(ren.get(),95, 95, 255, 255);
//		for (int x = 0; x < 800; x++)
//			SDL_RenderDrawLine(ren.get(), 200+x, 250, 200, 1000-x);
//
//		//треугольик
//		SDL_SetRenderDrawColor(ren.get(),0, 255, 255, 255);
//		for (int i =0; i< 150; i++){
//			SDL_RenderDrawLine(ren.get(), 150+i, 500-i*2, 150+i, 500+i);
//		}



		SDL_RenderPresent(ren.get());// показ изображения

	}





	//SDL_Delay(3000); //дурной тон, задержка

	std::cout << "Конец работы программы" << std::endl;

	return 0;
}


