#include "run_game2.h"
#include "run_game1.h"
int main (int argc, char **argv)
{
    playground pg1 = run_game1();

    int game = run_game2(pg1);

    return 0;
}
