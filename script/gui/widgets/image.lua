local Graphics = require "moon.graphics"

local mt, base = g_class 'gui.widgets.widget'

function mt:init()
    base:init(self)

    self.o_img = nil
end

function mt:update()
    base:update(self)
end

function mt:draw(x, y)
    base:draw(self)

	if self.o_img then
		local trans = { x, y }
		Graphics.draw(self.o_img, trans)
	end
end

return mt