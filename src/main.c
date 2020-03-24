#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "serial.h"
#include "vt100.h"
#include <stdint.h>
#define HITBOX (8)
#define HITBOX2 (6)
#define HITBOX3 (4)
#define TIMER (1)
#define LIMITE_MAX (71)
#define LIMITE_MIN (3)



int points = 0;
int compteur_enn = 0;
uint8_t m = 40, y;

typedef struct {
	uint8_t x_enn;
	uint8_t y_enn;
	uint8_t hit_enn;
	uint8_t type;
} donnees_ennemis;

donnees_ennemis *ptr_enn;
donnees_ennemis ennemis[5 + 6 + 9] = { { 5, 3, 0, 1 }, { 20, 3, 0, 1 }, { 35, 3,
		0, 1 }, { 50, 3, 0, 1 }, { 65, 3, 0, 1 }, { 10, 6, 0, 2 },
		{ 22, 6, 0, 2 }, { 34, 6, 0, 2 }, { 46, 6, 0, 2 }, { 58, 6, 0, 2 }, {
				70, 6, 0, 2 }, { 5, 9, 0, 3 }, { 13, 9, 0, 3 }, { 21, 9, 0, 3 },
		{ 29, 9, 0, 3 }, { 37, 9, 0, 3 }, { 45, 9, 0, 3 }, { 53, 9, 0, 3 }, {
				61, 9, 0, 3 }, { 69, 9, 0, 3 }, };

int x_tir = 0;

//int hit_enn6 = 0;
//int hit_enn7 = 0;
//int hit_enn8 = 0;
//int hit_enn9 = 0;
//int hit_enn10 = 0;
//int hit_enn11 = 0;
//int hit_enn12 = 0;
//int hit_enn13 = 0;
//int hit_enn14 = 0;
//int hit_enn15 = 0;
//int hit_enn16 = 0;
//int hit_enn17 = 0;
//int hit_enn18 = 0;
//int hit_enn19 = 0;
//int hit_enn20 = 0;

void timer(unsigned long int t) {

	int i = 0;
	unsigned long int max = t * 100000;
	do {
		i++;
	} while (i <= max);

}

void Bordures() {
	serial_init(115200);
	vt100_clear_screen();

	uint8_t x = 1;
	uint8_t y = 1;

	for (x = 1; x < 81; x++) {
		vt100_move(x, 1);
		serial_putchar(42);
		vt100_move(x, 24);
		serial_putchar(42);
	}

	for (y = 1; y < 25; y++) {
		vt100_move(1, y);
		serial_putchar(42);
		vt100_move(80, y);
		serial_putchar(42);

	}
}
int xxx = 10;
void Acceuil() {
	//vt100_clear_screen();
	vt100_move(27, 5);
	serial_puts("Bienvenue dans Space Invaders \n");
	vt100_move(30, 3);
	serial_puts("Bonjour jeune padawan \n");
	vt100_move(25, 7);
	serial_puts("Appuyer sur 'ESPACE' pour commencer \n");
	vt100_move(53, 23);
	serial_puts("Develloped by Ramounchito \n");
	vt100_move(xxx, 13); //11x8
	serial_puts("  #     #  ");
	vt100_move(xxx, 14);
	serial_puts("   #   #   ");
	vt100_move(xxx, 15);
	serial_puts("  #######  ");
	vt100_move(xxx, 16);
	serial_puts(" ## ### ## ");
	vt100_move(xxx, 17);
	serial_puts("###########");
	vt100_move(xxx, 18);
	serial_puts("# ####### #");
	vt100_move(xxx, 19);
	serial_puts("# #     # #");
	vt100_move(xxx, 20);
	serial_puts("   ## ##    ");

	vt100_move(61, 13); //11x8
	serial_puts("  #     #  ");
	vt100_move(61, 14);
	serial_puts("   #   #   ");
	vt100_move(61, 15);
	serial_puts("  #######  ");
	vt100_move(61, 16);
	serial_puts(" ## ### ## ");
	vt100_move(61, 17);
	serial_puts("###########");
	vt100_move(61, 18);
	serial_puts("# ####### #");
	vt100_move(61, 19);
	serial_puts("# #     # #");
	vt100_move(61, 20);
	serial_puts("   ## ##    ");
	int xx = 25;
	vt100_move(29, 10);
	serial_puts(" Les règles du jeu  sont :");
	vt100_move(29, 11);
	serial_puts(" ________________________");

	vt100_move(xx, 13);
	serial_puts("- Tuer tout les ennemis 'Z' = tir ");
	vt100_move(xx, 15);
	serial_puts("- Survivre aux tirs ennemis ");
	vt100_move(xx, 17);
	serial_puts("- 'Q' -> gauche  'D' -> droite ");
	vt100_move(xx, 19);
	serial_puts("- 'P' -> met le jeu en pause ");



}
void mechants(donnees_ennemis *ptr_enn) {
	//vt100_clear_screen();
	vt100_move(ptr_enn->x_enn, ptr_enn->y_enn);
	if (ptr_enn->type == 1)
		serial_puts("||==0==||");
	else if (ptr_enn->type == 2)
		serial_puts("\\\\=0=//");
	else if (ptr_enn->type == 3)
		serial_puts("[-0-]");

}

void mon_vaisseau() {
	vt100_move(m, 20);
	serial_puts("//0\\\\");

}

void move_vaisseau(int carac) {


	vt100_move(m, 21);
	serial_puts("//0\\\\");
	if (m < LIMITE_MAX + 4) {
		if (carac == 'd') {
			vt100_move(m, 21);
			serial_puts("     ");
			m += 1;
			vt100_move(m, 21);
			serial_puts("//0\\\\");
		}
	}
	if (m > LIMITE_MIN - 1) {
		if (carac == 'q') {
			vt100_move(m, 21);
			serial_puts("     ");
			m -= 1;
			vt100_move(m, 21);
			serial_puts("//0\\\\");
		}
	}
}

void fin() {
	vt100_move(35, 10);
	serial_puts("Dommage,  \n");
	vt100_move(22, 12);
	serial_puts("La prochaine fois sera la bonne \n");
	vt100_move(22, 14);
	serial_puts("Appuyer sur 'ESPACE' pour recommencer \n");
	vt100_move(53, 23);
	serial_puts("Develloped by Ramounchito \n");

}
void findujeu() {
	vt100_move(35, 8);
	serial_puts("Bien joué,  \n");
	vt100_move(22, 10);
	serial_puts("  La prochaine fois tu feras encore mieux ");
	vt100_move(22, 12);
	serial_puts("Appuyer sur le bouton Reset pour recommencer");
	vt100_move(22, 14);
	serial_puts("   Le bouton noir sur ta carte stm32");
	vt100_move(53, 23);
	serial_puts("Develloped by Ramounchito \n");
	while (1)
		;
}
int i = 0;
void move_mechants(donnees_ennemis *ptr_enn) {
	if (ptr_enn->hit_enn == 1)
		return;
	vt100_move(ptr_enn->x_enn, ptr_enn->y_enn);
	if (ptr_enn->type == 1)
		serial_puts("         ");
	else if (ptr_enn->type == 2)
		serial_puts("         ");
	else if (ptr_enn->type == 3)
		serial_puts("      ");
	if (ptr_enn->y_enn % 2 == 0) {
		if (ptr_enn->x_enn < LIMITE_MAX) {
			ptr_enn->x_enn += 1;
		} else {
			ptr_enn->y_enn += 1;
		}
	} else {
		if (ptr_enn->x_enn > LIMITE_MIN) {
			ptr_enn->x_enn -= 1;
		} else {
			ptr_enn->y_enn += 1;
		}
	}
	vt100_move(ptr_enn->x_enn, ptr_enn->y_enn);
	if (ptr_enn->type == 1)
		serial_puts("||==0==||");
	else if (ptr_enn->type == 2)
		serial_puts("\\\\=0=//");
	else if (ptr_enn->type == 3)
		serial_puts("[-0-]");
	timer(TIMER);
}

void defense() {
	vt100_move(10, 17);
	serial_puts("=====");
	vt100_move(40, 17);
	serial_puts("=====");
	vt100_move(70, 17);
	serial_puts("=====");

}
void info() {
	vt100_move(2, 2);
	serial_puts("Vies = ");
	vt100_move(67, 2);
	serial_puts("Points = ");

}

void tir(int carac) { //tir+hitbox
	uint8_t i;
	x_tir = m + 2;
	int test_tir = 0;
	if (carac == 'z') {
		for (y = 20; y > 1 && test_tir == 0; y--) {
			//timer(10);

			vt100_move(x_tir, y);
			serial_puts("|");
			timer(TIMER);
			vt100_move(x_tir, y);
			serial_puts(" ");

			for (i = 0; i < 20; i++) {

				if (y == ennemis[i].y_enn && x_tir >= ennemis[i].x_enn
						&& x_tir <= ennemis[i].x_enn + HITBOX
						&& ennemis[i].hit_enn == 0) {
					vt100_move(ennemis[i].x_enn, ennemis[i].y_enn);
					serial_puts("         ");
					ennemis[i].hit_enn = 1;
					compteur_enn += 1;
					test_tir += 1;
					if (ptr_enn->type == 1)
						points += 300;
					else if (ptr_enn->type == 2)
						points += 200;
					else if (ptr_enn->type == 3)
						points += 100;
					if (compteur_enn >= 20) {
						vt100_clear_screen();
						findujeu();
					}
				}
			}

		}
	}

}
//
//void tir() {
//	x_tir = m + 2;
//	if (carac == 'z') {
//		for (y = 20; y > 1; y--) {
//			//timer(10);
//			vt100_move(x_tir, y);
//			serial_puts("|");
//			vt100_move(x_tir, y);
//			serial_puts(" ");
//			if (y == *py && x_tir >= *px && x_tir <= *px + HITBOX) {
//				vt100_move(*px, *py);
//				serial_puts("         ");
//			}
//			if (y == 3 && x_tir >= x_enn2 && x_tir <= x_enn2 + HITBOX) {
//				vt100_move(x_enn2, y_enn);
//				serial_puts("         ");
//			}
//			if (y == 3 && x_tir >= x_enn3 && x_tir <= x_enn3 + HITBOX) {
//				vt100_move(x_enn3, y_enn);
//				serial_puts("         ");
//			}
//			if (y == 3 && x_tir >= x_enn4 && x_tir <= x_enn4 + HITBOX) {
//				vt100_move(x_enn4, y_enn);
//				serial_puts("         ");
//			}
//			if (y == 3 && x_tir >= x_enn5 && x_tir <= x_enn5 + HITBOX) {
//				vt100_move(x_enn5, y_enn);
//				serial_puts("         ");
//			}
//			if (hit_enn6 != 1 && y == 6 && x_tir >= x_enn6
//			&& x_tir <= x_enn6 + HITBOX2) {
//				vt100_move(x_enn6, y_enn2);
//				serial_puts("         ");
//				y = 2;
//				hit_enn6 += 1;
//
//			}
//			if (hit_enn7 != 1 && y == 6 && x_tir >= x_enn7
//			&& x_tir <= x_enn7 + HITBOX2) {
//				vt100_move(x_enn7, y_enn2);
//				serial_puts("         ");
//				y = 2;
//				hit_enn7 += 1;
//			}
//			if (hit_enn8 != 1 && y == 6 && x_tir >= x_enn8
//			&& x_tir <= x_enn8 + HITBOX2) {
//				vt100_move(x_enn8, y_enn2);
//				serial_puts("        ");
//				y = 2;
//				hit_enn8 += 1;
//			}
//			if (hit_enn9 != 1 && y == 6 && x_tir >= x_enn9
//			&& x_tir <= x_enn9 + HITBOX2) {
//				vt100_move(x_enn9, y_enn2);
//				serial_puts("        ");
//				y = 2;
//				hit_enn9 += 1;
//			}
//			if (hit_enn10 != 1 && y == 6 && x_tir >= x_enn10
//			&& x_tir <= x_enn10 + HITBOX2) {
//				vt100_move(x_enn10, y_enn2);
//				serial_puts("        ");
//				y = 2;
//				hit_enn10 += 1;
//			}
//			if (hit_enn11 != 1 && y == 6 && x_tir >= x_enn11
//			&& x_tir <= x_enn11 + HITBOX2) {
//				vt100_move(x_enn11, y_enn2);
//				serial_puts("        ");
//				y = 2;
//				hit_enn11 += 1;
//			}
//			if (hit_enn12 != 1 && y == y_enn3 && x_tir >= x_enn12
//			&& x_tir <= x_enn12 + HITBOX2) {
//				vt100_move(x_enn12, y_enn3);
//				serial_puts("       ");
//				y = 2;
//				hit_enn12 += 1;
//			}
//			if (hit_enn13 != 1 && y == y_enn3 && x_tir >= x_enn13
//			&& x_tir <= x_enn13 + HITBOX3) {
//				vt100_move(x_enn13, y_enn3);
//				serial_puts("      ");
//				y = 2;
//				hit_enn13 += 1;
//			}
//			if (hit_enn14 != 1 && y == y_enn3 && x_tir >= x_enn14
//			&& x_tir <= x_enn14 + HITBOX3) {
//				vt100_move(x_enn14, y_enn3);
//				serial_puts("      ");
//				y = 2;
//				hit_enn14 += 1;
//			}
//			if (hit_enn15 != 1 && y == y_enn3 && x_tir >= x_enn15
//			&& x_tir <= x_enn15 + HITBOX3) {
//				vt100_move(x_enn15, y_enn3);
//				serial_puts("      ");
//				y = 2;
//				hit_enn15 += 1;
//			}
//			if (hit_enn16 != 1 && y == y_enn3 && x_tir >= x_enn16
//			&& x_tir <= x_enn16 + HITBOX3) {
//				vt100_move(x_enn16, y_enn3);
//				serial_puts("      ");
//				y = 2;
//				hit_enn16 += 1;
//			}
//			if (hit_enn17 != 1 && y == y_enn3 && x_tir >= x_enn17
//			&& x_tir <= x_enn17 + HITBOX3) {
//				vt100_move(x_enn17, y_enn3);
//				serial_puts("      ");
//				y = 2;
//				hit_enn17 += 1;
//			}
//			if (hit_enn18 != 1 && y == y_enn3 && x_tir >= x_enn18
//			&& x_tir <= x_enn18 + HITBOX3) {
//				vt100_move(x_enn18, y_enn3);
//				serial_puts("      ");
//				y = 2;
//				hit_enn18 += 1;
//			}
//			if (hit_enn19 != 1 && y == y_enn3 && x_tir >= x_enn19
//			&& x_tir <= x_enn19 + HITBOX3) {
//				vt100_move(x_enn19, y_enn3);
//				serial_puts("      ");
//				y = 2;
//				hit_enn19 += 1;
//			}
//			if (hit_enn20 != 1 && y == y_enn3 && x_tir >= x_enn20
//			&& x_tir <= x_enn20 + HITBOX3) {
//				vt100_move(x_enn20, y_enn3);
//				serial_puts("      ");
//				y = 2;
//				hit_enn20 += 1;
//			}
//		}
//	}
//}

void commencer() {

	while (serial_get_last_char() != ' ') {

	}
}
void pause(int carac) {
	if (carac == 'p') {
		vt100_clear_screen();
		vt100_move(27, 9);
		serial_puts("####  ####  #  #  ####  #####");
		vt100_move(27, 10);
		serial_puts("#  #  #  #  #  #  #     #   ");
		vt100_move(27, 11);
		serial_puts("#  #  #  #  #  #  #     #   ");
		vt100_move(27, 12);
		serial_puts("####  ####  #  #  ####  #####");
		vt100_move(27, 13);
		serial_puts("#     #  #  #  #     #  #   ");
		vt100_move(27, 14);
		serial_puts("#     #  #  #  #     #  #");
		vt100_move(27, 15);
		serial_puts("#     #  #  ####  ####  #####");

		while (serial_get_last_char() != 'p') {


		}
		vt100_clear_screen();
		Bordures();
	}
}

int main(void) {
	uint8_t i;

	Bordures();
	Acceuil();
	commencer();
	vt100_clear_screen();
	Bordures();

	for (i = 0; i < 20; i++)
		mechants(&ennemis[i]);

	/* Initialize LEDs */
	STM_EVAL_LEDInit(LED3);
	STM_EVAL_LEDInit(LED4);
	STM_EVAL_LEDInit(LED5);
	STM_EVAL_LEDInit(LED6);

	/* Turn on LEDs */
	STM_EVAL_LEDOn(LED3);
	STM_EVAL_LEDOn(LED4);
	STM_EVAL_LEDOn(LED5);
	STM_EVAL_LEDOn(LED6);

	/* Infinite loop */

	while (1) {
		int carac = serial_get_last_char();
		pause(carac);
		tir(carac);
		move_vaisseau(carac);
		defense();
		info();
		for (i = 0; i < 20; i++)
			move_mechants(&ennemis[i]);

		if (ptr_enn->y_enn > 20) {
			vt100_clear_screen();
			while (1) {

				fin();
				commencer();
			}
		}

	}
}

void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size) {
	return;
}
uint16_t EVAL_AUDIO_GetSampleCallBack(void) {
	return -1;
}
