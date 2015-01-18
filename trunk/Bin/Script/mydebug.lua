
local function GoZeroBrane()
  local root_path = lfs.currentdir() .. "/Script/"
  root_path = root_path:gsub("\\", "/")
  local tbl_path = {    
  root_path,
  root_path .. "luasocket52/",
	root_path .. "AI/",
	root_path .. "Background/",
	root_path .. "Hero/",
	root_path .. "Object/",
	root_path .. "Shader/",
  }
  for key, value in pairs(tbl_path) do  
    local pkg_path = package.path  
    package.path = string.format("%s?.lua;%s", value, pkg_path)
  end
end

local mydebug = {
  _NAME = "mydebug",
  _VERSION = 0.1,
  _COPYRIGHT = "Damody",
  _DESCRIPTION = "Init Debugger for the Lua",
}

mydebug.gogo = gogo
mydebug.GoZeroBrane = GoZeroBrane
return mydebug
