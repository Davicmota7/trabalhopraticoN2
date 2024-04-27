#include <stdio.h>
#include <stdlib.h>
typedef struct {
    double x;
    double y;
} Point;


// ler vértices no arquivo

Point *VerticesDoArquivo(const char *nomedoArquivo, int *numVertices) {
    FILE *arquivo = fopen(nomedoArquivo, "r");
   
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return NULL;
    }

    fscanf(arquivo, "%d", numVertices);

    Point *vertices = (Point *)malloc(*numVertices * sizeof(Point));
   
    if (vertices == NULL) {
     
        printf("Erro na memória.\n");
        fclose(arquivo);
        
        return NULL;
    }

    for (int i = 0; i < *numVertices; i++) {
        fscanf(arquivo, "%lf %lf", &vertices[i].x, &vertices[i].y);
    }

    fclose(arquivo);
    return vertices;
}


// área do triangulo
float AreaTriangulo(Point A, Point B, Point C) {
    return 0.5 * ((A.x * (B.y - C.y)) + (B.x * (C.y - A.y)) + (C.x * (A.y - B.y)));
}

// área de um polígono
double AreaDoPoligono(Point vertices[], int numVertices) {
   
    double area = 0.0;
    int j;

    for (int i = 0; i < numVertices; i++) {
        j = (i + 1) % numVertices;
        area += (vertices[i].x * vertices[j].y) - (vertices[j].x * vertices[i].y);
    }

    area = area / 2.0;
    if (area < 0) {
        area = -area;
          }

    return area;
}

int main() {
    int numVertices;
    Point *vertice;
    double area;

    vertice = VerticesDoArquivo("vertices.txt", &numVertices);
    if (vertice == NULL) {
        return 1;
    }

    area = AreaDoPoligono(vertice, numVertices);
    
    printf("A área do polígono é: %.2lf\n", area);

    free(vertice);
    return 0;
}
