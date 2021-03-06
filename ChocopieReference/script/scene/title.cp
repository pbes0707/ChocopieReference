﻿# encoding:utf-8

import 'gameobject/*'

class Scene < SceneBase
	include EventHandler

    def initialize
        super

		@fontTitle = Font.new("gulim.ttc", 40)
		@fontVersion = Font.new("gulim.ttc", 20)
		@fontTitle.retain = 1
		@fontVersion.retain = 1

		@fontTitle.style = BOLD
		size = @fontTitle.query "Chocopie Reference"

		@titleText = Sprite.new(nil, size.w+5, size.h)
		@titleText.map "titleText"

		@titlePosition = Point.new(200,156)
		@titleSize = Size.new(size.w,size.h)

		@animatePosition = Point.new((@titlePosition.x - 15).to_f / 30, (@titlePosition.y - 363).to_f / 30)
		@animateSize = Size.new((@titleSize.w - 350).to_f / 30, (@titleSize.h - 32).to_f / 30)
		@animateTimer = Timer.new(30)

		$graphic.target = "titleText"
        drawText(0,0,"Chocopie Reference",@fontTitle, 5,4)
		$graphic.target = nil
    end

    def dispose
        super
    end

    def drawText(x,y,msg,font,sx,sy)
        font.color = Color.DarkGray
        font.draw(x+sx,y+sy,msg)
        font.color = Color.Black
        font.draw(x,y,msg)
    end
    def update
        crt = $graphic.size
        $graphic.color = Color.White
        $graphic.fill(0,0,crt.w,crt.h)

		if @animateTimer.done
			@titlePosition -= @animatePosition
			@titleSize -= @animateSize

			if @titlePosition.x.round == 15
				$scene.change "view"
				return
			end
		end

        @titleText.stretch(@titlePosition.x, @titlePosition.y, 
							@titleSize.w, @titleSize.h)

        @fontVersion.style = BOLD
        drawText(708,345,"api version",@fontVersion, 2,1)
        @fontVersion.style = NONE
        drawText(758,366,"1.41.0",@fontVersion, 1,1)
    end

	def keyDown(key)
		@animateTimer.start
	end
	def leftDown(x,y)
		@animateTimer.start
	end
end