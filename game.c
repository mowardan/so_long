#include "so_long.h"

int main()
{
    int w = 64;
    int h = 64;
    void *a = mlx_init();
    void *b = mlx_new_window(a, 640, 640 , "game");
    void *s = mlx_xpm_file_to_image(a, "textures/henix.xpm", &w, &h);
    mlx_put_image_to_window(a, b, s, 0, 0);
    mlx_loop(a);
}