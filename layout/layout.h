#pragma once

#include <limits>
#include <tiler.h>

struct pixel_size
{
	int width{};
	int height{};

	pixel_size operator/=(int num)
	{
		width /= num;
		height /= num;

		return *this;
	}
};

class layout
{
  public:
	constexpr virtual ~layout() = default;
	constexpr virtual int maxWindowsPerWorkspace() const
	{
		return std::numeric_limits<int>::max();
	}
	virtual void order(tiler &t) const = 0;

  protected:
	auto &get_win_stack(tiler &t) const
	{
		return t.m_win_stack;
	}
	Screen *get_screen(const tiler &t) const
	{
		return t.m_screen;
	}
};

class defualt : public layout
{

  public:
	void order(tiler &t) const override;

//  protected:
  defualt() = default;
  friend const layout& defualtLayout();
};

const layout& defualtLayout();
