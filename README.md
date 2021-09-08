# T7Overcharged
[![Releases](https://img.shields.io/github/downloads/JariKCoding/T7Overcharged/total.svg)](https://github.com/JariKCoding/T7Overcharged/)

**T7Overcharged** gives Call of Duty: Black Ops 3 modders the ability to take their mods to the next level by providing an API between Lua and C++. It also provides a hot reload functionality and gives the possibility to remove the UI error hash.

# Warning - This is still in early development

## How to use
- Clone this repo or download the latest release.
- Copy the files to the mod/map you want to use this in.
- Add the following lines to your zone file:
```
rawfile,ui/util/T7Overcharged.lua
rawfile,ui/util/T7OverchargedUtil.lua
rawfile,ui/util/json.lua
```
- Add the following lines in your main lua file:
```
require("ui.util.T7Overcharged")
```
- Under that add the following code but change variables to your map's information

for a mod:
```
InitializeT7Overcharged({
	modname = "t7overcharged",
	filespath = [[.\mods\t7overcharged\]],
	workshopid = "45131545"
})
```
for a map:
```
InitializeT7Overcharged({
	mapname = "zm_t7overcharged",
	filespath = [[.\usermaps\zm_t7overcharged\]],
	workshopid = "45131545"
})
```
- To start hot reload, add the following code to the PreLoadCallback in your hud's menu file
```
StartHotReload(HudRef, InstanceRef)
```
- To disable the UI error hash, add the following code above the last piece of code !!warning, this might crash your game!!
```
T7Overcharged.RemoveUiErrorHash()
```

## Pushing to the workshopid

Before you push to the workshop, you need to copy the .dll file(s) in T7Overcharged\x64\Release\ to your mod/maps zone folder (where the .ff, .xpak etc files are).

## Download

The latest version can be found on the [Releases Page](https://github.com/JariKCoding/T7Overcharged/releases).

## License 

T7Overcharged is licensed under the MIT license and its source code is free to use and modify. T7Overcharged comes with NO warranty, any damages caused are solely the responsibility of the user. See the LICENSE file for more information.