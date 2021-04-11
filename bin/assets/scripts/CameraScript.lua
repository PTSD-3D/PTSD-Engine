    function Update (n)
      --You first need to define this class in C++
      --If you're creating a variable just for this .lua please 
      --define it as a local variable.
      local dir = vec3:new(0, 0, 0)
      local posX = getMousePosX()
      local posY = getMousePosY()
      
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

      print(posX);
      print(posY);

      return true
    end

    Exit = false  --Please keep this or Lua explodes