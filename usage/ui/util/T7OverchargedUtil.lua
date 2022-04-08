

-- Function that we can use to safely call io and dll functions without crashing the client
function SafeCall( FunctionRef )
  local ok, result = pcall( FunctionRef )
  
  if not ok and result then
    Engine.ComError( Enum.errorCode.ERROR_UI, "SafeCall error: " .. result )
  elseif result then
    return result
  end
end
