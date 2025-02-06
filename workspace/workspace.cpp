#include "util.h"
#include <algorithm>
#include <keybindUtil.h>
#include <map>
#include <settings.h>
#include <workspace.h>

#include <list>

#include <X11/X.h>
#include <X11/Xlib.h>
#include <cstddef>
#include <iterator>
#include <vector>

workspace::workspace(Screen *screen) : m_screen{screen}, m_tiler{screen}
{
}

void workspace::add(Window w)
{
	if (map(w))
		m_tiler.add(w);
}

void workspace::remove(Window w)
{
	unmap(w);
	m_tiler.extract(w);
}

void workspace::hide()
{
	std::ranges::for_each(m_tiler.data(), unmap);
}

void workspace::show()
{
	std::ranges::for_each(m_tiler.data(), map);
}

workspace_manager::workspace_manager(int screen_num, std::size_t num_of_workspaces)
	: m_screen{ScreenOfDisplay(dpy(), screen_num)}, m_curr_workspace{1}
{
	m_workspaces.reserve(num_of_workspaces);

	for (std::size_t i{0}; i < num_of_workspaces; ++i)
		m_workspaces.emplace_back(workspace{m_screen});
}

workspace &workspace_manager::workSpace(std::size_t workspace_num)
{
	if (workspace_num == 0 || workspace_num > m_workspaces.size())
		return m_workspaces[m_curr_workspace];

	return m_workspaces[workspace_num - 1];
}

void workspace_manager::moveTo(std::size_t workspace_num)
{
	workSpace(m_curr_workspace).hide();
	workSpace(workspace_num).show();

	m_curr_workspace = workspace_num;
}

void workspace_manager::add(Window w)
{
	workSpace(m_curr_workspace).add(w);
}

void workspace_manager::remove(Window w)
{
	workSpace(m_curr_workspace).remove(w);
}

workspace_manager &screen_manager::workspaceManagerScreen(std::size_t idx)
{
	// a bit more complex for big O(n/2) time
	if (idx <= (m_workspaces_managers.size() / 2))
	{
		auto it{m_workspaces_managers.begin()};
		std::advance(it, idx);
		return *it;
	}
	else
	{
		auto it{m_workspaces_managers.rend()};
		std::advance(it, m_workspaces_managers.size() - idx);
		return *it;
	}
}

workspace_manager &screen_manager::screenNum(std::size_t num)
{
	if (num < m_workspaces_managers.size())
	{
		return workspaceManagerScreen(num);
	}

	return workspaceManagerScreen(0);
}

void screen_manager::init()
{
	for (int curr_screen{0}; curr_screen < ScreenCount(dpy()); ++curr_screen)
		m_workspaces_managers.emplace_back(workspace_manager{curr_screen, settings::defualt_num_of_workspaces});
}
