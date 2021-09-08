
EnableGlobals();

require("ui.util.T7OverchargedUtil")

-- Initialize everything, table needs to have the following properties:
--    mapname or modname: Enables debug mode and hot reloading when launched via the launcher
--    filespath: The path to the mod or map files that will be used for hot reloading eg [[.\maps\zm_factory\]]
--    workshopid: The id of the workshop item so the dll can be found
function InitializeT7Overcharged( options )
  if CoD.T7Overcharged then
    return false
  end

  local debug = false
  if options.mapname and Engine.GetCurrentMap() == options.mapname or
     options.modname and Engine.UsingModsUgcName() ==  options.modname then
    debug = true
  end

    -- The path that we copy the dll's from
  local dllPath = debug and options.filespath .. [[T7Overcharged\x64\Release\]] or [[..\..\workshop\content\311210\]] .. options.workshopid .. "\\"
    -- The dll's needed for the calls, the first one being the one that actually get's called
  local dlls = { "T7Overcharged.dll" }


  -- Make sure all needed dll's are moved to the bo3 root folder
  for i = 1, #dlls do
    CopyFile( dllPath..dlls[i], ".\\"..dlls[i] )
  end

  SafeCall(function()
    require("package").loadlib( dlls[1], "init" )()
  end)

  if debug then
    T7Overcharged.InitHotReload( options.filespath )
  end
end

function StartHotReload( luiRoot, controller )
  local timer = nil
  local refreshMenu = nil

  if not CoD.HotReloadMenus then
    CoD.HotReloadMenus = {}
  end

  -- Make sure we don't start reloading multiple times
  if CoD.HotReloadMenus[luiRoot.menuName] then
    return
  else
    CoD.HotReloadMenus[luiRoot.menuName] = true
  end

  refreshMenu = function()
    timer:close()

    local updateHud = 0
    SafeCall(function() 
      updateHud = T7Overcharged.CheckForHotReload()
    end)

    if updateHud == 1 then
      local parent = luiRoot:getParent()
      luiRoot:close()
      parent.T7HudMenuGameMode = LUI.createMenu[luiRoot.menuName]( controller )
      parent:addElement( parent.T7HudMenuGameMode )

      timer = LUI.UITimer.newElementTimer(1000, true, refreshMenu)
      parent.T7HudMenuGameMode:addElement(timer)

      luiRoot = parent.T7HudMenuGameMode
    else
      timer = LUI.UITimer.newElementTimer(1000, true, refreshMenu)
      luiRoot:addElement(timer)
    end
  end
  timer = LUI.UITimer.newElementTimer(1000, true, refreshMenu)
  luiRoot:addElement(timer)
end