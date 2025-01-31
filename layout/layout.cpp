#include "util.h"
#include <X11/X.h>
#include <X11/Xlib.h>
#include <layout.h>

void defualt::order(tiler &t) const 
{
	auto &window_list{get_win_stack(t)};

	if (window_list.size() == 0)
		return;

	Screen *curr_screen{get_screen(t)};

	pixel_size currSize{.width = WidthOfScreen(curr_screen), .height = HeightOfScreen(curr_screen)};

	int curr_x{0}, curr_y{0};
	int next_x{0}, next_y{0};

	// we are going to swap between the width and height with the devision, starting with width
	bool isWidthDevided{true};

	// going to stop in the one before the last
	auto lastWin{--window_list.end()};

	for (auto curr{window_list.begin()}; curr != lastWin; ++curr)
	{
		curr_x = next_x;
		curr_y = next_y;

		if (isWidthDevided)
		{
			currSize.width /= 2;
			isWidthDevided = false;
			next_x += currSize.width;
		}
		else
		{
			currSize.height /= 2;
			isWidthDevided = true;
			next_y += currSize.height;
		}
		resize(curr_x, curr_y, currSize, *curr);
	}

	resize(next_x, next_y, currSize, *lastWin);
}

const layout& defualtLayout()
{
  static defualt d {};
  return d;
}
