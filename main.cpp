#include "header.h"
#include "SearchForm.h"
#include <clocale>
#include <Windows.h>

int main(int argc, char *argv[])
{
    srand(time(NULL));
    QApplication a(argc, argv);
    SearchForm w;
    w.show();
    return a.exec();
}
