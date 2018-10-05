local Render   = require 'gui.render.render'
local Graphics = require 'moon.graphics'
local Box  = require 'gui.widgets.box'
local Text = require 'gui.widgets.text'

local mt, base = g_class 'gui.widgets.widget'

function mt:init()
    base:init(self)

    self.o_width  = 40
    self.o_height = 20

    local bg = g_object(Box)
    bg.o_width  = self.o_width
    bg.o_height = self.o_height        
    self.v_background = bg

    local text = g_object(Text)
    text.o_text = 'btn'
    self.v_text = text
end

function mt:update()
    base:update(self)
end

function mt:draw(x, y)
    base:draw(self)

    self.v_background:draw(x, y)
    self.v_text:draw(x, y)
end

function mt:on_mouse_down(x, y)
    print("down btn")    
end

function mt:on_mouse_up(x, y)
    print("up btn")
end

function mt:on_mouse_move(x, y)
    print("move btn")
end

return mt