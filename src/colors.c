#include <wolf.h>
#include <math.h>
#include <stdint.h>

/*
**  b << 16 | g << 8 | r
*/

static int32_t hsv_to_rgb(int32_t h, float s, float v)
{
	float c;
	float hh;
	float x;
	float m;
	int32_t rgb;

	if (h > 360 || h < 0 || s < 0.0 || s > 1.0 || v < 0.0 || v > 1.0)
		return (0x00000000);
	c = v * s;
	hh = fmod((float)h / 60, 6);
	x = c * (1.0 - fabs(fmod(hh, 2) - 1));
	m = v - c;
	if (h < 60)
		rgb = (int8_t)((x + m) * 255) << 8 | (int8_t)((c + m) * 255);
	else if (h < 120)
		rgb = (int8_t)((c + m) * 255) << 8 | (int8_t)((x + m) * 255);
	else if (h < 180)
		rgb = (int8_t)((x + m) * 255) << 16 | (int8_t)((c + m) * 255) << 8;
	else if (h < 240)
		rgb = (int8_t)((c + m) * 255) << 16 | (int8_t)((x + m) * 255) << 8;
	else if (h < 300)
		rgb = (int8_t)((c + m) * 255) | (int8_t)((x + m) * 255) << 16;
	else
		rgb = (int8_t)((x + m) * 255) | (int8_t)((c + m) * 255) << 16;
	return (rgb);
}

void	calculate_rgb_from_hsv(int32_t colors[360], const float s, const float v)
{
	int i;

	i = -1;
	while (++i < 360)
	{
		colors[i] = hsv_to_rgb(i, s, v);
	}
}
