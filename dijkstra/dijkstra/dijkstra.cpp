#include <iostream>

using namespace std;

const int matDim = 6; /// Modificando questo valore si imposta la dimensione della matrice di adiacenza

int matrix[matDim][matDim] = { -1,2,5,1,-1,-1, /// matrice di adiacenza
                            3,-1,3,2,-1,-1,
                            8,6,-1,3,1,5,
                            7,2,3,-1,1,-1,
                            -1,-1,1,1,-1,2,
                            -1,-1,8,-1,4,-1 };

struct verticeType
{
    int distanza = -1;
    bool visitato = 0;
};

/**
    (*) selVertice: ritorna la posizione del vertice con distanza minima
                che non è stato ancora visistato.
    (*) verticiVisitati: ritorna la conta dei vertici visitati
    (*) Dijkstra: algoritmo di dijkstra. Al termine della procedura l'array
              di vertici conterrà tutte le distanze minime.
    (*) StampaMatrix: stampa la matrice.
    (*) stampaStatoVertici: stampa le informazioni dei vertici.
    (*) Reset di un array di vertici (visitato = 0) (distanza = -1)
*/
int selVertice(verticeType vertice[], int n);
int verticiVisitati(verticeType vertice[], int n);
void Dijkstra(int mat[matDim][matDim], verticeType vertice[], int verticeOrigine, int n);
void StampaMatrix(int rig, int col, int matrix[matDim][matDim]);
void stampaStatoVertici(verticeType vertice[], int n);
void resetVertici(verticeType vertice[], int n);
int main()
{
    const int n = matDim;
    StampaMatrix(n, n, matrix);
    verticeType vertice[n];
    cout << "Stato dei vertici prima di ogni esecuzione dell'algoritmo di Dijkstra :" << endl;
    stampaStatoVertici(vertice, n);
    for (int i = 0; i < n; i++) /// ripeti per numero di vertici
    {
        int verticeOrigine = i;
        resetVertici(vertice, n);
        cout << "Eseguo algoritmo di Dijkstra sulla matrice con vertice origine = " << char(verticeOrigine + 65) << endl;
        Dijkstra(matrix, vertice, verticeOrigine, n);
        stampaStatoVertici(vertice, n);
    }
    return 0;
}

int verticiVisitati(verticeType vertice[], int n)
{
    int cont = 0;
    for (int i = 0; i < n; i++)
        if (vertice[i].visitato)cont++;
    return cont;
}
int selVertice(verticeType vertice[], int n)
{
    int pos, minimo;
    int i = 0;
    bool trovato = 0;
    do
    {
        if (!vertice[i].visitato)
        {
            if (vertice[i].distanza > -1)
            {
                pos = i;
                minimo = vertice[i].distanza;
                trovato = 1;
            }
        }
        i++;
    } while (!trovato && i < n);
    if (trovato)
    {
        for (int i = 0; i < n; i++)
            if (!vertice[i].visitato)
            {
                if (vertice[i].distanza <= minimo && vertice[i].distanza > -1)pos = i;
            }
        return pos;
    }
    else return -1;
}
void Dijkstra(int mat[matDim][matDim], verticeType vertice[], int verticeOrigine, int n)
{
    /// i vertici sono inizializzati con visitato = 0 e distanza = -1
    vertice[verticeOrigine].distanza = 0; ///set origine
    int rig, col;
    while ((verticiVisitati(vertice, n)) != n) /// ripeti fino a quando tutti i vertici non sono stati visitati
    {
        int v = selVertice(vertice, n); /// seleziona un vertice non visitato con distanza minore tra tutti
        rig = v; /// posizionati sulla riga del vertice scelto
        col = 0;
        for (int i = col; i < n; i++)
        {
            if (mat[rig][i] != -1) /// se v è collegato con il vertice in esame
            {
                /// se trovi un percorso migliore sostituisci l'etichetta
                if (vertice[i].distanza > vertice[v].distanza + mat[rig][i] || vertice[i].distanza == -1)
                    vertice[i].distanza = vertice[v].distanza + mat[rig][i];
            }
        }
        vertice[v].visitato = 1; /// imposta che il vertice v è stato visitato
    }
}

void stampaStatoVertici(verticeType vertice[], int n)
{
    cout << endl;
    cout << "Vertici : ";
    for (int i = 65; i < n + 65; i++)cout << char(i) << " ";
    cout << endl;
    cout << "Distanze dei vertici : ";
    for (int i = 0; i < n; i++)cout << vertice[i].distanza << " ";
    cout << endl;
    cout << "Stato visitato dei vertici : ";
    for (int i = 0; i < n; i++)cout << vertice[i].visitato << " ";
    cout << endl; cout << endl;
}

void StampaMatrix(int rig, int col, int matrix[matDim][matDim])
{
    cout << "CONTENUTO MATRICE:" << endl;
    for (int i = 0; i < rig; i++)
    {
        cout << endl;
        for (int j = 0; j < col; j++) cout << matrix[i][j] << "\t";
    }
    cout << endl; cout << endl;
}

void resetVertici(verticeType vertice[], int n)
{
    for (int i = 0; i < n; i++)
    {
        vertice[i].distanza = -1;
        vertice[i].visitato = 0;
    }
}
