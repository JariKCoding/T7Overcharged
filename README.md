[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)
[![Releases](https://img.shields.io/github/downloads/JariKCoding/T7Overcharged/total.svg)](https://github.com/JariKCoding/T7Overcharged/)

# T7Overcharged

**T7Overcharged** gives Call of Duty: Black Ops 3 modders the ability to take their mods to the next level by providing an API between Lua and C++ and providing already worked out components.

## Features
- Hot reloading of lua scripts
- UI Errors now give a stack trace and don't cause a freeze
- Extending the asset limits
- Printing to the in-game console from lua
- HTTP requests from lua
- Discord Rich Presence
- More to come!

## How to use
- Clone this repo or download the latest release.
- Copy the lua files to the mod/map you want to use this in.
- Copy the dll to the zone folder
- Add the following lines to your zone file:
```
rawfile,ui/util/T7Overcharged.lua
rawfile,ui/util/T7OverchargedUtil.lua
```
- Add the following lines in your main lua file:
```
require("ui.util.T7Overcharged")
```
- Under that add the following code but change variables to your map/mod's information

for a mod:
```
InitializeT7Overcharged({
	modname = "t7overcharged",
	filespath = [[.\mods\t7overcharged\]],
	workshopid = "45131545",
	discordAppId = nil--"{{DISCORD_APP_ID}}" -- Not required, create your application at https://discord.com/developers/applications/
})
```
for a map:
```
InitializeT7Overcharged({
	mapname = "zm_t7overcharged",
	filespath = [[.\usermaps\zm_t7overcharged\]],
	workshopid = "45131545",
	discordAppId = nil--"{{DISCORD_APP_ID}}" -- Not required, create your application at https://discord.com/developers/applications/
})
```

## Download

The latest version can be found on the [Releases Page](https://github.com/JariKCoding/T7Overcharged/releases).

## Compile from source

- Clone the Git repo. Do NOT download it as ZIP, that won't work.
- Update the submodules and run `premake5 vs2022` or simply use the delivered `generate.bat`.
- Build via solution file in `build\T7Overcharged.sln`.

## Credits

- [XLabsProjects](https://github.com/XLabsProject): Great project setup
- [Approved](https://github.com/approved): Asset limit extension
- [Serious](https://github.com/shiversoftdev): UI Error hash dvar

## License 

T7Overcharged is licensed under the GNUv3 license and its source code is free to use and modify. T7Overcharged comes with NO warranty, any damages caused are solely the responsibility of the user. See the LICENSE file for more information.