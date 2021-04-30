local prefabs = reqPrefab 
local sceneConfig = reqSceneConfigurations 
local Scene={
 Entities={	Goal=
        {
		Transform = {position={x=0.0,y=84.76555633544922,z=-37.48662567138672},rotation={x=0.0,y=0.0,z=0.0},scale={x=0.521728515625,y=0.521728515625,z=0.521728515625}},
            Components= {
            }
        }
        ,
	Platform_000=prefabs.Platform({
		Transform = {position={x=0.0,y=-6.6010847091674805,z=-40.0},rotation={x=0.0,y=0.0,z=0.0},scale={x=10.905817031860352,y=-10.831353187561035,z=1.0}}}),
	Platform_001=prefabs.Platform({
		Transform = {position={x=7.747493743896484,y=11.914058685302734,z=-40.0},rotation={x=0.0,y=-18.05662959930421,z=0.0},scale={x=3.8450777530670166,y=-3.6825337409973145,z=3.651704788208008}}}),
	Platform_002=prefabs.Platform({
		Transform = {position={x=-4.851972579956055,y=23.379627227783203,z=-40.0},rotation={x=0.0,y=10.730294634208086,z=0.0},scale={x=3.8450777530670166,y=-3.6825337409973145,z=3.651704788208008}}}),
	Platform_003=prefabs.Platform({
		Transform = {position={x=7.747493743896484,y=32.83156204223633,z=-40.0},rotation={x=0.0,y=-18.05662959930421,z=0.0},scale={x=3.8450777530670166,y=-3.6825337409973145,z=3.651704788208008}}}),
	Platform_004=prefabs.Platform({
		Transform = {position={x=4.768166542053223,y=45.469566345214844,z=-40.0},rotation={x=0.0,y=0.0,z=0.0},scale={x=2.203453540802002,y=4.325438022613525,z=1.0}}}),
	Platform_005=prefabs.Platform({
		Transform = {position={x=-5.274786949157715,y=53.66787338256836,z=-40.0},rotation={x=0.0,y=0.0,z=0.0},scale={x=2.203453540802002,y=4.325438022613525,z=1.0}}}),
	Platform_006=prefabs.Platform({
		Transform = {position={x=5.200106620788574,y=63.49094009399414,z=-40.0},rotation={x=0.0,y=0.0,z=0.0},scale={x=2.203453540802002,y=4.325438022613525,z=1.0}}}),
	Platform_007=prefabs.Platform({
		Transform = {position={x=0.0,y=84.19429016113281,z=-40.0},rotation={x=0.0,y=0.0,z=0.0},scale={x=10.905817031860352,y=-10.831353187561035,z=1.0}}}),
	Spawn=
        {
		Transform = {position={x=0.0,y=-9.152349472045898,z=-37.48662567138672},rotation={x=0.0,y=0.0,z=0.0},scale={x=0.521728515625,y=0.521728515625,z=0.521728515625}},
            Components= {
            }
        }
        },
		SceneConfig=
        {
        PhysicsConfig={
            Gravity = 5
        }
    }
}
return Scene
