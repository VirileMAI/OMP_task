#include "class.h"
#include "func.h"

int main() {
    locale::global(locale("ru_RU.UTF-8"));
    wcin.imbue(locale());

    BookStore store;
    loop(store);
    return 0;
}
