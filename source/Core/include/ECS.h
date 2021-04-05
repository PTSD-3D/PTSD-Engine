#pragma once
namespace PTSD
{
	using CmpIdType = unsigned long;

	enum CmpId: CmpIdType
	{
		Transform = 0,
		Scriptable, //Basically MonoBehaviour
		Rigidbody,
		Collider,
		Debug,

		MAXCOMPONENTS
	};

	using TagType = unsigned long;

	//IMPORTANT manually assign a correct bit
	enum Tag :TagType
	{
		Manger = 0,
		GameObject,
		SampleTag,


		MAXTAGS_
		
	};
}
