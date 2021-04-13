    function Update (n)
      --You first need to define this class in C++
      --If you're creating a variable just for this .lua please 
      --define it as a local variable.
      local dir = vec3:new(0, 0, 0)
      local sensitivity = 1 --Should be able to modify it from another class
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

      rotateCamera(mouseDirection * sensitivity)

      return true
    end

    Exit = false  --Please keep this or Lua explodes