local Graphics = require "moon.graphics"

local mt, base = g_class 'gui.widgets.widget'

function mt:init()
    base:init(self)

    self.o_width  = 200
    self.o_height = 200
	self.o_color = { 232, 232, 232 }
end

function mt:draw(x, y)
    base:draw(self)

    local w, h = self.o_width, self.o_height
    -- local x, y = self.o_x, self.o_y

    Graphics.set_color(self.o_color)
    Graphics.circle('fill', x, y, (w + h) * 0.25)
end

return mt