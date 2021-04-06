-- defines a factorial function
    --print("enter a number:")
    --a = io.read("*number")        -- read a number
    --print(fact(a))

    function Update (n)
      local dir = vec3:new(0, 0, 0)
      if keyPressed(4) then
        print("a")
        --Llama a mover
        dir = vec3:new(-1, 0, 0)
        translate(dir)
      end
      if keyPressed(26) then
        print("w")
        dir = vec3:new(0, 0, -1)
        translate(dir)
      end
      if keyPressed(22) then
        print("s")
        dir = vec3:new(0, 0, 1)
        translate(dir)
      end
      if keyPressed(7) then
        print("d")
        dir = vec3:new(1, 0, 0)
        translate(dir)
      end
      return true
    end

    Exit = false  --O se lo pones a Lua o se enfada