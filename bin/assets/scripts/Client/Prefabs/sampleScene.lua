local prefabs = reqPrefab 
local sceneConfig = reqPrefab 
local Scene={
 Entities={	DiscoCop=
        {
		Transform = {position={x=-0.0,y=0.0,z=0.0},rotation={x=-0.0,y=0.0,z=0.0},scale={x=1.0,y=1.0,z=1.0}},
        Components= {
            name="boombox",arguments={0.5,false,Resources.Sounds.PTSD_Anthem.id,-1}
        }
        }
        ,
	Enemy=prefabs.Enemy({
		Transform = {position={x=0.0,y=0.0,z=-37.56254196166992},rotation={x=-90.0,y=90.0,z=0.0},scale={x=1,y= 4.60,z=1}}})},
		SceneConfig=sceneConfig.sampleScene({})
}
return Scene
