#include "fractol.h"

int32_t		mouse_hook(int button, int x, int y, t_window *win)
{
	if (button == 4)
	{
		win->mods.xoffset -= win->mods.scale * ((double)x - (float)win->disp.center.x) / 11;
		win->mods.yoffset += win->mods.scale * ((double)y - (float)win->disp.center.y) / 11;
		win->mods.scale *= 1.1;
	}
	else if (button == 5)
	{
		win->mods.xoffset += win->mods.scale * ((double)x - (double)win->disp.center.x) / 11;
		win->mods.yoffset -= win->mods.scale * ((double)y - (double)win->disp.center.y) / 11;
		win->mods.scale /=  1.1;
	}
	win->mods.update = 1;
	return (0);
}

int32_t		mouse_moved(int x, int y, t_window *win)
{
	win->mods.xmouse = (x - (float)win->disp.center.x) / win->disp.width;
	win->mods.ymouse = (y - (float)win->disp.center.y) / win->disp.height;
	win->mods.update = 1;
	return (0);
}
