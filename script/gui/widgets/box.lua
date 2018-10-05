local Graphics = require "moon.graphics"

local mt, base = g_class 'gui.widgets.widget'

function mt:init()
    base:init(self)

    self.o_width  = 200
    self.o_height = 200
	self.o_color = { 232, 232, 232 }
end

-- local function is_white(color)
-- 	return color[1] == 255 and color[2] == 255 and color[3] == 255
-- end

function mt:draw(x, y)
    base:draw(self)

    local w, h = self.o_width, self.o_height
    -- local x, y = self.o_x - w * 0.5, self.o_y - h * 0.5

    Graphics.set_color(self.o_color)
    Graphics.rectangle('fill', x - w * 0.5, y - h * 0.5, w, h)
	-- if is_white(self.o_color) then
	-- 	Graphics.set_color({ 0, 0, 0 })
 --    	Graphics.rectangle('line', x, y, w, h)
	-- end
end

return mt