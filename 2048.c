/* Programarea Calculatoarelor, seria CC
 * Tema2 - 2048
 */
#include <ctype.h>
#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

/* ctype.h este necesar pentru funcția tolower
 * curses.h este necesar pentru biblioteca grafică ncurses
 * stdio.h este necesara pentru pentru citire și scriere
 * stdlib.h este necesara pentru generarea de numere aleatoare
 * time.h este necesar pentru citirea timpului curent
 * unistd.h este necesara pentru functia sleep
 */

// functie pentru generarea unui numar in joc
void numarnou(int tabla[4][4]) {
  int linie, coloana;
  // se executa pana celula gasita este goala
  do {
    // linie si coloana primesc niste numere la intamplare
    linie = rand() / 10 % 4;
    coloana = rand() % 4;
  } while (tabla[linie][coloana]);

  // se genereaza la intamplare numarul 2 sau 4
  tabla[linie][coloana] = (rand() % 2 + 1) * 2;
}

// functia pentru gasirea mutarii care elibereaza cele mai multe spatii
int mutareautomata(int tabla[4][4]) {
  int i, j, k, directie;
  // se va vedea cate spatii se elibereaza in urma fiecarei mutari, numarul de
  // spatii libere fiind salvate in variabilele urmatoare
  int sus = 0, jos = 0, stanga = 0, dreapta = 0, initial = 0;
  int copie[4][4];

  // se afla cate spatii goale are tabla initiala
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      if (!tabla[i][j]) {
        initial++;
      }
    }
  }

  // se creeaza o copie in care vom efectua mutarea la stanga
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      copie[i][j] = tabla[i][j];
    }
  }
  // se efectueaza mutarea la stanga pentru a avea celulele cu aleleasi numere
  // una langa alta
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 3; j++) {
      for (k = j + 1; k < 4; k++) {
        if (!copie[i][j] && copie[i][k]) {
          copie[i][j] = copie[i][k];
          copie[i][k] = 0;
        }
      }
    }
    // daca sunt celule alaturate cu acelasi numar le aduna intr-o celula iar in
    // cealalta se face 0
    for (j = 0; j < 3; j++) {
      if (copie[i][j] == copie[i][j + 1] && copie[i][j]) {
        copie[i][j] = copie[i][j] * 2;
        copie[i][j + 1] = 0;
      }
    }
    // se mai muta o data la stanga pentru ca in urma forului anterior nu mai
    // sunt toate multate la stanga
    for (j = 0; j < 3; j++) {
      for (k = j + 1; k < 4; k++) {
        if (!copie[i][j] && copie[i][k]) {
          copie[i][j] = copie[i][k];
          copie[i][k] = 0;
        }
      }
    }
  }
  // se afla cate spatii goale sunt dupa mutarea la stanga
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      if (!copie[i][j]) {
        stanga++;
      }
    }
  }

  // se creeaza o copie in care vom efectua mutarea la dreapta
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      copie[i][j] = tabla[i][j];
    }
  }
  // se efectueaza mutarea la dreapta pentru a avea celulele cu aleleasi numere
  // una langa alta
  for (i = 0; i < 4; i++) {
    for (j = 3; j > 0; j--) {
      for (k = j - 1; k >= 0; k--) {
        if (!copie[i][j] && copie[i][k]) {
          copie[i][j] = copie[i][k];
          copie[i][k] = 0;
        }
      }
    }
    // daca sunt celule alaturate cu acelasi numar le aduna intr-o celula iar in
    // cealalta se face 0
    for (j = 3; j > 0; j--) {
      if (copie[i][j] == copie[i][j - 1] && copie[i][j]) {
        copie[i][j] = copie[i][j] * 2;
        copie[i][j - 1] = 0;
      }
    }
    // se mai muta o data la dreapta pentru ca in urma forului anterior nu mai
    // sunt toate multate la dreapta
    for (j = 3; j > 0; j--) {
      for (k = j - 1; k >= 0; k--) {
        if (!copie[i][j] && copie[i][k]) {
          copie[i][j] = copie[i][k];
          copie[i][k] = 0;
        }
      }
    }
  }
  // se afla cate spatii goale sunt dupa mutarea la dreapta
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      if (!copie[i][j]) {
        dreapta++;
      }
    }
  }

  // se creeaza o copie in care vom efectua mutarea in sus
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      copie[i][j] = tabla[i][j];
    }
  }
  // se efectueaza mutarea in sus pentru a avea celulele cu aleleasi numere una
  // langa alta
  for (j = 0; j < 4; j++) {
    for (i = 0; i < 3; i++) {
      for (k = i + 1; k < 4; k++) {
        if (!copie[i][j] && copie[k][j]) {
          copie[i][j] = copie[k][j];
          copie[k][j] = 0;
        }
      }
    }
    // daca sunt celule alaturate cu acelasi numar le aduna intr-o celula iar in
    // cealalta se face 0
    for (i = 0; i < 3; i++) {
      if (copie[i][j] == copie[i + 1][j] && copie[i][j]) {
        copie[i][j] = copie[i][j] * 2;
        copie[i + 1][j] = 0;
      }
    }
    // se mai muta o data in sus pentru ca in urma forului anterior nu mai
    // sunt toate multate in sus
    for (i = 0; i < 3; i++) {
      for (k = i + 1; k < 4; k++) {
        if (!copie[i][j] && copie[k][j]) {
          copie[i][j] = copie[k][j];
          copie[k][j] = 0;
        }
      }
    }
  }
  // se afla cate spatii goale sunt dupa mutarea in sus
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      if (!copie[i][j]) {
        sus++;
      }
    }
  }

  // se creeaza o copie in care vom efectua mutarea in jos
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      copie[i][j] = tabla[i][j];
    }
  }
  // se efectueaza mutarea in jos pentru a avea celulele cu aleleasi numere una
  // langa alta
  for (j = 0; j < 4; j++) {
    for (i = 3; i > 0; i--) {
      for (k = i - 1; k >= 0; k--) {
        if (!copie[i][j] && copie[k][j]) {
          copie[i][j] = copie[k][j];
          copie[k][j] = 0;
        }
      }
    }
    // daca sunt celule alaturate cu acelasi numar le aduna intr-o celula iar in
    // cealalta se face 0
    for (i = 3; i > 0; i--) {
      if (copie[i][j] == copie[i - 1][j] && copie[i][j]) {
        copie[i][j] = copie[i][j] * 2;
        copie[i - 1][j] = 0;
      }
    }
    // se mai muta o data in jos pentru ca in urma forului anterior nu mai
    // sunt toate multate in jos
    for (i = 3; i > 0; i--) {
      for (k = i - 1; k >= 0; k--) {
        if (!copie[i][j] && copie[k][j]) {
          copie[i][j] = copie[k][j];
          copie[k][j] = 0;
        }
      }
    }
  }
  // se afla cate spatii goale sunt dupa mutarea in jos
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      if (!copie[i][j]) {
        jos++;
      }
    }
  }

  sus = sus - initial;
  jos = jos - initial;
  stanga = stanga - initial;
  dreapta = dreapta - initial;
  int vdirectie[5], z = 0;
  // se verfica daca mutarile au eliberat spatii si se salveaza intr-un vector
  // mutarile care au eliberat acelasi numar de spatii pentru a lua la
  // intamplare o mutare dintre acestea
  if (!sus && !jos && !stanga && !dreapta) {
    directie = rand() % 4;
  } else {
    if (sus >= jos && sus >= dreapta && sus >= stanga) {
      vdirectie[z] = 2;
      z++;
    }
    if (jos >= sus && jos >= dreapta && jos >= stanga) {
      vdirectie[z] = 3;
      z++;
    }
    if (dreapta >= jos && dreapta >= sus && dreapta >= stanga) {
      vdirectie[z] = 1;
      z++;
    }
    if (stanga >= jos && stanga >= dreapta && stanga >= sus) {
      vdirectie[z] = 0;
      z++;
    }
    directie = vdirectie[rand() % z];
  }
  return directie;
}

// functia pentru mutare, inregistrare scor si verificare daca o mutare este
// valida prin variabila nupot
int mutare(int directie2, int tabla[4][4], int *scor) {
  int i, j, k, nupot = 0;

  // fac mutarile si imbinarile la stanga
  if (directie2 == 0) {
    // se efectueaza mutarea la stanga pentru a avea celulele cu aleleasi numere
    // una langa alta
    for (i = 0; i < 4; i++) {
      for (j = 0; j < 3; j++) {
        for (k = j + 1; k < 4; k++) {
          if (!tabla[i][j] && tabla[i][k]) {
            tabla[i][j] = tabla[i][k];
            tabla[i][k] = 0;
            nupot = 1;
          }
        }
      }
      // daca sunt celule alaturate cu acelasi numar le aduna intr-o celula iar
      // in cealalta se face 0
      for (j = 0; j < 3; j++) {
        if (tabla[i][j] == tabla[i][j + 1] && tabla[i][j]) {
          tabla[i][j] = tabla[i][j] * 2;
          tabla[i][j + 1] = 0;
          nupot = 1;
          *scor = *scor + tabla[i][j];
        }
      }
      // se mai muta o data la stanga pentru ca in urma forului anterior nu mai
      // sunt toate multate la stanga
      for (j = 0; j < 3; j++) {
        for (k = j + 1; k < 4; k++) {
          if (!tabla[i][j] && tabla[i][k]) {
            tabla[i][j] = tabla[i][k];
            tabla[i][k] = 0;
            nupot = 1;
          }
        }
      }
    }
  }

  // fac mutarile si imbinarile la dreapta
  if (directie2 == 1) {
    // se efectueaza mutarea la dreapta pentru a avea celulele cu aleleasi
    // numere una langa alta
    for (i = 0; i < 4; i++) {
      for (j = 3; j > 0; j--) {
        for (k = j - 1; k >= 0; k--) {
          if (!tabla[i][j] && tabla[i][k]) {
            tabla[i][j] = tabla[i][k];
            tabla[i][k] = 0;
            nupot = 1;
          }
        }
      }
      // daca sunt celule alaturate cu acelasi numar le aduna intr-o celula iar
      // in cealalta se face 0
      for (j = 3; j > 0; j--) {
        if (tabla[i][j] == tabla[i][j - 1] && tabla[i][j]) {
          tabla[i][j] = tabla[i][j] * 2;
          tabla[i][j - 1] = 0;
          nupot = 1;
          *scor = *scor + tabla[i][j];
        }
      }
      // se mai muta o data la dreapta pentru ca in urma forului anterior nu mai
      // sunt toate multate la dreapta
      for (j = 3; j > 0; j--) {
        for (k = j - 1; k >= 0; k--) {
          if (!tabla[i][j] && tabla[i][k]) {
            tabla[i][j] = tabla[i][k];
            tabla[i][k] = 0;
            nupot = 1;
          }
        }
      }
    }
  }

  // fac mutarile si imbinarile in sus
  if (directie2 == 2) {
    // se efectueaza mutarea in sus pentru a avea celulele cu aleleasi numere
    // una langa alta
    for (j = 0; j < 4; j++) {
      for (i = 0; i < 3; i++) {
        for (k = i + 1; k < 4; k++) {
          if (!tabla[i][j] && tabla[k][j]) {
            tabla[i][j] = tabla[k][j];
            tabla[k][j] = 0;
            nupot = 1;
          }
        }
      }
      // daca sunt celule alaturate cu acelasi numar le aduna intr-o celula iar
      // in cealalta se face 0
      for (i = 0; i < 3; i++) {
        if (tabla[i][j] == tabla[i + 1][j] && tabla[i][j]) {
          tabla[i][j] = tabla[i][j] * 2;
          tabla[i + 1][j] = 0;
          nupot = 1;
          *scor = *scor + tabla[i][j];
        }
      }
      // se mai muta o data in sus pentru ca in urma forului anterior nu mai
      // sunt toate multate in sus
      for (i = 0; i < 3; i++) {
        for (k = i + 1; k < 4; k++) {
          if (!tabla[i][j] && tabla[k][j]) {
            tabla[i][j] = tabla[k][j];
            tabla[k][j] = 0;
            nupot = 1;
          }
        }
      }
    }
  }

  // fac mutarile si imbinarile in jos
  if (directie2 == 3) {
    // se efectueaza mutarea in jos pentru a avea celulele cu aleleasi numere
    // una langa alta
    for (j = 0; j < 4; j++) {
      for (i = 3; i > 0; i--) {
        for (k = i - 1; k >= 0; k--) {
          if (!tabla[i][j] && tabla[k][j]) {
            tabla[i][j] = tabla[k][j];
            tabla[k][j] = 0;
            nupot = 1;
          }
        }
      }
      // daca sunt celule alaturate cu acelasi numar le aduna intr-o celula iar
      // in cealalta se face 0
      for (i = 3; i > 0; i--) {
        if (tabla[i][j] == tabla[i - 1][j] && tabla[i][j]) {
          tabla[i][j] = tabla[i][j] * 2;
          tabla[i - 1][j] = 0;
          nupot = 1;
          *scor = *scor + tabla[i][j];
        }
      }
      // se mai muta o data in jos pentru ca in urma forului anterior nu mai
      // sunt toate multate in jos
      for (i = 3; i > 0; i--) {
        for (k = i - 1; k >= 0; k--) {
          if (!tabla[i][j] && tabla[k][j]) {
            tabla[i][j] = tabla[k][j];
            tabla[k][j] = 0;
            nupot = 1;
          }
        }
      }
    }
  }
  return nupot;
}

// functie pentru verificare daca s-a ajuns la 2048
int acastigat(int tabla[4][4]) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (tabla[i][j] == 2048) {
        // S-a atins valoarea 2048, jocul este câștigat
        return 1;
      }
    }
  }

  return 0;  // Nu s-a atins valoarea 2048
}

// functie pentru verificare daca nu mai sunt mutari posibile
int apierdut(int tabla[4][4]) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (!tabla[i][j]) {
        // Există celule libere, jocul nu s-a încheiat
        return 0;
      }

      if ((i + 1 < 4 && tabla[i][j] == tabla[i + 1][j]) ||
          (j + 1 < 4 && tabla[i][j] == tabla[i][j + 1])) {
        // Există celule vecine cu aceeași valoare
        return 0;
      }
    }
  }
  // Nu există celule libere și nici perechi vecine cu aceeași valoare
  return 1;
}

// functie pentru desenarea jocului
void interfata(int tabla[4][4], int scor, int topscor) {
  int i, j;
  for (i = 0; i < 4; ++i) {
    for (j = 0; j < 4; ++j) {
      // sterge elementul precedent, pentru a nu da clear, deoarece arata urat
      // cand dau clear
      mvprintw(i * 2 + 1, j * 5 + 1, "    ");
      mvprintw(i * 2 + 1, j * 5 + 1, "%d", tabla[i][j]);
      // Delimitare cu caractere ascii linii si bari

      mvhline(i * 2 + 2, j * 5, 0, 5);
      mvvline(i * 2, j * 5 + 5, 0, 2);
      mvvline(i * 2, j * 5, 0, 2);
      mvhline(0, j * 5, 0, 5);

      mvaddch(0, 20, '+');
      mvaddch(0, 0, '+');
      mvaddch(8, 20, '+');
      mvaddch(8, 0, '+');
    }
  }
  // afisaza pe ecran ce face fiecare tasta
  mvprintw(2, 25, "A-muta la stanga casutele");
  mvprintw(3, 25, "D-muta la dreapta casutele");
  mvprintw(4, 25, "W-muta in sus casutele");
  mvprintw(5, 25, "S-muta in jos casutele");
  mvprintw(6, 25, "Q-iesi din joc");
  mvprintw(
      8, 25,
      "Daca nu faceti o mutare in 10 secunde aceasta va fi facuta automat");
  mvprintw(7, 25, "R-pentru a reseta cel mai bun scor");
  // Afiseaza ora curenta si data
  time_t ora;
  time(&ora);
  // o facem o structura pentru a ne putea referi mai usor la fiecare element
  struct tm *structora = localtime(&ora);
  mvprintw(0, 25, "Data curenta: %02d/%02d/%04d", structora->tm_mday,
           structora->tm_mon + 1, structora->tm_year + 1900);
  mvprintw(1, 25, "Ora curenta: %02d:%02d:%02d", structora->tm_hour,
           structora->tm_min, structora->tm_sec);

  mvprintw(9, 0, "Scorul tau este:%d", scor);
  // spatiul este pentru a sterge scorul initial
  mvprintw(10, 0, "Cel mai bun scor este:%d          ", topscor);

  // Refresh pentru a afișa modificările
  refresh();
}

int main(void) {
  // ofera un seed diferit de fiecare data cand deschid aplicatia, pentru a nu
  // primi aceleasi numere pe aceleasi casute de fiecare data
  srand(time(NULL));
  int i, j;
  // in tasta se salveaza ce se apasa de la tastatura
  int tasta;
  // in loc salvam pozitia in care ne aflam in meniu, iar vechil si vechic le
  // folosesc pentru a avea doar o optiune iboldita
  int loc = 1, vechil = 1, vechic = 11;
  // tabla de joc
  int tabla[4][4] = {0};
  // scorul curent si cel mai bun scor de pana acum
  int scor = 0, topscor = 0;
  // variabile de tip da si nu pentru a verifica daca a inceput sau nu un meci
  int ainceput = 0, ainceput2 = 0, ainceput3 = 0, pierdut = 0;
  // retina cand a fost apasata ultima tasta pentru implementarea mutarii
  // automate
  int timptasta;
  // pentru a nu avea cel mai bun scor doar din sesiunea curenta salvam cel mai
  // bun scor intr-un fisier
  FILE *fisier = fopen("scor.txt", "r");
  if (fisier != NULL) {
    fscanf(fisier, "%d", &topscor);
    fclose(fisier);
  }

  /* Se inițializează ecranul; initscr se va folosi în mod obligatoriu */
  WINDOW *ecran = initscr();

  /* Se șterge ecranul */
  clear();
  /* Se inhibă afișarea caracterelor introduse de la tastatură */
  noecho();
  // activeaza ctrl+c pentru a iesi din aplicatie in cazul in care nu
  // functioneaza cum am dori
  cbreak();
  /* Se ascunde cursorul */
  curs_set(0);

  // desenam meniul
  mvprintw(0, 0, "Meniu Principal");
  mvprintw(1, 0, "1. New Game");
  mvprintw(2, 0, "2. Resume");
  mvprintw(3, 0, "3. Quit");
  mvprintw(1, 11, "<-");

  // iboldim initial New Game
  wattron(ecran, A_REVERSE);
  mvwprintw(ecran, 1, 0, "1. New Game");
  wattroff(ecran, A_REVERSE);
  refresh();
  // activam folosirea sagetilor
  keypad(stdscr, TRUE);
  while (1) {
    tasta = getch();

    // urca sau coboara doar daca are cum deoarece avem doar 3 alegeri
    switch (tasta) {
      case KEY_UP:
        if (loc > 1) {
          loc--;
        }
        break;
      case KEY_DOWN:
        if (loc < 3) {
          loc++;
        }
        break;
    }
    // daca ne aflam pe New Game acesta va fi iboldit cu o sageata in dreptul
    // optiunii, iar optiunea veche se deiboldeste
    if (loc == 1) {
      mvwprintw(ecran, 2, 0, "2. Resume");
      mvwprintw(ecran, 3, 0, "3. Quit");
      wattron(ecran, A_REVERSE);
      mvwprintw(ecran, 1, 0, "1. New Game");
      wattroff(ecran, A_REVERSE);
      mvprintw(vechil, vechic, "  ");
      mvprintw(1, 11, "<-");
      vechil = 1;
      vechic = 11;
    }
    // daca ne aflam pe Resume acesta va fi iboldit cu o sageata in dreptul
    // optiunii, iar optiunea veche se deiboldeste
    if (loc == 2) {
      mvwprintw(ecran, 1, 0, "1. New Game");
      mvwprintw(ecran, 3, 0, "3. Quit");
      wattron(ecran, A_REVERSE);
      mvwprintw(ecran, 2, 0, "2. Resume");
      wattroff(ecran, A_REVERSE);
      mvprintw(vechil, vechic, "  ");
      mvprintw(2, 9, "<-");
      vechil = 2;
      vechic = 9;
    }
    // daca ne aflam pe Quit acesta va fi iboldit cu o sageata in dreptul
    // optiunii, iar optiunea veche se deiboldeste
    if (loc == 3) {
      mvwprintw(ecran, 1, 0, "1. New Game");
      mvwprintw(ecran, 2, 0, "2. Resume");
      wattron(ecran, A_REVERSE);
      mvwprintw(ecran, 3, 0, "3. Quit");
      wattroff(ecran, A_REVERSE);
      mvprintw(vechil, vechic, "  ");
      mvprintw(3, 7, "<-");
      vechil = 3;
      vechic = 7;
    }

    // Enter este 10 in codul ascii
    if (tasta == 10) {
      // daca dau resume sau new game se intampla aproape acelasi lucru
      if (loc == 1 || loc == 2) {
        // se retine ca a inceput jocul, pentru a se reseta timerul
        timptasta = clock();
        if (loc == 1) {
          // daca dam new game se reseteaza tabla
          for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
              tabla[i][j] = 0;
            }
          }
          scor = 0;
          ainceput = 1;
          numarnou(tabla);
          numarnou(tabla);
          pierdut = 0;
        }
        if (ainceput == 1) {
          clear();
          interfata(tabla, scor, topscor);
          refresh();
          // trece de getch chiar daca nu  afost citit nimic de la tastatura
          nodelay(ecran, TRUE);
          while (1) {
            // daca s-a pierdut un meci atunci se verifica daca top scorul este
            // mai mare sau mai mic decat cel curent pentru a se putea salva cel
            // mai mare si se revine la meniul principal
            if (apierdut(tabla)) {
              if (topscor < scor) {
                topscor = scor;
              }
              // se salveaza in fisier cel mai bun scor
              FILE *fisier = fopen("scor.txt", "w");
              if (fisier != NULL) {
                fprintf(fisier, "%d", topscor);
                fclose(fisier);
              }
              ainceput = 0;
              ainceput2 = 0;
              ainceput3 = 0;
              pierdut = 1;
              // se afisaza pe ecran pentru 3 secunde ca ai pierdut si scorul cu
              // care ai pierdut
              clear();
              mvprintw(4, 0, "Ai pierdut cu un scor de:%d", scor);
              refresh();
              sleep(3);
              clear();
              // se deseneaza meniul
              mvprintw(0, 0, "Meniu Principal");
              mvprintw(1, 0, "1. New Game");
              mvprintw(2, 0, "2. Resume    ");
              mvprintw(3, 0, "3. Quit");
              mvprintw(1, 11, "<-");

              wattron(ecran, A_REVERSE);
              mvwprintw(ecran, 1, 0, "1. New Game");
              wattroff(ecran, A_REVERSE);
              // se seteaza New Game prima optiune dupa terminare
              loc = 1;
              refresh();
              break;
            }
            tasta = getch();
            // daca nu a fost apasata nici-o tasta se afisaza interfata pentru a
            // reseta ora, altfel se executa comanda corespunzatoare tastei
            // apasate
            if (tasta == ERR) {
              interfata(tabla, scor, topscor);
              clock_t ora = clock();
              // se face miscarea dupa 10 sec
              if ((ora - timptasta) > 10000000) {
                if (mutare(mutareautomata(tabla), tabla, &scor)) {
                  numarnou(tabla);
                  interfata(tabla, scor, topscor);
                  refresh();
                }
                // Actualizează timpul ultimei mișcări automate
                timptasta = clock();
              }
            } else {
              // se reseteaza timpul cand a fost apasata ultima tasta
              timptasta = clock();
              // daca se apasa q atunci se va iesi la meniul principal
              if (tasta == 'q') {
                loc = 1;
                vechil = 1;
                vechic = 11;

                clear();
                mvprintw(0, 0, "Meniu Principal");
                mvprintw(1, 0, "1. New Game");
                mvprintw(2, 0, "2. Resume");
                mvprintw(3, 0, "3. Quit");
                mvprintw(1, 11, "<-");

                wattron(ecran, A_REVERSE);
                mvwprintw(ecran, 1, 0, "1. New Game");
                wattroff(ecran, A_REVERSE);
                refresh();
                break;
              }
              // daca se apasa r atunci se reseteaza cel mai mare scor
              if (tasta == 'r') {
                FILE *fisier = fopen("scor.txt", "w");
                if (fisier != NULL) {
                  fprintf(fisier, "0");
                  fclose(fisier);
                  topscor = 0;
                  interfata(tabla, scor, topscor);
                }
              }
              // fiecarei mutari ii este atribuit in numar in functia mutare
              // care se executa daca se poate
              switch (tolower(tasta)) {
                case 'a':
                  if (mutare(0, tabla, &scor)) {
                    numarnou(tabla);
                    interfata(tabla, scor, topscor);
                  }
                  break;
                case 'd':
                  if (mutare(1, tabla, &scor)) {
                    numarnou(tabla);
                    interfata(tabla, scor, topscor);
                  }
                  break;
                case 'w':
                  if (mutare(2, tabla, &scor)) {
                    numarnou(tabla);
                    interfata(tabla, scor, topscor);
                  }
                  break;
                case 's':
                  if (mutare(3, tabla, &scor)) {
                    numarnou(tabla);
                    interfata(tabla, scor, topscor);
                  }
                  break;
              }
              // daca s-a castigat un meci atunci se verifica daca top scorul
              // este mai mare sau mai mic decat cel curent pentru a se putea
              // salva cel mai mare si se revine la meniul principal
              if (acastigat(tabla)) {
                if (topscor < scor) {
                  topscor = scor;
                }
                // se salveaza in fisier cel mai bun scor
                FILE *fisier = fopen("scor.txt", "w");
                if (fisier != NULL) {
                  fprintf(fisier, "%d", topscor);
                  fclose(fisier);
                }
                ainceput = 0;
                ainceput2 = 0;
                ainceput3 = 0;
                pierdut = 2;
                // se afisaza pe ecran pentru 3 secunde ca ai pierdut si scorul
                // cu care ai pierdut
                clear();
                mvprintw(4, 0, "Felicitari! Ai castigat cu un scor de:%d",
                         scor);
                refresh();
                sleep(3);
                // se deseneaza meniul
                clear();
                mvprintw(0, 0, "Meniu Principal");
                mvprintw(1, 0, "1. New Game");
                mvprintw(2, 0, "2. Resume    ");
                mvprintw(3, 0, "3. Quit");
                mvprintw(1, 11, "<-");

                wattron(ecran, A_REVERSE);
                mvwprintw(ecran, 1, 0, "1. New Game");
                wattroff(ecran, A_REVERSE);
                loc = 1;
                refresh();
                break;
              }
            }
          }
          // se opreste citirea continua de caractere deoarece nu ne trebuie in
          // meniul principal
          nodelay(ecran, FALSE);
        } else {
          // daca se da resume inainte de a incepe un joc it zice sa incepi un
          // joc
          if (pierdut == 1) {
            mvprintw(4, 0, "Jocul inceput a fost pierdut.");
          } else {
            if (pierdut == 0) {
              mvprintw(4, 0, "Nu ai inceput nici-un joc.");
            } else {
              mvprintw(4, 0, "Jocul inceput a fost castigat.");
            }
          }
          if (ainceput2 == 1) {
            mvprintw(4, 0,
                     "                                                         "
                     "      ");
            mvprintw(4, 0, "Apasa pe New Game.");
            if (ainceput3 == 1) {
              mvprintw(4, 0, "                            ");
              mvprintw(4, 0, "Refuz sa mai fac ceva daca nu apesi New Game.");
            }
            ainceput3 = 1;
          }
          ainceput2 = 1;
        }
      }
      // daca ne aflam pe quit cand dam enter iesim din while-ul infinit
      if (loc == 3) {
        break;
      }
    }
  }
  /* Se închide fereastra ncurses */
  endwin();

  return 0;
}
