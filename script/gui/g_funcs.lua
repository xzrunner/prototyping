function g_class(base)
    local mt = {}
    mt.__index = mt
    if type(base) == 'string' then
        base = require(base)
    end
    mt.__base = base
    setmetatable(mt, base)
    return mt, base
end

function g_object(mt, ...)
    local obj = setmetatable({}, mt)
    if obj.init then
        obj:init(...)
    end
    return obj
end