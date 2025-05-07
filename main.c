// Copyright [2024] <Theodor Vulpe>
// Realizat de Theodor Vulpe - seria 315CB

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Elibereaza memoria asociata unei matrice
void elibereaza_matrice(int **a, int N) {
    for (int i = 0; i < N; i++) {
        free(a[i]);
    }
    free(a);
    a = NULL;
}

void deplasare_coloana(int **a, int N, int coloana, int nr_pozitii) {
    // Repeta deplasarea circulara pe coloana
    for (int x = 1; x <= nr_pozitii; x++) {
        int aux = a[N - 1][coloana];
        for (int i = N - 1; i > 0; i--) {
            a[i][coloana] = a[i - 1][coloana];
        }
        a[0][coloana] = aux;
    }
}

void afisare_mat(int **a, int N, int M) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }
}

// Returneaza numarul de combinatii castigatoare pe linii
int verifica_linii(int **a, int M, int *scor_obtinut, int *ap) {
    int nr_castiguri = 0;

    *scor_obtinut = 0;

    for (int i = 0; i < 3; i++) {
        // Pentru fiecare linie, cauta secventa de lungime maxima

        int streak = 1, simbol_curent = a[i][0];
        int streak_maxim = -1, simbol_maxim;

        for (int j = 1; j < M; j++) {
            if (a[i][j] == simbol_curent) {
                streak++;

            } else {
                if (streak > streak_maxim) {
                    streak_maxim = streak;
                    simbol_maxim = simbol_curent;
                }

                simbol_curent = a[i][j];
                streak = 1;
            }
        }

        // La finalul liniei, verifica daca secventa ramasa este maximala.
        if (streak > streak_maxim) {
            streak_maxim = streak;
            simbol_maxim = simbol_curent;
        }

        // Verifica daca am gasit o secventa de cel putin trei elemente
        if (streak_maxim >= 3) {
            nr_castiguri++;
            *scor_obtinut += streak_maxim;
            if (simbol_maxim == 7) {
                *scor_obtinut += streak_maxim;
            }
        }
    }
    return nr_castiguri;
}

// Returneaza numarul de combinatii castigatoare pe diagonale
int verifica_diagonale(int **a, int M, int *scor_obtinut, int *ap) {
    int nr = 0;

    *scor_obtinut = 0;

    // Verifica diagonalele "principale"
    for (int j = 0; j + 2 < M; j++) {
        int element = a[0][j];
        if (a[1][j + 1] == element && a[2][j + 2] == element) {
            // Trebuie verificat sa nu fie un "X", care se evalueaza separat
            if (!(a[0][j + 2] == element && a[2][j] == element)) {
                nr++;
                *scor_obtinut += 7;
                if (element == 7) {
                    *scor_obtinut += 7;
                }
            }
        }
    }

    // Verifica diagonalele "secundare"
    for (int j = M - 1; j - 2 >= 0; j--) {
        int element = a[0][j];
        if (a[1][j - 1] == element && a[2][j - 2] == element) {
            // Trebuie verificat sa nu fie un "X", care se evalueaza separat
            if (!(a[0][j - 2] == element && a[2][j] == element)) {
                nr++;
                *scor_obtinut += 7;
                if (element == 7) {
                    *scor_obtinut += 7;
                }
            }
        }
    }

    return nr;
}

// Returneaza numarul de combinatii tip "X" castigatoare
int verifica_x(int **a, int M, int *scor_obtinut, int *ap) {
    int nr_x = 0;

    *scor_obtinut = 0;

    // Parcurge coloanele si verifica forma "X"
    for (int j = 1; j < M - 1; j++) {
        int element = a[1][j];
        if (a[0][j - 1] == element && a[0][j + 1] == element
        && a[2][j - 1] == element && a[2][j + 1] == element) {
            nr_x++;
            *scor_obtinut += 21;
            if (element == 7) {
                *scor_obtinut += 21;
            }
        }
    }

    return nr_x;
}

/*
 * Returneaza numarul de combinatii castigatoare din cadran.
 * Primeste ca parametri o matrice, numarul de coloane si o variabila 
 * prin care se intoarce scorul.
*/
int nr_castiguri(int **a, int N, int M, int *scor_obtinut) {
    // Vector de aparitii pentru a retine numarul de simboluri distincte.
    int *ap = calloc(10, sizeof(int));
    if (ap == NULL) {
        elibereaza_matrice(a, N);
        return 1;
    }

    int scor_linii = 0, scor_diagonale = 0, scor_x = 0, nr = 0;
    nr += verifica_linii(a, M, &scor_linii, ap);
    nr += verifica_diagonale(a, M, &scor_diagonale, ap);
    nr += verifica_x(a, M, &scor_x, ap);
    *scor_obtinut = scor_linii + scor_diagonale + scor_x;

    int simboluri_distincte = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < M; j++) {
            int elem_crt = a[i][j];
            if (ap[elem_crt] == 0) {
                simboluri_distincte++;
                ap[elem_crt] = 1;
            }
        }
    }

    if (simboluri_distincte <= 2) {
        *scor_obtinut += 100;
    } else if (simboluri_distincte <= 4) {
        *scor_obtinut += 15;
    }

    free(ap);
    ap = NULL;

    return nr;
}

// Inlocuieste, pe rand, fiecare simbol si returneaza castigul maxim
int schimb_maxim(int **a, int N, int M) {
    int castig_maxim = 0;

    // Parcurge cadranul
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < M; j++) {
            int simbol_initial = a[i][j];

            // Parcurge simbolurile
            for (int x = 0; x <= 9; x++) {
                a[i][j] = x;

                int castig = 0;
                // Calculeaza castigul curent din cadran
                nr_castiguri(a, N, M, &castig);

                if (castig > castig_maxim) {
                    castig_maxim = castig;
                }

                a[i][j] = simbol_initial;
            }
        }
    }

    return castig_maxim;
}

// Readuce o coloana rotita la forma initiala
void coloana_forma_intiala(int **mat_init, int **mat_modif, int N,
int M, int coloana) {
    for (int i = 0; i < N; i++) {
        mat_modif[i][coloana] = mat_init[i][coloana];
    }
}

// Roteste, pe rand, cate doua coloane si returneaza castigul maxim posibil
int doua_coloane_maxim(int **a, int N, int M) {
    /* 
     * Este necesar sa facem o copie a matricei pentru a putea
     * reveni la forma initiala.
    */
    int **copie;

    copie = malloc(N * sizeof(int *));
    if (copie == NULL) {
        elibereaza_matrice(a, N);
        return 1;
    }

    for (int i = 0; i < N; i++) {
        copie[i] = calloc(M, sizeof(int));

        if (copie[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(copie[i]);
            }
            free(copie);
            elibereaza_matrice(a, N);
            return 1;
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            copie[i][j] = a[i][j];
        }
    }

    int castig_maxim = 0;

    /*
     * Consideram toate rotirile posibile pentru toate perechile posibile
     * de cate doua coloane.
    */
    for (int col1 = 0; col1 < M - 1; col1++) {
        for (int rotiri1 = 0; rotiri1 <= N; rotiri1++) {
            deplasare_coloana(a, N, col1, rotiri1);

            for (int col2 = col1 + 1; col2 < M; col2++) {
                for (int rotiri2 = 0; rotiri2 <= N; rotiri2++) {
                    deplasare_coloana(a, N, col2, rotiri2);

                    int castig = 0;
                    nr_castiguri(a, N, M, &castig);
                    if (castig > castig_maxim) {
                        castig_maxim = castig;
                    }

                    // A doua coloana aleasa revine la forma initiala
                    coloana_forma_intiala(copie, a, N, M, col2);
                }
            }

            // Prima coloana aleasa revine la forma initiala
            coloana_forma_intiala(copie, a, N, M, col1);
        }
    }

    free(copie);
    copie = NULL;

    return castig_maxim;
}

// Necesar pentru a folosi o structura de tip coada
struct coord {
    int linie, coloana;
};

// Algoritmul lui Lee pentru a determina drumul de cost minim
int Lee(int **a, int N, int M) {
    struct coord *coada;

    // Multiplier pentru dimensiunea cozii
    int dim_coada = 1;

    // Alocam initial memorie pentru 3 * M elemente
    coada = malloc(3 * M * dim_coada * sizeof(struct coord));

    if (coada == NULL) {
        elibereaza_matrice(a, N);
        return 1;
    }

    int stanga = 0, dreapta = 0;
    coada[dreapta].linie = 0;
    coada[dreapta].coloana = 0;

    int **cost, **viz;

    // Alocare memorie matrice cost

    cost = malloc(3 * sizeof(int*));

    if (cost == NULL) {
        elibereaza_matrice(a, N);
        free(coada);
        coada = NULL;
        return 1;
    }

    for (int i = 0; i < 3; i++) {
        cost[i] = calloc(M, sizeof(int));
        if (cost[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(cost[i]);
            }
            elibereaza_matrice(a, N);
            free(coada);
            coada = NULL;
            free(cost);
            cost = NULL;
            return 1;
        }
    }

    // Alocare memorie matrice viz (vizite)

    viz = malloc(3 * sizeof(int*));

    if (viz == NULL) {
        for (int i = 0; i < 3; i++) {
            free(cost[i]);
        }
        free(cost);
        cost = NULL;
        free(coada);
        coada = NULL;
        elibereaza_matrice(a, N);
        return 1;
    }

    for (int i = 0; i < 3; i++) {
        viz[i] = calloc(M, sizeof(int));
        if (viz[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(viz[j]);
            }
            for (int i = 0; i < 3; i++) {
                free(cost[i]);
            }
            free(viz);
            viz = NULL;
            free(cost);
            cost = NULL;
            free(coada);
            coada = NULL;
            elibereaza_matrice(a, N);
            return 1;
        }
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < M; j++) {
            cost[i][j] = INT_MAX;
        }
    }

    // Vectori de deplasare pentru a calcula mai usor vecinii
    int *di, *dj;

    di = malloc(4 * sizeof(int));

    if (di == NULL) {
        for (int i = 0; i < 3; i++) {
            free(viz[i]);
            free(cost[i]);
        }
        free(viz);
        viz = NULL;
        free(cost);
        cost = NULL;
        free(coada);
        coada = NULL;
        elibereaza_matrice(a, N);
        return 1;
    }

    dj = malloc(4 * sizeof(int));

    if (dj == NULL) {
        for (int i = 0; i < 3; i++) {
            free(viz[i]);
            free(cost[i]);
        }
        free(di);
        di = NULL;
        free(viz);
        viz = NULL;
        free(cost);
        cost = NULL;
        free(coada);
        coada = NULL;
        elibereaza_matrice(a, N);
        return 1;
    }

    di[0] = 0; di[1] = 1; di[2] = 0; di[3] = -1;
    dj[0] = 1; dj[1] = 0; dj[2] = -1; dj[3] = 0;

    cost[0][0] = 0;

    // Cat timp mai exista elemente in coada
    while (stanga <= dreapta) {
        int lin_crt, col_crt;
        lin_crt = coada[stanga].linie;
        col_crt = coada[stanga].coloana;

        for (int k = 0; k < 4; k++) {
            int lin_vec, col_vec;
            lin_vec = lin_crt + di[k];
            col_vec = col_crt + dj[k];

            if (lin_vec >= 0 && lin_vec < 3 && col_vec >= 0 && col_vec < M) {
                int dif = abs(a[lin_vec][col_vec] - a[0][0]);
                int cost_potential = cost[lin_crt][col_crt] + dif;

                if (cost_potential < cost[lin_vec][col_vec]) {
                    cost[lin_vec][col_vec] = cost_potential;

                    dreapta++;
                    // Daca coada nu este suficient de mare, realocam memorie
                    if (dreapta >= 3 * M * dim_coada) {
                        dim_coada++;
                        coada = realloc(coada, 3 * M * dim_coada
                        * sizeof(struct coord));
                        if (coada == NULL) {
                            for (int i = 0; i < 3; i++) {
                                free(viz[i]);
                                free(cost[i]);
                            }
                            free(di);
                            di = NULL;
                            free(dj);
                            dj = NULL;
                            free(viz);
                            viz = NULL;
                            free(cost);
                            cost = NULL;
                            free(coada);
                            coada = NULL;
                            elibereaza_matrice(a, N);
                            return 1;
                        }
                    }
                    coada[dreapta].linie = lin_vec;
                    coada[dreapta].coloana = col_vec;
                }
            }
        }

        stanga++;
    }

    int raspuns = cost[2][M - 1];

    for (int i = 0; i < 3; i++) {
        free(viz[i]);
        free(cost[i]);
    }
    free(di);
    di = NULL;
    free(dj);
    dj = NULL;
    free(viz);
    viz = NULL;
    free(cost);
    cost = NULL;
    free(coada);
    coada = NULL;

    return raspuns;
}

int main() {
    int nr_task = 0, N = 0, M = 0, **a;

    scanf("%d %d %d", &nr_task, &N, &M);

    a = malloc(N * sizeof(int *));
    if (a == NULL) {
        return 1;
    }

    for (int i = 0; i < N; i++) {
        a[i] = calloc(M, sizeof(int));
        if (a[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(a[j]);
            }
            free(a);
            a = NULL;
            return 1;
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%d", &a[i][j]);
        }
    }

    int coloana = 0, nr_pozitii = 0, nrc = 0, scor_obtinut = 0;
    int T = 0, scor_total = 0;

    switch (nr_task) {
        case 1:
            scanf("%d %d", &coloana, &nr_pozitii);
            deplasare_coloana(a, N, coloana, nr_pozitii);
            afisare_mat(a, N, M);

            break;
        case 2:
            nrc = nr_castiguri(a, N, M, &scor_obtinut);
            printf("%d\n%d\n", nrc, scor_obtinut);

            break;
        case 3:
            scanf("%d", &T);

            for (int i = 1; i <= T; i++) {
                scanf("%d %d", &coloana, &nr_pozitii);

                deplasare_coloana(a, N, coloana, nr_pozitii);

                int scor_obtinut = 0;
                nr_castiguri(a, N, M, &scor_obtinut);
                scor_total += scor_obtinut;
            }

            printf("%d\n", scor_total);
            break;

        case 4:
            printf("%d\n", schimb_maxim(a, N, M));
            break;

        case 5:
            printf("%d\n", doua_coloane_maxim(a, N, M));
            break;

        case 6:
            printf("%d\n", Lee(a, N, M));
            break;
    }

    elibereaza_matrice(a, N);

    return 0;
}
