#include <stdio.h>
#include <stdlib.h>

//βρίσκει το άθροισμα των σβόλων χρυσού κατά μήκος μίας διαδρομής
int find_sum(int n, int *path) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += path[i];
    }
    return sum;
}

//συγκρίνει δύο διαδρομές ως προς το μεγαλύτερο άθροισμα σβώλων χρυσού και επιστρέφει αυτή με το μεγαλύτερο
int* find_best_path(int *path1, int *path2, int n) {
    return (find_sum(n, path1) > find_sum(n, path2)) ? path1 : path2;
}

//επιστρέφει τη διαδρομή με το μεγαλύτερο άθροισμα σβώλων χρυσού
int* find_path(int currentLine, int currentColumn, int **mine, int n) {
    int* path = (int *)calloc(n,  sizeof(int));

    //τερματισμός αναδρομής
    if(currentLine == n || currentColumn == n) {
        return path;
    }

    path = find_best_path(find_path(currentLine+1, currentColumn, mine, n), find_path(currentLine + 1, currentColumn+1, mine, n),n);
    path[currentLine] = mine[currentLine][currentColumn];
    return path;
}

int main() {
    //δέσμευση μνήμης και δημιουργία 2D πίνακα mine
    int n;
    FILE *in = fopen("gold.in", "r");
    fscanf(in, "%d",&n);
    int **mine = (int **)malloc(n * sizeof(int *));
    if (mine == NULL) {
        printf("Memory allocation failed\n");
        return 1; 
    }
    for (int i = 0; i < n; i++) {
        mine[i] = (int *)malloc(n * sizeof(int));
        if (mine[i] == NULL) {
            printf("Memory allocation failed\n");
            return 1;
        }
    }

    //καταχώρηση τιμών στα στοιχεία του πίνακα
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fscanf(in, "%d %*[^0-9]", &mine[i][j]);
        }
    }

    //υπολογισμός βέλτιστης διαδρομής
    int* best_path = find_path(0, 0, mine, n);

    //εκτύπωση διαδρομής
    for (int i = 0; i < n; i++) {
        if (i == n-1) {
            printf("%d\n",best_path[i]);
        } else {
            printf("%d => ",best_path[i]);
        }
    }
    
    //εκτύπωση μέγιστου πλήθους σβώλων
    printf("%d\n",find_sum(n,best_path)); 
    
    //αποδέσμευση μνήμης
    for (int j = 0; j < n; j++) {
        free(mine[j]);
    }
    free(mine);
    return 0;
}