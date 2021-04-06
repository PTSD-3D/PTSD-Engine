-- defines a factorial function
    --print("enter a number:")
    --a = io.read("*number")        -- read a number
    --print(fact(a))

    function Update (n)
      if keyPressed(4) then
        print("a")
        --Llama a mover
        translate({-1,0,0})
      end
      if keyPressed(26) then
        print("w")
        translate({0,0,-1})
      end
      if keyPressed(22) then
        print("s")
        translate({0,0,-1})
      end
      if keyPressed(7) then
        print("d")
        translate({1,0,0})
      end
      return true
    end

    Exit = false  --O se lo pones a Lua o se enfada