# Loțan Roberto-Gabriel

## Durata implementarii

Cu tot cu pregatirea pentru aceasta tema am stat pe parcursul a mai multor
zile aproape 18 ore.

Inainte de a ma apuca de implementat pentru a ma informa in legatura cu
interfata ncurses am stat aproximativ 8 ore.

1. Implementarea meniului a durat 3 ore.
2. Implementarea layout-ului ecranului de joc a durat 3 ore.
3. Implementaarea jocului 2048 a durat o ora jumatate, iar implementarea
scorului a luat 10 minute.
4. Implementarea mutarii auromate a luat o ora.
5. Implementarea verificarii daca jocul s-a terminat sau nu a durat 30
de minute.
6. Suplimentar am mai adaugat retinerea celui mai bun scor de pana acum,
asta durand 30 de minute.

## Explicarea codului

Prima functie genereaza la intamplare 2 numere din intervalul 0-3 care
reprezinta linia si coloana pana gaseste o celula libera pe care pune 2 sau 4.
A doua functie determina cate spatii libere sunt dupa fiecare mutare,
pentru a deteermina cea mai buna optiune, iar daca sunt mai multe
optiuni la fel de bune, se ia la intamplare una din acestea.
A trei a functie, cea de mutare a celulelor muta in directia respectiva
toate celulele, verifica daca sunt celule cu acelasi nr unu langa altul
si le imbina, apoi mai muta o data in directia respectiva pentru a elimina
spatiile goale create.
Urmatoarele 2 functii verifica daca s-a castigat sau s-a pierdut. Pentru
a se verifica daca s-a castigat se cauta numarul 2048, iar pentru a se
verifica daca s-a pierdut, cauta daca mai exista celule libere, in caz
contrar cauta daca sunt 2 celule alaturate care se pot imbina.
Ultima functie deseneaza tabla, ora si informatiile.

Srand primeste ora curenta pentru a primi un seed nou de fiecare data cand
deschizi jocul, astfel fiecare joc este diferit.
In joc puteti sa va deplasati in sus, jos, stanga si dreapta folosind tastele
W,A,S,D, iar cu tasta Q veti iesi in meniul principal.
In meniul principal va puteti deplasa cu sagetile sus si jos.
Ca implementare proprie am adaugat un topscor care retine cel mai bun scor
din toate meciurile jucate de pana acum, adaugand informatia intr-un fisier
pe care il apeleaza de fiecare data cand pormin jocul. Top scorul se reseteaza
daca apesi pe tasta R.
