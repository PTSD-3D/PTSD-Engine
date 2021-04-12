    function Update (n)
      --You first need to define this class in C++
      --If you're creating a variable just for this .lua please 
      --define it as a local variable.
      local dir = vec3:new(0, 0, 0)
      local deadZone = vec2:new(1.5, 1.5)
      --If we are using relative mouse position, this method returns the delta position of the mouse
      local mouseDirection = getMouseRelativePosition()

      if keyPressed(PTSDKeys.A) then
        dir = vec3:new(-1, 0, 0)
        translate(dir)
      end
      if keyPressed(PTSDKeys.W) then
        dir = vec3:new(0, 0, -1)
        translate(dir)
      end
      if keyPressed(PTSDKeys.S) then
        dir = vec3:new(0, 0, 1)
        translate(dir)
      end
      if keyPressed(PTSDKeys.D) then
        dir = vec3:new(1, 0, 0)
        translate(dir)
      end

      print(mouseDirection.x)
      print(mouseDirection.y)

      if (math.abs(mouseDirection.x) >= deadZone.x or math.abs(mouseDirection.y) >= deadZone.y) then
      
      end
      centerMouse()
      return true
    end

    Exit = false  --Please keep this or Lua explodes