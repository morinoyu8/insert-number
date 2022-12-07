# insert-number

左に行数を追加できます.

## build

```
make
```

## example

hello-world.c
```c
#include <stdio.h>

int main(void) {
    printf("Hello World!\n");
    return 0;
}
```

```
inu hello-world.c
```

hello-world-linenum.txt
```
 1  #include <stdio.h>
 2  
 3  int main(void) {
 4      printf("Hello World!\n");
 5      return 0;
 6  }
```

## オプション

- `-rem`

行数のあるプログラムの行数を削除します.

  - 行数からプログラムまでのスペースは2つである必要があります.
  - 1行目の行数が1である必要があります.
  - 行数は右揃えである必要があります.

hello-world.txt
```
 1  #include <stdio.h>
 2  
 3  int main(void) {
 4      printf("Hello World!\n");
 5      return 0;
 6  }
```

```
inu -rem hello-world.txt
```

hello-world-remnum.c
```c
#include <stdio.h>

int main(void) {
    printf("Hello World!\n");
    return 0;
}
```

- `-space int`

行数までのスペース数を指定できます. 1までのスペース数です. (default: 2)

hello-world.c
```c
#include <stdio.h>

int main(void) {
    printf("Hello World!\n");
    return 0;
}
```

```
inu -space 5 hello-world.c
```

hello-world-linenum.txt
```
     1  #include <stdio.h>
     2  
     3  int main(void) {
     4      printf("Hello World!\n");
     5      return 0;
     6  }
```

