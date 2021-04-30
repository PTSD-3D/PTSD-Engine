local prefabs = reqPrefab 
local sceneConfig = reqSceneConfigurations 
local Scene={
 Entities={	Goal=
        {
		Transform = {position={x=0.0,y=2.5133743286132812,z=84.76555633544922},rotation={x=0.0,y=0.0,z=0.0},scale={x=0.521728515625,y=0.521728515625,z=0.521728515625}},
            Components= {
            }
        }
        ,
	Platform_000=prefabs.Platform({
		Transform = {position={x=0.0,y=0.0,z=-6.6010847091674805},rotation={x=0.0,y=0.0,z=0.0},scale={x=10.905817031860352,y=1.0,z=-10.831353187561035}}}),
	Platform_001=prefabs.Platform({
		Transform = {position={x=7.747493743896484,y=0.0,z=11.914058685302734},rotation={x=0.0,y=0.0,z=-18.05662959930421},scale={x=3.8450777530670166,y=3.651704788208008,z=-3.6825337409973145}}}),
	Platform_002=prefabs.Platform({
		Transform = {position={x=-4.851972579956055,y=0.0,z=23.379627227783203},rotation={x=0.0,y=0.0,z=10.730294634208086},scale={x=3.8450777530670166,y=3.651704788208008,z=-3.6825337409973145}}}),
	Platform_003=prefabs.Platform({
		Transform = {position={x=7.747493743896484,y=0.0,z=32.83156204223633},rotation={x=0.0,y=0.0,z=-18.05662959930421},scale={x=3.8450777530670166,y=3.651704788208008,z=-3.6825337409973145}}}),
	Platform_004=prefabs.Platform({
		Transform = {position={x=4.768166542053223,y=0.0,z=45.469566345214844},rotation={x=0.0,y=0.0,z=0.0},scale={x=2.203453540802002,y=1.0,z=4.325438022613525}}}),
	Platform_005=prefabs.Platform({
		Transform = {position={x=-5.274786949157715,y=0.0,z=53.66787338256836},rotation={x=0.0,y=0.0,z=0.0},scale={x=2.203453540802002,y=1.0,z=4.325438022613525}}}),
	Platform_006=prefabs.Platform({
		Transform = {position={x=5.200106620788574,y=0.0,z=63.49094009399414},rotation={x=0.0,y=0.0,z=0.0},scale={x=2.203453540802002,y=1.0,z=4.325438022613525}}}),
	Platform_007=prefabs.Platform({
		Transform = {position={x=0.0,y=0.0,z=84.19429016113281},rotation={x=0.0,y=0.0,z=0.0},scale={x=10.905817031860352,y=1.0,z=-10.831353187561035}}}),
	Platform_008=prefabs.Platform({
		Transform = {position={x=-1.5478811264038086,y=3.36752986907959,z=-4.006361961364746},rotation={x=0.0,y=0.0,z=-18.05662959930421},scale={x=3.8450777530670166,y=3.651704788208008,z=-3.6825337409973145}}}),
	Spawn=
        {
		Transform = {position={x=0.0,y=2.5133743286132812,z=-9.152349472045898},rotation={x=0.0,y=0.0,z=0.0},scale={x=0.521728515625,y=0.521728515625,z=0.521728515625}},
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
