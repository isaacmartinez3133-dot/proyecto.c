#include <stdio.h>
#define MAX_OYENTES 100
#define canciones 10

// aqui leo los votos //
int leerVotos(int votos[MAX_OYENTES][3])
{
    int i = 0;
    int n;

    printf("Ingrese los votos de los oyentes\n");
    printf("Para terminar escriba -1 en el primer voto\n\n");

    while (i < MAX_OYENTES)
    {
        printf("Oyente %d\n", i + 1);

        for (n = 0; n < 3; n++)
        {
            do
            {
                printf("Voto %d: ", n + 1);
                scanf("%d", &votos[i][n]);

                if (votos[i][n] > 9)
                {
                    printf("Ingrese una cancion del 1 al 10\n");
                }

            } while (votos[i][n] > 9);

            /* terminar captura */
            if (n == 0 && votos[i][0] == -1)
            {
                return i;
            }
        }

        i++;
    }

    return i;
}
/* FUNCION PARA CALCULAR LOS VOTOS DE CADA CANCION */
void calcularVotos(int votos[MAX_OYENTES][3], int totalDeOyentes, int puntosCanciones[canciones])
{
    int i;
    int n;
    for (int n = 0; n < 10; n++)
    {
         puntosCanciones[n]= 0;
    }
    for (i = 0; i < totalDeOyentes; i++)
    {
        puntosCanciones[votos[i][0]] += 3;
        puntosCanciones[votos[i][1]] += 2;
        puntosCanciones[votos[i][2]] += 1;
    }
}

/* FUNCION PARA MOSTRAR LOS VOTOS */
void mostrarVotos(int puntosCanciones[canciones])
{
    int i;

    printf("\nPuntos por canción:\n");

    for (i = 0; i < canciones; i++)
    {
        printf("Cancion %d: %d puntos\n", i + 1, puntosCanciones[i]);
    }
}

/* FUNCION PARA OBTENER LAS DOS CANCIONES MAS VOTADAS */
void cancionesGanadoras(int puntosCanciones[canciones],
                        int *primera, int *segunda)
{
    int i;

    *primera = 0;
    *segunda = 0;

    for (i = 0; i < canciones; i++)
    {
        if (puntosCanciones[i] > puntosCanciones[*primera])
        {
            *segunda = *primera;
            *primera = i;
        }
        else if (i != *primera &&
                 puntosCanciones[i] > puntosCanciones[*segunda])
        {
            *segunda = i;
        }
    }
}

/* FUNCION PARA CALCULAR LOS PUNTOS DE LOS OYENTES */
void calcularPuntosOyentes(int votos[MAX_OYENTES][3],
                            int totalDeOyentes,
                            int primera,
                            int segunda,
                            int puntosOyentes[MAX_OYENTES])
{
    int i, j;

    for (i = 0; i < totalDeOyentes; i++)
    {
        puntosOyentes[i] = 0;

        int tienePrimera = 0;
        int tieneSegunda = 0;

        for (j = 0; j < 3; j++)
        {
            if (votos[i][j] == primera)
            {
                tienePrimera = 1;
            }

            if (votos[i][j] == segunda)
            {
                tieneSegunda = 1;
            }
        }

        if (tienePrimera)
        {
            puntosOyentes[i] += 30;
        }

        if (tieneSegunda)
        {
            puntosOyentes[i] += 20;
        }

        if (tienePrimera && tieneSegunda)
        {
            puntosOyentes[i] += 10;
        }
    }
}

//con esta pongo quien gano//
int obtenerGanador(int puntosOyentes[MAX_OYENTES], int totalDeOyentes)
{
    int i;
    int ganador = 0;

    for (i = 1; i < totalDeOyentes; i++)
    {
        if (puntosOyentes[i] > puntosOyentes[ganador])
        {
            ganador = i;
        }
    }

    return ganador;
}

//aqui van los puntos de los bros//
void mostrarPuntosOyentes(int puntosOyentes[MAX_OYENTES],
                            int totalDeOyentes)
{
    int i;

    printf("\nPuntos de los radioescuchas:\n");

    for (i = 0; i < totalDeOyentes; i++)
    {
        printf("Radioescucha %d: %d puntos\n", i, puntosOyentes[i]);
    }
}

int main()
{
    int votos[MAX_OYENTES][3];

    int puntosCanciones[canciones];

    int puntosOyentes[MAX_OYENTES];

    int totalDeOyentes;

    int primera, segunda;

    int ganador;

    totalDeOyentes = leerVotos(votos);

    calcularVotos(votos, totalDeOyentes, puntosCanciones);

    mostrarVotos(puntosCanciones);

    cancionesGanadoras(puntosCanciones, &primera, &segunda);

    printf("\nLa canción más votada es: %d\n", primera);
    printf("La que le sigue es: %s\n", segunda);

    calcularPuntosOyentes(votos, totalDeOyentes,
                            primera, segunda,
                            puntosOyentes);

    mostrarPuntosOyentes(puntosOyentes, totalDeOyentes);

    ganador = obtenerGanador(puntosOyentes, totalDeOyentes);

    printf("\nEl ganador es: Radioescucha número %d\n", ganador);

    return 0;
}
