
# Strike-Xlib-Window-Manager

a featerful and rich window manager


## Features

#### Reperenting
![Reperenting](https://github.com/orbabayof/Strike-Xlib-window-manager-/blob/main/readme/reprenting.gif)

#### Tiling

![Tiling](https://github.com/orbabayof/Strike-Xlib-window-manager-/blob/main/readme/tiling.gif)

#### Workspaces

![Workspaces](https://github.com/orbabayof/Strike-Xlib-window-manager-/blob/main/readme/workspaces.gif)
## configuration

to configure keybindings for example, is very easy compared to other window managers, allow me to demostrate:
```cpp
void settings::initKeyBinds()
{
	using enum window_t;

	static keybind<wm> st_term{"k", AnyModifier, spawn("st")};
	static keybind<wm> vs_code{"c", AnyModifier, spawn("code")};
	static keybind<wm> second{"w", AnyModifier, spawn("google-chrome-stable")};

	static keybind<allWindows> hide_window{"h", AnyModifier, hideWin};
	static keybind<allWindows> show_window{"s", AnyModifier, showWin};
  

	generate_workspace_nav_keybinds();
}

```

