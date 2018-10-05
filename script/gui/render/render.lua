local Graphics = require "moon.graphics"

local M = {}

function M.draw_outline(x, y, width, height)
	Graphics.rectangle('fill', x, y, width, 1)
	Graphics.rectangle('fill', x, y + height - 1, width, 1)
	Graphics.rectangle('fill', x, y, 1, height)
	Graphics.rectangle('fill', x + width - 1, y, 1, height)	
end

return M