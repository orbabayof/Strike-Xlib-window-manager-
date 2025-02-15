#pragma once

#include "tiler.h"
#include <X11/X.h>
#include <X11/Xlib.h>
#include <list>
#include <vector>

class workspace
{
  public:
	workspace(Screen *screen);

	void add(Window w);
	void remove(Window w);

	void hide();
	void show();

	// might add showIFEmpty

  private:
	// used to config next variables
	Screen *m_screen{nullptr};

	tiler m_tiler{};

	Window attachWorkspaceRoot();
};

class workspace_manager
{
  public:
	workspace_manager(int screen_num, std::size_t num_of_workspaces);
	workspace_manager() = delete;

	void moveTo(std::size_t workspace_num);
	workspace &workSpace(std::size_t workspace_num);

	void add(Window w);
	void remove(Window w);

  private:
	Screen *m_screen{};
	// indexing starts from 1
	std::size_t m_curr_workspace{};
	std::vector<workspace> m_workspaces{};
};

class screen_manager
{
  public:
	screen_manager();
	void init();

	workspace_manager &screenNum(std::size_t screen_num);
	workspace_manager &currScreen();

	void changeScreen(std::size_t next_screen);

  private:
	// ordered by screen number
	std::list<workspace_manager> m_workspaces_managers;
	std::size_t m_curr_screen{};

	workspace_manager &workspaceManagerScreen(std::size_t idx);
};
