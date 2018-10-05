local Graphics = require "moon.graphics"

local mt, base = g_class 'gui.widgets.widget'

function mt:init()
    base:init(self)

    self.o_width = 100
    self.o_height = 30

    self.o_text = "text"
    self.v_color = { 0, 0, 0 }
end

function mt:update()
    base:update(self)
end

function mt:draw(x, y)
    base:draw(self)

    local trans = { x, y }
    Graphics.print(self.o_text, trans, self.v_color)
end

return mt