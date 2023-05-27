#include <cstdlib>

#include <iostream>

#include<time.h>

#include<stdlib.h>

#include<math.h>


using namespace std;

void printGrid(int grid[5][5]) {

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (grid[i][j] == 1 || grid[i][j] == 0)
                cout << grid[i][j] << " ";
            else
                cout << char(grid[i][j]) << " "; //za izpis kvadratkov, X...
        }
        cout << endl;
    }
}

void printGridInGame(int grid[5][5]) {

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (grid[i][j] == 1 || grid[i][j] == 0)
                cout << "?" << " "; //neznano polje v procesu igre ce je voda ali ladja
            else
                cout << char(grid[i][j]) << " "; //izpise polja ki smo jih ze poskusili/zadeli
        }
        cout << endl;
    }

}

void inputLadja(int grid[5][5]) {
    int x, y;
    cout << endl << "Vnesi koodrinate ladjice(vrstica, stolpec): ";
    cin >> x >> y;

    while (cin.fail()) { //za char input prevention
        cout << endl << "Koordinate morajo biti v formatu X Y, npr 0 0, 1 1, 2 2...\nVnesi ponovno:";
        cin.clear(); //clears cin
        cin.ignore(256, '\n'); //clears buffer
        cin >> x >> y;
    }

    while (x > 4 || y > 4 || x < 0 || y < 0) {
        cout << endl << "Neveljavne koordinate. Vnesi ponovno. ";
        cin >> x >> y;
    }

    while (grid[x][y] == 1) {
        cout << endl << "Mesto je ze polno. Vnesi ponovno. ";
        cin >> x >> y;
    }

    grid[x][y] = 1; //fill spot
    printGrid(grid);
}

int randomX() {
    return rand() % 5;
}
int randomY() {
    return rand() % 5;
}

void generirajLadje(int grid[5][5]) {
    int rand_x = randomX();
    int rand_y = randomY();

    while (grid[rand_x][rand_y] == 1) {
        int rand_x = randomX();
        int rand_y = randomY();
    }
    grid[rand_x][rand_y] = 1;

}

int checkShip(int a, int b, int grid[5][5]) {

    if (grid[a][b] == 1) //bi lahko blo boljse ampak deluje
        return 1;
    else
        return 0;

}
void checkIfDifferentUsers(string user1, string user2) {

    while (user1 == user2) {
        cout << "Uporabnika morata imeti razlicna imena! Vnesi ponovno.\n";
        cout << "Ime igralca 1: ";
        cin >> user1;
        cout << "\nIme igralca 2: ";
        cin >> user2;
    }

}

void systemPause() {
    cout << "Press enter to continue...\n";
    char tmp[2];
    cin.clear();
    cin.ignore(1000, '\n');
    cin.getline(tmp, '\n');

}

int main() {

    //setting appropriate cls command
    #ifdef _WIN32
    char cls[4] = "cls";
    #else
    char cls[17] = "printf \"\33c\e[3J\""; //command for clearing screen which works with Linux and macOS
    #endif
    int a, b; //koodrinate za napad
    int grid[5][5] = {}; //grid za user1
    int grid2[5][5] = {}; //grid za user2
    int stLadjic = 5;
    bool igra = false;
    int player1_ships = stLadjic;
    int player2_ships = stLadjic;
    srand(time(0));
    string user1;
    string user2;
    int selection;
    bool loop = true; //za switch
    do {
        cout << "DOBRODOSLI V POTAPLJANJU LADJIC!\n";
        cout << "IZBERITE NACIN IGRE:\n";
        cout << "1. 2 IGRALCA(1V1)\n";
        cout << "2. VS AI(proti racunalniku)\n";
        cout << "----------------------\n";
        cin >> selection;
        switch (selection) {

        case 1: {
            loop = false;
            cout << "Ime igralca 1: ";
            cin >> user1;
            cout << "\nIme igralca 2: ";
            cin >> user2;
            checkIfDifferentUsers(user1, user2);

            system(cls);

            cout << "\n\n" << "Ladje naj vnese " << user1 << "\n";
            for (int i = 0; i < stLadjic; i++) {
                inputLadja(grid);
            }
            system(cls);

            cout << "\n\n" << "Ladje naj vnese " << user2 << "\n";
            for (int i = 0; i < stLadjic; i++) {
                inputLadja(grid2);
            }

            igra = true;
            system(cls);

            while (igra) {
                cout << user1 << ", vnesi koodrinate, ki jih bos napadel!";
                cin >> a >> b;
                while (a > 4 || b > 4 || a < 0 || b < 0) {
                    cout << endl << "\nNeveljavne koordinate. Vnesi ponovno. ";
                    cin >> a >> b;
                }
                while (grid2[a][b] == 254 || grid2[a][b] == 88) {
                    cout << "To polje si ze poskusil. Vnesi ponovno: ";
                    cin >> a >> b;
                }

                if (checkShip(a, b, grid2) == 1) {
                    cout << "\nZADETEK\n";
                    grid2[a][b] = 88; //X
                    player2_ships--;
                } else {
                    cout << "\nZGRESIL SI!\n";
                    grid2[a][b] = 254; //kvadrat
                }

                printGridInGame(grid2);

                if (player1_ships == 0) {
                    cout << "\n\n\nZMAGAL JE IGRALEC 2!";
                    igra = false;
                    break;
                }
                if (player2_ships == 0) {
                    cout << "\n\n\nZMAGAL JE IGRALEC 1!";
                    igra = false;
                    break;
                }

                cout << "\n" << user2 << ", vnesi koodrinate, ki jih bos napadel!";
                cin >> a >> b;
                while (a > 4 || b > 4 || a < 0 || b < 0) {
                    cout << endl << "\nNeveljavne koordinate. Vnesi ponovno. ";
                    cin >> a >> b;
                }
                while (grid[a][b] == 254 || grid[a][b] == 88) {
                    cout << "To polje si ze poskusil. Vnesi ponovno: ";
                    cin >> a >> b;
                }
                if (checkShip(a, b, grid) == 1) {
                    cout << "\nZADETEK!\n";
                    grid[a][b] = 88; //X
                    player1_ships--;
                } else {
                    cout << "\nZGRESIL SI!\n";
                    grid[a][b] = 254; //kvadrat
                }

                printGridInGame(grid);

                if (player1_ships == 0) {
                    cout << "\n\n\nZMAGAL JE IGRALEC 2!";
                    igra = false;
                    break;
                }
                if (player2_ships == 0) {
                    cout << "\n\n\nZMAGAL JE IGRALEC 1!";
                    igra = false;
                    break;
                }

            }

            cout << "\n\n\nKONCNA POLJA: \n\n\n";
            cout << "X = POTOPLJENA \n";
            cout << char(254) << " = ZGRESENO \n\n";
            cout << "1 = LADJA \n";
            cout << "0 = VODA \n";
            cout << "\nIgralec 1: \n";
            printGrid(grid);
            cout << "\nIgralec 2: \n";
            printGrid(grid2);
            systemPause(); //Used to be a system("PAUSE");
            break;
        }
        case 2: {
            loop = false;
            cout << "Ime igralca: ";
            cin >> user1;

            system(cls);

            cout << "\n\n" << "Vnesi svoje ladje, " << user1 << "\n";
            for (int i = 0; i < stLadjic; i++) {
                inputLadja(grid);
            }
            for (int i = 0; i < stLadjic; i++) {
                generirajLadje(grid2);
            }
            system(cls);
            igra = true;

            while (igra) {
                cout << user1 << ", vnesi koodrinate, ki jih bos napadel!";
                cin >> a >> b;
                while (a > 4 || b > 4 || a < 0 || b < 0) {
                    cout << endl << "\nNeveljavne koordinate. Vnesi ponovno. ";
                    cin >> a >> b;
                }
                while (grid2[a][b] == 254 || grid2[a][b] == 88) {
                    cout << "To polje si ze poskusil. Vnesi ponovno: ";
                    cin >> a >> b;
                }
                if (checkShip(a, b, grid2) == 1) {
                    cout << "\nZADETEK\n";
                    grid2[a][b] = 88; //X
                    player2_ships--;
                } else {
                    cout << "\nZGRESIL SI!\n";
                    grid2[a][b] = 254; //kvadrat
                }

                printGridInGame(grid2);

                if (player1_ships == 0) {
                    cout << "\n\n\nZMAGAL JE RACUNALNIK!";
                    igra = false;
                    break;
                }
                if (player2_ships == 0) {
                    cout << "\n\n\nZMAGAL JE " << user1 << "!";
                    igra = false;
                    break;
                }

                a = randomX();
                b = randomY();
                cout << "\nRacunalnik napada koodrinate:" << a << " " << b << "\n";

                while (grid[a][b] == 254 || grid[a][b] == 88) {
                    a = randomX();
                    b = randomY();
                }

                if (checkShip(a, b, grid) == 1) {
                    cout << "\nZADETEK!\n";
                    grid[a][b] = 88; //X
                    player1_ships--;
                } else {
                    cout << "\nRacunalnik je zgresil!\n";
                    grid[a][b] = 254; //kvadrat
                }

                printGridInGame(grid);

                if (player1_ships == 0) {
                    cout << "\n\n\nZMAGAL JE RACUNALNIK!";
                    igra = false;
                    break;
                }
                if (player2_ships == 0) {
                    cout << "\n\n\nZMAGAL JE " << user1 << "!";
                    igra = false;
                    break;
                }

            }
            cout << "\n\n\nKONCNA POLJA: \n\n\n";
            cout << "X = POTOPLJENA \n";
            cout << char(254) << " = ZGRESENO \n\n";
            cout << "1 = LADJA \n";
            cout << "0 = VODA \n";
            cout << "\n" << user1 << ": \n";
            printGrid(grid);
            cout << "\nRACUNALNIK: \n";
            printGrid(grid2);
            systemPause(); //Used to be a system("PAUSE");
            break;
        } //end case 2
        default: {
            cout << "Napacen vnos!";
            loop = true;
            system(cls);
        }
        } //end switch

    }
    while (loop);
}
