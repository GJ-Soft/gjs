#include <cstdio>
#include <cstdlib>
#include <cstring>

int main() {
    // setenv: copia, lo más seguro
    if (setenv("GJS_TEST", "hola", 1) != 0) { perror("setenv"); return 1; }
    printf("getenv tras setenv: [%s]\n", getenv("GJS_TEST"));

    // putenv: el buffer DEBE persistir → malloc sin free
    char *p = strdup("GJS_TEST2=mundo");
    if (putenv(p) != 0) { perror("putenv"); return 1; }
    printf("getenv tras putenv: [%s]\n", getenv("GJS_TEST2"));
    return 0;
}
