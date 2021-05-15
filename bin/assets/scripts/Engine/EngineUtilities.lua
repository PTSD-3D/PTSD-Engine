local ns = Namespace
local debugger = require("debugger")

--- ns.Call function to wrap pcall so we don't have to do if ... else checks everywhere
---@param errorString string to log if something goes wrong
---@param funct function to call
---@param args any parameters for the function call
---@return any result of the function call or false on error
function ns.call(errorString, funct, ...)
	local status, ret = pcall(funct, ...)
	if status then return ret end
	local message = tostring(errorString .. ret)
	LOG(message, LogLevel.Error, 1)
	return false
end

--Añadimos le debugger al namespace para que no se tenga que pedir desde require en cada archivo
--Adding debugger to namespace to avoid 'require'ing it everywhere
--How to use and developer of the debugger: https://github.com/slembcke/debugger.lua
ns.debugger = debugger


