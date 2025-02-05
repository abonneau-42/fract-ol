#include <stdlib.h>

int main() {
    int *ptr = malloc(sizeof(int));
    *ptr = 42;  // Utilisation après libération : cela doit être détecté par ASan
    return *ptr;
}
