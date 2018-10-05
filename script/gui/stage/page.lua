local mt = g_class()

function mt:init()
	self.o_widgets = {}
end

function mt:update()
	for _, v in ipairs(self.o_widgets) then
		v:update()
	end
end

function mt:draw()
	for _, v in ipairs(self.o_widgets) then
		v:draw()
	end
end

return mt