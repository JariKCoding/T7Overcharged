
local json = require("ui.util.json")

-- Copies a given file to a new location
function CopyFile( old_path, new_path )
  local old_file = require("io").open( old_path, "rb" )
  local new_file = require("io").open( new_path, "wb" )
  local old_file_sz, new_file_sz = 0, 0
  if not old_file or not new_file then
    return false
  end
  while true do
    local block = old_file:read( 2^13 )
    if not block then 
      old_file_sz = old_file:seek( "end" )
      break
    end
    new_file:write( block )
  end
  old_file:close()
  new_file_sz = new_file:seek( "end" )
  new_file:close()
  return new_file_sz == old_file_sz
end
-- Write the data to a file
function WriteToFile( path, data )
  local file = require("io").open( path, "w" )

  if not file then
    return false
  end

  file:write( data )
  file:close()

  return true
end
-- Read the result data
function ReadJsonFile( path )
  local resultFile = require("io").open( path, "r" )
  if resultFile then
    local resultContent = resultFile:read( "*all" )
    resultFile:close()
    require("os").remove( path )
    -- Return an empty table in case of an empty return
    if resultContent == "" then
      return {}
    end
    return json.decode( resultContent )
  end
  return {}
end
-- Function that we can use to safely call io and dll functions without crashing the client
function SafeCall( FunctionRef )
  local ok, result = pcall( FunctionRef )
  
  if not ok and result then
    Engine.ComError( Enum.errorCode.ERROR_UI, "SafeCall error: " .. result )
  elseif result then
    return result
  end
end
